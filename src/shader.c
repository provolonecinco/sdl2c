#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <cglm/struct.h>
#include "stb_image.h"


#include "gfx.h"

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

char* LoadShaderFile(char *filename) {
    long length;
    char *buffer; 

    FILE *file = fopen(filename, "rb");

    if (file) {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer = malloc(length);
        fread(buffer, 1, length, file);
        fclose(file);

        return buffer;
    } 

    printf("Unable to open: %s\n", filename);
    exit(1);
}

void LoadShaders(char *vertsource, char *fragsource) {
    char *vertbuf = LoadShaderFile(vertsource);
    char *fragbuf = LoadShaderFile(fragsource);
    
    ShaderProgram = glCreateProgram();
    GLuint VertexShader = CompileShader(GL_VERTEX_SHADER, vertbuf);
    GLuint FragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragbuf);

    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);
    glLinkProgram(ShaderProgram);

    free(vertbuf);
    free(fragbuf);
}
