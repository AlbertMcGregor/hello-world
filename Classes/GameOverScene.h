#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__
#include "cocos2d.h"
#include <string>

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(unsigned int tempScore);

    bool init();

	unsigned int GameOverScore;

    CREATE_FUNC(GameOverScene);
private:
	void GoToGameScene(Ref *sender);
	void ResetHighscore(Ref *sender);
};

#endif // __GAME_OVER_SCENE_H__
