#pragma once

#include <facade/Devices/IrrlichtStorage.hpp>
#include <facade/Render/FacadeRender.hpp>
#include <LeviatanGL/src/LeviatanGL.hpp>
using namespace irr;

class FacadeIrrRender : public FacadeRender {
    
    public:
        explicit FacadeIrrRender() = default;
        bool update() const override;
        bool isDeviceRunning() override;
        void dropDevice() override;
        void cleanScene() override;
        glm::vec2 getScreenSize() override;
        void createAnimatedNode(const ARCS::Entity &) override;  
        void createStaticNode(const ARCS::Entity &) override;
        void createStaticNode(const glm::vec3, const glm::vec3, const std::string_view) override;
        void createStaticNode(const int, const glm::vec3, const glm::vec3, const std::string_view) override;
        void createFPSCameraNode(const ARCS::Entity &) override;
        void setCameraTarget(const ARCS::CameraComponent &) override;
        void setCameraPosition(const ARCS::Entity &) override;
        glm::vec2 getScreenCenterPosition() const override;
        void setNoVisible(const int) override;
        void setVisible(const int) override;
        void setVisible(const int ,bool ) override;
        void setTransparent(const int) override;
        void hudInit() override;
        void menuInit() override;
        void pauseInit(bool die) override;
        void secondaryInit(int) override;
        void drawConver(int) override;
        void interInit() override;
        void drawHud(const ARCS::Entity &) override;
        void menuOptions(int) override;
        void pauseClean() override;
        void keyHUD(int) override;
        void drawStealthBar(int) override;
        void clearKeyHUD(int) override;
        void orbHUD() override;
        void interClean() override;
        void initStam() override;
        void drawStam(const ARCS::Entity &) override;
        void drawSeen(bool) override;
        void drawHudDeath() override;
        void clearHudDeath() override;
        void clearHudLife() override;
        void clearConver() override;
        void textKey(int) override;
        void clearTextKey(int) override;
        void textOrb() override;
        void clearTextOrb() override;
        void drawKill() override;
        void clearKill() override;
        void setSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back) override;
        void setTextureNode(int,std::string_view) override;
        void addSceneDirectionalNodeLight(glm::vec3, glm::vec3, glm::vec3, glm::vec3, bool) override;
        void addScenePointNodeLight(glm::vec3, float, float, float, glm::vec3, glm::vec3, glm::vec3, bool) override;
        void addSceneSpotNodeLight(glm::vec3, glm::vec3, float, float, float, glm::vec3, glm::vec3, glm::vec3, float, float, bool) override;
        void deleteLights() override;
        void setWindowTitle(std::string_view &&) override;
        void updateAnimation(int) override {};
        void doActionAnimation(int,int) override {};
        void paintChargeScreen() override {};
        
    private:
        IrrlichtStorage irrlicht { };
        //HUD Y MENUS
        gui::IGUIImage *lifeContainer           { nullptr };
        gui::IGUIImage *mainMenu                { nullptr };
        gui::IGUIImage *pause                   { nullptr };
        gui::IGUIImage *key                     { nullptr };
        gui::IGUIImage *orb                     { nullptr };
        gui::IGUIImage *inter                   { nullptr };
        gui::IGUIImage *stam                    { nullptr };
        gui::IGUIImage *death                   { nullptr };
        gui::IGUIImage *conver                  { nullptr };
        gui::IGUIImage *barStealth              { nullptr };
        gui::IGUIImage *eye                     { nullptr };
        gui::IGUIImage *textKeyPick             { nullptr };
        gui::IGUIImage *textOrbPick             { nullptr };
        gui::IGUIImage *enemyLife               { nullptr };
        gui::IGUIImage *kill                    { nullptr };
};

