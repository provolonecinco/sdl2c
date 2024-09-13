#ifndef gfx_h
#define gfx_h
// -------- global -------- //
extern const int screenWidth;
extern const int screenHeight;
int run;    // used in main loop 
// -------- Gfx.c -------- //
GLuint VAObuf;	        // Vertex Array Object
GLuint VBObuf;	        // Vertex Buffer Object
GLuint IBObuf;          // Index Buffer Object
void LoadBuffers();
// -------- Camera.c -------- //
struct camera {
    vec3s position; 
	vec3s orientation;  // {0.0f, 0.0f, -1.0f};
	vec3s up;           // {0.0f, 1.0f, 0.0f};
	GLint width;
	GLint height;
	float speed;        // 0.01f;
	float sensitivity;  // 1.00f;
} cam;

    void InitCamera(GLint, GLint, vec3s);
    void CameraMatrix(float, float, float, GLuint, const char*);
    void CameraInputs(SDL_Window*);
// -------- Shader.c -------- //
GLuint ShaderProgram;	// Shader Object
void LoadShaders();
#endif
