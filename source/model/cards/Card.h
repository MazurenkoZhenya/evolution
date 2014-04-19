#ifndef __MusicalAdventure__Cell__
#define __MusicalAdventure__Cell__

#include <iostream>
#include "cocos2d.h"
#include "tinyxml.h"

using namespace cocos2d;
using namespace std;

class Card{
public:
    static Card*    create(int _id);
    CCLayer*        getBody();
    string          getDescription(string);
    int             getNumber();
	~Card();
private:
    Card();
    CCLabelBMFont*	 m_Description;
    CCLayer*		 m_Body;
    int				 m_Number;
};

#endif /* defined(__MusicalAdventure__Cell__) */
