#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ArrayBuffer.h"
#include "VertexArray.h"
#include "Shader.h"



#include <functional>

void do_smthng() {
	// shader update position
	std::cout << "Key is pressed" << std::endl;
}



class InputControl {
public:
	void configure(int key, int action, std::function<void()> func){
		m_key = key;
		m_func = func;
	}

	std::function<void()> m_func;
	int m_key;
};

InputControl inputs;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == inputs.m_key && action == GLFW_PRESS)
		inputs.m_func();
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
	if (err != GLEW_OK) {
		std::cout << "error occured!" << std::endl;
		return 1;
	}

	/*setup keys Input*/
	glfwSetKeyCallback(window, key_callback);
	
	float postions[] = { -0.5f, -0.5f,	//0
						  0.5f , -0.5f,	//1
						  0.5f , 0.5f ,	//2
						 -0.5f, 0.5f };	//3

	unsigned char indecies[] = { 0,1,2,	//1st triangle
								 0,2,3 };	//2nd triangle
	
	// put the veticies data into GPU memory (vertix array buffer) - raw data
	VertexArrayBuffer vb(postions, sizeof(float) * 2 * 4);
	// create a layout for the data, descripe the raw data layout you entered -- this case each vertix is 2 floats
	VertexAttribLayout layout;
	layout.push<float>(2, false);
	// now connect the vertix attribute layout and the vetrix array buffer with vertix array object
	VertexArrayObject vao;
	vao.AddLayout(layout, vb);

	// put the indecies to index buffer
	IndexBuffer ib(indecies, sizeof(unsigned char) * 2 * 3);
	ShaderProgram program("Resources/Shaders/basic.shader");
	
	//TODO: use operator overloading
	unsigned int u_color = glGetUniformLocation(program.GetId(), "u_color");
	glProgramUniform4f(program.GetId(), u_color, 1.0f, 0.0f, 1.0f, 1.0f);

	
	inputs.configure((int)GLFW_KEY_E, (int)GLFW_PRESS, do_smthng);

	vb.UnBind();
	vao.Bind();
	ib.Bind();
	program.Bind();

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