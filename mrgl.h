#pragma once

#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glaux.h"
#include "GL/glut.h"
#include "stdio.h"

#if _WIN32
#include "windows.h"
#pragma comment(lib,"OPENGL32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"GLAUX.LIB")
#endif
#ifdef _WIN64
static AUX_RGBImageRec * auxDIBImageLoad(const char *Filename)
{  
	unsigned int Texture;  
	AUX_RGBImageRec * tex_result=new AUX_RGBImageRec; //be careful  
	FILE* img = NULL;  
	fopen_s(&img,Filename, "r");  
	GLint bWidth = 0;  
	GLint bHeight = 0;  
	DWORD size = 0;  
	fseek(img, 18, SEEK_SET);
	fread(&bWidth, 4, 1, img);
	fread(&bHeight, 4, 1, img);
	fseek(img, 0, SEEK_END);
	size = ftell(img) - 54;
	unsigned char *data = (unsigned char*)malloc(size);
	fseek(img, 54, SEEK_SET); // image data  
	fread(data, size, 1, img);
	fclose(img);
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bWidth, bHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	tex_result->sizeX = bWidth;
	tex_result->sizeY = bHeight;
	tex_result->data = data;
	 if (data)  
		 free(data);  
	return tex_result;
}
#endif

static void glinfo()
{
	const GLubyte* name = glGetString(GL_VENDOR);
	const GLubyte* biaoshifu = glGetString(GL_RENDERER);
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION);
	const GLubyte* gluVersion = gluGetString(GLU_VERSION);
	printf("OpenGL实现厂商的名字%s\n", name);
	printf("渲染器标识%s\n", biaoshifu);
	printf("OpenGL实现的版本号%s\n", OpenGLVersion);
	printf("GLU工具库版本%s\n", gluVersion);
}