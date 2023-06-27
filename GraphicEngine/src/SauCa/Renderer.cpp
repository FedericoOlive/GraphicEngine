#include "Renderer.h"

#include "GameObjects/GameObject.h"
#include "Render/Camera.h"

using namespace std;

std::list<Component*> Renderer::allRenderList;
std::list<Camera*> Renderer::cameras;

Shader* Renderer::defaultShaderSkybox;
Shader* Renderer::defaultShaderSolid;
Shader* Renderer::defaultShaderTexture;
Shader* Renderer::defaultShader;

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
    if (defaultShaderSkybox != nullptr)
    {
        delete defaultShaderSkybox;
        defaultShaderSkybox = nullptr;
    }
    if (defaultShaderSolid != nullptr)
    {
        delete defaultShaderSolid;
        defaultShaderSolid = nullptr;
    }
    if (defaultShaderTexture != nullptr)
    {
        delete defaultShaderTexture;
        defaultShaderTexture = nullptr;
    }
    if (defaultShader != nullptr)
    {
        delete defaultShader;
        defaultShader = nullptr;
    }
}

void Renderer::CreateShader()
{
    defaultShaderSkybox = new Shader();
    defaultShaderSkybox->CreateDefaultSkyboxShader();
    defaultShaderSolid = new Shader();
    defaultShaderSolid->CreateDefaultSolidShader();
    defaultShaderTexture = new Shader();
    defaultShaderTexture->CreateDefaultTextureShader();
    defaultShader = new Shader();
    defaultShader->CreateDefaultShader();
    std::cout << "\n";
}

void Renderer::CreateRenderer()
{
    glewExperimental = GL_TRUE;
    glewInit();
	
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
}

void Renderer::DrawEntity(unsigned int VAO, int sizeIndex, glm::mat4 model, unsigned int textureID, Material* material, float alpha, Camera* camera)
{
	material->shader->Use();
	
    SetMatrix(material->shader, camera, model);
    SetMaterial(material, alpha, textureID);
    SetLights(material);
	
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeIndex, GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}

void Renderer::DrawModel(glm::mat4 model, unsigned textureID, Material* material, float alpha, Camera* camera, std::vector<Mesh> meshes)
{
    material->shader->Use();
	
    SetMatrix(material->shader, camera, model);
    SetMaterial(material, alpha, textureID);
    SetLights(material);
	
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(material->shader);
	
    glUseProgram(0);
}

void Renderer::DrawCubemap(unsigned int VAO, unsigned int cubemapTexture, Material* material, std::list<Camera*> cameras)
{
    for (auto iterCamera = cameras.begin(); iterCamera != cameras.end(); ++iterCamera)
    {
        if ((*iterCamera)->isEnable && (*iterCamera)->gameobject->IsActive() && (*iterCamera)->gameobject->IsActiveInHierarch())
        {
            if ((*iterCamera)->isDrawSkybox)
            {
                (*iterCamera)->BeginDraw();
                glm::mat4 model = glm::mat4(1.0f);
                glm::mat4 view = (*iterCamera)->viewMatrix;
                glm::mat4 projection = (*iterCamera)->projectionMatrix;

                // draw skybox as last
                glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
                material->shader->Use();
                view = glm::mat4(glm::mat3((*iterCamera)->viewMatrix)); // remove translation from the view matrix
                material->shader->SetMat4("view", view);
                material->shader->SetMat4("projection", projection);
                // skybox cube
                glBindVertexArray(VAO);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                glBindVertexArray(0);
                glDepthFunc(GL_LESS); // set depth function back to default
                glUseProgram(0);
            }
        }
    }
}

void Renderer::SetMatrix(Shader* shader, Camera* camera, glm::mat4 model)
{
    glm::mat4 viewMatrix = camera->viewMatrix;
    glm::mat4 projectionMatrix = camera->projectionMatrix;

    shader->SetMat4("projectionMatrix", projectionMatrix);
    shader->SetMat4("viewMatrix", viewMatrix);
    shader->SetMat4("modelMatrix", model);
    shader->SetVec3("viewPos", camera->transform->GetWorldPosition());
}

