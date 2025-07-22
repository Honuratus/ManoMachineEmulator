#include <QPainter>
#include <QPaintEvent>
#include <algorithm>

#include "screenwidget.h"
#include "config.h"


ScreenWidget::ScreenWidget(QWidget* parent): QWidget(parent){
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, Qt::black);

        this->setAutoFillBackground(true);
        this->setPalette(pal);
}

void ScreenWidget:: setBuffer(const uint16_t* buffer){
    m_videoBuffer = buffer;
}

void ScreenWidget:: paintEvent(QPaintEvent* event){
    // return if videobuffer is nullptr
    if(m_videoBuffer == nullptr) return;

    QPainter painter(this);

    if (this->width() <= 0 || this->height() <= 0) {
        return;
    }

    int calculatedWidth =  this->width() / SCREEN_WIDTH;
    int calculatedHeight = this->height() / SCREEN_HEIGHT;

    int size = std::min(calculatedHeight,calculatedWidth);

    // offsetX and offsetY
    int offsetX = (this->width() - SCREEN_WIDTH * size) / 2;
    int offsetY = (this->height() - SCREEN_HEIGHT * size) / 2;


    painter.setBrush(QColor(255, 0 ,0));
    painter.setPen(Qt::NoPen);

    for(int y = 0; y<SCREEN_HEIGHT; y++){
        for(int x = 0; x<SCREEN_WIDTH; x++){
            int calculatedWord = (y * SCREEN_WIDTH + x) / 16;
            int calculatedWordBit = 15 - (x % 16);

            uint16_t word = m_videoBuffer[calculatedWord];

            // check the bit
            if (word & (1 << calculatedWordBit)){
                painter.drawRect(offsetX + (x * size), offsetY + (y * size), size, size);
            }
        }
    }
}


