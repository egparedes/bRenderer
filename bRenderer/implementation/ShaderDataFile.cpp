#include <string>
#include <fstream>
#include <iostream>
#include "../headers/ShaderDataFile.h"
#include "../headers/Logger.h"
#include "../headers/FileHandler.h"
#include "../headers/OSdetect.h"
#include "../headers/Configuration.h"
#include <boost/lexical_cast.hpp>

using boost::lexical_cast;

ShaderDataFile::ShaderDataFile(const std::string &shaderFileName, const std::string &shaderVersionDesktop, const std::string &shaderVersionES, GLuint maxLights)
	: _valid(true), _shaderVersionDesktop(shaderVersionDesktop), _shaderVersionES(shaderVersionES), _maxLights(maxLights)
{
	load(shaderFileName);
}

ShaderDataFile::ShaderDataFile(const std::string &vertShaderFileName, const std::string &fragShaderFileName, const std::string &shaderVersionDesktop, const std::string &shaderVersionES, GLuint maxLights)
	: _valid(false), _shaderVersionDesktop(shaderVersionDesktop), _shaderVersionES(shaderVersionES), _maxLights(maxLights)
{
    load(vertShaderFileName, fragShaderFileName);
}

ShaderDataFile::ShaderDataFile()
:   _valid(false)
{}

ShaderDataFile &ShaderDataFile::load(const std::string &shaderFileName)
{
	return load(shaderFileName + bRenderer::DEFAULT_VERTEX_SHADER_FILENAME_EXTENSION, shaderFileName + bRenderer::DEFAULT_FRAGMENT_SHADER_FILENAME_EXTENSION);
}

ShaderDataFile &ShaderDataFile::load(const std::string &vertShaderFileName, const std::string &fragShaderFileName)
{
    _vertShaderSrc = loadSrc(vertShaderFileName);
    _fragShaderSrc = loadSrc(fragShaderFileName);

	
#ifdef OS_DESKTOP	
	replaceMacro(bRenderer::SHADER_VERSION_MACRO, _shaderVersionDesktop);
#endif
#ifdef OS_IOS
	replaceMacro(bRenderer::SHADER_VERSION_MACRO, _shaderVersionES);
#endif
	replaceMacro(bRenderer::SHADER_MAX_LIGHTS_MACRO, lexical_cast< std::string >(_maxLights));

    return *this;
}

std::string ShaderDataFile::loadSrc(const std::string &fileName)
{
    bRenderer::log("Trying to load shader file " + fileName, bRenderer::LM_SYS);
    
    _valid = false;
    
    if (!bRenderer::fileExists(fileName))
    {
		bRenderer::log("Shader file doesn't exist: " + fileName, bRenderer::LM_ERROR);
        return std::string();
    }
    
	std::ifstream file(bRenderer::getFilePath(fileName), std::ifstream::in);
    
    std::string ret;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.length() > 0)
        {
            _valid = true;
        }
        ret += line + "\n";
    }
    
    return ret;
}

void ShaderDataFile::replaceMacro(const std::string &macro, const std::string &value)
{
	size_t i;
	size_t s = macro.size();
	while ((i = _vertShaderSrc.find(macro)) != std::string::npos)
		_vertShaderSrc.replace(i, s, value);
	while ((i = _fragShaderSrc.find(macro)) != std::string::npos)
		_fragShaderSrc.replace(i, s, value);
}