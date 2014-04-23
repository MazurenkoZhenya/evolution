#include <iostream>
#include <vector>
#include "Game.h"
#include "BattleScene.h"
#include "Timer.h"
#include "CCActionInterval.h"

using namespace std;

Game* Game::pSelf = NULL;

Game::Game()
	: SPEED_CELL(0.1)
    , timeToMove(0)
    , maxTimeToMove(15.0f)
{
	mas.clear();

    Game::pSelf = this;
	std::vector<Cell*> _cell;
	MemoryProfiler* mProfiler = MemoryProfiler::getInstance();
	for (int i = 0; i < mProfiler->m_Size; i++ )
	{
		_cell.clear();
		mas.push_back(_cell);
		for ( int j = 0; j < mProfiler->m_Size; j++ ) 
		{
			mas[i].push_back(NULL);
		}
	}
	_scene = BattleScene::pSelf;
    timeToMove = maxTimeToMove;
}

bool Game::rand_count() 
{
	MemoryProfiler* mProfiler = MemoryProfiler::getInstance();
	vector<CCPoint> arr;
    
    arr.clear();
	for (int i = 0; i < mProfiler->m_Size; i++ ) 
	{
		for ( int j = 0; j < mProfiler->m_Size; j++ ) 
		{
			if ( mas[i][j] == NULL )
			{
				arr.push_back(ccp(j, i));
			}
		}
	}

	if ( arr.size() == 0 )
		return false;

	CCPoint random_pos = arr[rand()%arr.size()];

    Cell* newCell = Cell::create(2);
    
	newCell->getBody()->setPosition(ccp(newCell->getBody()->getContentSize().width / 2 + mProfiler->START_POS_ARR.x + (mProfiler->INDENT_CELL.x * (random_pos.x + 1) + random_pos.x * newCell->getRect()->getContentSize().width) * mProfiler->m_Scale, newCell->getBody()->getContentSize().height / 2 - mProfiler->START_POS_ARR.y - fabs(random_pos.y * newCell->getRect()->getContentSize().height + mProfiler->INDENT_CELL.y * (random_pos.y + 1)) * mProfiler->m_Scale));
	newCell->getBody()->setScale(0.1);
    _scene->addChild(newCell->getBody());
    

	CCScaleTo* scale = CCScaleTo::create(0.2, 1, 1);
	newCell->getBody()->runAction(scale);

	mas[(int)(random_pos.y)][(int)(random_pos.x)] = newCell;

	return true;
}

void Game::move_to(CCLayer* _sprite, CCPoint& _endPos, float _time)
{
    cocos2d::CCFiniteTimeAction* curActionMove = CCMoveTo::create(_time, _endPos);
    curActionMove->startWithTarget(_sprite);
    
    CCCallFunc* nextMove = CCCallFunc::create( _sprite, NULL);
    CCSequence* sequence = CCSequence::create(curActionMove, nextMove, NULL);
    
    _sprite->runAction(sequence);
}

