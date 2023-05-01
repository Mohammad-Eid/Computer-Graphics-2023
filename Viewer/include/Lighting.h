//
//  Lighting.h
//  MeshViewer
//
//  Created by Mohammad EID on 13/01/2023.
//


#ifndef Lighting_h
#define Lighting_h

#include <glm/glm.hpp>

class Lighting{
public:
    Lighting()=default;
    ~Lighting()=default;
    
    
    
    // Light Source
    void SetLightSourcePosition(glm::vec3 position);
    void SetLightSourceColor(glm::vec4 color);
    
    glm::vec3 GetLightSourcePosition();
    glm::vec3 GetLightSourceColor();
    
    glm::mat4 GetLightSourceMat();
    
    glm::mat4 LocalTranslate=glm::mat4(1);
    glm::mat4 WorldTranslate=glm::mat4(1);
    
    
    
    
    void SetAmbientColor(glm::vec4 color);
    void SetSpecularColor(glm::vec4 color);
    void SetDiffuseColor(glm::vec4 color);
    
    glm::vec3 GetAmbientColor();
    glm::vec3 GetSpecularColor();
    glm::vec3 GetDiffuseColor();
    
    
    //shading
    bool FlatShading;
    bool GouraudShading;
    bool PhongShading;
    float FlatShadingIntesity = 0;
    float GouraudShadingIntesity = 0;
    float PhongShadingIntesity = 0;
    float specularDegree = 30.f;

    glm::vec3 LightSourcePosition = glm::vec3(0,0,0) ;
private:
    // Light Source
    
    glm::vec3 LightSourceColor=glm::vec3(1,1,1);
    glm::mat4 LightSourceMat=glm::mat4(1);
    
    

    
    //
    glm::vec3 AmbientColor=glm::vec3(1,1,1);
    glm::vec3 SpecularColor=glm::vec3(1,1,1);
    glm::vec3 DiffuseColor=glm::vec3(1,1,1);
};



#endif /* Lighting_h */
