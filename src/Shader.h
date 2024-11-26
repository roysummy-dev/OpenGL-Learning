//
// Created by 房世博 on 2024/11/10.
//

#ifndef OPENGL_LEARNING_SHADER_H
#define OPENGL_LEARNING_SHADER_H

#include <string>
#include <unordered_map>


struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};


class Shader {
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string &filepath);

    ~Shader();

    void Bind() const;

    void Unbind() const;

    void SetUniform1i(const std::string &name, int value);

    void SetUniform1f(const std::string &name, float value);

    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

private:
    ShaderProgramSource ParseShader(const std::string &filepath);

    unsigned int CompileShader(unsigned int type, const std::string &source);

    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

    int GetUniformLocation(const std::string &name);
};


#endif //OPENGL_LEARNING_SHADER_H
