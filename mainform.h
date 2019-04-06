#ifndef MAINFORM_H
#define MAINFORM_H

#include <QTimer>
#include <QWidget>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include "../../Models/.h"
#include "menuitem.h"

namespace Ui {
class MainForm;
}

//! \addtogroup MainMenuPluginView_imp
//! \{
class MainForm : public QWidget
{
    Q_OBJECT
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

    void SetRootMenuItem(IMainMenuModel::MenuItem *RootMenuItem);
    void AddSubitems(MenuItemGraphicsObject *ParentMenuItem, IMainMenuModel::MenuItem *ParentMenuItemStruct);
    void WipeAllItems();

private slots:
    void OnItemSelected(MenuItemGraphicsObject *menuItem);
    void ZoomAnimation();

signals:
    void OnItemSelected(IMainMenuModel::MenuItem *meta, MetaInfo *viewMeta);
    void OnClose();

private:
    Ui::MainForm *ui;
    IMainMenuModel::MenuItem *rootMenuItem;
    QGraphicsScene *scene;
    QList<MenuItemGraphicsObject*> menuItems;
    QTimer *zoomAnimTimer;
    QPoint newCenter;
    float sceneScale;
    int scaleIter;
};
//! \}
#endif // MAINFORM_H
