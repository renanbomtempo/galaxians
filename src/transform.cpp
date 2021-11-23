#include "moxxi/core.hpp"

namespace moxxi
{
    
Transform::Transform()
{
    this->positon = vec3(0);
    this->rotation = vec3(0);
    this->scale = vec3(1);
}

void Transform::Translate(vec3 direction)
{
    this->positon += direction;
}

void Transform::MoveTo(vec3 position)
{
    this->positon = position;
}   

void Transform::print()
{
    std::string msg;
    msg += "Transform.position = " + glm::to_string(this->positon) + "\n";
    msg += "Transform.rotation = " + glm::to_string(this->rotation) + "\n";
    msg += "Transform.scale = " + glm::to_string(this->scale);
    Debug::Echo(msg);
}

} // namespace moxxi
