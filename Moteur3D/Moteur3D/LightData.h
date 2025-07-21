#ifndef  CPN_LightData_H
#define CPN_LightData_H

#include<glm\glm.hpp>

#include "LightType.h"

#pragma once
struct LightData
{
    LightType lightType;

    //Light position
    glm::vec3 position;
    glm::vec3 direction;

    //Light color
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;

    //Point and Spot lights
    float linear;
    float quadratic;

    //Spot lights
    float cutoffAngle;
    float outerCutoffAngle;
};

#endif