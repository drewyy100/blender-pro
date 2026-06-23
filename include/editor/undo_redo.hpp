#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <string>

namespace bp::editor {

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string getName() const = 0;
};

class UndoRedoManager {
public:
    UndoRedoManager(size_t maxHistory = 100);
    void execute(std::shared_ptr<Command> command);
    void undo();
    void redo();
    void clear();
    bool canUndo() const;
    bool canRedo() const;
    std::string getUndoName() const;
    std::string getRedoName() const;
    size_t getHistorySize() const;
    size_t getMaxHistorySize() const;
    void setMaxHistorySize(size_t maxSize);

private:
    std::vector<std::shared_ptr<Command>> m_undoStack;
    std::vector<std::shared_ptr<Command>> m_redoStack;
    size_t m_maxHistory;
};

template<typename T>
class LambdaCommand : public Command {
public:
    LambdaCommand(const std::string& name, std::function<void()> executeFunc, std::function<void()> undoFunc)
        : m_name(name), m_execute(executeFunc), m_undo(undoFunc) {}
    
    void execute() override { m_execute(); }
    void undo() override { m_undo(); }
    std::string getName() const override { return m_name; }

private:
    std::string m_name;
    std::function<void()> m_execute;
    std::function<void()> m_undo;
};

}