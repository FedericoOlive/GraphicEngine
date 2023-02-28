#ifndef GAME_H
#define GAME_H
#include "SauCa.h"

class Player
{
public:
	Sprite* ssj1;
	Sprite* ssj2;
	Sprite* ssj3;
	Sprite* god;
	
	Texture* ssj1text;
	Texture* ssj2text;
	Texture* ssj3text;
	Texture* godtext;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	
	Player()
	{
		ssj1 = nullptr;
		ssj2 = nullptr;
		ssj3 = nullptr;
		god = nullptr;

		ssj1text = nullptr;
		ssj2text = nullptr;
		ssj3text = nullptr;
		godtext = nullptr;

		position = { 0,0,0 };
		rotation = { 0,0,0 };
		scale = { 0,0,0 };
	}

	~Player()
	{
		delete ssj1;
		delete ssj2;
		delete ssj3;
		delete god;
		delete ssj1text;
		delete ssj2text;
		delete ssj3text;
		delete godtext;
	}

	void Move(glm::vec3 newPos)
	{
		position = newPos;
		ssj1->SetPosition(position);
		ssj2->SetPosition(position);
		ssj3->SetPosition(position);
		god->SetPosition(position);
	}
	
	void SetScale(glm::vec3 newScale)
	{
		scale = newScale;
		ssj1->SetScale(scale);
		ssj2->SetScale(scale);
		ssj3->SetScale(scale);
		god->SetScale(scale);
	}
	
	void SetRotation(glm::vec3 newRot)
	{
		rotation = newRot;
		ssj1->SetRotation(rotation, false);
		ssj2->SetRotation(rotation, false);
		ssj3->SetRotation(rotation, false);
		god->SetRotation(rotation, false);
	}

	void CreatePlayerAssets()
	{
		position = { 640, 360, 1 };
		scale = { 400, 400, 1 };
		
		ssj1->SetColorTint(1.0f, 1.0f, 1.0f, 1.0f);
		ssj1->SetPosition(position);
		ssj1->SetScale(scale);
		ssj1->AddAnimation(0, 0, 410, 410, 6150, 410, 1);
		ssj1->AddAnimation(0, 0, 410, 410, 6150, 410, 2, 13);
		ssj1->AddAnimation(11, 0, 410, 410, 6150, 410, 1);

		ssj2->SetColorTint(1.0f, 1.0f, 1.0f, 1.0f);
		ssj2->SetPosition(position);
		ssj2->SetScale(scale);
		ssj2->AddAnimation(0, 0, 410, 410, 6970, 410, 1);
		ssj2->AddAnimation(0, 0, 410, 410, 6970, 410, 3, 17);
		ssj2->AddAnimation(16, 0, 410, 410, 6970, 410, 1);
		
		ssj3->SetColorTint(1.0f, 1.0f, 1.0f, 1.0f);
		ssj3->SetPosition(position);
		ssj3->SetScale(scale);
		ssj3->AddAnimation(0, 0, 410, 410, 10660, 410, 1);
		ssj3->AddAnimation(0, 0, 410, 410, 10660, 410, 3.2, 22);
		ssj3->AddAnimation(21, 0, 410, 410, 10660, 410, 1);
		
		god->SetColorTint(1.0f, 1.0f, 1.0f, 1.0f);
		god->SetPosition(position);
		god->SetScale(scale);
		god->AddAnimation(0, 0, 410, 410, 13120, 410, 1);
		god->AddAnimation(0, 0, 410, 410, 13120, 410, 3.2, 28);
		god->AddAnimation(28, 0, 410, 410, 13120, 410, 1);
	}
};

class Game : public BaseGame
{
private:
	Quad* floor;
	Quad* totalKi;
	Quad* actualKi;

	Player* player;
	int currentForm;
	int currentAnim;
	float ki = 0;
	bool chargeable = true;
	int indexDraw = 0;
	float multiply = 1;
	TileMap* tileMap;

public:
	void Initialize()override;
	void Inputs() override;
	void Update()override;
	void Draw()override;
	void DeInitialize() override;
	float GetRandom();
};



#endif