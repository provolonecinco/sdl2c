#include <stdio.h>
#include <stdlib.h>
#include <glad.h>

#include "opengl.h"

void PrintHWInfo() {
	printf("%s\n", glGetString(GL_VENDOR));
	printf("%s\n", glGetString(GL_RENDERER));
	printf("%s\n", glGetString(GL_VERSION));
	printf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void VertexSpec() {
    // Generate and bind VAO
    GLfloat vertexPosition[] = {
        // Interleaved attributes
        -0.8f, -0.8f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.8f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, &VAObuf);
    glBindVertexArray(VAObuf);

    // Generate and Bind VBO
    glGenBuffers(1, &VBObuf);
    glBindBuffer(GL_ARRAY_BUFFER, VBObuf);
    glBufferData(
            GL_ARRAY_BUFFER, 
            18 * sizeof(GLfloat), 
            vertexPosition, 
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

void CreateGraphicsPipeline() {
    char *VertexShader = 0;
    char *FragmentShader = 0;
    long length;

    FILE *file = fopen("src/shaders/vertex.glsl", "rb");
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

    file = fopen("src/shaders/fragment.glsl", "rb");
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
    
    //printf("Contents of src/shaders/vertex.glsl:\n%s\n", VertexShader);
    //printf("Contents of src/shaders/fragment.glsl:\n%s\n", FragmentShader);
 
    Shaderbuf = CreateShaderProgram(VertexShader, FragmentShader);
    
    free(VertexShader);
    free(FragmentShader);
}

void PreDraw() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, 640, 480);
	glClearColor(0.0f, 0.15f, 0.3f, 1.f);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glUseProgram(Shaderbuf);
}

void Draw() {
	glBindVertexArray(VAObuf);
	glBindBuffer(GL_ARRAY_BUFFER, VBObuf);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
