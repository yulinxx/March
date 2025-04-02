#include "InfoToolBar.h"
#include <QAction>
#include <QIcon>

InfoToolBar::InfoToolBar(QWidget* parent) : QToolBar(parent)
{
    setOrientation(Qt::Vertical);
    setMovable(false);
    setIconSize(QSize(32, 32));
    initUI();
}

void InfoToolBar::initUI()
{
    m_actNew = new QAction(QIcon("://icons/new.png"), tr("New"), this);
    m_actOpen = new QAction(QIcon("://icons/open.png"), tr("Open"), this);
    m_actSave = new QAction(QIcon("://icons/save.png"), tr("Save"), this);
    m_actCut = new QAction(QIcon("://icons/cut.png"), tr("Cut"), this);
    m_actCopy = new QAction(QIcon("://icons/copy.png"), tr("Copy"), this);
    m_actPaste = new QAction(QIcon("://icons/paste.png"), tr("Paste"), this);

    addAction(m_actNew);
    addAction(m_actOpen);
    addAction(m_actSave);
    addSeparator();
    addAction(m_actCut);
    addAction(m_actCopy);
    addAction(m_actPaste);
    addSeparator();

    connect(m_actNew, &QAction::triggered, this, [this]() { emit sigNewFile(); });
    connect(m_actOpen, &QAction::triggered, this, [this]() { emit sigOpenFile(); });
    connect(m_actSave, &QAction::triggered, this, [this]() { emit sigSaveFile(); });
    connect(m_actCut, &QAction::triggered, this, [this]() { emit sigCut(); });
    connect(m_actCopy, &QAction::triggered, this, [this]() { emit sigCopy(); });
    connect(m_actPaste, &QAction::triggered, this, [this]() { emit sigPaste(); });
}