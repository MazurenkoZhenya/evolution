#include "Timer.h"

using namespace cocos2d;

//---------------------------------------------------------------------------------------------------------------------------------
CTimer::CTimer(cocos2d::SEL_SCHEDULE _func, float _interval, unsigned int _call, float _delay, bool _cyclic):
func(_func),
interval(_interval),
call(_call),
delay(_delay),
cyclic(_cyclic)
{
    this->autorelease();
}

//---------------------------------------------------------------------------------------------------------------------------------
CTimer* CTimer::create(SEL_SCHEDULE _func, float _interval, unsigned int _repeat, float _delay)
{
    CTimer* pTimer = new CTimer(_func, _interval, _repeat + 1, _delay);
    pTimer->invoker(0);
    pTimer->onEnter();
    
    return pTimer;
}

//---------------------------------------------------------------------------------------------------------------------------------
CTimer* CTimer::createOnce(SEL_SCHEDULE _func, float _interval, float _delay)
{
    CTimer* pTimer = new CTimer(_func, _interval, 1, _delay);
    pTimer->invoker(0);
    pTimer->onEnter();
    return pTimer;
}

//---------------------------------------------------------------------------------------------------------------------------------
CTimer* CTimer::createCyclic(SEL_SCHEDULE _func, float _interval)
{
    CTimer* pTimer = new CTimer(_func, _interval, 1, 0, true);
    pTimer->invoker(0);
    pTimer->onEnter();
    
    return pTimer;
}

//---------------------------------------------------------------------------------------------------------------------------------
void CTimer::invoker(float _dt)
{
    if(_dt == 0)
    {
        if(cyclic)
            schedule(SEL_SCHEDULE(&CTimer::invoker), interval);
        else
            schedule(SEL_SCHEDULE(&CTimer::invoker), interval, call, delay);
    }
    else
    {
        if(call > 0)
        {
            schedule(func, 0, 0, 0);
        
            if(!cyclic)
                call--;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------