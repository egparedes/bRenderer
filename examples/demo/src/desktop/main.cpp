#include <bRenderer.h>
#include "../RenderProject.h"

int main(void)
{
#if (defined WIN32) || (defined _WIN32)
	bRenderer::setStandardFilePath("./data");
#else
	bRenderer::setStandardFilePath("./data");
#endif

	// Create and initialize the RenderProject
	RenderProject *project = new RenderProject();
	project->init();
	delete project;

	std::cout << "press ENTER to quit" << std::endl;
	std::cin.ignore();

	return 0;
}