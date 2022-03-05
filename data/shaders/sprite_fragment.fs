#version 110

//
// Uses the uniform and vertex colors value directly for a fragment's output.
//

uniform vec4 u_Color;

uniform sampler2D u_Texture;

void main(void)
{
        gl_FragColor.rgba = vec4(texture2D(u_Texture, gl_TexCoord[0].xy));
        gl_FragColor *= gl_Color;
        gl_FragColor *= u_Color;

        // Alpha Test
        if (gl_FragColor.a <= 0.0)
        {
            discard;
        }
}

