/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/Shader.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "../Implementation.h"

namespace VisApp {
namespace Renderer { 

class ShaderParamsVector : public std::vector<char*> {
public:
	typedef Shader::eShaderParameters eShaderParameters;

	ShaderParamsVector() {
		
		resize((unsigned)eShaderParameters::spMaxValue, 0);

		at((unsigned)eShaderParameters::spWorldMatrix) = "WorldMatrix";
		at((unsigned)eShaderParameters::spModelMatrix) = "ModelMatrix";
		at((unsigned)eShaderParameters::spCameraPos) = "CameraPos";

		at((unsigned)eShaderParameters::spBaseColor) = "BaseColor";
		
	}
};

const ShaderParamsVector ShaderParams;

void Shader::TestOpenGLFunctions() {
#define OGLASSERT(NAME) { if(!(NAME)) { throw OpenGLFunctionAssertException(#NAME); } } 
	OGLASSERT(glCreateProgram);
	OGLASSERT(glDeleteProgram);
	OGLASSERT(glUniformMatrix4fv);
	OGLASSERT(glUniform3fv);
	OGLASSERT(glGetUniformLocation);
	OGLASSERT(glCreateShader);
	OGLASSERT(glShaderSource);
	OGLASSERT(glCompileShader);
	OGLASSERT(glGetShaderiv);
	OGLASSERT(glGetShaderInfoLog);
	OGLASSERT(glAttachShader);
	OGLASSERT(glLinkProgram);
	OGLASSERT(glGetProgramiv);
	OGLASSERT(glUseProgram);
	OGLASSERT(glBindAttribLocation);
#undef OGLASSERT
}
 
Shader::Shader(const std::wstring &Name): 
		m_ShaderProgram(glCreateProgram()),
		m_Name(Name) {
	m_Ready = false;
	CheckStandardParamsLocation();
}

Shader::~Shader() {
	glDeleteProgram(m_ShaderProgram);
}

void Shader::BindShader() const { 
	glUseProgram(m_ShaderProgram); 
}
	
void Shader::BindCamera(VirtualCamera *Camera) {
	glUniformMatrix4fv(Location(eShaderParameters::spWorldMatrix), 1, GL_FALSE, &Camera->GetWorldMatrix()[0][0]);
}

void Shader::CheckStandardParamsLocation() {
	for(unsigned i = (unsigned)eShaderParameters::spWorldMatrix; i < (unsigned)eShaderParameters::spMaxValue; ++i)
		if(ShaderParams[i])
			m_ShaderParameters[i] = glGetUniformLocation(m_ShaderProgram, ShaderParams[i]);
}

GLuint Shader::CustomLocation(const char* name) const {
	return glGetUniformLocation(m_ShaderProgram, name);
}

const wchar_t *Stage2String(GLenum Stage) {
	static wchar_t buf[20];
	switch (Stage) {
	case GL_FRAGMENT_SHADER: return L"fragment";
	case GL_VERTEX_SHADER: return L"vertex";
	case GL_GEOMETRY_SHADER: return L"geometry";
	default:
		wsprintf(buf, L"Unknown(0x%x)", Stage);
		return buf;
	}
}

bool Shader::LoadCode(GLenum Stage, const char** Code, unsigned ElementCount) {
	if(m_Ready) return false;
	// Compile Shader
	GLuint shader = glCreateShader(Stage);
	//const char *code = ShaderCode.c_str();
	glShaderSource(shader, ElementCount, Code , NULL);
	glCompileShader(shader);
	// Check Shader
	GLint Result = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &Result);
	if(Result != GL_TRUE) {
		int InfoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(shader, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		AddLog(Error, "Unable to compile shader '" << m_Name << "', shader stage: " << Stage2String(Stage) << ". Error message:\n" << &ShaderErrorMessage[0]);
		glDeleteShader(shader);
		return false;
	}
	glAttachShader(m_ShaderProgram, shader);
	return true;
}

bool Shader::LoadCodeFromFile(GLenum Stage, const char* File) {
	if(m_Ready) return false;
	AddLog(Hint, "Loading shader " << m_Name << ", adding stage from file: " << File)
	std::ifstream stream(File, std::ios::in | std::ios::binary);
	if(!stream) {
		//TODO??
		return false;
	}
	stream.seekg(0, std::ios::end);
	std::streamoff len = stream.tellg();
	std::string ShaderCode;
	ShaderCode.resize(static_cast<unsigned>(len) + 1, 0);

	stream.seekg(0, std::ios::beg);
	stream.read((char*)ShaderCode.c_str(), len);
	stream.close();	
	const char *code = ShaderCode.c_str();
	return LoadCode(Stage, &code, 1);
}

bool Shader::Compile() {
	if(m_Ready) return false;
	//link program
	glLinkProgram(m_ShaderProgram);
		//check program for errors
	GLint Result = GL_FALSE;
	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &Result);
	if(Result != GL_TRUE) {
		int InfoLogLength;
		glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(m_ShaderProgram, InfoLogLength, NULL, &ProgramErrorMessage[0]);			
		AddLog(Error, L"Unable to link program " << m_Name << ". Error message:\n" << &ProgramErrorMessage[0]);
		glDeleteProgram(m_ShaderProgram);
		return false;
	}
	m_Ready = true;
	CheckStandardParamsLocation();
	return true;
}

} //namespace Renderer
} //namespace VisApp
