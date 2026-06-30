# 💡 Lighting, Shadows and Movement

An interactive 3D visualization built with **OpenGL** and **GLUT**.  
Watch a teapot move, rotate, and change colors in a dynamically lit environment!

---

## 🎮 Features

- **Real-time 3D rendering** — OpenGL with lighting and shadows
- **Dynamic color cycling** — the teapot smoothly transitions through colors
- **Continuous rotation** — the teapot spins on a random axis
- **Random movement** — the teapot drifts in a random direction
- **Dynamic background** — a pulsing checkerboard pattern
- **Multi-light setup** — two light sources for realistic shading

---

## 🛠️ Technologies Used

- **C++** — core logic
- **OpenGL / GLUT** — 3D graphics rendering

---

## 🚀 How to Build

### Requirements

Install OpenGL and GLUT:

bash
# Ubuntu / Debian
sudo apt install freeglut3-dev mesa-common-dev

# macOS (Homebrew)
brew install freeglut

# Windows (use MSYS2 or vcpkg)


## Compile

g++ -o lighting lighting.cpp \
    -lGL -lGLU -lglut -lm

## Run

./lighting










