#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

#include "gfx.h"

GLfloat vertexData[] = { 
    //     COORDINATES     //       COLORS          // TEXTURES
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.0f, 1.0f,  0.0f,     0.92f, 0.86f, 0.76f,	0.5f, 1.0f
};

GLuint indexData[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

void LoadBuffers() {
    // Generate and bind VAO
    glGenVertexArrays(1, &VAObuf);
    glBindVertexArray(VAObuf);

    // Generate and Bind VBO
    glGenBuffers(1, &VBObuf);
    glBindBuffer(GL_ARRAY_BUFFER, VBObuf);
    glBufferData(
        GL_ARRAY_BUFFER,            // Target
        sizeof(vertexData),         // Size
        vertexData,                 // Pointer to data
        GL_STATIC_DRAW              // usage
    );

    // Index Buffer information (IBO/EBO)
    glGenBuffers(1, &IBObuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBObuf);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indexData),
        indexData,
        GL_STATIC_DRAW
    );

    // Vertex information
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                          // Index
        3,                          // Size
        GL_FLOAT,                   // Type
        GL_FALSE,                   // Normalize fixed point values
        sizeof(GL_FLOAT) * 8,       // Stride (space between data)
        (void*)0                    // Pointer to first component
    ); 

    // Color information
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(GL_FLOAT) * 8, 
        (GLvoid*)(sizeof(GL_FLOAT) * 3)
    );

    // Texture information
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(GL_FLOAT) * 8, 
        (GLvoid*)(sizeof(GL_FLOAT) * 6)
    );


    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
