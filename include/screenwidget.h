#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H


#include <QWidget>

class ScreenWidget: public QWidget{
    Q_OBJECT

private:
    const uint16_t* m_videoBuffer = nullptr;
public:
    void setBuffer(const uint16_t* buffer);    
    ScreenWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    
};

#endif