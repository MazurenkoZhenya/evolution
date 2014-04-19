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
    void            menuCallback1(CCObject* _pSender);
    
private:
    //main menu
    cocos2d::CCMenuItemLabel*   menuLabel1;
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__MAIN_MENU_SCENE__
