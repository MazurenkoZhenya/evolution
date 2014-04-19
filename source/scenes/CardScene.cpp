#include "CardScene.h"
#include "Card.h"
#include "tinyxml.h"


using namespace cocos2d;


#define CARDS_XML "xml/cards.xml"


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


	loadCardsFromXml();

	return true;
}


void CardScene::loadCardsFromXml()
{
	TiXmlDocument doc;

	if ( doc.LoadFile(CARDS_XML) )
	{
		TiXmlElement* cards_tag = doc.FirstChildElement();
		TiXmlElement* card_tag = cards_tag->FirstChildElement();
		
		while ( card_tag )
		{
			int number = 0; 
			card_tag->QueryIntAttribute("number", &number);

			const char* path = card_tag->Attribute("path");
			const char* name = card_tag->Attribute("name");
			const char* description = card_tag->Attribute("description");
			
			card_tag = card_tag->NextSiblingElement();
		}
	}

}


CardScene::~CardScene()
{
	
}