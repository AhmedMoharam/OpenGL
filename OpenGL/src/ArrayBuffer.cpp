#include "ArrayBuffer.h"
#include <GL/glew.h>


ArrayBuffer::ArrayBuffer()
{
}

ArrayBuffer::~ArrayBuffer()
{
}

VertexArrayBuffer::VertexArrayBuffer(const void * data, unsigned int size)
{
	//create, set, configure
	glGenBuffers(1, &m_Renderer);
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexArrayBuffer::~VertexArrayBuffer()
{
	glDeleteBuffers(1, &m_Renderer);
}

void VertexArrayBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer);
}

void VertexArrayBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


ElementArrayBuffer::ElementArrayBuffer(const void * data, unsigned int size)
{
	//create, set, configure
	glGenBuffers(1, &m_Renderer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

ElementArrayBuffer::~ElementArrayBuffer()
{
	glDeleteBuffers(1, &m_Renderer);
}

void ElementArrayBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer);
}

void ElementArrayBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


