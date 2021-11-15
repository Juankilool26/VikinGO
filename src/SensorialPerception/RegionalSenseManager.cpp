#include "RegionalSenseManager.hpp"



    
RegionalSenseManager::~RegionalSenseManager(){
    clearOut();
}




void
RegionalSenseManager::check(){
    //std::vector<Notification>::iterator curNot;           
    //for (curNot = notifications.begin(); curNot != notifications.end(); ++curNot) {
    //    if(true){
    //    //  sensoryMemory->updateVision(curNot->enemie);
    //    }else{
    //        if(true){
    //    //      sensoryMemory->updateSound(curNot->enemie);
    //        }else{
    //    //
    //        }
    //    }
    //}
    //clearOut();
}





void
RegionalSenseManager::setNotification(Notification notification) {
    notifications.push_back(notification);
}





void
RegionalSenseManager::clearOut(){
    //std::vector<Notification>::iterator curNot;
    
    //for (curNot = notifications.begin(); curNot != notifications.end(); ++curNot) {
    //    notifications.erase(curNot);
    //}
    notifications.clear();
}