# Grocery List — Linked List System

## Project Overview

A C++ grocery shopping cart application that uses a singly linked list to manage items.

The program reads product information from a text file, allows users to add and remove groceries, calculates prices and taxes, and generates a receipt.

## Technologies Used

- C++
- Singly Linked Lists
- Dynamic Memory Allocation
- File I/O
- Pointers and Structures

## Project Features

- Read grocery products from an external database (`item.txt`).
- Add grocery items to a shopping cart.
- Maintain items in ascending order by item number.
- Remove items from the cart.
- Calculate quantities, subtotals, and taxes.
- Display the shopping cart.
- Generate a receipt in `Olu.txt`.

## How to Run

1. Download `lab2.5.cpp` and `item.txt`.
2. Keep both files in the same folder.
3. Compile the program using a C++ compiler:

```bash
g++ lab2.5.cpp -o grocery-cart
```

4. Run the executable:

```bash
./grocery-cart
```

5. Follow the menu instructions to manage your shopping cart.

## Known Limitations

- Duplicate item numbers in the product database may prevent some products from being selected.
- Adding an item already at the head of the linked list may create a duplicate entry instead of combining quantities.

## Project Information

**Language:** C++  
**Project Type:** Individual Programming Project  
**Focus:** Linked Lists, Data Structures, and File Handling
