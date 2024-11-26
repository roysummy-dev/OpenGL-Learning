//
// Created by 房世博 on 2024/11/9.
//

#ifndef OPENGL_LEARNING_RENDERER_H
#define OPENGL_LEARNING_RENDERER_H

#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

// 在visual studio上将__builtin_trap替换为__debug_break();
#define ASSERT(x) if(!(x)) __builtin_trap();
#define GLCall(x) GLCelarError(); \
    x;                            \
    ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLCelarError();

bool GLLogCall(const char *function, const char *file, int line);


class Renderer {
public:
    void Clear() const;

    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};

#endif //OPENGL_LEARNING_RENDERER_H
