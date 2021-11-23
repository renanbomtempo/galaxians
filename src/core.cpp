#include "moxxi/core.hpp"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

namespace moxxi
{

Core::~Core()
{
    glfwTerminate();
}

GLFWwindow* Core::getWindowPtr()
{
    return Core::window;
}

void Core::InitializeGLFW(unsigned int window_width, unsigned int window_height)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    Core::window = glfwCreateWindow(window_width, window_height, "Moxxi Game Engine", NULL, NULL);
    if (Core::window == NULL)
        throw std::runtime_error("Failed to create GLFW window");

    glfwMakeContextCurrent(Core::window);
    glfwSetFramebufferSizeCallback(Core::window, framebuffer_size_callback);
}
  
void Core::InitializeGLAD()
{
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

}

void Core::Refresh()
{
    glfwSwapBuffers(Core::window);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
}

void Core::changeTitle(std::string new_title)
{
    std::string title("Moxxi - ");
    title.append(new_title);
    glfwSetWindowTitle(window, title.c_str());
}

void Core::resizeWindow(unsigned int width, unsigned int height)
{
    framebuffer_size_callback(window, width, height);
}

void Core::InitializeGraphics(unsigned int width, unsigned int height)
{
    Core::InitializeGLFW(width, height);
    Core::InitializeGLAD();
}

} // End Moxxi Namespace;