#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>

#include "Renderer.h"
#include "InitShader.h"
#include "glm//gtx/normal.hpp"
using namespace std;

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define Z_INDEX(width,x,y) ((x)+(y)*(width))
#define power2(x) (x)*(x)
#define MatIndex(x,y) ((x)+(y)*(viewport_width))
#define KernelIndex(x,y) ((x+2)+((y+2) *5))

// global variable, created only to stop the stupid code that prints to the command prompt
int breaker = 0 ;
static int CameraProjection = 0;

Renderer::Renderer(int viewport_width, int viewport_height) :
    viewport_width(viewport_width),
    viewport_height(viewport_height)
{
    InitOpenglRendering();
    CreateBuffers(viewport_width, viewport_height);
}

Renderer::~Renderer()
{
    delete[] color_buffer;
    delete[] z_buffer;
}

void Renderer::PutPixel(int i, int j, const glm::vec3& color)
{
    if (i < 0) return; if (i >= viewport_width) return;
    if (j < 0) return; if (j >= viewport_height) return;
    
    color_buffer[INDEX(viewport_width, i, j, 0)] = color.x;
    color_buffer[INDEX(viewport_width, i, j, 1)] = color.y;
    color_buffer[INDEX(viewport_width, i, j, 2)] = color.z;
}

void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{
    // TODO: Implement bresenham algorithm
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

    //p1 is the start point
    int x1 = p1[0], x2 = p2[0], y1 = p1[1], y2 = p2[1];
    int dx = (x2 - x1);
    int dy = (y2 - y1);
    int x = x1, y = y1;
    int err;

    //if our line is on Y
    if (dx == 0) {

        if (dy > 0) {
            while (y <= y2) {
                PutPixel(x, y, color);
                y++;
            }
        }
        else {
            while (y >= y2) {
                PutPixel(x, y, color);
                y--;
            }
        }

    }


    //if our line is on X
    else if (dy == 0) {
        if (dx > 0) {
            while (x <= x2) {
                PutPixel(x, y, color);
                x++;
            }
        }
        while (x >= x2) {
            PutPixel(x, y, color);
            x--;
        }

    }

    else {
        float m; //m is our
        m = (float)dy / (float)dx;
        if (dy > 0) {
            if (m > 0 && m < 1) {
                err = -dx;
                while (x <= x2) {
                    if (err > 1 / 2) {
                        y++;
                        err = err - 2 * dx;
                    }

                    PutPixel(x, y, color);
                    x++;
                    err = err + 2 * dy;
                }
            }
            else if (m >= 1) {
                err = -dy;
                while (y <= y2) {
                    if (err > 1 / 2) {
                        x++;
                        err = err - 2 * dy;
                    }

                    PutPixel(x, y, color);
                    y++;
                    err = err + 2 * dx;
                }
            }
            else if (m <= -1) {
                err = -dy;
                while (y <= y2) {
                    if (err > 1 / 2) {
                        x--;
                        err = err - 2 * dy;
                    }

                    PutPixel(x, y, color);
                    y++;
                    err = err - 2 * dx;
                }
            }
            // if -1<m<0
            else if (m > -1 && m < 0) {
                err = -dx;
                while (x >= x2) {
                    if (err > 1 / 2) {
                        y++;
                        err = err + 2 * dx;
                    }
                    PutPixel(x, y, color);
                    x--;
                    err = err + 2 * dy;
                }
            }
        }
        else {
            // when a is between 0 and 1 and y is "-"
            if (m > 0 && m < 1) {
                err = -dx;
                while (x >= x2) {
                    if (err > 1 / 2) {
                        y--;
                        err = err + 2 * dx;
                    }

                    PutPixel(x, y, color);
                    x--;
                    err = err - 2 * dy;
                }
            }

            //when a is bigger than 1 & y is "-"
            else if (m >= 1) {
                err = -dy;
                while (y >= y2) {
                    if (err > 1 / 2) {
                        x--;
                        err = err + 2 * dy;
                    }

                    PutPixel(x, y, color);
                    y--;
                    err = err - 2 * dx;
                }
            }
            // when a is between 0 and -1 and y is "-"
            if (m < 0 && m > -1) {
                err = -dx;
                while (x <= x2) {
                    if (err > 1 / 2) {
                        y--;
                        err = err - 2 * dx;
                    }

                    PutPixel(x, y, color);
                    x++;
                    err = err - 2 * dy;
                }
            }

            //when a is smaller than -1 & y is "-"
            else if (m <= -1) {
                err = -dy;
                while (y >= y2) {
                    if (err > 1 / 2) {
                        x++;
                        err = err + 2 * dy;
                    }

                    PutPixel(x, y, color);
                    y--;
                    err = err + 2 * dx;
                }
            }
        }

    }

}

void Renderer::DrawBox(MeshModel model,glm::mat4x4 transform){
    
    
    float Xmax = 0;
    float Zmax = 0;
    float Ymax = 0;
    float Xmin = 0;
    float Ymin = 0;
    float Zmin = 0;
    for(int i=0 ; i < model.GetVerticesCount() ; i++){
        glm::vec3 Vertices = model.GetVertices(i);
        
            if (Vertices[0] < Xmin ){
                Xmin = Vertices[0];
            }
            else if (Vertices[0] > Xmax ){
                Xmax = Vertices[0];
            }
                else if (Vertices[1] < Ymin ){
                Ymin = Vertices[1];
            }

                else if (Vertices[1] > Ymax ){
                Ymax = Vertices[1];
            }

                else if (Vertices[2] < Zmin ){
                Zmin = Vertices[2];
            }

                else if (Vertices[2] > Zmax ){
                Zmax = Vertices[2];
            }
    
    }
    
    // defining 8 points for the 8 vertices of the box
    glm::vec4 point1,point2,point3,point4,point5,point6,point7,point8;
    
    point1 =   glm::vec4(Xmin, Ymin, Zmin,1) * transform;
    point2 =   glm::vec4(Xmin, Ymin, Zmax,1) * transform;
    point3 =   glm::vec4(Xmin, Ymax, Zmin,1) * transform;
    point4 =   glm::vec4(Xmin, Ymax, Zmax,1) * transform;
    point5 =   glm::vec4(Xmax, Ymin, Zmin,1) * transform;
    point6 =   glm::vec4(Xmax, Ymin, Zmax,1) * transform;
    point7 =   glm::vec4(Xmax, Ymax, Zmin,1) * transform;
    point8 =   glm::vec4(Xmax, Ymax, Zmax,1) * transform;
    
    
    
    // chosen color for the Bounding Box
    glm::vec3 pink = glm::vec3(1.0f, 0.0f, 1.0f);



    
}

