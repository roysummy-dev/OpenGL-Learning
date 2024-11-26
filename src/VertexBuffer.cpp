//
// Created by 房世博 on 2024/11/9.
//

#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    // 创建一个buffer，id赋值到buffer
    glGenBuffers(1, &m_RendererId);
    // 这里的bind改为select会更好，是一种选择，可以理解为在ps中选中了某个图层，之后的操作都是在这个图层上的
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    // 往buffer中填充数据
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()  {
    glDeleteBuffers(1, &m_RendererId);
}

void VertexBuffer::Bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}

void VertexBuffer::Unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
