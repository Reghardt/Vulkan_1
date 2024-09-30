// GLFW will include its own definitions and automatically load the Vulkan header
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// iostream and stdexcept headers are for reporting and propagating errors
#include <iostream>
#include <stdexcept>

// provides EXIT_SUCCESS and EXIT_FAILURE macros
#include <cstdlib>

#include <vector>

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
        createInstance();
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
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void createInstance()
    {

        // SECTION: Checking for extension support
        // this section is purely to print a list of available extensions, it is not required for functionality
        uint32_t extensionCount = 0;
        // request number of extensions and store in extensionCount, the last param should be nullptr for getting the count only
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        // allocate array to hold extension details
        std::vector<VkExtensionProperties> extensions(extensionCount);
        // query extension details
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        // list extension
        std::cout << "available extensions:\n";
        for (const auto &extension : extensions)
        {
            std::cout << '\t' << extension.extensionName << '\n';
        }
        // END SECTION

        // optional struct
        VkApplicationInfo appInfo{}; // brace initialization
        // fill struct with info
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // important struct that tells the Vulkan driver which global extensions and validation layers we want to use.
        // Global meaning th entire program and not a specific device
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // vulkan is platform agnostic which means an extention is required to interface with the window  system.
        // GLFW has a built in function that returns the extensions required which is passed to the struct
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        // Vulkan now has everything needed to create an instance:
        // 1: Pointer to struct with creation info
        // 2: Pointer to custom allocator callbacks, always nullptr in this tut
        // 3: Pointer to var that stores the handle to the new object
        // Nearly all vulkan funcs return a value of VkResult
        // VkResult is either VK_SUCCESS or an error code
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }

    GLFWwindow *window;
    VkInstance instance;
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