#include "H4Actions.hpp"

//************************//
// H4Actions constructor  //
//------------------------//
//                        //
//       Do nothing.      //
//                        //
//************************//
H4Actions::H4Actions () : G4VUserActionInitialization() {}

//************************//
//  H4Actions destructor  //
//------------------------//
//                        //
//       Do nothing.      //
//                        //
//************************//
H4Actions::~H4Actions () {}

//********************//
// Build the primary  //
// generator actions. //
//********************//
void H4Actions::Build () const {
  SetUserAction(new H4PrimaryGenerator);

  // Set actions.
  // Create the event action pointer.
  H4EventAction *event_action = new H4EventAction();

  // Event Actions.
  SetUserAction(event_action);

  // Tracking Actions.
  SetUserAction(new H4TrackingAction(event_action));

  // Run Actions.
  SetUserAction(new H4RunAction(event_action));
}

//
// H4Actions.cpp ends here.
//
