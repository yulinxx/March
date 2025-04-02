#ifndef HARDINFODOCK_H
#define HARDINFODOCK_H

#include <QDockWidget>
#include <QLabel>

class HardInfoDock final : public QDockWidget
{
    Q_OBJECT
public:
    explicit HardInfoDock(QWidget* parent = nullptr);

private:
    void setupUI();

private:
    QLabel* m_labelInfo{ nullptr };
};

#endif // HARDINFODOCK_H