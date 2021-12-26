
////////////////////////////////////////////////////////////////////////////////
//            Copyright (C) 2012-2016 by Bertram (Valyria Tear)
//                         All Rights Reserved
//
// This code is licensed under the GNU GPL version 2. It is free software
// and you may modify it and/or redistribute it under the terms of this license.
// See http://www.gnu.org/copyleft/gpl.html for details.
////////////////////////////////////////////////////////////////////////////////

/** ****************************************************************************
*** \file    gl_shader_definitions.h
*** \author  Authenticate, James Lammlein
*** \brief   Header file for shader definitions.
*** ***************************************************************************/

#ifndef __GL_SHADER_DEFINITIONS_HEADER__
#define __GL_SHADER_DEFINITIONS_HEADER__

#include <iostream>

namespace vt_video
{
namespace gl
{
namespace shader_definitions
{
    const std::string getDefaultVertex();

    const char SOLID_FRAGMENT[] =
        "#version 110\n"
        "\n"
        "//\n"
        "// Uses the uniform and vertex colors value directly for a fragment's output.\n"
        "//\n"
        "\n"
        "uniform vec4 u_Color;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "        gl_FragColor = gl_Color;\n"
        "        gl_FragColor *= u_Color;\n"
        "\n"
        "        // Alpha Test\n"
        "        if (gl_FragColor.a <= 0.0)\n"
        "        {\n"
        "            discard;\n"
        "        }\n"
        "}\n";

    const char SOLID_GRAYSCALE_FRAGMENT[] =
        "#version 110\n"
        "\n"
        "//\n"
        "// Converts the uniform and vertex colors to grayscale for a fragment's output.\n"
        "//\n"
        "\n"
        "uniform vec4 u_Color;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "        gl_FragColor = gl_Color;\n"
        "        gl_FragColor *= u_Color;\n"
        "\n"
        "        // Alpha Test\n"
        "        if (gl_FragColor.a <= 0.0)\n"
        "        {\n"
        "            discard;\n"
        "        }\n"
        "\n"
        "        // Grayscale filter\n"
        "        gl_FragColor.r *= 0.299;\n"
        "        gl_FragColor.g *= 0.587;\n"
        "        gl_FragColor.b *= 0.114;\n"
        "\n"
        "        float sum = gl_FragColor.r + gl_FragColor.g + gl_FragColor.b;\n"
        "\n"
        "        gl_FragColor.r = sum;\n"
        "        gl_FragColor.g = sum;\n"
        "        gl_FragColor.b = sum;\n"
        "}\n";

    const char SPRITE_FRAGMENT[] =
        "#version 110\n"
        "\n"
        "//\n"
        "// Samples a texture for a fragment's output.\n"
        "//\n"
        "\n"
        "uniform vec4 u_Color;\n"
        "uniform sampler2D u_Texture;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "        gl_FragColor.rgba = vec4(texture2D(u_Texture, gl_TexCoord[0].xy));\n"
        "        gl_FragColor *= gl_Color;\n"
        "        gl_FragColor *= u_Color;\n"
        "\n"
        "        // Alpha Test\n"
        "        if (gl_FragColor.a <= 0.0)\n"
        "        {\n"
        "            discard;\n"
        "        }\n"
        "}\n";

    const char SPRITE_GRAYSCALE_FRAGMENT[] =
        "\n"
        "#version 110\n"
        "\n"
        "//\n"
        "// Samples a texture and converts to grayscale for a fragment's output.\n"
        "//\n"
        "\n"
        "uniform vec4 u_Color;\n"
        "uniform sampler2D u_Texture;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "        gl_FragColor.rgba = vec4(texture2D(u_Texture, gl_TexCoord[0].xy));\n"
        "        gl_FragColor *= gl_Color;\n"
        "        gl_FragColor *= u_Color;\n"
        "\n"
        "        // Alpha Test\n"
        "        if (gl_FragColor.a <= 0.0)\n"
        "        {\n"
        "            discard;\n"
        "        }\n"
        "\n"
        "        // Grayscale filter\n"
        "        gl_FragColor.r *= 0.299;\n"
        "        gl_FragColor.g *= 0.587;\n"
        "        gl_FragColor.b *= 0.114;\n"
        "\n"
        "        float sum = gl_FragColor.r + gl_FragColor.g + gl_FragColor.b;\n"
        "\n"
        "        gl_FragColor.r = sum;\n"
        "        gl_FragColor.g = sum;\n"
        "        gl_FragColor.b = sum;\n"
        "}\n";

} // namespace shader_definition

} // namespace gl

} // namespace vt_video

#endif // __GL_SHADER_DEFINITIONS_HEADER__
