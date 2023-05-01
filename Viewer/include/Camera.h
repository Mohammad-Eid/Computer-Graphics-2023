#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    virtual ~Camera();

    void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);

    glm::mat4x4& GetProjectionTransformation();
    glm::mat4x4& GetViewTransformation();
    
    
    // Projection variables declaration
    float rightOrth = 1;
    float leftOrth = -1;
    float upOrth = 1;
    float downOrth = -1;

    float FruRight = 1;
    float FruLeft = -1;
    float FruUp = 1;
    float FruDown = -1;

    float Near = -10.0f;
    float Far = 10.0f;
    float Fov = 20.0f;
    
    float aspect;
    
    
    // transformation variables declaration
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
    
    
    // transfromation variables getters & setter declaration
    
    float* GetWorldxTranslate();
    float* GetWorldyTranslate();
    float* GetWorldzTranslate();
    float* GetLocalxTranslate();
    float* GetLocalyTranslate();
    float* GetLocalzTranslate();
    
    float* GetLocalzDegrees();
    float* GetLocalxDegrees();
    float* GetLocalyDegrees();
    float* GetWorldzDegrees();
    float* GetWorldxDegrees();
    float* GetWorldyDegrees();
    
    // helper fucntions
    void UpdateLocalRotationMat();
    void UpdateWorldRotationMat();
    void UpdateWorldTranslationMat();
    void UpdateLocalTranslationMat();
    void UpdateTransformMat();
    
    void SetCameraLookAt();
    void SetCameraLookAt(glm::vec3& eye, glm::vec3& at, glm::vec3& up);
    void Setorthographic();
    void SetFrustum();
    void Setperspective();
    
    void resetPosition(){
        position[0]=0.0;
        position[1]=0.0;
        position[2]=0.0;
    }
    
    void resetOrientation(){
        orientation[0]=0.0;
        orientation[1]=0.0;
        orientation[2]=-1.0;
    }
    
    
    // transformation matrices
    glm::mat4x4 Transformation= glm::mat4(1);
    glm::mat4x4 InverseCameraTransforms= glm::mat4(1);
    glm::mat4x4 LocalRotationMatrix= glm::mat4(1);
    glm::mat4x4 WorldRotationMatrix= glm::mat4(1);
    glm::mat4x4 LocalTranslationMatrix= glm::mat4(1);
    glm::mat4x4 WorldTranslationMatrix= glm::mat4(1);
    glm::mat4x4 XrotationMat= glm::mat4(1);
    glm::mat4x4 YrotationMat= glm::mat4(1);
    glm::mat4x4 ZrotationMat= glm::mat4(1);
    glm::mat4x4 XWrotationMat= glm::mat4(1);
    glm::mat4x4 YWrotationMat= glm::mat4(1);
    glm::mat4x4 ZWrotationMat= glm::mat4(1);

    
    
    // projection matrices
    glm::mat4x4 PerspectiveProjectionMatrix= glm::mat4(1);
    glm::mat4x4 FrustumProjectionMatrix= glm::mat4(1);
    glm::mat4x4 OrthogonalProjectionMatrix= glm::mat4(1);
    glm::mat4x4 LookAt= glm::mat4(1);
    
    
    // projection Variables
    glm::vec3 orientation={0.0f,0.0f,-1.0f};
    glm::vec3 uporientation ={0.0f,1.0f,0.0f};
    glm::vec3 position{0.0f,0.0f,0.0f};
    
    //other
    int Project_Mode = 0;
    int view_Mode = 0;
private:
    glm::mat4x4 view_transformation=glm::mat4(1);;
    glm::mat4x4 projection_transformation=glm::mat4(1);;
};
