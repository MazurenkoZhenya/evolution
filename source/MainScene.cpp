#include "MainScene.h"


using namespace cocos2d;


CCScene* MainScene::scene()
{
	CCScene* pScene = CCScene::create();
	MainScene* pMainScene = MainScene::create();
	pScene->addChild( pMainScene );

	return pScene;
}


MainScene::MainScene()
{

}


bool MainScene::init()
{
	if ( !CCLayer::init())
		return false;

	return true;
}


MainScene::~MainScene()
{
	
}