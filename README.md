# Ray Tracer

Just a simple real-time Ray Tracer I built using C++ and the [Walnut](https://github.com/TheCherno/Walnut) framework. It's got basic sphere rendering, lighting, and you can fly around the scene.

## Features

- **Real-time Rendering**: You can see the spheres update as you move them.
- **Scene Editor**: There's a UI to mess around with the spheres (change position, radius, color).
- **Camera**: Fly around the scene like a standard game camera.
- **Resizing**: The viewport resizes with the window.

## How to Run It

### Prerequisites
- Visual Studio 2022
- Git

### Setup

1.  **Clone it:**
    Make sure to use recursive so you get the submodules.
    ```bash
    git clone --recursive https://github.com/ayusman-1005/Ray-Tracer.git
    ```

2.  **Generate Files:**
    Run the setup script in the `scripts` folder:
    ```bash
    scripts/Setup.bat
    ```
    This makes the Visual Studio solution file (`RayTracer.sln`).

3.  **Build:**
    - Open `RayTracer.sln`.
    - Set `RayTracer` as the startup project.
    - Hit F5 to run.

## Controls

- **Navigation**: Hold **Right Click** on the viewport to look around.
  - **W, A, S, D**: Move forward, left, back, right.
  - **Q, E**: Move down and up.
- **Scene Panel**: Add or change spheres here.
- **Settings**: Check render time or force a render.

## Tech Stack

- **C++**
- **[Walnut](https://github.com/TheCherno/Walnut)**
- **[ImGui](https://github.com/ocornut/imgui)**
- **[GLM](https://github.com/g-truc/glm)**