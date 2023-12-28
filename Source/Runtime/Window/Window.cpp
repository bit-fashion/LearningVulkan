/* -------------------------------------------------------------------------------- *\
|*                                                                                  *|
|*    Copyright (C) 2023 bit-fashion                                                *|
|*                                                                                  *|
|*    This program is free software: you can redistribute it and/or modify          *|
|*    it under the terms of the GNU General Public License as published by          *|
|*    the Free Software Foundation, either version 3 of the License, or             *|
|*    (at your option) any later version.                                           *|
|*                                                                                  *|
|*    This program is distributed in the hope that it will be useful,               *|
|*    but WITHOUT ANY WARRANTY; without even the implied warranty of                *|
|*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *|
|*    GNU General Public License for more details.                                  *|
|*                                                                                  *|
|*    You should have received a copy of the GNU General Public License             *|
|*    along with this program.  If not, see <https://www.gnu.org/licenses/>.        *|
|*                                                                                  *|
|*    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.    *|
|*    This is free software, and you are welcome to redistribute it                 *|
|*    under certain conditions; type `show c' for details.                          *|
|*                                                                                  *|
\* -------------------------------------------------------------------------------- */

//////////////////////////////////////////////////////////////////////////////////////
///
/// File:           Window.cpp
/// Create Time:    2023/12/27 17:31
/// Author:         bit-fashion
/// EMail:          bit-fashion@hotmail.com
/// GitHub:         github.com/bit-fashion
///
//////////////////////////////////////////////////////////////////////////////////////
#include "Window.h"

Window::Window(int w, int h, const char *title)
  : m_Width(w), m_Height(h)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_HWIN = glfwCreateWindow(w, h, title, nullptr, nullptr);

    if (m_HWIN == NULL)
        throw std::runtime_error("Create glfw window failed!");

    glfwSetWindowUserPointer(m_HWIN, this);

    /* 设置窗口缩放事件 */
    glfwSetWindowSizeCallback(m_HWIN, [](GLFWwindow *window, int w, int h) {
        Window *p_win = (Window *) glfwGetWindowUserPointer(window);
        for (const auto &callback: p_win->m_WindowResizeEventCallbacks)
            callback(p_win, w, h);
    });
}

Window::~Window() {
    glfwDestroyWindow(m_HWIN);
    glfwTerminate();
}

void Window::AddWindowUserPointer(const std::string &name, void *pointer) {
    m_WindowUserPointers[name] = pointer;
}

void *Window::GetWindowUserPointer(const std::string &name) {
    return m_WindowUserPointers[name];
}

void Window::AddWindowResizeEventCallback(PFN_WindowResizeEventCallback callback) {
    m_WindowResizeEventCallbacks.push_back(callback);
}