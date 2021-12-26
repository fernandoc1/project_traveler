#version 110

//
// The default transformation pipeline.
//

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform float u_Angle;

attribute vec3 in_Vertex;
attribute vec2 in_TexCoords;
attribute vec4 in_Color;

mat4 u_Rotation = mat4(
vec4(cos(u_Angle), -sin(u_Angle), 0.0, 0.0),
vec4(sin(u_Angle),  cos(u_Angle), 0.0, 0.0),
vec4(0.0,         0.0,        1.0, 0.0),
vec4(0.0,         0.0,        0.0, 1.0));

void main()
{
    gl_Position       = u_Projection * (u_View * (u_Model * vec4(in_Vertex, 1.0))) * u_Rotation;
    gl_FrontColor     = in_Color;
    gl_TexCoord[0].xy = in_TexCoords.xy;
}
;
