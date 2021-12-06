#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace glm;

const GLuint WIDTH = 1280, HEIGHT = 720;

bool played = false, pressedDown = false, pressedUp = false, pressedLeft = false, pressedRight = false;

int enemyFormat = 0;

GLfloat xrot = 0, zrot = 0, vTrans = 0, hTrans = 0, hTransEnemy = 0, vTransEnemy = 0, hPos = 0, hPosE = 0, vPosE1 = 0, vPosE2 = 0;
GLfloat initP1X = -5.f, initEX = 7.f, initE1Y = 1.4f, initE2Y = -1.4f;

void resetVal()
{
    xrot = 0, zrot = 0, vTrans = 0, hTrans = 0, hTransEnemy = 0, vTransEnemy = 0;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_SPACE)
    {
        if (!played)
        {
            played = true;
        }
    }
    else if (key == GLFW_KEY_UP)
        pressedUp = true;
    else if (key == GLFW_KEY_DOWN)
        pressedDown = true;
    else if (key == GLFW_KEY_LEFT)
        pressedLeft = true;
    else if (key == GLFW_KEY_RIGHT)
        pressedRight = true;

    if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
        pressedUp = false;
    else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
        pressedDown = false;
    else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
        pressedLeft = false;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
        pressedRight = false;
}

