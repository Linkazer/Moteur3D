#include "RenderingManager.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CPN_Renderer.h"

RenderingManager::RenderingManager() 
    :Singleton<RenderingManager>()
{

}

RenderingManager::~RenderingManager()
{
}

void RenderingManager::Initialize()
{
    stbi_set_flip_vertically_on_load(true);

	glEnable(GL_DEPTH_TEST);
}

void RenderingManager::Clean()
{

}

void RenderingManager::Render(GLFWwindow& window)
{
    glClearColor(0.05f, 0.05f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (CPN_Renderer* renderer : renderersToRender)
    {
        renderer->Render();
    }

    glfwSwapBuffers(&window);
}

void RenderingManager::AddRendererToRender(CPN_Renderer& rendererToAdd)
{
    if (std::find(begin(GetInstance()->renderersToRender), end(GetInstance()->renderersToRender), &rendererToAdd) == end(GetInstance()->renderersToRender))
    {
        GetInstance()->renderersToRender.push_back(&rendererToAdd);
    }
}

void RenderingManager::RemoveRendererToRender(CPN_Renderer& rendererToRemove)
{
    auto it = std::find(begin(GetInstance()->renderersToRender), end(GetInstance()->renderersToRender), &rendererToRemove);
    GetInstance()->renderersToRender.erase(it);
}

void RenderingManager::AddLightToRender(CPN_LightCaster& lightToAdd)
{
    if (std::find(begin(GetInstance()->lightsToRender), end(GetInstance()->lightsToRender), &lightToAdd) == end(GetInstance()->lightsToRender))
    {
        GetInstance()->lightsToRender.push_back(&lightToAdd);
    }
}

void RenderingManager::RemoveLightToRender(CPN_LightCaster& lightToRemove)
{
    auto it = std::find(begin(GetInstance()->lightsToRender), end(GetInstance()->lightsToRender), &lightToRemove);
    GetInstance()->lightsToRender.erase(it);
}

void RenderingManager::SetMainCamera(CPN_Camera* cameraToSet)
{
    mainCamera = cameraToSet;
}
