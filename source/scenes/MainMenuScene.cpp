#include "MainMenuScene.h"
#include "BattleScene.h"
#include "CardScene.h"

using namespace cocos2d;

MainMenuScene* MainMenuScene::pSelf = NULL;

//---------------------------------------------------------------------------------------------------------------------------------
CCScene* MainMenuScene::scene()
{
    //'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    //'layer' is an autorelease object
    MainMenuScene::pSelf = MainMenuScene::create();
    scene->addChild( MainMenuScene::pSelf );

    return scene;
}

//---------------------------------------------------------------------------------------------------------------------------------
MainMenuScene::MainMenuScene():
//main menu
menuLabel1(NULL)
{
}

//---------------------------------------------------------------------------------------------------------------------------------
MainMenuScene::~MainMenuScene()
{   
    MainMenuScene::pSelf = NULL;
}

//---------------------------------------------------------------------------------------------------------------------------------
bool MainMenuScene::init()
{
    //super init first
    if(!CCLayer::init())
        return false;
    
    this->initMenu();
    
    
    this->scheduleUpdate();
    this->setTouchEnabled(true);
    
    
    // add background image
    CCSprite* bg = CCSprite::create("textures/scenes/main/mainmenu_bg.jpg");
    bg->setAnchorPoint(CCPointZero);
    this->addChild(bg, 0);
    //
    
    return true;
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::initMenu()
{
    CCMenu* menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    this->addChild(menu, 1450);
    
    
    //add "battle" button
	CCLabelBMFont* textLabel1 = CCLabelBMFont::create("START GAME", "fonts/days26black.fnt", 100.0f);
    textLabel1->setColor(ccc3(255, 255, 255));
    
    this->menuLabel1 = CCMenuItemLabel::create(textLabel1, this, menu_selector(MainMenuScene::menuCallback1));
    this->menuLabel1->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    this->menuLabel1->setAnchorPoint(ccp(0.5, 0.5));
    this->menuLabel1->setVisible(true);
	 
    menu->addChild(this->menuLabel1);
    //

	CCLabelBMFont* textLabel2 = CCLabelBMFont::create("CARD SCENE", "fonts/days26black.fnt", 100.0f);
    textLabel1->setColor(ccc3(255, 255, 255));
    
    this->menuLabel2 = CCMenuItemLabel::create(textLabel2, this, menu_selector(MainMenuScene::menuCallback2));
    this->menuLabel2->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200);
    this->menuLabel2->setAnchorPoint(ccp(0.5, 0.5));
    this->menuLabel2->setVisible(true);
	 
    menu->addChild(this->menuLabel2);
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::onEnter()
{
    CCLayer::onEnter();
    CCLOG("MainMenuScene::onEnter");
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::onExit()
{
    CCLayer::onExit();
    CCLOG("MainMenuScene::onExit");
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::replaceScene(cocos2d::CCScene* _scene)
{    
    CCDirector::sharedDirector()->replaceScene(_scene);
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::update(float _dt)
{
    
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::ccTouchesBegan(CCSet* _touches, CCEvent* _event)
{
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::ccTouchesEnded(CCSet* _touches, CCEvent* _event)
{
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::ccTouchesMoved(CCSet* _touches, CCEvent* _event)
{
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::ccTouchesCancelled(CCSet* _touches, CCEvent* _event)
{
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::menuCallback1(CCObject* _pSender)
{
    this->replaceScene(BattleScene::scene());
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::menuCallback2(CCObject* _pSender)
{
	this->replaceScene(CardScene::scene());
}
//---------------------------------------------------------------------------------------------------------------------------------