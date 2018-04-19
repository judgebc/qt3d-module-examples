cmake_minimum_required(VERSION 3.10)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(render)

find_package(Qt5 COMPONENTS gui 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation widgets REQUIRED)

file(GLOB src src/*.cpp src/*.h)

add_executable(${PROJECT_NAME} ${src} src/resources/resources.qrc)
target_link_libraries(${PROJECT_NAME}
	Qt5::Gui
	Qt5::3DCore
	Qt5::Widgets
	Qt5::3DRender
	Qt5::3DInput
	Qt5::3DLogic
	Qt5::3DExtras
	Qt5::3DAnimation
)

set(QT_DLL_BIN ${Qt5Core_DIR}/../../../bin)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_DLL_BIN}/Qt5Cored.dll ${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_DLL_BIN}/Qt5Guid.dll ${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_DLL_BIN}/Qt5Widgetsd.dll ${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_DLL_BIN}/Qt53DInputd.dll ${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_DLL_BIN}/Qt53DRenderd.dll ${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_DLL_BIN}/Qt53DExtrasd.dll ${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_DLL_BIN}/Qt53DCored.dll ${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_DLL_BIN}/Qt53DLogicd.dll ${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_DLL_BIN}/Qt5Gamepadd.dll ${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_DLL_BIN}/Qt5Networkd.dll ${CMAKE_BINARY_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_DLL_BIN}/Qt5Concurrentd.dll ${CMAKE_BINARY_DIR}/Debug

	COMMENT "Copying Qt Binaries" VERBATIM
)
