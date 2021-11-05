#include "target.h"

/* Функция для получения рандомного числа
 * в диапазоне от минимального до максимального
 * */
static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Target::Target(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    health = randomBetween(1,15);
    maxHealth = health;
}

Target::~Target()
{

}

QRectF Target::boundingRect() const
{
    return QRectF(-20,-20,40,40);
}

void Target::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //сама цель
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawRect(-20,-10,40,30);

    //полоска жизни
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(-20,-20, (int) 40*health/maxHealth,3);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Target::hit(int damage)
{
    health -= damage;
    this->update(QRectF(-20,-20,40,40));//перерисовываем мишень
    if(health <= 0) this->deleteLater();
}
