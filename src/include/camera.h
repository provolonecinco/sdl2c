#ifndef camera_h
#define camera_g
struct camera {
    vec3s position; 
	vec3s orientation; // {0.0f, 0.0f, -1.0f};
	vec3s up; // {0.0f, 1.0f, 0.0f};

	GLint width;
	GLint height;
	float speed; // 0.1f;
	float sensitivity; // 100.0f;
} cam;

    void InitCamera(GLint, GLint, vec3s);

    void CameraMatrix(float, float, float, GLuint, const char*);
    void CameraInputs(SDL_Window*);
#endif