#include "window.h"

namespace gold { namespace graphics {

	bool Window::m_Keys[MAX_KEYS];
	bool Window::m_MouseButtons[MAX_BUTTONS];
	double Window::mx, Window::my;

	void window_resize(GLFWwindow* window, int width, int height);

	Window::Window(const char* title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (!init())
			glfwTerminate();

		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_Keys[i] = false;
		}
		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtons[i] = false;
		}
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed To Load GLFW!" << std::endl;
			return false;
		}
			
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed To Create GLFW Window!" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed To Load GLEW!" << std::endl;
			return false;
		}

		return true;
	}

	void Window::update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void window_resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	bool Window::isKeyPressed(unsigned int keyCode)
	{
		if (keyCode >= MAX_KEYS)
			return false;
			return false;

		return m_Keys[keyCode];
	}
}}