#ifndef METRONOMETIMER_H
#define METRONOMETIMER_H

#include <QObject>
#include <QTimer>

class MetronomeTimer : public QObject
{
    Q_OBJECT
public:
    explicit MetronomeTimer(QObject *parent = nullptr);
    ~MetronomeTimer();

public slots:
    void start();
    void stop();
    void toggle();
    void setBPM(int bpm);

signals:
    void done();
    void stateChanged(QString state);

private:
    QTimer *timer;
    int ticks;
    bool running;
};

#endif // METRONOMETIMER_H