void Renderer::DrawFaceNormal(MeshModel model,glm::mat4x4 transformation,glm::vec3 color){
    

    
    for (int i=0; i < model.GetFacesCount();i++){
       Face tempFace = model.GetFace(i);
        

        glm::mat4 factor(50);

        glm::vec4 startPoint1(model.GetVertices(tempFace.GetVertexIndex(0)-1),1.0f);
        glm::vec4 startPoint2(model.GetVertices(tempFace.GetVertexIndex(1)-1),1.0f);
        glm::vec4 startPoint3(model.GetVertices(tempFace.GetVertexIndex(2)-1),1.0f);
        
        model.UpdateMainMatrix();
        
        startPoint1 = startPoint1 * transformation;
        startPoint2 = startPoint2 * transformation;
        startPoint3 = startPoint3 * transformation;

        
        glm::vec3 normal = glm::triangleNormal(glm::vec3(startPoint1), glm::vec3(startPoint2), glm::vec3(startPoint3));

        glm::vec4 startpoint;
        startpoint[0] = ((startPoint1[0] + startPoint2[0] + startPoint3[0])) / 3;
        startpoint[1] = ((startPoint1[1] + startPoint2[1] + startPoint3[1])) / 3;
        startpoint[2] = ((startPoint1[2] + startPoint2[2] + startPoint3[2])) / 3;
        glm::vec4 endpoint = startpoint + (glm::vec4(normal,0.f)*factor);
        
        Renderer::DrawLine(startpoint, endpoint, color);
    }
}

void Renderer::CreateBuffers(int w, int h)
{
    CreateOpenglBuffer(); //Do not remove this line.
    color_buffer = new float[3 * w * h];
    z_buffer = new float[3 * w * h];
    ClearColorBuffer(glm::vec3(0.0f, 0.0f, 0.0f));
    ClearZBuffer();
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::InitOpenglRendering()
{
    // Creates a unique identifier for an opengl texture.
    glGenTextures(1, &gl_screen_tex);

    // Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
    glGenVertexArrays(1, &gl_screen_vtc);

    GLuint buffer;

    // Makes this VAO the current one.
    glBindVertexArray(gl_screen_vtc);

    // Creates a unique identifier for a buffer.
    glGenBuffers(1, &buffer);

    // (-1, 1)____(1, 1)
    //         |\  |
    //         | \ | <--- The exture is drawn over two triangles that stretch over the screen.
    //         |__\|
    // (-1,-1)    (1,-1)
    const GLfloat vtc[]={
        -1, -1,
         1, -1,
        -1,  1,
        -1,  1,
         1, -1,
         1,  1
    };

    const GLfloat tex[]={
        0,0,
        1,0,
        0,1,
        0,1,
        1,0,
        1,1};

    // Makes this buffer the current one.
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // This is the opengl way for doing malloc on the gpu.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vtc)+sizeof(tex), NULL, GL_STATIC_DRAW);

    // memcopy vtc to buffer[0,sizeof(vtc)-1]
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

    // memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

    // Loads and compiles a sheder.
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );

    // Make this program the current one.
    glUseProgram(program);

    // Tells the shader where to look for the vertex position data, and the data dimensions.
    GLint  vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition,2,GL_FLOAT,GL_FALSE,0,0 );

    // Same for texture coordinates data.
    GLint  vTexCoord = glGetAttribLocation( program, "vTexCoord" );
    glEnableVertexAttribArray( vTexCoord );
    glVertexAttribPointer( vTexCoord,2,GL_FLOAT,GL_FALSE,0,(GLvoid *)sizeof(vtc) );

    //glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

    // Tells the shader to use GL_TEXTURE0 as the texture id.
    glUniform1i(glGetUniformLocation(program, "texture"),0);
}

void Renderer::CreateOpenglBuffer()
{
    // Makes GL_TEXTURE0 the current active texture unit
    glActiveTexture(GL_TEXTURE0);

    // Makes glScreenTex (which was allocated earlier) the current texture.
    glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

    // malloc for a texture on the gpu.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewport_width, viewport_height, 0, GL_RGB, GL_FLOAT, NULL);
    glViewport(0, 0, viewport_width, viewport_height);
}

void Renderer::SwapBuffers()
{
    // Makes GL_TEXTURE0 the current active texture unit
    glActiveTexture(GL_TEXTURE0);

    // Makes glScreenTex (which was allocated earlier) the current texture.
    glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

    // memcopy's colorBuffer into the gpu.
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewport_width, viewport_height, GL_RGB, GL_FLOAT, color_buffer);

    // Tells opengl to use mipmapping
    glGenerateMipmap(GL_TEXTURE_2D);

    // Make glScreenVtc current VAO
    glBindVertexArray(gl_screen_vtc);

    // Finally renders the data.
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
    for (int i = 0; i < viewport_width; i++)
    {
        for (int j = 0; j < viewport_height; j++)
        {
            PutPixel(i, j, color);
        }
    }
}

