#include "moxxi/core.hpp"

namespace moxxi
{
    Texture2D &Material::GetTexture()
    {
        return this->texture;
    }
    void Material::SetTexture(std::string name)
    {
        this->texture = ResourceManager::GetTexture(name);
    }

}