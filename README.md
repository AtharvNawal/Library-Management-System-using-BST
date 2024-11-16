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

## How the System Works

1. **Initialize System**
   - Load the existing list of books from a file (if available). If the file does not exist, initialize with a set of default books.

2. **Display Menu**
   - Show the user a list of options:
     - Display all books
     - Add a new book
     - Delete a book
     - Issue a book to a student
     - Return a book
     - Exit the system
   - Wait for the user to select an option.

3. **Display All Books**
   - Sort and display the list of books, showing their ID, title, author, publication year, issue status, and return date (if issued).

4. **Add a New Book**
   - Prompt the user for the book details: ID, title, author, and publication year.
   - Validate the publication year (must be 2024 or earlier).
   - Add the new book to the list of books.
   - Save the updated list of books back to the file.

5. **Delete a Book**
   - Ask the user for the book ID to delete.
   - Find and remove the book from the list.
   - Save the updated list back to the file.

6. **Issue a Book**
   - Prompt the user for the book ID, the student's name, and the return date.
   - Validate the return date format and ensure the year is 2024.
   - Check if the book is available (not already issued). If available:
     - Mark the book as issued, assigning it to the student, and set the return date.
   - Save the updated list of books back to the file.

7. **Return a Book**
   - Ask for the book ID to return.
   - Find the book and check if it is currently issued.
   - If the book is issued:
     - Mark it as returned and clear the student's name and return date.
   - Save the updated list of books back to the file.

8. **Save Data**
   - After any modification (add, delete, issue, or return), update the file to reflect the latest list of books.

9. **Exit the Program**
   - When the user selects "Exit", terminate the program.

---

This repository demonstrates a complete library management system using fundamental data structures and file handling techniques. It can be extended further to integrate more features like user authentication, book search by different criteria, or a more complex data model for the books and users.
