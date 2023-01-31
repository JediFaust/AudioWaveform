#ifndef AUDIOAMPLITUDE_H
#define AUDIOAMPLITUDE_H

#include <QObject>

class audioamplitude : public QObject
{
    Q_OBJECT
    Q_PROPERTY(READ samplesArr NOTIFY samplesChanged)
public:
    explicit audioamplitude(QObject *parent = nullptr);
    static QList<float> samplesArr;

signals:
    static void samplesChanged();

public slots:
    void getAmplitude();
};

#endif // AUDIOAMPLITUDE_H
