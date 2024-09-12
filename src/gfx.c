#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

#include "gfx.h"

GLfloat vertexData[] = { 
    // 0 - Vertex
    -0.5f, -0.5f, 0.0f,     // Bottom Left Vertex
    1.0f, 0.0f, 0.0f,       // color
    // 1 - Vertex
    0.5f, -0.5f, 0.0f,      // Bottom Right vertex
    0.0f, 1.0f, 0.0f,       // color
    // 2 - Vertex
    -0.5f, 0.5f, 0.0f,      // Top Left vertex
    0.0f, 0.0f, 1.0f,       // color
    // 3 - Vertex
    0.5f, 0.5f, 0.0f,       // Top Right Vertex
    1.0f, 0.0f, 0.0f,       // color
};

GLuint indexData[] = {
    2, 0, 1, 
    3, 2, 1
};

void PrintHWInfo() {
	printf("%s\n", glGetString(GL_VENDOR));
	printf("%s\n", glGetString(GL_RENDERER));
	printf("%s\n", glGetString(GL_VERSION));
	printf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void VertexSpec() {
    // Generate and bind VAO
    glGenVertexArrays(1, &VAObuf);
    glBindVertexArray(VAObuf);

    // Generate and Bind VBO
    glGenBuffers(1, &VBObuf);
    glBindBuffer(GL_ARRAY_BUFFER, VBObuf);
    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(vertexData), 
        vertexData, 
        GL_STATIC_DRAW
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
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(GL_FLOAT) * 6, 
        (void*)0
    ); 

    // Color information
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(GL_FLOAT) * 6, 
        (GLvoid*)(sizeof(GL_FLOAT) * 3)
    );

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

GLuint CompileShader(GLuint type, char *source) {
    GLuint shaderObject;
    if (type == GL_VERTEX_SHADER) {
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    } else if (type == GL_FRAGMENT_SHADER) {
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char *src = source;
    glShaderSource(shaderObject, 1, &src, 0);
    glCompileShader(shaderObject);
    
    return shaderObject;        
}

GLuint CreateShaderProgram(char *VertexShaderSource, char *FragmentShaderSource) {
    GLuint programObject = glCreateProgram(); // create graphics pipeline
    GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, VertexShaderSource);
    GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, FragmentShaderSource);

    glAttachShader(programObject, myVertexShader);
    glAttachShader(programObject, myFragmentShader);
    glLinkProgram(programObject);

    return programObject;
}

void CreateGraphicsPipeline(char *vertsource, char *fragsource) {
    char *VertexShader = 0;
    char *FragmentShader = 0;
    long length;

    FILE *file = fopen(vertsource, "rb");
    if (file == NULL) {
        printf("Unable to open vertex shader!\n");
        exit(1);
    }
    // find end of file to determine how many
    // bytes to allocate on the heap
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    printf("Vertex Shader: %d bytes\n", length);
    fseek(file, 0, SEEK_SET);
    VertexShader = malloc(length);

    if (VertexShader) {
        fread(VertexShader, 1, length, file);
    }
    fclose(file);

    file = fopen(fragsource, "rb");
    if (file == NULL) {
        printf("Unable to open fragment shader!\n");
        exit(1);
    }
    // find end of file to determine how many
    // bytes to allocate on the heap
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    printf("Fragment Shader: %d bytes\n", length);
    fseek(file, 0, SEEK_SET);
    FragmentShader = malloc(length);

    if (FragmentShader) {
        fread(FragmentShader, 1, length, file);
    }
    fclose(file);

    ShaderProgram = CreateShaderProgram(VertexShader, FragmentShader);
    
    free(VertexShader);
    free(FragmentShader);
}