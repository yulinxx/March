#ifndef STATUSINFOBAR_H
#define STATUSINFOBAR_H

#include <QStatusBar>

#include "CoordInfoMsg.h"
#include "ItemsMsg.h"
#include "ProgressMsg.h"
#include "HardMsg.h"

class StatusInfoBar final : public QStatusBar
{
    Q_OBJECT
public:
    StatusInfoBar(QWidget *parent = nullptr);
    ~StatusInfoBar();

public slots:
    void slotSetCoordInfo(float x, float y);
    void slotSetItemsInfo(const size_t n);
    void slotSetHardwareInfo(const QString &text);

    void slotSetProgressValue(int value);

public:
    void showProgress();
    void hideProgress();

private:
    CoordInfoMsg *m_coordMsg{nullptr};
    ItemsMsg *m_itemsMsg{nullptr};
    ProgressMsg *m_progressMsg{nullptr};
    HardMsg *m_hardwareMsg{nullptr};
};

#endif // STATUSINFOBAR_H