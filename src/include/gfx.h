#ifndef gfx_h
#define gfx_h

float g_uOffset;

GLuint VAObuf;	// Vertex Array Object
GLuint VBObuf;	// Vertex Buffer Object
GLuint IBObuf;  // Index Buffer Object
GLuint ShaderProgram;	// Shader Object

void PrintHWInfo();
void VertexSpec();
void CreateGraphicsPipeline();
void PreDraw();
void Draw();

#endif
