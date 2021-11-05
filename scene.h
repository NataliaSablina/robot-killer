#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QObject *parent = 0);
    ~CustomScene();

signals:

    void signalTargetCoordinate(QPointF point);//получает координаты курсора
    void signalShot(bool shot);

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);//отслеживание координаты мыши
    //отслеживаем нажатие кнопки мыши для стрельбы//проверка на нажатие и отпускание клавиш
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
