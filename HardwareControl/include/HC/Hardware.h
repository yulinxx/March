#ifndef HARDWARE_H
#define HARDWARE_H

#include "HardwareAPI.h"

class HARDWARE_API Hardware final
{
public:
    Hardware();
    ~Hardware();

    int GetValue() const;

private:
    int value;
};

#endif // HARDWARE_H