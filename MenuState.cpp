#include "MenuState.h"

using namespace Ogre;

MenuState::MenuState()
{
    m_bQuit         = false;
    m_FrameEvent    = Ogre::FrameEvent();
}

void MenuState::enter()
{
    AdvancedOgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering MenuState...");

    m_pSceneMgr = AdvancedOgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "MenuSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("MenuCam");
    m_pCamera->setPosition(Vector3(0, 25, -50));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);

    m_pCamera->setAspectRatio(Real(AdvancedOgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(AdvancedOgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

    AdvancedOgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "EnterBtn", "Enter GameState", 250);
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ExitBtn", "Exit AdvancedAdvancedOgreFramework", 250);
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "MenuLbl", "Menu mode", 250);

    createScene();
}

void MenuState::createScene()
{
}

void MenuState::exit()
{
    AdvancedOgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving MenuState...");

    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        AdvancedOgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);

    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);
}

bool MenuState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        m_bQuit = true;
        return true;
    }

    AdvancedOgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}

bool MenuState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    AdvancedOgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
    return true;
}

bool MenuState::mouseMoved(const OIS::MouseEvent &evt)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
    return true;
}

bool MenuState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    return true;
}

bool MenuState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    return true;
}

void MenuState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

    if(m_bQuit == true)
    {
        shutdown();
        return;
    }
}

void MenuState::buttonHit(OgreBites::Button *button)
{
    if(button->getName() == "ExitBtn")
        m_bQuit = true;
    else if(button->getName() == "EnterBtn")
        changeAppState(findByName("GameState"));
}