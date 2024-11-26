//
// Created by 房世博 on 2024/11/10.
//

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Renderer.h"


Shader::Shader(const std::string &filepath) : m_FilePath(filepath), m_RendererID(0) {
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1f(const std::string &name, float value) {
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1i(const std::string &name, int value) {
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

// 从文件中读取读取shader
ShaderProgramSource Shader::ParseShader(const std::string &filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int) type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int shaderType, const std::string &source) {
    unsigned int id = glCreateShader(shaderType);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // shader错误检查
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        // 这里的作用是在栈上动态分配内存
        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader."
                  << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int Shader::GetUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        // std::cout << "Cache hit." << std::endl;
        return m_UniformLocationCache[name];
    }
    unsigned int id = -1;
    GLCall(id = glGetUniformLocation(m_RendererID, name.c_str()));
    if (id == -1) {
        std::cout << "Get Location Error" << std::endl;
    }
    m_UniformLocationCache[name] = id;
    return id;
}
