#include <iostream>
#include "Config.h"
#include "Cell.h"
#include "common/MemoryProfiler.h"

class BattleScene;

using namespace std;

class Game
{
public:
    static Game*					  pSelf;
	Game();
	bool						      rand_count();
	void		                      moveDirection(duration_move _direction);
    void							  move_to(CCLayer* _sprite, CCPoint& _endPos, float _time);
	void				              run();
	bool	                          checkDefeat();
    void							  destroyCell(float _dt);
    vector<vector<Cell*>>			  mas;
    float							  timeToMove;
    const float						  maxTimeToMove;
    void							  upadte(float _dt);
private:
    BattleScene*					  _scene;
	int								  duration;
	int								  size;
	duration_move					  oldDirection;
	void							  onVictory();
    const float				          SPEED_CELL;
};