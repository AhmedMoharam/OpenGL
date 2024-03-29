#pragma once
#include <string>
#include <vector>

class Shader
{
public:
	Shader() = default;
	virtual ~Shader() {};
	virtual void Compile() = 0;
	virtual unsigned int GetId() = 0;

protected:
	void CompileShaderId(unsigned int id);
	
};

class VertexShader : public Shader
{
public:
	VertexShader(const std::string &);
	~VertexShader() override;
	void Compile() override;
	unsigned int GetId() override;
private:
	unsigned int m_id;
};

class FragmentShader : public Shader
{
public:
	FragmentShader(const std::string &);
	~FragmentShader() override;
	void Compile() override;
	unsigned int GetId() override;
private:
	unsigned int m_id;
};



class ShaderProgram
{
public:
	ShaderProgram(std::string file_path);
	~ShaderProgram();
	unsigned int GetId();
	void Bind();
	void UnBind();

private:
	void ParseShaderFile();
	void Compile();

private:
	unsigned int m_id;
	std::string m_file_path;
	std::vector< std::shared_ptr<Shader> > m_shaders;
};
