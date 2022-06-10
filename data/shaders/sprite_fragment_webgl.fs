#version 330

//
// Uses the uniform and vertex colors value directly for a fragment's output.
//

uniform vec4 u_Color;

uniform sampler2D u_Texture;

varying highp vec4 frontColor;
varying highp vec2 texCoord;

void main(void)
{
        gl_FragColor.rgba = vec4(texture2D(u_Texture, texCoord));
        gl_FragColor *= frontColor;
        gl_FragColor *= u_Color;

        // Alpha Test
        if (gl_FragColor.a <= 0.0)
        {
            discard;
        }
}

