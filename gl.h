#define GL_GLEXT_PROTOTYPES

#include <string>
#include <vector>
#include <GL/gl.h>

namespace gl {

    struct Shader {

        Shader(const GLenum type, const std::vector<std::string> &files);

    private:

        GLuint id;

        const GLchar *readFile(const std::string &file);

        friend struct Program;

    };

    struct Program {

        Program(const Shader &vertexShader, const Shader &fragmentShader);
        ~Program();

        void use();

    private:

        GLuint fragmentShaderId, id, vertexShaderId;

    };

    struct VertexArray {

        VertexArray();
        ~VertexArray();

        void bind();

    private:

        GLuint id;

    };

}