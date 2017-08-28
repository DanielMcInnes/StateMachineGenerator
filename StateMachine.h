#pragma once
#include <cassert>
#include <iostream>
#define COUT std::cout << __PRETTY_FUNCTION__ << ": " 

class StateMachine{
public:
    enum State{
        state_empty,
        state_open,
        state_stopped,
        state_playing,
        state_paused
    };

State m_state;
    void Enter_state_empty();
    void Enter_state_open();
    void Enter_state_stopped();
    void Enter_state_playing();
    void Enter_state_paused();

    const char* ToString(const State _state)
    {
        const char* retval;
        switch (_state)
        {
        case state_empty:
            retval = "state_empty";
            break;
        case state_open:
            retval = "state_open";
            break;
        case state_stopped:
            retval = "state_stopped";
            break;
        case state_playing:
            retval = "state_playing";
            break;
        case state_paused:
            retval = "state_paused";
            break;
        default: assert(0); break;
        }
        return retval;
    }

    enum Event{
        event_null,
        event_open_close,
        event_cd_detected,
        event_stop,
        event_play,
        event_pause
    };

    const char* ToString(const Event _event)
    {
        const char* retval;
        switch (_event)
        {
        case event_open_close:
            retval = "event_open_close";
            break;
        case event_cd_detected:
            retval = "event_cd_detected";
            break;
        case event_stop:
            retval = "event_stop";
            break;
        case event_play:
            retval = "event_play";
            break;
        case event_pause:
            retval = "event_pause";
            break;
        default: assert(0); break;
        }
        return retval;
    }

    void SetState(State _state)
    {
        m_state = _state;
        std::cout <<  "state: " << ToString(m_state) << std::endl;
    }
    Event state_empty_handle_event(Event _event)
    {
        switch (_event)
        {
        case event_cd_detected:
            SetState(state_stopped);
            Enter_state_stopped();
            break;
        case event_open_close:
            SetState(state_open);
            Enter_state_open();
            break;
            default: _event = event_null; break;
        }
    }
    Event state_open_handle_event(Event _event)
    {
        switch (_event)
        {
        case event_open_close:
            SetState(state_empty);
            Enter_state_empty();
            break;
            default: _event = event_null; break;
        }
    }
    Event state_paused_handle_event(Event _event)
    {
        switch (_event)
        {
        case event_open_close:
            SetState(state_open);
            Enter_state_open();
            break;
        case event_pause:
            SetState(state_playing);
            Enter_state_playing();
            break;
        case event_stop:
            SetState(state_stopped);
            Enter_state_stopped();
            break;
            default: _event = event_null; break;
        }
    }
    Event state_playing_handle_event(Event _event)
    {
        switch (_event)
        {
        case event_open_close:
            SetState(state_open);
            Enter_state_open();
            break;
        case event_pause:
            SetState(state_paused);
            Enter_state_paused();
            break;
        case event_stop:
            SetState(state_stopped);
            Enter_state_stopped();
            break;
            default: _event = event_null; break;
        }
    }
    Event state_stopped_handle_event(Event _event)
    {
        switch (_event)
        {
        case event_open_close:
            SetState(state_open);
            Enter_state_open();
            break;
        case event_play:
            SetState(state_playing);
            Enter_state_playing();
            break;
        case event_stop:
            SetState(state_stopped);
            Enter_state_stopped();
            break;
            default: _event = event_null; break;
        }
    }

    State HandleEvent(Event _event)
    {
        while (_event != event_null)
        {
            switch(m_state)
            {
            case state_empty:
                _event = state_empty_handle_event(_event);
                break;
            case state_open:
                _event = state_open_handle_event(_event);
                break;
            case state_stopped:
                _event = state_stopped_handle_event(_event);
                break;
            case state_playing:
                _event = state_playing_handle_event(_event);
                break;
            case state_paused:
                _event = state_paused_handle_event(_event);
                break;
            }
        }
    }
};
