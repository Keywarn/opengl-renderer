#include "mesh.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include "renderer.h"

namespace render_engine
{
mesh::mesh(vertices vertices, faces faces, std::shared_ptr<material> material, glm::mat4 transform)
    : m_transform(transform)
    , m_vertices(vertices)
    , m_faces(faces)
    , m_material(material)
{
    setup();
}

void mesh::setup()
{
    glGenVertexArrays(1, &m_vertex_array);
    glBindVertexArray(m_vertex_array);

    glGenBuffers(1, &m_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), &m_vertices.front(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_faces.size() * sizeof(unsigned int), &m_faces.front(), GL_STATIC_DRAW);

    // Vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(vertex), (void*)offsetof(vertex, m_normal));
    glEnableVertexAttribArray(1);

    //// Colour
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    // UVs
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(vertex), (void*)offsetof(vertex, m_uv));
    glEnableVertexAttribArray(2);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mesh::draw(float delta)
{
    //animate first
    //m_transform = glm::rotate(m_transform, delta * glm::radians(90.f), glm::vec3(0.5f, 1.0f, 0.0f));

    m_material->use(m_transform);

    glBindVertexArray(m_vertex_array);
    glDrawElements(GL_TRIANGLES, m_faces.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void mesh::free()
{
    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
}
}