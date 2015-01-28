#ifndef button_events_h
#define button_events_h

#include "window.h"

#include <string>

class Button_Events{
public:

    //Returns true if the button event opened a new window on top of previous ones.
    //Returns false otherwise.
    bool handle_button_event(std::string button_event,Window* parent_window=0);

    //Returns true if the passed button event was handled
    //Returns false if the passed button event was not handled
    bool handle_button_event_game(std::string button_event,Window* parent_window,bool& window_opened_on_top);
};

#endif