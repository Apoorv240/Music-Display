#ifndef METRONOMEPLAYER_H
#define METRONOMEPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class MetronomePlayer : public QObject
{
    Q_OBJECT
public:
    explicit MetronomePlayer(QObject *parent = nullptr);
    ~MetronomePlayer();

public slots:
    void playSound();
    void setVolume(int volume);

private:
    QMediaPlayer *player;
    QAudioOutput *output;
};

#endif // METRONOMEPLAYER_H