void Game::moveDirection(duration_move _direction)
{
    CCPoint newPos;
	MemoryProfiler* mProfiler = MemoryProfiler::getInstance();
	if (_direction == DM_DOWN)
	{
		for (int i = 0; i < mProfiler->m_Size; i++ )
		{
			for (int j = mProfiler->m_Size - 1; j >= 0; j-- )
			{
				for (int z = mProfiler->m_Size - (mProfiler->m_Size - j); z >= 0; z-- )
				{
					if ( mas[z][i] != 0 && z != j)
					{
                        if(mas[j][i] == NULL)
						{
							mas[j][i] = mas[z][i];
                            newPos = ccp(mas[j][i]->getBody()->getPositionX(), (mas[j][i]->getBody()->getContentSize().height / 2 - mProfiler->START_POS_ARR.y - fabs(j * mas[z][i]->getRect()->getContentSize().height + mProfiler->INDENT_CELL.y * (j + 1)) * mProfiler->m_Scale));
                            move_to(mas[j][i]->getBody(), newPos, SPEED_CELL);
                            mas[z][i] = NULL;
						}else if (mas[j][i]->getNumber() == mas[z][i]->getNumber())
						{
							mas[j][i]->setNumber(mas[j][i]->getNumber() + mas[z][i]->getNumber());
                            newPos = ccp(mas[j][i]->getBody()->getPositionX(), (mas[j][i]->getBody()->getContentSize().height / 2 - mas[j][i]->getBody()->getPositionY() + mas[j][i]->getRect()->getContentSize().height) * mProfiler->m_Scale);
                            move_to(mas[z][i]->getBody(), newPos, SPEED_CELL);
                            mProfiler->cellForDell.push_back(mas[z][i]);
                            mas[z][i] = NULL;
							mProfiler->slogeniya = true;
							break;
						}else
							break;
					}
				}
			}
		}
	}else if (_direction == DM_LEFT)
	{
		for (int i = 0; i < mProfiler->m_Size; i++ )
		{
			for (int j = 0; j < mProfiler->m_Size; j++ )
			{
				for (int z = j; z < mProfiler->m_Size; z++ )
				{
					if ( mas[i][z] != 0 && z != j)
					{
                        if(mas[i][j] == NULL)
						{
							mas[i][j] = mas[i][z];
                            newPos = ccp(mProfiler->START_POS_ARR.x + (mProfiler->INDENT_CELL.x * (j + 1) + j * mas[i][z]->getRect()->getContentSize().width) * mProfiler->m_Scale, mas[i][z]->getBody()->getPositionY());
                            move_to(mas[i][j]->getBody(), newPos, SPEED_CELL);
							mas[i][z] = NULL;
                        }else if (mas[i][j]->getNumber() == mas[i][z]->getNumber())
						{
							mas[i][j]->setNumber(mas[i][j]->getNumber() + mas[i][z]->getNumber());
                            newPos = ccp((mas[i][j]->getBody()->getPositionX() + mas[i][j]->getRect()->getContentSize().width) * mProfiler->m_Scale, mas[i][j]->getBody()->getPositionY());
                            move_to(mas[i][z]->getBody(), newPos, SPEED_CELL);
                            
                            mProfiler->cellForDell.push_back(mas[i][z]);
							mas[i][z] = NULL;
							mProfiler->slogeniya = true;
							break;
						}else
							break;
					}
				}
			}
		}	
	}else if (_direction == DM_RIGHT)
	{
		for (int i = 0; i < mProfiler->m_Size; i++ )
		{
			for (int j = mProfiler->m_Size - 1; j >= 0; j-- )
			{
				for (int z = mProfiler->m_Size - (mProfiler->m_Size - j); z >= 0; z-- )
				{
					if ( mas[i][z] != 0 && z != j)
					{
                        if(mas[i][j] == NULL)
						{
							mas[i][j] = mas[i][z];
                            newPos = ccp(mProfiler->START_POS_ARR.x + (mProfiler->INDENT_CELL.x * (j + 1) + j * mas[i][z]->getRect()->getContentSize().width) * mProfiler->m_Scale, mas[i][j]->getBody()->getPositionY());
                            move_to(mas[i][j]->getBody(), newPos, SPEED_CELL);
							mas[i][z] = NULL;
						}else if (mas[i][j]->getNumber() == mas[i][z]->getNumber())
						{
							mas[i][j]->setNumber(mas[i][j]->getNumber() + mas[i][z]->getNumber());
                            newPos = ccp((mas[i][j]->getBody()->getPosition().x - mas[i][j]->getRect()->getContentSize().width) * mProfiler->m_Scale, mas[i][j]->getBody()->getPosition().y);
                            move_to(mas[i][z]->getBody(), newPos, SPEED_CELL);
                            mProfiler->cellForDell.push_back(mas[i][z]);
							mas[i][z] = NULL;
							mProfiler->slogeniya = true;
							break;
						}else
							break;
					}
				}
			}
		}
	}else if (_direction == DM_TOP)
	{
		for (int i = 0; i < mProfiler->m_Size; i++ )
		{
			for (int j = 0; j < mProfiler->m_Size; j++ )
			{
				for (int z = j; z < mProfiler->m_Size; z++ )
				{
					if ( mas[z][i] != 0 && z != j)
					{
                        if(mas[j][i] == NULL)
						{
							mas[j][i] = mas[z][i];
                            newPos = ccp(mas[j][i]->getBody()->getPositionX(), mProfiler->START_POS_ARR.y - fabs(j * mas[z][i]->getRect()->getContentSize().height + mProfiler->INDENT_CELL.y * (j + 1)) * mProfiler->m_Scale);
                            move_to(mas[j][i]->getBody(), newPos, SPEED_CELL);
							mas[z][i] = NULL;
						}
						else if (mas[j][i]->getNumber() == mas[z][i]->getNumber())
						{
							mas[j][i]->setNumber(mas[j][i]->getNumber() + mas[z][i]->getNumber());
                            newPos = ccp(mas[j][i]->getBody()->getPosition().x, (mas[j][i]->getBody()->getPosition().y - mas[j][i]->getRect()->getContentSize().height) * mProfiler->m_Scale);
                            move_to(mas[z][i]->getBody(), newPos, SPEED_CELL);
                            mProfiler->cellForDell.push_back(mas[z][i]);
							mas[z][i] = NULL;
							mProfiler->slogeniya = true;
							break;
						}else
							break;

					}
				}
			}
		}
	}
    
	
    CTimer::createOnce(schedule_selector(Game::destroyCell), 0, SPEED_CELL);
    if(_direction != DM_NONE)
    {
	    if(oldDirection != _direction || MemoryProfiler::getInstance()->slogeniya)
	    {
	        MemoryProfiler::getInstance()->slogeniya = false;
            rand_count();
        }
    
        if(checkDefeat())
        {
            onVictory();
        }
        oldDirection = _direction;
    }
}

