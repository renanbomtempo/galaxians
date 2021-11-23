#ifndef PLAYER_H
#define PLAYER_H

#include <moxxi/gameobject.hpp>


namespace Game{

class Player: public moxxi::GameObject {
public:
    unsigned int life;
    
    Player(){
        this->entity_type = ENTITY_TYPE_PLAYER;
    };
};

}

#endif