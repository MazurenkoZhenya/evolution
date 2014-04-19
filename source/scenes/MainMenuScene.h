#ifndef __MAIN_MENU_SCENE__
#define __MAIN_MENU_SCENE__

#include "IScene.h"

//---------------------------------------------------------------------------------------------------------------------------------
class MainMenuScene: public IScene
{
public:
    static MainMenuScene*       pSelf;   
    static cocos2d::CCScene*    scene();    
private:
    bool            init();
    void            initMenu();
    
    void            update(float _dt);

    void            onEnter();
    void            onExit();
    
    void            replaceScene(cocos2d::CCScene* _scene);
    
    CREATE_FUNC(MainMenuScene);
    
    MainMenuScene();
    ~MainMenuScene();
    
    
    //touch events
    void            ccTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesEnded(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesMoved(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesCancelled(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);

    
    //main menu callbacks
	//replace to BattleScene
    void            menuCallback1(CCObject* _pSender);
	//replace to CardScene
	void            menuCallback2(CCObject* _pSender);
    //replace to ShopScene
	void			menuCallback3(CCObject* _pSender);
private:
    //to BattleScene button
    cocos2d::CCMenuItemLabel*   menuLabel1;

	//to Cards scene
	cocos2d::CCMenuItemLabel*   menuLabel2;

	//to Shop scene
	cocos2d::CCMenuItemLabel*	menuLabel3;
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__MAIN_MENU_SCENE__
