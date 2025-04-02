#ifndef HARDMSG_H
#define HARDMSG_H

#include <QLabel>
#include <QString>

// 连接的硬件信息类
class HardMsg final : public QWidget
{
public:
    HardMsg(QWidget* parent = nullptr);

public:
    void setMsg(const QString& info);

private:
    QLabel *m_label{nullptr};
};;

#endif // HARDMSG_H