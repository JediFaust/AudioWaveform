#include <QJniObject>
#include <QGuiApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantList>
#include "audioamplitude.h"

audioamplitude *audioamplitude::m_instance = nullptr;

audioamplitude::audioamplitude(QObject *parent)
    : QObject{parent}
{
    m_instance = this;
}

void audioamplitude::getSamples() {
    QJniObject nativeObj = QNativeInterface::QAndroidApplication::context();

    nativeObj.callMethod<int>("getAmplitude", "()I");
}

void audioamplitude::setSamples(QVariantList newSamples) {
    m_samples = newSamples;
    emit samplesChanged();
}

QVariantList audioamplitude::samples() {
    return m_samples;
}

extern "C" JNIEXPORT void JNICALL Java_com_AudioAmplitude_AudioAmplitude_transferSamples(JNIEnv *env, jobject, jstring _data){
    auto data = QJsonDocument::fromJson(env->GetStringUTFChars(_data, 0)).array().toVariantList();
    audioamplitude::instance()->setSamples(data);
}


