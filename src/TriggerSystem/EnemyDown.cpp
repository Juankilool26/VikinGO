#include "EnemyDown.hpp"



EnemyDown::EnemyDown(int t,int p)
    : LimitedTrigger(t,p)
{}




bool
EnemyDown::Try(ARCS::GameContext& gc,ARCS::CollisionSystem& cs, float delta){
    auto* player = gc.getEntityById(gc.getInputComponents()[0].getEntityID());
    if(intersects(cs,gc.getEntityById(entID)->pos->position ,*player)){
        //TODO: Aqui hacer lo que tiene que hacer
        //std::printf("The enemy has view an enemy down\n");
        lifeTime = 0;
    }
    return false;
    
}