#ifndef RENDERINGMANAGER_H
#define RENDERINGMANAGER_H

#include <memory>
#include <vector>

#include <glm/glm.hpp>

//TESTS
#include "GameObject.h"
#include "CPN_CameraController.h"
#include "CPN_Camera.h"

#include "Singleton.h"

#pragma once
class GLFWwindow;
class CPN_Renderer;
class CPN_LightCaster;
class Shader;

class RenderingManager : public Singleton<RenderingManager>
{
public:
	explicit RenderingManager();
	virtual ~RenderingManager();

	/// <summary>
	/// Initialize the Rendering data.
	/// </summary>
	void Initialize();
	/// <summary>
	/// Clean the RenderingManager and everything that need to be cleanse link to it.
	/// </summary>
	void Clean();

	/// <summary>
	/// Render every object that need to be rendered.
	/// </summary>
	void Render(GLFWwindow& window);

	/// <summary>
	/// Add a CPN_Renderer to the Render step.
	/// </summary>
	/// <param name="rendererToAdd">The CPN_Renderer to add.</param>
	static void AddRendererToRender(CPN_Renderer& rendererToAdd, bool isOpaque);
	/// <summary>
	/// Remove a CPN_Renderer from the Render step.
	/// </summary>
	/// <param name="rendererToRemove">The CPN_Renderer to remove.</param>
	static void RemoveRendererToRender(CPN_Renderer& rendererToRemove);

	/// <summary>
	/// Add a CPN_LightCaster that will be used in the Render step.
	/// </summary>
	/// <param name="lightToAdd">The CPN_LightCaster to add.</param>
	static void AddLightToRender(CPN_LightCaster& lightToAdd);
	/// <summary>
	/// Remove a CPN_LightCaster from the Render step.
	/// </summary>
	/// <param name="lightToRemove">The CPN_LightCaster to remove.</param>
	static void RemoveLightToRender(CPN_LightCaster& lightToRemove);
	/// <summary>
	/// Get every lights used in the Render step.
	/// </summary>
	/// <returns>Every lights used during the Render step.</returns>
	inline std::vector<CPN_LightCaster*> GetLights() { return lightsToRender; }

	/// <summary>
	/// Set a Camera as main, making it the Camera that will be used for the rendering.
	/// </summary>
	/// <param name="cameraToSet">The Camera to set as main.</param>
	void SetMainCamera(CPN_Camera* cameraToSet);
	/// <summary>
	/// Get the current main Camera.
	/// </summary>
	/// <returns>The current main Camera.</returns>
	inline CPN_Camera* GetMainCamera() { return mainCamera; }

private:
	std::vector<CPN_Renderer*> renderersToRender;
	std::vector<CPN_Renderer*> renderersTransparentToRender;
	std::vector<CPN_LightCaster*> lightsToRender;

	unsigned int quadVAO;
	unsigned int quadVBO;
	unsigned int opaqueFBO;
	unsigned int opaqueTexture;
	unsigned int depthTexture;
	unsigned int transparentFBO;
	unsigned int accumTexture;
	unsigned int revealTexture;

	glm::vec4 zeroFillerVec{ 0.0f, 0.0f, 0.0f, 0.0f };
	glm::vec4 oneFillerVec{ 1.0f, 1.0f, 1.0f, 1.0f };

	float quadVertices[30] = { //Fullscreen Plane
		// positions		// uv
		-1.0f, -1.0f, 0.0f,	0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,

		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f
	};

	std::unique_ptr<Shader> opaqueShader;
	std::unique_ptr<Shader> transparentShader;
	std::unique_ptr<Shader> compositeShader;
	std::unique_ptr<Shader> screenShader;

	CPN_Camera* mainCamera;
};
#endif

