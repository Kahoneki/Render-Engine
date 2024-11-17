#include <iostream>
#include "Source Files/Application/Application.h"
#include "Source Files/Application/Renderer.h"
#include "Source Files/Application/SceneManager.h"
#include "Source Files/Application/AssetManager.h"
#include "Source Files/Application/TimeManager.h"
#include "Source Files/Camera/PlayerCamera.h"
#include "Source Files/World/Drawable/Cube24.h"
#include "Source Files/World/Drawable/Plane.h"
#include "Source Files/World/Scene.h"
#include "Source Files/World/LightSource.h"
#include "Source Files/Shaders/shader.h"
#include "Source Files/Utility/RandomFunctions.h"
#include <GLM/gtx/string_cast.hpp>

int main()
{
	Application& app{ Application::getInstance() };

	//Define renderer
	Shader shader{ SHADER_PRESET::BLINN_PHONG };
	app.renderer->AddShader(&shader);
	app.renderer->SetActiveShader(0);
	app.renderer->SetClearColour(glm::vec4(0.8f, 1.0f, 1.0f, 1.0f));

	//Define scene
	Scene scene;

	PlayerCamera cam{ "Camera", nullptr };
	scene.AddRenderSource(&cam);
	scene.SetActiveRenderSource(0);

	Cube24 cube{ "Brick Cube", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f), glm::vec3(0.0f) };
	cube.material.setAmbientColour(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
	cube.material.setDiffuseColour(glm::vec4(0.75f, 0.75f, 0.75f, 1.0f));
	cube.material.setSpecularColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	cube.material.setSpecularPower(128.0f); // Specular strength
	cube.material.setRimPower(5.0f);
	cube.material.SetPropertyActive(MATERIAL_COLOUR_BIT, true);
	unsigned int brickAlbedoName{ app.assetManager.get()->addTexture("brickwall.jpg") };
	unsigned int brickNormalName{ app.assetManager.get()->addTexture("brickwall_normal.jpg") };
	cube.material.setAlbedoTextureName(brickAlbedoName);
	cube.material.setNormalTextureName(brickNormalName);
	cube.material.SetPropertyActive(MATERIAL_ALBEDO_TEXTURE_BIT, true);
	cube.material.SetPropertyActive(MATERIAL_NORMAL_TEXTURE_BIT, true);
	scene.AddDrawable(&cube);

	Plane plane{"Brick Plane", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(15.0f), glm::vec3(-90.0f, 0.0f, 0.0f) };
	plane.material.setAmbientColour(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
	plane.material.setDiffuseColour(glm::vec4(0.75f, 0.75f, 0.75f, 1.0f));
	plane.material.setSpecularColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	plane.material.setSpecularPower(128.0f); // Specular strength
	plane.material.setRimPower(5.0f);
	plane.material.SetPropertyActive(MATERIAL_COLOUR_BIT, true);
	plane.material.setAlbedoTextureName(brickAlbedoName);
	plane.material.setNormalTextureName(brickNormalName);
	plane.material.SetPropertyActive(MATERIAL_ALBEDO_TEXTURE_BIT, true);
	plane.material.SetPropertyActive(MATERIAL_NORMAL_TEXTURE_BIT, true);
	scene.AddDrawable(&plane);



	constexpr std::size_t NUM_LIGHTS{ 8 };
	LightSource* lights[NUM_LIGHTS];
	std::vector<std::string> lightNames;
	for (std::size_t i{ 0 }; i < NUM_LIGHTS; ++i) {
		lightNames.push_back(std::to_string(i));
	}
	for (int i{ 0 }; i < NUM_LIGHTS; ++i) {
		glm::vec3 specular{ randomVec3(0.0f, 1.0f) };
		lights[i] = new LightSource(
			lightNames[i].c_str(),
			randomVec3ExcludeByDistance(-18.0f, 18.0f, -15.5f, 15.5f),
			glm::vec4(specular * 0.1f, 1.0f),
			glm::vec4(specular * 0.3f, 1.0f),
			glm::vec4(specular, 1.0f),
			randomFloat((1.0f/NUM_LIGHTS) * 1000.0f, (1.0f/NUM_LIGHTS) * 2400.0f),
			nullptr
		);
		lights[i]->cube.material.SetPropertyActive(MATERIAL_COLOUR_BIT, true);
		scene.AddLightSource(lights[i]);
	}


	//Add scene to scene manager
	app.sceneManager->AddScene(&scene);
	app.sceneManager->SetActiveScene(0);
	app.sceneManager->GetActiveScene()->SetAutomaticLightUpdates(false);
	app.sceneManager->GetActiveScene()->UpdateLightSources();

	while (app.applicationRunning) {
		app.RunFrame();
		for (std::size_t i{ 0 }; i < NUM_LIGHTS; ++i) {
			lights[i]->setDiffuseColour(glm::vec4(randomVec3(0.0f, 1.0f), 1.0f));
		}
	}
}