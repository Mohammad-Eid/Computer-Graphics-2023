#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Face.h"

class MeshModel
{
public:
    MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name);
    virtual ~MeshModel();
    const Face& GetFace(int index) const;
    int GetFacesCount() const;
    const std::string& GetModelName() const;
    const int GetVerticesCount() const;
    glm::vec3 GetNormalVector(int i, int j);
    void PrintVertices();
    void PrintFaces();
    glm::vec3 GetMeshColor();
    glm::vec3 GetModelColor();
    glm::vec3 GetVertices(int index);
    void UpdateLocalMatrix();
    void UpdateWorldMatrix();
    void UpdateScaligMatrix();
    void UpdatezrotatingLocalMatrix();
    void UpdatexrotatingLocalMatrix();
    void UpdateyrotatingLocalMatrix();
    void UpdatezrotatingWorldMatrix();
    void UpdatexrotatingWorldMatrix();
    void UpdateyrotatingWorldMatrix();
    glm::vec3 GetNormal(int index);
    void UpdateMainMatrix();
    glm::mat4x4 GetModelMatrix();
    glm::vec2 GetMaxMinZ(glm::mat4x4 transform);
    
    float GetLocalxTranslate();
    float GetLocalyTranslate();
    float GetLocalzTranslate();
    
    void setLocalxTranslate(float tx);
    void setLocalyTranslate(float ty);
    void setLocalzTranslate(float tz);
    
    float GetWorldxTranslate();
    float GetWorldyTranslate();
    float GetWorldzTranslate();
    
    void setWorldxTranslate(float tx);
    void setWorldyTranslate(float ty);
    void setWorldzTranslate(float tz);
    
    void SetZdegreeLocal(float z);
    void SetXdegreeLocal(float x);
    void SetYdegreeLocal(float y);

    void SetZdegreeWorld(float z);
    void SetXdegreeWorld(float x);
    void SetYdegreeWorld(float y);
    
    void SetMeshColor(glm::vec3 color);
    
    bool GetBoxstatus();
    void SetBoxStatus(bool status);
    bool* GetBoxstatusvar();
    
    bool GetFaceNormalsStatus();
    void SetFaceNormalsStatus(bool status);
    bool* GetFaceNormalsStatusvar();
    
    void setScale(float scale);
    float GetScale();
    
    float xTranslateLocal = 0.;
    float yTranslateLocal = 0.;
    float zTranslateLoacl = 0.;
    float xTranslateWorld = 0.;
    float yTranslateWorld = 0.;
    float zTranslateWorld = 0.;
    
    float LocalzDegrees = 0.0;
    float LocalxDegrees = 0.0;
    float LocalyDegrees = 0.0;
    float WorldzDegrees = 0.0;
    float WorldxDegrees = 0.0;
    float WorldyDegrees = 0.0;
    
    float factor = 1000;
    
    bool faceNormalStatus = false;
    bool reflectionRays = false;
    bool Boxstatus = false;
    bool FaceNormalsStatus = false;
    bool DrawLines = true;
    bool DrawNormals = false;
    bool AfterBoundingBox = false;
    bool LocalAxis = false;
    bool WorldAxis = false;
    bool FaceBoundingBoxStutus =false;
    bool solidColor = false;
    bool changingColors = false;
    bool grayScale = false;
    
    void SetMeshColor(glm::vec4 color){
        ModelColor = color;
    }
    void SetLinesColor(glm::vec4 color){
        Linescolor = color;
    }
    void SetNormalsColor(glm::vec4 color){
        Normalscolor = color;
    }
    
    
    void SetAmbientColor(glm::vec4 color){
        AmbientColor = color;
    }
    void SetSpecularColor(glm::vec4 color){
        SpecularColor = color;
    }
    void SetDiffuseColor(glm::vec4 color){
        DiffuseColor = color;
    }
    
    float diffuseRate = 20.f;
    
    
    glm::vec3 AmbientColor = glm::vec3(1.f,0.f ,0.f );
    glm::vec3 DiffuseColor = glm::vec3(0.f,1.f ,0.f );
    glm::vec3 SpecularColor = glm::vec3(0.f,0.f ,1.f );
    

    glm::vec3 MeshColor = { 0.00, 0.00, 0.00 }; //black
    glm::vec3 ModelColor = { 0.00, 0.00, 0.00 }; //black
    glm::vec3 Normalscolor = { 0.00, 1.00, 0.00 }; //green
    glm::vec3 Linescolor = { 0.00, 0.00, 0.00 }; //black
    glm::vec3 CenterPoint = glm::vec3(0,0,0);
    glm::vec3 TransformedCenterPoint = glm::vec3(0, 0, 0);
    
    //Storing Edges Points
    glm::vec3 Max_Coordinates;
    glm::vec3 Min_Coordinates;

    glm::vec2 Max_Coordinates2D;
    glm::vec3 Min_Coordinates2D;

    glm::mat4 LocalMatrix = { 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 };
    
    glm::mat4 WorldMatrix = { 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 };
    glm::mat4 ScalingMatrix = { 100, 0, 0, 0,
        0, 100, 0, 0,
        0, 0, 100, 0,
        0, 0, 0, 1 };
    glm::mat4 zrotatingLocalMatrix = { glm::cos(0.0), glm::sin(0.0), 0, 0,
        -glm::sin(0.0), glm::cos(0.0), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 };
    glm::mat4 xrotatingLocalMatrix = { 1, 0, 0, 0,
        0, glm::cos(0.0), glm::sin(0.0), 0,
        0, -glm::sin(0.0), glm::cos(0.0), 0,
        0, 0, 0, 1 };
    glm::mat4 yrotatingLocalMatrix = {glm::cos(0.0), 0, -glm::sin(0.0), 0,
        0, 1, 0, 0,
        glm::sin(0.0), 0, glm::cos(0.0), 0,
        0, 0, 0, 1};

    glm::mat4 zrotatingWorldMatrix = { glm::cos(0.0), glm::sin(0.0), 0, 0,
        -glm::sin(0.0), glm::cos(0.0), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 };

    glm::mat4 xrotatingWorldMatrix = { 1, 0, 0, 0,
        0, glm::cos(0.0), glm::sin(0.0), 0,
        0, -glm::sin(0.0), glm::cos(0.0), 0,
        0, 0, 0, 1 };

    glm::mat4 yrotatingWorldMatrix = { glm::cos(0.0), 0, -glm::sin(0.0), 0,
        0, 1, 0, 0,
        glm::sin(0.0), 0, glm::cos(0.0), 0,
        0, 0, 0, 1 };
    
    glm::mat4 currentMatrix = { 1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1 };

private:
    std::vector<Face> faces;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::string model_name;
};
