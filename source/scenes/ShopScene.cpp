#include "ShopScene.h"
#include "MainMenuScene.h"

using namespace cocos2d;


//------------------------------------------------------------------------------------------------
CCScene* ShopScene::scene()
{
	CCScene* scene = CCScene::create();

	ShopScene* pShopScene = ShopScene::create();
    scene->addChild( pShopScene );

    return scene;
}

//------------------------------------------------------------------------------------------------
bool ShopScene::init()
{
	if(!CCLayer::init())
		return false;
	


	return true;
}

//------------------------------------------------------------------------------------------------
ShopScene::ShopScene()
{

}

//------------------------------------------------------------------------------------------------
ShopScene::~ShopScene()
{

}