void Renderer::SetMaterial(Material* material, float alpha, unsigned int textureID)
{
    material->shader->SetBool("material.hasTexture", material->hasTexture);
    material->shader->SetUnsignedInt("material.texture", textureID);
    material->shader->SetVec3("material.ambient", material->ambient);
    material->shader->SetVec3("material.diffuse", material->diffuse);
    material->shader->SetVec3("material.specular", material->specular);
    material->shader->SetVec3("material.colorTint", material->colorTint);
    material->shader->SetFloat("material.shininess", material->shininess);
	
    material->shader->SetVec3("colorTint", material->colorTint);
    material->shader->SetFloat("alpha", alpha);
    material->shader->SetUnsignedInt("ourTexture", textureID);
}

void Renderer::SetLights(Material* material)
{
    const int maxDirLights      = 20;
    const int maxPointLights    = 20;
    const int maxSpotLights     = 20;

    material->shader->SetInt("dirLightAmount", directionalLights.size());
    material->shader->SetInt("pointLightAmount", pointLights.size());
    material->shader->SetInt("spotLightAmount", spotLights.size());

    int i = 0;
    for (auto dirLight = directionalLights.begin(); dirLight != directionalLights.end(); ++dirLight)
    {
        if ((*dirLight)->isEnable && (*dirLight)->gameobject->IsActive() && (*dirLight)->gameobject->IsActiveInHierarch())
        {
            string dirLightString = "dirLights[" + to_string(i) + "].";

            material->shader->SetVec3(dirLightString + "direction", (*dirLight)->transform->forward());
            material->shader->SetVec3(dirLightString + "lightColor", (*dirLight)->lightColor);
            material->shader->SetVec3(dirLightString + "ambient", (*dirLight)->ambient * (*dirLight)->powerAmbient);
            material->shader->SetVec3(dirLightString + "diffuse", (*dirLight)->diffuse * (*dirLight)->powerDiffuse);
            material->shader->SetVec3(dirLightString + "specular", (*dirLight)->specular * (*dirLight)->powerSpecular);

            i++;
            if (i > maxDirLights)
                break;
        }
    }

    i = 0;
    for (auto pointLight = pointLights.begin(); pointLight != pointLights.end(); ++pointLight)
    {
        if ((*pointLight)->isEnable && (*pointLight)->gameobject->IsActive() && (*pointLight)->gameobject->IsActiveInHierarch())
        {
            string pointLightString = "pointLights[" + to_string(i) + "].";

            material->shader->SetVec3(pointLightString + "position", (*pointLight)->transform->GetWorldPosition());
            material->shader->SetVec3(pointLightString + "lightColor", (*pointLight)->lightColor);
            material->shader->SetVec3(pointLightString + "ambient", (*pointLight)->ambient * (*pointLight)->powerAmbient);
            material->shader->SetVec3(pointLightString + "diffuse", (*pointLight)->diffuse * (*pointLight)->powerDiffuse);
            material->shader->SetVec3(pointLightString + "specular", (*pointLight)->specular * (*pointLight)->powerSpecular);
            material->shader->SetFloat(pointLightString + "constant", (*pointLight)->constant);
            material->shader->SetFloat(pointLightString + "linear", (*pointLight)->linear);
            material->shader->SetFloat(pointLightString + "quadratic", (*pointLight)->quadratic);

            i++;
            if (i > maxPointLights)
                break;
        }
    }

    i = 0;
    for (auto spotLight = spotLights.begin(); spotLight != spotLights.end(); ++spotLight)
    {
        if ((*spotLight)->isEnable && (*spotLight)->gameobject->IsActive() && (*spotLight)->gameobject->IsActiveInHierarch())
        {
            string spotLightString = "spotLights[" + to_string(i) + "].";

            material->shader->SetVec3(spotLightString + "position", (*spotLight)->transform->GetWorldPosition());
            material->shader->SetVec3(spotLightString + "direction", (*spotLight)->transform->forward());
            material->shader->SetVec3(spotLightString + "lightColor", (*spotLight)->lightColor);
            material->shader->SetVec3(spotLightString + "ambient", (*spotLight)->ambient * (*spotLight)->powerAmbient);
            material->shader->SetVec3(spotLightString + "diffuse", (*spotLight)->diffuse * (*spotLight)->powerDiffuse);
            material->shader->SetVec3(spotLightString + "specular", (*spotLight)->specular * (*spotLight)->powerSpecular);
            material->shader->SetFloat(spotLightString + "constant", (*spotLight)->constant);
            material->shader->SetFloat(spotLightString + "linear", (*spotLight)->linear);
            material->shader->SetFloat(spotLightString + "quadratic", (*spotLight)->quadratic);
            material->shader->SetFloat(spotLightString + "cutOff", glm::cos(glm::radians((*spotLight)->cutOff)));
            material->shader->SetFloat(spotLightString + "outerCutOff", glm::cos(glm::radians((*spotLight)->outerCutOff)));

            i++;
            if (i > maxSpotLights)
                break;
        }
    }
}

