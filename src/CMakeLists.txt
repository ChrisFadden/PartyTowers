include_directories(${partytowers_SOURCE_DIR}/include)

set(MY_SOURCES main.cpp Tower.cpp GameObject.cpp Player.cpp Level.cpp Enemy.cpp
	TowerBase.cpp)

add_executable(partytowers ${MY_SOURCES})
target_link_libraries(partytowers SDL2 SDL2_net)
