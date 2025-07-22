#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "RenderingManager.h"
#include "Texture.h"
#include "Modele.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "CPN_LightCaster.h"
#include "LightData.h"
#include "LightType.h"

#include "GameObject.h"
#include "Transform.h"

#include "CPN_Renderer.h"

#include <string>
#include<iostream>

CPN_Renderer::CPN_Renderer()
	: Component()
{
}

CPN_Renderer::~CPN_Renderer()
{
}

void CPN_Renderer::Initialize(GameObject& nContainingGameObject)
{
	Component::Initialize(nContainingGameObject);

	modele = std::make_shared<Modele>();
	modele->LoadModele("ressources/objects/backpack.obj"); //REVIEW : Should move once the ModeleManager is done.

	RenderingManager::GetInstance()->AddRendererToRender(*this);
}

void CPN_Renderer::Destroy()
{
	RenderingManager::GetInstance()->RemoveRendererToRender(*this);
}

void CPN_Renderer::Render()
{
	//Materials and Shader
	std::vector<std::shared_ptr<Material>> materials = modele->GetMaterials();

	for (unsigned int i = 0; i < materials.size(); i++)
	{
		Shader& matShader = materials[i]->GetShader();

		matShader.Use();

		//Vertex Shader Setup
		//Projection Matrix
		matShader.SetMat4("projection", RenderingManager::GetInstance()->GetMainCamera()->GetProjectionMatrix());

		//View Matrix
		matShader.SetMat4("view", RenderingManager::GetInstance()->GetMainCamera()->GetViewMatrix());

		//Model Matrix
		matShader.SetMat4("model", containingGameObject->GetTransform()->GetModelMatrix());

		matShader.SetFloat("material.shininess", materials[i]->GetShininess());

		//Lights
		std::vector<CPN_LightCaster*> lights = RenderingManager::GetInstance()->GetLights();

		int directionalCount = 0;
		int pointCount = 0;
		int spotCount = 0;

		for (CPN_LightCaster* light : lights)
		{
			LightData lightData = light->GetData();

			std::string lightName;

			switch (lightData.lightType)
			{
			case LIGHTTYPE_Directional :
				lightName = "directionalLights[" + std::to_string(directionalCount) + "].";
				directionalCount++;
				break;
			case LIGHTTYPE_Point :
				lightName = "pointLights[" + std::to_string(pointCount) + "].";
				pointCount++;
				break;
			case LIGHTTYPE_Spot :
				lightName = "spotLights[" + std::to_string(spotCount) + "].";
				spotCount++;
				break;
			}

			matShader.SetVec3(lightName + "position", lightData.position);
			matShader.SetVec3(lightName + "direction", lightData.direction);
			matShader.SetVec3(lightName + "ambientColor", lightData.ambientColor);
			matShader.SetVec3(lightName + "diffuseColor", lightData.diffuseColor);
			matShader.SetVec3(lightName + "specularColor", lightData.specularColor);
			matShader.SetFloat(lightName + "linear", lightData.linear);
			matShader.SetFloat(lightName + "quadratic", lightData.quadratic);
			matShader.SetFloat(lightName + "cutoffAngle", lightData.cutoffAngle);
			matShader.SetFloat(lightName + "outerCutoffAngle", lightData.outerCutoffAngle);
		}

		matShader.SetVec3("viewPos", RenderingManager::GetInstance()->GetMainCamera()->GetTransform()->GetPosition()); //REVIEW : See to change the Fragment Shader for the ViewPos to not be necessary (Use view positions instead of world positions)
	}

	//Textures and Shader
	std::vector<std::shared_ptr<Mesh>> meshesToRender = modele->GetMeshes();

	for (unsigned int j = 0; j < meshesToRender.size(); j++)
	{
		Material& material = *(materials[meshesToRender[j]->GetMaterialIndex()]);

		material.GetShader().Use();

		//Render
		//Textures (TODO : A modifier quand on fera le Texture Manager)
		std::vector<Texture> textures = material.GetTextures();
		unsigned int diffuseNr = 0;
		unsigned int specularNr = 0;

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			std::string number;

			if (textures[i].type == "Diffuse")
			{
				number = std::to_string(diffuseNr++);
				material.GetShader().SetMat4(("material.diffuse[" + number + "]").c_str(), i);
			}
			else if (textures[i].type == "Specular")
			{
				number = std::to_string(specularNr++);
				material.GetShader().SetMat4(("material.specular[" + number + "]").c_str(), i);
			}

			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		glBindVertexArray(meshesToRender[j]->GetVAO());
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(meshesToRender[j]->GetIndices().size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
	}
}
