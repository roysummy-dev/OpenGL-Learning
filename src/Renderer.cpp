//
// Created by 房世博 on 2024/11/9.
//

#include "Renderer.h"
#include <iostream>


void GLCelarError() {
    while (glGetError() != GL_NO_ERROR);//将原有的错误清空
}

bool GLLogCall(const char *function, const char *file, int line) {
    if (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
                  " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
    shader.Bind();
    // 绑定vao相当于绑定了vertex buffer以及设置了 glVertexAttribPointer 和 glEnableVertexAttribArray
    // 使用封装的vertex array替代opengl native api
    va.Bind();
    ib.Bind(); //使用封装的类代替glBindBuffer
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    //glDrawArrays(GL_TRIANGLES, 0, 6);
    // 使用indexbuffer时就不能使用DrawArrays了，需要使用Draw Eelements
    // 第三个type必须为unsigned，否则会黑屏。最后一个因为index buffer已经绑定了，所以传入null即可。
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}