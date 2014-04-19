#include "BattleScene.h"
#include "Game.h"

using namespace cocos2d;


BattleScene* BattleScene::pSelf = NULL;

//---------------------------------------------------------------------------------------------------------------------------------
CCScene* BattleScene::scene()
{
    //'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    //'layer' is an autorelease object
    BattleScene::pSelf = BattleScene::create();
    scene->addChild(BattleScene::pSelf);
    
        //'debug draw screen' is an autorelease object
        //BattleScene::pSelf->pDebugScreen = DebugDrawScreen::create();
        //pSelf->addChild( BattleScene::pSelf->pDebugScreen );
    
        //'hud screen' is an autorelease object
        BattleScene::pSelf->pHudScreen = HudScreen::create(BattleScene::pSelf);
    
    //scene->setRotation(90);
    return scene;
}

//---------------------------------------------------------------------------------------------------------------------------------
BattleScene::BattleScene():
pHudScreen(NULL),
START_POS_ARR(ccp(225, 650)),
MIN_DISTANCE_MOVE(30),
MAX_TIME_MOVE_ENEMY(1.0f)
{
    
}

//---------------------------------------------------------------------------------------------------------------------------------
BattleScene::~BattleScene()
{
    BattleScene::pSelf = NULL;
}

//---------------------------------------------------------------------------------------------------------------------------------
bool BattleScene::init()
{
    //super init first
    if(!CCLayer::init())
        return false;
    
    this->scheduleUpdate();
    this->setTouchEnabled(true);
    CCSprite* shading1 = CCSprite::create("textures/scenes/battle/shading_team_one.png");
    shading1->setScaleX(1024);
    shading1->setScaleY(768);
    shading1->setAnchorPoint(ccp(0, 0));
    this->addChild(shading1, -2);
    
    shading2 = CCSprite::create("textures/scenes/battle/shading_team_two.png");
    shading2->setScaleX(1024);
    shading2->setScaleY(768);
    shading2->setAnchorPoint(ccp(0, 0));
    shading2->setVisible(false);
    this->addChild(shading2, -1);
    background = CCSprite::create("textures/scenes/battle/background.png");
    background->setAnchorPoint(ccp(0, 1));
    background->setPosition(START_POS_ARR);
    
    
    this->addChild(background);
    /*
    SoundManager::sharedInstance()->playMusic("sounds/sound", true);
    SoundManager::sharedInstance()->playSound("sounds/test", true);
    */
    
    return true;
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::onEnter()
{
    this->setScale(2.2);
    CCLayer::onEnter();
    
    gameModel = new Game();
    gameModel->rand_count();
	gameModel->rand_count();

    srand(time(NULL));
    
    CCLOG("BattleScene::onEnter");
    
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::onExit()
{
    CCLayer::onExit();
    
    CCLOG("BattleScene::onExit");
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::replaceScene(cocos2d::CCScene* _scene)
{    
    CCDirector::sharedDirector()->replaceScene(_scene);
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::update(float _dt)
{
    
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesBegan(CCSet* _touches, CCEvent* _event)
{
    CCTouch* touch = NULL;
    
    CCSetIterator it;
    for (it = _touches->begin(); it != _touches->end(); ++it)
    {
        if (!(*it))
            break;
        
        touch = (CCTouch*)(*it);
        touchBegin = touch->getLocation();
        break;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesEnded(CCSet* _touches, CCEvent* _event)
{
    CCTouch* touch = NULL;
    
    CCSetIterator it;
    for (it = _touches->begin(); it != _touches->end(); ++it)
    {
        if (!(*it))
            break;
        
        touch = (CCTouch*)(*it);
        
        CCPoint checkDuration = ccp(touch->getLocation().x - touchBegin.x, touch->getLocation().y - touchBegin.y);
        
        if(fabs(checkDuration.x) > fabs(checkDuration.y))
        {
            if(checkDuration.x > 0)
            {
                if(MIN_DISTANCE_MOVE < checkDuration.x)
                    durationMove = DM_TOP;
                else
                    durationMove = DM_NONE;
            }
            else
            {
                if(-MIN_DISTANCE_MOVE > checkDuration.x)
                    durationMove = DM_DOWN;
                else
                    durationMove = DM_NONE;
            }
        }else
        {
            if(checkDuration.y > 0)
            {
                if(MIN_DISTANCE_MOVE < checkDuration.y)
                    durationMove = DM_LEFT;
                else
                    durationMove = DM_NONE;
            }
            else
            {
                if(-MIN_DISTANCE_MOVE > checkDuration.y)
                    durationMove = DM_RIGHT;
                else
                    durationMove = DM_NONE;
            }
        }
        if(durationMove != DM_NONE)
        {
            gameModel->moveDirection(durationMove);
            shading2->setVisible(false);
        }
        
        break;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesMoved(CCSet* _touches, CCEvent* _event)
{
    CCTouch* touch = NULL;
    
    CCSetIterator it;
    for (it = _touches->begin(); it != _touches->end(); ++it)
    {
        if (!(*it))
            break;
        
        touch = (CCTouch*)(*it);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesCancelled(CCSet* _touches, CCEvent* _event)
{
}

//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------