cmake_minimum_required(VERSION 3.10)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(render)

find_package(Qt5 COMPONENTS
	gui
	3dcore
	3drender
	3dinput
	3dlogic
	3dextras
	3danimation
	widgets
	concurrent
	gamepad
	network
	core
REQUIRED)

file(GLOB src src/*.cpp src/*.h)

add_executable(${PROJECT_NAME} ${src} src/resources/resources.qrc)
target_link_libraries(${PROJECT_NAME}
	Qt5::Gui
	Qt5::Widgets
	Qt5::3DCore
	Qt5::3DRender
	Qt5::3DInput
	Qt5::3DLogic
	Qt5::3DExtras
	Qt5::3DAnimation
	Qt5::Core
)

set(QT_DLL_BIN ${Qt5Core_DIR}/../../../bin)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::3DCore> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::3DRender> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::3DInput> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::3DLogic> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::3DExtras> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::3DAnimation> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Concurrent> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Network> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gamepad> ${CMAKE_BINARY_DIR}/$<CONFIGURATION>

	COMMENT "Copying Qt Binaries" VERBATIM
)
