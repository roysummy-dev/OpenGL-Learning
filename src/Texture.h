//
// Created by 房世博 on 2024/11/19.
//

#ifndef OPENGL_LEARNING_TEXTURE_H
#define OPENGL_LEARNING_TEXTURE_H

#include "Renderer.h"

class Texture {
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_BPP; // bits per pixel
public:
    Texture(const std::string &path);

    ~Texture();

    void Bind(unsigned int slot = 0) const;

    void Unbind() const;

    inline int GetWidth() const { return m_Width; }

    inline int GetHeight() const { return m_Height; }

};


#endif //OPENGL_LEARNING_TEXTURE_H
