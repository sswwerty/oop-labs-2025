set(SOURCES
    NPC.cpp
    Factories.cpp
    Visitor.cpp
    Observer.cpp
    Dungeon.cpp
)

add_library(balagur_lib ${SOURCES})
target_include_directories(balagur_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(balagur main.cpp)
target_link_libraries(balagur balagur_lib)
