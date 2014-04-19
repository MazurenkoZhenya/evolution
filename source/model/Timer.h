#ifndef __CTimer__
#define __CTimer__

#include "cocos2d.h"

//---------------------------------------------------------------------------------------------------------------------------------
class CTimer : public cocos2d::CCNode
{
public:
    static CTimer* create(cocos2d::SEL_SCHEDULE _func, float _interval, unsigned int _repeat = 0, float _delay = 0);
    static CTimer* createOnce(cocos2d::SEL_SCHEDULE _func, float _interval, float _delay = 0);
    static CTimer* createCyclic(cocos2d::SEL_SCHEDULE _func, float _interval);

private:
    cocos2d::SEL_SCHEDULE   func;
    float                   interval;
    unsigned int            call;
    float                   delay;
    bool                    cyclic;
    
    void invoker(float _dt);
    
    CTimer(cocos2d::SEL_SCHEDULE _func, float _interval, unsigned int _call, float _delay, bool _cyclic = false);
    ~CTimer(){};
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__CTimer__
