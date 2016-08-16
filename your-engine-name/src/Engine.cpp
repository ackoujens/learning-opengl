#include <Engine.hpp>
#include <iostream>

Engine::Engine() {
    window = NULL;
    title = "Untitled Application";
    width = 640;
    height = 480;
}

Engine::~Engine() {}

void Engine::run(Engine *app) {
    using namespace std;
    cout << "Running " << title << " ..." << endl;

    // GLFW Init
    if (!glfwInit()) cout << "GLFW initialization failed !" << endl;
    else cout << "GLFW initialized" << endl;

    // Enabled OSX to use a more advanced OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create Window
    this->window = glfwCreateWindow(this->width,
                                    this->height,
                                    this->title,
                                    NULL,
                                    NULL);
    if (!window) cout << "Window or OpenGL context creation failed !" << endl;
    else cout << "Window or OpenGL context created" << endl;
    glfwMakeContextCurrent(this->window);

    // Game Loop
    while (!glfwWindowShouldClose(this->window)) {
        if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            cout << "Closing GLFW window" << endl;
            glfwSetWindowShouldClose(this->window, true);
        }

        render(glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Destruct
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::render(double currentTime){}
