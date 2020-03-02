#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

//interface
Shader::Shader()
{
}

Shader::~Shader()
{
}


//vertexShader
VertexShader::VertexShader(const std::string & src) : m_src(src)
{
	m_id = glCreateShader(GL_VERTEX_SHADER);
}

VertexShader::~VertexShader()
{
	glDeleteShader(m_id);
}

void VertexShader::Compile()
{
	const char * src = m_src.c_str();
	glShaderSource(m_id, 1, &src, NULL);
	glCompileShader(m_id);
	int compile_status;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &compile_status);
	if (compile_status != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_id, 1024, &log_length, message);
		std::cout << "ERROR! Compiling Shader:\n" << message << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

unsigned int VertexShader::GetId()
{
	return m_id;
}


//FragmentShader
FragmentShader::FragmentShader(const std::string & src) : m_src(src)
{
	m_id = glCreateShader(GL_FRAGMENT_SHADER);
}

FragmentShader::~FragmentShader()
{
	glDeleteShader(m_id);
}

void FragmentShader::Compile()
{
	const char * src = m_src.c_str();
	glShaderSource(m_id, 1, &src, NULL);
	glCompileShader(m_id);
	int compile_status;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &compile_status);
	if (compile_status != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_id, 1024, &log_length, message);
		std::cout << "ERROR! Compiling Shader:\n" << message << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

unsigned int FragmentShader::GetId()
{
	return m_id;
}


//ShaderProgram
ShaderProgram::ShaderProgram(std::string file_path) 
	: m_file_path(file_path), m_id(0)
{
	ParseShaderFile();
	Compile();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_id);
}

unsigned int ShaderProgram::GetId()
{
	return m_id;
}


void ShaderProgram::Bind()
{
	glUseProgram(m_id);
}

void ShaderProgram::UnBind()
{
	glUseProgram(0);
}

void ShaderProgram::ParseShaderFile()
{
	std::ifstream inputFile(m_file_path);
	std::string line;
	enum ShaderType {
		None = -1,
		Vertex = 0,
		Fragment = 1
	};
	ShaderType shader_mode = ShaderType::None;
	std::stringstream ss[2];

	while (std::getline(inputFile, line)) {
		if (line.find("#ShaderBegin") != std::string::npos) {
			if (line.find("VertexShader") != std::string::npos) {
				shader_mode = ShaderType::Vertex;
			}
			else if (line.find("FragmentShader") != std::string::npos) {
				shader_mode = ShaderType::Fragment;
			}
		}
		else {
			ss[shader_mode] << line << std::endl;
		}
	}

	m_shaders.push_back( std::make_shared<VertexShader> (ss[ShaderType::Vertex].str()) );
	m_shaders.push_back(std::make_shared<FragmentShader>(ss[ShaderType::Fragment].str()) );

}

void ShaderProgram::Compile()
{
	m_id = glCreateProgram();
	for (auto & shader : m_shaders) {
		shader->Compile();
		glAttachShader(m_id, shader->GetId());
	}
	int link_status;
	glLinkProgram(m_id);
	glGetProgramiv(m_id, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(m_id, 1024, &log_length, message);
		std::cout << "ERROR! Linking Shaders:\n" << message << std::endl;
		std::exit(EXIT_FAILURE);
	}
	glValidateProgram(m_id);
	int validation_status;
	glGetProgramiv(m_id, GL_VALIDATE_STATUS, &validation_status);
	if (validation_status != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(m_id, 1024, &log_length, message);
		std::cout << "ERROR! Application is not valid:\n" << message << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

