#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Target : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Target(QObject *parent = 0);
    ~Target();
    /*функция по нанесению урона,
     величина урона передается в качестве аргумента функции*/
    void hit(int damage);

public slots:

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int health;////текущий запас энергии
    int maxHealth;////максимальный запас энергии
};

#endif // TARGET_H
