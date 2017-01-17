/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "System.hh"

#pragma region GAME_SCENES
#include "MenuScene.h"
#include "GameScene.hh"
#include "LevelSelect.h"
#include "RankingScene.h"
#pragma endregion TODO

//! Initializes game needs and controls the game loop
namespace GameEngine {
	//! Loads main resources such as game images and fonts
	void LoadMedia(void) {
		R.LoadFont<FontID::ARIAL>("fnt/arial.ttf", 40);
		R.LoadFont<FontID::CANDY>("fnt/candy.ttf", 50);
		R.LoadFont<FontID::FACTORY>("fnt/candsb.ttf", 80);
		R.LoadTexture<ObjectID::BARRO>("gfx/barro.png");
		R.LoadTexture<ObjectID::CAMION>("gfx/camion.png");
		R.LoadTexture<ObjectID::COCHE>("gfx/coche.png");
		R.LoadTexture<ObjectID::COCODRILO_CERRADO>("gfx/cocodrilo_cerrado.png");
		R.LoadTexture<ObjectID::COCODRILO_ABIERTO>("gfx/cocodrilo_abierto.png");
		R.LoadTexture<ObjectID::EXCAVADORA>("gfx/excavadora1.png");
		R.LoadTexture<ObjectID::META>("gfx/meta.png");
		R.LoadTexture<ObjectID::MOSCA>("gfx/mosca.png");
		R.LoadTexture<ObjectID::NUTRIA2>("gfx/nutria.png");
		R.LoadTexture<ObjectID::NUTRIA>("gfx/nutria2.png");
		R.LoadTexture<ObjectID::RALLY1>("gfx/rally1.png");
		R.LoadTexture<ObjectID::RALLY2>("gfx/rally2.png");
		R.LoadTexture<ObjectID::RANA>("gfx/rana.png");
		R.LoadTexture<ObjectID::RANA2>("gfx/rana2.png");
		R.LoadTexture<ObjectID::RANA_FEMENINA>("gfx/LadyFrog.png");
		R.LoadTexture<ObjectID::SERPIENTE>("gfx/serpiente1.png");
		R.LoadTexture<ObjectID::TITULO>("gfx/titulo.png");
		R.LoadTexture<ObjectID::TORTUGA>("gfx/tortuga.png");
		R.LoadTexture<ObjectID::TORTUGA2>("gfx/tortuga2.png");
		R.LoadTexture<ObjectID::TORTUGA3>("gfx/tortuga3.png");
		R.LoadTexture<ObjectID::TORTUGA4>("gfx/tortuga4.png");
		R.LoadTexture<ObjectID::TORTUGA5>("gfx/tortuga5.png");
		R.LoadTexture<ObjectID::TORTUGA6>("gfx/tortuga6.png");
		R.LoadTexture<ObjectID::TRITUGA1>("gfx/trituga1.png");
		R.LoadTexture<ObjectID::TRITUGA2>("gfx/trituga2.png");
		R.LoadTexture<ObjectID::TRITUGA3>("gfx/trituga3.png");
		R.LoadTexture<ObjectID::TRITUGA4>("gfx/trituga4.png");
		R.LoadTexture<ObjectID::TRITUGA5>("gfx/trituga5.png");
		R.LoadTexture<ObjectID::TRONCO_CORTO>("gfx/tronco_corto.png");
		R.LoadTexture<ObjectID::TRONCO_LARGO>("gfx/tronco_largo.png");
		R.LoadTexture<ObjectID::TRONCO_MEDIANO>("gfx/tronco_mediano.png");
		R.LoadTexture<ObjectID::TIMER>("gfx/timer.jpg");
		R.LoadTexture<ObjectID::BG_00>("gfx/frogger.jpg");
		R.LoadTexture<ObjectID::BG_GAME>("gfx/background.png");
		R.LoadTexture<ObjectID::BG_RANKING>("gfx/niggish.jpg");
	}
	//! Adds the game scenes into the Scene Manager and decides which is the first screen
	void AddScenes(void) {
		SM.AddScene<MenuScene>();
		SM.AddScene<GameScene>();
		SM.AddScene<LevelSelect>();
		SM.AddScene<RankingScene>();
		SM.SetCurScene<MenuScene>();
	}
	/** 
	 * Runs the game specifying the window's name and dimensions
	 * @tparam screenWidth Determines the window's width
	 * @tparam screenHeight Determines the window's height
	 * @param name Determines the window's title
	 */
	template<int screenWidth, int screenHeight>
	void Run(std::string &&name) {
		Window::Instance(std::move(name), screenWidth, screenHeight); // Initialize window Singleton instance for the first time
		LoadMedia(); // Loads the resource assets
		AddScenes(); // Loads the scenes
		FPSLimiter _fpsLimiter;
		_fpsLimiter = FPSLimiter(true, 60, false);
		bool m_isRunning{ true }; // Decides if the game loop is running
		Scene *&m_curScene(SM.GetCurScene()); // Defines a reference to a pointer that points to the current scene pointer (mindblown)
		while (!IM.HasQuit() && m_isRunning) { // Checks while game's still playable
			TM.FPSBegin(); // Calculates the time difference for deltaTime and FPS limiting purposes
			_fpsLimiter.startSynchronization();
			#pragma region GAME_UPDATE
				switch (m_curScene->GetState()) { // Check for the state of the screen
					case SceneState::RUNNING:	IM.Update(); m_curScene->Update(); break; // Updates the InputManager and the current scene
					case SceneState::EXIT:		m_isRunning = false; break; // Triggers an end of the game looping
					case SceneState::SLEEP: default:;

				}
			#pragma endregion
			#pragma region GAME_DRAW
				TM.FPSEnd([&]() { // Limits the FPS rendering with a lambda function as the parameter that draws the whole game
				_fpsLimiter.forceSynchronization();
					if (m_curScene->CheckState<SceneState::RUNNING>()) { // If screen object exists and its state is running
						R.Clear();			// Clear the screen buffer
						m_curScene->Draw(); // Call the draw method of the scene
						R.Render();			// Update the screen buffer with all sprites that were pushed
					}});
			#pragma endregion
		}
	}
}