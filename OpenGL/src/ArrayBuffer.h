#pragma once

class ArrayBuffer
{
public:

	ArrayBuffer();
	virtual ~ArrayBuffer() = 0;
	virtual void Bind() const =0;
	virtual void UnBind() const = 0;

};

class VertexArrayBuffer : public ArrayBuffer
{
public:
	VertexArrayBuffer(const void * data, unsigned int size);
	~VertexArrayBuffer() override;
	void Bind() const override;
	void UnBind() const override;

private:
	unsigned int m_Renderer;
};

class ElementArrayBuffer : public ArrayBuffer
{
public:
	ElementArrayBuffer(const void * data, unsigned int size);
	~ElementArrayBuffer() override;
	void Bind() const override;
	void UnBind() const override;

private:
	unsigned int m_Renderer;
};
typedef ElementArrayBuffer IndexBuffer;