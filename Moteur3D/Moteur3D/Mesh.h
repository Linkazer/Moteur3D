#ifndef  MESH_H
#define MESH_H

#include<memory>
#include<vector>

#pragma once
class Vertex;
class Texture;
class Material;

class Mesh
{
public:
	explicit Mesh(std::vector<Vertex> nVertices, std::vector<unsigned int> nIndices, unsigned int nMaterialIndex);
	virtual ~Mesh();

	/// <summary>
	/// Initialize the Mesh with its VBO, EBO and VAO.
	/// </summary>
	void InitializeMesh();

	/// <summary>
	/// Get the VAO of the Mesh.
	/// </summary>
	/// <returns>The VAO of the Mesh.</returns>
	inline unsigned int GetVAO() { return VAO; }

	/// <summary>
	/// Get all indices of the Mesh.
	/// </summary>
	/// <returns>All indices of the Mesh.</returns>
	inline std::vector<unsigned int> GetIndices() { return indices; }

	/// <summary>
	/// Get the index of the Material to use.
	/// </summary>
	/// <returns>The index of the Material to use.</returns>
	inline unsigned int& GetMaterialIndex() { return materialIndex; }

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	unsigned int materialIndex;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};
#endif
