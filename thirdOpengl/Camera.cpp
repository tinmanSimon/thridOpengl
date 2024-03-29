#include "Camera.h"

using namespace std;
using namespace glm;

Camera* cam;

float lastPress = 0.0f;


Camera::Camera()
{
	cameraFront = vec3(0.0f, 0.0f, -1.0f);
	cameraPos = vec3(0.0f, 0.0f, 3.0f);
	cameraUp = vec3(0.0f, 1.0f, 0.0f);
	fov = 45.0f;
	fovmin = 1.0f;
	fovmax = 90.0f;
	fovSensitive = 2.0f;

	//global variables for delta time
	currentFrame = 0.0f;
	lastFrame = 0.0f;
	deltaTime = 0.0f;

	//global variables for call back functions
	firstMouse = true;
	sensitivity = 0.05f;
	Yaw = -90.0f;
	Pitch = 0.0f;

	view = mat4(1.0f);
	projection = mat4(1.0f);
	n = 0.1f;
	f = 100.0f;

	camProtoSpeed = 1.5f;
}


Camera::~Camera()
{
}

void Camera::update() {
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection = glm::perspective(glm::radians(fov), window->width / window->height, n, f);
	//projection = glm::perspective(glm::radians(fov), 7.0f/6.0f, n, f);
}

//adjust window size
void framebuffer_size_callback(GLFWwindow * w, int width, int height) {
	window->height = (float)height;
	window->width = (float)width;
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow * window, double x, double y)
{
	float fov = cam->fov;
	float fovmin = cam->fovmin;
	float fovmax = cam->fovmax;
	float fovSensitive = cam->fovSensitive;
	if (fov >= fovmin && fov <= fovmax)
		cam->fov -= fovSensitive * y;
	if (fov <= fovmin)
		cam->fov = fovmin + 0.01f;
	if (fov >= fovmax)
		cam->fov = fovmax - 0.01f;
}

/*
The copyright of mouse_callback goes to Joey de Vries at https://learnopengl.com/Getting-started/Camera.
*/
void mouse_callback(GLFWwindow * window, double xpos, double ypos) {

	if (cam->firstMouse)
	{
		cam->lastX = xpos;
		cam->lastY = ypos;
		cam->firstMouse = false;
	}
	float lastX = cam->lastX;
	float lastY = cam->lastY;
	float sensitivity = cam->sensitivity;
	float Yaw = cam->Yaw;
	float Pitch = cam->Pitch;

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	cam->lastX = xpos;
	cam->lastY = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	cam->Yaw += xoffset;
	cam->Pitch += yoffset;

	//cout << Yaw << endl;

	if (Pitch > 89.0f) cam->Pitch = 89.0f;
	if (Pitch < -89.0f) cam->Pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(cam->Pitch)) * cos(glm::radians(cam->Yaw));
	front.y = sin(glm::radians(cam->Pitch));
	front.z = cos(glm::radians(cam->Pitch)) * sin(glm::radians(cam->Yaw));
	cam->cameraFront = glm::normalize(front);

}


void updateDeltaTime() {
	cam->currentFrame = glfwGetTime();
	cam->deltaTime = cam->currentFrame - cam->lastFrame;
	cam->lastFrame = cam->currentFrame;
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		float diff = glfwGetTime() - lastPress;
		if (diff > 0.2) pause = !pause;
		lastPress = glfwGetTime();
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		float diff = glfwGetTime() - lastPress;
		if (diff > 0.2) skyboxes = 1 - skyboxes;
		lastPress = glfwGetTime();
	}


	float cameraSpeed = cam->camProtoSpeed * cam->deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam->cameraPos += cameraSpeed * cam->cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam->cameraPos -= cameraSpeed * cam->cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam->cameraPos -= normalize(cross(cam->cameraFront, cam->cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam->cameraPos += normalize(cross(cam->cameraFront, cam->cameraUp)) * cameraSpeed;
}

