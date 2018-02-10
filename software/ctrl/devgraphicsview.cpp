#include "devgraphicsview.h"

DevGraphicsView::DevGraphicsView(QWidget *parent ):QGraphicsView(parent)
{
this->setMouseTracking(true);
  this->setRenderHints(QPainter::Antialiasing);

}
 //DevGraphicsView::DevGraphicsView(const DevGraphicsView&view )
 //{

 //}

void DevGraphicsView::mousePressEvent(QMouseEvent *event)
{

}


 void DevGraphicsView::mouseMoveEvent(QMouseEvent *event)
 {

        emit this->sig_mouseMoveEvent(event);

 }
