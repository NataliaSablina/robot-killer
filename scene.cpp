#include "scene.h"

CustomScene::CustomScene(QObject *parent) :
    QGraphicsScene()
{
    Q_UNUSED(parent);
}

CustomScene::~CustomScene()
{

}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate(event->scenePos());//координаты события(присутствия курсора)//вызываем сигнал
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(true);
    Q_UNUSED(event);
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(false);
    Q_UNUSED(event);
}
