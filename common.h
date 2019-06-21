#ifndef COMMON_H
#define COMMON_H

// #define DEBUG

#define FALSE (0)
#define TRUE (1)
#define ABS(x) ((x)<0?(-x):(x))
#define sign(x) ((x)<0?-1.:1.)

#ifdef WIN32
#	define WIN32_LEAN_AND_MEAN
#	define VC_EXTRALEAN
#	include <windows.h>
#	include <commctrl.h>
#	include <mmsystem.h>
#	include <Mmreg.h>
#endif

#include <GL/gl.h>
#include <glext.h>

// OpenGL extensions
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORM2FPROC glUniform2f;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC glNamedRenderbufferStorageEXT;
PFNGLUNIFORM1IPROC glUniform1i;
#ifdef WIN32
PFNGLACTIVETEXTUREPROC glActiveTexture;
#endif

// Standard library and CRT rewrite for saving executable size
void *memset(void *ptr, int value, size_t num)
{
	for(int i=num-1; i>=0; i--)
		((unsigned char *)ptr)[i] = value;
	return ptr;
}

size_t strlen(const char *str)
{
	int len = 0;
	while(str[len] != '\0') ++len;
	return len;
}

#ifdef DEBUG
#include <stdio.h>
#include <stdlib.h>

// TODO: remove below
void debug(int shader_handle)
{
	printf("    Debugging shader with handle %d.\n", shader_handle);
	int compile_status = 0;
	glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
	if(compile_status != GL_TRUE)
	{
		printf("    FAILED.\n");
		GLint len;
		glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &len);
		printf("    Log length: %d\n", len);
		GLchar *CompileLog = (GLchar*)malloc(len*sizeof(GLchar));
		glGetShaderInfoLog(shader_handle, len, NULL, CompileLog);
		printf("    Error messages:\n%s\n", CompileLog);
		free(CompileLog);
	}
	else
		printf("    Shader compilation successful.\n");
}

void debugp(int program)
{
	printf("    Debugging program with handle %d.\n", program);
	int compile_status = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &compile_status);
	if(compile_status != GL_TRUE)
	{
		printf("    FAILED.\n");
		GLint len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		printf("    Log length: %d\n", len);
		GLchar *CompileLog = (GLchar*)malloc(len*sizeof(GLchar));
		glGetProgramInfoLog(program, len, NULL, CompileLog);
		printf("    Error messages:\n%s\n", CompileLog);
		free(CompileLog);
	}
	else
		printf("    Program linking successful.\n");
}
#else // DEBUG
#define printf(a)
#endif //DEBUG

int w = 1920, h = 1080;

int
// SFX
sfx_program,
sfx_handle,
sfx_blockoffset_location,
sfx_samplerate_location,
sfx_volumelocation,
sfx_texs_location,
sfx_sequence_texture_location,
sfx_sequence_width_location,

// Sequence
sequence_texture_handle,

// Loading bar
load_handle,
load_program,
load_resolution_location,
load_time_location,
load_progress_location,

// Post processing
post_handle,
post_program,
post_resolution_location,
post_fsaa_location,
post_channel0_location,

// Antialiasing
fsaa = 25,
txaa = 1,

// Logo
logo210_time_location,
logo210_resolution_location,
logo210_program,
logo210_handle,

// Decaying factory
//     decayingfactory_time_location, 
//     decayingfactory_resolution_location,
//     decayingfactory_program, 
//     decayingfactory_handle,

	// Text
	text_time_location,
	text_resolution_location,
	text_font_width_location,
	text_channel0_location,
	text_font_location,
	font_texture_handle,
	text_program,
	text_handle;

// Demo globals
#define duration 96.
double t_start = 0.,
t_now = 0.,
t_end = duration;

unsigned int loading = 1, music_loading = 0;
int music_block = 0;
unsigned int snd_framebuffer;
unsigned int scene_override = 0, override_index = 0;

// Music shader globals
int sample_rate = 44100, channels = 2;
double duration1 = duration; //3 min running time
float *smusic1;
int music1_size;
float texs = 512;
int block_size = 512 * 512,
nblocks1;
unsigned int paused = 0;
float progress = .0;

double t_paused;

GLuint first_pass_framebuffer = 0, first_pass_texture;
GLenum error;
#define NSHADERS 3.

float t_load_end = 0.;


void load_demo();
unsigned long __stdcall LoadMusicThread(void *lpParam);
unsigned long __stdcall LoadLogo210Thread(void * lpParam);
unsigned long __stdcall LoadTextThread(void * lpParam);
void quad();
void updateBar();
void draw();


#include "sequence.h"

#include "sfx.h"
#define SFX_VAR_IVOLUME "iVolume"
#define SFX_VAR_ISAMPLERATE "iSampleRate"
#define SFX_VAR_IBLOCKOFFSET "iBlockOffset"
#define SFX_VAR_ITEXSIZE "iTexSize"
#define SFX_VAR_ISEQUENCE "iSequence"
#define SFX_VAR_ISEQUENCEWIDTH "iSequenceWidth"

#include "font/font.h"

// #include "gfx/decayingfactory.h"
// #define DECAYINGFACTORY_VAR_IRESOLUTION "iResolution"
// #define DECAYINGFACTORY_VAR_ITIME "iTime"

#include "gfx/load.h"
#define LOAD_VAR_ITIME "iTime"
#define LOAD_VAR_IPROGRESS "iProgress"
#define LOAD_VAR_IRESOLUTION "iResolution"

#include "gfx/logo210.h"
#define LOGO210_VAR_IRESOLUTION "iResolution"
#define LOGO210_VAR_ITIME "iTime"

#include "gfx/post.h"
#define POST_VAR_IFSAA "iFSAA"
#define POST_VAR_IRESOLUTION "iResolution"
#define POST_VAR_ICHANNEL0 "iChannel0"

#include "gfx/symbols.h"

#include "gfx/text.h"
#define TEXT_VAR_IRESOLUTION "iResolution"
#define TEXT_VAR_ITIME "iTime"
#define TEXT_VAR_IFONT "iFont"
#define TEXT_VAR_IFONTWIDTH "iFontWidth"
#define TEXT_VAR_ICHANNEL0 "iChannel0"

#ifdef WIN32
#	include "pal_win32.h"
#else
#	include "pal_linux.h"
#endif

#endif
