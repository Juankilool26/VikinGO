#pragma once

#include <RecordMemory/SensoryMemory.hpp>
#include <facade/Render/ManFacadeRender.hpp>


namespace ARCS {


struct GameContext;


struct ArrowSystem {
    
public:
    explicit ArrowSystem();
    ~ArrowSystem();
    bool update(GameContext &,float ) const noexcept;

private:
    ManFacadeRender* manFacadeRender { nullptr };

};


} // namespace ARCS