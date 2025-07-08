# Practical Work Nº 2 | Video Game Programming I

## 🎮 Activity
This project is about creating a 2D platformer, implementing in code the concepts of stacks and queues learned in class.

## 🕹️ Gameplay

[![Ver video del gameplay](https://img.youtube.com/vi/468tXj5txqs/0.jpg)](https://youtu.be/468tXj5txqs)


## 📝 Objective
Control a character that must climb platforms, avoid enemies, and reach the exit door before the time runs out.

### Main mechanics:
- 6 platforms the player can move across.
- he character can jump up through platforms from below.
- It’s only possible to go up; you can’t return to previous platforms.
- The character starts on floor 0 and must reach floor 6, where the exit door is.
- Each floor has enemies moving sideways, but only one enemy moves at a time.
- If the player touches an enemy, they fall back to the starting floor (0).

## ⏱️ Game over conditions

- **WIn:** reach the exit before the time runs out.
- **Lose:** run out of time (30 seconds) before reaching the exit.

## 📦 Implementation of Stacks & Queues

### 🔄 Queues (3 floors)

Enemies on three floors use a **queue structure**:

- The first enemy in the queue starts moving.
- When it reaches the end of the floor, it **goes off screen** and is reinserted **at the end of the queue**.
- The cycle repeats with the next enemy waiting.

👉 This simulates a **continuous and orderly flow** of enemies.

### 🔁 Stacks (3 other floors)

The other floors use a **stack structure** (Stack A and Stack B):

- The enemy at the **top of Stack A** moves across the floor.
- When it finishes its path, it’s pushed into **Stack B**.
- When all enemies are in Stack B, the process **reverses**, moving them back to Stack A.

👉 This creates a **cyclical and controlled flow** of enemies..


### Controls

- **A / D**: move
- **Space / W**: jump
- **Shift + A / Shift + D**: run

At the end, you’ll see **Game Over** or **You Win**.

## ⚙️ Technologies used

- C++
- SFML
- Visual Studio

## 🖼️ Assets & License

Graphics used in this project come from:

- **CHARACTER ANIMATION ASSET PACK**
- **CITY STREET TILESET PACK**

Created by **Mucho Pixels**, a studio specialized in pixel art for games.

> The **CHARACTER ANIMATION ASSET PACK** is completely free to use in commercial projects, with the following restrictions:

❌ You can't redistribute the files directly.  
❌ You can't use them as part of a logo or registered trademark.

🔗 Official site: [www.muchopixels.com]

---

## 📦 Download

[Download on itch.io](https://juliocz36.itch.io/platformer-stacks-queues)

---

## 👨‍💻 Autor

**JulioCZ** - Technical Degree in Video Game Design and Programming
