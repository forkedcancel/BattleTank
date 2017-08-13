cmake_minimum_required (VERSION 2.6)
project (UE4)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/clang")

include("/Users/wrose/dev/unreal/BattleTank/Intermediate/ProjectFiles/IncludeDirectories.cmake")
include("/Users/wrose/dev/unreal/BattleTank/Intermediate/ProjectFiles/Definitions.cmake")
include("/Users/wrose/dev/unreal/BattleTank/Intermediate/ProjectFiles/BattleTankEditor.cmake")

set(MONO_ROOT_PATH "/Applications/UE_4.16/Engine/Binaries/DotNET")
set(BUILD cd "${MONO_ROOT_PATH}")

# Custom target for BattleTankEditor project, Development configuration
add_custom_target(BattleTankEditor-Development ${BUILD} && mono UnrealBuildTool.exe BattleTankEditor Mac Development -project="/Users/wrose/dev/unreal/BattleTank/BattleTank.uproject" -game -progress)
add_custom_target(BattleTankEditor-Development-CLEAN ${BUILD} && mono UnrealBuildTool.exe BattleTankEditor Mac Development -project="/Users/wrose/dev/unreal/BattleTank/BattleTank.uproject" -clean)

add_executable(PleaseIgnoreMe ${BattleTankEditor_FILES})