#version 330

//
// Uses the uniform and vertex colors value directly for a fragment's output.
//

uniform vec4 u_Color;

varying highp vec4 frontColor;

void main(void)
{
        gl_FragColor = frontColor;
        gl_FragColor *= u_Color;

        // Alpha Test
        if (gl_FragColor.a <= 0.0)
        {
            discard;
        }
}

