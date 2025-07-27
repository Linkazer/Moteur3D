#include "Engine.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include "RenderingManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Component.h"

Engine::Engine()
    :Singleton<Engine>()
{
    window = nullptr;

    renderingManagerPtr = std::make_unique<RenderingManager>();

    inputManagerPtr = std::make_unique<InputManager>();
}

Engine::~Engine()
{
}

bool Engine::Initialize()
{
    if (instance != this)
    {
        return false; //We make sure only one engine is initialized and used
    }

    //GLFW Initialisation
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //Window Creation
    window = glfwCreateWindow(widowWidth, widowHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        Quit();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });

    //Glad Initialisation
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        Quit();
        return false;
    }

    //Rendering Initialisation
    renderingManagerPtr->Initialize();
    inputManagerPtr->Initialize(window);

    return true;
}

void Engine::Clean()
{
    while (!instantiatedGameObjects.empty())
    {
        instantiatedGameObjects[0]->Destroy();
    }

    renderingManagerPtr->Clean();
}

void Engine::Quit()
{
    Clean();

    glfwTerminate();
}

void Engine::Update(float deltaTime)
{
    for (GameObject* gameObject : instantiatedGameObjects)
    {
        gameObject->Update(deltaTime); //REVIEW : We can put DeltaTime in a static variable to use it only when we need it.
    }
}

void Engine::LateUpdate(float deltaTime)
{
    for (GameObject* gameObject : instantiatedGameObjects)
    {
        gameObject->LateUpdate(deltaTime);
    }
}

void Engine::Render()
{
    renderingManagerPtr->Render(*window);
}

void Engine::InputEvents()
{
    inputManagerPtr->UpdateInputs();
    glfwPollEvents();

    //REVIEW : See where we could put the Quit input
    if (inputManagerPtr->GetKey(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

bool Engine::IsRunning()
{
    return !glfwWindowShouldClose(window);
}

void Engine::InstantiateGameObject(GameObject& toInstantiate)
{
    if (std::find(GetInstance()->instantiatedGameObjects.begin(), GetInstance()->instantiatedGameObjects.end(), &toInstantiate) == GetInstance()->instantiatedGameObjects.end())
    {
        GetInstance()->instantiatedGameObjects.push_back(&toInstantiate);
    }
}

void Engine::DeleteGameObject(GameObject& toDelete)
{
    auto it = std::find(begin(GetInstance()->instantiatedGameObjects), end(GetInstance()->instantiatedGameObjects), &toDelete);
    if (it != end(GetInstance()->instantiatedGameObjects))
    {
        GetInstance()->instantiatedGameObjects.erase(it);
    }
}
