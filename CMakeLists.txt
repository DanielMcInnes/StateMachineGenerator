cmake_minimum_required(VERSION 3.7.2)
project(GenerateStateMachine)

set (GSM_SOURCES GenerateStateMachine.cpp)
set (EXAMPLE_SOURCES StateMachine.cpp StateMachine.h ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(GenerateStateMachine ${GSM_SOURCES})

add_custom_command(OUTPUT ${EXAMPLE_SOURCES}
    COMMAND GenerateStateMachine -infile ${CMAKE_CURRENT_SOURCE_DIR}/ExampleStateMachine.dot -classname StateMachine
)

#install(FILES ExampleStateMachine.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/build)
add_custom_target(example_sources DEPENDS ${GSM_SOURCES} ${EXAMPLE_SOURCES})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(example ${EXAMPLE_SOURCES})

