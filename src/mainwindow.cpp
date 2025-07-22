#include <QKeyEvent>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent){
    EmulatorCore* emulator = new EmulatorCore(this);
    ScreenWidget* screenWidget = new ScreenWidget(this);
    QTimer* timer = new QTimer(this);

    m_cpuTimer = timer;
    m_emulator = emulator;
    m_screenWidget = screenWidget;


    this->setCentralWidget(m_screenWidget);
    m_screenWidget->setBuffer(m_emulator->getVideoBuffer());

    connect(m_cpuTimer, &QTimer::timeout, m_emulator, &EmulatorCore::tick);
    connect(m_emulator, &EmulatorCore::screenUpdated, m_screenWidget, QOverload<>::of(&QWidget::update));
    connect(m_emulator, &EmulatorCore::computerHalted, this, &MainWindow::onComputerHalted);
    
    m_cpuTimer->start(0);
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    QString text = event->text();
    if (!text.isEmpty()) {
        char code = text.at(0).toLatin1();
        m_emulator->handleKeyPress(code);
    }
}

void MainWindow::onComputerHalted(){
    m_cpuTimer->stop();
    this->setWindowTitle("Computer Halted!");
}

