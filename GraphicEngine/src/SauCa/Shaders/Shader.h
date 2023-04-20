#ifndef SHADER_H
#define SHADER_H

#include "glew.h"
#include "Exports.h"
#include <string>
#include <iostream>
#include <glm/glm/vec2.hpp>
#include <glm/glm/vec3.hpp>
#include <glm/glm/vec4.hpp>
#include <glm/glm/mat2x2.hpp>
#include <glm/glm/mat3x3.hpp>
#include <glm/glm/mat4x4.hpp>

class SAUCA_API Shader
{
private:
#pragma region Source Shaders Defaults
    const std::string vertexShaderSolidSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "layout(location = 2) in vec3 aNormal;\n"
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
        "layout(location = 2) in vec3 aNormal;\n"
        "layout(location = 3) in vec2 aTexCoord;\n"
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
	const std::string vertexShaderBasicLightSource = 
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aNormal;\n"

		"out vec3 FragPos;\n"
		"out vec3 Normal;\n"

		"uniform mat4 modelMatrix;\n"
		"uniform mat4 viewMatrix;\n"
		"uniform mat4 projectionMatrix;\n"

		"void main()\n"
		"{\n"
			"FragPos = vec3(modelMatrix * vec4(aPos, 1.0));\n"
			"Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;\n"
			"gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);\n"
		"}\n";
	const std::string fragmentShaderBasicLightSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"

		"in vec3 Normal;\n"
		"in vec3 FragPos;\n"

		"uniform vec3 lightPos;\n"
		"uniform vec3 viewPos;\n"
		"uniform vec3 lightColor;\n"
		"uniform vec3 colorTint;\n"

		"void main()\n"
		"{\n"
			// ambient
			"float ambientStrength = 0.1;\n"
			"vec3 ambient = ambientStrength * lightColor;\n"
			// diffuse 
			"vec3 norm = normalize(Normal);\n"
			"vec3 lightDir = normalize(lightPos - FragPos);\n"
			"float diff = max(dot(norm, lightDir), 0.0);\n"
			"vec3 diffuse = diff * lightColor;\n"
			// specular
			"float specularStrength = 0.5;\n"
			"vec3 viewDir = normalize(viewPos - FragPos);\n"
			"vec3 reflectDir = reflect(-lightDir, norm);\n"
			"float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
			"vec3 specular = specularStrength * spec * lightColor;\n"

			"vec3 result = (ambient + diffuse + specular) * colorTint;\n"
			"FragColor = vec4(result, 1.0);\n"
		"}\n";
	
