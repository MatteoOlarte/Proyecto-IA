---
description: Development guidelines for the Wumpus World project in C++ (Group SN3). Use this skill for any design decision, implementation, code review, or any question related to the project.

paths:
  - "**/*"
---

# Project Guidelines — Wumpus World (Group SN3)

## Language

- **User:** Spanish C2 / English B2
- **Chat:** Spanish; short and direct responses.
- **Code:**
  - Identifiers (variables, functions, constants): English
  - Documentation, comments, and console messages: Spanish, formal third-person style

---

## Project Description

Console simulation of the classic **Wumpus World** game, implemented in **C++** using **structured programming**.

The agent navigates a grid searching for gold while avoiding the Wumpus and pits, reasoning from perceptions to decide its actions.

---

## Technical Constraints (MANDATORY)

| Constraint         | Detail                                                           |
| ------------------ | ---------------------------------------------------------------- |
| Language           | Standard C++ (C++11 or higher)                                   |
| Paradigm           | **Structured programming only** — no classes, no objects, no OOP |
| Containers         | **Plain arrays (`[]`) only** — `#include <vector>` is forbidden  |
| Graphics libraries | **Forbidden** — console output only (`cout`)                     |
| Time libraries     | Allowed (`<chrono>`, `<ctime>`) if the team decides to use them  |
| STL utilities      | Allowed: `<algorithm>`, `<string>`, `<iostream>`, `<cstdlib>`    |

> **Golden rule:** If it is not a plain function or a C-style array, ask before using it.

---

## File Structure

The entire project must be contained in a **single file:**

```
main.cpp    <- All code: constants, structs, functions, and main()
```

Internal organization within `main.cpp` (in this order):

1. `#include` directives and global constants
2. Struct definitions
3. Function prototypes
4. `main()` function
5. Function implementations

---

## Naming Conventions

| Element         | Style            | Example                                 |
| --------------- | ---------------- | --------------------------------------- |
| Functions       | PascalCase       | `MoveAgent()`, `PrintPerceptionTable()` |
| Constants       | UPPER_SNAKE_CASE | `GRID_SIZE`, `MAX_ACTIONS`              |
| Local variables | camelCase        | `currentRow`, `actionCount`             |
