#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defaults.h"
#include <QPushButton>
#include <QPdfDocument>
#include <QDebug>
#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    metronomePlayer = new MetronomePlayer();
    metronomeTimer = new MetronomeTimer();

    ui->setupUi(this);

    setDefaults();
    makeConnections();
}

void MainWindow::setDefaults() {
    ui->volumeSlider->setSliderPosition(DEFAULT_VOLUME);
    ui->volumeSlider->setMinimum(VOLUME_MIN);
    ui->volumeSlider->setMaximum(VOLUME_MAX);

    ui->volumeValueLabel->setNum(DEFAULT_VOLUME);

    ui->metronomeSlider->setSliderPosition(DEFAULT_METRONOME);
    ui->metronomeSlider->setMinimum(METRONOME_MIN);
    ui->metronomeSlider->setMaximum(METRONOME_MAX);

    ui->metronomeSpinBox->setValue(DEFAULT_METRONOME);
    ui->metronomeSpinBox->setMinimum(METRONOME_MIN);
    ui->metronomeSpinBox->setMaximum(METRONOME_MAX);

    metronomeTimer->setBPM(DEFAULT_METRONOME);
}

void MainWindow::makeConnections() {
    // connect volumeSlider value to volumeLabel value
    connect(ui->volumeSlider, static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
            ui->volumeValueLabel, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    // connect metronomeSlider value to metronomeLabel value
    connect(ui->metronomeSlider, static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
            ui->metronomeSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::setValue));
    connect(ui->metronomeSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            ui->metronomeSlider, static_cast<void (QSlider::*)(int)>(&QSlider::setValue));

    // connect metronomeStartButton to MetronomeTimer start
    connect(ui->metronomeToggleButton, &QPushButton::clicked,
            metronomeTimer, &MetronomeTimer::toggle);

    // connect metronomeTimer to MetronomePlayer
    connect(metronomeTimer, &MetronomeTimer::done,
            metronomePlayer, &MetronomePlayer::playSound);

    connect(ui->metronomeSlider, static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
            metronomeTimer, static_cast<void (MetronomeTimer::*)(int)>(&MetronomeTimer::setBPM));

    // connect volumeSlider value to metronomePlayer volume
    connect(ui->volumeSlider, static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
            metronomePlayer, static_cast<void (MetronomePlayer::*)(int)>(&MetronomePlayer::setVolume));

    connect(metronomeTimer, static_cast<void (MetronomeTimer::*)(QString)>(&MetronomeTimer::stateChanged),
            ui->metronomeToggleButton, static_cast<void (QPushButton::*)(const QString &)>(&QPushButton::setText));
/*
    connect(ui->actionOpen_File, &QAction::triggered,
            ui->pdfViewer, &MusicPdfViewer::open);*/

    connect(ui->actionOpen_File, &QAction::triggered,
            ui->pdfView, &MusicPdfViewer::open);
    connect(ui->actionClose_File, &QAction::triggered,
            ui->pdfView, &MusicPdfViewer::close);

    connect(ui->actionZoom_In, &QAction::triggered,
            ui->pdfView, &MusicPdfViewer::incrementZoom);
    connect(ui->actionZoom_Out, &QAction::triggered,
            ui->pdfView, &MusicPdfViewer::decrementZoom);
    connect(ui->actionReset_Zoom, &QAction::triggered,
            ui->pdfView, &MusicPdfViewer::resetZoom);

    connect(ui->actionShow_Control_Panel, static_cast<void (QAction::*)(bool)>(&QAction::toggled),
            ui->controlPanelFrame, static_cast<void (QFrame::*)(bool)>(&QFrame::setVisible));
    connect(ui->actionShow_Control_Panel, &QAction::toggled,
            this, [this]() {
                    if (ui->actionShow_Control_Panel->isChecked()) {
                        metronomeTimer->start();
                    } else {
                        metronomeTimer->stop();
                    }
                }
            );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete metronomePlayer;
    delete metronomeTimer;
}
