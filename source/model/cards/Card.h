#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class Card: public CCNode
{
public:
    static Card*    create(int _id);


    string          getDescription();
    int             getNumber();
	
private:
	bool init(int _id);

    Card();
	~Card();


    CCLabelBMFont*	 m_Description;

    int				 m_Number;
};

#endif /*__CARD_H__*/
