#include "CoordInfoMsg.h"
#include <QHBoxLayout>

CoordInfoMsg::CoordInfoMsg(QWidget* parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_label = new QLabel(this);
    layout->addWidget(m_label);
    setLayout(layout);

    setMsg(999, 999);
}

void CoordInfoMsg::setMsg(float x, float y)
{
    m_label->setText(QString("Coord: (%1, %2)")
    .arg(QString::number(x, 'f', 2)).arg(QString::number(y, 'f', 2)));
}