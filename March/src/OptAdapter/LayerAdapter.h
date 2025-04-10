#ifndef LAYER_ADAPTER_H
#define LAYER_ADAPTER_H

#include <QObject>

class MainWindow;
// class ColorLayerBar;

class LayerAdapter final : public QObject
{
    Q_OBJECT

public:
    explicit LayerAdapter(MainWindow* parent = nullptr);
    ~LayerAdapter();

signals:
    void sigStatusMsgChanged(const QString &msg);

public slots:
    void slotSelLayer(const int color);

private:
    // ColorLayerBar* m_colorLayerBar{nullptr};
    MainWindow* m_mainWnd{nullptr};
};

#endif // LAYER_ADAPTER_H