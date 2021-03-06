#include "bullet.h"
#include <math.h>

static const double Pi = 3.14159;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Bullet::Bullet(QPointF start, QPointF end, QGraphicsItem * hero, QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    this->hero = hero;
    this->setRotation(0);
    this->setPos(start);

    QLineF lineToTarget(start, end);

    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    if (angleToTarget >= 0 && angleToTarget < Pi) {

        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {

        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }

    timerBullet = new QTimer();///полетный таймер, таймер по которому пуля будет перемещаться по полю

    connect(timerBullet, &QTimer::timeout, this, &Bullet::slotTimerBullet);
    timerBullet->start(7);///раз в 7 секунд пуля перемещается по нашему полю
}

Bullet::~Bullet()
{

}

QRectF Bullet::boundingRect() const
{
    return QRectF(0,0,2,4);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawRect(0,0,2,4);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Bullet::slotTimerBullet()
{
    setPos(mapToParent(0, -10));///пулья перемещается на 10 пикселей вперед установкой позиции


    ////проверка, ударяется ли наша пуля о какой либо объект
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF() << mapToScene(0, 0)<< mapToScene(-1, -1) << mapToScene(1, -1));

    foreach (QGraphicsItem *item, foundItems) {//если это сама пуля или сам объект то ничего не делаем
        if (item == this || item == hero || item->type() == (UserType + 1))
            continue;

        scene()->addItem(new Bang(this->pos()));
        callbackFunc(item);//если это наша цель, вызываем колл бэк функцию и уничтожаем объект
        this->deleteLater();
    }

    if(this->x() < 0){///
        this->deleteLater();
    }
    if(this->x() > 500){
        this->deleteLater();
    }

    if(this->y() < 0){
        this->deleteLater();
    }
    if(this->y() > 500){
        this->deleteLater();
    }
}

void Bullet::setCallbackFunc(void (*func)(QGraphicsItem *))
{
    callbackFunc = func;
}
