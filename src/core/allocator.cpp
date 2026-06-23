#include "core/allocator.hpp"
#include <cstring>

namespace bp::core {

LinearAllocator::LinearAllocator(size_t capacity) : m_capacity(capacity), m_offset(0) {
    m_buffer = new uint8_t[capacity];
}

LinearAllocator::~LinearAllocator() {
    delete[] m_buffer;
}

void* LinearAllocator::allocate(size_t size, size_t alignment) {
    size_t aligned_offset = (m_offset + alignment - 1) & ~(alignment - 1);
    if (aligned_offset + size > m_capacity) return nullptr;
    void* ptr = m_buffer + aligned_offset;
    m_offset = aligned_offset + size;
    return ptr;
}

void LinearAllocator::reset() {
    m_offset = 0;
}

size_t LinearAllocator::getAllocatedSize() const {
    return m_offset;
}

PoolAllocator::PoolAllocator(size_t blockSize, size_t blockCount) : m_blockSize(blockSize), m_blockCount(blockCount) {
    m_memory = new uint8_t[blockSize * blockCount];
    m_freeList = new uint8_t*[blockCount];
    for (size_t i = 0; i < blockCount; ++i) {
        m_freeList[i] = m_memory + (i * blockSize);
    }
    m_freeBlockCount = blockCount;
}

PoolAllocator::~PoolAllocator() {
    delete[] m_memory;
    delete[] m_freeList;
}

void* PoolAllocator::allocate() {
    if (m_freeBlockCount == 0) return nullptr;
    void* ptr = m_freeList[m_freeBlockCount - 1];
    --m_freeBlockCount;
    return ptr;
}

void PoolAllocator::deallocate(void* ptr) {
    if (m_freeBlockCount >= m_blockCount) return;
    m_freeList[m_freeBlockCount] = static_cast<uint8_t*>(ptr);
    ++m_freeBlockCount;
}

size_t PoolAllocator::getFreeBlockCount() const {
    return m_freeBlockCount;
}

}