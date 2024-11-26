//
// Created by 房世博 on 2024/11/9.
//

#ifndef OPENGL_LEARNING_VERTEXBUFFER_H
#define OPENGL_LEARNING_VERTEXBUFFER_H


class VertexBuffer {
private:
    unsigned int m_RendererId;

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

};


#endif //OPENGL_LEARNING_VERTEXBUFFER_H
