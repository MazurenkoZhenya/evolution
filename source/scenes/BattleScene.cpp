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
    
	//'hud screen' is an autorelease object
	BattleScene::pSelf->pHudScreen = HudScreen::create(BattleScene::pSelf);
    return scene;
}

//---------------------------------------------------------------------------------------------------------------------------------
BattleScene::BattleScene():
pHudScreen(NULL),
MIN_DISTANCE_MOVE(30),
MAX_TIME_MOVE_ENEMY(1.0f),
MAX_TIME_SHOW_ADD_GOLD(3.0f),
m_CurTimeShowGold(0)
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
    
	MemoryProfiler* mProfiler = MemoryProfiler::getInstance();

    
    CCSprite* shading1 = CCSprite::create("textures/scenes/battle/shading.png");
	shading1->setScaleX(SCREEN_WIDTH);
    shading1->setScaleY(SCREEN_HEIGHT);
    shading1->setAnchorPoint(ccp(0, 0));
    this->addChild(shading1, -2);

    background = CCSprite::create("textures/scenes/battle/background.png");
    background->setAnchorPoint(ccp(0, 1));
    background->setPosition(mProfiler->START_POS_ARR);
    this->addChild(background);

	m_AddGold = CCLabelBMFont::create("+0", "fonts/days26black.fnt", 20.0f);
    m_AddGold->setPosition(ccp(mProfiler->START_POS_ARR.x + background->getContentSize().width / 2, mProfiler->START_POS_ARR.y + 40));
	m_AddGold->setColor(ccc3(255, 0, 0));
    this->addChild(m_AddGold, 4564646);
    
	
	char buf[255];
	sprintf(buf, "%d", mProfiler->m_Hero->getGold());

	m_AllGold = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 30.0f);
    m_AllGold->setPosition(ccp(mProfiler->START_POS_ARR.x + background->getContentSize().width / 2, mProfiler->START_POS_ARR.y + 10));
	m_AllGold->setColor(ccc3(255, 0, 0));
    this->addChild(m_AllGold, 4564646);

	this->scheduleUpdate();
    this->setTouchEnabled(true);


    return true;
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::onEnter()
{
    CCLayer::onEnter();
    
    gameModel = new Game();
    gameModel->rand_count();
	gameModel->rand_count();

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
	this->m_AddGold->setOpacity((this->m_CurTimeShowGold * 255) / 3);
    
    if(this->m_CurTimeShowGold - _dt > 0)
        this->m_CurTimeShowGold -= _dt;
    else
        this->m_CurTimeShowGold = 0;

	if(MemoryProfiler::getInstance()->slogeniya > 0)
	{
		MemoryProfiler* mProfiler = MemoryProfiler::getInstance();

		int addGold = mProfiler->m_Hero->generateGold(mProfiler->slogeniya);

		if(addGold > 0)
		{
			char buf[255];
			sprintf(buf, "+%d", addGold);
			this->m_AddGold->setString(buf);
		    this->m_AddGold->setOpacity(255);

			sprintf(buf, "%d", mProfiler->m_Hero->getGold());
			this->m_AllGold->setString(buf);

			this->m_CurTimeShowGold = this->MAX_TIME_SHOW_ADD_GOLD;
		}

		mProfiler->slogeniya = 0;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesBegan(CCSet* _touches, CCEvent* _event)
{
	CCTouch* touch = NULL;
	touch = dynamic_cast<CCTouch*>(_touches->anyObject());
	if(touch)
		touchBegin = touch->getLocation();
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesEnded(CCSet* _touches, CCEvent* _event)
{
    CCTouch* touch = NULL;
	touch = dynamic_cast<CCTouch*>(_touches->anyObject());
	CCPoint checkDuration = ccp(touch->getLocation().x - touchBegin.x, touch->getLocation().y - touchBegin.y);
	if(fabs(checkDuration.x) > fabs(checkDuration.y))
    {
        if(checkDuration.x > 0)
        {
            if(MIN_DISTANCE_MOVE < checkDuration.x)
                durationMove = DM_RIGHT;
            else
                durationMove = DM_NONE;
        }
        else
        {
            if(-MIN_DISTANCE_MOVE > checkDuration.x)
                durationMove = DM_LEFT;
            else
                durationMove = DM_NONE;
        }
    }else
    {
        if(checkDuration.y > 0)
        {
            if(MIN_DISTANCE_MOVE < checkDuration.y)
                durationMove = DM_TOP;
            else
                durationMove = DM_NONE;
        }
        else
        {
            if(-MIN_DISTANCE_MOVE > checkDuration.y)
                durationMove = DM_DOWN;
            else
                durationMove = DM_NONE;
        }
    }
    if(durationMove != DM_NONE)
    {
        gameModel->moveDirection(durationMove);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesMoved(CCSet* _touches, CCEvent* _event)
{
    
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesCancelled(CCSet* _touches, CCEvent* _event)
{
}

//---------------------------------------------------------------------------------------------------------------------------------