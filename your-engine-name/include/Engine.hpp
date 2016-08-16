#ifndef Engine_hpp
#define Engine_hpp

#include <GLFW/glfw3.h>
#include <string>

class Engine {
public:
    GLFWwindow *window;
    const char *title;
    int width;
    int height;

    Engine();
    virtual ~Engine();

    virtual void run(Engine *app);

    virtual void render(double currentTime);
};

#define DECLARE_MAIN(a)                 \
  int main(int argc, const char **argv) \
  {                                     \
    a *app = new a;                     \
    app->run(app);                      \
    delete app;                         \
    return 0;                           \
  }

#endif /* Engine_hpp */
