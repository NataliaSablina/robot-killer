#include "triangle.h"
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

Triangle::Triangle(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    setRotation(0);//начальный разворот треугольника

    target = QPointF(0,0);//начальное положение курсора
    shot = false;

    gameTimer = new QTimer();
    connect(gameTimer, &QTimer::timeout, this, &Triangle::slotGameTimer);//подключение сигнала от таймера к игровому слоту
    gameTimer->start(5);

    bulletTimer = new QTimer();
    connect(bulletTimer, &QTimer::timeout, this, &Triangle::slotBulletTimer);
    bulletTimer->start(1000/6);
}

Triangle::~Triangle()
{

}


QRectF Triangle::boundingRect() const
{
    return QRectF(-12,-15,24,30);
}

/////возвращаем форму героя, отрисовываем эллипс
QPainterPath Triangle::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint(0,-15) << QPoint(12,15) << QPoint(-12,15);
    painter->setBrush(Qt::red);
    painter->drawPolygon(polygon);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Triangle::slotTarget(QPointF point)
{
    target = point;
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    if (angleToTarget >= 0 && angleToTarget < Pi) {

        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {

        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}

void Triangle::slotGameTimer()
{
    if(GetAsyncKeyState('A')){
        this->setX(this->x() - 1);
/////проверка на коллизии
        if(!scene()->collidingItems(this).isEmpty()){
            this->setX(this->x() + 1);
        }
    }
    if(GetAsyncKeyState('D')){
        this->setX(this->x() + 1);

        if(!scene()->collidingItems(this).isEmpty()){
            this->setX(this->x() - 1);
        }
    }
    if(GetAsyncKeyState('W')){
        this->setY(this->y() - 1);

        if(!scene()->collidingItems(this).isEmpty()){
            this->setY(this->y() + 1);
        }
    }
    if(GetAsyncKeyState('S')){
        this->setY(this->y() + 1);

        if(!scene()->collidingItems(this).isEmpty()){
            this->setY(this->y() - 1);
        }
    }

    if(this->x() - 30 < 0){
        this->setX(30);
    }
    if(this->x() + 30 > 520){
        this->setX(520 - 30);
    }

    if(this->y() - 30 < 0){
        this->setY(30);
    }
    if(this->y() + 30 > 520){
        this->setY(520 - 30);
    }

    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));

    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    if (angleToTarget >= 0 && angleToTarget < Pi) {

        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {

        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}

void Triangle::slotBulletTimer()
{

    if(shot) emit signalBullet(mapToScene(0,-25), target);

}

void Triangle::slotShot(bool shot)///нужно для дополнительного игрового таймера для вызова пули
{
    this->shot = shot;
}
