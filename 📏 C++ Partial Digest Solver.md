# 📏 C++ Partial Digest Solver

A C++ implementation of the **Partial Digest Problem** using a recursive backtracking algorithm. The program reconstructs possible point locations from a collection of pairwise distances.

## 🚀 Features

- 🧩 Solves the Partial Digest Problem
- 🔄 Uses recursive backtracking
- 📂 Reads distance data from an input file
- 🔍 Validates candidate point placements
- 📐 Calculates distances between reconstructed points
- 💾 Writes discovered solutions to an output file
- 🛠️ Uses C++ STL containers and algorithms

## 🧠 How It Works

The program receives a collection of distances between unknown points.

It first finds the **largest distance**, which represents the total width of the reconstructed point set. The endpoints `0` and the maximum width are placed first.

The program then uses **backtracking** to test possible positions for the remaining points. A position is accepted only when all required distances are available in the remaining distance collection.

**Backtracking** means trying a possible solution, continuing if it works, and going back to try another option when it does not.

## 🛠️ Technologies

- C++
- C++17
- STL
- Recursive Algorithms
- Backtracking
- File I/O
- Vectors
- Sorting and Searching

## ⚙️ Compile

```bash
g++ -std=c++17 -O2 main.cpp -o Prog2
```

## ▶️ Run

```bash
./Prog2 pdp_input_sample.txt
```

The sample input contains a collection of pairwise distances that the algorithm uses to reconstruct possible point sets.

## 📤 Output

The program writes the discovered solutions to:

```text
Prog2-output.txt
```

A reconstructed solution is displayed in a format similar to:

```text
X = { 0, 3, 7, 10 }
```

## 📚 Concepts Demonstrated

This project demonstrates my understanding of:

- Recursive problem solving
- Backtracking algorithms
- Algorithm design
- Data validation
- C++ classes
- STL containers and algorithms
- File input and output

## 🎯 Purpose

This project was created to practice solving a reconstruction problem with algorithmic techniques in C++. It demonstrates how backtracking can systematically explore candidate solutions while rejecting placements that do not satisfy the required distance constraints.

## 👨‍💻 Portfolio Project

This project is part of my C++ programming portfolio and demonstrates practical experience with algorithms, recursion, data structures, and structured problem solving.