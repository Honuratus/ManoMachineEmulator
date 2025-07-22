#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "config.h"
#include "emulatorcore.h"
#include "screenwidget.h"

class MainWindow: public QMainWindow{
    Q_OBJECT
private:
    EmulatorCore* m_emulator;
    ScreenWidget* m_screenWidget;
    QTimer* m_cpuTimer;

public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void onComputerHalted();
    
};



#endif