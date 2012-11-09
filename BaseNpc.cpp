#include "BaseNpc.h"

BaseNpc::BaseNpc()
{
}

BaseNpc::BaseNpc(Ogre::String name, Ogre::SceneManager* m_pSceneMgr, Ogre::Vector3 start)
{
  // Create renderable
  m_pNPC = m_pSceneMgr->createEntity(name, "robot.mesh");
  //m_pNPC->setCastShadows(true);
  m_pNpcNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(name + "Node");
  m_pNpcNode->attachObject(m_pNPC);
  m_pNpcNode->setPosition(start);

  m_pCurrentState = Idle::Instance();

  // Show name
  // Ogre::MovableText* msg = new Ogre::MovableText("TXT_001", "this is the caption");
  // msg->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE); // Center horizontally and display above the node
  // // msg->setAdditionalHeight( 2.0f ); //msg->setAdditionalHeight( ei.getRadius() ) // apparently not needed from 1.7
  // m_pNpcNode->attachObject(msg);

  // Create the walking list
  mWalkList.push_back(Ogre::Vector3(400.0f,  0.0f,  0.0f ));
  // mWalkList.push_back(Ogre::Vector3(400.0f,  0.0f, -200.0f));
  // mWalkList.push_back(Ogre::Vector3(0.0f,  0.0f, -200.0f));
  // mWalkList.push_back(Ogre::Vector3(0.0f,  0.0f, 0.0f));
  // mWalkList.push_back(Ogre::Vector3(400.0f,  0.0f, 400.0f));

  // Set idle animation
  mAnimationState = m_pNPC->getAnimationState("Idle");
  mAnimationState->setLoop(true);
  mAnimationState->setEnabled(true);

  // Set default values for variables
  mWalkSpeed = 35.0f;
  mDirection = Ogre::Vector3::ZERO;
  isMoving = false;
  mName = name;
}

void BaseNpc::update(double timeSinceLastFrame)
{
  mAnimationState->addTime(timeSinceLastFrame);

  if (m_pCurrentState) {
    m_pCurrentState->Execute(this);
  }

  if (isMoving == false) {
    if (nextLocation(m_pNpcNode)) {
      // Set walking animation
      mAnimationState = m_pNPC->getAnimationState("Walk");
      mAnimationState->setLoop(true);
      mAnimationState->setEnabled(true);
      isMoving = true;
    } else {
      // Not moving and no locations in list
    }
  } else {
    Ogre::Real move = mWalkSpeed * timeSinceLastFrame;
    mDistance -= move;
    if (mDistance <= 0.0f) {
      m_pNpcNode->setPosition(mDestination);
      mDirection = Ogre::Vector3::ZERO;
      // Set animation based on if the robot has another point to walk to.
      if (! nextLocation(m_pNpcNode)) {
          // Set Idle animation
          mAnimationState = m_pNPC->getAnimationState("Idle");
          mAnimationState->setLoop(true);
          mAnimationState->setEnabled(true);
      } else {
        Ogre::Vector3 src = m_pNpcNode->getOrientation() * Ogre::Vector3::UNIT_X;
        if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) {
          m_pNpcNode->yaw(Ogre::Degree(180));
        } else {
          Ogre::Quaternion quat = src.getRotationTo(mDirection);
          m_pNpcNode->rotate(quat);
        }
      }
    } else {
      m_pNpcNode->translate(mDirection * move);
    }
  }
}

void BaseNpc::ChangeState(NpcBaseState *pNewState)
{
   assert(m_pCurrentState && pNewState);

   m_pCurrentState->Exit(this);
   m_pCurrentState = pNewState;
   m_pCurrentState->Enter(this);
}

void BaseNpc::addLocation(Ogre::Vector3 destination)
{
  mWalkList.push_back(destination);
}

bool BaseNpc::nextLocation(Ogre::SceneNode* m_pNpcNode)
{
  if (mWalkList.empty()) {
    return false;
  }

  mDestination = mWalkList.front();  // this gets the front of the deque
  mWalkList.pop_front();             // this removes the front of the deque

  mDirection = mDestination - m_pNpcNode->getPosition();
  mDistance = mDirection.normalise();
}
