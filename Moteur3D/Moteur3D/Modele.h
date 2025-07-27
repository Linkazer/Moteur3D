#ifndef  MODELE_H
#define MODELE_H

#include <vector>
#include <string>
#include <memory>

#pragma once
class Mesh;
class aiNode;
class aiScene;
class aiMesh;
//Texture and Material classes (Could be put in a loading class)
class Material;
class Texture;
class aiMaterial;
enum aiTextureType;

class Modele
{
public:
	explicit Modele();
	virtual ~Modele();

	/// <summary>
	/// Load the Modele.
	/// </summary>
	/// <param name="path">The path where the Modele is stored.</param>
	void LoadModele(std::string const& path, bool isOpaque);

	/// <summary>
	/// Get all the Modele's meshes.
	/// </summary>
	/// <returns>All the Modele's meshes.</returns>
	inline std::vector<std::shared_ptr<Mesh>> GetMeshes() { return meshes; }
	/// <summary>
	/// Get all the Modele's materials.
	/// </summary>
	/// <returns>All the Modele's materials.</returns>
	inline std::vector<std::shared_ptr<Material>> GetMaterials() { return materials; }

private :
	std::vector<std::shared_ptr<Material>> materials;
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::string modelDirectoryPath;

	/// <summary>
	/// Process an Assimp Node.
	/// </summary>
	/// <param name="node">The Node to process.</param>
	/// <param name="scene">The parent Scene used.</param>
	void ProcessAssimpNode(aiNode* node, const aiScene* scene);
	/// <summary>
	/// Process an Assimp Material and transcribes it in a Material class.
	/// </summary>
	/// <param name="materialToProcess">The Assimp Material to process.</param>
	/// <param name="scene">The parent Scene used.</param>
	/// <returns>The newly created Material.</returns>
	Material ProcessMaterial(aiMaterial* materialToProcess, const aiScene* scene, bool isOpaque);
	/// <summary>
	/// Process an Assimp Mesh and transcribes it in a Mesh class.
	/// </summary>
	/// <param name="mesh">The Assimp Mesh to process</param>
	/// <param name="scene">The parent Scene used.</param>
	/// <returns>The newly created Mesh.</returns>
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
};
#endif
