#define _USE_MATH_DEFINES
#include <cmath>
#include <imgui/imgui.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nfd.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer.h"
#include "Scene.h"
#include "Utils.h"

using namespace glm;

/**
 * Fields
 */
bool show_demo_window = false;
bool show_another_window = false;
bool show_models_window = false;
bool show_Cameras_window = false;
bool show_lights_controls = false;
bool ColorControls = false;

bool stats = false;
bool position = false;
bool orientaion =false;
glm::vec4 clear_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.00f);
glm::vec4 mesh_color = glm::vec4(0.1f, 0.1f, 0.1f, 1.00f);
glm::vec4 lines_color = glm::vec4(0.1f, 0.1f, 0.1f, 1.00f);
glm::vec4 normals_color = glm::vec4(0.0f, 0.1f, 0.0f, 1.00f);


float TxLocal = 0;
float TyLocal = 0;
float TzLocal = 0;
float TxWorld = 0;
float TyWorld = 0;
float TzWorld = 0;
float YdegreesLocal = 0;
float XdegreesLocal=0;
float ZdegreesLocal=0;
float YdegreesWorld = 0;
float XdegreesWorld=0;
float ZdegreesWorld=0;
float scale = 1;


float Translatex = 0;
float Translatey = 0;
float Translatez = 0;


int modelIndex = 0;
int cameraIndex = 0;


/**
 * Function declarations
 */
void PrintMatrix(mat4x4 input);
static void GlfwErrorCallback(int error, const char* description);
GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);
ImGuiIO& SetupDearImgui(GLFWwindow* window);
void StartFrame();
void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io);
void Cleanup(GLFWwindow* window);
void DrawImguiMenus(ImGuiIO& io, Scene& scene);
void UpdateModelVals(MeshModel model);

/**
 * Function implementation
 */
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
    // TODO: Handle mouse scroll here
}

int main(int argc, char **argv)
{
    int windowWidth = 1280, windowHeight = 720;
    GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Mesh Viewer");
    if (!window)
        return 1;

    int frameBufferWidth, frameBufferHeight;
    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

    Renderer renderer = Renderer(frameBufferWidth, frameBufferHeight);
    Scene scene = Scene();
    Camera new_cam = Camera();
    std::shared_ptr<Camera> sharedcam = std::make_shared<Camera>(new_cam);
    scene.AddCamera(sharedcam);
    ImGuiIO& io = SetupDearImgui(window);
    glfwSetScrollCallback(window, ScrollCallback);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        StartFrame();
        DrawImguiMenus(io, scene);
        RenderFrame(window, scene, renderer, io);
    }

    Cleanup(window);
    return 0;
}

static void GlfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
    glfwSetErrorCallback(GlfwErrorCallback);
    if (!glfwInit())
        return NULL;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
                         // very importent!! initialization of glad
                         // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    return window;
}

ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();
    return io;
}

void StartFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io)
{
    ImGui::Render();
    int frameBufferWidth, frameBufferHeight;
    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    
    if (frameBufferWidth != renderer.GetViewportWidth() || frameBufferHeight != renderer.GetViewportHeight())
    {
        Renderer NewRenderer = Renderer(frameBufferWidth, frameBufferHeight);
        renderer = (NewRenderer);
        if(!frameBufferWidth || !frameBufferHeight)
        scene.GetActiveCamera().aspect = frameBufferWidth / frameBufferHeight;
        renderer.CreateBuffers(frameBufferWidth, frameBufferHeight);
        // TODO: Set new aspect ratio
    }

    if (!io.WantCaptureKeyboard)
    {
        if (scene.GetModelCount() != 0){
        // TODO: Handle keyboard events here
        if (io.KeysDown[65]) //left
        {
            TxLocal = scene.GetActiveModel().GetLocalxTranslate();
            TxLocal -= 50;
            scene.GetActiveModel().setLocalxTranslate(TxLocal);
            // A key is down
        }
        if (io.KeysDown[68])//right
        {
            TxLocal = scene.GetActiveModel().GetLocalxTranslate();
            TxLocal += 50;
            scene.GetActiveModel().setLocalxTranslate(TxLocal);
            // D key is down
        }
        if (io.KeysDown[87])//up
        {
            TyLocal = scene.GetActiveModel().GetLocalyTranslate();
            TyLocal += 50;
            scene.GetActiveModel().setLocalyTranslate(TyLocal);
            // W key is down
        }
        if (io.KeysDown[83])//down
        {
            TyLocal = scene.GetActiveModel().GetLocalyTranslate();
            TyLocal -= 50;
            scene.GetActiveModel().setLocalyTranslate(TyLocal);
            // S key is down
        }
        if (io.KeysDown[69])
        {
            TyLocal = scene.GetActiveModel().GetLocalyTranslate();
            TxLocal = scene.GetActiveModel().GetLocalxTranslate();
            TyLocal += 50;
            TxLocal += 50;
            scene.GetActiveModel().setLocalxTranslate(TxLocal);
            scene.GetActiveModel().setLocalyTranslate(TyLocal);
            // E key is down
        }
        if (io.KeysDown[81])
        {
            TyLocal = scene.GetActiveModel().GetLocalyTranslate();
            TxLocal = scene.GetActiveModel().GetLocalxTranslate();
            TyLocal += 50;
            TxLocal -= 50;
            scene.GetActiveModel().setLocalxTranslate(TxLocal);
            scene.GetActiveModel().setLocalyTranslate(TyLocal);
            // Q key is down
        }
        if (io.KeysDown[88])
        {
            TyLocal = scene.GetActiveModel().GetLocalyTranslate();
            TxLocal = scene.GetActiveModel().GetLocalxTranslate();
            TyLocal -= 50;
            TxLocal += 50;
            scene.GetActiveModel().setLocalxTranslate(TxLocal);
            scene.GetActiveModel().setLocalyTranslate(TyLocal);
            // X key is down
        }
        if (io.KeysDown[90])
        {
            TyLocal = scene.GetActiveModel().GetLocalyTranslate();
            TxLocal = scene.GetActiveModel().GetLocalxTranslate();
            TyLocal -= 50;
            TxLocal -= 50;
            scene.GetActiveModel().setLocalxTranslate(TxLocal);
            scene.GetActiveModel().setLocalyTranslate(TyLocal);
            // Z key is down
        }
        }
    }

    if (!io.WantCaptureMouse)
    {
        // TODO: Handle mouse events here
        if (io.MouseDown[0])
        {
            // Left mouse button is down
        }
    }

    renderer.ClearColorBuffer(clear_color);
    renderer.Render(scene);
    renderer.SwapBuffers();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwMakeContextCurrent(window);
    glfwSwapBuffers(window);
}

