# Binary Search Tree (BST) Operations & File Management System

This project implements key operations on a Binary Search Tree (BST), focusing on **Insertion**, **Deletion**, and **Depth First Search (DFS)** for searching nodes. Additionally, it incorporates **File Handling** to persist data, making it suitable for use cases like **Library Management Systems** or other applications requiring efficient data storage and retrieval.

## Key Features

### Binary Tree Operations:
- **Insertion**: Allows adding nodes to the BST while maintaining its properties.
- **Deletion**: Implements the logic for removing nodes, handling different cases (leaf, one child, two children).
- **DFS for Searching**: Depth First Search (DFS) is used for efficiently finding nodes within the tree.

### Library Management Features:
- **Issue Book**: Simulates the process of issuing books from the library, ensuring correct validation of user actions.
- **Return Book**: Handles the return process, updating the system with the return status and due dates.

### File Handling:
- Uses file operations to store and retrieve data, allowing the system to persist changes between sessions.
- Book details, user information, and transaction records are stored in text or binary files for easy access and modification.

### User Interaction:
- A **menu-driven interface** allows users to interact with the system, choosing from options to issue books, return books, search for books, and manage the BST.

### Validation & Error Handling:
- **Date Validation**: Ensures that issue and return dates are properly formatted and logically correct (e.g., return date cannot be before the issue date).
- **Error Handling**: Catches invalid inputs or system errors (such as trying to issue a non-existent book or delete a node that doesn't exist) and provides appropriate feedback.

## Technologies & Concepts:
- **Binary Search Tree (BST)**
- **Depth First Search (DFS) algorithm**
- **File I/O** (Read/Write operations)
- **Error handling** and **input validation**

---

This repository demonstrates a complete library management system using fundamental data structures and file handling techniques. It can be extended further to integrate more features like user authentication, book search by different criteria, or a more complex data model for the books and users.
