#ifndef NPC_OWNED_STATES_H
#define NPC_OWNED_STATES_H

#include "NpcBaseState.h"

class Idle : public NpcBaseState
{
private:
  Idle() {};
public:
  static Idle* Instance();

  void virtual Enter(BaseNpc* npc);
  void virtual Execute(BaseNpc* npc);
  void virtual Exit(BaseNpc* npc);
};

class Work : public NpcBaseState
{
private:
  Work() {};
public:
  static Work* Instance();

  void virtual Enter(BaseNpc* npc);
  void virtual Execute(BaseNpc* npc);
  void virtual Exit(BaseNpc* npc);
};

class Tavern : public NpcBaseState
{
private:
  Tavern() {};
public:
  static Tavern* Instance();

  void virtual Enter(BaseNpc* npc);
  void virtual Execute(BaseNpc* npc);
  void virtual Exit(BaseNpc* npc);
};

class Sleep : public NpcBaseState
{
private:
  Sleep() {};
public:
  static Sleep* Instance();

  void virtual Enter(BaseNpc* npc);
  void virtual Execute(BaseNpc* npc);
  void virtual Exit(BaseNpc* npc);
};

#endif // NPC_OWNED_STATES_H