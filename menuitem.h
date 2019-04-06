#ifndef MENUITEM_H
#define MENUITEM_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QRegExp>
#include <QEvent>
#include <QStringList>

#include "../../Interfaces/iuimanager.h"

//! \addtogroup MainMenuPluginView_imp
//! \{
class MenuItemGraphicsObject : public QWidget, public QGraphicsItem
{
    Q_OBJECT
    void FormatMenuItemName(QString name);

public:
    MenuItemGraphicsObject(MenuItemGraphicsObject *ParentMenuItem, QWeakPointer<IUIManager::IUIElement> MenuItemGraphicsObject, MetaInfo ViewPlugin, QWidget *parent = nullptr);
    MenuItemGraphicsObject(QString name, QWidget *parent = nullptr);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    MenuItemGraphicsObject *parentMenuItem;
    QWeakPointer<IUIManager::IUIElement> menuItem;
    MetaInfo viewPluginMeta;

protected:
    bool pressed;
    int dx, dy;
    QString itemMenuName;
    QRectF boundRect;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void OnClicked(MenuItemGraphicsObject *me);
};
//! \}
#endif // MENUITEM_H
