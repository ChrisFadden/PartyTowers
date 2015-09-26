include_directories(${partytowers_SOURCE_DIR}/include)

set(MY_SOURCES main.cpp Tower.cpp GameObject.cpp Player.cpp Level.cpp Enemy.cpp Path.cpp Bullet.cpp
TowerBase.cpp MsgStruct.cpp DrawableObject.cpp Cursor.cpp TextureLoader.cpp Soldier.cpp 
Cavalry.cpp Cannon.cpp Rocket.cpp Sound.cpp Text.cpp)

add_executable(partytowers ${MY_SOURCES})
target_link_libraries(partytowers SDL2 SDL2_net SDL2_image SDL2_mixer SDL2_ttf)
