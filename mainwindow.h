#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtPdfWidgets/QtPdfWidgets>
#include "metronomeplayer.h"
#include "metronometimer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
    MetronomePlayer *metronomePlayer;
    MetronomeTimer *metronomeTimer;

    void setDefaults();
    void makeConnections();
};
#endif // MAINWINDOW_H