void Renderer::Render(const Scene& scene)
{
    // TODO: Replace this code with real scene rendering code
    int half_width = viewport_width / 2;
    int half_height = viewport_height / 2;
    ClearZBuffer();
    Zmaxmin[0]=0;
    Zmaxmin[1]=0;
    Scene tempScene = scene;
    if (scene.GetCameraCount())
    {
        Camera& CurrentCam = tempScene.GetActiveCamera();
        glm::mat4x4 CameraSetUp = CurrentCam.GetViewTransformation() * CurrentCam.GetProjectionTransformation();
        CameraProjection = CurrentCam.Project_Mode;
        if (scene.GetModelCount() != 0) {
            for (int i = 0; i < scene.GetModelCount(); i++) {
                
                MeshModel& model = scene.GetModel(i);
                glm::mat4 transform = CameraSetUp * model.GetModelMatrix();
                model.TransformedCenterPoint = glm::vec3(transform * glm::vec4(model.CenterPoint, 1.0f));
                glm::vec2 Zvals = model.GetMaxMinZ(transform);
                if(Zvals[0] > Zmaxmin[0] ){
                    Zmaxmin[0] =Zvals[0];
                }
                if(Zvals[1] < Zmaxmin[1] ){
                    Zmaxmin[1] =Zvals[1];
                }
                
                if(scene.GetLightCount() != 0){
                    DrawLightSource(scene.GetActiveLight());
                    DrawMesh(model, transform, CurrentCam , scene.GetActiveLight());

                }
                else{
                DrawMesh(model, transform);
                }
                
                
                
                if (scene.GetModel(i).WorldAxis)
                {
                    
                    float AxisLength = 200.0f;
                    vec3 X_Axis = vec3(1.0f, 0.0f, 0.0f);
                    vec3 Y_Axis = vec3(0.0f, 1.0f, 0.0f);
                    vec3 Z_Axis = vec3(0.0f, 0.0f, 1.0f);

                    X_Axis = vec3(CameraSetUp * vec4(X_Axis, 0.0f));
                    Y_Axis = vec3(CameraSetUp * vec4(Y_Axis, 0.0f));
                    Z_Axis = vec3(CameraSetUp * vec4(Z_Axis, 0.0f));

                    X_Axis = normalize(X_Axis);
                    Y_Axis = normalize(Y_Axis);
                    Z_Axis = normalize(Z_Axis);

                    DrawLine(scene.GetModel(i).TransformedCenterPoint, scene.GetModel(i).TransformedCenterPoint + X_Axis * AxisLength, vec3(1.0f, 0.0f, 0.0f));
                    DrawLine(scene.GetModel(i).TransformedCenterPoint, scene.GetModel(i).TransformedCenterPoint + Y_Axis * AxisLength, vec3(0.0f, 1.0f, 0.0f));
                    DrawLine(scene.GetModel(i).TransformedCenterPoint, scene.GetModel(i).TransformedCenterPoint + Z_Axis * AxisLength, vec3(0.0f, 0.0f, 1.0f));
                }
            }
        }
        
    }
}

int Renderer::GetViewportWidth() const
{
    return viewport_width;
}

int Renderer::GetViewportHeight() const
{
    return viewport_height;
}

void Renderer::DrawMeshExtensions(MeshModel Object, mat4x4 input)
{
    if (Object.Boxstatus)
    {
        DrawBox(Object, input);
    }
    if (Object.FaceNormalsStatus)
    {
        DrawFaceNormal(Object,input,glm::vec3(1.0f,1.0f,1.0f));
    }

}





