#include "CardScene.h"
#include "Card.h"

using namespace cocos2d;


CCScene* CardScene::scene()
{
	CCScene* scene = CCScene::create();
	CardScene* layer = CardScene::create();
	scene->addChild( layer );

	return scene;
}


CardScene::CardScene()
	: m_pScrollList(NULL)
{

}


bool CardScene::init()
{
	if ( !CCLayer::init() )
		return false;


	//TODO: back and shop as buttons
	CCSprite* backArrow = CCSprite::create("textures/scenes/card/backArrow.png");
	backArrow->setPosition( ccp(650, 930) );
	addChild( backArrow );

	CCSprite* shop = CCSprite::create("textures/scenes/card/shop.png");
	shop->setPosition( ccp(100, 930) );
	addChild( shop );

	//TODO: init card from XML
	Card* card1 = Card::create(0);
	Card* card2 = Card::create(0);

	CCArray* cardList = CCArray::create(card1, card2, NULL);

	m_pScrollList = CCScrollLayer::create(cardList);
	m_pScrollList->setPosition( ccp(0, 0) );
	addChild( m_pScrollList );


	return true;
}


CardScene::~CardScene()
{
	
}