cmake_minimum_required(VERSION 3.23)
project(materiel)

set(CMAKE_CXX_STANDARD 20)
set(external_INCLUDE_DIRS
        external/imgui
#        external/imgui_node_editor/NodeEditor/Include
        external/imnodes
        external/glad/include
        external/glfw/include)

set(glad_SOURCE_FILE
        external/glad/src/gl.c)

set(imgui_SOURCE_FILES
        external/imgui/imconfig.h
        external/imgui/imgui.cpp
        external/imgui/imgui.h
        external/imgui/imgui_demo.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_internal.h
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imstb_rectpack.h
        external/imgui/imstb_textedit.h
        external/imgui/imstb_truetype.h
        external/imgui/backends/imgui_impl_opengl3.cpp
        external/imgui/backends/imgui_impl_glfw.cpp)

#set(imgui_node_SOURCE_FILES
#        external/imgui_node_editor/NodeEditor/Source/crude_json.cpp
#        external/imgui_node_editor/NodeEditor/Source/crude_json.h
#        external/imgui_node_editor/NodeEditor/Source/imgui_bezier_math.h
#        external/imgui_node_editor/NodeEditor/Source/imgui_bezier_math.inl
#        external/imgui_node_editor/NodeEditor/Source/imgui_canvas.cpp
#        external/imgui_node_editor/NodeEditor/Source/imgui_canvas.h
#        external/imgui_node_editor/NodeEditor/Source/imgui_extra_math.h
#        external/imgui_node_editor/NodeEditor/Source/imgui_extra_math.inl
#        external/imgui_node_editor/NodeEditor/Source/imgui_node_editor.cpp
#        external/imgui_node_editor/NodeEditor/Source/imgui_node_editor_api.cpp
#        external/imgui_node_editor/NodeEditor/Source/imgui_node_editor_internal.h
#        external/imgui_node_editor/NodeEditor/Source/imgui_node_editor_internal.inl)

set(imnodes_SOURCE_FILE external/imnodes/imnodes.cpp)


set(SOURCE_FILES
        src/main.cpp
        ${glad_SOURCE_FILE}
        ${imgui_SOURCE_FILES}
#        ${imgui_node_SOURCE_FILES}
        ${imnodes_SOURCE_FILE})

add_executable(materiel)
target_sources(materiel PRIVATE ${SOURCE_FILES})
target_include_directories(materiel PRIVATE ${external_INCLUDE_DIRS})
target_link_directories(materiel PRIVATE external/glfw/lib-vc2022)
target_link_libraries(materiel glfw3)