void Renderer::DrawMesh(MeshModel model,glm::mat4x4 transformation)
{
    float MaximumXTransformed = -1 * static_cast<float>(INFINITY);
    float MinmumXTransformed = static_cast<float>(INFINITY);

    float MaximumYTransformed = -1 * static_cast<float>(INFINITY);
    float MinmumYTransformed = static_cast<float>(INFINITY);

    vec3 ver1, ver2, ver3;
        // load the desired mesh color from the meshmodel class
        glm::vec3 Linescolor = model.GetMeshColor();
        glm::vec3 Modelcolor = model.GetMeshColor();
        // loop that goes throught the faces of the current model
    for (int i = 0; i < model.GetFacesCount(); i++) {
        
        // vector that will hold the indecies of the vertexes each face
        glm::ivec3 tempvertices;
        
        // in each face we load the indecies of the face into a temporary vector
        for (int j = 0; j < 3; j++) {
            tempvertices[j] = model.GetFace(i).GetVertexIndex(j);
        }
        
        // we normalize each vector so it would be a vec4
        glm::vec4 vertex1 = glm::vec4(model.GetVertices(tempvertices[0] - 1), 1.0);
        glm::vec4 vertex2 = glm::vec4(model.GetVertices(tempvertices[1] - 1), 1.0);
        glm::vec4 vertex3 = glm::vec4(model.GetVertices(tempvertices[2] - 1), 1.0);
        
        vertex1 = transformation * vertex1;
        vertex2 = transformation * vertex2;
        vertex3 = transformation * vertex3;
        
        
        float minX = std::min(vertex1[0],std::min(vertex2[0],vertex3[0]));
        float minY = std::min(vertex1[1],std::min(vertex2[1],vertex3[1]));
        float maxX = std::max(vertex1[0],std::max(vertex2[0],vertex3[0]));
        float maxY = std::max(vertex1[1],std::max(vertex2[1],vertex3[1]));
        
        
        
        if (CameraProjection != 1)
        {
            ver1 = vertex1 / vertex1.w;
            ver2 = vertex2 / vertex2.w;
            ver3 = vertex3 / vertex3.w;
        }
        else
        {
            ver1 = vec3(vertex1[0], vertex1[1], vertex1[2]);
            ver2 = vec3(vertex2[0], vertex2[1], vertex1[2]);
            ver3 = vec3(vertex3[0], vertex3[1], vertex1[2]);
        }
        
        MaximumXTransformed = std::max(MaximumXTransformed, std::max(ver1.x, std::max(ver2.x, ver3.x)));
        MaximumYTransformed = std::max(MaximumYTransformed, std::max(ver1.y, std::max(ver2.y, ver3.y)));
        
        MinmumXTransformed = std::min(MinmumXTransformed, std::min(ver1.x, std::min(ver2.x, ver3.x)));
        MinmumYTransformed = std::min(MinmumYTransformed, std::min(ver1.y, std::min(ver2.y, ver3.y)));
        
        
        // triangle drawing --------- the triangle of each face
        if (model.DrawLines)
        {
            DrawLine(ver1, ver2, Linescolor);
            DrawLine(ver2, ver3, Linescolor);
            DrawLine(ver3, ver1, Linescolor);
        }
        if (model.FaceBoundingBoxStutus){
            
//            float R_Color = (rand() % (100));
//            float G_Color = (rand() % (100));
//            float B_Color = (rand() % (100));
//
//            R_Color = R_Color / 100 ;
//            G_Color = G_Color / 100 ;
//            B_Color = B_Color / 100 ;
            
            
            float temp = z_buffer[int(ver1[0]) + int(ver1[1]) * viewport_width];
            float gray = ( temp - Zmaxmin[1]) / (1 * (Zmaxmin[0] - Zmaxmin[1]));
            gray = 1 - gray;
            
            glm::vec3 Boxcolor(gray, gray, gray);

            //glm::vec3 Boxcolor (R_Color, G_Color, B_Color);
            
            
            DrawLine(glm::vec2(minX,minY), glm::vec2(minX,maxY), Boxcolor);
            DrawLine(glm::vec2(minX,minY), glm::vec2(maxX,minY), Boxcolor);
            DrawLine(glm::vec2(minX,maxY), glm::vec2(maxX,maxY), Boxcolor);
            DrawLine(glm::vec2(maxX,minY), glm::vec2(maxX,maxY), Boxcolor);
        }
        if (model.solidColor) {
            DrawTriangle(ver1, ver2, ver3, Modelcolor,Modelcolor,Modelcolor,false, false);
        }
        if (model.changingColors) {
            float R_Color = (rand() % (100));
            float G_Color = (rand() % (100));
            float B_Color = (rand() % (100));

            R_Color = R_Color / 100;
            G_Color = G_Color / 100;
            B_Color = B_Color / 100;

            glm::vec3 RandomColor(R_Color, G_Color, B_Color);
            DrawTriangle(ver1, ver2, ver3, RandomColor ,RandomColor,RandomColor,false, false);
        }
        if (model.grayScale) {
            DrawTriangle(ver1, ver2, ver3, Modelcolor,Modelcolor,Modelcolor,false, true);
        }
        if (model.Boxstatus)
        {
            glm::vec3 pink = glm::vec3(1.0f, 0.0f, 1.0f);
            
            
            vec3 Point1 = vec3(model.Min_Coordinates[0], model.Min_Coordinates[1], model.Min_Coordinates[2]);
            vec3 Point2 = vec3(model.Min_Coordinates[0], model.Min_Coordinates[1], model.Max_Coordinates[2]);
            vec3 Point3 = vec3(model.Min_Coordinates[0], model.Max_Coordinates[1], model.Min_Coordinates[2]);
            vec3 Point4 = vec3(model.Min_Coordinates[0], model.Max_Coordinates[1], model.Max_Coordinates[2]);
            
            vec3 Point5 = vec3(model.Max_Coordinates[0], model.Min_Coordinates[1], model.Min_Coordinates[2]);
            vec3 Point6 = vec3(model.Max_Coordinates[0], model.Min_Coordinates[1], model.Max_Coordinates[2]);
            vec3 Point7 = vec3(model.Max_Coordinates[0], model.Max_Coordinates[1], model.Min_Coordinates[2]);
            vec3 Point8 = vec3(model.Max_Coordinates[0], model.Max_Coordinates[1], model.Max_Coordinates[2]);
            
            
            Point1 = vec3(transformation * vec4(Point1, 1.0f));
            Point2 = vec3(transformation * vec4(Point2, 1.0f));
            Point3 = vec3(transformation * vec4(Point3, 1.0f));
            Point4 = vec3(transformation * vec4(Point4, 1.0f));
            Point5 = vec3(transformation * vec4(Point5, 1.0f));
            Point6 = vec3(transformation * vec4(Point6, 1.0f));
            Point7 = vec3(transformation * vec4(Point7, 1.0f));
            Point8 = vec3(transformation * vec4(Point8, 1.0f));
            
            DrawLine(glm::vec2(Point2), glm::vec2(Point4), pink);
            DrawLine(glm::vec2(Point1), glm::vec2(Point2), pink);
            DrawLine(glm::vec2(Point4), glm::vec2(Point3), pink);
            DrawLine(glm::vec2(Point3), glm::vec2(Point1), pink);
            
            DrawLine(glm::vec2(Point4), glm::vec2(Point8), pink);
            DrawLine(glm::vec2(Point8), glm::vec2(Point7), pink);
            DrawLine(glm::vec2(Point7), glm::vec2(Point3), pink);
            DrawLine(glm::vec2(Point7), glm::vec2(Point5), pink);
            
            DrawLine(glm::vec2(Point5), glm::vec2(Point1), pink);
            DrawLine(glm::vec2(Point5), glm::vec2(Point6), pink);
            DrawLine(glm::vec2(Point6), glm::vec2(Point2), pink);
            DrawLine(glm::vec2(Point6), glm::vec2(Point8), pink);
            
            
        }
        if (model.FaceNormalsStatus)
        {
            float VectorLength = 50.0f;
            vec3 FaceColor = vec3(0.7f, 0.5f, 0.3f);
            vec3 FaceNormal = triangleNormal((vec3)vertex1, (vec3)vertex2, (vec3)vertex3);
            vec3 FaceCenter = (ver1 + ver2 + ver3) / 3.0f;
            
            //FaceCenter = transformation * vec4(FaceCenter,1.0f);
            
            //FaceNormal = normalize(FaceNormal);
            
            DrawLine(FaceCenter, FaceCenter + VectorLength * FaceNormal, FaceColor);
        }
        if (model.DrawNormals)
        {
            float LengthVector = 50.0f;
            vec3 Normal1 = model.GetNormalVector(i, 0);
            vec3 Normal2 = model.GetNormalVector(i, 1);
            vec3 Normal3 = model.GetNormalVector(i, 2);
            
            Normal1 = vec3(transformation * vec4(Normal1, 1.0f));
            Normal2 = vec3(transformation * vec4(Normal2, 1.0f));
            Normal3 = vec3(transformation * vec4(Normal3, 1.0f));
            
            Normal1 = normalize(Normal1);
            Normal2 = normalize(Normal2);
            Normal3 = normalize(Normal3);
            
            
            DrawLine(ver1, ver1 + LengthVector * Normal1, vec3(1.0f, 0.3, 0.7));
            DrawLine(ver2, ver2 + LengthVector * Normal2, vec3(1.0f, 0.3, 0.7));
            DrawLine(ver3, ver3 + LengthVector * Normal3, vec3(1.0f, 0.3, 0.7));
        }
        
    }
    
    if (model.AfterBoundingBox)
      
    {
        vec3 BoundingBoxColor = vec3(0.3f, 0.5f, 0.7f);
        
        vec2 Point1 = glm::vec2(MinmumXTransformed, MinmumYTransformed);
        vec2 Point2 = glm::vec2(MinmumXTransformed, MaximumYTransformed);
        vec2 Point3 = glm::vec2(MaximumXTransformed, MinmumYTransformed);
        vec2 Point4 = glm::vec2(MaximumXTransformed, MaximumYTransformed);
        
        DrawLine(Point1, Point2, BoundingBoxColor);
        DrawLine(Point1, Point3, BoundingBoxColor);
        DrawLine(Point4, Point2, BoundingBoxColor);
        DrawLine(Point4, Point3, BoundingBoxColor);
        
        
    }

        if (model.LocalAxis)
        {
            float AxisLength = 200.0f;
            vec3 X_Axis = vec3(1.0f, 0.0f, 0.0f);
            vec3 Y_Axis = vec3(0.0f, 1.0f, 0.0f);
            vec3 Z_Axis = vec3(0.0f, 0.0f, 1.0f);

            X_Axis = vec3(transformation * vec4(X_Axis, 0.0f));
            Y_Axis = vec3(transformation * vec4(Y_Axis, 0.0f));
            Z_Axis = vec3(transformation * vec4(Z_Axis, 0.0f));

            X_Axis = normalize(X_Axis);
            Y_Axis = normalize(Y_Axis);
            Z_Axis = normalize(Z_Axis);

            DrawLine(model.TransformedCenterPoint, model.TransformedCenterPoint + X_Axis * AxisLength, vec3(1.0f, 1.0f, 0.0f));
            DrawLine(model.TransformedCenterPoint, model.TransformedCenterPoint + Y_Axis * AxisLength, vec3(0.0f, 1.0f, 1.0f));
            DrawLine(model.TransformedCenterPoint, model.TransformedCenterPoint + Z_Axis * AxisLength, vec3(1.0f, 0.0f, 1.0f));

        }
    
    
    
        

}





