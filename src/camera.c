#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <cglm/struct.h>
#include "stb_image.h"

#include "input.h"
#include "gfx.h"
#include "shader.h"
#include "camera.h"

void InitCamera(GLint width, GLint height, vec3s position) {
    cam.width = width;
    cam.height = height;
    cam.position = position;

    // default orientation
    vec3s def = {0.0f, 0.0f, -1.0f};
    cam.orientation = def;

    // default vertical axis
    vec3s def2 = {0.0f, 1.0f, 0.0f};
	cam.up = def2;

    cam.speed = 0.01f;
	cam.sensitivity = 1.0f;
}

void CameraMatrix(float FOVdeg, float nearPlane, float farPlane, GLuint program, const char* uniform) {
    // initialize matrices
    mat4s view = glms_mat4_identity();
    mat4s projection = glms_mat4_identity();
    // set view matrix to camera
    view = glms_lookat(cam.position, glms_vec3_add(cam.position, cam.orientation), cam.up);
    // add perspective to scene
    projection = glms_perspective(FOVdeg, (float)(cam.width/cam.height), nearPlane, farPlane);
    // yeah

    mat4s viewjection = glms_mat4_mul(projection, view);
    glUniformMatrix4fv(glGetUniformLocation(program, uniform), 1, GL_FALSE, (float *)&viewjection);
}


void CameraInputs(SDL_Window* window) {
// TODO - control camera
    if (input.W) {
        cam.position = glms_vec3_add(cam.position, (glms_vec3_scale(cam.orientation, cam.speed)));
    }

    if (input.A) {
        cam.position = glms_vec3_add(cam.position, (glms_vec3_scale(glms_vec3_negate((glms_vec3_cross(cam.orientation, cam.up))), cam.speed)));
    }  

    if (input.S) {
        cam.position = glms_vec3_add(cam.position, (glms_vec3_scale(glms_vec3_negate(cam.orientation), cam.speed)));
    }

    if (input.D) {
        cam.position = glms_vec3_add(cam.position, (glms_vec3_scale((glms_vec3_cross(cam.orientation, cam.up)), cam.speed)));
    }

    if (input.UP) {
        cam.position = glms_vec3_add(cam.position, (glms_vec3_scale(cam.up, cam.speed)));
    }

    if (input.DOWN) {
        cam.position = glms_vec3_add(cam.position, (glms_vec3_scale(glms_vec3_negate(cam.up), cam.speed)));
    }

    if (input.SHIFT) {
        cam.speed = 0.04f;
    } else {
        cam.speed = 0.01f;
    }

    int mouseX, mouseY, firstclick;
    Uint32 mousestate = SDL_GetMouseState(&mouseX, &mouseY);

    if (mousestate == SDL_BUTTON_LEFT) {
        SDL_ShowCursor(SDL_DISABLE);
        
        if (firstclick) {
            SDL_WarpMouseInWindow(window, 640/2, 480/2);
            firstclick = 0;
        }

        float rotX = cam.sensitivity * (float)(mouseY - (480/2)) / 480;
        float rotY = cam.sensitivity * (float)(mouseX - (640/2)) / 640;

        vec3s newOrientation = glms_vec3_rotate(cam.orientation, -rotX, glms_normalize(glms_cross(cam.orientation, cam.up)));

        if (abs(glms_vec3_angle(newOrientation, cam.up)) - 90.0f <= 85.0f) {
            cam.orientation = newOrientation;
        }        

        cam.orientation = glms_vec3_rotate(cam.orientation, -rotY, cam.up);
        SDL_WarpMouseInWindow(window, 640/2, 480/2);
    } else {
        SDL_ShowCursor(SDL_ENABLE);
        firstclick = 1;
    }
}