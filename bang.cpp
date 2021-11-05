#include "bang.h"

Bang::Bang(QPointF point, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    this->setPos(point);
    currentFrame = 0;//координата Х начала взрыва пули
    bangImage = new QPixmap(":/img/img/sprite_sheet.png");

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Bang::nextFrame);
    timer->start(25);
}

QRectF Bang::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void Bang::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-10,-10, *bangImage, currentFrame, 0, 20,20);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Bang::nextFrame()
{
    currentFrame += 20;
    if (currentFrame >= 300 ) {
        this->deleteLater();
    } else {
        this->update(-10,-10,20,20);
    }
}

int Bang::type() const {
    return Type;
}
