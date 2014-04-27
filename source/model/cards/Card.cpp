#include "Card.h"


using namespace cocos2d;


Card::Card()
	: m_pDescription(NULL)
	, m_pCardSprite(NULL)
	, m_Number(0)
{
    
}


Card::~Card()
{
    
}


Card* Card::create(int _number, const char* _texture_path, const char* _desciption_string)
{
    Card* card = new Card();    
	if (card && card->init(_number, _texture_path, _desciption_string))
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


bool Card::init(int _number, const char* _texture_path, const char* _desciption_string)
{
	m_Number = _number;

	m_pCardSprite = CCSprite::create(_texture_path);
	m_pCardSprite->setAnchorPoint( ccp(0, 0) );
	m_pCardSprite->setPosition( ccp(150, 50) );
	addChild( m_pCardSprite );

	m_pDescription = CCLabelBMFont::create(_desciption_string, "days26black.fnt", m_pCardSprite->getContentSize().width);
	m_pDescription->setAnchorPoint( ccp(0, 0) );
	m_pDescription->setPosition(150, 100);
	addChild( m_pDescription );


	return true;
}


int Card::getNumber()
{
    return m_Number;
}

string Card::getDescription()
{
	assert( m_pDescription );

	if ( !m_pDescription )
		return "";

	return m_pDescription->getString();
}