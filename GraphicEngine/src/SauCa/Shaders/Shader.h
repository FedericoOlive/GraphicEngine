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
    const std::string  fspath = "Shader/fs.shader";

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(unsigned int shader, std::string type);
};
#endif

