#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPolygon>
#include <QTimer>
#include <QDebug>
#include <QCursor>

#include <windows.h>

class Triangle : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Triangle(QObject *parent = 0);
    ~Triangle();

signals:

    void signalBullet(QPointF start, QPointF end);

public slots:
    void slotTarget(QPointF point);//слот для получения данных о положении курсора//в нем устанавливаем направление куда смотрит наш треугольник
    void slotShot(bool shot);

private:
    QRectF boundingRect() const;//
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);//
    QPainterPath shape() const;/////функция возвращающая форму фигуры, необходимую для обработки коллизий

private slots:
    void slotGameTimer();//игровой слот который будет вызываться по сигналу от игрового таймера
    //обработка перемещений нашего героя, обработка взгляда за курсором
    void slotBulletTimer();

private:
    bool shot;
    QTimer *bulletTimer;///таймер для вызова пуль
    QTimer *gameTimer;//игровой таймер отвечающий за перемещение героя
    QPointF target;//положение курсора
};

#endif // TRIANGLE_H
