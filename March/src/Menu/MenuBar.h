#ifndef MAINMENUBAR_H
#define MAINMENUBAR_H

#include <QMenuBar>
#include <QMenu>

class MenuBar final : public QMenuBar
{
    Q_OBJECT

public:
    MenuBar(QWidget* parent = nullptr);

signals:
    void sigNewFile(QString str);
    void sigOpenFile(QString str);
    void sigSaveFile(QString str);

    void sigRedo();
    void sigUndo();
    
    void sigShowDrawToolBar();
    void sigShowHardInfoDock();
    void sigImportFile(QString);

    void sigEntityOpration(int);
    void sigCreateEntity(int);

private:
    void initMenu();
    void initFileMenu(QMenu* menu);
    void initEditMenu(QMenu* menu);
    void initViewMenu(QMenu* menu);
    void initDrawMenu(QMenu* menu);

private:
    QMenu *m_menuFile{nullptr};
    QMenu *m_menuEdit{nullptr};
    QMenu *m_menuView{nullptr};
    QMenu *m_menuDraw{nullptr};

    QAction *m_undoAct { nullptr };
    QAction *m_redoAct { nullptr };
    QAction *m_actSelect { nullptr };
    QAction *m_actDrawPoint { nullptr };
    QAction *m_actDrawLine { nullptr };
    QAction *m_actDrawPline { nullptr };
    QAction *m_actDrawCircle { nullptr };
    QAction *m_actDrawText { nullptr };
    QAction *m_actDrawArc { nullptr };
    QAction *m_actDrawPolygon { nullptr };
    QAction *m_actDrawImage { nullptr };

};

#endif // MAINMENUBAR_H