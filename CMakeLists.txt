#!TODO!: generate c++17 VS projects
cmake_minimum_required(VERSION 3.10)
project(Blank_Sail)

set(CMAKE_CXX_STANDARD 17) #keeping this option for other compilers but for MSVC it does not work
set(CMAKE_CXX_STANDARD_REQUIRED ON)




#Add an option for building with 64 or 32 bit on Windows
if(MSVC)
    #Include Directories
    set(SDL2_INCLUDE_DIRS "C:/libs/SDL2-2.28.1")
#    set(SDL2_IMG_INCLUDE_DIR "C:/libs/SDL2_image-2.0.5")
#    set(SPDLOG_INCLUDE_DIR "C:/libs/spdlog/include")
#    set(IMGUI_DIR "C:/libs/imgui")

    

    if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8") #checks x64
        set(CMAKE_GENERATOR_PLATFORM x64)
        #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17") #doesnt work for MSVC
        # Specify the path to the SDL2 manually
        set(SDL2_LIB ${SDL2_INCLUDE_DIRS}/lib/x64/SDL2.lib)
        set(SDL2MAIN_LIB ${SDL2_INCLUDE_DIRS}/lib/x64/SDL2main.lib)
        set(SDL2_DLL ${SDL2_INCLUDE_DIRS}/lib/x64/SDL2.dll)
        #set(SDL2_IMG_LIB ${SDL2_IMG_INCLUDE_DIR}/lib/x64/SDL2_image.lib)
        #set(SDL2_IMG_DLL ${SDL2_IMG_INCLUDE_DIR}/lib/x64/SDL2_image.dll)
        #set(SPDLOG_LIB "C:/libs/spdlog/bin/x64/spdlog.lib")
        
        #Extra SDL2_image .dlls
        #set(SDL2_IMG_zlib ${SDL2_IMG_INCLUDE_DIR}/lib/x64/zlib1.dll)
        #set(SDL2_IMG_libpng ${SDL2_IMG_INCLUDE_DIR}/lib/x64/libpng16-16.dll)

    elseif("${CMAKE_SIZEOF_VOID_P}" EQUAL "4") #checks x86
        set(CMAKE_GENERATOR_PLATFORM Win32)
        set(SDL2_LIB "C:/libs/SDL2-2.26.4/lib/x86/SDL2.lib")
        set(SDL2MAIN_LIB "C:/libs/SDL2-2.26.4/lib/x86/SDL2main.lib")
        #set(SDL2_DLL "C:/libs/SDL2-2.26.4/lib/x86/SDL2.dll")
        #set(SDL2_IMG_LIB "C:/libs/SDL2_image-2.6.3/lib/x86/SDL2_image.lib")
        #set(SDL2_IMG_DLL "C:/libs/SDL2_image-2.6.3/lib/x86/SDL2_image.dll")
    endif()
endif()
# Check if the compiler is MSVC
if(MSVC)
    # Set compiler flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Blank_Sail)
    #add_definitions(-D_WIN32_WINNT=0x600) #preprocessor for requiring at least Vista
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -I/usr/include/SDL2")
endif()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED True)


#Only necessary when the libraries are in some "known" place, like on linux
# find_library(SDL2_LIB SDL2 ${SDL2_LIBRARIES})
# find_library(SDL2MAIN_LIB SDL2main ${SDL2_LIBRARIES})

#WARNING: This will not find subdirectories inside of src/
# Use GLOB_RECURSE for that
file(GLOB SOURCES 
        "src/*.cpp"
        "src/*.h"
        # ${IMGUI_DIR}/*.cpp
        # ${IMGUI_DIR}/*.h
        #${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
        #${IMGUI_DIR}/backends/imgui_impl_sdl2.h
        #${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp
        #${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.h
)

add_executable(Blank_Sail ${SOURCES})

#add_executable(MyProject src/main.cpp)

# Link SDL2,SDL2_image, spdlog, e.t.c
include_directories(${SDL2_INCLUDE_DIRS}/include)
target_link_libraries(Blank_Sail ${SDL2_LIB} ${SDL2MAIN_LIB})
target_compile_features(Blank_Sail PUBLIC cxx_std_17) #Works for MSVC


if(MSVC)
    # Copy SDL2.dll to the output directory
    add_custom_command(TARGET Blank_Sail POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                        ${SDL2_DLL}
                        # ${SDL2_IMG_DLL}
                        # ${SDL2_IMG_zlib}
                        # ${SDL2_IMG_libpng}
                        $<TARGET_FILE_DIR:Blank_Sail>)
endif()