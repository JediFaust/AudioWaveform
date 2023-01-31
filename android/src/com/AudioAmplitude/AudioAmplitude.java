package com.AudioAmplitude;
import org.qtproject.qt.android.bindings.QtActivity;
import android.os.Bundle;
import android.util.Log;
import android.media.MediaCodec;
import org.json.JSONArray;
import org.json.JSONException;
import java.lang.Math;

import android.media.AudioFormat;
import android.media.AudioTrack;
import android.media.MediaExtractor;
import android.media.MediaCodec;
import android.media.MediaFormat;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;




public class AudioAmplitude extends QtActivity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    private void getSamples(int[] samples, int size) {
        int lines = 60;
        int divider = size / lines;

        float[] resultSamples = new float[lines];
        JSONArray jsArray = new JSONArray();

        for (int i = 0; i < lines; i++) {
                float currentSample = 0;
                for(int j = i * divider; j < i * divider + divider; j++) {
                        currentSample += samples[j] * samples[j];
                        }
                float mean = currentSample / divider;
                float rms_point = (float) Math.sqrt(mean);

                resultSamples[i] = rms_point;
            try {
                jsArray.put(resultSamples[i]);
            } catch (JSONException e) {
                // Error
                break;
            }
        }

        Log.d("JavaLog", "loop finished~");
        transferSamples(jsArray.toString());
    }

    private static native void transferSamples(String _data);

    public int getAmplitude() {
        String path = "/storage/emulated/0/Download/pressure.mp3";

                        try {
                            MediaExtractor extractor = new MediaExtractor();
                            extractor.setDataSource(path);

                            int numTracks = extractor.getTrackCount();

                            MediaFormat format = new MediaFormat();

                            for (int i = 0; i < numTracks; i++) {
                                format = extractor.getTrackFormat(i);
                                if(format.getString(MediaFormat.KEY_MIME).startsWith("audio/")) {
                                    extractor.selectTrack(i);
                                    break;
                                }
                            }

                            int sampleRate = format.getInteger(MediaFormat.KEY_SAMPLE_RATE);
                            String mime = format.getString(MediaFormat.KEY_MIME);

                            int minBuffSize = AudioTrack.getMinBufferSize(sampleRate, AudioFormat.CHANNEL_OUT_STEREO, AudioFormat.ENCODING_PCM_16BIT);

                            MediaCodec deCoder = MediaCodec.createDecoderByType(mime);

                            deCoder.setCallback(new MediaCodec.Callback() {
                                private boolean inputEOS = false;
                                private boolean outputEOS = false;
                                private int sampleData[] = new int[minBuffSize * 8];
                                private int sampleIndex = 0;

                                @Override
                                public void onInputBufferAvailable(MediaCodec mediaCodec, int i) {
                                    if (inputEOS | outputEOS) return;

                                    ByteBuffer inputBuffer = deCoder.getInputBuffer(i);
                                    if (inputBuffer == null) return;

                                    long sampleTime = 0;
                                    int result = extractor.readSampleData(inputBuffer, 0);
                                    if (result >= 0) {
                                        sampleTime = extractor.getSampleTime();
                                        deCoder.queueInputBuffer(i, 0, result, sampleTime, 0);
                                        extractor.advance();
                                    } else {
                                        deCoder.queueInputBuffer(i, 0, 0, -1, MediaCodec.BUFFER_FLAG_END_OF_STREAM);
                                        inputEOS = true;
                                    }
                                }

                                @Override
                                public void onOutputBufferAvailable(MediaCodec mediaCodec, int i, MediaCodec.BufferInfo bufferInfo) {
                                    ByteBuffer outputBuffer = deCoder.getOutputBuffer(i);

                                    if (outputBuffer != null) {
                                        outputBuffer.rewind();
                                        outputBuffer.order(ByteOrder.LITTLE_ENDIAN);

                                        sampleData[sampleIndex++] = (int) outputBuffer.get();
                                    }
                                    outputEOS |= ((bufferInfo.flags & MediaCodec.BUFFER_FLAG_END_OF_STREAM) != 0);
                                    deCoder.releaseOutputBuffer(i, false);

                                    if (outputEOS) {
                                        getSamples(sampleData, sampleIndex);
                                        deCoder.stop();
                                        deCoder.release();
                                        extractor.release();
                                    }
                                }

                                @Override
                                public void onError(MediaCodec mediaCodec, MediaCodec.CodecException e) {
                                    Log.d("JavaLog", "Error on decoding: " + e.getMessage());
                                }

                                @Override
                                public void onOutputFormatChanged(MediaCodec mediaCodec, MediaFormat mediaFormat) {
                                    Log.d("JavaLog", "Format changed to: " + mediaFormat.toString());
                                }
                            });

                            deCoder.configure(format, null, null, 0);
                            deCoder.start();

                        } catch (IOException e) {
                            Log.d("JavaLog", "MediaCodec creation failed");
                        }

                        return 666;
    }
}


