/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include "RankingScene.h"

using namespace Logger;

SDL_RendererFlip flip = SDL_FLIP_NONE;

GameScene::GameScene(void){
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_GAME };
	barro = { { 0, W.GetHeight()/2-(W.GetHeight() / 40), W.GetWidth(), W.GetHeight()/12 }, ObjectID::BARRO };
	barroini = { { 0, W.GetHeight()- (W.GetHeight() / 13), W.GetWidth(), W.GetHeight()/12 }, ObjectID::BARRO };
	meta = { { 0,0, W.GetWidth(), W.GetHeight() / 10 }, ObjectID::META };
	timer = { { 0, W.GetHeight() - 30, W.GetWidth(), 10 }, ObjectID::TIMER };
	textureData = R.GetTextureData();
	SDL_QueryTexture(textureData.find(ObjectID::RANA)->second, NULL, NULL, &rana.transform.w, &rana.transform.h);
	rana = { { W.GetWidth() / 2 , W.GetHeight() - rana.transform.h * 2, rana.transform.w * 2, rana.transform.h * 2 }, ObjectID::RANA };
	
}

GameScene::~GameScene(void){
}

void GameScene::OnEntry(void) {
	itemList = IOManager::LoadLevelXML("cfg/Difficulty.xml");
	
	std::cout << "Introduce your name: " << std::endl;
	std::cin >> name;
		if (name.size() >= 3) {
			name.resize(3);
		}
	score = 0;
	//Assignació de vides i velocitat depenent la dificultat
	if (LevelSelect::_diff == "Easy") {
		maxLifes = 10;
		lvlTime = 60;
		maxTime = lvlTime;
		vel = 1.0000f;
		vel2 = 2.0000f;
	}
	else if (LevelSelect::_diff == "Medium") {
		maxLifes = 5;
		lvlTime = 30;
		maxTime = lvlTime;
		vel = 2.0f;
		vel2 = 3.0f;
	}
	if (LevelSelect::_diff == "Hard") {
		maxLifes = 1;
		lvlTime = 20;
		maxTime = lvlTime;
		vel = 3.0f;
		vel2 = 4.0f;
	}
	
	//AQUI AFEGIM LES METES A UN VECTOR DE METES I ASSIGNEM LA POSICIO A CADASCUNA
	goalList.push_back(goal1);
	goalList.push_back(goal2);
	goalList.push_back(goal3);
	goalList.push_back(goal4);
	goalList.push_back(goal5);
	
	for (int l = 0; l < goalList.size(); l++) {
		goalList[l].y = 50;
		if (l == 0) {
			goalList[l].x = 54;
		}
		else {
			goalList[l].x = goalList[l - 1].x + 176;
		}
	}

	//AFEGIM LES VIDES SEGONS LA DIFICULTAT
	for (int l = 0; l < maxLifes; l++) {
		lifeList.push_back(life);
	}
	for (int l = 0; l < lifeList.size(); l++) {
		lifeList[l].transform.y = W.GetHeight() - 40;
		lifeList[l].objectID = ObjectID::RANA;
		if (l == 0) {
			lifeList[l].transform.x = 800;
		}
		else {
			lifeList[l].transform.x = lifeList[l - 1].transform.x - 30;
		}
	}
}

void GameScene::OnExit(void) {
}

