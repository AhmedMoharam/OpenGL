#include "VertexArray.h"
#include "ArrayBuffer.h"
#include <GL/glew.h>

static unsigned int getSize(unsigned int type) {
	switch (type)
	{
	case GL_FLOAT:
		return sizeof(float);
	case GL_UNSIGNED_INT:
		return sizeof(unsigned int);
	case GL_INT:
		return sizeof(int);
	default:
		return 0;
	}
}

VertexAttribLayout::VertexAttribLayout():  m_stride(0)
{
}

VertexAttribLayout::~VertexAttribLayout()
{
}

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_Renderer);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_Renderer);
}

void VertexArray::AddLayout(const VertexAttribLayout & layout, const ArrayBuffer & vb)
{
// offset is the offset in bytes of the position data
// in each vertex. For example if your vertex structure is
// [ position, texcoord, normal ] then position vertex_position_offset will
// have offset 0, vertex_texcoord_offset is 12 (position is 3 * sizeof(float)
// bytes large, and texcoord comes just after) and vertex_normal_offset is
// 20 = 5 * sizeof(float).
// http://docs.gl/gl4/glEnableVertexAttribArray

	vb.Bind();
	Bind();
	GLintptr offset = 0;
	for (int i = 0; i < layout.m_elements.size(); i ++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, layout.m_elements[i].m_count, layout.m_elements[i].m_type, layout.m_elements[i].m_normalized, layout.m_stride, (void *) offset);
		offset += layout.m_elements[i].m_count * getSize(layout.m_elements[i].m_type);
	}

}

void VertexArray::Bind() const
{
	glBindVertexArray(m_Renderer);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}
