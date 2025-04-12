#include "FileAdapter.h"
#include "MainWindow.h"

FileAdapter::FileAdapter(MainWindow* parent) : QObject(parent)
{
    m_mainWnd = parent;
    auto m = parent->getMenuBar();
    auto t = parent->getMainToolBar();

    // 关联信号槽
    connect(m, &MenuBar::sigNewFile, this, &FileAdapter::slotNew, Qt::UniqueConnection);
    connect(m, &MenuBar::sigOpenFile, this, &FileAdapter::slotOpenFile, Qt::UniqueConnection);
    connect(m, &MenuBar::sigSaveFile, this, &FileAdapter::slotSaveFile, Qt::UniqueConnection);

    // 撤销重做信号关联槽函数
    connect(m, &MenuBar::sigUndo, this, &FileAdapter::slotUndo, Qt::UniqueConnection);
    connect(m, &MenuBar::sigRedo, this, &FileAdapter::slotRedo, Qt::UniqueConnection);

    // connect(t, &InfoToolBar::sigNewFile, this, &FileAdapter::slotNew);
    // connect(t, &InfoToolBar::sigOpenFile, this, &FileAdapter::slotOpenFile);
    // connect(t, &InfoToolBar::sigSaveFile, this, &FileAdapter::slotSaveFile);
}

void FileAdapter::slotNew(const QString& filePath)
{
    m_mainWnd->createNewView();
}

void FileAdapter::slotOpenFile(const QString& filePath)
{
}

void FileAdapter::slotSaveFile(const QString& filePath)
{
}

void FileAdapter::slotUndo()
{
    m_mainWnd->getView()->getScene()->undo();
    m_mainWnd->updateScene();
}

void FileAdapter::slotRedo()
{
    m_mainWnd->getView()->getScene()->redo();
    m_mainWnd->updateScene();
}