#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <vector>
#include <memory>

#include <iostream>

//TESTS
#include "GameObject.h"
#include "CPN_Renderer.h"
#include "Modele.h"
#include "Transform.h"
#include "CPN_Camera.h"
#include "CPN_CameraController.h"
#include "CPN_LightCaster.h"
#include "LightType.h"

#include "Engine.h"

int main()
{
    std::unique_ptr<Engine> enginePtr = std::make_unique<Engine>();

    //Engine Initialisation
    if (!enginePtr->Initialize())
    {
        return 0; //Quit program if the Engine can't Initialize
    }

    //---Tests---
    std::vector<GameObject*> objVec;

    for (int i = 0; i < 4; i++)
    {
        objVec.push_back(new GameObject());
        objVec.back()->Initialize();
    }

    //Camera Test Object
    std::shared_ptr<CPN_Camera> camera = std::make_shared<CPN_Camera>();
    objVec[0]->AddComponent(*camera);
    std::shared_ptr<CPN_CameraController> cameraContr = std::make_shared<CPN_CameraController>();
    objVec[0]->AddComponent(*cameraContr);
    objVec[1]->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    //Renderer Test Object
    std::shared_ptr<CPN_Renderer> renderer = std::make_shared<CPN_Renderer>();
    objVec[1]->AddComponent(*renderer);
    objVec[1]->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));

    //Lights test Objects
    //Directional
    std::shared_ptr<CPN_LightCaster> directionalLight = std::make_shared<CPN_LightCaster>();
    directionalLight->SetData(LIGHTTYPE_Directional,
                                glm::vec3(0.1f, 0.1f, 0.1f),
                                glm::vec3(0.96f, 0.38f, 0.17f),
                                glm::vec3(1.0f, 1.0f, 1.0f),
                                0.0f,
                                0.0f,
                                0.0f,
                                0.0f);
    objVec[2]->AddComponent(*directionalLight);
    objVec[2]->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    objVec[2]->GetTransform()->RotateByAngle(glm::vec2(150.0f, 25.0f));

    //Point
    std::shared_ptr<CPN_LightCaster> pointLight = std::make_shared<CPN_LightCaster>();
    pointLight->SetData(LIGHTTYPE_Point,
                                glm::vec3(0.0f, 0.1f, 0.1f),
                                glm::vec3(0.0f, 0.13f, 0.8f),
                                glm::vec3(0.0f, 0.16f, 1.0f),
                                0.14f,
                                0.07f,
                                0.0f,
                                0.0f);
    objVec[3]->AddComponent(*pointLight);
    objVec[3]->GetTransform()->SetPosition(glm::vec3(-0.5f, -1.0f, -11.0f));

    //Spot (Added on the Camera GameObject)
    std::shared_ptr<CPN_LightCaster> spotLight = std::make_shared<CPN_LightCaster>();
    spotLight->SetData(LIGHTTYPE_Spot,
                                glm::vec3(0.1f, 0.1f, 0.1f),
                                glm::vec3(0.8f, 0.8f, 0.8f),
                                glm::vec3(1.0f, 1.0f, 1.0f),
                                0.35f,
                                0.44f,
                                glm::cos(glm::radians(9.0f)),
                                glm::cos(glm::radians(12.0f)));
    objVec[0]->AddComponent(*spotLight);

    //--End Test--

    float lastTick = (float)glfwGetTime();
    float currentTick = lastTick;

    //Engine Loop
    while (enginePtr->IsRunning())
    {
        lastTick = currentTick;
        currentTick = (float)glfwGetTime();

        enginePtr->InputEvents();
        enginePtr->Update(currentTick - lastTick);
        enginePtr->LateUpdate(currentTick - lastTick);
        enginePtr->Render();
    }

    //Engine Stop
    enginePtr->Quit();

    return 0;
}