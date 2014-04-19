#include <iostream>
#include <vector>
#include "Game.h"
#include "BattleScene.h"
#include "Timer.h"
#include "common/MemoryProfiler.h"

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
	
	for (int i = 0; i < ROW_GAME; i++ )
	{
		_cell.clear();
		mas.push_back(_cell);
		for ( int j = 0; j < COL_GAME; j++ ) 
		{
			mas[i].push_back(NULL);
		}
	}
	_scene = BattleScene::pSelf;
    timeToMove = maxTimeToMove;
}

bool Game::rand_count() 
{
	vector<CCPoint> arr;
    
    arr.clear();
	for (int i = 0; i < ROW_GAME; i++ ) 
	{
		for ( int j = 0; j < COL_GAME; j++ ) 
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
    newCell->setPos(random_pos);
    
    newCell->getBody()->setPosition(ccp(12 * (random_pos.x + 1) + _scene->START_POS_ARR.x + random_pos.x * newCell->getRect()->getContentSize().width, _scene->START_POS_ARR.y - random_pos.y * newCell->getRect()->getContentSize().height - 13 * (random_pos.y + 1)));
    
    _scene->addChild(newCell->getBody());
    
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
    minusHP = 0;
    CCPoint newPos;
	if (_direction == DM_DOWN)
	{
		for (int i = 0; i < ROW_GAME; i++ )
		{
			for (int j = COL_GAME - 1; j >= 0; j-- )
			{
				for (int z = COL_GAME - (COL_GAME - j); z >= 0; z-- )
				{
					if ( mas[z][i] != 0 && z != j)
					{
                        if(mas[j][i] == NULL)
						{
							mas[j][i] = mas[z][i];
                            mas[j][i]->setPos(ccp(i, j));
                            newPos = ccp(mas[j][i]->getBody()->getPositionX(), _scene->START_POS_ARR.y - j * mas[z][i]->getRect()->getContentSize().height - 13 * (j + 1));
                            move_to(mas[j][i]->getBody(), newPos, SPEED_CELL);
                            //mas[j][i]->getBody()->setPositionY(_scene->START_POS_ARR.y - j * mas[z][i]->getRect()->getContentSize().height - 13 * (j + 1));
                            mas[z][i] = NULL;
						}else if (mas[j][i]->getNumber() == mas[z][i]->getNumber())
						{
							mas[j][i]->setNumber(mas[j][i]->getNumber() + mas[z][i]->getNumber());
                            mas[j][i]->setPos(ccp(i, j));
                            newPos = ccp(mas[j][i]->getBody()->getPositionX(), mas[j][i]->getBody()->getPositionY() + mas[j][i]->getRect()->getContentSize().height);
                            move_to(mas[z][i]->getBody(), newPos, SPEED_CELL);
                            MemoryProfiler::getInstance()->cellForDell.push_back(mas[z][i]);
                            //mas[z][i]->getBody()->removeFromParentAndCleanup(true);
                            mas[z][i] = NULL;
                            minusHP += mas[j][i]->getNumber();
							MemoryProfiler::getInstance()->slogeniya = true;
							break;
						}else
							break;
					}
				}
			}
		}
	}else if (_direction == DM_LEFT)
	{
		for (int i = 0; i < ROW_GAME; i++ )
		{
			for (int j = 0; j < COL_GAME; j++ )
			{
				for (int z = j; z < COL_GAME; z++ )
				{
					if ( mas[i][z] != 0 && z != j)
					{
                        if(mas[i][j] == NULL)
						{
							mas[i][j] = mas[i][z];
                            mas[i][j]->setPos(ccp(j, i));
                            newPos = ccp(12 * (j + 1) + _scene->START_POS_ARR.x + j * mas[i][z]->getRect()->getContentSize().width, mas[i][z]->getBody()->getPositionY());
                            move_to(mas[i][j]->getBody(), newPos, SPEED_CELL);
                            //mas[i][j]->getBody()->setPositionX(12 * (j + 1) + _scene->START_POS_ARR.x + j * mas[i][z]->getRect()->getContentSize().width);
							mas[i][z] = NULL;
                        }else if (mas[i][j]->getNumber() == mas[i][z]->getNumber())
						{
							mas[i][j]->setNumber(mas[i][j]->getNumber() + mas[i][z]->getNumber());
                            mas[i][j]->setPos(ccp(j, i));
                            newPos = ccp(mas[i][j]->getBody()->getPositionX() + mas[i][j]->getRect()->getContentSize().width, mas[i][j]->getBody()->getPositionY());
                            move_to(mas[i][z]->getBody(), newPos, SPEED_CELL);
                            
                            MemoryProfiler::getInstance()->cellForDell.push_back(mas[i][z]);
                            //mas[i][z]->getBody()->removeFromParentAndCleanup(true);
							mas[i][z] = NULL;
							minusHP += mas[i][j]->getNumber();
							MemoryProfiler::getInstance()->slogeniya = true;
							break;
						}else
							break;
					}
				}
			}
		}	
	}else if (_direction == DM_RIGHT)
	{
		for (int i = 0; i < ROW_GAME; i++ )
		{
			for (int j = COL_GAME - 1; j >= 0; j-- )
			{
				for (int z = COL_GAME - (COL_GAME - j); z >= 0; z-- )
				{
					if ( mas[i][z] != 0 && z != j)
					{
                        if(mas[i][j] == NULL)
						{
							mas[i][j] = mas[i][z];
                            mas[i][j]->setPos(ccp(j, i));
                            newPos = ccp(12 * (j + 1) + _scene->START_POS_ARR.x + j * mas[i][z]->getRect()->getContentSize().width, mas[i][j]->getBody()->getPositionY());
                            move_to(mas[i][j]->getBody(), newPos, SPEED_CELL);
                            //mas[i][j]->getBody()->setPositionX(12 * (j + 1) + _scene->START_POS_ARR.x + j * mas[i][z]->getRect()->getContentSize().width);
							mas[i][z] = NULL;
						}else if (mas[i][j]->getNumber() == mas[i][z]->getNumber())
						{
							mas[i][j]->setNumber(mas[i][j]->getNumber() + mas[i][z]->getNumber());
                            mas[i][j]->setPos(ccp(j, i));
                            newPos = ccp(mas[i][j]->getBody()->getPosition().x - mas[i][j]->getRect()->getContentSize().width, mas[i][j]->getBody()->getPosition().y);
                            move_to(mas[i][z]->getBody(), newPos, SPEED_CELL);
                            MemoryProfiler::getInstance()->cellForDell.push_back(mas[i][z]);
                            //mas[i][z]->getBody()->removeFromParentAndCleanup(true);
							mas[i][z] = NULL;
							minusHP += mas[i][j]->getNumber();
							MemoryProfiler::getInstance()->slogeniya = true;
							break;
						}else
							break;
					}
				}
			}
		}
	}else if (_direction == DM_TOP)
	{
		for (int i = 0; i < ROW_GAME; i++ )
		{
			for (int j = 0; j < COL_GAME; j++ )
			{
				for (int z = j; z < COL_GAME; z++ )
				{
					if ( mas[z][i] != 0 && z != j)
					{
                        if(mas[j][i] == NULL)
						{
							mas[j][i] = mas[z][i];
                            newPos = ccp(mas[j][i]->getBody()->getPositionX(), _scene->START_POS_ARR.y - j * mas[z][i]->getRect()->getContentSize().height - 13 * (j + 1));
                            move_to(mas[j][i]->getBody(), newPos, SPEED_CELL);
                            //mas[j][i]->getBody()->setPositionY(_scene->START_POS_ARR.y - j * mas[z][i]->getRect()->getContentSize().height - 13 * (j + 1));
							mas[z][i] = NULL;
						}
						else if (mas[j][i]->getNumber() == mas[z][i]->getNumber())
						{
							mas[j][i]->setNumber(mas[j][i]->getNumber() + mas[z][i]->getNumber());
                            mas[j][i]->setPos(ccp(i, j));
                            newPos = ccp(mas[j][i]->getBody()->getPosition().x, mas[j][i]->getBody()->getPosition().y - mas[j][i]->getRect()->getContentSize().height);
                            move_to(mas[z][i]->getBody(), newPos, SPEED_CELL);
                            MemoryProfiler::getInstance()->cellForDell.push_back(mas[z][i]);
                            //mas[z][i]->getBody()->removeFromParentAndCleanup(true);
							mas[z][i] = NULL;
							minusHP += mas[j][i]->getNumber();
							MemoryProfiler::getInstance()->slogeniya = true;
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
		for (int i = 0; i < ROW_GAME; i++ )
		{
			for (int j = COL_GAME - 1; j >= 0; j-- )
			{
				for (int z = COL_GAME - (COL_GAME - j); z >= 0; z-- )
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

		for (int i = 0; i < ROW_GAME; i++ )
		{
			for (int j = 0; j < COL_GAME; j++ )
			{
				for (int z = j; z < COL_GAME; z++ )
				{
					if ( mas[i][z] != 0 && z != j)
					{
                        if(mas[i][j] == NULL)
                            return false;
                        else if (mas[i][j]->getNumber() == mas[i][z]->getNumber())
                            return false;
						else
							z = COL_GAME;
					}
				}
			}
		}

		for (int i = 0; i < ROW_GAME; i++ )
		{
			for (int j = COL_GAME - 1; j >= 0; j-- )
			{
				for (int z = COL_GAME - (COL_GAME - j); z >= 0; z-- )
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

		for (int i = 0; i < ROW_GAME; i++ )
		{
			for (int j = 0; j < COL_GAME; j++ )
			{
				for (int z = j; z < COL_GAME; z++ )
				{
					if ( mas[z][i] != 0 && z != j)
					{
                        if(mas[j][i] == NULL)
							return false;
						else if (mas[j][i]->getNumber() == mas[z][i]->getNumber())
							return false;
						else
							z = COL_GAME;
                        
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
    for (int i = 0; i < ROW_GAME; i++)
    {
        for (int j = 0; j < COL_GAME; j++)
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