void Renderer::DrawTriangle(glm::vec3 ver1, glm::vec3 ver2, glm::vec3 ver3, glm::vec3 color,glm::vec3 color2,glm::vec3 color3,bool interpulation,bool filling){
   
    glm::vec3& top = ver1;
    glm::vec3& bottom = ver2;
    glm::vec3& mid = ver3;
 
    if (mid.y < bottom.y){
        swap(mid,bottom);
    }
    if(top.y < mid.y){
        swap(top,mid);
    }
    if (mid.y < bottom.y){
        swap(mid, bottom);
    }
    
    if (top.y == mid.y ){ // flat top
        if(mid.x < top.x){
            glm::vec3 temp = top ;
            top = mid;
            mid = temp;
        }
        DrawFlatTopTriangle(top, mid, bottom, color,color2,color3,interpulation, filling);
    }
    else if (mid.y == bottom.y){ // flat bottom
        if(bottom.x < mid.x){
            glm::vec3 temp = bottom;
            bottom = mid;
            mid = temp;
        }
        DrawFlatBottomTriangle(top, mid, bottom, color,color2,color3,interpulation, filling);
    }
    else {
        float t = (top.y - mid.y) / (top.y - bottom.y);
        glm::vec3 vi;
        // finding the splitting point with the linear interpulation technique
        vi = ((1 - t) * top) + (t * bottom);
        if (mid.x < vi.x) {
            DrawFlatBottomTriangle(top, mid, vi, color,color2,color3,interpulation, filling);
            DrawFlatTopTriangle(mid, vi, bottom, color,color2,color3,interpulation, filling);
        }
        else {
            DrawFlatBottomTriangle(top, vi, mid, color,color2,color3,interpulation, filling);
            DrawFlatTopTriangle(vi, mid, bottom, color,color2,color3,interpulation, filling);
        }
    }

}

void Renderer::DrawFlatTopTriangle(glm::vec3 top, glm::vec3 mid, glm::vec3 bottom, glm::vec3 color,glm::vec3 color2,glm::vec3 color3,bool interpulation,bool filling) {
    float mMidBottom = (mid.x - bottom.x) / (mid.y - bottom.y);
    float mTopBottom = (top.x - bottom.x) / (top.y - bottom.y);

    int yMax = (int)ceil(top.y - 0.5f);
    int yMin = (int)ceil(bottom.y - 0.5f);

    for (int i = yMin; i < yMax; i++) {

        float leftX = mTopBottom * (float(i) + 0.5f - top.y) + top.x;
        float rightX = mMidBottom * (float(i) + 0.5f - mid.y) + mid.x;

        int xMax = (int)ceil(rightX - 0.5f);
        int xMin = (int)ceil(leftX - 0.5f);

        for (int j = xMin; j < xMax; j++) {
            float tempZ = getZ_flat_t(top, mid, bottom, xMin, xMax, j, i);
            if (filling) {
                
                if (FillZBuffer(j, i, tempZ)) {
                    float temp = z_buffer[j + i * viewport_width];
                    float gray = ( temp - Zmaxmin[1]) / (1 * (Zmaxmin[0] - Zmaxmin[1]));
                    gray = 1 - gray;
                    glm::vec3 grayscale(gray, gray, gray);
                    PutPixel(j, i, grayscale);
                }
            }
            else if (interpulation){
//                glm::vec3 color_ = getPixelColor(j,i,top,mid,bottom,color,color2,color3);
                PutPixel(j, i, color);
            }
            else {
                if (FillZBuffer(j, i, tempZ)){
                PutPixel(j, i, color);
                }
            }
        }
    }
}

void Renderer::DrawFlatBottomTriangle(glm::vec3 top, glm::vec3 mid, glm::vec3 bottom, glm::vec3 color,glm::vec3 color2,glm::vec3 color3,bool interpulation,bool filling) {
    float mTopMid = (mid.x - top.x) / (mid.y - top.y);
    float mTopBottom = (top.x - bottom.x) / (top.y - bottom.y);

    int yMax = (int)ceil(top.y - 0.5f);
    int yMin = (int)ceil(bottom.y - 0.5f);

    for (int i = yMin; i < yMax; i++) {

        float leftX = mTopMid * (float(i) + 0.5f - mid.y) + mid.x;
        float rightX = mTopBottom * (float(i) + 0.5f - bottom.y) + bottom.x;

        int xMax = (int)ceil(rightX - 0.5f);
        int xMin = (int)ceil(leftX - 0.5f);

        for (int j = xMin; j < xMax; j++) {
            float tempZ = getZ_flat_b(top, mid, bottom, xMin, xMax, j, i);
            if (filling) {
                
                if (FillZBuffer(j, i, tempZ)) {
                    float temp = z_buffer[j + i * viewport_width];
                    float gray = ( temp - Zmaxmin[1]) / (1 * (Zmaxmin[0] - Zmaxmin[1]));
                    gray = 1 - gray;
                    
                    glm::vec3 grayscale(gray, gray, gray);
                    PutPixel(j, i, grayscale);
                }
            }
            else if (interpulation){
//                glm::vec3 color_ = getPixelColor(j,i,top,mid,bottom,color,color2,color3);
                PutPixel(j, i, color);
            }
            else {
                if (FillZBuffer(j, i, tempZ)){
                PutPixel(j, i, color);
                }
            }
        }

    }
}



