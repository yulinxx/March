#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <memory>
#include <deque>
#include "Command.h"

namespace MEngine
{
    using CommandPtr = std::unique_ptr<Command>;

    class CommandManager final
    {
    public:
        CommandManager(size_t maxHistorySize = 20);
        ~CommandManager();

    public:
        void execute(CommandPtr cmd);
        void undo();
        void redo();

        void executeBatch(std::vector<CommandPtr> cmds);
        void undoBatch(size_t count);
        void redoBatch(size_t count);

        bool canUndo() const;
        bool canRedo() const;

        void setMaxHistorySize(size_t sz);
        size_t getMaxHistorySize() const;

    private:
        void trimStacks();
        void clearStacks();

    private:
        std::deque<CommandPtr> m_undoStack;   // 已执行命令栈
        std::deque<CommandPtr> m_redoStack;   // 已撤销命令栈

        size_t m_nMmaxHistory{ 20 };            // 最大历史记录数
    };
}

#endif // COMMANDMANAGER_H