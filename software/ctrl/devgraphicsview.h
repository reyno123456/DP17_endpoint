#ifndef DEVGRAPHICSVIEW_H
#define DEVGRAPHICSVIEW_H
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>


namespace Ui {
class DevGraphicsView;
}

class DevGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    DevGraphicsView(QWidget *parent = NULL);
    //DevGraphicsView(const DevGraphicsView&view );
    void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
signals:
    void sig_mouseMoveEvent(QMouseEvent *event);
};

#endif // DEVGRAPHICSVIEW_H
