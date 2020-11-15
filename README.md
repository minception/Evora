# Evora
![game](https://github.com/minception/evora/blob/master/game.png?raw=true)

An implementation of a popular board game Azul.  
Make sure to update submodules recursively before proceeding.

## Windows
### Installation requirements
VC redistributable V16 x64 - can be found at https://aka.ms/vs/16/release/vc_redist.x64.exe
### Build Requirements
* Scons
* Godot game engine
* Microsoft Visual studio with visual c++
* NSIS (for installer creation)
### Build Instructions
* First build the bindings  
```
$ cd godot-cpp
$ scons platform=windows generate_bindings=yes target=runtime
```
* In visual studio set build to release and build the project. After this it should be possible to run the game in godot, following instructions are for creating the installer  

* Open Godot/project.godot using the godot game engine and go to project -> export and click on export.  
* Using NSIS run the script located in Installer\Evora.nsi. Before running the script, the folder should contain these files:
    * Evora.exe
    * Evora.pck
    * LibGodotUI-x64-Release.dll

## Linux
### Requirements
* Scons
* Meson
* Ninja
* Godot game engine
### Build Instructions

```
$ cd godot-cpp
$ scons platform=linux generate_bindings=yes
$ cd ..
$ cd Src/Evora
$ meson
$ cd build
$ ninja
```
After this, it should be possible to run the game in the Godot game engine
