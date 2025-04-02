#include "TipWidget.h"
#include <QPainterPath>
#include <QScreen>

TipWidget* TipWidget::m_instance = nullptr;

TipWidget* TipWidget::instance(QWidget* parent)
{
    if (!m_instance)
    {
        m_instance = new TipWidget(parent);
    }

    return m_instance;
}

TipWidget::TipWidget(QWidget* parent) : QWidget(parent)
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_animation = new QPropertyAnimation(this, "opacity");
    m_animation->setDuration(500);
    m_animation->setStartValue(0.0f);
    m_animation->setEndValue(1.0f);

    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        m_animation->setDirection(QPropertyAnimation::Backward);
        m_animation->start();
        });

    // connect(m_animation, &QPropertyAnimation::finished, this, [this]() {
    //     if(m_animation->direction() == QPropertyAnimation::Backward)
    //         hide();
    // });
    connect(m_animation, &QPropertyAnimation::finished, this, [this]() {
        if (m_animation->direction() == QPropertyAnimation::Backward)
        {
            QTimer::singleShot(200, this, &TipWidget::hide);  // 延迟 200 毫秒隐藏
        }
        });
}

TipWidget::~TipWidget()
{
    delete m_animation;
    delete m_timer;
}

#include <QMouseEvent>
void TipWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        m_timer->stop();
        m_animation->stop();
        hide();
    }
    QWidget::mousePressEvent(event);
}

float TipWidget::opacity() const
{
    return m_opacity;
}
void TipWidget::setOpacity(float value)
{
    m_opacity = value;
    update();
}

// void TipWidget::showMessage(const QString& msg)
// {
//     m_timer->stop();
//     m_animation->stop();
//     // m_animation->setDirection(QPropertyAnimation::Forward);

//     if (msg.length() > 128)
//         m_strTipMsg = msg.left(64) + "..." + msg.right(64);
//     else
//         m_strTipMsg = msg;

//     QFont font("Microsoft Yahei", 20);
//     QFontMetrics fm(font);
//     QRect textRect = fm.boundingRect(0, 0, 300, 0, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, msg);

//     int padding = 20;
//     int verticalPadding = 10;
//     setFixedSize(qMax(200, textRect.width() + padding + 20), textRect.height() + verticalPadding + 10);

//     QWidget* mainWindow = parentWidget();
//     if (mainWindow)
//     {
//         QRect mainGeo = mainWindow->geometry();
//         int x = mainGeo.right() - width() - 20;
//         int y = mainGeo.bottom() - height() - 40;
//         move(x, y);
//     }

//     update();
//     show();
//     m_animation->start();
//     m_timer->start(5000);
// }

void TipWidget::showMessage(const QString& msg)
{
    // 停止并重置动画和定时器
    m_timer->stop();
    m_animation->stop();
    m_animation->setDirection(QPropertyAnimation::Forward);

    // 更新消息内容
    if (msg.length() > 68)
        m_strTipMsg = msg.left(34) + "..." + msg.right(34);
    else
        m_strTipMsg = msg;

    m_strTipMsg = m_strTipMsg.trimmed();

    // 计算提示框大小并调整位置
    QFont font("Microsoft Yahei", 20);
    QFontMetrics fm(font);
    QRect rectText = fm.boundingRect(0, 0, 100, 0, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, m_strTipMsg);

    int nPadding = 20;
    int nVPadding = 10;
    setFixedSize(qMax(200, rectText.width() + nPadding + 20), rectText.height() + nVPadding + 10);

    QWidget* mainWindow = parentWidget();
    if (mainWindow)
    {
        QRect mainGeo = mainWindow->geometry();
        int x = mainGeo.right() - width() - 20;
        int y = mainGeo.bottom() - height() - 40;
        move(x, y);
    }

    // 更新并显示提示框
    update();
    show();

    // 开始动画并设置定时器
    m_animation->start();
    m_timer->start(5000);
}

void TipWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制半透明背景
    QPainterPath path;
    path.addRoundedRect(rect(), 8, 8);
    painter.fillPath(path, QColor(50, 50, 50, 200 * m_opacity));

    // 绘制文字
    painter.setPen(QColor(255, 255, 255, 255 * m_opacity));
    painter.setFont(QFont("Microsoft Yahei", 20));
    painter.drawText(rect().adjusted(10, 5, -10, -5),
        Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, m_strTipMsg);
}