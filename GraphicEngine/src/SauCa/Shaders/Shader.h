#ifndef SHADER_H
#define SHADER_H

#include "Exports.h"
#include <string>
#include <iostream>



class SAUCA_API Shader
{
public:
    int ID;
    Shader();
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
    //    FSPATH = R"($(SolutionDir)Shader\fs.shader)"
private:
    const std::string vspath = "Shader/vs.shader";
    const std::string fspath = "Shader/fs.shader";
	
    const std::string vsDefaultSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "out vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos, 1.0);\n"
        "ourColor = aColor;\n"
        "}\0";
    const std::string fsDefaultSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(ourColor, 1.0);\n"
        "}\0";
	 

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(unsigned int shader, std::string type);
};
#endif

