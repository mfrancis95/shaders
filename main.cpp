#define GL_GLEXT_PROTOTYPES

#include <vector>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include "gl.h"
#include "obj.h"

int main() {
    auto window = SDL_CreateWindow(
        "Shaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960,
        SDL_WINDOW_OPENGL
    );
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    auto context = SDL_GL_CreateContext(window);
    glEnable(GL_DEPTH_TEST);
    GLuint buffers[2];
    gl::VertexArray vertexArray;
    vertexArray.bind();
    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    OBJ obj{"suzanne.obj"};
    glBufferStorage(
        GL_ARRAY_BUFFER, obj.positionData.size() * sizeof(float),
        obj.positionData.data(), 0
    );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    if (!obj.normalData.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
        glBufferStorage(
            GL_ARRAY_BUFFER, obj.normalData.size() * sizeof(float),
            obj.normalData.data(), 0
        );
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }
    gl::Shader vertexShader{GL_VERTEX_SHADER, {"shader.vert"}};
    gl::Shader fragmentShader{GL_FRAGMENT_SHADER, {"shader.frag"}};
    gl::Program program{vertexShader, fragmentShader};
    program.use();
    auto projection = glm::perspective(
        glm::radians(45.0f), 1280.0f / 960.0f, 0.1f, 1000.0f
    );
    glUniformMatrix4fv(0, 1, GL_FALSE, &projection[0][0]);
    auto view = glm::lookAt(
        {0.0f, 0.0f, 5.0f}, glm::vec3{0.0f}, {0.0f, 1.0f, 0.0f}
    );
    glUniformMatrix4fv(1, 1, GL_FALSE, &view[0][0]);
    auto lightDirection = glm::normalize(glm::vec3{1.0f, 0, 1.0f});
    glUniform3f(3, lightDirection.x, lightDirection.y, lightDirection.z);
    glUniform3f(4, 1, 0, 0);
    auto angle = 0.0f;
    SDL_Event event;
    auto quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
        auto model = glm::rotate(glm::mat4{1.0f}, glm::radians(angle), {1.0f, 0.3f, 0.5f});
        glUniformMatrix4fv(2, 1, GL_FALSE, &model[0][0]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, obj.positionData.size() / 3);
        SDL_GL_SwapWindow(window);        
        SDL_Delay(16);
        angle++;
    }
    glDeleteBuffers(2, buffers);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}