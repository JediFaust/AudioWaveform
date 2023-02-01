#ifndef AUDIOAMPLITUDE_H
#define AUDIOAMPLITUDE_H

#include <QObject>
#include <QVariantList>

class audioamplitude : public QObject
{
    Q_OBJECT
public:
    explicit audioamplitude(QObject *parent = nullptr);
    static audioamplitude *instance() { return m_instance; }
//    QVariantList samplesArr;

signals:
    void samplesChanged(QVariantList samples);

public slots:
    void getAmplitude();
private:
    static audioamplitude *m_instance;
};

#endif // AUDIOAMPLITUDE_H
