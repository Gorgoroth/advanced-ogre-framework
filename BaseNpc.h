#ifndef BASE_NPC_H
#define BASE_NPC_H

#include "GameState.h"
#include "NpcOwnedStates.h"

class BaseNpc
{
public:
  BaseNpc();
  BaseNpc(Ogre::String name, Ogre::SceneManager* m_pSceneMgr, Ogre::Vector3 start);
  void update(double timeSinceLastFrame);
  virtual void addLocation(Ogre::Vector3 destination);

  void ChangeState(NpcBaseState *pNewState);

protected:
  virtual bool nextLocation(Ogre::SceneNode* m_pNpcNode);

private:
  Ogre::Entity* m_pNPC;
  Ogre::SceneNode* m_pNpcNode;

  bool isMoving;
  Ogre::Real mDistance;                  // The distance the object has left to travel
  Ogre::Vector3 mDirection;              // The direction the object is moving
  Ogre::Vector3 mDestination;            // The destination the object is moving towards
  Ogre::AnimationState *mAnimationState; // The current animation state of the object
  std::deque<Ogre::Vector3> mWalkList;   // The list of points we are walking to
  Ogre::Real mWalkSpeed;                 // The speed at which the object is moving
  Ogre::String mName;
  // String mesh;
  // Vector3 position;
  // Orientation

  NpcBaseState* m_pCurrentState;
};

#endif // BASE_NPC_H
