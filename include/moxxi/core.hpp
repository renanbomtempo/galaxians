#ifndef MOXXI_CORE_H
#define MOXXI_CORE_H

#include <list>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#define CUR_MOXXI_VERSION_MAJOR 0
#define CUR_MOXXI_VERSION_MINOR 0

#define DEFAULT_SCR_WIDTH 800
#define DEFAULT_SCR_HEIGHT 600

// Directions
#define LEFT vec3(-1, 0, 0)
#define RIGHT vec3(1, 0, 0)
#define UP vec3(0, 1, 0)
#define DOWN vec3(0, -1, 0)
#define FRONT vec3(0, 0, 1)
#define BACK vec3(0, 0, -1)

using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

namespace moxxi
{
    // Class Attribute Declarations
    // ----------------------------
    class Core
    {
    private:
        inline static GLFWwindow *window = NULL;
        Core(void);
        static void InitializeGLFW(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
        static void InitializeGLAD();

    public:
        ~Core(void);
        static GLFWwindow *getWindowPtr();
        static void Update();
        static void InitializeGraphics(unsigned int width, unsigned int height);
        static void Refresh();

        static int GetKeyPressed();
        vec2 GetMousePosition();

        static void changeTitle(std::string new_title);
        static void resizeWindow(unsigned int width, unsigned int height);
    };

    class Debug
    {
    public:
        // Echo vectors
        static void Warning(std::string msg);
        static void Echo(std::string msg, bool endline = true);
    };

    class Mesh
    {
    private:
        unsigned int VBO, VAO, EBO;
        std::vector<vec3> vertices;
        std::vector<unsigned int> indices;

        void updateGLBuffers();

    public:
        Mesh();
        ~Mesh();
        std::vector<vec3> getVertices();
        void LoadMeshData(std::vector<vec3> vertices, std::vector<unsigned int> indices);
        std::vector<unsigned int> getIndices();
        std::string strVertices();
        const unsigned int vertexCount();
    }; // Class Mesh

    class Shader
    {
    public:
        // state
        unsigned int ID;
        // constructor
        Shader() {}
        // sets the current shader as active
        Shader &Use();
        // compiles the shader from given source code
        void Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr); // note: geometry source code is optional
        // utility functions
        void SetFloat(const char *name, float value, bool useShader = false);
        void SetInteger(const char *name, int value, bool useShader = false);
        void SetVector2f(const char *name, float x, float y, bool useShader = false);
        void SetVector2f(const char *name, const glm::vec2 &value, bool useShader = false);
        void SetVector3f(const char *name, float x, float y, float z, bool useShader = false);
        void SetVector3f(const char *name, const glm::vec3 &value, bool useShader = false);
        void SetVector4f(const char *name, float x, float y, float z, float w, bool useShader = false);
        void SetVector4f(const char *name, const glm::vec4 &value, bool useShader = false);
        void SetMatrix4(const char *name, const glm::mat4 &matrix, bool useShader = false);

    private:
        // checks if compilation or linking failed and if so, print the error logs
        void checkCompileErrors(unsigned int object, std::string type);
    };

    class Texture2D
    {
    public:
        // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
        unsigned int ID;
        // texture image dimensions
        unsigned int Width, Height; // width and height of loaded image in pixels
        // texture Format
        unsigned int Internal_Format; // format of texture object
        unsigned int Image_Format;    // format of loaded image
        // texture configuration
        unsigned int Wrap_S;     // wrapping mode on S axis
        unsigned int Wrap_T;     // wrapping mode on T axis
        unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
        unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels
        // constructor (sets default texture modes)
        Texture2D();
        // generates texture from image data
        void Generate(unsigned int width, unsigned int height, unsigned char *data);
        // binds the texture as the current active GL_TEXTURE_2D texture object
        void Bind() const;
    };

    class Material
    {
    private:
        Texture2D texture;

    public:
        void SetShader(const char *vertex_shader_path, const char *fragment_shader_path);
        void UseShader();
        void SetTexture(std::string name);
        Texture2D &GetTexture();

    }; // Class Material

    class Transform
    {
    public:       
        vec3 positon;
        vec3 rotation;
        vec3 scale;

        Transform();
        
        // Position
        void Translate(vec3 direction);
        void MoveTo(vec3 position);

        // Roatation
        void Rotate(vec3 rotation);

        // Scale
        void Scale(vec3 scale);

        // Debug
        void print();
    }; // Class Transform

    class Renderer {};

    class SpriteRenderer : public Renderer
    {
    public:
        SpriteRenderer(Shader &shader);
        ~SpriteRenderer();
        void DrawSprite(Texture2D &texture, glm::vec3 position,
                        glm::vec3 size = glm::vec3(10.0f), float rotate = 0.0f,
                        glm::vec3 color = glm::vec3(1.0f));

    private:
        Shader shader;
        unsigned int quadVAO;
        void initRenderData();
    };

    class GameObject
    {
    public:
        std::string name;
        Transform transform;
        Material material;

        GameObject() {}
        GameObject(std::string name);
        ~GameObject();
        
        virtual void Render() {};
        virtual void Update() {};
        virtual void FixedUpdate() {};

    }; // Class GameObject

    class ResourceManager
    {
    public:
        // resource storage
        static std::map<std::string, Shader> Shaders;
        static std::map<std::string, Texture2D> Textures;
        static std::map<std::string, Mesh> Meshes;
        // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
        static Shader LoadShader(std::string name, const char *vShaderFile, const char *fShaderFile, const char *gShaderFile);
        // retrieves a stored sader
        static Shader GetShader(std::string name);
        // loads (and generates) a texture from file
        static Texture2D LoadTexture(std::string name, const char *file, bool alpha);
        // retrieves a stored texture
        static Texture2D GetTexture(std::string name);
        // loads (and generates) a mesh from file
        static Mesh LoadMesh(std::string name, const char *path);
        // retrieves a stored mesh
        static Mesh GetMesh(std::string name);
        // properly de-allocates all loaded resources
        static void Clear();

    private:
        // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
        ResourceManager() {}
        // loads and generates a mesh from OBJ
        static Mesh LoadMeshFromOBJ(const char *path);
        // loads and generates a shader from file
        static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
        // loads a single texture from file
        static Texture2D loadTextureFromFile(const char *file, bool alpha);
    };
}

#endif