//
// Created by 房世博 on 2024/11/10.
//

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"


VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_RendererID));
    GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    Bind();
    vb.Bind();
    const auto &elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];
        // 设置vertex buffer的layout，也即将buffer的结构告诉opengl
        /*
         * index 指定要配置的顶点属性的编号。
         * size 指定每个顶点属性的分量数（1、2、3 或 4，就像向量的维度一样）。
         * type 指定每个分量的数据类型，可以是 GL_BYTE、GL_UNSIGNED_BYTE、GL_SHORT、GL_UNSIGNED_SHORT、GL_INT、GL_UNSIGNED_INT、GL_FLOAT 或 GL_DOUBLE。
         * normalized 指定是否将数据归一化到 [0,1] 或 [-1,1] 范围内。
         * stride （步长）指定连续两个顶点属性间的字节数。如果为 0，则表示顶点属性是紧密排列的。
         * pointer 指向缓冲对象中第一个顶点属性的第一个分量的地址。（offset的作用）
         * */
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),
                                     (const void *) offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const {
    GLCall(glBindVertexArray(0));
}
