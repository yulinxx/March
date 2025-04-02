#include "Command/CommandManager.h"
#include <memory>
#include <vector>
#include <deque>

namespace MEngine
{
    CommandManager::CommandManager(size_t maxHistorySize /*=20*/)
        : m_nMmaxHistory(maxHistorySize)
    {
    }

    CommandManager::~CommandManager()
    {
        clearStacks();
    }

    void CommandManager::execute(CommandPtr cmd)
    {
        cmd->execute();

        if (m_undoStack.size() >= m_nMmaxHistory)
        {
            m_undoStack.pop_front();
        }

        m_undoStack.push_back(std::move(cmd));
        m_redoStack.clear();
    }

    void CommandManager::undo()
    {
        if (!m_undoStack.empty())
        {
            CommandPtr cmd = std::move(m_undoStack.back());
            m_undoStack.pop_back();
            cmd->undo();

            if (m_redoStack.size() >= m_nMmaxHistory)
                m_redoStack.pop_front();

            m_redoStack.push_back(std::move(cmd));
        }
    }

    void CommandManager::redo()
    {
        if (!m_redoStack.empty())
        {
            CommandPtr cmd = std::move(m_redoStack.back());
            m_redoStack.pop_back();
            cmd->execute();

            if (m_undoStack.size() >= m_nMmaxHistory)
                m_undoStack.pop_front();

            m_undoStack.push_back(std::move(cmd));
        }
    }

    void CommandManager::executeBatch(std::vector<CommandPtr> cmds)
    {
        for (auto& cmd : cmds)
        {
            execute(std::move(cmd));
        }
    }

    void CommandManager::undoBatch(size_t count)
    {
        for (size_t i = 0; i < count && canUndo(); ++i)
        {
            undo();
        }
    }

    void CommandManager::redoBatch(size_t count)
    {
        for (size_t i = 0; i < count && canRedo(); ++i)
        {
            redo();
        }
    }

    void CommandManager::clearStacks()
    {
        m_undoStack.clear();
        m_redoStack.clear();
    }

    void CommandManager::setMaxHistorySize(size_t sz)
    {
        m_nMmaxHistory = sz;
        trimStacks();
    }

    size_t CommandManager::getMaxHistorySize() const
    {
        return m_nMmaxHistory;
    }

    void CommandManager::trimStacks()
    {
        while (m_undoStack.size() > m_nMmaxHistory)
        {
            m_undoStack.pop_front();
        }

        while (m_redoStack.size() > m_nMmaxHistory)
        {
            m_redoStack.pop_front();
        }
    }

    bool CommandManager::canUndo() const
    {
        return !m_undoStack.empty();
    }

    bool CommandManager::canRedo() const
    {
        return !m_redoStack.empty();
    }
}