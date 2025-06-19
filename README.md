# 🔤 Custom Radix Sort vs std::sort

This project compares a custom pointer-based radix sort with the C++ standard sort — both racing through 10 million fixed-length strings.  
No abstractions, no STL tricks — just raw sorting logic and hard numbers.

> ✍️ Core function `radix_par` was written from scratch (see `sort.cpp`).  
> The rest: setup, timing, and correctness verification.

---

## ⚙️ What It Does

- Generates **10,000,000 strings**, each 3 characters long  
- Uses a limited alphabet: `"ABCDE"`  
- Runs two sorting algorithms:
  - 🧪 `radix_par`: custom implementation using direct memory access
  - 🧊 `std::sort`: baseline comparison using pointer dereferencing

Each run checks correctness and benchmarks the runtime.

---

## 🧠 Why It Matters

Sorting short fixed-length strings is deceptively simple — but when the input explodes, so do the bottlenecks.  
This project explores:

- raw pointer access vs STL dereferencing
- low-level memory efficiency
- **when** a hand-written algorithm can beat the standard one — and **why**

> ⚠️ If it sorts wrong, it's useless.  
> 🐌 If it sorts slow, it's boring.  
> 💣 I made sure it's neither.

---

## 📁 Project Structure

| File        | Role                                 |
|-------------|--------------------------------------|
| `sort.cpp`  | ⭐ Yourpunk's implementation of `radix_par` |
| `main.cpp`  | Input generation, execution, timing  |
| `sort.h`    | Header for sort interface            |
| `test.h`    | Test runner and result validator     |

---

## 🚀 Running the Code

Requires a **C++17**-compatible compiler.

```bash
g++ -std=c++17 main.cpp sort.cpp -O2 -o sort_test
./sort_test
```

Example output:

``` yaml
student's radix sort       257ms
std::sort                  435ms
```

Or, if broken:
```yaml
student's radix sort       --- wrong result ---
std::sort                  450ms
```

# 🔍 Dev Notes

- `radix_par()` is written from scratch, optimized for this specific task
- Assumes string length and alphabet size are fixed & known at compile time
- Code is deliberately raw — meant for learning, not production

# 📜 License

MIT — Use, modify, fork. Just don’t hand it in as your homework.  
That would be lazy. You're better than that.

## 👤 Author
🦾 Crafted by Aleksandra Kenig (aka [yourpunk](https://github.com/yourpunk)).<br>
### Want to collab or roast my radix? Hit me up.
