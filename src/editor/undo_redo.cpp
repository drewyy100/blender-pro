#include "editor/undo_redo.hpp"
#include "core/logger.hpp"
#include <algorithm>

namespace bp::editor {

UndoRedoManager::UndoRedoManager(size_t maxHistory) : m_maxHistory(maxHistory) {}

void UndoRedoManager::execute(std::shared_ptr<Command> command) {
    if (!command) return;
    command->execute();
    m_undoStack.push_back(command);
    m_redoStack.clear();
    if (m_undoStack.size() > m_maxHistory) {
        m_undoStack.erase(m_undoStack.begin());
    }
    bp::core::Logger::debug("Command executed: {}", command->getName());
}

void UndoRedoManager::undo() {
    if (!canUndo()) return;
    auto command = m_undoStack.back();
    m_undoStack.pop_back();
    command->undo();
    m_redoStack.push_back(command);
    bp::core::Logger::debug("Undo: {}", command->getName());
}

void UndoRedoManager::redo() {
    if (!canRedo()) return;
    auto command = m_redoStack.back();
    m_redoStack.pop_back();
    command->execute();
    m_undoStack.push_back(command);
    bp::core::Logger::debug("Redo: {}", command->getName());
}

void UndoRedoManager::clear() {
    m_undoStack.clear();
    m_redoStack.clear();
}

bool UndoRedoManager::canUndo() const {
    return !m_undoStack.empty();
}

bool UndoRedoManager::canRedo() const {
    return !m_redoStack.empty();
}

std::string UndoRedoManager::getUndoName() const {
    if (!canUndo()) return "";
    return m_undoStack.back()->getName();
}

std::string UndoRedoManager::getRedoName() const {
    if (!canRedo()) return "";
    return m_redoStack.back()->getName();
}

size_t UndoRedoManager::getHistorySize() const {
    return m_undoStack.size();
}

size_t UndoRedoManager::getMaxHistorySize() const {
    return m_maxHistory;
}

void UndoRedoManager::setMaxHistorySize(size_t maxSize) {
    m_maxHistory = maxSize;
}

}