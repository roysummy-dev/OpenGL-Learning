// 取消glClear过时的warning
#define GL_SILENCE_DEPRECATION

#include "GL/glew.h" //这个要放在其他opengl头文件之前
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Mac上不加这段话使用的opengl版本是2.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // 限制刷新频率，等待垂直同步
    glfwSwapInterval(1);

    // glewInit必须在有了可用的opengl上下文之后才能正常调用，也就是必须放在上面这句话之后
    if (glewInit() != GLEW_OK) {
        std::cout << "glew init error!" << std::endl;
        return 0;
    }
    // 这里大括号的目的是为了将在main里创建的类实例的作用域放在glTerminate之前
    // 如果不这样做的话因为我们申请VertexBuffer和IndexBuffer是在栈上直接申请的
    // 在main的return 0 之后才会退出
    // 然后在这两个类的析构函数里使用GLCall来检测错误了，在GLClearError时会掉入到while的死循环里
    // 因为glTerminate会销毁OpenGL Context，而没有OpenGL Context时glGetError会返回true
    {
        // 打印opengl版本
        std::cout << glGetString(GL_VERSION) << std::endl;

        float positions[] = {
                -0.5f, -0.5f, 0.0f, 0.0f,   //0 position, texture coordinate
                0.5f, -0.5f, 1.0f, 0.0f,    //1
                0.5f, 0.5f, 1.0f, 1.0f,    //2
                -0.5f, 0.5f, 0.0f, 1.0f, //3
        };

        unsigned int indicies[] = {
                0, 1, 2,      //第一个三角形三个顶点的索引
                2, 3, 0       //第二个三角形三个顶点的索引
        };

        GLCall(glEnable(GL_BLEND));
        // 两个参数分别代表blend时新的颜色输出与该位置原有的颜色的权值
        // 例如这里将src(新画的)设置为alpha值，dest(原有颜色)权值设置为1-alpha，当新画的颜色全透明时 alpha = 0，即混合的颜色为 新颜色*0+原有颜色*1
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // core profile时必须显式自己创建vao，compat profile会使用默认的。
        VertexArray va;

        // 使用封装的类代替vertexbuffer的操作
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2); // 增加两个纹理坐标
        va.AddBuffer(vb, layout);


        // 使用封装的类代替 index buffer绑定和填充
        IndexBuffer ib(indicies, 6);

        // 投影矩阵为正交矩阵，目的在于将所画的内容缩放到4:3，与窗口比例统一
        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

        Shader shader("../res/Shaders/Basic.shader");
//        ShaderProgramSource source = ParseShader("../res/Shaders/Basic.shader");
//        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
//        glUseProgram(shader);
        shader.Bind();

        // 这是旧的获取uniform location的方法，4.3之后可以通过递增的location来获取。
//        GLCall(int location = glGetUniformLocation(shader, "u_Color"));
//        ASSERT(location != -1);
//        GLCall(glUniform4f(location, 1.0f, 0.3f, 0.8f, 1.0f));
        // shader.SetUniform4f("u_Color", 1.0f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", proj);
        float r = 1.0f;
        float increment = 0.02f;

        Texture texture("../res/images/XR.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        // 模拟渲染多种物体的情况，首先将绑定的内容清空
        va.Unbind();
//        glUseProgram(0);
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.Clear();
            shader.Bind();
            // 模拟切换到渲染当前正方形的上下文环境。
            // shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            renderer.Draw(va, ib, shader);


            if (r >= 1.0f) {
                increment = -0.02f;
            }
            else if (r <= 0.0f) {
                increment = 0.02f;
            }
            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}