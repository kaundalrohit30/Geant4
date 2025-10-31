#include "ActionInitialization.hh"



ActionInitialization::ActionInitialization(){

}

ActionInitialization::~ActionInitialization(){

}

void ActionInitialization::BuildForMaster() const{

    //RunAction *runAction = new RunAction();
    //SetUserAction(runAction);

    //EventAction *eventAction = new EventAction();
    //SetUserAction(eventAction);
//
    //SteppingAction *steppingAction = new SteppingAction();
    //SetUserAction(steppingAction);
}

void ActionInitialization::Build() const{

    PrimaryGenerator *generator = new PrimaryGenerator();
    SetUserAction(generator);

    RunAction *runAction = new RunAction();
    SetUserAction(runAction);

    EventAction *eventAction = new EventAction(runAction);
    SetUserAction(eventAction);

    SteppingAction *steppingAction = new SteppingAction(eventAction);
    SetUserAction(steppingAction);
}