#ifndef  CPN_LightCaster_H
#define CPN_LightCaster_H

#include<glm\glm.hpp>

#include "Component.h"
#include "LightData.h"

#pragma once
class CPN_LightCaster : public Component
{
public :
    explicit CPN_LightCaster();
    virtual ~CPN_LightCaster();

    void Initialize(GameObject& nContainingGameObject) override;
    void Destroy() override;

    /// <summary>
    /// Get the LightData of the Light.
    /// </summary>
    /// <returns>The LightData of the Light.</returns>
    LightData GetData();

    /// <summary>
    /// Set the light's data.
    /// </summary>
    /// <param name="lightType">The type of light it is.</param>
    /// <param name="ambientColor">The ambient color used by the light.</param>
    /// <param name="diffuseColor">The diffuse color used by the light.</param>
    /// <param name="specularColor">The specular color used by the light.</param>
    /// <param name="linear">ONLY FOR POINT AND SPOT. Set the linear variable of the attenuation calcul.</param>
    /// <param name="quadratic">ONLY FOR POINT AND SPOT. Set the quadratic variable of the attenuation calcul.</param>
    /// <param name="cutoffAngle">ONLY FOR SPOT. Set the cutoff angle of the spotlight.</param>
    /// <param name="outerCutoffAngle">ONLY FOR SPOT. Set the outer cutoff angle of the spotlight.</param>
    void SetData(LightType lightType, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float linear, float quadratic, float cutoffAngle, float outerCutoffAngle);
    //REVIEW : See if we can simplify the Linear and Quadratic to put only a light's distance and calculate the linear and quadratic in the function.

private :
    LightData lightData;
};
#endif