void Cleanup(GLFWwindow* window)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
    static bool ModelExtension = false;
    // Menu Bar
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open", "CTRL+O"))
            {
                nfdchar_t* outPath = NULL;
                nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
                if (result == NFD_OKAY)
                {
                    scene.AddModel(Utils::LoadMeshModel(outPath));
                    free(outPath);
                }
                else if (result == NFD_CANCEL)
                {
                }
                else
                {
                }

            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Objects"))
        {
            if (ImGui::MenuItem("Models Window"))
            {
                show_models_window = true;
            }
            if (ImGui::MenuItem("cameras Window"))
            {
                show_Cameras_window = true;
            }
            if (ImGui::MenuItem("Lights Window"))
            {
                show_lights_controls = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("World Controls")) {
            
        }
        if (ImGui::MenuItem("Lights Controls")) {
            
        }
        if (ImGui::MenuItem("Color Controls")) {
            ColorControls = true;
        }

        ImGui::EndMainMenuBar();
    }

    {
        ImGui::Begin("Main Menu");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Checkbox("demo Window", &show_demo_window);
        ImGui::Checkbox("stats Window", &stats);
        ImGui::Checkbox("Mesh Model Extensions Window", &ModelExtension);
        ImGui::ColorEdit3("Clear Color", (float*)&clear_color);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
    
    if (show_models_window)
    {
        ImGui::Begin("Model Window", &show_models_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("This window contains controls for the models");
        if(scene.GetModelCount())
        {
            int c = scene.GetModelCount();
            ImGui::Text("We have %d models.", c);

            {
                std::string modelname = scene.GetActiveModel().GetModelName();
                ImGui::Text("The active model is: %s", modelname.c_str());   // the model name doesn't show in the menu
                ImGui::Text("The active model number: %d", modelIndex);   // the model name doesn't show in the menu
                ImGui::Text("\n");
            }
            
            {
                if (ImGui::Button("Previous Model")) {// Buttons return true when clicked (most widgets return true when edited/activated)
                    modelIndex--;
                    if (modelIndex < 0) {
                        modelIndex = c - 1;
                    }
                    scene.SetActiveModelIndex(modelIndex);
                    UpdateModelVals(scene.GetActiveModel());

                }
                ImGui::SameLine();
                if (ImGui::Button("Next Model")) {// Buttons return true when clicked (most widgets return true when edited/activated)
                    modelIndex++;
                    if (modelIndex == c) {
                        modelIndex = 0;
                    }
                    scene.SetActiveModelIndex(modelIndex);
                    UpdateModelVals(scene.GetActiveModel());

                    // update all model data
                }
            }

            /*static glm::vec3 meshcolor = glm::vec3(0.0f, 0.0f, 0.0f);
            ImGui::ColorEdit3("Model color", (float*)&meshcolor);
            scene.GetActiveModel().SetMeshColor(mesh_color);*/
            

            if (ImGui::CollapsingHeader("Local"))
            {
                static bool LocalStats = false;
                ImGui::Checkbox("Local Stats", &LocalStats);

                static vec3 Scale = vec3(1.0f, 1.0f, 1.0f);
                if (ImGui::SliderFloat3("scale :", (float*)&Scale, 10, 9000)) {
                    scene.GetActiveModel().ScalingMatrix[0][0] = Scale.x;
                    scene.GetActiveModel().ScalingMatrix[1][1] = Scale.y;
                    scene.GetActiveModel().ScalingMatrix[2][2] = Scale.z;
                    scene.GetActiveModel().UpdateMainMatrix();
                    //scene.GetActiveModel().setScale(scale);
                }

                if (ImGui::SliderFloat("Translate X Local", &TxLocal, -1000, 1000)) {
                    scene.GetActiveModel().setLocalxTranslate(TxLocal);
                }
                if (ImGui::SliderFloat("Translate Y Local", &TyLocal, -1000, 1000)) {
                    scene.GetActiveModel().setLocalyTranslate(TyLocal);
                }
                if (ImGui::SliderFloat("Translate Z Local", &TzLocal, -1000, 1000)) { // todo
                    scene.GetActiveModel().setLocalzTranslate(TzLocal);
                }
                if (ImGui::SliderFloat("RotateY Local", &YdegreesLocal, -360, 360)) {
                    scene.GetActiveModel().SetYdegreeLocal(glm::radians(YdegreesLocal));
                }

                if (ImGui::SliderFloat("RotateX Local", &XdegreesLocal, -360, 360)) {
                    scene.GetActiveModel().SetXdegreeLocal(glm::radians(XdegreesLocal));
                }

                if (ImGui::SliderFloat("RotateZ Local", &ZdegreesLocal, -360, 360)) {
                    scene.GetActiveModel().SetZdegreeLocal(glm::radians(ZdegreesLocal));
                }

                if (LocalStats)
                {
                    MeshModel& Current = scene.GetActiveModel();
                    ImGui::Begin("Local Stats Window");
                    ImGui::Text("Main Matrix");
                    PrintMatrix(Current.currentMatrix);
                    ImGui::NewLine();

                    ImGui::Text("Local Translate");
                    PrintMatrix(Current.LocalMatrix);
                    ImGui::NewLine();

                    ImGui::Text("Local Scale");
                    PrintMatrix(Current.ScalingMatrix);
                    ImGui::NewLine();

                    ImGui::Text("Local Rotation");
                    mat4x4 LocalRotation = Current.xrotatingLocalMatrix * Current.yrotatingLocalMatrix * Current.zrotatingLocalMatrix;
                    PrintMatrix(LocalRotation);
                    ImGui::NewLine();

                    /*ImGui::Text("");
                    PrintMatrix();
                    ImGui::NewLine();*/

                    ImGui::End();

                }

            }
            ImGui::NewLine();
            if (ImGui::CollapsingHeader("World"))
            {
                static bool WorldStats = false;
                ImGui::Checkbox("World Stats", &WorldStats);

                if (ImGui::SliderFloat("Translate X World", &TxWorld, -1000, 1000)) {
                    scene.GetActiveModel().setWorldxTranslate(TxWorld);
                }
                if (ImGui::SliderFloat("Translate Y World", &TyWorld, -1000, 1000)) {
                    scene.GetActiveModel().setWorldyTranslate(TyWorld);
                }
                if (ImGui::SliderFloat("Translate Z World", &TzWorld, -1000, 1000)) { // todo
                    scene.GetActiveModel().setWorldzTranslate(TzWorld);
                }
                if (ImGui::SliderFloat("RotateY World", &YdegreesWorld, -360, 360)) {
                    scene.GetActiveModel().SetYdegreeWorld(glm::radians(YdegreesWorld));
                }

                if (ImGui::SliderFloat("RotateX World", &XdegreesWorld, -360, 360)) {
                    scene.GetActiveModel().SetXdegreeWorld(glm::radians(XdegreesWorld));
                }

                if (ImGui::SliderFloat("RotateZ World", &ZdegreesWorld, -360, 360)) {
                    scene.GetActiveModel().SetZdegreeWorld(glm::radians(ZdegreesWorld));
                }

                if (WorldStats)
                {
                    MeshModel& Current = scene.GetActiveModel();
                    ImGui::Begin("Local Stats Window");
                    ImGui::Text("Main Matrix");
                    PrintMatrix(Current.currentMatrix);
                    ImGui::NewLine();

                    ImGui::Text("Local Translate");
                    PrintMatrix(Current.WorldMatrix);
                    ImGui::NewLine();

                    ImGui::Text("Local Rotation");
                    PrintMatrix(Current.xrotatingLocalMatrix * Current.yrotatingLocalMatrix * Current.zrotatingLocalMatrix);
                    ImGui::NewLine();

                    /*ImGui::Text("");
                    PrintMatrix();
                    ImGui::NewLine();*/

                    ImGui::End();

                }

            }
            
            
        }
        else{
            ImGui::Text("There are no active models");
        }
        
        
        
        
        if (ImGui::Button("Close Me"))
            show_models_window = false;
        ImGui::End();
    }
    if (ColorControls){
        ImGui::Begin("Color Controls");
        if (scene.GetModelCount() != 0){
            
            ImGui::ColorEdit3("Clear color", (float*)&clear_color); // Edit 3 floats representing a color
            
            ImGui::ColorEdit3("Lines color", (float*)&lines_color); // Edit 3 floats representing a color
            
            ImGui::ColorEdit3("Model color", (float*)&mesh_color); // Edit 3 floats representing a color
            
            ImGui::ColorEdit3("Normals color", (float*)&normals_color); // Edit 3 floats representing a color
            
            scene.GetActiveModel().SetMeshColor(mesh_color);
            scene.GetActiveModel().SetLinesColor(lines_color);
            scene.GetActiveModel().SetNormalsColor(normals_color);
        }
        if (ImGui::Button("Close")) {
            ColorControls = false;
        }
        ImGui::End();
    }
    if (show_lights_controls){
         
        static glm::vec4 lightcolor;
        ImGui::Begin("Lights controls");
        if (ImGui::Button("Add Light")) {
            const Lighting& L = Lighting();
            std::shared_ptr<Lighting> light = std::make_shared<Lighting>(L);
            scene.AddLight(light);
        }
        if (scene.GetLightCount() != 0 ){

            ImGui::SliderFloat("translate Light X: ",&Translatex,-4000, 4000.0f);
            ImGui::SliderFloat("translate Light y: ",&Translatey,-4000, 4000.0f);
            ImGui::SliderFloat("translate Light z: ",&Translatez,-4000, 4000.0f);

            glm::vec3 oldpossition = scene.GetActiveLight().GetLightSourcePosition();
            
            oldpossition[0] = Translatex;
            oldpossition[1] = Translatey;
            oldpossition[2] = Translatez;

            scene.GetActiveLight().SetLightSourcePosition(oldpossition);
            ImGui::ColorEdit3("Light color", (float*)&lightcolor);
            scene.GetActiveLight().SetLightSourceColor(lightcolor);
            
        }
        if (scene.GetLightCount() != 0){
            glm::vec3 lposition = scene.GetActiveLight().LightSourcePosition;
            // shading choose
            ImGui::Checkbox("Flat Shade", &scene.GetActiveLight().FlatShading);
            ImGui::SameLine();
            ImGui::Checkbox("Gouraud Shade", &scene.GetActiveLight().GouraudShading);
            ImGui::SameLine();
            ImGui::Checkbox("Phong Shade", &scene.GetActiveLight().PhongShading);
            
            ImGui::Text(" Light position :%f  %f  %f ", lposition[0], lposition[1], lposition[2]);
            
            // shading effect
            if (scene.GetActiveLight().FlatShading){
                
                ImGui::SliderFloat("Intensity Level: ",&scene.GetActiveLight().FlatShadingIntesity, 0, 6000.0f);
            }
            if (scene.GetActiveLight().GouraudShading){
                
                ImGui::SliderFloat("Intensity Level :",&scene.GetActiveLight().GouraudShadingIntesity, 0, 6000.0f);
            }
            if (scene.GetActiveLight().PhongShading){
                
                ImGui::SliderFloat("Intensity Level:",&scene.GetActiveLight().PhongShadingIntesity, 0, 6000.0f);
            }
            
            ImGui::NewLine();
            static bool Light=false;
            static bool model=false;
            static bool DiffuseColor=false;
            static bool SpecularColor=false;
            static bool AmbientColor=false;
            static bool MDiffuseColor = false;
            static bool MSpecularColor = false;
            static bool MAmbientColor = false;
            static glm::vec4 Lightcolor=glm::vec4(1,1,1,1);
            static glm::vec4 Lightcolor2=glm::vec4(1,1,1,1);
            static glm::vec4 Lightcolor3=glm::vec4(1,1,1,1);
            static glm::vec4 Lightcolor4=glm::vec4(1,1,1,1);
            static glm::vec4 Lightcolor5=glm::vec4(1,1,1,1);
            static glm::vec4 Lightcolor6=glm::vec4(1,1,1,1);
            static glm::vec4 modelcolor=glm::vec4(1,1,1,1);
            
            ImGui::Checkbox("Light source controls", &Light);
            ImGui::SameLine();
            ImGui::Checkbox("model controls", &model);
            
            ImGui::SliderFloat("Diffuse rate: ", &scene.GetActiveModel().diffuseRate, 0, 100);
            
            if(Light){
                ImGui::Checkbox("Ambient Color", &AmbientColor);
                ImGui::SameLine();
                ImGui::Checkbox("Specular Color", &SpecularColor);
                ImGui::SameLine();
                ImGui::Checkbox("Diffuse Color", &DiffuseColor);
                if(AmbientColor){
                    ImGui::ColorEdit3("Ambient color", (float*)&Lightcolor);
                    scene.GetActiveLight().SetAmbientColor(Lightcolor);
                }
                if(SpecularColor){
                    ImGui::ColorEdit3("Specular color", (float*)&Lightcolor2);
                    scene.GetActiveLight().SetSpecularColor(Lightcolor2);
                }
                if(DiffuseColor){
                    ImGui::ColorEdit3("Diffuse color", (float*)&Lightcolor3);
                    scene.GetActiveLight().SetDiffuseColor(Lightcolor3);
                }
               
            }
            if(model){
                ImGui::Checkbox("ambient Color", &MAmbientColor);
                ImGui::SameLine();
                ImGui::Checkbox("specular Color", &MSpecularColor);
                ImGui::SameLine();
                ImGui::Checkbox("diffuse Color", &MDiffuseColor);
                if(MAmbientColor){
                    ImGui::ColorEdit3("ambient color", (float*)&Lightcolor4);
                    scene.GetActiveModel().SetAmbientColor(Lightcolor4);
                }
                if(MSpecularColor){
                    ImGui::ColorEdit3("specular color", (float*)&Lightcolor5);
                    scene.GetActiveModel().SetSpecularColor(Lightcolor5);
                }
                if(MDiffuseColor){
                    ImGui::ColorEdit3("diffuse color", (float*)&Lightcolor6);
                    scene.GetActiveModel().SetDiffuseColor(Lightcolor6);
                }
            }
            
        
        }
        if (ImGui::Button("Close")) {
            show_lights_controls = false;
        }
        ImGui::End();
    }

    if (show_Cameras_window)
    {
        Scene tempScene = scene;
        ImGui::Begin("Cameras Window", &show_Cameras_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("This window contains controls for the Cameras");
        if (ImGui::Button("Add Camera")) {
            const Camera& c = Camera();
            std::shared_ptr<Camera> cam = std::make_shared<Camera>(c);
            scene.AddCamera(cam);
        }
        if(scene.GetCameraCount() != 0){
            int c = scene.GetCameraCount();
            ImGui::Text("We have %d Cameras.", c);

            ImGui::Text("The active Camera index: %d", cameraIndex);   // the model name doesn't show in the menu
            ImGui::Text("\n");
            
            if (ImGui::Button("Previous Cam")) {// Buttons return true when clicked (most widgets return true when edited/activated)
                cameraIndex--;
                if (cameraIndex < 0) {
                    cameraIndex = c - 1;
                }
                scene.SetActiveCameraIndex(cameraIndex);
                //UpdateModelVals(scene.GetActiveModel());

            }
            ImGui::SameLine();
            if (ImGui::Button("Next Cam")) {// Buttons return true when clicked (most widgets return true when edited/activated)
                cameraIndex++;
                if (cameraIndex == c) {
                    cameraIndex = 0;
                }
                scene.SetActiveCameraIndex(cameraIndex);
            }
            if (ImGui::CollapsingHeader("View Mode"))
            {
                Camera& activeCam = scene.GetCamera(cameraIndex);

                ImGui::RadioButton("Regular Transformation", &activeCam.view_Mode, 0);
                ImGui::RadioButton("LookAt Transformation", &activeCam.view_Mode, 1);

                if (activeCam.view_Mode == 0)
                {
                    ImGui::SliderFloat("Translate X Local", activeCam.GetLocalxTranslate(), -1000, 1000);
                    ImGui::SliderFloat("Translate Y Local", activeCam.GetLocalyTranslate(), -1000, 1000);
                    ImGui::SliderFloat("Translate Z Local", activeCam.GetLocalzTranslate(), -1000, 1000);
                    ImGui::SliderFloat("Translate X World", activeCam.GetWorldxTranslate(), -1000, 1000);
                    ImGui::SliderFloat("Translate Y World", activeCam.GetWorldyTranslate(), -1000, 1000);
                    ImGui::SliderFloat("Translate Z World", activeCam.GetWorldzTranslate(), -1000, 1000);
                    ImGui::SliderFloat("Rotate X Local", activeCam.GetLocalxDegrees(), -360, 360);
                    ImGui::SliderFloat("Rotate Y Local", activeCam.GetLocalyDegrees(), -360, 360);
                    ImGui::SliderFloat("Rotate Z Local", activeCam.GetLocalzDegrees(), -360, 360);
                    ImGui::SliderFloat("Rotate X World", activeCam.GetWorldxDegrees(), -360, 360);
                    ImGui::SliderFloat("Rotate Y World", activeCam.GetWorldyDegrees(), -360, 360);
                    ImGui::SliderFloat("Rotate Z World", activeCam.GetWorldzDegrees(), -360, 360);
                    activeCam.UpdateTransformMat();
                }

                if (activeCam.view_Mode == 1)
                {
                    ImGui::SliderFloat("Position X", &tempScene.GetActiveCamera().position[0], -50, 50);
                    ImGui::SliderFloat("Position Y", &tempScene.GetActiveCamera().position[1], -50, 50);
                    ImGui::SliderFloat("Position Z", &tempScene.GetActiveCamera().position[2], -50, 50);
                  
                   if (ImGui::Button("Reset Position"))
                   {
                       tempScene.GetActiveCamera().resetPosition();
                   }
                   
                   ImGui::SliderFloat("Orientaion X", &tempScene.GetActiveCamera().orientation[0], -50, 50);
                   ImGui::SliderFloat("Orientaion Y", &tempScene.GetActiveCamera().orientation[1], -50, 50);
                   ImGui::SliderFloat("Orientaion Z", &tempScene.GetActiveCamera().orientation[2], -50, 50);
                  
                   if (ImGui::Button("Reset Orientaion")) {
                       tempScene.GetActiveCamera().resetOrientation();
                   }

                   tempScene.GetActiveCamera().SetCameraLookAt();
                }
            }

            if (ImGui::CollapsingHeader("Projection Mode"))
            {
                Camera& activeCam = scene.GetCamera(cameraIndex);
                ImGui::RadioButton("Orthographic Projection", &activeCam.Project_Mode, 0);
                if (activeCam.Project_Mode == 0)
                {
                    ImGui::SliderFloat("Ortho Right",&activeCam.rightOrth , -10, 10);
                    ImGui::SliderFloat("Ortho Up",&activeCam.upOrth , -10, 10);
                    ImGui::SliderFloat("Ortho Down",&activeCam.leftOrth , -10, 10);
                    ImGui::SliderFloat("Ortho Left",&activeCam.downOrth, -10, 10);
                    activeCam.Setorthographic();
                }
                ImGui::RadioButton("Perspective Projection", &activeCam.Project_Mode, 1);
                if (activeCam.Project_Mode == 1)
                {
                    ImGui::SliderFloat("Perspective FOV", &activeCam.Fov, -10, 10);
                    ImGui::SliderFloat("Perspective Near", &activeCam.Near, -10, 10);
                    ImGui::SliderFloat("Perspective Far", &activeCam.Far, -10, 10);
                    activeCam.Setperspective();

                }
                ImGui::RadioButton("Frustum Projection", &activeCam.Project_Mode, 2);
                if (activeCam.Project_Mode == 2)
                {
                    ImGui::SliderFloat("Frustum Right", &activeCam.FruRight, -10, 10);
                    ImGui::SliderFloat("Frustum Up", &activeCam.FruUp, -10, 10);
                    ImGui::SliderFloat("Frustum Down", &activeCam.FruDown, -10, 10);
                    ImGui::SliderFloat("Frustum Left", &activeCam.FruLeft, -10, 10);
                    ImGui::SliderFloat("Frustum Near", &activeCam.Near, -10, 10);
                    ImGui::SliderFloat("Frustum Far", &activeCam.Far, -10, 10);
                    activeCam.SetFrustum();
                }


            }
            
        }
        else{
            ImGui::Text("There are no active Cameras");
            
        }
        
        
        
        
        if (ImGui::Button("Close Me"))
            show_Cameras_window = false;
        ImGui::End();
    }
    
    if (show_demo_window)
    {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    if (stats)
    {
        ImGui::Begin("stats window");
        if (scene.GetModelCount())
        {
            MeshModel& CurrentMeshModel = scene.GetActiveModel();
            ImGui::Text("X = %f Y = %f Z = %f", CurrentMeshModel.CenterPoint.x, CurrentMeshModel.CenterPoint.y, CurrentMeshModel.CenterPoint.z);
            ImGui::NewLine();
            ImGui::Text("X = %f Y = %f Z = %f", CurrentMeshModel.TransformedCenterPoint.x, CurrentMeshModel.TransformedCenterPoint.y, CurrentMeshModel.TransformedCenterPoint.z);
        }
        if (ImGui::Button("close")) stats = false;
        ImGui::End();
    }

    if (ModelExtension)
    {
        ImGui::Begin("Mesh Model Extensions");
        MeshModel& CurrentModel = scene.GetActiveModel();
        if (ImGui::CollapsingHeader("Mesh Model Colors"))
        {
            ImGui::ColorEdit3("Mesh Model Color", (float*)&CurrentModel.MeshColor);
        }
        if (ImGui::CollapsingHeader("Mesh Model Features"))
        {
            ImGui::Checkbox("Model Local BoundingBox", &CurrentModel.Boxstatus);
            ImGui::Checkbox("Model World BoundingBox", &CurrentModel.AfterBoundingBox);
            ImGui::Checkbox("Model World Draw Lines", &CurrentModel.DrawLines);
            ImGui::Checkbox("Model World Face Normals Status", &CurrentModel.FaceNormalsStatus);
            ImGui::Checkbox("Model World Draw Normals", &CurrentModel.DrawNormals);
            ImGui::Checkbox("Model Local Axis", &CurrentModel.LocalAxis);
            ImGui::Checkbox("Model World Axis", &CurrentModel.WorldAxis);
            ImGui::Checkbox("Model Face Bounding boxes", &CurrentModel.FaceBoundingBoxStutus);
            ImGui::Checkbox("Model Solid Color", &CurrentModel.solidColor);
            ImGui::Checkbox("Model Changing Color", &CurrentModel.changingColors);
            ImGui::Checkbox("Model Gray Scale", &CurrentModel.grayScale);
            ImGui::Checkbox("Model Reflection rays", &CurrentModel.reflectionRays);


        }
        ImGui::End();

    }
}

void UpdateModelVals(MeshModel currentModel) {
     mesh_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);

     TxLocal = currentModel.GetLocalxTranslate();
     TyLocal = currentModel.GetLocalyTranslate();
     TzLocal = currentModel.GetLocalzTranslate();
     TxWorld = currentModel.GetWorldxTranslate();
     TyWorld = currentModel.GetWorldyTranslate();
     TzWorld = currentModel.GetWorldzTranslate();
     YdegreesLocal = currentModel.LocalyDegrees;
     XdegreesLocal=currentModel.LocalxDegrees;
     ZdegreesLocal=currentModel.LocalzDegrees;
     YdegreesWorld = currentModel.WorldyDegrees;
    XdegreesWorld=currentModel.WorldxDegrees;;
    ZdegreesWorld=currentModel.WorldzDegrees;;
     scale = currentModel.GetScale();
}

void PrintMatrix(mat4x4 input)
{
    for (int i = 0; i < 4; i++)
    {
        ImGui::Text("%f %f %f %f", input[i].x, input[i].y, input[i].z, input[i].w);
    }
    ImGui::NewLine();
}
