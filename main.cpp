#include "StateMachine.h"


using namespace std;


int main ()
{
    StateMachine state_machine(StateMachine::state_empty);   
/*
    // needed to start the highest-level SM. This will call on_entry and mark the start of the SM
    p.start(); 
    // go to Open, call on_exit on Empty, then action, then on_entry on Open
    p.process_event(open_close()); pstate(p);
    p.process_event(open_close()); pstate(p);
    // will be rejected, wrong disk type
    p.process_event(
    cd_detected("louie, louie",DISK_DVD)); //pstate(p);
    p.process_event(
    cd_detected("louie, louie",DISK_CD)); //pstate(p);
		
    p.process_event(play());

    // at this point, Play is active      
    p.process_event(pause()); pstate(p);
    // go back to Playing
    p.process_event(end_pause());  pstate(p);
    p.process_event(pause()); pstate(p);
    p.process_event(stop());  pstate(p);
    // event leading to the same state
    // no action method called as it is not present in the transition table
    p.process_event(stop());  pstate(p);
    //std::cout << "stop fsm" << std::endl;
    p.stop();
*/
    state_machine.HandleEvent(StateMachine::event_open_close);
    state_machine.HandleEvent(StateMachine::event_open_close);
    state_machine.HandleEvent(StateMachine::event_cd_detected);
    state_machine.HandleEvent(StateMachine::event_cd_detected);
    state_machine.HandleEvent(StateMachine::event_play);
    state_machine.HandleEvent(StateMachine::event_pause);
    state_machine.HandleEvent(StateMachine::event_pause);
    state_machine.HandleEvent(StateMachine::event_stop);
    state_machine.HandleEvent(StateMachine::event_stop);



	return 0;
}

