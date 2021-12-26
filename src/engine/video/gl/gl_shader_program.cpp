////////////////////////////////////////////////////////////////////////////////
//            Copyright (C) 2012-2016 by Bertram (Valyria Tear)
//                         All Rights Reserved
//
// This code is licensed under the GNU GPL version 2. It is free software
// and you may modify it and/or redistribute it under the terms of this license.
// See http://www.gnu.org/copyleft/gpl.html for details.
////////////////////////////////////////////////////////////////////////////////

/** ****************************************************************************
*** \file    gl_shader_program.cpp
*** \author  Authenticate, James Lammlein
*** \brief   Source file for shader programs used in OpenGL.
*** ***************************************************************************/

#include "gl_shader_program.h"

#include "gl_shader.h"

#include "utils/utils_common.h"
#include "utils/exception.h"
#include "utils/utils_strings.h"

#include <cassert>
#include <cstring>

namespace vt_video
{
namespace gl
{

ShaderProgram::ShaderProgram(const Shader* vertex_shader,
                             const Shader* fragment_shader,
                             const std::vector<std::string>& attributes) :
    _program(0),
    _vertex_shader(vertex_shader),
    _fragment_shader(fragment_shader)
{
    bool errors = false;

    assert(_vertex_shader != nullptr);
    assert(_fragment_shader != nullptr);

    // Create the program.
    if (!errors) {
        _program = glCreateProgram();

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            errors = true;
            PRINT_ERROR << "Failed to create the shader program." << std::endl;
            assert(error == GL_NO_ERROR);
        }
    }

    // Attach the vertex shader.
    if (!errors) {
        glAttachShader(_program, _vertex_shader->_shader);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            errors = true;
            PRINT_ERROR << "Failed to attach the vertex shader to the shader program. Shader Program ID: " <<
                           vt_utils::NumberToString(_program) << " Shader ID: " <<
                           vt_utils::NumberToString(_vertex_shader->_shader) <<
                           std::endl;
            assert(error == GL_NO_ERROR);
        }
    }

    // Attach the fragment shader.
    if (!errors) {
        glAttachShader(_program, _fragment_shader->_shader);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            errors = true;
            PRINT_ERROR << "Failed to attach the fragment shader to the shader program. Shader Program ID: " <<
                           vt_utils::NumberToString(_program) << " Shader ID: " <<
                           vt_utils::NumberToString(_fragment_shader->_shader) <<
                           std::endl;
            assert(error == GL_NO_ERROR);
        }
    }

    // Bind the attributes.
    if (!errors) {
        std::vector<std::string>::const_iterator i;
        i = attributes.begin();
        GLuint count = 0;
        while (i != attributes.end() && !errors) {
            glBindAttribLocation(_program, count, i->c_str());

            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                errors = true;
                PRINT_ERROR << "Failed to bind attribute to shader program. Shader Program ID: " <<
                           vt_utils::NumberToString(_program) << " Attribute Location: " <<
                           vt_utils::NumberToString(count) << " Attribute Name: " << *i <<
                           std::endl;
                assert(error == GL_NO_ERROR);
            }

            ++count;
            ++i;
        }
    }

    // Link the shader program.
    if (!errors) {
        glLinkProgram(_program);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            errors = true;
            PRINT_ERROR << "Failed to link shader program. Shader Program ID: " <<
                           vt_utils::NumberToString(_program) <<
                           std::endl;
            assert(error == GL_NO_ERROR);
        }
    }

    // Check for linkage errors.
    if (errors)
        return;

    GLint is_linked = -1;
    glGetProgramiv(_program, GL_LINK_STATUS, &is_linked);

    // Return if linkage went well
    if (is_linked != 0)
        return;

    // Retrieve the linker output.
    GLint length = 0;
    glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &length);

    // Allocate space for the log.
    char* log = new char[length];
    memset(log, 0, length);
    glGetProgramInfoLog(_program, length, &length, log);

    PRINT_ERROR << "Failed to link the shader program. Shader Program ID: " <<
                    vt_utils::NumberToString(_program) << " Linker Output: " <<
                    log << std::endl;

    // Clean up the log.
    delete [] log;
    log = nullptr;

    assert(is_linked != 0);
}

ShaderProgram::~ShaderProgram()
{
    glDetachShader(_program, _vertex_shader->_shader);
    glDetachShader(_program, _fragment_shader->_shader);

    if (_program != 0) {
        glDeleteProgram(_program);
        _program = 0;
    }
}

bool ShaderProgram::Load()
{
    bool result = true;

    glUseProgram(_program);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        result = false;
        PRINT_ERROR << "Failed to load the shader program. Shader Program ID: " <<
                       vt_utils::NumberToString(_program) <<
                       std::endl;
        assert(error == GL_NO_ERROR);
    }

    return result;
}

bool ShaderProgram::UpdateUniform(const std::string& uniform, float value)
{
    bool result = true;

    GLint location = glGetUniformLocation(_program, uniform.c_str());
    glUniform1f(location, value);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        result = false;
        PRINT_ERROR << "Failed to update the shader program uniform. Shader Program ID: " <<
                       vt_utils::NumberToString(_program) << " Uniform Name: " << uniform <<
                       std::endl;
        assert(error == GL_NO_ERROR);
    }

    return result;
}

bool ShaderProgram::UpdateUniform(const std::string& uniform, int32_t value)
{
    bool result = true;

    GLint location = glGetUniformLocation(_program, uniform.c_str());
    glUniform1i(location, value);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        result = false;
        PRINT_ERROR << "Failed to update the shader program uniform. Shader Program ID: " <<
                       vt_utils::NumberToString(_program) << " Uniform Name: " << uniform <<
                       std::endl;
        assert(error == GL_NO_ERROR);
    }

    return result;
}

bool ShaderProgram::UpdateUniform(const std::string& uniform, const float* data, uint32_t length)
{
    bool result = false;

    GLint location = glGetUniformLocation(_program, uniform.c_str());

    // This function currently only supports matrices and vectors.
    assert(data != nullptr && (length == 4 || length == 16 || length == 1));
    if (data != nullptr) {
        if (length == 4) {
            result = true;

            // The vector case.
            glUniform4f(location, data[0], data[1], data[2], data[3]);
        }
        else if (length == 16) {
            result = true;

            // The matrix case.
            glUniformMatrix4fv(location, 1, true, data);
        } else if(length == 1) {
            result = true;

            // The single variable case.
            glUniform1d(location, data[1]);
        }
    }

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        result = false;
        PRINT_ERROR << "Failed to update the shader program uniform. Shader Program ID: " <<
                       vt_utils::NumberToString(_program) << " Uniform Name: " << uniform <<
                       std::endl;
        assert(error == GL_NO_ERROR);
    }

    return result;
}

ShaderProgram::ShaderProgram(const ShaderProgram&)
{
    throw vt_utils::Exception("Not Implemented!",
                              __FILE__, __LINE__, __FUNCTION__);
}

ShaderProgram& ShaderProgram::operator=(const ShaderProgram&)
{
    throw vt_utils::Exception("Not Implemented!",
                              __FILE__, __LINE__, __FUNCTION__);
    return *this;
}

} // namespace gl

} // namespace vt_video
