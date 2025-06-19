# 🗂️ File and Directory Management System (DSA Project in C)

A simulation of a simple file system in C using custom data structures. This command-line application allows users to create directories and files, navigate between directories, and display metadata — all modeled using a tree-based structure for hierarchy representation.

---

## 🧩 Tech Stack

- **Language**: C  
- **Data Structures**: Custom Tree (for directory hierarchy)  
- **File Metadata**: Simulated with structs  

---

## 🎯 Features

- 📁 Create and manage directories  
- 📄 Create files with metadata (size, creation date, modification date)  
- 📂 Navigate between parent and child directories  
- 📌 Display absolute and relative paths  
- 🌳 Visualize the entire file system hierarchy  

---

## 🛠️ How It Works

- Uses a **custom tree structure** (`TreeNode`) to simulate files and directories  
- Each node stores:
  - Name
  - Type (file/directory)
  - Pointers to parent, children, and siblings
- Files also store metadata like:
  - Size
  - Creation date
  - Modification date
- Root is initialized as `"C:\"` and users interact via a terminal menu

---

## 🧪 Functional Overview

| Option | Function |
|--------|----------|
| `1` | **Create Directory** – Add a new directory under current location |
| `2` | **Create File** – Add a new file with metadata |
| `3` | **Change Directory** – Navigate into subdirectories or back to parent |
| `4` | **Display File System** – Show hierarchical structure of all files and directories |
| `5` | **Print Absolute Path** – Show full path from root to current directory |
| `6` | **Print Relative Path** – Show relative path based on current context |
| `7` | **Exit** – Quit the program |

---

## 🧬 Sample Data Structure

```c
typedef struct TreeNode {
    char name[MAX_NAME_LENGTH];
    int is_directory;
    union {
        File file_data;
    } data;
    struct TreeNode* parent;
    struct TreeNode* children;
    struct TreeNode* next_sibling;
} TreeNode;
```

## Compilation and execution

gcc file_system.c -o file-system
./file-system

## Sample Run

Options:
1. Create Directory
2. Create File
3. Change Directory
4. Display File System Hierarchy
5. Print Absolute Path
6. Print Relative Path
7. Exit
Enter option (1-7):


## AUTHOR

** S Shreyas **

Project built as part of Data Structures and Algorithms coursework
