#include "Timer.hpp"
#include <thread>




GameTimer::GameTimer() noexcept {
    start();
}



void
GameTimer::start() noexcept {
    m_start = clk::now();
}



uint64_t
GameTimer::elapsedNano() noexcept {
    auto nsPassed { clk::now() - m_start };
    return nsPassed.count();
}



double
GameTimer::elapsedSecond() noexcept {
    return ( elapsedNano() / 1000000000.0 );
}



uint64_t
GameTimer::waitUntil_ns(uint64_t to_ns) {
    uint64_t towait { 0 };
    if ( elapsedNano() < to_ns ) {
        towait = to_ns - elapsedNano();
        std::this_thread::sleep_for( nano_t{towait} );
    }
    return towait;
}




int64_t
GameTimer::currentFPS() noexcept {
    int64_t fps { -1 };
    auto tElapsed { elapsedSecond() };

    ++nbFrames;
    if ( tElapsed >= 1.0 ) {
        fps = static_cast<double>(nbFrames) / 1.0;
        nbFrames = 0;
        start();
    }

    return fps;
}