void Renderer::Clear(GLbitfield field)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DrawLinesFrustum(Camera* camera)
{
    Plane left      = camera->frustum->leftFace;
    Plane right     = camera->frustum->rightFace;
    Plane top       = camera->frustum->topFace;
    Plane bottom    = camera->frustum->bottomFace;
    Plane far       = camera->frustum->farFace;
    Plane near      = camera->frustum->nearFace;
	
    glm::vec3 nearLeftTop =     Plane::FindIntersectionPoint(near, left,  top);
    glm::vec3 nearLeftBottom =  Plane::FindIntersectionPoint(near, left,  bottom);
    glm::vec3 nearRightTop =    Plane::FindIntersectionPoint(near, right, top);
    glm::vec3 nearRightBottom = Plane::FindIntersectionPoint(near, right, bottom);
    glm::vec3 farLeftTop =      Plane::FindIntersectionPoint(far,  left,  top);
    glm::vec3 farLeftBottom =   Plane::FindIntersectionPoint(far,  left,  bottom);
    glm::vec3 farRightTop =     Plane::FindIntersectionPoint(far,  right, top);
    glm::vec3 farRightBottom =  Plane::FindIntersectionPoint(far,  right, bottom);
    enum DrawMode { Both, PlaneNear, PlaneFar };
    DrawMode drawMode = Both;
    switch (drawMode)
	{
    case Both:
        Renderer::DrawLine(nearLeftTop, nearLeftBottom);
        Renderer::DrawLine(nearLeftTop, nearRightTop);
        Renderer::DrawLine(nearLeftTop, farLeftBottom);

        Renderer::DrawLine(nearRightBottom, nearLeftBottom);
        Renderer::DrawLine(nearRightBottom, nearRightTop);
        Renderer::DrawLine(nearRightBottom, farRightBottom);

        Renderer::DrawLine(farRightTop, farRightBottom);
        Renderer::DrawLine(farRightTop, nearRightTop);
        Renderer::DrawLine(farRightTop, farLeftTop);

        Renderer::DrawLine(farLeftBottom, farLeftTop);
        Renderer::DrawLine(farLeftBottom, nearLeftBottom);
        Renderer::DrawLine(farLeftBottom, farRightBottom);
	    break;
    case PlaneNear:
        Renderer::DrawLine(nearRightBottom, nearRightTop);
        Renderer::DrawLine(nearRightBottom, nearLeftBottom);
        Renderer::DrawLine(nearLeftTop, nearRightTop);
        Renderer::DrawLine(nearLeftTop, nearLeftBottom);
	    break;
    case PlaneFar:
        Renderer::DrawLine(farRightBottom, farRightTop);
        Renderer::DrawLine(farRightBottom, farLeftBottom);
        Renderer::DrawLine(farLeftTop, farRightTop);
        Renderer::DrawLine(farLeftTop, farLeftBottom);
	    break;
    default: ;
    }
	
   
}

void Renderer::Draw()
{
    int count = 0;
    Camera* cam = (*cameras.begin());
    Frustum* frustum = cam->frustum;
    cam->frustum->Update(cam->fov, cam->aspect, cam->far, cam->near, cam->transform->GetWorldPosition(), cam->transform->forward(), cam->transform->right(), cam->transform->up());
    for (auto iterCamera = cameras.begin(); iterCamera != cameras.end(); ++iterCamera)
    {
        count++;
        //Frustum* frustum = cam->frustum;
        //(*iterCamera)->frustum->Update(cam->fov, cam->aspect, cam->far, cam->near, cam->transform->GetWorldPosition(), cam->transform->forward(), cam->transform->right(), cam->transform->up());
        (*iterCamera)->BeginDraw();
        for (auto iterComponent = (*iterCamera)->cameraRenderList.begin(); iterComponent != (*iterCamera)->cameraRenderList.end(); ++iterComponent)
        {
            glm::mat4 model = (*iterComponent)->transform->GetModelMatrix();
            glm::vec3 right = (*iterComponent)->transform->right();
            glm::vec3 up = (*iterComponent)->transform->up();
            glm::vec3 forward = (*iterComponent)->transform->forward();

            bool isOnFrustum = (*iterComponent)->transform->aabb->IsOnFrustum((*frustum), (*iterComponent)->transform->aabb);
        	
            if (isOnFrustum)
            {
                bool isRenderizable = (*iterComponent)->IsRenderizable();
                bool isEnable = (*iterComponent)->isEnable;
                bool isActive = (*iterComponent)->gameobject->IsActive();
                bool isActiveInHierarch = (*iterComponent)->gameobject->IsActiveInHierarch();

                if (isRenderizable && isEnable && isActive && isActiveInHierarch)
                    (*iterComponent)->Draw((*iterCamera));
            }
        }
    }
}

