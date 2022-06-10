#version 110

//
// Uses the uniform and vertex colors value directly for a fragment's output.
//

varying highp vec4 frontColor;
varying highp vec2 texCoord;

uniform vec4 u_Color;

uniform sampler2D uSampler;

void main(void)
{
        gl_FragColor = texture2D(uSampler, texCoord);;
        gl_FragColor *= u_Color;

        // Alpha Test
        if (gl_FragColor.a <= 0.0)
        {
            discard;
        }
}

