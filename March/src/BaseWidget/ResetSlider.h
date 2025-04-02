#pragma once
#include <QSlider>
#include <QMouseEvent>

/**
 * @brief 支持双击滑块重置默认值的滑动条控件
 * @details 该控件继承自QSlider，在原有功能基础上增加：
 * - 双击滑块区域重置为默认值
 * - 可动态设置默认值
 * - 提供重置操作信号
 *
 * @usage
 * @code
 * ResetSlider* slider = new ResetSlider(Qt::Horizontal, this);
 * slider->setDefaultValue(50);
 * connect(slider, &ResetSlider::resetValue, [](int value) {
 *     qDebug() << "滑块重置为:" << value;
 * });
 * @endcode
 */
class ResetSlider final : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(int defaultValue READ defaultValue WRITE setDefaultValue)
public:
    explicit ResetSlider(Qt::Orientation orientation, QWidget* parent = nullptr);

    /**
     * @brief 获取当前默认值
     */
    int defaultValue() const;

    /**
     * @brief 设置新的默认值
     * @param value 需要设置的默认值，自动限制在有效范围内
     */
    void setDefaultValue(int value);

signals:
    /**
     * @brief 数值重置信号
     * @param value 重置后的数值
     * @note 在以下时机触发：
     * 1. 双击滑块区域完成重置操作后
     */
    void resetValue(int value);

protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    int m_nDefaultValue = 0;
};