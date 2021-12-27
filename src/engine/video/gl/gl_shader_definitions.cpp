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

const std::string getDefaultVertex() {
    std::ifstream file("data/shaders/default_vertex.vs");
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
}
}
}