void Renderer::SwapBuffers(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

void Renderer::BindGenBufferObject(unsigned int& buffer)
{
    glGenVertexArrays(1, &buffer);
    glBindVertexArray(buffer);
}

void Renderer::UnBindGenBufferObject()
{
    glBindVertexArray(0);
}

void Renderer::GenBuffer(int amount, unsigned int& buffer)
{
    // Generar objeto de búfer de vértices para posición de vértices
    glGenBuffers(amount, &buffer);
}

void Renderer::BindBufferData(unsigned int buffer, int atribPointer, int atribPointerSize, int size, float* arrayData, int modeDataStore)
{
    glEnableVertexAttribArray(atribPointer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), arrayData, (modeDataStore == 0) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
    glVertexAttribPointer(atribPointer, atribPointerSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Renderer::BindIndex(unsigned int buffer, int size, int* arrayData)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(int), arrayData, GL_STATIC_DRAW);
}

void Renderer::UnBindObject(VertexData* vertexData)
{
    UnBindObject(vertexData->VAO, vertexData->VBO, vertexData->CBO, vertexData->NBO, vertexData->UVB, vertexData->EBO);
}

void Renderer::UnBindObject(unsigned int& VAO, unsigned int& VBO, unsigned int& CBO, unsigned int& NBO, unsigned int& UVB, unsigned int& EBO)
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &CBO);
    glDeleteBuffers(1, &NBO);
    glDeleteBuffers(1, &UVB);
    glDeleteBuffers(1, &EBO);
}

void Renderer::BindTextures(unsigned int& texture)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Renderer::AddCamera(Camera* cam)
{
    cameras.push_back(cam);

    if (cam->autoAddGameObjects)
    {
        for (auto iter = allRenderList.begin(); iter != allRenderList.end(); ++iter)
        {
            cam->cameraRenderList.push_back((*iter));
        }
    }
}

void Renderer::AddToRenderList(Component* component)
{
    allRenderList.push_back(component);

    for (auto iter = cameras.begin(); iter != cameras.end(); ++iter)
        if ((*iter)->autoAddGameObjects)
            (*iter)->cameraRenderList.push_back(component);
}

void Renderer::RemoveCamera(Camera* cam)
{
    for (auto iter = cameras.begin(); iter != cameras.end(); ++iter)
    {
        if ((*iter) == cam)
        {
            cameras.erase(iter);
            break;
        }
    }
}

void Renderer::DrawLine(const glm::vec3& startPoint, const glm::vec3& endPoint, float lineWidth, glm::vec3 color, Camera* camera)
{
    if (camera == nullptr)
        camera = *cameras.begin();
    if (camera == nullptr)
        return;

    camera->BeginDraw();
    Shader* shader = GetDefaultShaderSolid();
    shader->Use();

    shader->SetMat4("modelMatrix", glm::mat4(1.0f));
    shader->SetMat4("viewMatrix", camera->viewMatrix);
    shader->SetMat4("projectionMatrix", camera->projectionMatrix);
    shader->SetVec3("colorTint", color);
    shader->SetFloat("alpha", 1);
    shader->SetBool("useBaseColor", false);

    glLineWidth(lineWidth);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    
    glBegin(GL_LINES);
    glVertex3f(startPoint.x, startPoint.y, startPoint.z);
    glVertex3f(endPoint.x, endPoint.y, endPoint.z);
    glEnd();
    shader->SetBool("useBaseColor", true);
}