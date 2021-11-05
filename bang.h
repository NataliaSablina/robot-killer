#ifndef BANG_H
#define BANG_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Bang : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bang(QPointF point, QObject *parent = 0);//куда добавляем взрыв

    enum { Type = UserType + 1 };//переопределяем тип графического объекта взрыва чтобы пуля могла данный объект игнорировать

    int type() const;//также переопределяем функцию для получения типа объекта

signals:

public slots:

private slots:
    void nextFrame();//слот для перемещ кадров

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QTimer *timer;
    QPixmap *bangImage;
    int currentFrame;
};

#endif // BANG_H
