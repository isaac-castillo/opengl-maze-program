cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
project(opengl)


add_executable(
    
opengl 
main.cpp 
window.cpp
input.cpp
action_injection.cpp
input_event_manager.cpp
src/opengl/compiler.cpp
src/opengl/shader.cpp
MoveAction.cpp
create_square_action.cpp
OpenGLShapeCreator.cpp
primitive.cpp
place_square_action.cpp
camera.cpp
transform.cpp
imgui_ui.cpp
imgui/imgui.cpp
imgui/imgui_demo.cpp
imgui/imgui_draw.cpp
imgui/imgui_widgets.cpp
imgui/backends/imgui_impl_glfw.cpp
imgui/backends/imgui_impl_opengl3.cpp

)

include_directories(imgui)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)


target_link_libraries(opengl ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glfw)