bool Renderer::FillZBuffer(int x, int y, float z) {
    if (x < 0) return false; if (x >= viewport_width) return false;
    if (y < 0) return false; if (y >= viewport_height) return false;
        if (z < z_buffer[x + y * viewport_width]) {
            z_buffer[x + y * viewport_width] = z; /// todo (check if i go to the right place in the array)
            return true;
        }
        return false;
    }


// this function works only on flat_bottom triangles
float Renderer::getZ_flat_b(glm::vec3 top, glm::vec3 mid, glm::vec3 bottom, int Xmin, int Xmax, int x, int y) {
        float Zb_Slope = (bottom.z - top.z) / (bottom.y - top.y);
        float Za_Slope = (mid.z - top.z) / (mid.y - top.y);
        float Za = top.z + ((y - top.y) * Za_Slope);
        float Zb = top.z + ((y - top.y) * Zb_Slope);
        float Zp_Slope = (Zb - Za) / (Xmin - Xmax);
        return Za + ((x - Xmin) * Zp_Slope);
    }


// this function works only on flat_top triangles
float Renderer::getZ_flat_t(glm::vec3 top, glm::vec3 mid, glm::vec3 bottom, int Xmin, int Xmax, int x, int y) {
        float Za_Slope = (bottom.z - top.z) / (bottom.y - top.y);
        float Zb_Slope = (bottom.z - mid.z) / (bottom.y - mid.y);
        float Za = top.z + ((y - top.y) * Za_Slope);
        float Zb = mid.z + ((y - mid.y) * Zb_Slope);
        float Zp_Slope = (Zb - Za) / (Xmin - Xmax);

        return Za + ((x - Xmin) * Zp_Slope);

    }


void Renderer::ClearZBuffer() {
    for (int i = 0; i < viewport_height * viewport_width; i++) {
        z_buffer[i] = std::numeric_limits<float>::infinity();
    }
}



