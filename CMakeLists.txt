cmake_minimum_required(VERSION 3.0)

project(
	predator_and_prey_qt
	LANGUAGES CXX
)

# Dependencies {{{

# Qt5 {{{

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets CONFIG REQUIRED)

# }}}

# }}}

# Definitions {{{

set(
	${PROJECT_NAME}_src
	./src/predator_and_prey.cpp
	./src/main.cpp
)

add_executable(
	${PROJECT_NAME}
	${${PROJECT_NAME}_src}
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
	Qt5::Widgets
)

# }}}

# Installation {{{

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin COMPONENT Runtime
)

# }}}
