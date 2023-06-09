#include "Scene.h"
#include "MeshModel.h"
#include <string>

Scene::Scene() :
	active_camera_index(0),
	active_model_index(0),
    active_light_index(0)
{

}


void Scene::AddLight(const std::shared_ptr<Lighting>& light)
{
    Lights.push_back(light);
    //active_light_index++;
}

int Scene::GetLightCount() const
{
    return int(Lights.size());
}

Lighting& Scene::GetLight(int index) const
{
    return *Lights[index];
}

Lighting& Scene::GetActiveLight() const
{
    return *Lights[active_light_index];
}

void Scene::SetActiveLightIndex(int index)
{
    active_light_index = index;
}

int Scene::GetActiveLightIndex() const
{
    return active_light_index;
}

void Scene::AddModel(const std::shared_ptr<MeshModel>& mesh_model)
{
	mesh_models.push_back(mesh_model);
}

int Scene::GetModelCount() const
{
	return mesh_models.size();
}

MeshModel& Scene::GetModel(int index) const
{
	return *mesh_models[index];
}

MeshModel& Scene::GetActiveModel() const
{
	return *mesh_models[active_model_index];
}

void Scene::AddCamera(const std::shared_ptr<Camera>& camera)
{
	cameras.push_back(camera);
}

int Scene::GetCameraCount() const
{
	return cameras.size();
}

Camera& Scene::GetCamera(int index)
{
	return *cameras[index];
}

Camera& Scene::GetActiveCamera()
{
	return *cameras[active_camera_index];
}

void Scene::SetActiveCameraIndex(int index)
{
	active_camera_index = index;
}

int Scene::GetActiveCameraIndex() const
{
	return active_camera_index;
}

void Scene::SetActiveModelIndex(int index)
{
	active_model_index = index;
}

int Scene::GetActiveModelIndex() const
{
	return active_model_index;
}
