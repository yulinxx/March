#include "ProgressMsg.h"

ProgressMsg::ProgressMsg(QWidget* parent) : QProgressBar(parent)
{
    setRange(0, 100);
    setValue(0);
}

void ProgressMsg::setProgress(int value)
{
    setValue(value);
}