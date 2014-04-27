#ifndef __CARD_SCENE_H__
#define __CARD_SCENE_H__

#include "cocos2d.h"
#include "common\CCScrollLayer.h"

class CardScene: public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();

	CREATE_FUNC( CardScene );

private:
	bool				init();

	void				initMenu();
	void				loadCardsFromXml();

	void				onBackButtonAction(cocos2d::CCObject* sender);
	void				onShopButtonAction(cocos2d::CCObject* sender);

	virtual void		ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void		ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void		ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void		ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	CardScene();
	~CardScene();

	CCScrollLayer*		m_pScrollList;
};

#endif /*__CARD_SCENE_H__*/