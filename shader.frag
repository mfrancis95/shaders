#version 440

in vec3 position;
in vec3 normal;

layout(location = 3) uniform vec3 lightDirection;
layout(location = 4) uniform vec3 materialColour;

out vec3 colour;

void main() {
    colour = materialColour * max(dot(normal, lightDirection), 0.0);
}