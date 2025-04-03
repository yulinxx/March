#ifndef DRAWTOOLBAR_H
#define DRAWTOOLBAR_H

#include <QDockWidget>
#include <QToolBar>
#include <QAction>

#include <map>

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

private:
    void initUI();

private:
    QToolBar* m_toolbar{ nullptr };

    std::map<int, QAction*> m_mapActions;


};
#endif // DRAWTOOLBAR_H