//  CCScrollLayer.h
//  Museum
//
//  Created by GParvaneh on 29/12/2010.
//  Copyright 2010 All rights reserved.
//  Ported to C++ by Lior Tamam on 03/04/2011
//  Cleaned for Cocos2d-x V2.x by @HermanJakobi (01/12/12)
#pragma once
#include "cocos2d.h"


class CCScrollLayer : public cocos2d::CCLayer 
{
    
public:
    
	static CCScrollLayer* create(cocos2d::CCArray* layers);
	
    bool init(cocos2d::CCArray *layers);

	virtual void moveToPage(int page);
	virtual void moveToNextPage();
	virtual void moveToPreviousPage();

	virtual int getCurrentPageIndex() { return m_current_page; }
	virtual int getPageCount() { return m_pages->count(); }
	virtual int getPageIndex(CCNode* page) { return m_pages->indexOfObject(page); }

	virtual void addPage(CCNode* page);
	virtual void insertPage(CCNode* page, int index);
	virtual void removePage(CCNode* page);

	inline bool isSwipeEnabled() const { return m_swipe_enabled; }
	inline void setSwipeEnabled(bool val) { m_swipe_enabled = val; }

protected:

	virtual void onMovePage(int page);
	virtual float getSwipeTreshold();

	long millisecondNow();
    
private:
    
	bool m_locked;
	bool m_swipe_enabled;

	float m_move_treshold;
	long m_quick_swipe_time;
	float m_quick_swipe_treshold;

    // Holds the current height and width of the screen
	int scrollHeight;
	int scrollWidth;
	
	// Holds the height and width of the screen when the class was inited
	int startHeight;
	int startWidth;
	
	// Holds the current page being displayed
	int m_current_page;
	
	// The initial point the user starts their swipe
	float startSwipe;

	long m_start_time;

	cocos2d::CCArray* m_pages;

	void movePage(int page);
	CCNode* getPage(int page);

	void rechildScreens();
	void rechildScreens(int prev_ind, int cur_ind, int next_ind);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);	
    
    virtual void onEnter();
	virtual void onExit();
    
	void onEndMove();

	void endMove(float f);
};