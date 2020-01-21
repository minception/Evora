shared_library('godot_ui',

    ['Board.cpp', 'BoardLoader.cpp', 'Factory.cpp', 'FactoryLoader.cpp', 'GodotGame.cpp',
     'GodotLibrary.cpp', 'GodotTile.cpp', 'ObjectLoader.cpp', 'Root.cpp', 'TileLoader.cpp',
     'Utils.cpp','GodotScenes.cpp'],

    dependencies: godot_lib,
    include_directories: [ai_inc, control_inc, model_inc, godot_includes],
    link_with: [ai_lib, control_lib, model_lib])
