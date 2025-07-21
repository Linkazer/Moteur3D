#ifndef  SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>

#pragma once
class Shader
{
public :
	explicit Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader();

	void Use() const; //NOTE : A const function means this function can't change any member variable of the class.

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec2(const std::string& name, glm::vec2 value) const;
	void SetVec3(const std::string& name, glm::vec3 value) const;
	void SetVec4(const std::string& name, glm::vec4 value) const;
	void SetMat2(const std::string& name, glm::mat2 value) const;
	void SetMat3(const std::string& name, glm::mat3 value) const;
	void SetMat4(const std::string& name, glm::mat4 value) const;

	inline unsigned int GetID() { return id; }

private :
	unsigned int id;

	void CheckCompileError(GLuint shaderId, std::string type);
};
#endif
