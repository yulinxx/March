#ifndef COORDINFOMSG_H
#define COORDINFOMSG_H

#include <QLabel>
#include <QString>

// 鼠标坐标信息类
class CoordInfoMsg final : public QWidget
{
public:
    CoordInfoMsg(QWidget* parent = nullptr);

public:
    void setMsg(float x, float y);

private:
    QLabel *m_label{nullptr};
};;

#endif // COORDINFOMSG_H