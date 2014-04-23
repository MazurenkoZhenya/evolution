#ifndef __TEST_SCENE__
#define __TEST_SCENE__

#include "IScene.h"
//screens
#include "HudScreen.h"
#include "common/MemoryProfiler.h"
class Game;

using namespace cocos2d;

//---------------------------------------------------------------------------------------------------------------------------------
class BattleScene: public IScene
{
public:
    static BattleScene*         pSelf;
    static cocos2d::CCScene*    scene();
    
    HudScreen*                  getHudScreen() const { return pHudScreen; }
    CCSprite*                   background;
    CCSprite*                   shading1;
    CCSprite*                   shading2;
    Game*                       gameModel;
private:
    CCLabelBMFont*              m_LTimeToMove;
    CCPoint                     touchBegin;
    
    duration_move               durationMove;
    bool                        init();
    
    void                        update(float _dt);

    void                        onEnter();
    void                        onExit();
    
    void                        replaceScene(cocos2d::CCScene* _scene);

    float                       timeMoveEnemy;
    const float                 MAX_TIME_MOVE_ENEMY;
    
    CREATE_FUNC(BattleScene);
    
    BattleScene();
    ~BattleScene();
    
    
    //touch events
    void            ccTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesEnded(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesMoved(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesCancelled(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    
    HudScreen*          pHudScreen;
    const int           MIN_DISTANCE_MOVE;    
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__TEST_SCENE__
