#ifndef  VERTEX_H
#define VERTEX_H

#include <glm\glm.hpp>

#pragma once
/// <summary>
/// Contains all Vertex data.
/// </summary>
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normale;
	glm::vec2 texCoords;
};
#endif