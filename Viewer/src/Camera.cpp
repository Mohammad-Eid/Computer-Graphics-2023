#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>

Camera::Camera()
{
    
}

Camera::~Camera()
{
    
}

glm::mat4x4& Camera::GetProjectionTransformation()
{
    if (this->Project_Mode == 0)
    {
        projection_transformation = OrthogonalProjectionMatrix;
    }
    if (this->Project_Mode == 1)
    {
        projection_transformation = PerspectiveProjectionMatrix;
    }
    if (this->Project_Mode == 2)
    {
        projection_transformation = FrustumProjectionMatrix;
    }
    return projection_transformation;
}

glm::mat4x4& Camera::GetViewTransformation()
{
    if (this->view_Mode == 0)
    {
        this->view_transformation = glm::inverse(this->Transformation);
    }
    if (this->view_Mode == 1)
    {
        this->view_transformation = glm::inverse(this->LookAt);
    }
    return view_transformation;
}


// implemintation of transfromation variables getters & setters

float* Camera::GetWorldxTranslate(){
    return &xTranslateWorld;
}
float* Camera::GetWorldyTranslate(){
    return &yTranslateWorld;
}
float* Camera::GetWorldzTranslate(){
    return &zTranslateWorld;
}
float* Camera::GetLocalxTranslate(){
    return &xTranslateLocal;
}
float* Camera::GetLocalyTranslate(){
    return &yTranslateLocal;
}
float* Camera::GetLocalzTranslate(){
    return &zTranslateLoacl;
}

float* Camera::GetLocalzDegrees(){
    return &LocalzDegrees;
}
float* Camera::GetLocalxDegrees(){
    return &LocalxDegrees;
}
float* Camera::GetLocalyDegrees(){
    return &LocalyDegrees;
}
float* Camera::GetWorldzDegrees(){
    return &WorldzDegrees;
}
float* Camera::GetWorldxDegrees(){
    return &WorldxDegrees;
}
float* Camera::GetWorldyDegrees(){
    return &WorldyDegrees;
}



// implementation of helper functions

void Camera::UpdateLocalRotationMat(){
    XrotationMat = { 1, 0, 0, 0,
                              0, glm::cos(LocalxDegrees), glm::sin(LocalxDegrees), 0,
                              0, -glm::sin(LocalxDegrees), glm::cos(LocalxDegrees), 0,
                              0, 0, 0, 1 };
    YrotationMat = { glm::cos(LocalyDegrees), 0, -glm::sin(LocalyDegrees), 0,
                                       0, 1, 0, 0,
                                glm::sin(LocalyDegrees), 0, glm::cos(LocalyDegrees), 0,
                                      0, 0, 0, 1 };
    ZrotationMat = { glm::cos(LocalzDegrees), glm::sin(LocalzDegrees), 0, 0,
                                -glm::sin(LocalzDegrees), glm::cos(LocalzDegrees), 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1 };

    LocalRotationMatrix= XrotationMat * YrotationMat * ZrotationMat;
}
void Camera::UpdateWorldRotationMat(){
    XWrotationMat = { 1, 0, 0, 0,
                              0, glm::cos(WorldxDegrees), glm::sin(WorldxDegrees), 0,
                              0, -glm::sin(WorldxDegrees), glm::cos(WorldxDegrees), 0,
                              0, 0, 0, 1 };
    YWrotationMat = { glm::cos(WorldyDegrees), 0, -glm::sin(WorldyDegrees), 0,
                                       0, 1, 0, 0,
                                glm::sin(WorldyDegrees), 0, glm::cos(WorldyDegrees), 0,
                                      0, 0, 0, 1 };
    ZWrotationMat = { glm::cos(WorldzDegrees), glm::sin(WorldzDegrees), 0, 0,
                                -glm::sin(WorldzDegrees), glm::cos(WorldzDegrees), 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1 };

    WorldRotationMatrix= XWrotationMat * YWrotationMat * ZWrotationMat;
}
void Camera::UpdateWorldTranslationMat(){
    WorldTranslationMatrix = { 1, 0, 0,xTranslateWorld,
        0, 1, 0,yTranslateWorld,
        0, 0, 1, zTranslateWorld,
        0, 0, 0, 1 };
}
void Camera::UpdateLocalTranslationMat(){
    LocalTranslationMatrix = { 1, 0, 0,xTranslateLocal,
        0, 1, 0,yTranslateLocal,
        0, 0, 1, zTranslateLoacl,
        0, 0, 0, 1 };
}
void Camera::UpdateTransformMat(){
    UpdateLocalRotationMat();
    UpdateWorldRotationMat();
    UpdateLocalTranslationMat();
    UpdateWorldTranslationMat();
    
    Transformation = WorldTranslationMatrix * WorldRotationMatrix * LocalTranslationMatrix * LocalRotationMatrix;
    InverseCameraTransforms = glm::inverse(Transformation);
}

void Camera::SetCameraLookAt() {
    LookAt = glm::lookAt(position, orientation, uporientation);
}
void Camera::SetCameraLookAt(glm::vec3& eye, glm::vec3& at, glm::vec3& up) {
    LookAt = glm::lookAt(eye, at, up);
}

void Camera::Setorthographic() {
    OrthogonalProjectionMatrix = glm::ortho(leftOrth, rightOrth, downOrth, upOrth);
}

void Camera::SetFrustum() {
    FrustumProjectionMatrix = glm::frustum(FruLeft, FruRight, FruDown, FruUp, Near, Far);
}

void Camera::Setperspective() {
    PerspectiveProjectionMatrix = glm::perspective((Fov), aspect, Near, Far);
}
