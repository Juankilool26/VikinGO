#pragma once

#include <string_view>
#include <glm/glm.hpp>
#include <vector>


namespace ARCS {
    struct Entity;
    struct CameraComponent;
}

struct FacadeRender {
    virtual ~FacadeRender() = default;
    virtual bool update() const = 0;
    virtual bool isDeviceRunning() = 0;
    virtual void dropDevice() = 0;
    virtual void cleanScene() = 0;
    virtual glm::vec2 getScreenSize() = 0;
    virtual void createAnimatedNode(const ARCS::Entity &) = 0;
    virtual void createStaticNode(const ARCS::Entity &) = 0;
    virtual void createStaticNode(const glm::vec3, const glm::vec3, const std::string_view) = 0;
    virtual void createStaticNode(const int, const glm::vec3, const glm::vec3, const std::string_view) = 0;
    virtual void createFPSCameraNode(const ARCS::Entity &) = 0;
    virtual void setCameraTarget(const ARCS::CameraComponent &) = 0;
    virtual void setCameraPosition(const ARCS::Entity &) = 0;
    virtual glm::vec2 getScreenCenterPosition() const = 0;
    virtual void setNoVisible(const int) = 0;
    virtual void setVisible(const int) = 0;
    virtual void setVisible(const int ,bool ) = 0;
    virtual void setTransparent(const int ) = 0;
    virtual void hudInit() = 0;
    virtual void menuInit() = 0;
    virtual void pauseInit(bool die) = 0;
    virtual void secondaryInit(int) = 0;
    virtual void interInit() = 0;
    virtual void drawHud(const ARCS::Entity &) = 0;
    virtual void menuOptions(int) = 0;
    virtual void pauseClean() = 0;
    virtual void keyHUD(int) = 0;
    virtual void drawConver(int) = 0;
    virtual void drawStealthBar(int) = 0;
    virtual void clearKeyHUD(int) = 0;
    virtual void orbHUD() = 0;
    virtual void interClean() = 0;
    virtual void initStam() = 0;
    virtual void drawStam(const ARCS::Entity &) = 0;
    virtual void drawHudDeath() = 0;
    virtual void drawSeen(bool) = 0;
    virtual void clearHudDeath() = 0;
    virtual void clearHudLife() = 0;
    virtual void clearConver() = 0;
    virtual void textKey(int) = 0;
    virtual void clearTextKey(int) = 0;
    virtual void textOrb() = 0;
    virtual void clearTextOrb() = 0;
    virtual void drawKill() = 0;
    virtual void clearKill() = 0;
    virtual void setSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back) = 0;
    virtual void setTextureNode(int,std::string_view) = 0;
    virtual void addSceneDirectionalNodeLight(glm::vec3, glm::vec3, glm::vec3, glm::vec3, bool) = 0;
    virtual void addScenePointNodeLight(glm::vec3, float, float, float, glm::vec3, glm::vec3, glm::vec3, bool) = 0;
    virtual void addSceneSpotNodeLight(glm::vec3, glm::vec3, float, float, float, glm::vec3, glm::vec3, glm::vec3, float, float, bool) = 0;
    virtual void deleteLights() = 0;
    virtual void setWindowTitle(std::string_view &&) = 0;
    virtual void updateAnimation(int) = 0;
    virtual void doActionAnimation(int, int) = 0;
    virtual void paintChargeScreen() = 0;
};
