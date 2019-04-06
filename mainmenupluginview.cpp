#include "mainmenupluginview.h"
#include "ui_form.h"

MainMenuPluginView::MainMenuPluginView(QWidget *parent) :
    PluginBase(parent)
{
    myModel = nullptr;
    rootMenuItem = nullptr;
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    sceneScale = 1;
    ui->graphicsView->scale(sceneScale, sceneScale);

    zoomAnimTimer = new QTimer(this);
    zoomAnimTimer->setInterval(50);
    connect(zoomAnimTimer, SIGNAL(timeout()),
            SLOT(ZoomAnimation()));
    connect(this, SIGNAL(OnItemSelected(IUIManager::IUIElement*,MetaInfo*)),
            SLOT(OpenChildPlugin(IUIManager::IUIElement*,MetaInfo*)));
}

MainMenuPluginView::~MainMenuPluginView()
{
    delete zoomAnimTimer;
    for(int i = 0; i < menuItems.count(); ++i)
        delete menuItems[i];
    menuItems.clear();

    WipeAllItems();
}

void MainMenuPluginView::OpenChildPlugin(QWeakPointer<IUIManager::IUIElement> menuItem, MetaInfo *viewMeta)
{
    menuItem.data()->open();
}

void MainMenuPluginView::SetRootMenuItem(QWeakPointer<IUIManager::IUIElement> RootMenuItem)
{
    rootMenuItem = RootMenuItem;
    MenuItemGraphicsObject *exitItem = new MenuItemGraphicsObject("Exit");
    connect(exitItem, SIGNAL(OnClicked(MenuItemGraphicsObject*)),
            SLOT(CloseMainMenu()));
    scene->addItem(exitItem);
    menuItems.append(exitItem);

    MenuItemGraphicsObject *menuItem;
    auto rootConnectedItems = rootMenuItem.data()->getConnectedElements();
    for(auto iter = rootConnectedItems.begin(); iter != rootConnectedItems.end(); ++iter)
    {
        menuItem = new MenuItemGraphicsObject(nullptr, rootMenuItem, rootMenuItem.data()->getMeta());
        connect(menuItem, SIGNAL(OnClicked(MenuItemGraphicsObject*)),
                SLOT(OnItemSelected(MenuItemGraphicsObject*)));
        scene->addItem(menuItem);
        menuItems.append(menuItem);
    }

    AddSubitems(nullptr, rootMenuItem);
}

void MainMenuPluginView::AddSubitems(MenuItemGraphicsObject *ParentMenuItem, QWeakPointer<IUIManager::IUIElement> ParentMenuItemStruct)
{
    auto connectedItems = ParentMenuItemStruct.data()->getConnectedElements();
    if(!connectedItems.count())
        return;

    MenuItemGraphicsObject *menuItem;
    for(auto iter = connectedItems.begin(); iter != connectedItems.end(); ++iter)
    {
        menuItem = new MenuItemGraphicsObject(ParentMenuItem, iter.value(), iter.value().data()->getMeta());
        connect(menuItem, SIGNAL(OnClicked(MenuItemGraphicsObject*)), SLOT(OnItemSelected(MenuItemGraphicsObject*)));
        scene->addItem(menuItem);
        menuItems.append(menuItem);
        AddSubitems(menuItem, iter.value());
    }
}

void MainMenuPluginView::WipeAllItems()
{
    for(int i = 0; i < menuItems.count(); ++i)
        delete menuItems[i];
    menuItems.clear();
}

void MainMenuPluginView::OnItemSelected(MenuItemGraphicsObject *menuItem)
{
//    sceneScale = 1.05;
//    scaleIter = 0;
//    zoomAnimTimer->start();

    emit OnItemSelected(menuItem->menuItem, menuItem->viewPluginMeta);
}

void MainMenuPluginView::ZoomAnimation()
{
    if(++scaleIter > 20)
        zoomAnimTimer->stop();

    ui->graphicsView->scale(sceneScale, sceneScale);
}


void MainMenuPluginView::onAllReferencesSet()
{
    if(m_isAllReferencesSet)
    {
        for(const auto &reference : m_referencesMap)
        {
            if(reference->getPluginMetaInfo().InterfaceName == "IUIMANAGER")
            {
                myModel = castPluginToInterface<IUIManager>(reference);
            }
        }
    }
    PluginBase::onAllReferencesSet();
}

void MainMenuPluginView::onAllReferencesReady()
{
    SetRootMenuItem(myModel->getRootElement());

    PluginBase::onAllReferencesReady();
}
