#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>
#include <QDebug>

#include <bang.h>

class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bullet(QPointF start, QPointF end, QGraphicsItem *hero, QObject *parent = 0);
    ~Bullet();

    ////функция для установки колл бэк функции
    void setCallbackFunc(void (*func) (QGraphicsItem * item));////нанесение урона основано нв коллбэк функциях
    ////будет вызываться каждый раз когда пуля будет ударяться о прептствие

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void (*callbackFunc)(QGraphicsItem * item);////сигнатура кооллбэк функции

private:
    QTimer *timerBullet;///по таймеру будет производиться перемещение пули по игровому полю
    QGraphicsItem *hero;
private slots:
    void slotTimerBullet();///по таймеру будет производиться перемещение пули по игровому полю
};

#endif // BULLET_H