void GameScene::Update(void) {

	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

	static MouseCoords mouseCoords(0, 0);
	
	//PAUSAR EL JOC
	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) {
		if (pause) {
			pause = false;
		}
		else {
			pause = true;
		}
	}

	//INCREMENTAR VELOCITAT RESPECTE LA PUNTUACIO
	if (score != antScore) {
		scorediff = score - antScore;
		vel += scorediff / 100000.f;
		vel2 += scorediff / 100000.f;
		//std::cout << vel << std::endl;
		//std::cout << vel2 << std::endl;
		antScore = score;
	}

	if (!pause) {
		//INPUT DEL JUGADOR
		if (IM.IsKeyDown<KEY_BUTTON_UP>() && rana.transform.y > rana.transform.h) {
			rana.transform.y -= 60;
			angle = 0;
			rana.objectID = ObjectID::RANA2;
			score += 10;
		}
		else if (IM.IsKeyUp<KEY_BUTTON_UP>()) {
			rana.objectID = ObjectID::RANA;
		}
		if (IM.IsKeyDown<KEY_BUTTON_DOWN>() && rana.transform.y < W.GetHeight() - (2 * rana.transform.h)) {
			rana.transform.y += 60;
			angle = 180;
			rana.objectID = ObjectID::RANA2;
		}
		else if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) {
			rana.objectID = ObjectID::RANA;
		}
		if (IM.IsKeyDown<KEY_BUTTON_LEFT>() && rana.transform.x > rana.transform.h) {
			rana.transform.x -= 60;
			angle = 270;
			rana.objectID = ObjectID::RANA2;
		}
		else if (IM.IsKeyUp<KEY_BUTTON_LEFT>()) {
			rana.objectID = ObjectID::RANA;
		}
		if (IM.IsKeyDown<KEY_BUTTON_RIGHT>() && rana.transform.x < W.GetWidth() - (2 * rana.transform.h)) {
			rana.transform.x += 60;
			angle = 90;
			rana.objectID = ObjectID::RANA2;
		}
		else if (IM.IsKeyUp<KEY_BUTTON_RIGHT>()) {
			rana.objectID = ObjectID::RANA;
		}

		//CREAR LADYFROG
		srand(time(NULL));
		if (ladyFrogTime.count() >= timeRand && !lady && !ladyGotcha) {
			ladyFrog = new Sprite;
			ladyFrog->objectID = ObjectID::RANA_FEMENINA;
			random1 = rand() % 6 + 19;
			ladyFrog->transform.x = itemList[random1].transform.x;
			ladyFrog->transform.y = itemList[random1].transform.y;
			lady = true;
		}

		//CREAR INSECTE
		if (insecteTime.count() >= timeRand2 && !insect) {
			//std::cout << "mosca";
			random2 = rand() % 5;
			goalList[random2].insecte.objectID = ObjectID::MOSCA;
			while (goalList[random2].in) {
				if (random2 == goalList.size() - 1) {
					random2 = 0;
				}
				else random2++;
			}
			goalList[random2].insectON = true;
			insect = true;

		}

		//ELIMINAR INSECTE
		if (insecteTime.count() >= timeRand2 + 5 && insect) {
			insecteTime -= insecteTime;
			insect = false;
			goalList[random2].insectON = false;
		}

		//ELEMENTS QUE APAREIXEN SEGONS EL NIVELL
		if (nivell == 1) {
			MoveElements(itemList.size() - 2);
		}
		if (nivell >= 2) {
			itemList[25].objectID = ObjectID::COCODRILO_CERRADO;
			if (cocodrileTime.count() >= 3) {
				itemList[25].objectID = ObjectID::COCODRILO_ABIERTO;
				if (cocodrileTime.count() >= 6) {
					cocodrileTime -= cocodrileTime;
				}
			}
			MoveElements(itemList.size() - 2);
		}
		if (nivell >= 3) {
			MoveElements(itemList.size());
		}

		//COLISIONS
		i = 0;
		colision = false;
		if (nivell >= 1) {
			ColideElements(itemList.size() - 1);
		}
		else ColideElements(itemList.size());

		//ARRIVAR A LA META
		c = 0;
		while (c < goalList.size()) {
			if (rana.transform.x <= goalList[c].x + goalList[c].w && rana.transform.x + rana.transform.w >= goalList[c].x
				&& rana.transform.y <= goalList[c].y + goalList[c].h && rana.transform.y + rana.transform.h >= goalList[c].y) {
				if (!goalList[c].in) {
					rana.transform.x = W.GetWidth() / 2;
					rana.transform.y = W.GetHeight() - rana.transform.h;
					countIn++;
					goalList[c].in = true;
					if (ladyGotcha) {
						ladyFrogTime -= ladyFrogTime;
						timeRand = rand() % (maxTime - 5);
						ladyGotcha = false;
						if (goalList[c].insectON) {
							score += 1200;
							insecteTime -= insecteTime;
							insect = false;
							goalList[random2].insectON = false;
						}
						else score += 200;
					}
					else {
						if (goalList[c].insectON) {
							score += 1000;
							insecteTime -= insecteTime;
							insect = false;
							goalList[random2].insectON = false;
						}
						else score += 50;
					}
				}
			}
			c++;
		}

		//SI NO ENTRO A LA META...
		if (rana.transform.y <= 73) {
			KillFrog();
		}

		//SI CAIC A L'AIGUA...
		if (!colision && rana.transform.y < W.GetHeight() / 2 - (W.GetHeight() / 40) && rana.transform.y > 73) {
			KillFrog();
		}

		//PASSAR DE NIVELL
		if (countIn == 5) {
			score += maxTime * 2;
			score += 1000;
			nivell++;
			//std::cout << "nivell" << nivell << std::endl;
			for (int j = 0; j < goalList.size(); j++) {
				goalList[j].in = false;
			}
			countIn = 0;
		}

		//VIDES
		if (lifeList.size() == 0) {
			// guardar score
			//score = 0;
			SM.SetCurScene<RankingScene>();
			//std::cout << "ded" << std::endl;
		}

		//CRONOMETRE

		//std::cout << maxTime << std::endl;
		maxTime = lvlTime;
		std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
		actualTime += std::chrono::duration_cast<std::chrono::duration<float>>(t2 - t1) * 10;
		cocodrileTime += std::chrono::duration_cast<std::chrono::duration<float>>(t2 - t1) * 10;
		insecteTime += std::chrono::duration_cast<std::chrono::duration<float>>(t2 - t1) * 10;
		ladyFrogTime += std::chrono::duration_cast<std::chrono::duration<float>>(t2 - t1) * 10;
		tortugaTime += std::chrono::duration_cast<std::chrono::duration<float>>(t2 - t1) * 10;
		std::chrono::seconds sec(1);
		//std::cout << cocodrileTime.count() << std::endl;

		if (maxTime > 0) {
			maxTime -= actualTime.count();
		}
		if (maxTime <= 0) {
			KillFrog();
		}
	}

	if (pause) {
		if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>() && IM.GetMouseCoords().x > 342 && IM.GetMouseCoords().x < 489 && IM.GetMouseCoords().y > 283 && IM.GetMouseCoords().y < 342) {  //Apretar el boto de play
			pause = false;
			mouseCoords = IM.GetMouseCoords();
		}

		if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>() && IM.GetMouseCoords().x > 313 && IM.GetMouseCoords().x < 455 && IM.GetMouseCoords().y > 438 && IM.GetMouseCoords().y < 503) {  //Apretar el boto de play
			IM.SetQuit();																																								//SM.SetCurScene <LevelSelect>();
			mouseCoords = IM.GetMouseCoords();
		}
	}
	timer.transform.w = maxTime * 5;
	//std::cout << vel << std::endl;
}

