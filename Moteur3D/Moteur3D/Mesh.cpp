#include "Mesh.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Vertex.h"
#include "Texture.h"

Mesh::Mesh(std::vector<Vertex> nVertices, std::vector<unsigned int> nIndices, unsigned int nMaterialIndex)
{
	vertices = nVertices;
	indices = nIndices;
	materialIndex = nMaterialIndex;

	InitializeMesh();
}

Mesh::~Mesh()
{
}

void Mesh::InitializeMesh()
{
	//Setup VAO, VBO and EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Shader Setup
	//Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//Vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normale));
	//Vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}
