#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <vector>

#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"

namespace render_engine
{

class renderer
{
public:
    renderer(GLFWwindow* window);

    void render(float delta);

    void toggle_wireframe();
    void toggle_persepctive();

    texture* register_texture(const char* path);
    shader* register_shader(const char* vertex_path, const char* fragment_path, texture* texture);
    mesh* register_mesh(vertices vertices, faces faces, shader* shader, glm::mat4 transform);

    void free();

    glm::mat4& get_view()
    {
        return m_camera.get_view();
    }

    glm::mat4& get_projection()
    {
        return m_perspective ? m_camera.get_perspective() : m_camera.get_orthographic();
    }

private:
    GLFWwindow* m_window;
    camera m_camera;

    std::vector<texture> m_textures;
    std::vector<shader> m_shaders;
    std::vector<mesh> m_meshes;

    bool m_wireframe = false;
    bool m_perspective = true;
};
}