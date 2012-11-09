#include "NpcOwnedStates.h"
#include <OgreSubEntity.h>


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
  // Say: "I now want to work."

  // Go to workplace
  npc->addLocation(Ogre::Vector3(400.0f,0.0f,400.0f));

  // Set working animation
}


void Work::Execute(BaseNpc* npc)
{
  // Say: "Still ẃant to work."

  // Check for state change
}

void Work::Exit(BaseNpc* npc)
{
  // Say: "I don't want to work anymore."

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
  // Say: "I'm now want social contact and beverages."

  // Go to tavern
  npc->addLocation(Ogre::Vector3(-400.0f,0.0f,400.0f));

  // Set tavern animation
}


void Tavern::Execute(BaseNpc* npc)
{
  // Say: "Still want social contact and beverages."

  // Check for state change
}

void Tavern::Exit(BaseNpc* npc)
{
  // Say: "Do not want social contact and beverages anymore."

  // Destroy at the tavern animation?
}

// ----------------------------------------------------------------------------
Sleep* Sleep::Instance()
{
  static Sleep instance;

  return &instance;
}

void Sleep::Enter(BaseNpc* npc)
{
  // Say: "I'm now sleepy."

  // Go to tavern
  npc->addLocation(Ogre::Vector3(-400.0f,0.0f,-400.0f));

  // Set tavern animation
}


void Sleep::Execute(BaseNpc* npc)
{
  // Say: "Still sleepy."

  // Check for state change
}

void Sleep::Exit(BaseNpc* npc)
{
  // Say: "Time to stop being sleepy."

  // Destroy sleep animation?
}