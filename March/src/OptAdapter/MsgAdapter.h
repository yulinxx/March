#ifndef MSGADAPTER_H 
#define MSGADAPTER_H

#include <QObject>

class MainWindow;

class MsgAdapter final : public QObject
{
public:
    explicit MsgAdapter(MainWindow *parent = nullptr);

public:
    void reInit();

private:
    MainWindow *m_mainWnd{nullptr};
};

#endif // MSGADAPTER_H