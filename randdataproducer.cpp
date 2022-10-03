#include "randdataproducer.h"
#include <QThread>

// ////////////////////////////////////////////////////////////////////////// //

const unsigned long WAIT_TIME_MS = 100;

// ////////////////////////////////////////////////////////////////////////// //

double RandDataProducer::Rand(double aMin, double aMax) {
    double f = (double)rand() / RAND_MAX;
    return aMin + f * (aMax - aMin);
}

// ////////////////////////////////////////////////////////////////////////// //

void RandDataProducer::run() {
    QVector<double> x(1);
    QVector<double> y(1);
    size_t current_x = 0;

    m_paused = false;
    while (m_running) {
        QThread::msleep(WAIT_TIME_MS);
        if (!m_paused) {
            x[0] = ++current_x;
            y[0] = Rand(m_min, m_max);
            emit newData(x, y);
        }
    }

    emit finished();
}

// ////////////////////////////////////////////////////////////////////////// //
