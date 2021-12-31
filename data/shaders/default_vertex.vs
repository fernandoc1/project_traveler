#version 110

//
// The default transformation pipeline.
//

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform float u_AngleX;
uniform float u_AngleY;
uniform float u_AngleZ;

uniform float u_tx;
uniform float u_ty;

attribute vec3 in_Vertex;
attribute vec2 in_TexCoords;
attribute vec4 in_Color;

mat4 u_RotationX = mat4(
vec4(1.0, 0.0, 0.0, 0.0),
vec4(0.0, cos(u_AngleX), -sin(u_AngleX), 0.0),
vec4(0.0, sin(u_AngleX),  cos(u_AngleX), 0.0),
vec4(0.0, 0.0, 0.0, 1.0));

mat4 u_RotationY = mat4(
vec4(cos(u_AngleY), 0.0, sin(u_AngleY), 0.0),
vec4(0.0, 1.0, 0.0, 0.0),
vec4(-sin(u_AngleY), 0.0, cos(u_AngleY), 0.0),
vec4(0.0, 0.0, 0.0, 1.0));

mat4 u_RotationZ = mat4(
vec4(cos(u_AngleZ), -sin(u_AngleZ), 0.0, 0.0),
vec4(sin(u_AngleZ),  cos(u_AngleZ), 0.0, 0.0),
vec4(0.0,         0.0,        1.0, 0.0),
vec4(0.0,         0.0,        0.0, 1.0));

mat4 u_Translation = mat4(
vec4(1.0,  0.0,  0.0, 0.0),
vec4(0.0,  1.0,  0.0, 0.0),
vec4(0.0,  0.0,  1.0, 0.0),
vec4(u_tx, u_ty, 0.0, 1.0));

void main()
{
    mat4 u_Rotation = u_RotationX * u_RotationY * u_RotationZ;
    gl_Position       = u_Projection * (u_View * (u_Model * u_Translation * u_Rotation * vec4(in_Vertex, 1.0)));
    gl_FrontColor     = in_Color;
    gl_TexCoord[0].xy = in_TexCoords.xy;
}
;
