# E-Commerce Recommendation System (C, DSA-Based)

## 📘 Overview
This project implements a **basic E-commerce Recommendation System** using only **Data Structures and Algorithms in C**.  
It demonstrates how simple **item-based collaborative filtering** works using fundamental DSA concepts such as arrays, structs, loops, searching, and sorting — without any external libraries.

The program is **menu-driven** and allows:
- Adding users and their purchased items
- Displaying all users and items
- Generating personalized recommendations for any user based on co-occurrence similarity

---

## 🧠 Concept

### Recommendation Logic
If two items are frequently bought together, they are considered **similar**.  
For a given user, items that have the highest **co-occurrence score** with their previously purchased items are recommended.

**Example:**
- User 1 bought items `{1, 2}`  
- User 2 bought items `{1, 2, 3}`  
→ Item `3` is recommended for User 1 since items 1 and 2 co-occurred with 3 in other users’ data.

---

## ⚙️ Features
- Add user purchase records interactively  
- Show available catalog items  
- View all users and their purchases  
- Generate recommendations for a specific user  
- Preloaded demo dataset for quick testing  

---

## 🧩 Data Structures & Algorithms Used

| Concept | Purpose |
|----------|----------|
| **Arrays** | Store users, items, and catalogs |
| **Structs** | Define user records with ID and item list |
| **Linear Search** | Check whether a user purchased an item |
| **Nested Loops** | Compute item–item co-occurrence similarity |
| **Selection Sort** | Rank recommendations by score |
| **Menu-driven control** | User-friendly console interaction |

---

## 🖥️ How to Compile and Run

### Step 1 — Clone or Download
```bash
git clone https://github.com/<your-username>/ecommerce-recommender-c.git
cd ecommerce-recommender-c
