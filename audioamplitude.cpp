#include <QJniObject>
#include <QGuiApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "audioamplitude.h"

audioamplitude::audioamplitude(QObject *parent)
    : QObject{parent}
{

}

void audioamplitude::getAmplitude() {
    QJniObject nativeObj = QNativeInterface::QAndroidApplication::context();

    nativeObj.callMethod<int>("getAmplitude", "()I");
}

extern "C" JNIEXPORT void JNICALL Java_com_AudioAmplitude_AudioAmplitude_transferSamples(JNIEnv *env, jobject, jstring _data){
    auto data = QJsonDocument::fromJson(env->GetStringUTFChars(_data, 0)).array().toVariantList();
    QList<float> tmpSamples;
    for (int i = 0; i < data.count(); i++) {
        qDebug() << "Sample in C++: " << data.at(i);
        tmpSamples.append(data.at(i).toFloat());
    }
    audioamplitude::samplesArr = tmpSamples;
    audioamplitude::samplesChanged();
}


