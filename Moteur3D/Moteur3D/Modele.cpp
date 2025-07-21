#include <glad\glad.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "Modele.h"

#include "stb_image.h"

#include "Mesh.h"
#include "Material.h"
#include "Vertex.h"
#include "Texture.h"


Modele::Modele()
{
	
}

Modele::~Modele()
{
}

void Modele::LoadModele(std::string const& path)
{
	//Load with Assimp
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	//Check for Error
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	
	modelDirectoryPath = path.substr(0, path.find_last_of('/'));

	//Material process
	for (unsigned int i = 0; i < scene->mNumMaterials; i++)
	{
		materials.push_back(std::make_shared<Material>(ProcessMaterial(scene->mMaterials[i], scene)));
	}

	//Node process
	ProcessAssimpNode(scene->mRootNode, scene);
}

void Modele::ProcessAssimpNode(aiNode* node, const aiScene* scene)
{
	//Mesh process
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(std::make_shared<Mesh>(ProcessMesh(mesh, scene)));
	}

	//Child Node process
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessAssimpNode(node->mChildren[i], scene);
	}
}

Material Modele::ProcessMaterial(aiMaterial* materialToProcess, const aiScene* scene)
{
	Material processedMaterial;

	processedMaterial.LoadMaterial(*materialToProcess, modelDirectoryPath); //REVIEW : See if we should put all the Assimp logic outside of the Material class.

	return processedMaterial;
}

Mesh Modele::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	//Vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;//TEST : Voir si on peut le sortir de la boucle (Le push_back devrait faire une copie)
		glm::vec3 calculVector; //Use to compute vectors as Assimp use its own vector class.

		calculVector.x = mesh->mVertices[i].x;
		calculVector.y = mesh->mVertices[i].y;
		calculVector.z = mesh->mVertices[i].z;
		vertex.position = calculVector;

		if (mesh->HasNormals())
		{
			calculVector.x = mesh->mNormals[i].x;
			calculVector.y = mesh->mNormals[i].y;
			calculVector.z = mesh->mNormals[i].z;
			vertex.normale = calculVector;
		}

		if (mesh->mTextureCoords[0] != nullptr)
		{
			calculVector.x = mesh->mTextureCoords[0][i].x; //NOTE : We can handle multiple Texture coordinates, but for now we only do one.
			calculVector.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = glm::vec2{ calculVector.x, calculVector.y };
		}

		vertices.push_back(vertex);
	}

	//Indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return Mesh(vertices, indices, mesh->mMaterialIndex);
}