#include "Render.h"

std::shared_ptr<Camera> sCamera;

void Render::Start(std::shared_ptr<Camera> camera)
{
    sCamera = camera;
}

void Render::Draw(std::shared_ptr<Object> object)
{
    // set the background color
    auto textures = object->getMaterial()->getTextures();
    for (auto& texture : textures) {
        texture->bind();
    }
    // activate the shader program
    auto shader = object->getShader();
    shader->use();
    // set the m v p matrix
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.2f, 0.5, 0.8f));// rotate the model by time
    view = sCamera->getViewMatrix();
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));// set the view position
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    // projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 0.1f, 100.0f);
    shader->setBool("useTexture", true);
    shader->setMat4f("model", model);
    shader->setMat4f("view", view);
    shader->setMat4f("projection", projection);
    shader->setInt("texture1", textures[0]->getTexturePositionID());
    shader->setInt("texture2", textures[1]->getTexturePositionID());
    
    object->getMesh()->draw();
}