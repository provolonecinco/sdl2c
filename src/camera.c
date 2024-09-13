#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <cglm/cglm.h>
#include "stb_image.h"

#include "input.h"
#include "gfx.h"
#include "shader.h"
#include "camera.h"

void InitCamera(GLint width, GLint height, vec3 position) {
    camera.width = width;
    camera.height = height;
    glm_vec3_copy(position, camera.position);

    // default orientation
    vec3 def = {0.0f, 0.0f, -1.0f};
    glm_vec3_copy(def, camera.orientation);

    // default vertical axis
    vec3 def2 = {0.0f, 1.0f, 0.0f};
	glm_vec3_copy(def2, camera.up);

    camera.speed = 0.01f;
	camera.sensitivity = 100.0f;
}

void CameraMatrix(float FOVdeg, float nearPlane, float farPlane, GLuint program, const char* uniform) {
    // initialize matrices
    mat4 view = {1.0f};
    mat4 projection = {1.0f};

    // sum of camera.position and camera.orientation
    vec3 combo;
    glm_vec3_add(camera.position, camera.orientation, combo);
    // set view matrix to camera
    glm_lookat(camera.position, combo, camera.up, view);
    // add perspective to scene
    glm_perspective(FOVdeg, (float)(camera.width/camera.height), nearPlane, farPlane, projection);
    // yeah

    mat4 viewjection;
    glm_mat4_mul(projection, view, viewjection);
    glUniformMatrix4fv(glGetUniformLocation(program, uniform), 1, GL_FALSE, (float *)viewjection);
}


void CameraInputs(SDL_Window* window) {
// TODO - control camera
}