#include <fstream>
#include "gl.h"

using namespace gl;

Program::Program(const Shader &vertexShader, const Shader &fragmentShader) {
    id = glCreateProgram();
    glAttachShader(id, vertexShaderId = vertexShader.id);
    glAttachShader(id, fragmentShaderId = fragmentShader.id);
    glLinkProgram(id);
}

Program::~Program() {
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    glDeleteProgram(id);
}

void Program::use() {
    glUseProgram(id);
}

Shader::Shader(GLenum type, const std::vector<std::string> &files) {
    id = glCreateShader(type);
    const GLchar *sources[files.size()];
    for (auto i = 0; i < files.size(); i++) {
        sources[i] = readFile(files[i]);
    }
    glShaderSource(id, files.size(), sources, nullptr);
    glCompileShader(id);
    for (auto i = 0; i < files.size(); i++) {
        delete [] sources[i];
    }
}

const GLchar * Shader::readFile(const std::string &file) {
    std::ifstream stream{file, std::ios::ate};
    std::streamoff length = stream.tellg();
    stream.seekg(0, std::ios::beg);
    auto data = new GLchar[length + 1];
    stream.read(data, length);
    data[length] = '\0';
    return data;
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() {
    glBindVertexArray(id);
}