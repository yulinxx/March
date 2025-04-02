#ifndef COMMAND_H
#define COMMAND_H

#include "Scene/Group.h"
#include "Entity/Entity.h"

#include "Ut/tools.h"
#include <vector>
#include <memory>

namespace MEngine
{
    class MENGINE_API Command
    {
    public:
        virtual ~Command() = default;

    public:
        virtual void execute() = 0; // 执行操作
        virtual void redo() = 0;    // 执行操作
        virtual void undo() = 0;    // 撤销操作
    };
}

#endif // COMMAND_H