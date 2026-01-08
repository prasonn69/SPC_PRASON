# SPC_PRASON
---

# 🏰 Dungeon Adventure (C Console Game)

## 📌 Overview

**Dungeon Adventure** is a text-based console game written in **C**, where the player explores rooms, collects items, fights a monster, and attempts to retrieve a treasure to win the game.

The game uses **structures, functions, conditionals, loops, and string handling**, making it a solid example of core C programming concepts.

---

## 🎮 Game Objective

* Explore different rooms of the dungeon
* Collect essential items (Sword, Torch, Key)
* Defeat the monster
* Unlock the treasure chest
* Escape alive with the treasure

Winning condition: **Open the treasure chest using the key**
Losing condition: **Health drops to 0**

---

## 🧠 Concepts Used

* `struct` for game state management
* Modular programming using functions
* String handling (`strcmp`, `strstr`)
* Conditional logic & loops
* Random seed initialization
* Input handling using `fgets()`

---

## 🗺️ Game Map (Room Layout)

| Room No | Room Name     | Description        |
| ------- | ------------- | ------------------ |
| 0       | Entrance Hall | Starting area      |
| 1       | Armory        | Contains the Sword |
| 2       | Library       | Contains the Torch |
| 3       | Treasure Room | Locked chest       |
| 4       | Dark Corridor | Path to monster    |
| 5       | Monster Den   | Monster + Key      |

---

## 🧰 Items

* 🗝️ **Key** – Required to open the treasure chest
* 🗡️ **Sword** – Required to defeat the monster
* 🔥 **Torch** – Required to enter the dark corridor

---

## 🧟 Monster Mechanics

* Attacking without a sword → lose **40 health**
* Attacking with sword → monster defeated + key obtained
* Monster appears only once

---

## ❤️ Health System

* Player starts with **100 health**
* Monster attack reduces health
* Game ends if health reaches **0**

---

## ⌨️ Available Commands

| Command                       | Action                     |
| ----------------------------- | -------------------------- |
| `north / south / east / west` | Move between rooms         |
| `take sword / torch`          | Pick up items              |
| `fight / attack`              | Fight the monster          |
| `open chest`                  | Open treasure              |
| `look`                        | Redisplay room description |
| `status`                      | Show health and inventory  |
| `help`                        | Show commands              |
| `quit`                        | Exit game                  |

---

## ▶️ How to Compile and Run

### Compile

```bash
gcc dungeon.c -o dungeon
```

### Run

```bash
./dungeon
```

---

## 🏁 Game Endings

* 🏆 **Victory**: Treasure opened successfully
* ☠️ **Death**: Health drops to zero
* 🚪 **Quit**: Player exits manually

---

## 📂 File Information

* `dungeon.c` → Main source file
* `README.md` → Project documentation

---

## 🧪 Possible Improvements (Optional)

* Add save/load feature
* Add multiple monsters
* Add score system
* Add random events

---

## 👨‍💻 Author

**Prason**
Engineering Student
(Console-based C project)

---


