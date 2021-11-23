#include "moxxi/core.hpp"

using namespace moxxi;
enum GameState {
        GAME_PAUSE,
        GAME_VICTORY,
        GAME_LOST
    };
class Game
{
public:
    
    Game() {}
    void Init();
    void ProcessInput();

private:
    GameState state;
};