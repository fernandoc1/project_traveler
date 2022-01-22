#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

extern "C" {

GLAPI void GLAPIENTRY glGetTexImage( GLenum target, GLint level,
                                     GLenum format, GLenum type,
                                     GLvoid *pixels ) {
    printf("WARNING: Called unsupported function: glGetTexImage\n");
}

GLAPI const GLubyte * GLAPIENTRY gluErrorString (GLenum error) {
    printf("WARNING: Called unsupported function: gluErrorString\n");
    return NULL;
}

}