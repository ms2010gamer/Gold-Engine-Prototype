#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace gold { namespace graphics {
	
#define MAX_KEYS		1024
#define MAX_BUTTONS		32

	class Window
	{
	private:
		friend struct GLFWwindow;

		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow* m_Window;
		bool m_Closed;

		static bool m_Keys[MAX_KEYS];
		static bool m_MouseButtons[MAX_BUTTONS];
		static double mx, my;
	public:
		Window(const char* name, int width, int height);
		~Window();
		bool closed() const;
		void update();
		void clear() const;
		void close() const;

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }

		static bool isKeyPressed(unsigned int keyCode);
	private:
		bool init();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};

}}