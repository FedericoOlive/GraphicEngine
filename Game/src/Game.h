#ifndef GAME_H
#define GAME_H
#include "SauCa.h"

class Game : public BaseGame
{
private:
	Transform* target = nullptr;
	float multiply = 0.5f;
	float* targetFloatModify = nullptr;
	string targetString = "";
	int currentColor = 0;

	Camera* camera = nullptr;
	Camera* cameraMinimap = nullptr;
	CharacterController* player = nullptr;
	GameObject* cubeControll = nullptr;
	GameObject* cubeContent = nullptr;
	GameObject* cube1 = nullptr;
	GameObject* cube2 = nullptr;
	GameObject* cube3 = nullptr;
	GameObject* cube4 = nullptr;
	
	SpotLight* spotlightPlayer = nullptr;
	glm::vec3 playerZoom = {0, 1, 3};

	Texture* floorTexture;
	Texture* wallRightTexture;
	Texture* wallLeftTexture;
	Texture* wallBackTexture;
	Texture* wallFrontTexture;

public:
	void Initialize()override;
	void Inputs() override;
	void Update()override;
	void DeInitialize() override;
	void Draw() override;

	void SetLights();
	void SetEnviroment();
	void AddListeners();
	void AddPlayer();
	void AddMinimap();
	void AddModels3D();

	void ChangeColorSpotLight();
	void OnMouseMove(double xPos, double yPos);
	void OnMouseScrollMovement(double xOffset, double yOffset);
	Model* AddNewModel(std::string name, std::string path, glm::vec3 pos);
	void CreateRoom(GameObject* WorldContent, glm::vec3 position, float dimension);

	void AddBSP();
};

#endif