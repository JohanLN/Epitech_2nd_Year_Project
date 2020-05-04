//
// Created by johan.lenagard on 6/13/19.
//

#ifndef OOP_INDIE_STUDIO_2018_EVENTBUTTON_HPP
#define OOP_INDIE_STUDIO_2018_EVENTBUTTON_HPP

#include <irrlicht.h>
#include <driverChoice.h>
#include "ACharacter.hpp"
#include "Menu.hpp"
#include "Game.hpp"

struct SAppContext
{
    IrrlichtDevice *device;
    irr::video::IVideoDriver *driver;
    irr::scene::ISceneManager *manager;
    irr::gui::IGUIEnvironment *gui;
    Menu menu;
    Game *game;
};

enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_START_BUTTON = 1,
    GUI_ID_PREGAME_BUTTON = 2,
    GUI_ID_P1_BUTTON = 3,
    GUI_ID_P2_BUTTON = 4,
    GUI_ID_P3_BUTTON = 5,
    GUI_ID_P4_BUTTON = 6,
    GUI_ID_RETURN_NBPLAYER_BUTTON = 7,
    GUI_ID_LTP_BUTTON = 9
};

class EventButton : public IEventReceiver {
public:
    EventButton(SAppContext & context) : Context(context) {
        for (irr::u32 i = 0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

    virtual bool IsKeyDown(int keyCode) const
    {
        return KeyIsDown[keyCode];
    }

    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_KEY_INPUT_EVENT) {
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        }

        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();

            switch(event.GUIEvent.EventType)
            {
                case gui::EGET_BUTTON_CLICKED:
                    switch(id)
                    {
                        case GUI_ID_QUIT_BUTTON: {
                            Context.device->closeDevice();
                            Context.device->drop();
                            exit(0);
                        }

                        case GUI_ID_PREGAME_BUTTON: {
                            Context.game->coreGame(1);
                            exit(100);
                        }

                        case GUI_ID_P1_BUTTON: {
                            Context.game->coreGame(2);
                            exit(200);
                        }

                        case GUI_ID_P2_BUTTON: {
                            Context.game->coreGame(3);
                            exit(0);
                        }

                        case GUI_ID_P3_BUTTON: {
                            Context.game->coreGame(4);
                            exit(0);
                        }

                        case GUI_ID_P4_BUTTON: {
                            Context.game->coreGame(5);
                            exit(0);
                        }

                        case GUI_ID_RETURN_NBPLAYER_BUTTON: {
                            Context.game->coreGame(0);
                            exit(0);
                        }

                        case GUI_ID_LTP_BUTTON: {
                            Context.game->coreGame(8);
                            exit(0);
                        }
                        default:
                            return false;
                    }
                    break;

                default:
                    break;
            }
        }

        return false;
    }
    SAppContext & Context;

private:
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


#endif //OOP_INDIE_STUDIO_2018_EVENTBUTTON_HPP
