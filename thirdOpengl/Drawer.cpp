#include "Drawer.h"

using namespace std;
using namespace glm;

bool pause = false;

int skyboxes = 1;

float cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
float planeVertices[] = {
	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
	 10.0f, -0.5f,  10.0f,  2.0f, 0.0f,
	-10.0f, -0.5f,  10.0f,  0.0f, 0.0f,
	-10.0f, -0.5f, -10.0f,  0.0f, 2.0f,

	 10.0f, -0.5f,  10.0f,  2.0f, 0.0f,
	-10.0f, -0.5f, -10.0f,  0.0f, 2.0f,
	 10.0f, -0.5f, -10.0f,  2.0f, 2.0f
};

float grassVertices[] = {
	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, 0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, 0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, 0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, 0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f
};

float screenVertices[] = {
	// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
};

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

vector<std::string> lake
{
	"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
};
vector<std::string> sahara
{

		"sahara_lf.jpg",
		"sahara_rt.jpg",
		"sahara_up.jpg",
		"sahara_dn.jpg",

		"sahara_ft.jpg",
		"sahara_bk.jpg"
};

//bloody-marvelous
vector<std::string> marvelous
{
		"bloody-marvelous_ft.jpg",
		"bloody-marvelous_bk.jpg",



		"bloody-marvelous_up.jpg",
		"bloody-marvelous_dn.jpg",

		"bloody-marvelous_rt.jpg",
		"bloody-marvelous_lf.jpg"

};

vector<glm::vec3> vegetation;
Drawer::Drawer()
{
}


Drawer::~Drawer()
{
}

unsigned int framebuffer; //for fbo test only
unsigned int texColorBuffer;
unsigned int rbo;
unsigned int depthFrameBuffer;
unsigned int depthMap;

void drawerinit() {
	//init VAOs, and note VAOS is the vector of all existing VAOs. Because in VAO constructor, it pushes itself to VAOS
	//no need to do it manually.
	new VAO(false);
	new VAO(false);
	new VAO(false);
	new VAO(false);
	new VAO(false);
	VAOS[0]->bufferData(cubeVertices, sizeof(cubeVertices));
	VAOS[0]->addAttribute(0,3,6*sizeof(float),0);
	VAOS[0]->addAttribute(1, 3, 6 * sizeof(float), (void*) (3*sizeof(float)));
	VAOS[1]->bufferData(skyboxVertices, sizeof(skyboxVertices));
	VAOS[1]->addAttribute(0, 3, 3 * sizeof(float), 0);
	VAOS[2]->bufferData(grassVertices, sizeof(grassVertices));
	VAOS[2]->addAttribute(0, 3, 5 * sizeof(float), 0);
	VAOS[2]->addAttribute(2, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	VAOS[3]->bufferData(screenVertices, sizeof(screenVertices));
	VAOS[3]->addAttribute(0, 2, 4 * sizeof(float), 0);
	VAOS[3]->addAttribute(1, 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	VAOS[4]->bufferData(planeVertices, sizeof(planeVertices));
	VAOS[4]->addAttribute(0, 3, 5 * sizeof(float), 0);
	VAOS[4]->addAttribute(2, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	//init shaders
	shaders.push_back(new Shader("vertex.txt", "frag2.txt"));
	shaders.push_back(new Shader("vertex2.txt", "frag4.txt"));
	shaders.push_back(new Shader("cubemapVertex.txt", "cubmapFrag.txt"));
	shaders.push_back(new Shader("envvertex.txt", "envfrag.txt"));
	shaders[0]->setInt(0, "texture1");
	shaders[1]->setInt(0, "texture1");
	shaders[2]->setInt(0, "skybox");
	shaders[3]->setInt(0, "skybox");

	//init textures
	Texture::reverseImage();
	globalTextures.push_back(new Texture("floor2.png"));
	globalTextures.push_back(new Texture("diagmonds.png","","",GL_RGBA,1));

	//generate multi sample fbo
	globalTextures.push_back(new Texture(window->width, window->height, true));
	framebuffer = globalTextures[2]->framebuffer;

	//init cube text
	Texture::reverseImage();
	globalTextures.push_back(new Texture(marvelous));
	globalTextures.push_back(new Texture(lake));

	//another fbo for intermidiate and depth
	globalTextures.push_back(new Texture(window->width, window->height));
	
	//depth frame buffer
	glGenFramebuffers(1, &depthFrameBuffer);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		window->width, window->height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthFrameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);



	//init camera
	cam = new Camera();

	//for blending
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 1.3f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 1.6f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 1.9f));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

void logic() {
	updateDeltaTime();

	//update camera
	cam->update();

	//set up shader
	//shader 0
	mat4 model = mat4(1.0f);
	model = translate(model, vec3(0.0f, -1.0f, 0.0f));
	shaders[0]->setmat4(model, "model");
	shaders[0]->setmat4(cam->view, "view");
	shaders[0]->setmat4(cam->projection, "projection");
	//model = translate(model, cam->cameraPos);
	//shaders[2]->setmat4(model, "model");
	mat4 view = mat4(mat3(cam->view));
	shaders[2]->setmat4(view, "view");
	shaders[2]->setmat4(cam->projection, "projection");

	shaders[3]->setmat4(cam->view, "view");
	shaders[3]->setmat4(cam->projection, "projection");
	shaders[3]->setVec3(cam->cameraPos.x, cam->cameraPos.y, cam->cameraPos.z, "cameraPos");

	//reset texture color buffer
	globalTextures[2]->resetWidthHeight(window->width, window->height, true);
	globalTextures[5]->resetWidthHeight(window->width, window->height);
}

void draw() {
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
	glEnable(GL_DEPTH_TEST);

	//draw cubemap
	glDepthMask(GL_FALSE); //disable depth writing since we are really drawing the skybox here
	shaders[2]->use();
	if(skyboxes == 1) globalTextures[3]->use(GL_TEXTURE0, GL_TEXTURE_CUBE_MAP);
	else globalTextures[4]->use(GL_TEXTURE0, GL_TEXTURE_CUBE_MAP);
	VAOS[1]->use();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
	
	//draw 2 cubes
	shaders[3]->use();
	VAOS[0]->use();
	mat4 model = mat4(1.0f);
	model = translate(model, vec3(0, 0.01, 0));
	shaders[3]->setmat4(model, "model");
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = mat4(1.0f);
	model = translate(model, vec3(0, 0.01, 3.6));
	shaders[3]->setmat4(model, "model");
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//draw 5 transparent walls
	shaders[0]->use();
	VAOS[2]->use();
	globalTextures[1]->use(GL_TEXTURE0);
	for (unsigned int i = 0; i < vegetation.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, vegetation[i]);
		shaders[0]->setmat4(model, "model");
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	
	
	glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, globalTextures[5]->framebuffer);
	glBlitFramebuffer(0, 0, window->width, window->height, 0, 0, window->width, window->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	VAOS[3]->use();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	shaders[1]->use();
	glDisable(GL_DEPTH_TEST);
	globalTextures[5]->use(GL_TEXTURE0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	
}

void cleanup() {
	for (int i = 0; i < VAOS.size(); ++i) {
		free(VAOS[i]);
	}
	for (int i = 0; i < shaders.size(); ++i) {
		free(shaders[i]);
	}
	for (int i = 0; i < Models.size(); ++i) {
		free(Models[i]);
	}
	for (int i = 0; i < globalTextures.size(); ++i) {
		free(globalTextures[i]);
	}
}