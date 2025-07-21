#include "CPN_LightCaster.h"

#include "Transform.h"
#include "RenderingManager.h"

CPN_LightCaster::CPN_LightCaster()
	: Component()
{
	lightData = LightData();
}

CPN_LightCaster::~CPN_LightCaster()
{
}

void CPN_LightCaster::Initialize(GameObject& nContainingGameObject)
{
	Component::Initialize(nContainingGameObject);

	RenderingManager::AddLightToRender(*this);
}

void CPN_LightCaster::Destroy()
{
	RenderingManager::RemoveLightToRender(*this);
}

LightData CPN_LightCaster::GetData()
{
	lightData.position = GetTransform()->GetPosition();
	lightData.direction = GetTransform()->GetForwardVector();

    return lightData;
}

void CPN_LightCaster::SetData(LightType lightType, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float linear, float quadratic, float cutoffAngle, float outerCutoffAngle)
{
	lightData.lightType = lightType;
	lightData.ambientColor = ambientColor;
	lightData.diffuseColor = diffuseColor;
	lightData.specularColor = specularColor;
	lightData.linear = linear;
	lightData.quadratic = quadratic;
	lightData.cutoffAngle = cutoffAngle;
	lightData.outerCutoffAngle = outerCutoffAngle;
}