    const std::string vertexShaderLightSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos; \n"
        "layout(location = 1) in vec3 aColor; \n"
        "layout(location = 2) in vec3 aNormal; \n"
        "layout(location = 3) in vec2 aTexCoords; \n"
        "out vec3 FragPos; \n"
        "out vec3 Normal; \n"
        "out vec2 TexCoords; \n"
        "uniform mat4 modelMatrix; \n"
        "uniform mat4 viewMatrix; \n"
        "uniform mat4 projectionMatrix; \n"
        "void main()\n"
        "{\n"
        "    FragPos = vec3(modelMatrix * vec4(aPos, 1.0)); \n"
        "    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal; \n"
        "    TexCoords = aTexCoords; \n"
        "    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0); \n"
        "}\n";
    const std::string fragmentShaderLightSource =
	    "#version 330 core\n"
		"out vec4 FragColor;\n"
		"struct Material {\n"
		"    sampler2D diffuse;\n"
		"    sampler2D specular;\n"
		"    float shininess;\n"
		"};\n"
		"struct DirLight {\n"
		"    vec3 direction;\n"
		"    vec3 ambient;\n"
		"    vec3 diffuse;\n"
		"    vec3 specular;\n"
		"};\n"
		"struct PointLight {\n"
		"    vec3 position;\n"
		"    float constant;\n"
		"    float linear;\n"
		"    float quadratic;\n"
		"    vec3 ambient;\n"
		"    vec3 diffuse;\n"
		"    vec3 specular;\n"
		"};\n"
		"struct SpotLight {\n"
		"    vec3 position;\n"
		"    vec3 direction;\n"
		"    float cutOff;\n"
		"    float outerCutOff;\n"
		"    float constant;\n"
		"    float linear;\n"
		"    float quadratic;\n"
		"    vec3 ambient;\n"
		"    vec3 diffuse;\n"
		"    vec3 specular;\n"
		"};\n"
		"#define NR_POINT_LIGHTS 4\n"
		"in vec3 FragPos;\n"
		"in vec3 Normal;\n"
		"in vec2 TexCoords;\n"
		"uniform vec3 viewPos;\n"
		"uniform DirLight dirLight;\n"
		"uniform PointLight pointLights[NR_POINT_LIGHTS];\n"
		"uniform SpotLight spotLight;\n"
		"uniform Material material;\n"
		"vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);\n"
		"vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);\n"
		"vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);\n"
		"void main()\n"
		"{\n"
		"    vec3 norm = normalize(Normal);\n"
		"    vec3 viewDir = normalize(viewPos - FragPos);\n"
		"    vec3 result = CalcDirLight(dirLight, norm, viewDir);\n"
		"    for (int i = 0; i < NR_POINT_LIGHTS; i++)\n"
		"        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);\n"
		"    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);\n"
		"    FragColor = vec4(result, 1.0);\n"
		"}\n"
		"vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)\n"
		"{\n"
		"    vec3 lightDir = normalize(-light.direction);\n"
		"    float diff = max(dot(normal, lightDir), 0.0);\n"
		"    vec3 reflectDir = reflect(-lightDir, normal);\n"
		"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
		"    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));\n"
		"    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));\n"
		"    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));\n"
		"    return (ambient + diffuse + specular);\n"
		"}\n"
		"vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)\n"
		"{\n"
		"    vec3 lightDir = normalize(light.position - fragPos);\n"
		"    float diff = max(dot(normal, lightDir), 0.0);\n"
		"    vec3 reflectDir = reflect(-lightDir, normal);\n"
		"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
		"    float distance = length(light.position - fragPos);\n"
		"    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));\n"
		"    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));\n"
		"    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));\n"
		"    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));\n"
		"    ambient *= attenuation;\n"
		"    diffuse *= attenuation;\n"
		"    specular *= attenuation;\n"
		"    return (ambient + diffuse + specular);\n"
		"}\n"
		"vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)\n"
		"{\n"
		"    vec3 lightDir = normalize(light.position - fragPos);\n"
		"    float diff = max(dot(normal, lightDir), 0.0);\n"
		"    vec3 reflectDir = reflect(-lightDir, normal);\n"
		"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
		"    float distance = length(light.position - fragPos);\n"
		"    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));\n"
		"    float theta = dot(lightDir, normalize(-light.direction));\n"
		"    float epsilon = light.cutOff - light.outerCutOff;\n"
		"    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);\n"
		"    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));\n"
		"    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));\n"
		"    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));\n"
		"    ambient *= attenuation * intensity;\n"
		"    diffuse *= attenuation * intensity;\n"
		"    specular *= attenuation * intensity;\n"
		"    return (ambient + diffuse + specular);\n"
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

    void setBool(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }
    void setInt(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
    void setFloat(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
    void setVec2(const std::string& name, const glm::vec2& value) const { glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    void setVec2(const std::string& name, float x, float y) const { glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); }
    void setVec3(const std::string& name, const glm::vec3& value) const { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    void setVec3(const std::string& name, float x, float y, float z) const { glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); }
    void setVec4(const std::string& name, const glm::vec4& value) const { glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    void setVec4(const std::string& name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); }
    void setMat2(const std::string& name, const glm::mat2& mat) const { glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    void setMat3(const std::string& name, const glm::mat3& mat) const { glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    void setMat4(const std::string& name, const glm::mat4& mat) const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
};
#endif