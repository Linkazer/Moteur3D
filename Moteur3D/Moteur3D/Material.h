#ifndef  MEMATERIAL_H
#define MATERIAL_H

#include <vector>

#pragma once
class Texture;
class Shader;
class aiMaterial;
enum TextureType;

class Material
{
public:
	explicit Material();
	~Material();

	/// <summary>
	/// Load the Material from an Assimp Material data.
	/// </summary>
	/// <param name="materialData">The Assimp Material to get the data from.</param>
	/// <param name="modeleDirectory">The directory where the Modele is stored.</param>
	void LoadMaterial(aiMaterial& materialData, std::string modeleDirectory);

	/// <summary>
	/// Set the Shader that will be used by the Material.
	/// </summary>
	/// <param name="shaderToUse">The Shader to use for this Material.</param>
	void SetShader(Shader& shaderToUse);
	/// <summary>
	/// Get the Shader used by the Material.
	/// </summary>
	/// <returns>The Shader used by the Material</returns>
	Shader& GetShader();

	/// <summary>
	/// Get every Textures used by the Material.
	/// </summary>
	/// <returns>Every Textures used by the Material.</returns>
	std::vector<Texture> GetTextures();

	inline float GetShininess() { return shininess; }

private :
	std::vector<Texture> textures;
	float shininess;
	Shader* shader;

	//REVIEW : Both function should be put in a TextureManager class.
	void LoadTextures(aiMaterial* material, aiTextureType textureType, std::string textureTypeName, std::string modeleDirectory);
	unsigned int GetTextureFromFile(const char* path, const std::string directory, bool gamma = false);
};
#endif