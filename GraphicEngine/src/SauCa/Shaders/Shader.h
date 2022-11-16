#ifndef SHADER_H
#define SHADER_H

#include "Exports.h"
#include <string>
#include <iostream>
#include <glm/glm/vec3.hpp>

class SAUCA_API Shader
{
private:
#pragma region Source Shaders Defaults
    const std::string vertexShaderSolidSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "out vec3 ourColor;\n"
        "uniform mat4 projectionMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 modelMatrix;\n"
        "void main()\n"
        "{\n"
        "gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
        "ourColor = aColor;\n"
        "}\n";
    const std::string fragmentShaderSolidSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "uniform vec3 colorTint;\n"
        "uniform float alpha;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(ourColor.x * colorTint.x, ourColor.y * colorTint.y, ourColor.z * colorTint.z, alpha);\n"
        "}";
    const std::string vertexShaderTextureSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "layout(location = 2) in vec2 aTexCoord;\n"
        "out vec3 ourColor;\n"
        "out vec2 TexCoord;\n"
        "uniform mat4 projectionMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 modelMatrix;\n"
        "void main()\n"
        "{\n"
        "gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
        "ourColor = aColor;\n"
        "TexCoord = aTexCoord;\n"
        "}\n";
    const std::string fragmentShaderTextureSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"

        "in vec3 ourColor;\n"
        "in vec2 TexCoord;\n"

        "uniform sampler2D ourTexture;\n"
        "uniform vec3 colorTint;\n"
        "uniform float alpha;\n"

        "void main()\n"
        "{\n"
        "FragColor = texture(ourTexture, TexCoord) * vec4(ourColor.x * colorTint.x, ourColor.y * colorTint.y, ourColor.z * colorTint.z, alpha);\n"
        "}\n";
#pragma endregion
    
    void CheckCompileErrors(unsigned int shader, std::string type);
	
public:
    int ID;
    Shader(bool hasTexture);
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath, bool hasTexture);
    ~Shader();
    void CreateShader(std::string vsPath, std::string fsPath, bool hasTexture);
    void CreateShaderBySource(std::string vertexShaderSource, std::string fragmentShaderSource);
    void Use();
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;

};
#endif