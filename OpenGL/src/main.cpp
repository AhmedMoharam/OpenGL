#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ArrayBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


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
	
	float postions[] = { -0.5f, -0.5f,	//0
						  0.5f , -0.5f,	//1
						  0.5f , 0.5f ,	//2
						 -0.5f, 0.5f };	//3

	unsigned char indecies[] = { 0,1,2,	//1st triangle
								 0,2,3 };	//2nd triangle
	
	VertexArrayBuffer vb(postions, sizeof(float) * 2 * 4);
	VertexAttribLayout layout;
	layout.push<float>(2, false);
	VertexArrayObject vao;
	vao.AddLayout(layout, vb);
	IndexBuffer ib(indecies, sizeof(unsigned char) * 2 * 3);
	ShaderProgram program("Resources/Shaders/basic.shader");
	
	//TODO: use operator overloading
	unsigned int u_color = glGetUniformLocation(program.GetId(), "u_color");
	glProgramUniform4f(program.GetId(), u_color, 1.0f, 0.0f, 1.0f, 1.0f);

	

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