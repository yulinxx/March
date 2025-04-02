#ifndef ITEMSMSG_H
#define ITEMSMSG_H

#include <QLabel>
#include <QString>

// 图元选择数量信息类
class ItemsMsg final : public QWidget
{
public:
    ItemsMsg(QWidget* parent = nullptr);
    void setMsg(size_t count);

private:
    QLabel *m_label{nullptr};
};;

#endif // ITEMSMSG_H