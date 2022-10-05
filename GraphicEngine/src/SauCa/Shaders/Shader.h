#ifndef SHADER_H
#define SHADER_H

#include "Exports.h"
#include <string>
#include <iostream>

class SAUCA_API Shader
{
public:
    int ID;
    Shader(bool isPrimitive);
    ~Shader();
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    // activate the shader
    // ------------------------------------------------------------------------
    void Use();
    // utility uniform functions
    // ------------------------------------------------------------------------
    void SetBool(const std::string& name, bool value) const;
    // ------------------------------------------------------------------------
    void SetInt(const std::string& name, int value) const;
    // ------------------------------------------------------------------------
    void SetFloat(const std::string& name, float value) const;
    //VSPATH = R"($(SolutionDir)Shader\vs.shader)"
    //FSPATH = R"($(SolutionDir)Shader\fs.shader)"
private:
    const std::string vspath = "Shader/vs.shader";
    const std::string fspath = "Shader/fs.shader";
	
    const std::string vspathTexture = "Shader/vsTexture.shader";
    const std::string fspathTexture = "Shader/fsTexture.shader";
	
    const std::string vsDefaultSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "out vec3 ourColor;\n"
        "uniform mat4 projectionMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 modelMatrix;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
        "    ourColor = aColor;\n"
        "}\0";
    const std::string fsDefaultSource =
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
        "    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
        "    ourColor = aColor;\n"
        "    TexCoord = aTexCoord;\n"
        "}\0";
	 

    void CreateShapeShader();
    void CreateTextureShader();
    void CreateShader(std::string vsPath, std::string fsPath);
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(unsigned int shader, std::string type);
};
#endif

