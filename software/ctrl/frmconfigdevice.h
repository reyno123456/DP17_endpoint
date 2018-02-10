#ifndef FRMCONFIGDEVICE_H
#define FRMCONFIGDEVICE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "devgraphicsview.h"

namespace Ui {
class frmConfigDevice;
}

class frmConfigDevice : public QWidget
{
    Q_OBJECT

public:
    explicit frmConfigDevice(QWidget *parent = 0);
    ~frmConfigDevice();

    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::frmConfigDevice *ui;
    QGraphicsScene* pScene;
    QGraphicsView * pView ;
    DevGraphicsView* pDevGraphicsView;

public slots:
    void test1();
    void test2();

    void graphics_mouse_move(QMouseEvent *event);
};

#endif // FRMCONFIGDEVICE_H
