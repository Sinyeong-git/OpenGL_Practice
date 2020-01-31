
#include <sb6.h>
#include <vmath.h>
#include <cmath>
#include <math.h>

//쉐이더 컴파일을 위한 클래스
GLuint compile_shaders(void) {

    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;

    //GLSL 버텍스 쉐이더 코드
    static const GLchar * vertex_shader_source[] =
    {
        "#version 430 core                                                              \n"
        "                                                                               \n"      
        "void main(void)                                                                \n"
        "{                                                                              \n"
        "    gl_Position = vec4(0.0, 0.0, 0.5, 1.0);                                    \n"
        "}                                                                              \n"
    };

    //GLSL 프래그먼트 쉐이더 소스 코드
    static const GLchar* fragment_shader_source[] = {
        "#version 430 core                                                              \n"
        "                                                                               \n"
        "out vec4 color;                                                                \n"
        "void main(void)                                                                \n"
        "{                                                                              \n"
        "   color = vec4(0.0,0.8,1.0,1.0);                                              \n"
        "}                                                                              \n"

    };

    //버텍스 쉐이더 생성 컴파일
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vertex_shader_source , NULL);
    glCompileShader(vertex_shader);

    //프래그먼트 쉐이더 생성 컴파일
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    //프로그램 생성 , 쉐이더를 어태치 시키고 링크
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    //프로그램이 쉐이더를 소유하므로 쉐이더 삭제
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

class my_application : public sb6::application
{
public:
    void startup() {
        rendering_program = compile_shaders();
        glGenVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
    }

    void shutdown() {
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(rendering_program);
        glDeleteVertexArrays(1, &vertex_array_object);
    }

    virtual void render(double currentTime)
    {
        const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f,
                                  (float)cos(currentTime) * 0.5f + 0.5f,
                                  0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, color);

        //렌더링을 위해 앞서 생성한 객체 사용
        glUseProgram(rendering_program);

        //점 크기 키우기
        glPointSize(40.0f);

        //점 하나 그림
        glDrawArrays(GL_POINTS, 0, 1);
    }

private:
    GLuint rendering_program;
    GLuint vertex_array_object;
};

DECLARE_MAIN(my_application)
