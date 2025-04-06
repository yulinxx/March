#include "MenuBar.h"

#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include "Widgets/TipWidget.h"
#include "Logger.h"
#include "def.h"

MenuBar::MenuBar(QWidget* parent)
    : QMenuBar(parent)
{
    initMenu();
}

void MenuBar::initMenu()
{
    m_menuFile = new QMenu(tr("&File"), this);
    initFileMenu(m_menuFile);
    addMenu(m_menuFile);

    m_menuEdit = new QMenu(tr("&Edit"), this);
    initEditMenu(m_menuEdit);
    addMenu(m_menuEdit);

    m_menuView = new QMenu(tr("&View"), this);
    initViewMenu(m_menuView);
    addMenu(m_menuView);

    m_menuDraw = new QMenu(tr("&Draw"), this);
    initDrawMenu(m_menuDraw);
    addMenu(m_menuDraw);
}

void MenuBar::initFileMenu(QMenu* menu)
{
    QAction* newAct = new QAction(tr("New"), this);
    newAct->setShortcut(QKeySequence::New);
    menu->addAction(newAct);
    if (newAct)
    {
        connect(newAct, &QAction::triggered, this, [this]() {
            TipWidget::instance()->showMessage("Creating new file...");
            emit sigNewFile("");
            });
    }

    QAction* openAct = new QAction(tr("Open"), this);
    openAct->setShortcut(QKeySequence::Open);
    menu->addAction(openAct);
    if (openAct)
    {
        connect(openAct, &QAction::triggered, this, [this]() {
            QMessageBox::information(this, tr("Info"), tr("Opening file..."));
            emit sigOpenFile("");
            });
    }

    QAction* saveAct = new QAction(tr("Save"), this);
    saveAct->setShortcut(QKeySequence::Save);
    menu->addAction(saveAct);
    if (saveAct)
    {
        connect(saveAct, &QAction::triggered, this, [this]() {
            QMessageBox::information(this, tr("Info"), tr("Saving file..."));
            emit sigSaveFile("");
            });
    }

    QAction* importAct = new QAction(tr("Import..."), this);
    importAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_I));
    menu->addAction(importAct);
    if (importAct)
    {
        connect(importAct, &QAction::triggered, this, [this]() {
            QMessageBox::information(this, tr("Info"), tr("Starting import..."));
            QString file = QFileDialog::getOpenFileName(this, tr("Select File"), "",
                tr("All Supported Files (*.jpg *.bmp *.png *.jpeg *.gif *.dxf *.dwg *.dwt *.dwf);;")
                + tr("Images (*.jpg *.bmp *.png *.jpeg *.gif);;")
                + tr("CAD Files (*.dxf *.dwg *.dwt *.dwf);;")
            );

            if (!file.isEmpty())
            {
                emit sigImportFile(file);
                MLog::Logger::LogInfo("Importing file: " + file.toStdString());
            }
            });
    }
    // 添加皮肤切换菜单
    QMenu* skinMenu = new QMenu(tr("Skin"), menu);
    menu->addMenu(skinMenu);

    // 定义不同的皮肤选项
    QMap<QString, QString> mapSkins = {
        {"MetroUI", ":/theme/MetroUI.qss"},
        {"Aqua", ":/theme/Aqua.qss"},
        {"ConsoleStyle", ":/theme/ConsoleStyle.qss"},
        {"ElegantDark", ":/theme/ElegantDark.qss"},
        {"MacOS", ":/theme/MacOS.qss"},
        {"ManjaroMix", ":/theme/ManjaroMix.qss"},
        {"MaterialDark", ":/theme/MaterialDark.qss"},
        {"Ubuntu", ":/theme/Ubuntu.qss"}
    };

    for (const QString& option : mapSkins.keys())
    {
        QAction* skinAct = new QAction(option, skinMenu);
        skinMenu->addAction(skinAct);

        connect(skinAct, &QAction::triggered, this, [this, option, mapSkins]() {
            TipWidget::instance()->showMessage(tr("Switching to %1 skin...").arg(option));
            QString filePath = mapSkins.value(option);

            QFile file(filePath);

            if (file.open(QFile::ReadOnly | QFile::Text))
            {
                QTextStream stream(&file);
                QString styleSheet = stream.readAll();
                qApp->setStyleSheet(styleSheet);
                file.close();
            }
            // emit sigSwitchSkin(filePath);
            });
    }
}