int main()
{
    if (!glfwInit())
    {
        cerr << "GLFW tidak dapat dimulai" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Workshop Computer Graphics Project Farid AA", 0, NULL);

    if (window == nullptr)
    {
        cerr << "Window tidak dapat dibuka" << endl;
        glfwTerminate();
        return -2;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        cerr << "GLEW tidak dapat dimulai" << endl;
        glfwTerminate();
        return -3;
    }

    //vesion info
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *ver = glGetString(GL_VERSION);
    printf("Renderer : %s\n", renderer);
    printf("OpenGL Ver. supported %s\n", ver);

    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);

    Shader shader0("btn.vs", "btn.fs");
    Shader shader1("vertex1.vs", "fragment1.fs");

    GLfloat vertices0[] = {
        -0.3f, 0.5f, 0.f, 0.2f, 0.2f, 0.2f,
        -0.3f, -0.5f, 0.f, 0.2f, 0.2f, 0.2f,
        0.3f, 0.f, 0.f, 0.2f, 0.2f, 0.2f};

    GLuint indices0[] = {0, 1, 2};

    VAO VAO0;
    VAO0.Bind();

    VBO VBO0(vertices0, sizeof(vertices0));
    EBO EBO0(indices0, sizeof(indices0));

    VAO0.LinkAttrib(VBO0, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    VAO0.LinkAttrib(VBO0, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    VAO0.Unbind();
    VBO0.Unbind();
    EBO0.Unbind();

    GLfloat vertices1[] = {
        0.0f, 0.0f, 0.5f, 0.13, 0.44, 0.58,
        0.0f, -0.2f, -0.5f, 0.13, 0.44, 0.58,
        -0.02f, 0.0f, -0.5f, 0.13, 0.44, 0.58,
        0.02f, 0.0f, -0.5f, 0.13, 0.44, 0.58,

        0.0f, 0.0f, 0.5f, 0.2, 0.67, 0.88,
        -0.02f, 0.0f, -0.5f, 0.2, 0.67, 0.88,
        -0.3f, 0.0f, -0.3f, 0.2, 0.67, 0.88,
        -0.2f, 0.0f, -0.55, 0.2, 0.67, 0.88,

        0.0f, 0.0f, 0.5f, 0.2, 0.67, 0.88,
        0.02f, 0.0f, -0.5f, 0.2, 0.67, 0.88,
        0.3f, 0.0f, -0.3f, 0.2, 0.67, 0.88,
        0.2f, 0.0f, -0.55, 0.2, 0.67, 0.88,

        0.0f, 0.0f, 0.5f, 0.2, 0.67, 0.88,
        -0.02f, -0.05f, -0.3f, 0.2, 0.67, 0.88,
        -0.3f, 0.0f, -0.3f, 0.2, 0.67, 0.88,

        0.0f, 0.0f, 0.5f, 0.2, 0.67, 0.88,
        0.02f, -0.05f, -0.3f, 0.2, 0.67, 0.88,
        0.3f, 0.0f, -0.3f, 0.2, 0.67, 0.88,

        //1
    };

    GLuint indices1[] = {
        0, 1, 2,
        0, 1, 3,
        4, 5, 6,
        5, 6, 7,
        8, 9, 10,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,

        // 1
    };

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices1, sizeof(vertices1));
    EBO EBO1(indices1, sizeof(indices1));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLfloat vertices2[] = {
        0.0f, 0.0f, 0.5f, 0.7, 0.22, 0.22,
        0.0f, -0.2f, -0.5f, 0.7, 0.22, 0.22,
        -0.02f, 0.0f, -0.5f, 0.7, 0.22, 0.22,
        0.02f, 0.0f, -0.5f, 0.7, 0.22, 0.22,

        0.0f, 0.0f, 0.5f, 1.f, 0.32, 0.32,
        -0.02f, 0.0f, -0.5f, 1.f, 0.32, 0.32,
        -0.3f, 0.0f, -0.3f, 1.f, 0.32, 0.32,
        -0.2f, 0.0f, -0.55, 1.f, 0.32, 0.32,

        0.0f, 0.0f, 0.5f, 1.f, 0.32, 0.32,
        0.02f, 0.0f, -0.5f, 1.f, 0.32, 0.32,
        0.3f, 0.0f, -0.3f, 1.f, 0.32, 0.32,
        0.2f, 0.0f, -0.55, 1.f, 0.32, 0.32,

        0.0f, 0.0f, 0.5f, 1.f, 0.32, 0.32,
        -0.02f, -0.05f, -0.3f, 1.f, 0.32, 0.32,
        -0.3f, 0.0f, -0.3f, 1.f, 0.32, 0.32,

        0.0f, 0.0f, 0.5f, 1.f, 0.32, 0.32,
        0.02f, -0.05f, -0.3f, 1.f, 0.32, 0.32,
        0.3f, 0.0f, -0.3f, 1.f, 0.32, 0.32,

        //2
    };

    VAO VAO2;
    VAO2.Bind();

    VBO VBO2(vertices2, sizeof(vertices2));
    EBO EBO2(indices1, sizeof(indices1));

    VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    VAO2.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();

    VAO VAO3;
    VAO3.Bind();

    VBO VBO3(vertices2, sizeof(vertices2));
    EBO EBO3(indices1, sizeof(indices1));

    VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    VAO3.Unbind();
    VBO3.Unbind();
    EBO3.Unbind();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // PLAYER SIDE

        if (pressedUp == false && xrot < 0)
        {
            xrot += 1;
            zrot += ((float)2 / (float)3);
            vTrans += 0.005;
        }
        if (pressedDown == false && xrot > 0)
        {
            xrot -= 1;
            zrot -= ((float)2 / (float)3);
            vTrans -= 0.005;
        }
        if (pressedUp)
        {
            if (xrot > -45)
            {
                xrot -= 1;
                zrot -= ((float)2 / (float)3);
            }
            vTrans += 0.03;
        }
        if (pressedDown)
        {
            if (xrot < 45)
            {
                xrot += 1;
                zrot += ((float)2 / (float)3);
            }
            vTrans -= 0.03;
        }
        if (pressedLeft)
            hTrans -= 0.03;
        if (pressedRight)
            hTrans += 0.03;

        if (!played)
        {
            shader0.Use();
            VAO0.Bind();
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            VAO0.Unbind();
        }

        if (played)
        {
            shader1.Use();
            mat4 model, view, projection;

            GLint modelLoc = glGetUniformLocation(shader1.Program, "model");
            GLint viewLoc = glGetUniformLocation(shader1.Program, "view");
            GLint projLoc = glGetUniformLocation(shader1.Program, "projection");

            view = lookAt(
                vec3(0, 0, 4),
                vec3(0, 0, 0),
                vec3(0, 1, 0));
            projection = perspectiveFov(radians(30.0f), (GLfloat)WIDTH, (GLfloat)HEIGHT, 0.1f, 100.f);

            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

            // don't change what lies above

            model = mat4(1.0);
            model = scale(model, vec3(0.3, 0.3, 0.3));
            model = translate(model, vec3(initP1X, 0.0f, 0.f));
            model = rotate(model, radians(90.0f), vec3(0.f, 1.f, 0.f));

            model = translate(model, vec3(0.f, vTrans, hTrans));
            model = rotate(model, radians(xrot), vec3(1.f, 0.f, 0.f));
            model = rotate(model, radians(zrot), vec3(0.f, 0.f, 1.f));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

            VAO1.Bind();
            glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
            VAO1.Unbind();

            // ENEMY SIDE

            hTransEnemy += 0.03;
            if (hTransEnemy > 14)
            {
                enemyFormat++;
                if (enemyFormat > 2)
                {
                    enemyFormat = 0;
                }
                hTransEnemy = 0;
            }

            vTransEnemy += 0.05;

            model = mat4(1.0);
            model = scale(model, vec3(0.3, 0.3, 0.3));
            model = translate(model, vec3(initEX, initE1Y, 0.f));
            model = rotate(model, radians(-90.0f), vec3(0.f, 1.f, 0.f));

            if (enemyFormat == 0)
            {
                model = translate(model, vec3(0.f, 0.0f, hTransEnemy));
                model = rotate(model, radians(0.f), vec3(1.f, 0.f, 0.f));
                model = rotate(model, radians(0.f), vec3(0.f, 0.f, 1.f));
            }
            else if (enemyFormat == 1 || enemyFormat == 2)
            {
                model = translate(model, vec3(0.f, sin(vTransEnemy), hTransEnemy));
                model = rotate(model, radians(sin(vTransEnemy - 45) * 30), vec3(1.f, 0.f, 0.f));
                model = rotate(model, radians(sin(vTransEnemy + 45) * 15), vec3(0.f, 0.f, 1.f));
            }

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

            VAO2.Bind();
            glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
            VAO2.Unbind();

            model = mat4(1.0);
            model = scale(model, vec3(0.3, 0.3, 0.3));
            model = translate(model, vec3(initEX, initE2Y, 0.f));
            model = rotate(model, radians(-90.0f), vec3(0.f, 1.f, 0.f));

            if (enemyFormat == 0)
            {
                model = translate(model, vec3(0.f, 0.0f, hTransEnemy));
                model = rotate(model, radians(0.f), vec3(1.f, 0.f, 0.f));
                model = rotate(model, radians(0.f), vec3(0.f, 0.f, 1.f));
            }
            else if (enemyFormat == 1)
            {
                model = translate(model, vec3(0.f, sin(vTransEnemy), hTransEnemy));
                model = rotate(model, radians(sin(vTransEnemy - 45) * 30), vec3(1.f, 0.f, 0.f));
                model = rotate(model, radians(sin(vTransEnemy + 45) * 15), vec3(0.f, 0.f, 1.f));
            }
            else if (enemyFormat == 2)
            {
                model = translate(model, vec3(0.f, cos(vTransEnemy), hTransEnemy));
                model = rotate(model, radians(cos(vTransEnemy - 45) * 30), vec3(1.f, 0.f, 0.f));
                model = rotate(model, radians(cos(vTransEnemy + 45) * 15), vec3(0.f, 0.f, 1.f));
            }

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

            VAO3.Bind();
            glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
            VAO3.Unbind();
        }

        // COLLISION DETECTION

        hPos = hTrans + initP1X;
        hPosE = (hTransEnemy - initEX) * -1.f;
        if ((hPos < hPosE + 1.f) && (hPos > hPosE - 0.7f))
        {
            if (enemyFormat == 0)
            {
                if ((vTrans > 1.2 && vTrans < 1.6) || (vTrans < -1.2 && vTrans > -1.6))
                {
                    played = false;
                    resetVal();
                }
            }
            if (enemyFormat == 1)
            {
                vPosE1 = sin(vTransEnemy) + 1.4;
                vPosE2 = sin(vTransEnemy) - 1.4;
                if ((vTrans < vPosE1 + 0.2f && vTrans > vPosE1 - 0.2f) || (vTrans < vPosE2 + 0.2f && vTrans > vPosE2 - 0.2f))
                {
                    played = false;
                    resetVal();
                }
            }
            if (enemyFormat == 2)
            {
                vPosE1 = sin(vTransEnemy) + 1.4;
                vPosE2 = cos(vTransEnemy) - 1.4;
                if ((vTrans < vPosE1 + 0.2f && vTrans > vPosE1 - 0.2f) || (vTrans < vPosE2 + 0.2f && vTrans > vPosE2 - 0.2f))
                {
                    played = false;
                    resetVal();
                }
            }
        }

        glfwSwapBuffers(window);
    }

    VAO0.Delete();
    VBO0.Delete();
    EBO0.Delete();

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    VAO2.Delete();
    VBO2.Delete();
    EBO2.Delete();

    VAO3.Delete();
    VBO3.Delete();
    EBO3.Delete();

    glfwTerminate();
    return 0;
}
