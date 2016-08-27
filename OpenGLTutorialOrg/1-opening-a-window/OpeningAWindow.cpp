#include <Engine.hpp>
#include <OpenGL/gl3.h>

class OpeningAWindow : public Engine {

public:
    // Override Virtual Render Function
    void render(double currentTime) {
        // Allot of code to create a window is already encapsulated into my engine
    }

};

DECLARE_MAIN(OpeningAWindow);
