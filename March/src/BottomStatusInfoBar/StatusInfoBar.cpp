#include "StatusInfoBar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

StatusInfoBar::StatusInfoBar(QWidget* parent) : QStatusBar(parent)
{
    // 创建一个容器 QWidget 来管理两层布局
    QWidget* container = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(container);

    // 第一层：进度条
    m_progressMsg = new ProgressMsg(this);
    m_progressMsg->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    mainLayout->addWidget(m_progressMsg);

    // 第二层：水平布局控件
    QHBoxLayout* infoLayout = new QHBoxLayout();

    m_coordMsg = new CoordInfoMsg(this);
    m_coordMsg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_coordMsg->setFixedWidth(300);
    infoLayout->addWidget(m_coordMsg);
    infoLayout->setAlignment(m_coordMsg, Qt::AlignLeft);

    m_itemsMsg = new ItemsMsg(this);
    m_itemsMsg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_itemsMsg->setFixedWidth(300);
    infoLayout->addWidget(m_itemsMsg);
    infoLayout->setAlignment(m_itemsMsg, Qt::AlignHCenter);

    m_hardwareMsg = new HardMsg(this);
    m_hardwareMsg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_hardwareMsg->setFixedWidth(500);
    // 在硬件信息控件前添加伸缩因子
    infoLayout->addStretch();
    infoLayout->addWidget(m_hardwareMsg);
    infoLayout->setAlignment(m_hardwareMsg, Qt::AlignRight);

    mainLayout->addLayout(infoLayout);

    // 设置垂直布局的拉伸比例
    mainLayout->setStretch(0, 1); // 进度条
    mainLayout->setStretch(1, 3); // 信息控件

    // 将容器添加到 QStatusBar
    addWidget(container, 1); // 占用所有可用空间
    setMinimumHeight(120);
    slotSetCoordInfo(123.45f, 678.90f);
}

StatusInfoBar::~StatusInfoBar()
{
    // 可以在这里添加自定义的析构代码
}

void StatusInfoBar::slotSetCoordInfo(float x, float y)
{
    m_coordMsg->setMsg(x, y);
}

void StatusInfoBar::slotSetItemsInfo(const size_t n)
{
    m_itemsMsg->setMsg(n);
}

void StatusInfoBar::slotSetHardwareInfo(const QString& text)
{
    m_hardwareMsg->setMsg(text);
}

void StatusInfoBar::slotSetProgressValue(int value)
{
    if (m_progressMsg)
        m_progressMsg->setValue(value);
}

void StatusInfoBar::showProgress()
{
    if (m_progressMsg)
    {
        m_progressMsg->show();
        static_cast<QVBoxLayout*>(m_progressMsg->parentWidget()->layout())->setStretch(0, 1);
        static_cast<QVBoxLayout*>(m_progressMsg->parentWidget()->layout())->setStretch(1, 3);
    }
}

void StatusInfoBar::hideProgress()
{
    if (m_progressMsg)
    {
        m_progressMsg->hide();
        static_cast<QVBoxLayout*>(m_progressMsg->parentWidget()->layout())->setStretch(0, 0);
        static_cast<QVBoxLayout*>(m_progressMsg->parentWidget()->layout())->setStretch(1, 10);
    }
}