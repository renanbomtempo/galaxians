#include <iostream>
#include <chrono>
#include <thread>
#include "moxxi/core.hpp"
#include "game.hpp"
#include "player.hpp"

using namespace std;
using namespace moxxi;

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

int main()
{
    // Initialize engine core (initializes OpenGL libraries)
    // -----------------------------------------------------
    Core::InitializeGraphics(800, 600);

    Game game;
    game.Init();
    
    // Configur renderer
    Shader sprite_shader = ResourceManager::GetShader("sprite");
    SpriteRenderer sprite_renderer = SpriteRenderer(sprite_shader);

    
    // Configure player
    Player player = Player();
    player.material.SetTexture("player");
    

    while(!glfwWindowShouldClose(Core::getWindowPtr()))
    {
        player.Update();
        player.Render(sprite_renderer);

        Core::Refresh();
    }

    return 0;
}