#pragma once

#include <functional>
#include <type_traits>
#include <utility>

template<class T>
struct RawPtr final {
    RawPtr() = default;
    explicit RawPtr(T* value)
        : ptr(value) { }
    RawPtr& operator=(const T* p) {
        ptr = p;
        return *this;
    }
    RawPtr(RawPtr&& other)
        : ptr(other.ptr) { other.ptr = nullptr; }
    RawPtr& operator=(RawPtr&& other) {
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }
    void swap(RawPtr& other) { std::swap(ptr, other.ptr); }
    T& operator*() { return *ptr; }
    const T& operator*() const { return *ptr; }
    T* operator->() { return ptr; }
    const T* operator->() const { return ptr; }
    T* ptr { nullptr };
};

// only support very basic pointer arithmetic to avoid smelly code
template<class T>
RawPtr<T> operator+(const RawPtr<T>& ptr, std::size_t offset) { return RawPtr<T>(ptr.ptr + offset); }
template<class T>
RawPtr<T> operator-(const RawPtr<T>& ptr, std::size_t offset) { return RawPtr<T>(ptr.ptr - offset); }
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
