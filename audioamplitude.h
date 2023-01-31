#ifndef AUDIOAMPLITUDE_H
#define AUDIOAMPLITUDE_H

#include <QObject>

class audioamplitude : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QVariantList samplesArr READ samplesArr WRITE setAmplitude NOTIFY samplesChanged)
public:
    explicit audioamplitude(QObject *parent = nullptr);
    static QList<float> samplesArr;

signals:
    static void samplesChanged();

public slots:
    void getAmplitude();
    void setAmplitude(QList<float>);
};

#endif // AUDIOAMPLITUDE_H
