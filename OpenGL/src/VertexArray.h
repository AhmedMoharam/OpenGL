#pragma once
#include <vector>
#include <GL/glew.h>

struct LayoutElement {
	LayoutElement(int count, unsigned int type, bool normalized) :
		m_count(count), m_type(type), m_normalized(normalized){}

	int m_count;
	unsigned int m_type;
	bool m_normalized;
};

class VertexAttribLayout {
public:
	friend class VertexArray;
	VertexAttribLayout();
	~VertexAttribLayout();
	template <typename Type>
	void push(int count, bool normalized) {
		static_assert(0);
	}
	template <>
	void push<float>(int count, bool normalized) {
		m_elements.push_back({ count, GL_FLOAT, normalized });
		m_stride  += count * sizeof(float);
	}
	template <>
	void push<unsigned int>(int count, bool normalized) {
		m_elements.push_back({ count, GL_UNSIGNED_INT, normalized });
		m_stride += count * sizeof(unsigned int);
	}
	template <>
	void push<int>(int count, bool normalized) {
		m_elements.push_back({ count, GL_INT, normalized });
		m_stride += count * sizeof(int);
	}

private:
	//stride is the whole vertex structure size
	//https://stackoverflow.com/questions/4291271/opengl-vertex-attribute-stride 
	unsigned int m_stride;
	std::vector< LayoutElement> m_elements;
};

class ArrayBuffer;
class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void AddLayout(const VertexAttribLayout& layout, const ArrayBuffer& vb);
	void Bind() const;
	void UnBind() const;
private:
	unsigned int m_Renderer;
};
typedef  VertexArray VertexArrayObject;

