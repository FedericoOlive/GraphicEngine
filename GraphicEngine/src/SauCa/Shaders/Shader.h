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
    
private:
    std::string vspath = "D:/Image Campus/4- Gráficos I/GraphicEngineSolution/GraphicEngine/vs.shader";
    std::string fspath = "D:/Image Campus/4- Gráficos I/GraphicEngineSolution/GraphicEngine/fs.shader";
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(unsigned int shader, std::string type);
};
#endif

