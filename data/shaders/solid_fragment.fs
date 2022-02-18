#version 110

//
// Uses the uniform and vertex colors value directly for a fragment's output.
//

uniform vec4 u_Color;

void main(void)
{
        gl_FragColor = gl_Color;
        gl_FragColor *= u_Color;

        // Alpha Test
        if (gl_FragColor.a <= 0.0)
        {
            discard;
        }
}


