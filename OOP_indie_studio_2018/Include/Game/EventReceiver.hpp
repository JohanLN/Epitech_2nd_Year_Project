//
// Created by johan.lenagard on 6/10/19.
//

#ifndef OOP_INDIE_STUDIO_2018_EVENTRECEIVER_HPP
#define OOP_INDIE_STUDIO_2018_EVENTRECEIVER_HPP


#include <irrlicht.h>

using namespace irr;

class EventReceiver : public IEventReceiver {

public:
    EventReceiver()
    {
        for (irr::u32 i = 0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }
    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return false;
    }
    virtual bool IsKeyDown(int keyCode) const
    {
        return KeyIsDown[keyCode];
    }
private:
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif //OOP_INDIE_STUDIO_2018_EVENTRECEIVER_HPP
