# RawPtr

A pointer which helps you **avoid**

- copying owning pointers, solved by deleting copy ctors,
- accidentally treating a pointer like an array, solved by disallowing indexing and weird (non-`size_t`) offsets
