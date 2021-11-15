#pragma once

#include <facade/Render/ManFacadeRender.hpp>


namespace ARCS {

    struct GameContext;

    class RenderSystem {
        
        public:
            explicit RenderSystem();
            ~RenderSystem();
            bool update(GameContext &,float ,bool );
            bool isDeviceRunning();
            void dropDevice();
            void cleanScene();
            void changePrivateTime() { timetoChangeFrame = 0; }
            void incrementDeltatime(float deltatime) { timetoChangeFrame += deltatime; }
            
        private:
            ManFacadeRender* manFacadeRender { 0 };
            float timetoChangeFrame = 0.0f;
            inline static constexpr float kMaxAnim { 0.08f };
        };

} // namespace ARCS
