#include "SystemParams.h"

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
* February 2016
*/

SystemParams::SystemParams()
{
}

// not using qrc
//std::string SystemParams::v_shader_file = "D:\\Code\\QtOpenGLCanvas33\\shader.vert";
//std::string SystemParams::f_shader_file = "D:\\Code\\QtOpenGLCanvas33\\shader.frag";

// using qrc
// not that the colon sign means the file is taken for a .qrc file
std::string SystemParams::v_shader_file = ":/shader.vert"; 
std::string SystemParams::f_shader_file = ":/shader.frag";
