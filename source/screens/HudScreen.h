#ifndef __HUD_SCREEN__
#define __HUD_SCREEN__

#include "IScreen.h"
#include "IScene.h"

//---------------------------------------------------------------------------------------------------------------------------------
class HudScreen: public IScreen
{
public:
    static HudScreen*   create(IScene* _parent);
    
private:
    bool                init();

    void                update(float _dt);

    void                onEnter();
    void                onExit();

    HudScreen();
    ~HudScreen();
        
    //touch events
    void                ccTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void                ccTouchesEnded(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void                ccTouchesMoved(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void                ccTouchesCancelled(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__HUD_SCREEN__
