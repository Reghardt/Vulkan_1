// GLFW will include its own definitions and automatically load the Vulkan header
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// iostream and stdexcept headers are for reporting and propagating errors
#include <iostream>
#include <stdexcept>

// provides EXIT_SUCCESS and EXIT_FAILURE macros
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication
{
public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow()
    {
        // initializes GLFW library
        glfwInit();
        // GLFW was intended to be used with an openGL context so we need to tell it not to use an OpenGL context in this call
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        // resizing windows takes special care that will be looked at later, disables for now
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // Width, height and title. The fourth specifies a monitor, the fifth is only relevant to OpenGL
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan()
    {
    }

    void mainLoop()
    {
        // keeps tha app running until an error or window closure
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        // cleanup resources and terminate glfw
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    GLFWwindow *window;
};

int main()
{
    HelloTriangleApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Hello" << std::endl;
    return EXIT_SUCCESS;
}