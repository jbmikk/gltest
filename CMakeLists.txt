cmake_minimum_required (VERSION 2.8.0)
project (gltest)

add_executable (
        gltest
        gltest.c
        matrix.c
        context.c
        texture.c
        model.c
        camera.c
        window.c
        input.c
)


#Link GLFW
#-----------

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
target_link_libraries(gltest ${GLFW_STATIC_LIBRARIES})
#target_link_libraries(gltest ${GLFW_LIBRARIES})
#target_link_libraries(gltest glfw3)

message(STATUS "Link GLFW: ${GLFW_STATIC_LIBRARIES}")


#Link GLEW
#-----------

find_package(GLEW REQUIRED)
target_link_libraries(gltest ${GLEW_LIBRARIES})
message(STATUS "Link GLEW: ${GLEW_LIBRARIES}")


#Link OpenGl
#-----------

find_package(OpenGL REQUIRED)
target_link_libraries(gltest ${OPENGL_LIBRARIES} )
message(STATUS "Link OpenGl: ${OPENGL_LIBRARIES}")


message(STATUS "Copy Textures")
file(COPY textures DESTINATION .)
file(GLOB files "textures/*")
foreach(filename ${files})
	file(COPY ${filename} DESTINATION "./textures")
endforeach()
