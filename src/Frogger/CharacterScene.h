/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "Grid.hh"
#include "Scene.hh"

// GameScene class with the main gameplay mode
class CharacterScene : public Scene {
public:
	explicit CharacterScene();
	~CharacterScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background;
	Sprite mccree;
	int m_score{ 0 };
};