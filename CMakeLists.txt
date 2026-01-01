cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME InertRefSys)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
        Core/Src/IMU/IMU_DataPolling.h
        Core/Src/IMU/IMU_DataPolling.c
        Core/Src/IMU/IMU_PreProcessing.h
        Core/Src/IMU/IMU_PreProcessing.c
        Core/Src/Mag/Mag_DataPolling.h
        Core/Src/Mag/Mag_DataPolling.c
        Core/Src/Math/vector.h
        Core/Src/Math/vector.c
        Core/Src/Math/quaternion.h
        Core/Src/Math/quaternion.c
        Core/Src/Baro/Baro_DataPolling.h
        Core/Src/Baro/Baro_DataPolling.c
        Core/Src/GNSS/GNSS_DataPolling.c
        Core/Src/GNSS/GNSS_DataPolling.h
        Core/Src/IRS/IRS.c
        Core/Src/IRS/IRS.h
        Core/Src/DeadReckoning/DeadReckoning.h
        Core/Src/DeadReckoning/DeadReckoning.c
        Core/Src/KarmanFilter/KarmanFilter.h
        Core/Src/KarmanFilter/KarmanFilter.c
        Core/Src/Math/matrix.h
        Core/Src/Math/matrix.c
)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx
)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
        stmems_drivers
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
        ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STMEMS/Inc/lsm6dsv16x_reg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STMEMS/Inc/lis2mdl_reg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STMEMS/Inc/lps22df_reg.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
        ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STMEMS/Inc
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    # Add user defined libraries
)

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
        -u _printf_float
)