void Renderer::DrawMesh(MeshModel temp,glm::mat4x4 transformation,Camera& cam, Lighting& Light){
        
//        glm::vec3 Linescolor = temp.GetLinesColor();
//        glm::vec3 Modelcolor = temp.GetModelColor();
        glm::vec3 Linescolor = temp.GetMeshColor();
        glm::vec3 Modelcolor = temp.GetMeshColor();
        for (int i = 0; i < temp.GetFacesCount(); i++) {
            
            glm::ivec3 tempvertices;
            glm::ivec3 tempnormals;

            for (int j = 0; j < 3; j++) {
                tempvertices[j] = temp.GetFace(i).GetVertexIndex(j);
                tempnormals[j] = temp.GetFace(i).GetNormalIndex(j);
            }

            glm::vec4 vertex1 = glm::vec4(temp.GetVertices(tempvertices[0] - 1), 1.0);
            glm::vec4 vertex2 = glm::vec4(temp.GetVertices(tempvertices[1] - 1), 1.0);
            glm::vec4 vertex3 = glm::vec4(temp.GetVertices(tempvertices[2] - 1), 1.0);
            
            temp.UpdateMainMatrix();
            vertex1 = transformation * vertex1;
            vertex2 = transformation * vertex2;
            vertex3 = transformation * vertex3;

            

            float minX = std::min(vertex1[0],std::min(vertex2[0],vertex3[0]));
            float minY = std::min(vertex1[1],std::min(vertex2[1],vertex3[1]));
            float maxX = std::max(vertex1[0],std::max(vertex2[0],vertex3[0]));
            float maxY = std::max(vertex1[1],std::max(vertex2[1],vertex3[1]));

            glm::vec3 ver1(vertex1[0], vertex1[1], vertex1[2]);
            glm::vec3 ver2(vertex2[0], vertex2[1], vertex1[2]);
            glm::vec3 ver3(vertex3[0], vertex3[1], vertex1[2]);

            int factor = temp.GetScale();
            Zmaxmin=temp.GetMaxMinZ(transformation);
//            Zmaxmin[0] = Zmaxmin[0] * factor;
//            Zmaxmin[1] = Zmaxmin[1] * factor;

            if (CameraProjection != 1)
            {
                ver1 = vertex1 / vertex1.w;
                ver2 = vertex2 / vertex2.w;
                ver3 = vertex3 / vertex3.w;
            }
            else
            {
                ver1 = vec3(vertex1[0], vertex1[1], vertex1[2]);
                ver2 = vec3(vertex2[0], vertex2[1], vertex1[2]);
                ver3 = vec3(vertex3[0], vertex3[1], vertex1[2]);
            }
            
            // triangle drawing ---------
            if (temp.DrawLines) {
                DrawLine(ver1, ver2, Linescolor);
                DrawLine(ver2, ver3, Linescolor);
                DrawLine(ver3, ver1, Linescolor);
            }
            
            
            // light source position
            glm::vec3 position = Light.GetLightSourcePosition();
            
            if(temp.reflectionRays){
                glm::vec3 middlePoint = (ver1 + ver2 + ver3) / 3.0f;
                glm::vec3 Normal = glm::triangleNormal(ver1, ver2, ver3);
                glm::vec3 LightVector = position - middlePoint;
                glm::vec3 reflectVector = glm::normalize(glm::reflect(-1.f * LightVector, Normal));
                glm::vec3 endpoint = 50.f * reflectVector ;
                endpoint = endpoint + middlePoint;
                DrawLine(middlePoint, endpoint, temp.Normalscolor);
            }
            // solid color model here we add all shading options
            if (temp.solidColor) {
                
                if(Light.FlatShading){
                    glm::vec3 triangleNormal = glm::normalize( glm::triangleNormal(ver1, ver2, ver3));
                    glm::vec3 middlePoint = (ver1 + ver2 + ver3) / 3.0f;
                    glm::vec3 LightDirection = glm::normalize(glm::vec3(Light.GetLightSourcePosition())-middlePoint);
                    auto Attenuation = 1 / ((power2(position.x - middlePoint.x) +  power2(position.y - middlePoint.y) + power2(position.z - middlePoint.z)) + 1.0f);
                    float alpha = std::max(glm::dot(triangleNormal, LightDirection), 0.0f);
                    
//                    glm::vec3 Ambient = Light.GetAmbientColor() * temp.AmbientColor * temp.GetModelColor();
                    glm::vec3 Ambient = Light.GetAmbientColor() * temp.AmbientColor * temp.ModelColor;
                    glm::vec3 Diffuse = Attenuation * alpha * temp.diffuseRate * temp.DiffuseColor * Light.FlatShadingIntesity * Light.GetDiffuseColor();
                    //Specular
                    glm::vec3 CameraVector = glm::normalize(cam.position - middlePoint);
                    glm::vec3 reflect_Light = glm::normalize(glm::reflect((float)-1 * LightDirection, triangleNormal));
                    float specular_angle = pow(std::max(glm::dot(CameraVector, reflect_Light), 0.0f), Light.specularDegree);
                    glm::vec3 Specular_Vector = Attenuation * temp.diffuseRate * Light.FlatShadingIntesity * (1 - specular_angle) * temp.SpecularColor * Light.GetSpecularColor();

                    glm::vec3 face_colortotal = (Ambient + Diffuse + Specular_Vector);

                    DrawTriangle(ver1, ver2, ver3, face_colortotal * temp.GetModelColor(),face_colortotal * temp.GetModelColor(),face_colortotal * temp.GetModelColor(),false, false);
                    
                }
                else if (Light.PhongShading){
                    
                    glm::vec4 norm1 = glm::vec4(temp.GetNormal(tempnormals[0] - 1), 1.0);
                    glm::vec4 norm2 = glm::vec4(temp.GetNormal(tempnormals[1] - 1), 1.0);
                    glm::vec4 norm3 = glm::vec4(temp.GetNormal(tempnormals[2] - 1), 1.0);
                    
                    norm1 = glm::normalize( transformation * norm1 );
                    norm2 = glm::normalize( transformation * norm2 );
                    norm3 = glm::normalize( transformation * norm3 );
                    
                    float Xmin, Xmax;
                    Xmin = std::min(ver1.x, std::min(ver2.x, ver3.x));
                    Xmax = std::max(ver1.x, std::max(ver2.x, ver3.x));
                    float Ymin, Ymax;
                    Ymin = std::min(ver1.y, std::min(ver2.y, ver3.y));
                    Ymax = std::max(ver1.y, std::max(ver2.y, ver3.y));
                    
                    
                    
                    for (int i = Ymin ; i <= Ymax ; i++){
                        for(int j = Xmin ; j <= Xmax ; j++){
                            if(PointIsValid(glm::ivec2(j,i), ver1, ver2, ver3)){
                                glm::vec3 LightVector = glm::normalize( position - glm::vec3(j,i,0));
                                auto Attenuation = 1 / ((power2(position.x - j) +  power2(position.y - i) + power2(position.z - 0)) + 1.0f); // might need to change z=0 to interpolated value of z
                                
                                // Now we need to do interpulatioin for the normals
                                // using the area interpulation method
                                glm::vec3 tempPoint(j,i,0);
                                float area1 = area(tempPoint,ver1,ver2);
                                float area2 = area(tempPoint,ver1,ver3);
                                float area3 = area(tempPoint,ver2,ver3);
                                float total = area(ver1,ver2,ver3);
                                
                                float ratio1 = area1/total;
                                float ratio2 = area2/total;
                                float ratio3 = area3/total;
                                
                                // this is the interpulated normal
                                glm::vec4 Normal = glm::normalize( norm1 * ratio3 + norm2 * ratio2 + norm3 * ratio1 ) ;
                                glm::vec3 Normal3 = Normal;
                                
                                float alpha = std::max(glm::dot(Normal3,LightVector),0.f);
                                glm::vec3 Ambient = Light.GetAmbientColor() * temp.AmbientColor ;
                                glm::vec3 Diffuse = Attenuation * Light.PhongShadingIntesity * alpha *Light.GetDiffuseColor();
                                glm::vec3 camVector = glm::normalize(cam.position - tempPoint);
                                glm::vec3 reflect = glm::normalize(glm::reflect(LightVector, Normal3));
                                float max = std::max(glm::dot(camVector, reflect),0.f);
                                float alpha2 = pow(max,Light.specularDegree);
                                
                                glm::vec3 Specular = temp.diffuseRate * Light.PhongShadingIntesity * Attenuation * alpha2 * Light.GetSpecularColor() ;
                                
                                glm::vec3 color = Ambient + Diffuse + Specular ;
                                
                                for(int z =0 ; z<3 ; z++){
                                    if(color[z] > 1){
                                        color[z] = 1;
                                    }
                                    else if (color[z] < 0){
                                        color[z] = 0 ;
                                    }
                                    else{
                                        continue;
                                    }
                                }
                                
                                PutPixel(j, i, color);
                                
                                
                            }
                            
                            
                        }
                    }
                    
                    
                }
                else if (Light.GouraudShading){
                    
                    glm::vec4 norm1 = glm::vec4(temp.GetNormal(tempnormals[0] - 1), 1.0);
                    glm::vec4 norm2 = glm::vec4(temp.GetNormal(tempnormals[1] - 1), 1.0);
                    glm::vec4 norm3 = glm::vec4(temp.GetNormal(tempnormals[2] - 1), 1.0);
                    
                    norm1 = glm::normalize( transformation * norm1 );
                    norm2 = glm::normalize( transformation * norm2 );
                    norm3 = glm::normalize( transformation * norm3 );
                    
                    glm::vec3 LightVector1 = glm::normalize(position - ver1);
                    glm::vec3 LightVector2 = glm::normalize(position - ver2);
                    glm::vec3 LightVector3 = glm::normalize(position - ver3);
                    
                    glm::vec3 Normal = glm::normalize(glm::triangleNormal(ver1, ver2, ver3));
                    
                    float alpha1 = std::max(glm::dot(Normal, LightVector1), 0.0f);
                    float alpha2 = std::max(glm::dot(Normal, LightVector2), 0.0f);
                    float alpha3 = std::max(glm::dot(Normal, LightVector3), 0.0f);
                    
                    glm::vec3 Ambient = Light.GetAmbientColor() * temp.AmbientColor ;
                    
                    auto Attenuation = 1 / ((power2(position.x - ver1.x) +  power2(position.y - ver1.y) + power2(position.z - ver1.z)) + 1.0f);
                    auto Attenuation2 = 1 / ((power2(position.x - ver2.x) +  power2(position.y - ver2.y) + power2(position.z - ver2.z)) + 1.0f);
                    auto Attenuation3 = 1 / ((power2(position.x - ver3.x) +  power2(position.y - ver3.y) + power2(position.z - ver3.z)) + 1.0f);
                    
                    glm::vec3 Diffuse1 = Attenuation * alpha1 * temp.diffuseRate * Light.GouraudShadingIntesity  * Light.GetDiffuseColor();
                    glm::vec3 Diffuse2 = Attenuation2 * alpha2 * temp.diffuseRate * Light.GouraudShadingIntesity * Light.GetDiffuseColor();
                    glm::vec3 Diffuse3 = Attenuation3 * alpha3 * temp.diffuseRate * Light.GouraudShadingIntesity * Light.GetDiffuseColor();
                    
                    glm::vec3 camVector1 = glm::normalize(cam.position - ver1);
                    glm::vec3 camVector2 = glm::normalize(cam.position - ver2);
                    glm::vec3 camVector3 = glm::normalize(cam.position - ver3);
                    
                    glm::vec3 reflect1 = glm::normalize(glm::reflect(-1.f * LightVector1, Normal));
                    glm::vec3 reflect2 = glm::normalize(glm::reflect(-1.f * LightVector2, Normal));
                    glm::vec3 reflect3 = glm::normalize(glm::reflect(-1.f * LightVector3, Normal));
                    
//                    glm::vec3 reflect1 = glm::normalize(glm::reflect( LightVector1, Normal));
//                    glm::vec3 reflect2 = glm::normalize(glm::reflect( LightVector2, Normal));
//                    glm::vec3 reflect3 = glm::normalize(glm::reflect( LightVector3, Normal));
                    
                    float angle1 = pow(std::max(glm::dot(camVector1, reflect1), 0.0f), Light.specularDegree);
                    float angle2 = pow(std::max(glm::dot(camVector2, reflect2), 0.0f), Light.specularDegree);
                    float angle3 = pow(std::max(glm::dot(camVector3, reflect3), 0.0f), Light.specularDegree);
                    
                    glm::vec3 Specular1 = temp.diffuseRate * Attenuation * Light.GouraudShadingIntesity * angle1 * Light.GetSpecularColor();
                    glm::vec3 Specular2 = temp.diffuseRate * Attenuation2 * Light.GouraudShadingIntesity * angle2 * Light.GetSpecularColor();
                    glm::vec3 Specular3 = temp.diffuseRate * Attenuation3 * Light.GouraudShadingIntesity * angle3 * Light.GetSpecularColor();
                    
                    glm::vec3 color1 = temp.GetModelColor() * (Ambient + Diffuse1 + Specular1) ;
                    glm::vec3 color2 = temp.GetModelColor() * (Ambient + Diffuse2 + Specular2);
                    glm::vec3 color3 = temp.GetModelColor() * (Ambient + Diffuse3 + Specular3) ;
                    
                    DrawTriangle(ver1, ver2, ver3, color1, color2, color3, true, false);
                }
                else{
                    
                    DrawTriangle(ver1, ver2, ver3, Modelcolor,Modelcolor,Modelcolor,false, false);
                }
                
                
                
                
                
            }
            
            // color changing model
            if (temp.changingColors) {
                float R_Color = (rand() % (100));
                float G_Color = (rand() % (100));
                float B_Color = (rand() % (100));

                R_Color = R_Color / 100;
                G_Color = G_Color / 100;
                B_Color = B_Color / 100;

                glm::vec3 RandomColor(R_Color, G_Color, B_Color);
                DrawTriangle(ver1, ver2, ver3, RandomColor ,RandomColor,RandomColor,false, false);
            }
            
            
            // gray scale model
            if (temp.grayScale) {
                DrawTriangle(ver1, ver2, ver3, Modelcolor,Modelcolor,Modelcolor,false, true);
            }
            
            // rectangle drawing ----------
            if (temp.FaceBoundingBoxStutus){
                //glm::vec3 Boxcolor = temp.GetRandomColor();  // this doesn't wok
                
                float R_Color = (rand() % (100));
                float G_Color = (rand() % (100));
                float B_Color = (rand() % (100));

                R_Color = R_Color / 100 ;
                G_Color = G_Color / 100 ;
                B_Color = B_Color / 100 ;

                glm::vec3 Boxcolor (R_Color, G_Color, B_Color);
                
                
                DrawLine(glm::vec2(minX,minY), glm::vec2(minX,maxY), Boxcolor);
                DrawLine(glm::vec2(minX,minY), glm::vec2(maxX,minY), Boxcolor);
                DrawLine(glm::vec2(minX,maxY), glm::vec2(maxX,maxY), Boxcolor);
                DrawLine(glm::vec2(maxX,minY), glm::vec2(maxX,maxY), Boxcolor);
            }
            
    }
}

