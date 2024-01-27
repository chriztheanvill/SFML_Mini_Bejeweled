cmake_minimum_required(VERSION 3.27)
project(Mini_Bejeweled)

set(CMAKE_CXX_STANDARD 23)

# # Debug flags.
set(CMAKE_BUILD_TYPE Debug)

# set(CMAKE_BUILD_TYPE Release)

# # Check compiler
# # https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# find_package(SDL2 REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(Mini_Bejeweled main.cpp)

target_link_libraries(
        ${PROJECT_NAME} PUBLIC

        # # Options
        # project_options
        # project_warnings
        #
        # # Pkgs
        fmt::fmt
        nlohmann_json::nlohmann_json

        # range-v3::range-v3

        # CONAN_PKG::imgui-sfml
        # CONAN_PKG::sdl2
        # # MY LIBRARIES

        # Component
        # Engine

        # ####################################
        # # Conan v1
        # CONAN_PKG::docopt.cpp
        # CONAN_PKG::fmt
        # CONAN_PKG::spdlog
        # CONAN_PKG::range-v3

        # CONAN_PKG::glew # OpenGL
        # CONAN_PKG::glad # OpenGL
        # CONAN_PKG::nlohmann_json
        #
        #        SDL2
        #        SDL2_image
        #        SDL2_net
        #        SDL2_mixer
        #        SDL2_ttf
        #        SDL2_gfx
        ${SFML_LIBRARIES}
        ${SFML_DEPENDENCIES}
        sfml-system
        sfml-window
        sfml-graphics
        sfml-network
        sfml-audio
)

target_compile_features(
        ${PROJECT_NAME} PRIVATE

        # LAMBDA FEATURES
        cxx_lambda_init_captures

        # C++17 ENABLED
        # cxx_std_17
        # C++20 ENABLED
        cxx_std_20

        # C++23 ENABLED
        #        cxx_std_23
)