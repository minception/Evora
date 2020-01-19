project('evora', 'cpp')

godot_dir = '../../godot-cpp'
godot_bin = meson.source_root() + '/' + godot_dir + '/bin'

if host_machine.system() == 'linux'
    godot_libname = 'godot-cpp.linux.debug.64'
elif host_machine.system() == 'windows'
    godot_libname = 'godot-cpp.windows.debug.default'
else
    error('unknown platform')
endif

cpp = meson.get_compiler('cpp')
godot_lib = cpp.find_library(godot_libname, dirs: [godot_bin])

godot_includes = include_directories(
    godot_dir + '/godot_headers',
    godot_dir + '/include',
    godot_dir + '/include/core',
    godot_dir + '/include/gen')

subdir('AzulModel')
subdir('AzulControl')
subdir('AzulAI')
subdir('ConsoleUI')
subdir('GodotUI')
