#include "WindowManager.h"
#include "Application.h"
#include "InputManager.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

WindowManager::WindowManager(Application* _app)
{
	app = _app;

	SCRWIDTH = 800;
	SCRHEIGHT = 800;

	window = InitialiseGLFW();
	glfwMakeContextCurrent(window);
}

//GLFWwindow* WindowManager::GetWindow()
//{
//	return window;
//}


GLFWwindow* WindowManager::InitialiseGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	GLFWwindow* window{ glfwCreateWindow(SCRWIDTH, SCRHEIGHT, "[Render Engine Name Here]", NULL, NULL) };
	if (window == NULL) {
		std::cerr << "Failed to initialise GLFW." << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);
	glfwSetCursorPosCallback(window, &mouse_callback);
	glfwSetScrollCallback(window, &scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return window;
}

void WindowManager::framebuffer_size_callback_impl(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void WindowManager::mouse_callback_impl(GLFWwindow* window, double xposIn, double yposIn)
{
	app->inputManager->ProcessMouse(xposIn, yposIn);
}

void WindowManager::scroll_callback_impl(GLFWwindow* window, double xOffset, double yOffset)
{
	app->inputManager->ProcessScroll(yOffset);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	WindowManager* wm = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
	wm->framebuffer_size_callback_impl(window, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	WindowManager* wm = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
	wm->mouse_callback_impl(window, xposIn, yposIn);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	WindowManager* wm = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
	wm->scroll_callback_impl(window, xOffset, yOffset);
}