#ifndef OGRE_DEMO_H
#define OGRE_DEMO_H

#include "AdvancedOgreFramework.h"
#include "AppStateManager.h"

class DemoApp
{
public:
  DemoApp();
  ~DemoApp();

  void startDemo();

private:
  AppStateManager*  m_pAppStateManager;
};

#endif

