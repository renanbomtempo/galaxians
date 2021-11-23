#include "player.hpp"

Player::Player()
{
    this->transform.positon = vec3(0);
    this->transform.scale = vec3(10);
}

void Player::Update()
{
    double xpos, ypos;
    glfwGetCursorPos(Core::getWindowPtr(), &xpos, &ypos);
    const int scancode = glfwGetKeyScancode(GLFW_KEY_X);

    this->transform.MoveTo(vec3(xpos, ypos, 0));
}

void Player::Move()
{

}

void Player::TakeDamage(unsigned int damage)
{

}

void Player::Shoot(unsigned int damage)
{

}

void Player::Render(SpriteRenderer &renderer)
{
    renderer.DrawSprite(material.GetTexture(), transform.positon, transform.scale);
}
