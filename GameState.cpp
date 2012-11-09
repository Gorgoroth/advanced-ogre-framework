#include "GameState.h"

using namespace Ogre;

GameState::GameState()
{
    m_MoveSpeed                 = 1.0f;
    m_RotateSpeed               = 0.3f;

    m_bLMouseDown       = false;
    m_bRMouseDown       = false;
    m_bQuit             = false;
    m_bSettingsMode     = false;

    m_pDetailsPanel             = 0;
}

void GameState::enter()
{
    AdvancedOgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");

    m_pSceneMgr = AdvancedOgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "GameSceneMgr");

    mRaySceneQuery = m_pSceneMgr->createRayQuery(Ogre::Ray());

    m_pRSQ = m_pSceneMgr->createRayQuery(Ray());

    m_pCamera = m_pSceneMgr->createCamera("GameCamera");
    m_pCamera->setPosition(Vector3(0, 100, 100));
    m_pCamera->lookAt(Vector3(0, 20, 0));
    m_pCamera->setNearClipDistance(5);

    m_pCamera->setAspectRatio(Real(AdvancedOgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(AdvancedOgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

    AdvancedOgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
    m_pCurrentObject = 0;

    buildGUI();
    createScene();
}

bool GameState::pause()
{
    AdvancedOgreFramework::getSingletonPtr()->m_pLog->logMessage("Pausing GameState...");

    return true;
}

void GameState::resume()
{
    AdvancedOgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming GameState...");

    buildGUI();

    AdvancedOgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
    m_bQuit = false;
}

void GameState::exit()
{
    AdvancedOgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");

    m_pSceneMgr->destroyCamera(m_pCamera);
    m_pSceneMgr->destroyQuery(m_pRSQ);
    if(m_pSceneMgr){
        AdvancedOgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
    }
}

void GameState::createScene()
{
    // --- Objects
    m_pNpc01 = new BaseNpc("Blacksmith", m_pSceneMgr, Ogre::Vector3(50.0f,  0.0f,  50.0f));
    //m_pNpc02 = new BaseNpc("Woman", m_pSceneMgr, Ogre::Vector3(-50.0f,  0.0f,  -50.0f));
    //m_pNpc01->addLocation(Ogre::Vector3(-100.0f,0.0f,-100.0f));

    // --- World
    // Light
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7, 0.7, 0.7));

    // Objects
    // Home
    Ogre::Entity* home = m_pSceneMgr->createEntity("Home", "tudorhouse.mesh");
    //home->setCastShadows(true);
    Ogre::SceneNode* homeNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("HomeNode");
    homeNode->attachObject(home);
    homeNode->setPosition(Ogre::Vector3(-400.0f,220.0f,-400.0f));
    homeNode->setScale(0.4f, 0.4f, 0.4f);

    // Work
    Ogre::Entity* work = m_pSceneMgr->createEntity("Work", "tudorhouse.mesh");
    //work->setCastShadows(true);
    Ogre::SceneNode* workNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("WorkNode");
    workNode->attachObject(work);
    workNode->setPosition(Ogre::Vector3(400.0f,220.0f,400.0f));
    workNode->setScale(0.4f, 0.4f, 0.4f);
    workNode->yaw(Ogre::Degree(180));

    // Tavern
    Ogre::Entity* tavern = m_pSceneMgr->createEntity("Tavern", "tudorhouse.mesh");
    //tavern->setCastShadows(true);
    Ogre::SceneNode* tavernNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("TavernNode");
    tavernNode->attachObject(tavern);
    tavernNode->setPosition(Ogre::Vector3(-400.0f,220.0f,400.0f));
    tavernNode->setScale(0.4f, 0.4f, 0.4f);
    tavernNode->yaw(Ogre::Degree(180));


    // Ground
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::Entity* entGround = m_pSceneMgr->createEntity("GroundEntity", "ground");
    m_pSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
    entGround->setMaterialName("Examples/Rockwall");
    entGround->setCastShadows(false);
}

bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        pushAppState(findByName("PauseState"));
        return true;
    }

    if(AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_I))
    {
        if(m_pDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        {
            AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->moveWidgetToTray(m_pDetailsPanel, OgreBites::TL_TOPLEFT, 0);
            m_pDetailsPanel->show();
        }
        else
        {
            AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->removeWidgetFromTray(m_pDetailsPanel);
            m_pDetailsPanel->hide();
        }
    }

    if(m_bSettingsMode && AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_RETURN) ||
        AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_NUMPADENTER))
    {
    }

    if(!m_bSettingsMode || (m_bSettingsMode && !AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_O)))
        AdvancedOgreFramework::getSingletonPtr()->keyPressed(keyEventRef);

    return true;
}

bool GameState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    AdvancedOgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}

bool GameState::mouseMoved(const OIS::MouseEvent &evt)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;

    if(m_bRMouseDown)
    {
        m_pCamera->yaw(Degree(evt.state.X.rel * -0.1f));
        m_pCamera->pitch(Degree(evt.state.Y.rel * -0.1f));
    }

    return true;
}

bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;

    if(id == OIS::MB_Left)
    {
        onLeftPressed(evt);
        m_bLMouseDown = true;
    }
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = true;
    }

    return true;
}

bool GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;

    if(id == OIS::MB_Left)
    {
        m_bLMouseDown = false;
    }
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = false;
    }

    return true;
}

void GameState::onLeftPressed(const OIS::MouseEvent &evt)
{
    Viewport* vp = m_pSceneMgr->getCurrentViewport();

    float x = evt.state.X.abs/float(vp->getActualWidth());
    float z = 0;
    float y = evt.state.Y.abs/float(vp->getActualHeight());

    Ogre::Ray mouseRay = m_pCamera->getCameraToViewportRay(x, y);
    mRaySceneQuery->setRay(mouseRay);

    Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr = result.begin( );

    // Get results, create a node/entity on the position
    if (itr != result.end() && itr->worldFragment) {
        m_pNpc01->addLocation(Ogre::Vector3(-100.0f,0.0f,-100.0f));
        // m_pNpc01->addLocation(itr->worldFragment->singleIntersection);
    }
}

void GameState::moveCamera()
{
    if(AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_LSHIFT))
        m_pCamera->moveRelative(m_TranslateVector);
    m_pCamera->moveRelative(m_TranslateVector / 10);
}

void GameState::getInput()
{
    if(m_bSettingsMode == false)
    {
        if(AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
            m_TranslateVector.x = -m_MoveScale;

        if(AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
            m_TranslateVector.x = m_MoveScale;

        if(AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
            m_TranslateVector.z = -m_MoveScale;

        if(AdvancedOgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
            m_TranslateVector.z = m_MoveScale;
    }
}

void GameState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

    if(m_bQuit == true) {
        popAppState();
        return;
    }

    m_MoveScale = m_MoveSpeed   * timeSinceLastFrame;
    m_RotScale  = m_RotateSpeed * timeSinceLastFrame;

    m_TranslateVector = Vector3::ZERO;

    m_pNpc01->update(timeSinceLastFrame/100);
    //m_pNpc02->update(timeSinceLastFrame/100);

    getInput();
    moveCamera();
}

void GameState::buildGUI()
{
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_TOPLEFT);
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "GameLbl", "Game mode", 250);
    AdvancedOgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();
}
