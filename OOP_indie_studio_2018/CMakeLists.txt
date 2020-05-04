cmake_minimum_required(VERSION 3.13)
project(OOP_indie_studio_2018)

set(CMAKE_CXX_STANDARD 14)

include_directories(Include
                    Include/Character
                    Include/Exception
                    Include/Game
                    Include/Item
                    Include/Map
					Include/Menu
                    Library/Irrlicht/Include
                    Library/Irrklang/Include)

set(    SOURCE_FILES
		Source/Character/RandomPlayer.cpp
		Source/Item/Bomb.cpp
		Source/Item/AItem.cpp
		Source/Item/Potion.cpp
		Source/Item/itemFactory.cpp
		Source/Character/Adc.cpp
		Source/Character/Rapido.cpp
		Source/Character/Tank.cpp
		Source/Main.cpp
		Source/Map/Map.cpp
		Include/Exception/Error.cpp
		Source/Game/Game.cpp
		Source/Menu/Menu.cpp
		Source/Character/ACharacter.cpp
        )

if(UNIX)
    set(IRRKLANG_LIBRARY libIrrKlang.so)
    link_directories(./Library/Irrklang/Linux)

    set(IRRLICHT_LIBRARY
            -L./Library/Irrlicht/Linux
            -lIrrlicht
            -lIrrKlang
            -lGL
            -lXext
            -lX11
            -lXxf86vm
            )

    add_executable(
            bomberman
            ${SOURCE_FILES}
    )
	target_link_libraries(
        bomberman
        ${IRRLICHT_LIBRARY}
	)
elseif (WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Release")
	add_library(Irrlicht STATIC IMPORTED)
	add_library(Irrklang STATIC IMPORTED)
	set_property(TARGET Irrlicht PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Library/Irrlicht/Windows/Irrlicht.lib)
	set_property(TARGET Irrklang PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Library/Irrklang/Windows/irrKlang.lib)
	    add_executable(
            bomberman
            ${SOURCE_FILES}
    )
	target_link_libraries(
		bomberman
        Irrlicht
		Irrklang
)
endif(UNIX)
