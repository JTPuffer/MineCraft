#pragma once
#include "ResourceManager.h"
#include "camera.h"
#include "RenderChunk.h"
#include "Chunk.h"
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};


class Game
{
	RenderChunk*renderer;
	Texture diff;
	Texture spec;
public:
	// game state
	GameState State;
	bool Keys[1024];
	unsigned int width, height;
	// constructor/destructor
	Game(unsigned int width, unsigned int height);
	~Game();
	// initialize game state (load all shaders/textures/levels)
	void Init();
	// game loop
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
	Camera camera;
	std::vector<Chunk> chunks;
};
