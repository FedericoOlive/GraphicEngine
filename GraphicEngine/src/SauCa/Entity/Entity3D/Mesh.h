#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Exports.h"
#include "Shaders/Shader.h"

#define MAX_BONE_INFLUENCE 4
class Camera;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct MeshTexture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class SAUCA_API Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<MeshTexture> textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);
    void Draw(Shader* shader);
	
private:	
    unsigned int VBO;
    unsigned int EBO;
    void setupMesh();
};

#endif