void GameScene::Draw(void) {
	m_background.Draw(); // Render background
	barro.Draw();
	barroini.Draw();
	meta.Draw();

	if (nivell <= 2) {
		DrawElements(itemList.size() - 2);
	}
	else DrawElements(itemList.size());

	for (int j = 0; j < goalList.size(); j++) {
		goalList[j].printX = goalList[j].x - goalList[j].w / 2 + goalList[j].winnerFrog.transform.w / 4;
		goalList[j].printY = goalList[j].y - goalList[j].h / 2;
		if (goalList[j].in) {
			SDL_QueryTexture(textureData.find(ObjectID::RANA)->second, NULL, NULL, &goalList[j].winnerFrog.transform.w, &goalList[j].winnerFrog.transform.h);
			goalList[j].winnerFrog = { { goalList[j].printX, goalList[j].printY, goalList[j].winnerFrog.transform.w * 2, goalList[j].winnerFrog.transform.h * 2 }, ObjectID::RANA};
			goalList[j].winnerFrog.Draw();
		}
		if (goalList[j].insectON) {
			SDL_QueryTexture(textureData.find(ObjectID::MOSCA)->second, NULL, NULL, &goalList[j].insecte.transform.w, &goalList[j].insecte.transform.h);
			goalList[j].insecte = { { goalList[j].printX, goalList[j].printY, goalList[j].insecte.transform.w * 2, goalList[j].insecte.transform.h * 2 }, ObjectID::MOSCA };
			goalList[j].insecte.Draw();
		}
	}
	if (lady) {
		SDL_QueryTexture(textureData.find(ObjectID::RANA_FEMENINA)->second, NULL, NULL, &ladyFrog->transform.w, &ladyFrog->transform.h);
		ladyFrog->transform.w *= 2;
		ladyFrog->transform.h *= 2;
		ladyFrog->Draw();
	}

	for (int j = 0; j < lifeList.size(); j++) {
		SDL_QueryTexture(textureData.find(lifeList[j].objectID)->second, NULL, NULL, &lifeList[j].transform.w, &lifeList[j].transform.h);
		lifeList[j] = { { lifeList[j].transform.x, lifeList[j].transform.y, lifeList[j].transform.w, lifeList[j].transform.h }, lifeList[j].objectID};
		lifeList[j].Draw();
	}

	timer.Draw();
	GUI::DrawTextBlended<FontID::ARIAL>(name+ ": " + std::to_string(score),
	{ W.GetWidth() / 2 , W.GetHeight() / 2 + 10, 1, 1 },
	{ 255, 255, 255 });
	R.Rotate(rana.transform, rana.objectID, angle, flip);
	R.Rotate(rana.transform, rana.objectID, angle ,flip);
	
	//DIBUIXAR EL MENU DE PAUSA
	if (pause) {
		GUI::DrawTextShaded<FontID::ARIAL>("Resume",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
		{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
		GUI::DrawTextShaded<FontID::ARIAL>("Exit",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
		{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
	}

}

void GameScene::MoveElements(int size) {
	for (int n = 0; n < size; n++) {
		if (itemList[n].transform.x >= W.GetWidth()) {
			itemList[n].transform.x = -itemList[n].transform.w;
		}
		else if (itemList[n].transform.x <= -itemList[n].transform.w) {
			itemList[n].transform.x = W.GetWidth();
		}
		if (itemList[n].objectID == ObjectID::RALLY2) {
			itemList[n].transform.x -= static_cast<int>(vel2);
		}
		else if (itemList[n].objectID == ObjectID::RALLY1) {
			itemList[n].transform.x += static_cast<int>(vel2);
		}
		else if (itemList[n].objectID == ObjectID::NUTRIA) {
			itemList[n].transform.x += static_cast<int>(vel2);
		}
		else if (itemList[n].objectID == ObjectID::NUTRIA2) {
			itemList[n].transform.x += static_cast<int>(vel2);
		}
		else {
			if (n <= 14) {
				itemList[n].transform.x -= static_cast<int>(vel);

			}
			else itemList[n].transform.x += static_cast<int>(vel);
		}

		//MOVIMENT ladyFrog
		if (lady) {
			if (ladyFrog->transform.x >= W.GetWidth()) {
				ladyFrog->transform.x = -ladyFrog->transform.w;
			}
			else if (ladyFrog->transform.x <= -ladyFrog->transform.w) {
				ladyFrog->transform.x = W.GetWidth();
			}
			ladyFrog->transform.x = itemList[random1].transform.x + (itemList[random1].transform.w / 2);

		}

		//MOVIMENT TORTUGUES
		if (tortugaTime.count() >= 3) {
			itemList[11].objectID = ObjectID::TORTUGA3;
			itemList[12].objectID = ObjectID::TORTUGA3;
			itemList[13].objectID = ObjectID::TORTUGA3;
			itemList[14].objectID = ObjectID::TORTUGA3;
			if (tortugaTime.count() >= 6) {
				itemList[11].objectID = ObjectID::TORTUGA4;
				itemList[12].objectID = ObjectID::TORTUGA4;
				itemList[13].objectID = ObjectID::TORTUGA4;
				itemList[14].objectID = ObjectID::TORTUGA4;
				if (tortugaTime.count() >= 9) {
					itemList[11].objectID = ObjectID::TORTUGA5;
					itemList[12].objectID = ObjectID::TORTUGA5;
					itemList[13].objectID = ObjectID::TORTUGA5;
					itemList[14].objectID = ObjectID::TORTUGA5;
					if (tortugaTime.count() >= 12) {
						itemList[11].objectID = ObjectID::TORTUGA6;
						itemList[12].objectID = ObjectID::TORTUGA6;
						itemList[13].objectID = ObjectID::TORTUGA6;
						itemList[14].objectID = ObjectID::TORTUGA6;
						if (tortugaTime.count() >= 15) {
							tortugaTime -= tortugaTime;
						}
					}
				}
			}
		}
		else if (tortugaTime.count() <= 1) {
			itemList[11].objectID = ObjectID::TORTUGA;
			itemList[12].objectID = ObjectID::TORTUGA;
			itemList[13].objectID = ObjectID::TORTUGA;
			itemList[14].objectID = ObjectID::TORTUGA;
		}
		else if (tortugaTime.count() > 2) {
			itemList[11].objectID = ObjectID::TORTUGA2;
			itemList[12].objectID = ObjectID::TORTUGA2;
			itemList[13].objectID = ObjectID::TORTUGA2;
			itemList[14].objectID = ObjectID::TORTUGA2;
		}

		//MOVIMENT TRITUGUES
		if (tortugaTime.count() >= 3) {
			itemList[6].objectID = ObjectID::TRITUGA3;
			itemList[7].objectID = ObjectID::TRITUGA3;
			itemList[8].objectID = ObjectID::TRITUGA3;
			if (tortugaTime.count() >= 6) {
				itemList[6].objectID = ObjectID::TRITUGA4;
				itemList[7].objectID = ObjectID::TRITUGA4;
				itemList[8].objectID = ObjectID::TRITUGA4;
				if (tortugaTime.count() >= 9) {
					itemList[6].objectID = ObjectID::TRITUGA5;
					itemList[7].objectID = ObjectID::TRITUGA5;
					itemList[8].objectID = ObjectID::TRITUGA5;
					if (tortugaTime.count() >= 12) {
						itemList[6].objectID = ObjectID::TORTUGA6;
						itemList[7].objectID = ObjectID::TORTUGA6;
						itemList[8].objectID = ObjectID::TORTUGA6;
						if (tortugaTime.count() >= 15) {
							tortugaTime -= tortugaTime;
						}
					}
				}
			}
		}
		else if (tortugaTime.count() <= 1) {
			itemList[6].objectID = ObjectID::TRITUGA1;
			itemList[7].objectID = ObjectID::TRITUGA1;
			itemList[8].objectID = ObjectID::TRITUGA1;
		}
		else if (tortugaTime.count() > 2) {
			itemList[6].objectID = ObjectID::TRITUGA2;
			itemList[7].objectID = ObjectID::TRITUGA2;
			itemList[8].objectID = ObjectID::TRITUGA2;
		}
	}
}

void GameScene::ColideElements(int size) {
	while (i < size) {
		if (rana.transform.y > W.GetHeight() / 2 - (W.GetHeight() / 40)) {
			if (rana.transform.x <= itemList[i].transform.x + itemList[i].transform.w && rana.transform.x + rana.transform.w >= itemList[i].transform.x
				&& rana.transform.y <= itemList[i].transform.y + itemList[i].transform.h && rana.transform.y + rana.transform.h >= itemList[i].transform.y) {
				KillFrog();
				i = size;

			}
		}

		else if (rana.transform.y < W.GetHeight() / 2 - (W.GetHeight() / 40)) {
			if (rana.transform.x <= itemList[i].transform.x + itemList[i].transform.w && rana.transform.x + rana.transform.w >= itemList[i].transform.x
				&& rana.transform.y <= itemList[i].transform.y + itemList[i].transform.h && rana.transform.y + rana.transform.h >= itemList[i].transform.y && !colision) {
				rana.transform.y = itemList[i].transform.y;
				colision = true;

				//MOVIMENT DE LA GRANOTA SOBRE OBJECTES DEL RIU
				if (i <= 14) {
					rana.transform.x -= static_cast<int>(vel);
				}
				else {
					rana.transform.x += static_cast<int>(vel);
				}
				//SI ES MENJA EL ladyFrog
				if (lady) {
					if (rana.transform.x <= ladyFrog->transform.x + ladyFrog->transform.w && rana.transform.x + rana.transform.w >= ladyFrog->transform.x
						&& rana.transform.y <= ladyFrog->transform.y + ladyFrog->transform.h && rana.transform.y + rana.transform.h >= ladyFrog->transform.y) {
						ladyGotcha = true;
						lady = false;
						delete ladyFrog;
					}
				}

				//MIRAR ESTAT DE LA TORTUGA PER SABER SI CAU
				if (itemList[i].objectID == ObjectID::TORTUGA6) {
					KillFrog();;
				}

				//LA NUTRIA MATA A LA GRANOTA
				if (itemList[i].objectID == ObjectID::NUTRIA) {
					KillFrog();
				}

				//MIRAR SI EL COCODRIL ES MENJA LA GRANOTA
				if (itemList[i].objectID == ObjectID::COCODRILO_ABIERTO) {
					if (rana.transform.x >= itemList[i].transform.x + itemList[i].transform.w / 2) { //SI ESTA DE LA MEITAT CAP A LA DRETA SEL MENJA, SINO FA DE TRONC
						KillFrog();
					}
				}
				i = size;
			}
			
		}
		i++;
	}
}

void GameScene::KillFrog(){
	rana.transform.x = W.GetWidth() / 2;
	rana.transform.y = W.GetHeight() - rana.transform.h;
	lifeList.pop_back();
	maxTime = lvlTime;
	actualTime -= actualTime;
}

void GameScene::DrawElements(int size) {
	for (int i = 0; i < size; i++) {
		SDL_QueryTexture(textureData.find(itemList[i].objectID)->second, NULL, NULL, &itemList[i].transform.w, &itemList[i].transform.h);
		itemList[i] = { { itemList[i].transform.x , itemList[i].transform.y,  itemList[i].transform.w * 2, itemList[i].transform.h * 2 }, itemList[i].objectID };
		itemList[i].Draw();
	}
}

