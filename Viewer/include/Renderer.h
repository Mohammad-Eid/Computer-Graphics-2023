#pragma once
#include "Scene.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
using namespace glm;

class Renderer
{
public:
	Renderer(int viewportWidth, int viewportHeight);
	virtual ~Renderer();
	void Render(const Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
    void ClearZBuffer();
	int GetViewportWidth() const;
	int GetViewportHeight() const;
    void DrawMesh(MeshModel model,glm::mat4x4 transformation);
    void DrawMesh(MeshModel temp,glm::mat4x4 transformation,Camera& cam, Lighting& Light);
    void DrawBox(MeshModel model,glm::mat4x4 transform);
    void DrawFaceNormal(MeshModel model,glm::mat4x4 transformation,glm::vec3 color);
    void DrawMeshExtensions(MeshModel Object, mat4x4 input);
    void DrawTriangle(glm::vec3 ver1, glm::vec3 ver2, glm::vec3 ver3, glm::vec3 color,glm::vec3 color2,glm::vec3 color3,bool interpulation,bool filling);
    void DrawFlatTopTriangle(glm::vec3 top, glm::vec3 mid, glm::vec3 bottom, glm::vec3 color,glm::vec3 color2,glm::vec3 color3,bool interpulation,bool filling);
    void DrawFlatBottomTriangle(glm::vec3 top, glm::vec3 mid, glm::vec3 bottom, glm::vec3 color,glm::vec3 color2,glm::vec3 color3,bool interpulation,bool filling);
    bool FillZBuffer(int x, int y, float z);
    float getZ_flat_b(glm::vec3 top, glm::vec3 mid, glm::vec3 bottom, int Xmin, int Xmax, int x, int y);
    float getZ_flat_t(glm::vec3 top, glm::vec3 mid, glm::vec3 bottom, int Xmin, int Xmax, int x, int y);
    glm::vec2 Zmaxmin;
    bool PointIsValid(glm::ivec2 p, glm::ivec2 p0, glm::ivec2 p1, glm::ivec2 p2);
    float area(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3);
	void PutPixel(const int i, const int j, const glm::vec3& color);
	void DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color);
    void DrawLightSource(Lighting& lightSource);

	void CreateBuffers(int w, int h);
	void CreateOpenglBuffer();
	void InitOpenglRendering();

    float* z_buffer;
	float* color_buffer;
	int viewport_width;
	int viewport_height;
	GLuint gl_screen_tex;
	GLuint gl_screen_vtc;
};
