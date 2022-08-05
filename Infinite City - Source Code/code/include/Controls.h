#pragma once
#include <GLFW/glfw3.h> 

class Controls {
    public:
        static int shiftState;
        static double lastMousePosX;
        static double lastMousePosY;

        static void globalControls(GLFWwindow* window);
        static void firstPersonControls(GLFWwindow* window, float dt);
};