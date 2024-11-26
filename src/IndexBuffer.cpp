//
// Created by 房世博 on 2024/11/9.
//

#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_Count(count) {

    ASSERT(sizeof (unsigned int) == sizeof(GLuint));

    // 创建一个buffer，id赋值到buffer
    glGenBuffers(1, &m_RendererId);
    // 这里的bind改为select会更好，是一种选择，可以理解为在ps中选中了某个图层，之后的操作都是在这个图层上的
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
    // 往buffer中填充数据
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_RendererId);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
