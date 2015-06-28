#include "../../headers/OSdetect.h"

#ifdef OS_IOS

#include "../../headers/Renderer.h"
#include "../../headers/IRenderProject.h"

/* Public functions */

bool Renderer::isRunning()
{
    return _view.isRunning();
}

void Renderer::runRenderer()
{
    _view.setRunning(true);
    bRenderer::log("Renderer started", bRenderer::LM_SYS);
}

void Renderer::stopRenderer()
{
    _view.setRunning(false);
    bRenderer::log("Renderer stopped", bRenderer::LM_SYS);
}

void Renderer::terminateRenderer()
{
    _initialized = false;
    
    if (_terminateFunction)
        _terminateFunction();
    
    if (_renderProject)
        _renderProject->terminateFunction();
    
	_view.terminateView();

	reset();
    
    bRenderer::log("Renderer terminated", bRenderer::LM_SYS);
    
    //        exit(0);
}

/* Private functions */

void Renderer::draw(double currentTime)
{
	// clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render here
    if (_loopFunction)
        _loopFunction(currentTime - _elapsedTime, currentTime);
    
    if (_renderProject)
        _renderProject->loopFunction(currentTime - _elapsedTime, currentTime);
    
    // adjust time
    _elapsedTime = currentTime;
}

#endif