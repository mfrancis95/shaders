#version 440

in vec3 inPosition;
in vec3 inNormal;

layout(location = 0) uniform mat4 projection;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;

out vec3 position;
out vec3 normal;

void main() {
    gl_Position = projection * view * model * vec4(inPosition, 1);
    normal = normalize(mat3(transpose(inverse(model))) * inNormal);
    position = (model * vec4(inPosition, 1)).xyz;
}