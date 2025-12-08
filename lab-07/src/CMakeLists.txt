set(SOURCES
    NPC.cpp
    Factories.cpp
    Visitor.cpp
    Dungeon.cpp
)

add_library(lab07_lib ${SOURCES})
target_include_directories(lab07_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(lab07 main.cpp)
target_link_libraries(lab07 lab07_lib)

