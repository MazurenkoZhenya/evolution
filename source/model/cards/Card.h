#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"


using namespace std;

class Card: public cocos2d::CCNode
{
public:
    static Card*    create(int _number, const char* _texture_path, const char* _desciption_string);

    string          getDescription();
    int             getNumber();
	
private:
	bool init(int _number, const char* _texture_path, const char* _desciption_string);

    Card();
	~Card();


    cocos2d::CCLabelBMFont*		m_pDescription;
	cocos2d::CCSprite*			m_pCardSprite;

    int							m_Number;
};

#endif /*__CARD_H__*/
