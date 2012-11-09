#include "NpcOwnedStates.h"


// ----------------------------------------------------------------------------
Idle* Idle::Instance()
{
  static Idle instance;

  return &instance;
}

void Idle::Enter(BaseNpc* npc)
{
  // Say: "I'm now idle."

  // Set idle animation
}


void Idle::Execute(BaseNpc* npc)
{
  // Say: "Still idle doing nothing."

  // Check for state change
}

void Idle::Exit(BaseNpc* npc)
{
  // Say: "Time to stop being idle."

  // Destroy idle animation?
}

// ----------------------------------------------------------------------------
Work* Work::Instance()
{
  static Work instance;

  return &instance;
}

void Work::Enter(BaseNpc* npc)
{
  // Say: "I'm now working."

  // Set working animation
}


void Work::Execute(BaseNpc* npc)
{
  // Say: "Still working."

  // Check for state change
}

void Work::Exit(BaseNpc* npc)
{
  // Say: "Time to stop working."

  // Destroy working animation?
}

// ----------------------------------------------------------------------------
Tavern* Tavern::Instance()
{
  static Tavern instance;

  return &instance;
}

void Tavern::Enter(BaseNpc* npc)
{
  // Say: "I'm now at the tavern."

  // Set tavern animation
}


void Tavern::Execute(BaseNpc* npc)
{
  // Say: "Still at the tavern."

  // Check for state change
}

void Tavern::Exit(BaseNpc* npc)
{
  // Say: "Time to leave the tavern."

  // Destroy at the tavern animation?
}