#include "LeviatanStorage.hpp"


LeviatanStorage::LeviatanStorage()
{
    if(device){
        return;
    }
    device = std::make_unique<LeviatanGL>(WIDTH, HEIGHT, "VikinGO - 60 FPS");
}
LeviatanStorage::~LeviatanStorage()
{
}