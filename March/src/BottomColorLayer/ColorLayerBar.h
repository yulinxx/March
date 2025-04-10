#ifndef COLORLAYERBAR_H
#define COLORLAYERBAR_H

#include <QDockWidget>
#include <QToolBar>
#include <QPushButton>

class ColorLayerBar final : public QDockWidget
{
    Q_OBJECT
public:
    explicit ColorLayerBar(QWidget* parent = nullptr);

signals:
    void sigColorLayerSelected(const QString& color);
    void sigSelColorLayer(const int color);

private slots:
    void slotDockPosChanged(Qt::DockWidgetArea area);
    void slotColorBtnClicked(const QString& color);

private:
    void initUI();

private:
    QToolBar* m_toolbar{ nullptr };

};
#endif // COLORLAYERBAR_H