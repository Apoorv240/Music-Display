#include "metronometimer.h"
#include "defaults.h"

MetronomeTimer::MetronomeTimer(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    timer->stop();
    ticks = 60000 / DEFAULT_METRONOME;
    running = false;
}

void MetronomeTimer::start() {
    connect(timer, &QTimer::timeout, this, &MetronomeTimer::done);
    timer->start(ticks);
    running = true;

    emit stateChanged("Pause");
}

void MetronomeTimer::setBPM(int bpm) {
    ticks = 60000 / bpm;

    if (running) {
        timer->start(ticks);
    }
}

void MetronomeTimer::toggle() {
    if (running) return stop();
    return start();
}

void MetronomeTimer::stop() {
    timer->stop();
    disconnect(timer, &QTimer::timeout, this, &MetronomeTimer::done);
    running = false;

    emit stateChanged("Play");
}

MetronomeTimer::~MetronomeTimer() {
    delete timer;
}


