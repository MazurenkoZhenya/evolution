#include "Card.h"

Card::Card()
{
    
}

Card::~Card()
{
    
}

Card* Card::create(int _numberCell)
{

    Card* card = new Card();    
    
    return card;
}

CCLayer* Card::getBody()
{
    return m_Body;
}

int Card::getNumber()
{
    return m_Number;
}