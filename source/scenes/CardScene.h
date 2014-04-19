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

	CardScene();
	~CardScene();

	CCScrollLayer*		m_pScrollList;
};

#endif /*__CARD_SCENE_H__*/