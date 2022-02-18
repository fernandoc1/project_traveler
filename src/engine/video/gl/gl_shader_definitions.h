
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
    const std::string getSolidFragment();
    const std::string getSolidGrayscaleFragment();
    const std::string getSpriteFragment();
    const std::string getSpriteGrayscaleFragment();

} // namespace shader_definition

} // namespace gl

} // namespace vt_video

#endif // __GL_SHADER_DEFINITIONS_HEADER__
