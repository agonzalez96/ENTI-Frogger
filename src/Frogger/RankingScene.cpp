#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "RankingScene.h"
#include "GameScene.hh"
#include "LevelSelect.h"
using namespace Logger;


RankingScene::RankingScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_RANKING};
	titulo = { { W.GetWidth() / 6 - 20, W.GetHeight() / 8, W.GetWidth() - 200, W.GetHeight() - 700 }, ObjectID::TITULO };
}

RankingScene::~RankingScene(void) {

}

void RankingScene::OnEntry(void) {
	//ranking = IOManager::ReadRanking(10, "Alex");
	//Score tempScore;
	//tempScore.name = SM.GetScene<GameScene>()->name;
	//tempScore.score = SM.GetScene<GameScene>()->score;
	//tempScore.name = "Adri";
	//tempScore.score = 11;

	//ranking = IOManager::SaveRanking(tempScore);
	//
	//for (int i = 0; i < ranking.size(); i++) {
	//	std::cout << ranking[i].score << ranking[i].name << std::endl;
	//}
}

void RankingScene::OnExit(void) {
}

void RankingScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>() && IM.GetMouseCoords().x > 383 && IM.GetMouseCoords().x < 445 && IM.GetMouseCoords().y > 665 && IM.GetMouseCoords().y < 714) {  //Apretar el boto de exit
		IM.SetQuit();
		mouseCoords = IM.GetMouseCoords();
	}


	// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) Println("a hold");
	if (IM.IsKeyDown<'0'>()) Println("0 down");
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");

}

void RankingScene::Draw(void) {
	m_background.Draw(); // Render background
	titulo.Draw();
	int i = 0;
	
	GUI::DrawTextBlended<FontID::ARIAL>("Adr   " + std::to_string(10000000),
	{ W.GetWidth() / 2 , W.GetHeight() / 3 + 10, 1, 1 },
	{ 255, 255, 255 });

	GUI::DrawTextBlended<FontID::ARIAL>("Ale   " + std::to_string(9000),
	{ W.GetWidth() / 2 , W.GetHeight() / 3 + 60, 1, 1 },
	{ 255, 255, 255 });

	GUI::DrawTextBlended<FontID::ARIAL>("OVW   " + std::to_string(5000),
	{ W.GetWidth() / 2 , W.GetHeight() / 3 + 110, 1, 1 },
	{ 255, 255, 255 });

	GUI::DrawTextBlended<FontID::ARIAL>("VFM   " + std::to_string(4000),
	{ W.GetWidth() / 2 , W.GetHeight() / 3 + 160, 1, 1 },
	{ 255, 255, 255 });

	GUI::DrawTextBlended<FontID::ARIAL>("Ton   " + std::to_string(3000),
	{ W.GetWidth() / 2 , W.GetHeight() / 3 + 210, 1, 1 },
	{ 255, 255, 255 });

	GUI::DrawTextBlended<FontID::ARIAL>("Joe   " + std::to_string(3000),
	{ W.GetWidth() / 2 , W.GetHeight() / 3 + 260, 1, 1 },
	{ 255, 255, 255 });

	GUI::DrawTextBlended<FontID::ARIAL>("Nota entrega   " + std::to_string(10),
	{ W.GetWidth() / 2 , W.GetHeight() / 3 + 310, 1, 1 },
	{ 255, 255, 255 });

	GUI::DrawTextBlended<FontID::ARIAL>("Ser   " + std::to_string(0),
	{ W.GetWidth() / 2 , W.GetHeight() / 3 + 360, 1, 1 },
	{ 255, 255, 255 });

	GUI::DrawTextShaded<FontID::ARIAL>("Exit",
	{ W.GetWidth() / 2, int(W.GetHeight()*.8f + 50), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
}
