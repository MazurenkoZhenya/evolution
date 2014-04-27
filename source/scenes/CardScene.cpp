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

	setTouchEnabled( true );

	initMenu();

	loadCardsFromXml();

	return true;
}


void CardScene::initMenu()
{
	CCSprite* backButtonSprite = CCSprite::create("backArrow.png");
	CCSprite* backButtonSpriteSel = CCSprite::create("backArrow.png");
	backButtonSpriteSel->setScale( 0.9 );

	CCSprite* shopButtonSprite = CCSprite::create("shop.png");
	CCSprite* shopButtonSpriteSel = CCSprite::create("shop.png");
	shopButtonSpriteSel->setScale( 0.9 );

	CCMenuItemSprite* backButton = CCMenuItemSprite::create(backButtonSprite, backButtonSpriteSel, this, menu_selector(CardScene::onBackButtonAction));
	backButton->setPosition( ccp(650, 930) );
	
	CCMenuItemSprite* shopButton = CCMenuItemSprite::create(shopButtonSprite, shopButtonSpriteSel, this, menu_selector(CardScene::onShopButtonAction));
	shopButton->setPosition( ccp(100, 930) );

	CCMenu* menu = CCMenu::create(backButton, shopButton, NULL);
	menu->setPosition(0, 0);
	addChild( menu );
}


void CardScene::loadCardsFromXml()
{
	TiXmlDocument doc;

	//list of card for scroll layer init
	CCArray* cardList = CCArray::create();

	if ( doc.LoadFile(CARDS_XML) )
	{
		TiXmlElement* cards_tag = doc.FirstChildElement();
		TiXmlElement* card_tag = cards_tag->FirstChildElement();
		
		while ( card_tag )
		{
			int number = 0; 
			card_tag->QueryIntAttribute("number", &number);

			const char* path = card_tag->Attribute("path");
			const char* description_id = card_tag->Attribute("description_id");

			//TODO: load description from L10n(Localization) file with description_id

			//create card and add to card list
			Card* card = Card::create(number, path, description_id);
			cardList->addObject( card );
			
			card_tag = card_tag->NextSiblingElement();
		}
	}


	m_pScrollList = CCScrollLayer::create(cardList);
	m_pScrollList->setPosition( ccp(0, 0) );
	addChild( m_pScrollList );

}


void CardScene::onBackButtonAction(cocos2d::CCObject* sender)
{
	//TODO: replace scene
	Card* card = Card::create(0, "manTemp.jpg", "THIS_IS_NEW_STRING");
	m_pScrollList->addPage( card );
}


void CardScene::onShopButtonAction(cocos2d::CCObject* sender)
{
	//TODO: replace scene
}


void CardScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
	CCPoint touch_point = convertTouchToNodeSpace( touch );

}


void CardScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}


void CardScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
	CCPoint touch_point = convertTouchToNodeSpace( touch );
}


void CardScene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	this->ccTouchesEnded(pTouches, pEvent);
}


CardScene::~CardScene()
{
	
}