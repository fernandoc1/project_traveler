#include "gl_shader_definitions.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace vt_video
{
namespace gl
{
namespace shader_definitions
{

const std::string readFullTextFile(std::string path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

const std::string getDefaultVertex() {
    return readFullTextFile("data/shaders/default_vertex.vs");
}

const std::string getSolidFragment() { 
    return readFullTextFile("data/shaders/solid_fragment.fs");
}


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


//const std::string getSolidGrayscaleFragment() { return std::string(SOLID_GRAYSCALE_FRAGMENT); }
//const std::string getSpriteGrayscaleFragment() { return std::string(SPRITE_GRAYSCALE_FRAGMENT); }

const std::string getSpriteFragment() { return readFullTextFile("data/shaders/sprite_fragment.fs"); }
const std::string getSolidGrayscaleFragment() { return readFullTextFile("data/shaders/sprite_fragment.fs"); }
const std::string getSpriteGrayscaleFragment() { return readFullTextFile("data/shaders/sprite_fragment.fs"); }

}
}
}
