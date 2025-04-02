#include "HardInfoDock.h"
#include <QVBoxLayout>

HardInfoDock::HardInfoDock(QWidget* parent) : QDockWidget(parent)
{
    setWindowTitle(tr("HardInfo"));
    setupUI();
    // 设置大小策略
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void HardInfoDock::setupUI()
{
    QWidget* contentWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(contentWidget);

    m_labelInfo = new QLabel(tr("HardwareInfomations"), this);
    layout->addWidget(m_labelInfo);

    contentWidget->setLayout(layout);
    setWidget(contentWidget);
}