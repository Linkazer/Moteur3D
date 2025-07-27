#include "RenderingManager.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Engine.h"
#include "Shader.h"
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

    //Shader Set up
    compositeShader = std::make_unique<Shader>("composite.vs", "composite.fs");
    screenShader = std::make_unique<Shader>("screen.vs", "screen.fs");

    //Screen plane Set up
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    //Opaque framebuffer Set up
    glGenFramebuffers(1, &opaqueFBO);

    glGenTextures(1, &opaqueTexture);
    glBindTexture(GL_TEXTURE_2D, opaqueTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Engine::GetWindowWidth(), Engine::GetWindowHeight(), 0, GL_RGBA, GL_HALF_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Engine::GetWindowWidth(), Engine::GetWindowHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, opaqueFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, opaqueTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Opaque framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //Transparent framebuffer Set up
    glGenFramebuffers(1, &transparentFBO);

    glGenTextures(1, &accumTexture);
    glBindTexture(GL_TEXTURE_2D, accumTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Engine::GetWindowWidth(), Engine::GetWindowHeight(), 0, GL_RGBA, GL_HALF_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &revealTexture);
    glBindTexture(GL_TEXTURE_2D, revealTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, Engine::GetWindowWidth(), Engine::GetWindowHeight(), 0, GL_RED, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, transparentFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, accumTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, revealTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0); // opaque framebuffer's depth texture

    const GLenum transparentDrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, transparentDrawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Transparent framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    //Depth Testing
    //glEnable(GL_DEPTH_TEST);

    //Blending // Waiting for IOT course
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Face culling
    //glEnable(GL_CULL_FACE);
}

void RenderingManager::Clean()
{
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteVertexArrays(1, &quadVBO);
    glDeleteTextures(1, &opaqueTexture);
    glDeleteTextures(1, &depthTexture);
    glDeleteTextures(1, &accumTexture);
    glDeleteTextures(1, &revealTexture);
    glDeleteFramebuffers(1, &opaqueFBO);
    glDeleteFramebuffers(1, &transparentFBO);
}

void RenderingManager::Render(GLFWwindow& window)
{
    //Opaque pass
    //  Configure render states
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glClearColor(0.15f, 0.15f, 0.0f, 0.0f);

    //  Bind opaque framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, opaqueFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  Render opaque renderers
    for (CPN_Renderer* renderer : renderersToRender)
    {
        renderer->Render();
    }

    //Transparent pass
    //  Configure render states
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunci(0, GL_ONE, GL_ONE);
    glBlendFunci(1, GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
    glBlendEquation(GL_FUNC_ADD);

    //  Bind transparent buffer
    glBindFramebuffer(GL_FRAMEBUFFER, transparentFBO);
    glClearBufferfv(GL_COLOR, 0, &zeroFillerVec[0]);
    glClearBufferfv(GL_COLOR, 1, &oneFillerVec[0]);

    //  Render transparent renderers
    for (CPN_Renderer* renderer : renderersTransparentToRender)
    {
        renderer->Render();
    }

    //Composite pass
    //  Configure render states
    glDepthFunc(GL_ALWAYS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //  Bind composite (opaque) framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, opaqueFBO);

    //  Use composite shader
    compositeShader->Use();

    //  Render screen plane
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, accumTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, revealTexture);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //Backbuffer pass
    //  Configure render states
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE); // enable depth writes so glClear won't ignore clearing the depth buffer
    glDisable(GL_BLEND);

    //  Bind backbuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //  Use screen shader
    screenShader->Use();

    //  Render screen plane
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, opaqueTexture);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    /*glClearColor(0.05f, 0.05f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (CPN_Renderer* renderer : renderersToRender)
    {
        renderer->Render();
    }*/

    glfwSwapBuffers(&window);
}

void RenderingManager::AddRendererToRender(CPN_Renderer& rendererToAdd, bool isOpaque)
{
    if (isOpaque)
    {
        if (std::find(begin(GetInstance()->renderersToRender), end(GetInstance()->renderersToRender), &rendererToAdd) == end(GetInstance()->renderersToRender))
        {
            GetInstance()->renderersToRender.push_back(&rendererToAdd);
        }
    }
    else
    {
        if (std::find(begin(GetInstance()->renderersTransparentToRender), end(GetInstance()->renderersTransparentToRender), &rendererToAdd) == end(GetInstance()->renderersTransparentToRender))
        {
            GetInstance()->renderersTransparentToRender.push_back(&rendererToAdd);
        }
    }
}

void RenderingManager::RemoveRendererToRender(CPN_Renderer& rendererToRemove)
{
    /*auto itOpaq = std::find(begin(GetInstance()->renderersToRender), end(GetInstance()->renderersToRender), &rendererToRemove);
    GetInstance()->renderersToRender.erase(itOpaq);

    auto itTransp = std::find(begin(GetInstance()->renderersTransparentToRender), end(GetInstance()->renderersTransparentToRender), &rendererToRemove);
    GetInstance()->renderersTransparentToRender.erase(itTransp);*/
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
