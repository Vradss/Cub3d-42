# 🎮 Cub3D

Cub3D is a **simple 3D graphics engine** built in C, inspired by the legendary *Wolfenstein 3D*.  
It was developed as part of the **42 school **, and it uses **raycasting** to render a real-time first-person view from a 2D map.

> 💡 No external libraries are used — only the C standard library and **MiniLibX**.

---

## 🧠 Features

- Real-time **raycasting** rendering engine
- First-person movement (WASD + arrow keys)
- **Minimap** (optional bonus)
- Support for **textured walls**
- Basic collision detection
- Clean, modular C code (max 25 lines per function)
- Built without any external dependencies

---

## Parsing FC tests:

✅ 1. error_invalid_characters.cub

F 120,xx,255

Expected Output:
Error:
Invalid characters in RGB line

✅ 2. error_rgb_out_of_range.cub

C 256,100,100

Expected Output:
Error:
RGB value out of range

✅ 3. error_missing_rgb_component.cub

F 120,120

Expected Output:
Error:
Missing RGB components

✅ 4. error_missing_commas.cub

C 100 100 100

Expected Output:
Error:
Missing commas in RGB

✅ 5. error_duplicate_F.cub

F 100,100,100
F 200,200,200

Expected Output:
Error:
Duplicate 'F' color

✅ 6. error_invalid_identifier.cub

Z 100,100,100

Expected Output:
Error:
Wrong attributes

✅ 7. error_rgb_symbol.cub

C 100,100,#100

Expected Output:
Error:
Invalid characters in RGB line

✅ 8. valid_colors.cub

F 100,150,200
C 50,60,70

Expected Output:
✅ No error — should proceed to map check or next validation.