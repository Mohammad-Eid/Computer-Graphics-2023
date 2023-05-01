#pragma once

#include <vector>
#include <memory>
#include "Lighting.h"
#include "Camera.h"
#include "MeshModel.h"

using namespace std;

class Scene {
public:
	Scene();

	void AddModel(const shared_ptr<MeshModel>& mesh_model);
	int GetModelCount() const;
	MeshModel& GetModel(int index) const;
	MeshModel& GetActiveModel() const;
	
	void AddCamera(const shared_ptr<Camera>& camera);
	int GetCameraCount() const;
	Camera& GetCamera(int index);
	Camera& GetActiveCamera();

	void SetActiveCameraIndex(int index);
	int GetActiveCameraIndex() const;

	void SetActiveModelIndex(int index);
	int GetActiveModelIndex() const;
    
    
    void AddLight(const shared_ptr<Lighting>& light); //adds a Light to our models vector
    int GetLightCount() const; // returns the number of Lights we have on the scene
    Lighting& GetLight(int index) const; //returns the Light in the vector[index]
    Lighting& GetActiveLight() const;//returns the Light in the vector[active_model_index]
    void SetActiveLightIndex(int index); //sets the active_Light_index
    int GetActiveLightIndex() const; //returns the active_Light_index
	
private:
	vector<shared_ptr<MeshModel>> mesh_models;
	vector<shared_ptr<Camera>> cameras;
    vector<shared_ptr<Lighting>> Lights;

	int active_camera_index = 0;
	int active_model_index = 0;
    int active_light_index = 0;
    
};
