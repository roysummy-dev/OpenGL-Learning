//
// Created by 房世博 on 2024/11/9.
//

#ifndef OPENGL_LEARNING_INDEXBUFFER_H
#define OPENGL_LEARNING_INDEXBUFFER_H


class IndexBuffer {
private:
    unsigned int m_RendererId;
    unsigned int m_Count;

public:
    IndexBuffer(const unsigned int *data, unsigned int count);

    ~IndexBuffer();

    void Bind() const;

    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }

};

#endif //OPENGL_LEARNING_INDEXBUFFER_H
