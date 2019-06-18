# Fuer Elite - 64k Intro by Team210 at Underground Conference 9
# Copyright (C) 2018  Alexander Kraus <nr4@z10.info>
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.12)

project(fuer-elite)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CTRL_ALT_TEST_MINIFIER OFF)

# Find the right python interpreter version
find_package(Python3 REQUIRED COMPONENTS Interpreter)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)

if(MSVC AND ${CTRL_ALT_TEST_MINIFIER})
    find_program(MINIFIER shader_minifier.exe HINTS ${PROJECT_BINARY_DIR})
    add_custom_target(minification
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
else()
    add_custom_target(minification
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/minification/
        COMMAND "${Python3_EXECUTABLE}" shader-compressor.py  -o "${PROJECT_SOURCE_DIR}/sfx.h" "${PROJECT_SOURCE_DIR}/sfx.frag" --no-minification
        COMMAND "${Python3_EXECUTABLE}" shader-compressor.py -o "${PROJECT_SOURCE_DIR}/gfx/load.h" "${PROJECT_SOURCE_DIR}/gfx/load.frag" --no-minification
        COMMAND "${Python3_EXECUTABLE}" shader-compressor.py -o "${PROJECT_SOURCE_DIR}/gfx/post.h" "${PROJECT_SOURCE_DIR}/gfx/post.frag" --no-minification
        COMMAND "${Python3_EXECUTABLE}" shader-compressor.py -o "${PROJECT_SOURCE_DIR}/gfx/logo210.h" "${PROJECT_SOURCE_DIR}/gfx/logo210.frag" --no-minification
        COMMAND "${Python3_EXECUTABLE}" shader-compressor.py -o "${PROJECT_SOURCE_DIR}/gfx/decayingfactory.h" "${PROJECT_SOURCE_DIR}/gfx/decayingfactory.frag" --no-minification
        COMMAND "${Python3_EXECUTABLE}" shader-compressor.py -o "${PROJECT_SOURCE_DIR}/gfx/text.h" "${PROJECT_SOURCE_DIR}/gfx/text.frag" --no-minification
    )
endif()

add_custom_target(texture_packing
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/font/
    COMMAND "${Python3_EXECUTABLE}" pack.py
)

add_custom_target(symbolization
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/gfx/
    COMMAND "${Python3_EXECUTABLE}" symbolize.py z10out.frag -o symbols.h
)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:demo /SUBSYSTEM:Windows  /OPT:REF  /OPT:ICF=10 /VERBOSE /NODEFAULTLIB")
endif()

add_executable(fuer-elite fe.c )
add_dependencies(fuer-elite minification)
add_dependencies(fuer-elite texture_packing)
add_dependencies(fuer-elite symbolization)

target_include_directories(fuer-elite SYSTEM PRIVATE "${OPENGL_INCLUDE_DIR}")

target_link_libraries(fuer-elite OpenGL::GL)

if(MSVC)
    target_compile_options(fuer-elite PRIVATE /Gy /O1 /fp:fast /GR- /GS- /MT)

    if (MSVC_VERSION GREATER_EQUAL 1910) # VS2017
        target_link_libraries(fuer-elite Winmm.lib User32.lib ucrt.lib msvcrt.lib vcruntime.lib ucrt.lib)
    else()
        # for debug output: User32.lib ucrt.lib msvcrt.lib
        target_link_libraries(fuer-elite Winmm.lib User32.lib ucrt.lib msvcrt.lib)
    endif()

    find_program(KKRUNCHY_K7 kkrunchy_k7.exe HINTS "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}")
    add_custom_command(TARGET fuer-elite COMMAND "${KKRUNCHY_K7}" --best "$<TARGET_FILE:fuer-elite>" --out "$<TARGET_FILE_DIR:fuer-elite>/fuer-elitec.exe" POST_BUILD)
else()
    find_package(SDL2 REQUIRED)
    target_include_directories(fuer-elite SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(fuer-elite ${SDL2_LIBRARIES})
endif()
