# 🔤 Custom Radix Sort vs std::sort

This project puts a custom radix sort head-to-head against the C++ standard sort.  
The task: sort 10 million fixed-length strings made from a tiny alphabet.  
No tricks, no fancy abstractions — just raw sorting logic and timing.

> ✍️ I wrote the function `radix_par` from scratch — you’ll find it in `sort.cpp`.  
> Everything else is just setup, timing, and result verification.

---

## 🧠 What It Does

- Generates 10,000,000 strings of length 3  
- Strings are made from this alphabet: `"ABCDE"`  
- Uses two sorting strategies:
  - 🧪 `radix_par`: student’s custom radix sort (pointer-based)
  - 🧊 `std::sort`: baseline sort with pointer dereferencing

After sorting, results are verified for correctness and runtime is measured.

---

## 📦 File Breakdown

| File         | What it does                        |
|--------------|-------------------------------------|
| `sort.cpp`   | ⭐ My implementation of `radix_par` |
| `main.cpp`   | Generates data, runs both sorts     |
| `sort.h`     | Interface definition                |
| `test.h`     | Sorting test logic + verification   |

---

## 🛠 How To Run

Make sure you have a C++17-compatible compiler.

```bash
g++ -std=c++17 main.cpp sort.cpp -o sort_test
./sort_test
```

Expected output looks like this:
```rust
student's radix sort       257ms
std::sort                  435ms
```
Or:

```rust
student's radix sort       --- wrong result ---
std::sort                  450ms
```

## 💬 Why It Matters
Sorting 10 million items isn’t hard — but doing it fast and right is.
This wasn’t just about writing a sorting algorithm — it was about:
- handling fixed-length string sorting efficiently
- using pointers for speed
- keeping results reproducible and testable

> If it sorts wrong, it’s **useless**. <br>If it sorts slow, it’s **boring**. <br>I made sure it’s neither.

## 📜 License
MIT. Use it, tweak it, break it, fix it. Just don’t submit it as your own homework.

## 👤 Author
🦾 Crafted by Aleksandra Kenig (aka [yourpunk](https://github.com/yourpunk)).<br>
💌 Wanna collab or throw some feedback? You know where to find me.
