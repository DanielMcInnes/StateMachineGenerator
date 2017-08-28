#pragma once
#include <cassert>
#include <iostream>
#define COUT std::cout << __PRETTY_FUNCTION__ << ": "

class StateMachine
{
public:

enum State
{
	state_initial,
	state_empty,
	state_open,
	state_paused,
	state_playing,
	state_stopped
};

void Enter_state_inital();
void Enter_state_empty();
void Enter_state_open();
void Enter_state_paused();
void Enter_state_playing();
void Enter_state_stopped();

State m_state = state_initial;

const char* ToString(const State _state)
{
    const char* retval = 0;

    switch(_state)
    {
        case state_initial:                   
            retval = "state_initial";
            break;

    	case state_empty:            
            retval = "state_empty";
            break;

        case state_open:
            retval = "state_open";
            break;

        case state_paused:
            retval = "state_paused";
            break;

        case state_playing:
            retval = "state_playing";
            break;

        case state_stopped:
            retval = "state_stopped";
            break;

        default:
            assert(0);
            break;
    }
    return retval;
}

enum Event
{
    event_invalid,
    event_null,
    event_open_close,
    event_cd_detected,
    event_stop,
    event_pause,
    event_play,
};

const char* ToString(Event _event)
{
    const char* retval = 0;

    switch (_event)
    {
        case event_invalid: 
            retval = "event_invalid";
            break;
        case event_null: 
            retval = "event_null";
            break;
        case event_open_close: 
            retval = "event_open_close";
            break;
        case event_cd_detected: 
            retval = "event_cd_detected";
            break;
        case event_stop: 
            retval = "event_stop";
            break;
        case event_pause: 
            retval = "event_pause";
            break;
        case event_play: 
            retval = "event_play";
            break;
        default:
            assert(0);
            break;
    }
}

void SetState(State _state)
{
    m_state = _state;
    std::cout << "state: " << ToString(m_state) << std::endl; 
}

Event Initial(Event _event)
{
    switch (_event)
    {
        case event_invalid:
            SetState(state_empty);
            break;
        case event_null:
            SetState(state_empty);
            break;
        case event_open_close:
            SetState(state_empty);
            break;
        case event_cd_detected:
            SetState(state_empty);
            break;
        case event_stop:
            SetState(state_empty);
            break;
        case event_pause:
            SetState(state_empty);
            break;
        case event_play:
            SetState(state_empty);
            break;

    }
    return event_null;
}

Event Empty(Event _event)
{
    switch (_event)
    {
        case event_invalid:
            SetState(state_empty);
            break;
        case event_null:
            SetState(state_empty);
            break;
        case event_open_close:
            SetState(state_open);
            break;
        case event_cd_detected:
            SetState(state_stopped);
            break;
        case event_stop:
            SetState(state_empty);
            break;
        case event_pause:
            SetState(state_empty);
            break;
        case event_play:
            SetState(state_empty);
            break;

    }
    return event_null;
}

Event Open(Event _event)
{
    switch (_event)
    {
        case event_invalid:
            SetState(state_empty);
            break;
        case event_null:
            SetState(state_empty);
            break;
        case event_open_close:
            SetState(state_empty);
            break;
        case event_cd_detected:
            SetState(state_empty);
            break;
        case event_stop:
            SetState(state_empty);
            break;
        case event_pause:
            SetState(state_empty);
            break;
        case event_play:
            SetState(state_empty);
            break;

    }
    return event_null;
}

Event Paused(Event _event)
{
    switch (_event)
    {
        case event_invalid:
            SetState(state_empty);
            break;
        case event_null:
            SetState(state_empty);
            break;
        case event_open_close:
            SetState(state_open);
            break;
        case event_cd_detected:
            SetState(state_empty);
            break;
        case event_stop:
            SetState(state_stopped);
            break;
        case event_pause:
            SetState(state_playing);
            break;
        case event_play:
            SetState(state_empty);
            break;

    }
    return event_null;
}

Event Playing(Event _event)
{
    switch (_event)
    {
        case event_invalid:
            SetState(state_empty);
            break;
        case event_null:
            SetState(state_empty);
            break;
        case event_open_close:
            SetState(state_open);
            break;
        case event_cd_detected:
            SetState(state_empty);
            break;
        case event_stop:
            SetState(state_stopped);
            break;
        case event_pause:
            SetState(state_paused);
            break;
        case event_play:
            SetState(state_empty);
            break;

    }
    return event_null;
}

Event Stopped(Event _event)
{
    switch (_event)
    {
        case event_invalid:
            SetState(state_empty);
            break;
        case event_null:
            SetState(state_empty);
            break;
        case event_open_close:
            SetState(state_open);
            break;
        case event_cd_detected:
            SetState(state_stopped);
            break;
        case event_stop:
            SetState(state_stopped);
            break;
        case event_pause:
            SetState(state_empty);
            break;
        case event_play:
            SetState(state_playing);
            break;

    }
    return event_null;
}

State HandleEvent(Event _event)
{
    COUT << ToString(_event) << std::endl;
    while (_event != event_null)
    {
    	switch (m_state)
	    {
	    case state_initial:                   
                _event = Initial(_event);
                break;

    	    case state_empty:            
                _event = Empty(_event);
                break;

            case state_open:
                _event = Open(_event);
                break;

            case state_paused:
                _event = Paused(_event);
                break;

            case state_playing:
                _event = Playing(_event);
                break;

            case state_stopped:
                _event = Stopped(_event);
                break;
        }
    }
}

};
