#include <iostream>
#include <tuple>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


std::tuple<std::string, std::string> ParseShaders(const std::string & file_path) {
	std::ifstream inputFile(file_path);
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

	return std::make_tuple<std::string, std::string>(ss[ShaderType::Vertex].str(), ss[ShaderType::Fragment].str());
}

unsigned int CreateProgram(const std::vector<std::pair<std::string, unsigned int>>& shaders) {

	unsigned int program = glCreateProgram();
	for (auto & shader : shaders) {
		unsigned int id = glCreateShader(shader.second);
		const char * src = shader.first.c_str();
		glShaderSource(id, 1, &src, NULL);
		glCompileShader(id);
		int compile_status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
		if (compile_status != GL_TRUE) {
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetShaderInfoLog(id, 1024, &log_length, message);
			std::cout << "ERROR! Compiling Shader:\n" << message << std::endl;
			std::exit(EXIT_FAILURE);
		}
		glAttachShader(program, id);
	}
	int link_status;
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(program, 1024, &log_length, message);
		std::cout << "ERROR! Linking Shaders:\n" << message << std::endl;
		std::exit(EXIT_FAILURE);
	}
	glValidateProgram(program);
	int validation_status;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &validation_status);
	if (validation_status != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(program, 1024, &log_length, message);
		std::cout << "ERROR! Application is not valid:\n" << message << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return program;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
#ifdef _WIN64
	window = glfwCreateWindow(640, 480, "Hello World (WIN64)", NULL, NULL);
#else
	window = glfwCreateWindow(640, 480, "Hello World (WIN32)", NULL, NULL);
#endif
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	unsigned int err = glewInit();
	
	float postions[] = { -0.5f, -0.5f,	//0
						  0.5f , -0.5f,	//1
						  0.5f , 0.5f ,	//2
						 -0.5f, 0.5f };	//3

	unsigned char indecies[] = { 0,1,2,	//1st triangle
								 0,2,3 };	//2nd triangle
	//create buffer and fill it with data
	unsigned int buffer_id;
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, postions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);

	//create index buffer object
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned char) * 2 * 3, indecies, GL_STATIC_DRAW);

	auto [vertex_shader, fragment_shader] = ParseShaders("Resources/Shaders/basic.shader");
	unsigned int program = CreateProgram({ {vertex_shader, GL_VERTEX_SHADER }, {fragment_shader, GL_FRAGMENT_SHADER } });
	glUseProgram(program);
	

	if (err != GLEW_OK) {
		std::cout << "error occured!" << std::endl;
		return 1;
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//glBindVertexArray(vao_id);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);


		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}