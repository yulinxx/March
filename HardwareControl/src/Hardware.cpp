#include "Hardware.h"

Hardware::Hardware() : value(42)
{
}

Hardware::~Hardware()
{
}

int Hardware::GetValue() const
{
    return value;
}