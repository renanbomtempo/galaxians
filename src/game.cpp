#include "game.hpp"

void Game::Init()
{
    ResourceManager::LoadTexture("player", "GameAssets/textures/player.png", true);
    ResourceManager::LoadShader("sprite", "GameAssets/shaders/sprite.vs", "GameAssets/shaders/sprite.fs", nullptr);

    glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(DEFAULT_SCR_WIDTH), static_cast<float>(DEFAULT_SCR_HEIGHT), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", proj);
}