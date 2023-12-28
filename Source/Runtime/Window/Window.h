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
/// File:           Window.h
/// Create Time:    2023/12/27 17:31
/// Author:         bit-fashion
/// EMail:          bit-fashion@hotmail.com
/// GitHub:         github.com/bit-fashion
///
//////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Typedef.h>
#include <GLFW/glfw3.h>

class Window;

typedef void (*PFN_WindowResizeEventCallback) (Window *p_win, int w, int h);

//
// 封装 GLFW Window 窗口类
//
class Window {
public:
    Window(int w, int h, const char *title);
   ~Window();

   void AddWindowUserPointer(const std::string &name, void *pointer);
   void *GetWindowUserPointer(const std::string &name);
   void AddWindowResizeEventCallback(PFN_WindowResizeEventCallback callback);

public:
   //
   // GET/SET
   //
   int GetWidth() const { return m_Width; }
   int GetHeight() const { return m_Height; }
   GLFWwindow *GetWindowHandle() const { return m_HWIN; }

   //
   // GLFW
   //
   bool IsShouldClose() { return glfwWindowShouldClose(m_HWIN); }

public:
    //
    // 事件轮询
    //
    inline static void PollEvents() { glfwPollEvents(); }

private:
    int m_Width;
    int m_Height;
    GLFWwindow *m_HWIN;

    Vector<PFN_WindowResizeEventCallback> m_WindowResizeEventCallbacks;
    HashMap<std::string, void *> m_WindowUserPointers;
};