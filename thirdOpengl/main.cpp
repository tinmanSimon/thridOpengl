#include "Window.h"
#include <Simon/simon_func.h>
#include <STB_IMG/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>





using namespace std;
using namespace glm;

int main() {
	float width = 1900;
	float height = 1200;
	char w_name[100] = "secOpengl";
	window = new Window(w_name, width, height);
	if (window->init() != 0) return -1;
	window->loop();
	free(window);
	return 0;
}