#include "AnimationApplication.h"
#include "AppSettings.h"

int main(int argc, char* argv[])
{

	AnimationApplication application;
	
	Debugger::print = false;

	Mesh::normalScale = NORMALS_SIZE;
	Light::lightModelScale = LIGHT_MODEL_SIZE;

	application.InitializeWindow(APP_WIDTH, APP_HEIGHT);

	application.MainLoop();

	return -1;
}