bool Renderer::PointIsValid(glm::ivec2 p, glm::ivec2 p0, glm::ivec2 p1, glm::ivec2 p2)
{
    float r = (p0.x - p2.x) * (p.y - p2.y) - (p0.y - p2.y) * (p.x - p2.x);
    float t = (p1.x - p0.x) * (p.y - p0.y) - (p1.y - p0.y) * (p.x - p0.x);

    if ((r < 0) != (t < 0) && r != 0 && t != 0)
        return false;

    float d = (p2.x - p1.x) * (p.y - p1.y) - (p2.y - p1.y) * (p.x - p1.x);
    return d == 0 || (d < 0) == (r + t <= 0);
}

void Renderer::DrawLightSource(Lighting& lightSource)
{
    int r = 50 ;// radius of circle
    for(int angel = -90; angel <= 90; angel++)
    {
        float theta = 2.0f * 3.1415926f * float(angel) / float(360);//get the current angle

        float x = r * cos(theta);//calculate the x component
        float y = r * sin(theta);//calculate the y component
        float positionX = lightSource.GetLightSourcePosition()[0];
        float positiony = lightSource.GetLightSourcePosition()[1];
        
//        float tempx = x + positionX;
//        float tempy = y + positiony;
        
        for (int j = positionX - x ; j <= positionX + x ; j++){
            PutPixel(j, y + positiony, lightSource.GetLightSourceColor());
        }

        
    }
   
}


float Renderer::area(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
{
    if (abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0) == INFINITY)
    {
        return 0;
    }
    else
        return abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0);
}
