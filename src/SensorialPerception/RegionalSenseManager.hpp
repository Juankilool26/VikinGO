#pragma once 
#include <vector>
#include "Notification.hpp"
#include <system/CollisionSystem.hpp>

class RegionalSenseManager {
    
public:
    //Reserve del vector de notificaciones = numero de enemmigos
    RegionalSenseManager() = default; 
    ~RegionalSenseManager();
    void check();
    void setNotification(Notification notification);

    std::vector<Notification> notifications;

private:
    void clearOut();
};


