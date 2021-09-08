# RawPtr

A pointer which helps you **avoid**

- copying owning pointers, solved by deleting copy ctors,
- accidentally treating a pointer like an array, solved by disallowing indexing and weird (non-`size_t`) offsets

## Summary

Provides:
- all comparison operators (`operator==`, `operator!=`, `operator<`,etc.)
- `operator+`, `operator-` for very select pointer arithmetic
- `operator*`, `operator->` for accessing fields & methods, but **no** `operator[]`
- `swap()` to swap two pointers
- `std::hash<RawPtr<T>>`
- move-only constructors
- default initialization to nullptr
