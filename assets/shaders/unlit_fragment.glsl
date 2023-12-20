#version 330 core

uniform vec3 albedo;

out vec4 fragment_colour;

void main()
{
    fragment_colour = vec4(albedo, 1.0);
}