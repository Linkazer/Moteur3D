#include <assimp/scene.h>
#include <glad\glad.h>

#include <iostream>

#include "stb_image.h"

#include "Texture.h"
#include"Shader.h"

#include "Material.h"

Material::Material(bool isOpaque)
{
	if (isOpaque)
	{
		shader = new Shader("opaque.vs", "opaque.fs");
	}
	else
	{
		shader = new Shader("ShaderTest.vs", "ShaderTest.fs");
	}
}

Material::~Material()
{
}

void Material::LoadMaterial(aiMaterial& materialData, std::string modeleDirectory)
{
	//Setup Textures
	LoadTextures(&materialData, aiTextureType_DIFFUSE, "Diffuse", modeleDirectory);
	LoadTextures(&materialData, aiTextureType_SPECULAR, "Specular", modeleDirectory);
	//LoadTextures(&materialData, aiTextureType_HEIGHT, Normal);	//TODO : A faire après le cours sur les normals
	//LoadTextures(&materialData, aiTextureType_AMBIENT, Height);	//TODO : A faire après le cours sur les normals

	//Setup Material properties
	materialData.Get(AI_MATKEY_SHININESS, shininess);

	//Setup Shader
	//SetShader(shaderToUse); //REVIEW : See where we could store/define the shader to use.
}

void Material::SetShader(Shader& shaderToUse)
{
	shader = &shaderToUse;
}

Shader& Material::GetShader()
{
	return *shader;
}

std::vector<Texture> Material::GetTextures()
{
	return textures;
}

void Material::LoadTextures(aiMaterial* material, aiTextureType textureType, std::string textureTypeName, std::string modeleDirectory)
{
	for (unsigned int i = 0; i < material->GetTextureCount(textureType); i++)
	{
		aiString str;
		material->GetTexture(textureType, i, &str);

		//Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures.size(); j++)
		{
			if (std::strcmp(textures[j].path.data(), str.C_Str()) == 0)
			{
				skip = true; //A texture with the same filepath has already been loaded, continue to next one.
				break;
			}
		}
		if (!skip)
		{
			Texture texture;
			texture.id = GetTextureFromFile(str.C_Str(), modeleDirectory);
			texture.type = textureTypeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
		}
	}
}

unsigned int Material::GetTextureFromFile(const char* path, const std::string modeleDirectory, bool gamma)
{
	std::string filename = std::string(path);
	filename = modeleDirectory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
