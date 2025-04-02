#pragma once
#include <QPushButton>
#include <QTimer>

/**
 * @brief 带有自动禁用功能的定时按钮控件
 * @details 该按钮在点击后会自动禁用指定时长，通过定时器自动恢复可用状态
 * 
 * 使用示例：
 * @code
 * TimerButton* btn = new TimerButton(this);
 * btn->setDisabledDuration(2000); // 设置2秒禁用时长
 * connect(btn, &TimerButton::stateChanged, [](bool enabled) {
 *     qDebug() << "按钮状态:" << (enabled ? "启用" : "禁用");
 * });
 * @endcode
 */
class TimerButton final : public QPushButton {
    Q_OBJECT
public:
    explicit TimerButton(QWidget* parent = nullptr);
    
    /**
     * @brief 设置按钮禁用时长
     * @param milliseconds 禁用持续时间（毫秒），最小值100毫秒
     */
    void setDisabledDuration(int milliseconds);

signals:
    /**
     * @brief 按钮状态变化信号
     * @param enabled 当前状态：true-启用可用，false-禁用不可用
     * @note 在以下时机触发：
     * 1. 用户点击按钮后立即触发（enabled=false）
     * 2. 定时器超时后自动恢复时触发（enabled=true）
     */
    void sigStateChanged(bool enabled);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QTimer* m_timer;
    int m_duration = 1000;
};