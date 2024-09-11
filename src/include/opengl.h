#ifndef opengl_h
#define opengl_h

GLuint VAObuf;	// Vertex Array Object
GLuint VBObuf;	// Vertex Buffer Object
GLuint IBObuf;  // Index Buffer Object
GLuint Shaderbuf;	// Shader Object

void PrintHWInfo();
void VertexSpec();
void CreateGraphicsPipeline();
void PreDraw();
void Draw();

#endif
