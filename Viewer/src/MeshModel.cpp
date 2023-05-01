#include "MeshModel.h"
#include <iostream>

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name) :
    faces(faces),
    vertices(vertices),
    normals(normals),
    model_name(model_name)
{
    float MaximumX = -1 * static_cast<float>(INFINITY);
    float MinimumX = static_cast<float>(INFINITY);
    float MaximumY = -1 * static_cast<float>(INFINITY);
    float MinimumY = static_cast<float>(INFINITY);
    float MaximumZ = -1 * static_cast<float>(INFINITY);
    float MinimumZ = static_cast<float>(INFINITY);

    for (int i = 0 ; i < vertices.size(); i++)
    {
        if (vertices[i].x > MaximumX)
            MaximumX = vertices[i].x;
        if (vertices[i].x < MinimumX)
            MinimumX = vertices[i].x;

        if (vertices[i].y > MaximumY)
            MaximumY = vertices[i].y;
        if (vertices[i].y < MinimumY)
            MinimumY = vertices[i].y;

        if (vertices[i].z > MaximumZ)
            MaximumZ = vertices[i].z;
        if (vertices[i].z < MinimumZ)
            MinimumZ = vertices[i].z;
    }
    this->Max_Coordinates = glm::vec3(MaximumX, MaximumY, MaximumZ);
    this->Min_Coordinates = glm::vec3(MinimumX, MinimumY, MinimumZ);

    this->CenterPoint = glm::vec3((MaximumX + MinimumX) / 2, (MaximumY + MinimumY) / 2, (MaximumZ + MinimumZ) / 2);
}

MeshModel::~MeshModel()
{
}

const Face& MeshModel::GetFace(int index) const
{
    return faces[index];
}

int MeshModel::GetFacesCount() const
{
    return faces.size();
}

const std::string& MeshModel::GetModelName() const
{
    return model_name;
}


bool MeshModel::GetBoxstatus(){
    return Boxstatus;
}
void MeshModel::SetBoxStatus(bool status){
    Boxstatus = status;
}
bool* MeshModel::GetBoxstatusvar(){
    return &Boxstatus;
}

bool MeshModel::GetFaceNormalsStatus(){
    return FaceNormalsStatus;
}
void MeshModel::SetFaceNormalsStatus(bool status){
    FaceNormalsStatus = status;
}
bool* MeshModel::GetFaceNormalsStatusvar(){
    return &FaceNormalsStatus;
}

glm::vec3 MeshModel::GetVertices(int index){
    return vertices[index];
}

float MeshModel::GetScale(){
    return factor;
}

const int MeshModel::GetVerticesCount() const
{
    return vertices.size();
}

glm::vec3 MeshModel::GetMeshColor(){
    return MeshColor;
}



glm::vec3 MeshModel::GetModelColor(){
    return ModelColor;
}



void MeshModel::PrintVertices()
{
    for (int i = 0; i < vertices.size(); i++) {
        std::cout << "V " << vertices[i][0] << ',' << vertices[i][1] << ',' << vertices[i][2] << std::endl;
    }
}

void MeshModel::PrintFaces()
{
    for (int i = 0; i < faces.size(); i++) {
        std::cout << "f " ;
        faces[i].printFace();
    }
}

void MeshModel::setScale(float scale){
    factor = scale;
    UpdateScaligMatrix();
    UpdateMainMatrix();
}

float MeshModel::GetLocalxTranslate(){
    return xTranslateLocal;
}
float MeshModel::GetLocalyTranslate(){
    return yTranslateLocal;
}
float MeshModel::GetLocalzTranslate(){
    return zTranslateLoacl;
}

void MeshModel::setWorldxTranslate(float tx){
    xTranslateWorld = tx;
    UpdateWorldMatrix();
    UpdateMainMatrix();
}
void MeshModel::setWorldyTranslate(float ty){
    yTranslateWorld = ty;
    UpdateWorldMatrix();
    UpdateMainMatrix();
}
void MeshModel::setWorldzTranslate(float tz){
    zTranslateWorld = tz;
    UpdateWorldMatrix();
    UpdateMainMatrix();
}

void MeshModel::setLocalxTranslate(float tx){
    xTranslateLocal = tx;
    UpdateLocalMatrix();
    UpdateMainMatrix();
}
void MeshModel::setLocalyTranslate(float ty){
    yTranslateLocal = ty;
    UpdateLocalMatrix();
    UpdateMainMatrix();
}
void MeshModel::setLocalzTranslate(float tz){
    zTranslateLoacl = tz;
    UpdateLocalMatrix();
    UpdateMainMatrix();
}

float MeshModel::GetWorldxTranslate(){
    return xTranslateWorld;
}
float MeshModel::GetWorldyTranslate(){
    return yTranslateWorld;
}
float MeshModel::GetWorldzTranslate(){
    return zTranslateWorld;
}

void MeshModel::SetMeshColor(glm::vec3 color){
    MeshColor = color;
}


void MeshModel::UpdateLocalMatrix() {
    LocalMatrix = { 1, 0, 0,xTranslateLocal,
        0, 1, 0,yTranslateLocal,
        0, 0, 1, zTranslateLoacl,
        0, 0, 0, 1 };
    LocalMatrix = transpose(LocalMatrix);
}


