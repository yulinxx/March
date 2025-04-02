#ifndef PROGRESSMSG_H
#define PROGRESSMSG_H

#include <QProgressBar>

// 进度条信息类
class ProgressMsg final : public QProgressBar
{
public:
    ProgressMsg(QWidget* parent = nullptr);

public:
    void setProgress(int value);
};

#endif // PROGRESSMSG_H