#ifndef RANDDATAPRODUCER_H
#define RANDDATAPRODUCER_H

#include <QObject>

class RandDataProducer : public QObject {
    Q_OBJECT

    double m_min;   // минимальное значение
    double m_max;   // максимальное значение
    bool m_running; // работаем?
    bool m_paused;  // мы на паузе?

    static double Rand(double min, double max);

public:
    explicit RandDataProducer(double fMin, double fMax, QObject *parent = 0)
        : QObject(parent)
        , m_min(fMin)
        , m_max(fMax)
        , m_running(false)
        , m_paused(false)
    {}

    bool isRunning() const {
        return m_running;
    }

    bool isPaused() const {
        return m_paused;
    }

signals:
    void newData(QVector<double> x, QVector<double> y);
    void finished();

public slots:

    void run();

    void setRunning(bool running) {
        m_running = running;
    }

    void setPaused(bool paused) {
        m_paused = paused;
    }
};

#endif // RANDDATAPRODUCER_H
