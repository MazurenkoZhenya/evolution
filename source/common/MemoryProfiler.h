#ifndef __MusicalAdventure__MemoryProfiler__
#define __MusicalAdventure__MemoryProfiler__

#include <iostream>
#include "Cell.h"
#include "Character.h"

class MemoryProfiler
{
public:
    std::vector<Cell*>			cellForDell;
    static MemoryProfiler*		getInstance();
    static void					destroy();
    int							slogeniya;
	CCPoint						START_POS_ARR;
	CCPoint						INDENT_CELL;
	const int					m_DefSize;
	int							m_Size;
	float						m_Scale;
	void						setSize(int _size);
	Character*					m_Hero;
	int							m_RandNumber;
private:
    MemoryProfiler();
    ~MemoryProfiler();
    static MemoryProfiler* instance;
};

#endif /* defined(__MusicalAdventure__MemoryProfiler__) */
