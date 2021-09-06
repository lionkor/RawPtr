#pragma once

#include <functional>
#include <utility>

template<class T>
struct RawPtr final {
    RawPtr() = default;
    explicit RawPtr(T*&& value)
        : ptr(value) { }
    RawPtr(const RawPtr&) = delete;
    RawPtr& operator=(const RawPtr&) = delete;
    RawPtr(RawPtr&& other)
        : ptr(other.ptr) { other.ptr = nullptr; }
    RawPtr& operator=(RawPtr& other) { swap(other); }
    void swap(RawPtr& other) { std::swap(ptr, other.ptr); }
    T& operator*() { return *ptr; }
    const T& operator*() const { return *ptr; }
    T* operator->() { return ptr; }
    const T* operator->() const { return ptr; }
    operator bool() const { return bool(ptr); }
    // only support very basic pointer arithmetic to avoid smelly code
    RawPtr operator+(std::size_t offset) const { return RawPtr(ptr + offset); }
    RawPtr operator-(std::size_t offset) const { return RawPtr(ptr - offset); }
    T* ptr { nullptr };
};

// comparison operators
template<class T>
bool operator==(const RawPtr<T>& a, const RawPtr<T>& b) { return a.ptr == b.ptr; }
template<class T>
bool operator!=(const RawPtr<T>& a, const RawPtr<T>& b) { return a.ptr != b.ptr; }
template<class T>
bool operator<(const RawPtr<T>& a, const RawPtr<T>& b) { return a.ptr < b.ptr; }
template<class T>
bool operator>(const RawPtr<T>& a, const RawPtr<T>& b) { return a.ptr > b.ptr; }
template<class T>
bool operator<=(const RawPtr<T>& a, const RawPtr<T>& b) { return a.ptr <= b.ptr; }
template<class T>
bool operator>=(const RawPtr<T>& a, const RawPtr<T>& b) { return a.ptr >= b.ptr; }

// std::hash of RawPtr
namespace std {
template<class T>
struct hash<RawPtr<T>> {
    size_t operator()(const RawPtr<T>& ptr) { return std::hash<T*>(ptr.ptr); }
};
};