void MenuBar::initEditMenu(QMenu* menu)
{
    m_undoAct = new QAction(tr("Undo"), this);
    m_undoAct->setShortcut(QKeySequence::Undo);
    m_menuEdit->addAction(m_undoAct);
    connect(m_undoAct, &QAction::triggered, this, [this]() {
        //QMessageBox::information(this, tr("Info"), tr("Undoing last action..."));
        emit sigUndo();
        });
    m_redoAct = new QAction(tr("Redo"), this);
    m_redoAct->setShortcut(QKeySequence::Redo);
    m_menuEdit->addAction(m_redoAct);
    connect(m_redoAct, &QAction::triggered, this, [this]() {
        //QMessageBox::information(this, tr("Info"), tr("Redoing last action..."));
        emit sigRedo();
        });
}

void MenuBar::initViewMenu(QMenu* menu)
{
    QAction* showDrawToolBarAct = new QAction(tr("ShowDrawToolBar"), this);
    menu->addAction(showDrawToolBarAct);
    connect(showDrawToolBarAct, &QAction::triggered, this, [this]() {
        QMessageBox::information(this, tr("Info"), tr("Toggling draw toolbar..."));
        emit sigShowDrawToolBar();
        });

    QAction* showHardInfoDockAct = new QAction(tr("ShowHardInfo"), this);
    menu->addAction(showHardInfoDockAct);
    connect(showHardInfoDockAct, &QAction::triggered, this, [this]() {
        QMessageBox::information(this, tr("Info"), tr("Toggling hardware info dock..."));
        emit sigShowHardInfoDock();
        });
}

void MenuBar::initDrawMenu(QMenu* menu)
{
    // TODO: 与绘图工具进行复用
    m_actSelect = new QAction(QIcon("://icons/draw-select.png"), tr("Select"), this);
    m_actDrawPoint = new QAction(QIcon("://icons/draw-point.png"), tr("Point"), this);
    m_actDrawLine = new QAction(QIcon("://icons/draw-line.png"), tr("Line"), this);
    m_actDrawPline = new QAction(QIcon("://icons/draw-pline.png"), tr("Polyline"), this);
    m_actDrawCircle = new QAction(QIcon("://icons/draw-circle.png"), tr("Circle"), this);
    m_actDrawText = new QAction(QIcon("://icons/draw-text.png"), tr("Text"), this);
    m_actDrawArc = new QAction(QIcon("://icons/draw-arc.png"), tr("Arc"), this);
    m_actDrawPolygon = new QAction(QIcon("://icons/draw-polygon.png"), tr("Polygon"), this);
    m_actDrawImage = new QAction(QIcon("://icons/draw-image.png"), tr("Image"), this);

    // 添加与工具栏相同的action
    menu->addAction(m_actDrawPoint);
    menu->addAction(m_actDrawLine);
    menu->addAction(m_actDrawPline);
    menu->addAction(m_actDrawCircle);
    menu->addAction(m_actDrawText);
    menu->addAction(m_actDrawArc);
    menu->addAction(m_actDrawPolygon);

    connect(m_actSelect, &QAction::triggered, this, [this]() {
        emit sigEntityOpration(static_cast<int>((0)));
        });
    connect(m_actDrawPoint, &QAction::triggered, this, [this]() {
        emit sigCreateEntity(static_cast<int>(DrawType::Point));
        });
    connect(m_actDrawLine, &QAction::triggered, this, [this]() {
        emit sigCreateEntity(static_cast<int>((DrawType::Line)));
        });
    connect(m_actDrawPline, &QAction::triggered, this, [this]() {
        emit sigCreateEntity(static_cast<int>((DrawType::Polyline)));
        });
    connect(m_actDrawCircle, &QAction::triggered, this, [this]() {
        emit sigCreateEntity(static_cast<int>((DrawType::Circle)));
        });
    connect(m_actDrawText, &QAction::triggered, this, [this]() {
        emit sigCreateEntity(static_cast<int>((DrawType::Text)));
        });
    connect(m_actDrawArc, &QAction::triggered, this, [this]() {
        TipWidget::instance()->showMessage(tr("Arc"));
        });
    connect(m_actDrawPolygon, &QAction::triggered, this, [this]() {
        TipWidget::instance()->showMessage(tr("Polygon"));
        });
}