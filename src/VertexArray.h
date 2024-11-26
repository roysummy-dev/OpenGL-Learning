//
// Created by 房世博 on 2024/11/10.
//

#ifndef OPENGL_LEARNING_VERTEXARRAY_H
#define OPENGL_LEARNING_VERTEXARRAY_H

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();

    ~VertexArray();

    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    void Bind() const;

    void Unbind() const;
};


#endif //OPENGL_LEARNING_VERTEXARRAY_H
