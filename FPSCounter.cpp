#include <chrono>
#include <iostream>

class FPSCounter {
public:
    void frameStart() {
        currentFrameTime = std::chrono::high_resolution_clock::now();
    }

    void frameEnd() {
        auto now = std::chrono::high_resolution_clock::now();
        double frameTime = std::chrono::duration<double, std::chrono::seconds::period>(now - currentFrameTime).count();

        frameCount++;
        elapsedTime += frameTime;
        if (elapsedTime >= 1.0) {
            fps = frameCount / elapsedTime;
            std::cout << "FPS: " << fps << std::endl;
            frameCount = 0;
            elapsedTime = 0.0;
        }
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> currentFrameTime;
    int frameCount = 0;
    double elapsedTime = 0.0;
    double fps = 0.0;
};
