cmake_minimum_required(VERSION 3.0)

project(oslearn
	VERSION 23.1.10.1
	LANGUAGES C CXX 
	DESCRIPTION "树莓派4B实验"
)

# 禁止直接在源码目录编译, 要放在 project指令之后
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(FATAL_ERROR "You cannot build in a source directory (or any directory with a  CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# 输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

subdirs(base)

foreach(_target
  01_Dule_color_LED
  02_Rgb_Led
  04_relay
  05_laser
  06_Button
  07_tilt_switch
  08_vibration_switch
  09_active_buzzer
  09_passive_buzzer
  10_reed_switch)

  add_executable(${_target}
    ${_target}.cpp)
  target_link_libraries(${_target}
    base )
endforeach()