glm::mat4x4 MeshModel::GetModelMatrix(){
    return currentMatrix;
}

void MeshModel::UpdateScaligMatrix() {
    ScalingMatrix = { factor, 0,   0,    0,
                              0, factor, 0,    0,
                              0,    0, factor, 0,
                              0,    0,   0,    1 };
}
void MeshModel::UpdatezrotatingLocalMatrix() {
    zrotatingLocalMatrix = { glm::cos(LocalzDegrees), glm::sin(LocalzDegrees), 0, 0,
                                -glm::sin(LocalzDegrees), glm::cos(LocalzDegrees), 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1 };
}
void MeshModel::UpdatexrotatingLocalMatrix() {
    xrotatingLocalMatrix = { 1, 0, 0, 0,
                              0, glm::cos(LocalxDegrees), glm::sin(LocalxDegrees), 0,
                              0, -glm::sin(LocalxDegrees), glm::cos(LocalxDegrees), 0,
                              0, 0, 0, 1 };
}
void MeshModel::UpdateyrotatingLocalMatrix() {
    yrotatingLocalMatrix = { glm::cos(LocalyDegrees), 0, -glm::sin(LocalyDegrees), 0,
                                       0, 1, 0, 0,
                                glm::sin(LocalyDegrees), 0, glm::cos(LocalyDegrees), 0,
                                      0, 0, 0, 1 };
}

void MeshModel::UpdatezrotatingWorldMatrix() {
    zrotatingWorldMatrix = { glm::cos(WorldzDegrees), glm::sin(WorldzDegrees), 0, 0,
        -glm::sin(WorldzDegrees), glm::cos(WorldzDegrees), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 };
}
void MeshModel::UpdatexrotatingWorldMatrix() {
    xrotatingWorldMatrix = { 1, 0, 0, 0,
        0, glm::cos(WorldxDegrees), glm::sin(WorldxDegrees), 0,
        0, -glm::sin(WorldxDegrees), glm::cos(WorldxDegrees), 0,
        0, 0, 0, 1 };
}
void MeshModel::UpdateyrotatingWorldMatrix() {
    yrotatingWorldMatrix = { glm::cos(WorldyDegrees), 0, -glm::sin(WorldyDegrees), 0,
        0, 1, 0, 0,
        glm::sin(WorldyDegrees), 0, glm::cos(WorldyDegrees), 0,
        0, 0, 0, 1 };
}


void MeshModel::UpdateMainMatrix(){
//   currentMatrix =  ScalingMatrix * (xrotatingLocalMatrix * yrotatingLocalMatrix * zrotatingLocalMatrix) * LocalMatrix ;
    glm::mat4x4 WorldRotation = (xrotatingWorldMatrix * yrotatingWorldMatrix * zrotatingWorldMatrix);
    glm::mat4x4 LocalRotation = (xrotatingLocalMatrix * yrotatingLocalMatrix * zrotatingLocalMatrix);

    currentMatrix = glm::transpose(WorldRotation * WorldMatrix) * LocalMatrix * LocalRotation * ScalingMatrix;

}



void MeshModel::SetZdegreeLocal(float z)
{
    this->LocalzDegrees = z;
    UpdatezrotatingLocalMatrix();
    UpdateMainMatrix();
}

void MeshModel::SetXdegreeLocal(float x)
{
    this->LocalxDegrees = x;
    UpdatexrotatingLocalMatrix();
    UpdateMainMatrix();

}

void MeshModel::SetYdegreeLocal(float y)
{
    this->LocalyDegrees = y;
    UpdateyrotatingLocalMatrix();
    UpdateMainMatrix();

}
void MeshModel::SetZdegreeWorld(float z)
{
    this->WorldzDegrees = z;
    UpdatezrotatingWorldMatrix();
    UpdateMainMatrix();
}

void MeshModel::SetXdegreeWorld(float x)
{
    this->WorldxDegrees = x;
    UpdatexrotatingWorldMatrix();
    UpdateMainMatrix();
}

void MeshModel::SetYdegreeWorld(float y)
{
    this->WorldyDegrees = y;
    UpdateyrotatingWorldMatrix();
    UpdateMainMatrix();
}

glm::vec3 MeshModel::GetNormal(int index){
    return normals[index-1];
}

void MeshModel::UpdateWorldMatrix() {
    WorldMatrix = { 1, 0, 0,xTranslateWorld,
        0, 1, 0,yTranslateWorld,
        0, 0, 1, zTranslateWorld,
        0, 0, 0, 1 };
}

glm::vec3 MeshModel::GetNormalVector(int i, int j)
{
    return this->normals[this->faces[i].GetNormalIndex(j) - 1.0f];
}

glm::vec2 MeshModel::GetMaxMinZ(glm::mat4x4 transform) {
    glm::vec2 z; // z[0] is max z , z[1] is min z
    z[0] = -1000;
    z[1] = 1000;
    for (int i = 0; i < GetVerticesCount(); i++) {
        glm::vec4 tempVec = glm::vec4(GetVertices(i),1);
        
        tempVec = transform * tempVec;


        if (tempVec[2] < z[1]) {
            z[1] = tempVec[2];
        }

        else if (tempVec[2] > z[0]) {
            z[0] = tempVec[2];
        }

    }
    return z;
}
