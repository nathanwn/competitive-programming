# Notes for team

## Coding Style

### Indentation

- 4 spaces

### Brackets

- Whatever

### Naming rules

- Variables: `lower_case_with_underscore`
- Constants: `lowerCamelCase`
- Functions/Methods: `lowerCamelCase`
- Struct/Classes: `UpperCase`
- Files: `lower_case_with_underscore.cc`

### Naming conventions

- Graphs:
  - Adjacency list should be named `adj` (avoid using `g` in this case, since it can be ambiguous whether `g` is an adjacency list or matrix).
  - You should avoid naming adjacency matrix `adj` if you can.
  - An instance of a `Graph/DiGraph` class (which wraps around `adj`) can be named `g` or `graph`.
  - For a directed edge, the initial vertex is always named `u` and the terminal vertex is always named `v`.
  - The weight of an edge should be named `w`.
  - If is not stated otherwise in the problem statement, the number of vertices should be `n` and the number of edges should be `m`.
- Ranges on an array should be named `[from, to]`.

### Other things to consider

- You should minimize the use of `pair`, as it is not always easy to quickly understand what `first` and `second` are. (Although sometimes it is too convenient  to use `pair` and using a struct would not make it more understandable anyway).
- If a problem has multiple tests in the input, we should create a `Solver` class and create a new instance of `Solver` each time we solve a new test.
- Referencing (with `&`) as much as you can to avoid unnecessary copying (sometimes it causes TLE unintentionally). When you want to make sure you don't change anything by mistake, use `const`.
