#include "DemoApp.h"

#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"

DemoApp::DemoApp()
{
        m_pAppStateManager = 0;
}

DemoApp::~DemoApp()
{
    delete m_pAppStateManager;
    delete AdvancedOgreFramework::getSingletonPtr();
}

void DemoApp::startDemo()
{
    new AdvancedOgreFramework();
    if(!AdvancedOgreFramework::getSingletonPtr()->initOgre("AdvancedAdvancedOgreFramework", 0, 0))
            return;

    AdvancedOgreFramework::getSingletonPtr()->m_pLog->logMessage("Demo initialized!");

    m_pAppStateManager = new AppStateManager();

    MenuState::create(m_pAppStateManager, "MenuState");
    GameState::create(m_pAppStateManager, "GameState");
    PauseState::create(m_pAppStateManager, "PauseState");

    m_pAppStateManager->start(m_pAppStateManager->findByName("MenuState"));
}
