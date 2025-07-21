#ifndef  CPN_RENDERER_H
#define CPN_RENDERER_H


#include<memory>
#include "Component.h"

#pragma once
class Modele;

class CPN_Renderer : public Component
{
public :
	explicit CPN_Renderer();
	virtual ~CPN_Renderer();

	void Initialize(GameObject& nContainingGameObject) override;
	void Destroy() override;

	/// <summary>
	/// Render the Modele used by this Renderer.
	/// </summary>
	void Render();
	
private :
	std::shared_ptr<Modele> modele;
};

#endif
