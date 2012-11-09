class NpcBaseState
{
  public:
    virtual ~NpcBaseState() {}

    void virtual Enter(BaseNpc*)=0;
    void virtual Execute(BaseNpc*)=0;
    void virtual Exit(BaseNpc*)=0;
};