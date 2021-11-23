#include "moxxi/core.hpp"

using namespace moxxi;

class Player : public GameObject
{
private:
    unsigned int health = 100;
public:
    Player();
    void Update();
    void Move();
    void TakeDamage(unsigned int damage);
    void Shoot(unsigned int damage);
    void Render(SpriteRenderer &renderer);
};
