#ifndef MAINMENUPLUGINVIEW_H
#define MAINMENUPLUGINVIEW_H

#include <QLayout>
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/iuimanager.h"

#include "menuitem.h"

//! \defgroup MainMenuPluginView
//!     \ingroup MainMenuPlugin_rel_v
//! \defgroup MainMenuPluginView_imp Implementation
//!     \ingroup MainMenuPluginView

//! \addtogroup MainMenuPluginView_imp
//! \{
class MainMenuPluginView : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin)

public:
    explicit MainMenuPluginView(QWidget *parent = nullptr);
    ~MainMenuPluginView();

    void SetRootMenuItem(QWeakPointer<IUIManager::IUIElement> RootMenuItem);
    void AddSubitems(MenuItemGraphicsObject *ParentMenuItem, QWeakPointer<IUIManager::IUIElement> ParentMenuItemStruct);
    void WipeAllItems();

private slots:
    void OpenChildPlugin(QWeakPointer<IUIManager::IUIElement> menuItem, MetaInfo *viewMeta);
    void CloseMainMenu();

    void OnItemSelected(MenuItemGraphicsObject *menuItem);
    void ZoomAnimation();

signals:
    void OnItemSelected(QWeakPointer<IUIManager::IUIElement> meta, MetaInfo viewMeta);

private:
    IUIManager *myModel;
    QWeakPointer<IUIManager::IUIElement> rootMenuItem;

    QGraphicsScene *scene;
    QList<MenuItemGraphicsObject*> menuItems;
    QTimer *zoomAnimTimer;
    QPoint newCenter;
    float sceneScale;
    int scaleIter;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;
};
//! \}
#endif // MAINMENUPLUGINVIEW_H
