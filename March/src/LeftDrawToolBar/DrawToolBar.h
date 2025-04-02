#ifndef LEFTDRAWTOOLBAR_DRAWTOOLBAR_H
#define LEFTDRAWTOOLBAR_DRAWTOOLBAR_H
#include <QDockWidget>
#include <QToolBar>
#include <QAction>

class DrawToolBar final : public QDockWidget
{
    Q_OBJECT
public:
    explicit DrawToolBar(QWidget* parent = nullptr);

signals:
    void sigEntityOpration(int);
    void sigCreateEntity(int);
    
private slots:
    void slotDockPosChanged(Qt::DockWidgetArea area);

    void slotSelect();
    void slotDrawPoint();
    void slotDrawLine();
    void slotDrawPline();
    void slotDrawCircle();
    void slotDrawText();
    void slotDrawArc();
    void slotDrawPolygon();
    void slotDrawImage();

private:
    void initUI();

private:
    QToolBar* m_toolbar{ nullptr };

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
#endif // LEFTDRAWTOOLBAR_DRAWTOOLBAR_H