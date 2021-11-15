#include "VisualDepuration.hpp"
#include "ID.hpp"


namespace ARCS {



VisualDepurationComponent::VisualDepurationComponent(int entID)
    : Component(entID)
{
    visualID = {
            ID::getNewDepurationID()
        ,   ID::getNewDepurationID()
        ,   ID::getNewDepurationID()
        ,   ID::getNewDepurationID()
    };
}


VisualDepurationComponent::ArrayObj
VisualDepurationComponent::visualObj = {
        "media/models/arma.obj"
    ,   "media/models/indicador.obj"
    ,   "media/models/oido.obj"
    ,   "media/models/vista.obj"
};


VisualDepurationComponent::ArrayPos
VisualDepurationComponent::visualPos = {
        glm::vec3(0, 0, 0)
    ,   glm::vec3(0, 2.2, 0)
    ,   glm::vec3(0, -1.4, 0)
    ,   glm::vec3(0, 0, 0)
};



} // namespace ARCS