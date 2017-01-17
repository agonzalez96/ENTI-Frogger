/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once

#include "Scene.hh"
#include "Sprite.hh"
#include "IOManager.hh"
#include "LevelSelect.h"
#include "FPSLimiter.h"
#include <time.h>
#include <chrono>
#include <ctime>
#include "Goal.hh"
#include <math.h>  


//Posar nivell 
// GameScene class with the main gameplay mode
class GameScene : public Scene {
public:
	explicit GameScene();
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void KillFrog(void);
	void MoveElements(int size);
	void DrawElements(int size);
	void ColideElements(int size);
	int score{ 0 };
	std::string name; 
private:
	std::vector<Sprite> itemList; 
	Sprite rana;
	Sprite m_background;
	Sprite barro;
	Sprite barroini;
	Sprite meta;
	Sprite timer;	
	std::vector<Sprite> lifeList;
	Sprite life;
	std::vector<Goal> goalList;
	int countIn = 0;
	Goal goal1;
	Goal goal2;
	Goal goal3;
	Goal goal4;
	Goal goal5;
	std::unordered_map<ObjectID, SDL_Texture*> textureData;

	int antScore = 0;
	int scorediff = 0;
	float vel;
	float vel2;
	int i = 0;
	int c = 0;
	int angle = 0;
	bool pause = false;
	int maxLifes;
	int maxTime;
	int lvlTime;
	std::chrono::duration<float> actualTime;
	std::chrono::duration<float> insecteTime;
	std::chrono::duration<float> ladyFrogTime;
	std::chrono::duration<float> tortugaTime;
	std::chrono::duration<float> cocodrileTime;
	bool colision = false;
	bool lady = false;
	bool ladyGotcha = false;
	bool insect = false;
	Sprite *ladyFrog;
	float timeRand = rand() % (maxTime - 20);
	float timeRand2 = rand() % (maxTime - 15);
	int random1;
	int random2;
	int nivell = 1;
};