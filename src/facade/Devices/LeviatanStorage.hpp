#pragma once
#include <LeviatanGL/src/LeviatanGL.hpp>
#include <memory>

using namespace LVGL;


#define WIDTH   1280
#define HEIGHT  720


struct LeviatanStorage {


    // Build Leviatan
    explicit LeviatanStorage();
    ~LeviatanStorage();

    // Leviatan Graphic Engine
    inline static std::unique_ptr<LeviatanGL> device;

};