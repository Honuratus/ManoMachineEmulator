#ifndef EMULATORCORE_H
#define EMULATORCORE_H

#include <QObject>
#include "rtl.h"



class EmulatorCore: public QObject
{
    Q_OBJECT
private:
    Computer m_computer;
public:    
    const uint16_t* getVideoBuffer() const;
    void handleKeyPress(char code);

    EmulatorCore(QObject* parent = nullptr);
    ~EmulatorCore();

public slots:
    void tick();

signals:
    void screenUpdated();
    void computerHalted();

};



#endif