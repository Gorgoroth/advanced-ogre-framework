#ifndef NPC_BASE_STATE_H
#define NPC_BASE_STATE_H

class BaseNpc;

class NpcBaseState
{
  public:
    virtual ~NpcBaseState() {}

    void virtual Enter(BaseNpc*)=0;
    void virtual Execute(BaseNpc*)=0;
    void virtual Exit(BaseNpc*)=0;
};

#endif // NPC_BASE_STATE_H