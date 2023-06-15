#ifndef SHADER_H
#define SHADER_H

#include "glew/glew.h"
#include "Exports.h"
#include <string>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

class SAUCA_API Shader
{
private:    
    void CheckCompileErrors(unsigned int shader, std::string type);
    void CreateShaderBySource(std::string vertexShaderSource, std::string fragmentShaderSource);
	
public:
    int ID;
    Shader();
    ~Shader();
	
    void CreateShader(std::string vsPath, std::string fsPath);
	void CreateDefaultSkyboxShader();
	void CreateDefaultSolidShader();
    void CreateDefaultTextureShader();
    void CreateDefaultShader();

    void Use();
	
    void SetBool(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }
    void SetInt(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
    void SetUnsignedInt(const std::string& name, unsigned int value) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), static_cast<GLfloat>(value)); }
    void SetFloat(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
    void SetVec2(const std::string& name, const glm::vec2& value) const { glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    void SetVec2(const std::string& name, float x, float y) const { glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); }
    void SetVec3(const std::string& name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    void SetVec3(const std::string& name, float x, float y, float z) const { glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); }
    void SetVec4(const std::string& name, const glm::vec4& value) const { glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    void SetVec4(const std::string& name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); }
    void SetMat2(const std::string& name, const glm::mat2& mat) const { glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    void SetMat3(const std::string& name, const glm::mat3& mat) const { glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    void SetMat4(const std::string& name, const glm::mat4& mat) const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
};
#endif