#pragma once
#include <cstddef>
#include <cstdint>

namespace bp::core {

class LinearAllocator {
public:
    explicit LinearAllocator(size_t capacity);
    ~LinearAllocator();
    void* allocate(size_t size, size_t alignment = 16);
    void reset();
    size_t getAllocatedSize() const;
private:
    uint8_t* m_buffer;
    size_t m_capacity;
    size_t m_offset;
};

class PoolAllocator {
public:
    PoolAllocator(size_t blockSize, size_t blockCount);
    ~PoolAllocator();
    void* allocate();
    void deallocate(void* ptr);
    size_t getFreeBlockCount() const;
private:
    uint8_t* m_memory;
    uint8_t** m_freeList;
    size_t m_blockSize;
    size_t m_blockCount;
    size_t m_freeBlockCount;
};

}