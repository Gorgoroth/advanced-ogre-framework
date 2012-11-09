#include "PauseState.h"

using namespace Ogre;

PauseState::PauseState()
{
    m_bQuit             = false;
    m_bQuestionActive   = false;
    m_FrameEvent        = Ogre::FrameEvent();
}

void PauseState::enter()
{
    AdvancedOgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering PauseState...");

    m_pSceneMgr = AdvancedOgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "PauseSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("PauseCam");
    m_pCamera->setPosition(Vector3(0, 25, -50));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);

    m_pCamera->setAspectRatio(Real(AdvancedOgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(AdvancedOgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

    AdvancedOgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "BackToGameBtn", "Return to Game", 250);
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "BackToMenuBtn", "Return to Menu", 250);
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ExitBtn", "Exit Game", 250);
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "PauseLbl", "Pause mode", 250);

    m_bQuit = false;

    createScene();
}

void PauseState::createScene()
{
}

void PauseState::exit()
{
    AdvancedOgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving PauseState...");

    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        AdvancedOgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);

    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);
}

bool PauseState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE) && !m_bQuestionActive)
    {
        m_bQuit = true;
        return true;
    }

    AdvancedOgreFramework::getSingletonPtr()->keyPressed(keyEventRef);

    return true;
}

bool PauseState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    AdvancedOgreFramework::getSingletonPtr()->keyReleased(keyEventRef);

    return true;
}

bool PauseState::mouseMoved(const OIS::MouseEvent &evt)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
    return true;
}

bool PauseState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    return true;
}

bool PauseState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    return true;
}

void PauseState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

    if(m_bQuit == true)
    {
        popAppState();
        return;
    }
}

void PauseState::buttonHit(OgreBites::Button *button)
{
    if(button->getName() == "ExitBtn")
    {
        AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->showYesNoDialog("Sure?", "Really leave?");
        m_bQuestionActive = true;
    }
    else if(button->getName() == "BackToGameBtn")
        m_bQuit = true;
    else if(button->getName() == "BackToMenuBtn")
        popAllAndPushAppState(findByName("MenuState"));
}

void PauseState::yesNoDialogClosed(const Ogre::DisplayString& question, bool yesHit)
{
    if(yesHit == true)
        shutdown();
    else
        AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->closeDialog();

    m_bQuestionActive = false;
}

