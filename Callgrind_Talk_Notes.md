# Profiling C++ Code with Callgrind & KCachegrind

## 1. Introduction
- Profiling helps identify performance bottlenecks in code.
- Callgrind (part of Valgrind) collects detailed information about function calls and instruction usage.
- KCachegrind is a GUI to visualize Callgrind output.

## 2. What is Callgrind?
- A Valgrind tool for profiling programs, especially C/C++.
- Measures function calls, instruction counts, and (optionally) cache usage.

## 3. Example C++ Programs
- We'll use small C++ programs to demonstrate profiling:
  - `fib_recursive.cpp`: Recursive Fibonacci
  - `fib_iterative.cpp`: Iterative Fibonacci
  - `sort.cpp`: Simple sorting
  - `matrix_mult.cpp`: Matrix multiplication

## 4. Compiling for Profiling
- Always compile with debug symbols for best results:
  ```sh
  g++ -g -O2 fib_recursive.cpp -o fib_recursive
  ```

## 5. Running Callgrind
- Basic usage:
  ```sh
  valgrind --tool=callgrind ./fib_recursive
  ```
- Output: `callgrind.out.<pid>`

## 6. Analyzing Results
- Use `callgrind_annotate` to view results in the terminal:
  ```sh
  callgrind_annotate callgrind.out.<pid>
  ```
- Key metrics: instruction counts, function call counts, call graph

## 7. Visualizing with KCachegrind
- Open the output file in KCachegrind:
  ```sh
  kcachegrind callgrind.out.<pid>
  ```
- Explore call graphs, source code view, and hotspots

## 8. Useful Callgrind Options
- `--dump-instr=yes`: Show instruction counts
- `--simulate-cache=yes`: Enable cache simulation
- `--collect-jumps=yes`: Collect jump info
- `--callgrind-out-file=custom.out`: Custom output file name
- Example:
  ```sh
  valgrind --tool=callgrind --simulate-cache=yes ./matrix_mult
  ```

## 9. Comparing Implementations
- Profile both `fib_recursive` and `fib_iterative` to compare performance.
- Discuss how algorithmic changes affect profiling results.

## 10. Tips & Best Practices
- Use `--instr-atstart=no` and `callgrind_control -i on` to focus on specific code regions.
- Profile real-world projects for actionable insights.

## 11. Q&A

---

### References
- [Valgrind Documentation](http://valgrind.org/docs/manual/manual.html)
- [KCachegrind](https://kcachegrind.github.io/html/Home.html)

---

**See the provided C++ files for hands-on examples.**
