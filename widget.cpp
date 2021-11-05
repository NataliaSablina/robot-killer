#include "widget.h"
#include "ui_widget.h"

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->resize(800,600);
    this->setFixedSize(800,600);

    ui->setupUi(this);
    scene   = new CustomScene();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);//сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(0,0,520,520);

    QCursor cursor = QCursor(QPixmap(":/img/img/cursorTarget.png"));
    ui->graphicsView->setCursor(cursor);
    triangle = new Triangle();
    triangle->setPos(60,60);
    //triangle->setZValue(2);
    scene->addItem(triangle);

    ui->graphicsView->setMouseTracking(true);//отслеживание перемещения мыши всегда

    connect(scene, &CustomScene::signalTargetCoordinate, triangle, &Triangle::slotTarget);//связываем сигнал сцены со слотом треугольника
    //(передаем координаты в зависимости от которых треугольник будет куда-то смотреть)

    connect(scene, &CustomScene::signalShot, triangle, &Triangle::slotShot);

    connect(triangle, &Triangle::signalBullet, this, &Widget::slotBullet);


    /////ставим стены
    scene->addRect(0,0,520,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(0,0,20,520,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(0,500,520,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(500,0,20,520,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(170,250,180,20,QPen(Qt::NoPen),QBrush(Qt::darkGray));
    scene->addRect(250,170,20,180,QPen(Qt::NoPen),QBrush(Qt::darkGray));

    ////таймер для создания мишеней
    timerTarget = new QTimer();
    connect(timerTarget, &QTimer::timeout, this, &Widget::slotCreateTarget);
    timerTarget->start(1500);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotBullet(QPointF start, QPointF end)///
{
    Bullet *bullet = new Bullet(start, end, triangle);///добавляем на сцену пулю
    bullet->setCallbackFunc(slotHitTarget);
    scene->addItem(bullet);///
}

void Widget::slotCreateTarget()
{
    Target *target = new Target();
    scene->addItem(target);
    target->setPos(qrand() % ((500 - 40 + 1) - 40) + 40,
                  qrand() % ((500 - 40 + 1) - 40) + 40);
    target->setZValue(-1);////помещаем цель ниже нашего героя
    targets.append(target);//добавляем цель в список
}

void Widget::slotHitTarget(QGraphicsItem *item)
{
    foreach (QGraphicsItem *targ, targets) {////перебираем если мишень то преобразовываем в мишень
        if(targ == item){
            Target *t = qgraphicsitem_cast <Target *> (targ);
            t->hit(randomBetween(1,3));////наносим урон
        }
    }
}

QList<QGraphicsItem *> Widget::targets;
