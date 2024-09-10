#include <stdio.h>
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
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f, 0.8f, 0.0f
    };

    glGenVertexArrays(1, &VAObuf);
    glBindVertexArray(VAObuf);

    // Generate and Bind VBO
    glGenBuffers(1, &VBObuf);
    glBindBuffer(GL_ARRAY_BUFFER, VBObuf);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertexPosition, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // 3 points, float, no rgba
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
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
    char VertexShader[256];
    char FragmentShader[256];

    FILE *file = fopen("src/shaders/vertex.glsl", "r");
    if (file == NULL) {
    	printf("Unable to open vertex shader file");
    }

    fgets(VertexShader, sizeof(VertexShader), file);
    fclose(file);

    file = fopen("src/shaders/fragment.glsl", "r");
    if (file == NULL) {
    	printf("Unable to open vertex shader file");
    }

    fgets(FragmentShader, sizeof(FragmentShader), file);
    fclose(file);

    Shaderbuf = CreateShaderProgram(VertexShader, FragmentShader);
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
