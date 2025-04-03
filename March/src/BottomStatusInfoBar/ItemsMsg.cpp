#include "ItemsMsg.h"
#include <QHBoxLayout>

ItemsMsg::ItemsMsg(QWidget* parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_label = new QLabel(this);
    layout->addWidget(m_label);
    setLayout(layout);

    setMsg(99999999);
}

void ItemsMsg::setMsg(size_t count)
{
    m_label->setText(QString("选中图元数量: %1").arg(QString::number(count)));
}