cmake_minimum_required (VERSION 2.8.0)
project (gltest)

include(ExternalProject)


# Include externals
# -----------------

include_directories("${CMAKE_BINARY_DIR}/xmatrix-prefix/src/xmatrix/src")

externalproject_add(
        xmatrix
        GIT_REPOSITORY git@github.com:jbmikk/matrix.git
        GIT_TAG 0.1.0
        DOWNLOAD_NAME matrix
        DOWNLOAD_DIR matrix
        INSTALL_COMMAND ""
        UPDATE_DISCONNECTED 1
)

include_directories("${CMAKE_BINARY_DIR}/ctest-prefix/src/ctest/src")

externalproject_add(
        ctest
        GIT_REPOSITORY git@github.com:jbmikk/ctest.git
        DOWNLOAD_NAME ctest
        DOWNLOAD_DIR ctest
        INSTALL_COMMAND ""
        UPDATE_DISCONNECTED 1
)


# Add matrix static library
# -------------------------

set(MATRIX_DIR "${CMAKE_BINARY_DIR}/xmatrix-prefix/src/xmatrix-build")

add_library(matrix STATIC IMPORTED GLOBAL) 

set_property(
        TARGET matrix
        PROPERTY IMPORTED_LOCATION "${MATRIX_DIR}/libmatrix.a"
)


# Add matrix update target
# ------------------------

externalproject_add_steptargets(xmatrix update)

add_custom_target(
        update 
        DEPENDS xmatrix-update
)


# Pars
# ----

add_executable (
        gltest
        gltest.c
        context.c
        loaders.c
        model.c
        camera.c
        window.c
        input.c
)

add_dependencies(gltest xmatrix)

target_link_libraries(gltest matrix)

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


message(STATUS "Copy assets")
file(COPY assets DESTINATION .)
file(GLOB files "assets/*")
foreach(filename ${files})
	file(COPY ${filename} DESTINATION "./assets")
endforeach()


# Tests
# -----

include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(loaders_test test/loaders_test.c)

add_dependencies(loaders_test ctest)
