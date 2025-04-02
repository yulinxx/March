#ifndef TIPWIDGET_H
#define TIPWIDGET_H

/**
 * @class TipWidget
 * @brief 气泡提示控件，支持渐入渐出动画效果
 *
 * 该控件用于在应用程序中显示临时提示信息，支持以下特性：
 * - 淡入淡出动画效果
 * - 自动隐藏功能（3秒后自动消失）
 * - 自定义半透明背景和圆角样式
 *
 * @usage
 * // 创建实例（建议作为全局组件）
 * TipWidget *tip = new TipWidget(parentWidget);
 *
 * // 显示提示信息（自动居中于父控件）
 * tip->showMessage("保存成功");
 *
 * // 手动调整位置
 * tip->move(x, y);
 */

#include <QWidget>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPainter>

class TipWidget final : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float opacity READ opacity WRITE setOpacity)

public:
    static TipWidget *instance(QWidget *parent = nullptr);

private:
    explicit TipWidget(QWidget *parent = nullptr);
    ~TipWidget();

public:
    void mousePressEvent(QMouseEvent *event) override;

public:
    /**
     * @brief 显示带动画的提示信息
     * @param msg 需要显示的文本内容
     */
    void showMessage(const QString &msg);
    float opacity() const;
    
    /**
     * @brief 设置控件透明度（带动画过渡）
     */
    void setOpacity(float value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    static TipWidget *m_instance;

    QPropertyAnimation *m_animation{nullptr};
    ;
    QTimer *m_timer{nullptr};
    QString m_strTipMsg;
    float m_opacity{1.0f};
};

#endif // TIPWIDGET_H
