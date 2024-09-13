#ifndef camera_h
#define camera_g
struct cam {
    vec3 position; 
	vec3 orientation; // {0.0f, 0.0f, -1.0f};
	vec3 up; // {0.0f, 1.0f, 0.0f};

	GLint width;
	GLint height;
	float speed; // 0.1f;
	float sensitivity; // 100.0f;
} camera;

    void InitCamera(GLint, GLint, vec3);

    void CameraMatrix(float, float, float, GLuint, const char*);
    void CameraInputs(SDL_Window*);
#endif