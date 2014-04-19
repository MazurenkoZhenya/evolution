#include "Card.h"

Card::Card()
	: m_Description(NULL)
	, m_Number(0)
{
    
}


Card::~Card()
{
    
}


Card* Card::create(int _id)
{
    Card* card = new Card();    
	if (card && card->init(_id))
	{
		card->autorelease();
		return card;
	}
	else
	{
		delete card;
		card = NULL;
		return NULL;
	}
}


bool Card::init(int _id)
{
	/*if ( !CCLayer::init() )
		return false;*/
	CCSprite* tempSpr = CCSprite::create("textures/scenes/card/manTemp.jpg");
	tempSpr->setAnchorPoint( ccp(0, 0) );
	tempSpr->setPosition( ccp(150, 50) );
	addChild( tempSpr );


	return true;
}


int Card::getNumber()
{
    return m_Number;
}

string Card::getDescription()
{
	return m_Description->getString();
}