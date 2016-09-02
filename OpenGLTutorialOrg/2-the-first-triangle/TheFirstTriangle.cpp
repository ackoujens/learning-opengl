#include <Engine.hpp>
#include <OpenGL/gl3.h>

class TheFirstTriangle : public Engine {

public:
    GLuint VertexArrayID;
    
    /*
      Triangle = defined by 3 points
      Points = vertices
      Vertex = 3 coordinates (x, y, z)
    */
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[];

    // This will identify our vertex buffer
    GLuint vertexbuffer;

    // Override virtual Startup Function
    void startup() {
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);
        
        const float g_vertex_buffer_data[] = {
          -1.0f, -1.0f, 0.0f,
           1.0f, -1.0f, 0.0f,
           0.0f,  1.0f, 0.0f
         };

         // Generate 1 buffer, put the resulting identifier in vertex buffer
         glGenBuffers(1, &vertexbuffer);

         // The following commands will talk about our 'vertexbuffer' buffer
         glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

         // Give our vertices to OpenGL
         glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    }

    // Override Virtual Render Function
    void render(double currentTime) {
        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
          0,        // attribute 0 to match the layout
          3,        // size
          GL_FLOAT, // type
          GL_FALSE, // normalized?
          0,        // stride
          (void*)0  // array buffer offset
        );

        // draw the the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3); // starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);
    }

};

DECLARE_MAIN(TheFirstTriangle);
