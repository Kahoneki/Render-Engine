#ifndef SCENE_H
#define SCENE_H

#include "SceneObject.h"

#include <vector>

class LightSource;
class RenderSource;
class Drawable;

/*Scene class - holds all the `SceneObject`s*/

class Scene
{

	friend class Renderer;

public:
	Scene();
	Scene(std::vector<LightSource*> _lightSources, std::vector<RenderSource*> _renderSources, std::vector<Drawable*> _drawables);
	~Scene();

	//If true, light sources must be updated manually with UpdateLightSources() - this can be more performant than automatic updates
	void SetAutomaticLightUpdates(bool val);
	bool GetAutomaticLightUpdates();

	std::size_t AddSceneObject(SceneObject* sceneObject); //Returns index - this function should only be used on standalone SceneObjects (if SceneObject is an instance of a derived class (e.g.: Drawable), use the appropriate function call for that type (e.g.: AddDrawable()))
	void RemoveSceneObject(std::size_t index);

	std::size_t AddLightSource(LightSource* lightSource); //Returns index
	void RemoveLightSource(std::size_t index);
	void UpdateLightSources();
	bool lightsChanged; //Used to determine whether light sources need to be updated - should be set to false when lights are changed and true when a light changes

	std::size_t AddRenderSource(RenderSource* renderSource); //Returns index
	void RemoveRenderSource(std::size_t index);
	void SetActiveRenderSource(std::size_t index);
	RenderSource* GetActiveRenderSource();

	std::size_t AddDrawable(Drawable* drawable); //Returns index
	void RemoveDrawable(std::size_t index);
	void ReorderDrawable(Drawable* drawable); //Reorders drawable in drawables vector based on drawable's new renderOrder

	std::vector<Drawable*> drawables;

private:

	bool automaticLightUpdates;

	std::vector<LightSource*> lightSources; //Can't be pointers as they need to be passed to the GPU
	unsigned int lightSourcesBuffer;

	std::vector<RenderSource*> renderSources; //E.g.: cameras
	std::size_t activeRenderSource;

	std::vector<SceneObject*> sceneObjects; //Contains all light sources, render sources, and drawables
};

#endif