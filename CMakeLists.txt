cmake_minimum_required(VERSION 3.10)

project(render)

find_package(Qt5 COMPONENTS gui 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation widgets REQUIRED)

file(GLOB src src/*.cpp src/*.h)

add_executable(${PROJECT_NAME} ${src})
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
