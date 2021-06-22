#include "H4SteppingAction.hpp"

//**********************************//
// H4SteppingAction constructor     //
//----------------------------------//
//                                  //
//          Do nothing.             //
//                                  //
//**********************************//
H4SteppingAction::H4SteppingAction (H4EventAction *event_action)
: G4UserSteppingAction(),
m_event_action(event_action) { }

//**********************************//
// H4SteppingAction constructor     //
//----------------------------------//
//                                  //
//          Do nothing.             //
//                                  //
//**********************************//
H4SteppingAction::~H4SteppingAction () { }

//******************************//
//                              //
// Actions before the tracking. //
//                              //
//******************************//
void H4SteppingAction::UserSteppingAction (const G4Step *step) {

  if (
    std::regex_match(
      step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName(),
      std::regex("Inner module \\([0-9]{1,2},[0-9]{1,2}\\) - "
      "[a-z]{4,12} tile: [0-9]{1,2}.{0,}")
    )
  ) {

    std::string volume_name =
    step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
    std::smatch number;
    std::regex reg("[0-9]{1,2}");

    std::vector< int > coordinates;

    while ( std::regex_search(volume_name, number, reg) ) {
      std::string matched_number = number[0].str();

      coordinates.push_back(std::atoi(matched_number.c_str()));

      volume_name = number.suffix().str();
    }

    float energy_deposit = step->GetTotalEnergyDeposit();
    float step_lenght = step->GetStepLength();

    if (
      std::regex_match(
        step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName(),
        std::regex("Inner module \\([0-9]{1,2},[0-9]{1,2}\\) - "
        "scintillator tile: [0-9]{1,2} - row: [0-9]{1,2} - col: [0-9]{1,2}")
      )
    ) {

      m_event_action->AppendXStepScintillator(39 - coordinates[0]);
      m_event_action->AppendYStepScintillator(coordinates[1] - 20);
      m_event_action->AppendZStepScintillator(coordinates[2]);
      m_event_action->AppendrStepScintillator(coordinates[3]);
      m_event_action->AppendcStepScintillator(coordinates[4]);
      m_event_action->AppendEStepScintillator(energy_deposit);
      m_event_action->AppendSLStepScintillator(step_lenght);

    } else if (
      std::regex_match(
        step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName(),
        std::regex("Inner module \\([0-9]{1,2},[0-9]{1,2}\\) - "
        "lead tile: [0-9]{1,2}")
      )
    ) {

      m_event_action->AppendXStepLead(39 - coordinates[0]);
      m_event_action->AppendYStepLead(coordinates[1] - 20);
      m_event_action->AppendZStepLead(coordinates[2]);
      m_event_action->AppendEStepLead(energy_deposit);
      m_event_action->AppendSLStepLead(step_lenght);

    }

  }

}

//
// H4SteppingAction.cpp ends here.
//
