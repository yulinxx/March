#ifndef ENTITY_DRAW_ADAPTER_H
#define ENTITY_DRAW_ADAPTER_H

#include <QObject>

class MainWindow;
class ViewWrapper;

class EntityDrawAdapter final : public QObject
{
    Q_OBJECT

public:
    explicit EntityDrawAdapter(MainWindow* parent = nullptr);

signals:
    void sigStatusMsgChanged(const QString &msg);

public slots:
    void slotCreateEntity(int);

private:
    ViewWrapper* m_view{nullptr};
    MainWindow* m_mainWnd{nullptr};
};

#endif // ENTITY_DRAW_ADAPTER_H