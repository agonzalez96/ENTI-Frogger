#pragma once
#include "Sprite.hh"
#include "Scene.hh"
#include "Score.hh"

// MenuScene class with the main gameplay mode
class RankingScene : public Scene {
private:
	Sprite m_background;
	Sprite titulo;
public:
	explicit RankingScene();
	~RankingScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	std::vector<Score> ranking;

};