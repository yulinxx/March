#include "HardMsg.h"
#include <QHBoxLayout>

HardMsg::HardMsg(QWidget* parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_label = new QLabel(this);
    layout->addWidget(m_label);
    setLayout(layout);

    setMsg("Test Hard Infomation");
}

void HardMsg::setMsg(const QString& info)
{
    m_label->setText(tr("HardInfo: %1").arg(info));
}