void Game::upadte(float _dt)
{
}

bool Game::checkDefeat()
{
	MemoryProfiler* mProfiler = MemoryProfiler::getInstance();
		for (int i = 0; i < mProfiler->m_Size; i++ )
		{
			for (int j = mProfiler->m_Size - 1; j >= 0; j-- )
			{
				for (int z = mProfiler->m_Size - (mProfiler->m_Size - j); z >= 0; z-- )
				{
					if ( mas[z][i] != 0 && z != j)
					{
                        if(mas[j][i] == NULL)
                            return false;
						else if (mas[j][i]->getNumber() == mas[z][i]->getNumber())
							return false;
                        else
                        {
							z = -1;
                        }
                    }
				}
			}
		}

		for (int i = 0; i < mProfiler->m_Size; i++ )
		{
			for (int j = 0; j < mProfiler->m_Size; j++ )
			{
				for (int z = j; z < mProfiler->m_Size; z++ )
				{
					if ( mas[i][z] != 0 && z != j)
					{
                        if(mas[i][j] == NULL)
                            return false;
                        else if (mas[i][j]->getNumber() == mas[i][z]->getNumber())
                            return false;
						else
							z = mProfiler->m_Size;
					}
				}
			}
		}

		for (int i = 0; i < mProfiler->m_Size; i++ )
		{
			for (int j = mProfiler->m_Size - 1; j >= 0; j-- )
			{
				for (int z = mProfiler->m_Size - (mProfiler->m_Size - j); z >= 0; z-- )
				{
					if ( mas[i][z] != 0 && z != j)
					{
                        if(mas[i][j] == NULL)
                            return false;
						else if (mas[i][j]->getNumber() == mas[i][z]->getNumber())
                            return false;
						else
							z = -1;
					}
				}
			}
		}

		for (int i = 0; i < mProfiler->m_Size; i++ )
		{
			for (int j = 0; j < mProfiler->m_Size; j++ )
			{
				for (int z = j; z < mProfiler->m_Size; z++ )
				{
					if ( mas[z][i] != 0 && z != j)
					{
                        if(mas[j][i] == NULL)
							return false;
						else if (mas[j][i]->getNumber() == mas[z][i]->getNumber())
							return false;
						else
							z = mProfiler->m_Size;
                        
					}
				}
			}
		}    
    return true;
}

void Game::destroyCell(float _dt)
{
    MemoryProfiler* mProfiler = MemoryProfiler::getInstance();
    for (vector<Cell*>::iterator iter = mProfiler->cellForDell.begin(); iter < mProfiler->cellForDell.end(); iter++)
    {
        if((*iter))
        {
            (*iter)->getBody()->removeFromParentAndCleanup(true);
            delete (*iter);
        }
    }
    mProfiler->cellForDell.clear();

    Game::pSelf->timeToMove = Game::pSelf->maxTimeToMove;
}

void Game::onVictory()
{
	MemoryProfiler* mProfiler = MemoryProfiler::getInstance();
    for (int i = 0; i < mProfiler->m_Size; i++)
    {
        for (int j = 0; j < mProfiler->m_Size; j++)
        {
            if(Game::pSelf->mas[i][j] != NULL)
            {
                Game::pSelf->mas[i][j]->getBody()->removeAllChildrenWithCleanup(true);
                Game::pSelf->mas[i][j] = NULL;
            }
        }
    }
    
    Game::pSelf->rand_count();
    Game::pSelf->rand_count();
}