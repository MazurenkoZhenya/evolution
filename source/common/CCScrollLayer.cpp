//  CCScrollLayer.cpp
//  Museum
//
//  Created by GParvaneh on 29/12/2010.
//  Copyright 2010. All rights reserved.
//  Ported to C++ by Lior Tamam on 03/04/2011
//  Cleaned for Cocos2d-x V2.x by @HermanJakobi (01/12/12)

#include "CCScrollLayer.h"

USING_NS_CC;

CCScrollLayer* CCScrollLayer::create(CCArray *layers)
{	
	CCScrollLayer *pRet = new CCScrollLayer();
	if (pRet && pRet->init(layers))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCScrollLayer::init(CCArray *layers)
{	
	if (CCLayer::init())
	{		
		
		m_locked = false;
		m_swipe_enabled = true;

		m_move_treshold = 20.0f;
		m_quick_swipe_time = 500;
		m_quick_swipe_treshold = 150.0f;
		
		m_current_page = 0;
		
		// offset added to show preview of next/previous screens
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        
		scrollWidth  = s.width;
		scrollHeight = s.height;
		startWidth = scrollWidth;
		startHeight = scrollHeight;
		
		// Loop through the array and add the screens
		m_pages = layers;
		m_pages->retain();
		rechildScreens();
		
		return true;	
	}
	
    
    return false;
    
}

void CCScrollLayer::onEnter()
{
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    CCLayer::onEnter();
}

void CCScrollLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	
    CCLayer::onExit();
}	


void CCScrollLayer::moveToPage(int page)
{	
	if(abs(page - m_current_page) > 1)
	{
		if(page > m_current_page)
		{
			rechildScreens(m_current_page - 1, m_current_page, page);
		}
		else
		{
			rechildScreens(page, m_current_page, m_current_page + 1);
		}
	}
	movePage(page);
}

void CCScrollLayer::moveToNextPage()
{	
	int next = m_current_page + 1;
	if(next < getPageCount())
	{
		movePage(next);
	}
}

void CCScrollLayer::moveToPreviousPage()
{	
	int prev = m_current_page - 1;
	if(prev >= 0)
	{
		movePage(prev);
	}
}

void CCScrollLayer::onEndMove()
{
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCScrollLayer::endMove), this, 0.0f, 0, 0.0f, false);
}

void CCScrollLayer::endMove( float f )
{
	rechildScreens();
	m_locked = false;
}

void CCScrollLayer::movePage( int page )
{
	if(!m_locked)
	{
		m_locked = true;
		
		int relative = m_current_page == page ? 0 : m_current_page > page ? -1 : 1;
		CCPoint dest(-(relative*scrollWidth), 0);
		CCPoint cur_pos = getPosition();
		float delta = abs(dest.x - cur_pos.x);
		float duration = 0.3f;
		duration *= delta/scrollWidth;

		if(delta < getSwipeTreshold())
		{
			duration *= 1.2*getSwipeTreshold()/delta;
			/*if(duration < 0.15f)
			{
				duration = 0.15f;
			}*/
		}

		CCEaseBounce* changePage = CCEaseBounce::create(CCMoveTo::create(duration, dest));
		CCFiniteTimeAction* move_done = CCCallFunc::create(this, callfunc_selector(CCScrollLayer::onEndMove));
		this->runAction( CCSequence::create(changePage, move_done, NULL));
		onMovePage(m_current_page);
		m_current_page = page;
	}
}

bool CCScrollLayer::ccTouchBegan(CCTouch *touch, CCEvent *withEvent)
{
	if(m_swipe_enabled)
	{
		CCPoint touchPoint = touch->getLocation(); // Get the touch position
		touchPoint = this->getParent()->convertToNodeSpace(touchPoint);
	
		startSwipe = touchPoint.x;
		m_start_time = millisecondNow();
		return true;
	}
	return false;
}

void CCScrollLayer::ccTouchMoved(CCTouch *touch, CCEvent *withEvent)
{	
    CCPoint touchPoint = touch->getLocation(); // Get the touch position
    touchPoint = this->getParent()->convertToNodeSpace(touchPoint);
	
	float delta = touchPoint.x - startSwipe;
	if(abs(delta) >= m_move_treshold)
	{
		float visible_delta = delta > 0 ? delta - m_move_treshold : delta + m_move_treshold;
		this->setPosition(ccp(visible_delta, 0));
	}
}

void CCScrollLayer::ccTouchEnded(CCTouch *touch, CCEvent *withEvent)
{
    CCPoint touchPoint = touch->getLocation(); // Get the touch position
    touchPoint = this->getParent()->convertToNodeSpace(touchPoint);
	
	float delta_x = touchPoint.x - startSwipe;
	float time = millisecondNow() - m_start_time;
    
	if ( delta_x < -getSwipeTreshold() && (m_current_page + 1) < getPageCount() )
	{
		this->moveToNextPage();
	}
	else if ( delta_x > getSwipeTreshold() && m_current_page > 0 )
	{
		this->moveToPreviousPage();
	}
	else if( delta_x <= -m_quick_swipe_treshold && time <= m_quick_swipe_time && (m_current_page + 1) < getPageCount() )
	{
		this->moveToNextPage();
	}
	else if( delta_x >= m_quick_swipe_treshold && time <= m_quick_swipe_time && m_current_page > 0)
	{
		this->moveToPreviousPage();
	}
	else 
	{
		this->moveToPage(m_current_page);		
	}	
}

void CCScrollLayer::onMovePage( int page )
{

}

void CCScrollLayer::rechildScreens()
{
	rechildScreens(m_current_page - 1, m_current_page, m_current_page + 1);
}

void CCScrollLayer::rechildScreens( int prev_ind, int cur_ind, int next_ind )
{
	removeAllChildren();

	CCNode* prev = getPage(prev_ind);
	CCNode* cur = getPage(cur_ind);
	CCNode* next = getPage(next_ind);

	if(prev)
	{
		addChild(prev);
		prev->setPosition(ccp(-scrollWidth, 0));
	}
	addChild(cur);
	cur->setPosition(CCPointZero);
	if(next)
	{
		addChild(next);
		next->setPosition(ccp(scrollWidth, 0));
	}
	this->setPosition(CCPointZero);
}

CCNode* CCScrollLayer::getPage( int page )
{
	if(page >= 0 && page < getPageCount())
	{
		return static_cast<CCNode*>(m_pages->objectAtIndex(page));
	}
	return NULL;
}

void CCScrollLayer::addPage( CCNode* page )
{
	m_pages->addObject(page);
	if(abs(m_current_page - (getPageCount() - 1)) <= 1)
	{
		rechildScreens();
	}
}

void CCScrollLayer::insertPage( CCNode* page, int index )
{
	if(index >= 0 && index <= getPageCount())
	{
		m_pages->insertObject(page, index);
		if(abs(m_current_page - index) <= 1)
		{
			rechildScreens();
		}
	}
}

void CCScrollLayer::removePage( CCNode* page )
{
	int index = m_pages->indexOfObject(page);
	if(index >= 0)
	{
		m_pages->removeObjectAtIndex(index);
		if(m_current_page >= getPageCount())
		{
			m_current_page = getPageCount() - 1;
		}
		if(abs(m_current_page - index) <= 1)
		{
			rechildScreens();
		}
	}
}

float CCScrollLayer::getSwipeTreshold()
{
	return scrollWidth * 0.33;
}

long CCScrollLayer::millisecondNow()
{
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}