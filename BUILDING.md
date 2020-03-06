# Installer build instructions for windows
## Requirements
* Scons
* Visual Studio
* Godot Game Engine
* NSIS

## Build instructions
1. Compile godot-cpp submodule
2. Use Visual Studio to build the solution Src\Evora\Evora.sln
3. Using Godot Game Engine open Godot project file in Godot\project.godot
4. Go to menu Project->Export
5. Select the Windows Desktop (Runnable) option and click on Export project
6. Using NSIS open a script Installer\Evora.nsi
