#include "metronomeplayer.h"
#include "defaults.h"
#include <QDebug>

MetronomePlayer::MetronomePlayer(QObject *parent)
    : QObject{parent}
{
    this->player = new QMediaPlayer(this);
    this->output = new QAudioOutput(this);

    this->output->setVolume(DEFAULT_VOLUME/100.0);
    this->player->setAudioOutput(output);
    this->player->setSource(QUrl("qrc:/sounds/sounds/click_low.wav"));
}

void MetronomePlayer::setVolume(int volume) {
    float newVolume = volume/100.0;
    this->output->setVolume(newVolume);
    qDebug() << QString::number(newVolume);
}

void MetronomePlayer::playSound() {
    this->player->play();
}

MetronomePlayer::~MetronomePlayer() {
    delete this->player;
    delete this->output;
}
