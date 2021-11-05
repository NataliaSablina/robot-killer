#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>

#include <triangle.h>
#include <scene.h>
#include <bullet.h>
#include <target.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    CustomScene  *scene;//
    Triangle *triangle;//
    QTimer *timerTarget;////таймер для создания мешеней
    static QList<QGraphicsItem *> targets;////список всех мишеней

    static void slotHitTarget(QGraphicsItem *item);////колл бэк функция которая передается в каждую создаваемую пулю
////с помощь. нее пуля говорит что ударилась вкакойто объект, обработка происходит в виджет
///
private slots:
    void slotBullet(QPointF start, QPointF end);
    void slotCreateTarget();//слот для создания мешеней

};

#endif // WIDGET_H
