# Declare project
project(
    'Noctyra',
    'c',
    version: '1.0',
    default_options : ['c_std=c11', 'c_visibility=default']
)

# Find dependencies
glfw = dependency('glfw3', required: true)
opengl = dependency('gl', required: true)

# Glad Dependency building
glad_sources = files('vendor/glad.c')
glad = declare_dependency(
    include_directories: include_directories('vendor/include/glad'),
    sources: glad_sources
)

cglm = declare_dependency(
    include_directories: include_directories('vendor/include/cglm')
)

# Compile the engine
engine_sources = files(
    'src/renderer.c',
    'src/window.c',
    'src/quad.c'
)
engine = shared_library(
    'noctyra',
    engine_sources,
    include_directories: include_directories('include'),
    dependencies: [glfw, opengl, glad, cglm],
    install: true
)

# Build executable
executable(
    'main',
    [
        'example/main.c',
    ],
    include_directories: include_directories('include'),
    dependencies: [glfw, opengl, glad, cglm],
    link_with: engine,
    install: true
)