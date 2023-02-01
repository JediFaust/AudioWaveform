#ifndef AUDIOAMPLITUDE_H
#define AUDIOAMPLITUDE_H

#include <QObject>
#include <QVariantList>

class audioamplitude : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList samples READ samples WRITE setSamples NOTIFY samplesChanged)

public:
    explicit audioamplitude(QObject *parent = nullptr);
    static audioamplitude *instance() { return m_instance; }
    QVariantList samples();
    void setSamples(QVariantList newSamples);

signals:
    void samplesChanged();

public slots:
    void getSamples();

private:
    static audioamplitude *m_instance;
    QVariantList m_samples;
};

#endif // AUDIOAMPLITUDE_H
