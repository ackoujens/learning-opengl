#include <Engine.hpp>

Engine::Engine() {
  using namespace std;
    window = NULL;
    title = "Untitled Application";
    width = 640;
    height = 480;
    cout << "Engine Created" << endl;
}

Engine::~Engine() {
  using namespace std;
  cout << "Engine destroyed" << endl;
}

static void error_callback(int error, const char* description) {
  fprintf(stderr, "Error %s\n", description);
}

void Engine::init() {
  glfwSetErrorCallback(error_callback);
}

void Engine::startup() {

}

void Engine::shutdown() {}

void Engine::run(Engine *app) {
    using namespace std;
    // GLFW Init
    if (!glfwInit()) cout << "GLFW initialization failed !" << endl;
    else cout << "GLFW initialized" << endl;

    init();

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
    if (!window) { cout << "Window or OpenGL context creation failed !" << endl; }
    else { cout << "Window or OpenGL context created" << endl; }
    glfwMakeContextCurrent(this->window);

    startup();
    cout << "Running " << title << " ..." << endl;

    // Game Loop
    while (!glfwWindowShouldClose(this->window)) {
        if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            cout << "Closing GLFW window" << endl;
            glfwSetWindowShouldClose(this->window, true);
        }

        render(glfwGetTime());
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }

    // Destruct
    shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::render(double currentTime){}
