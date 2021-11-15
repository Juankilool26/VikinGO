#pragma once

#include <chrono>
#include <cstdint>



struct GameTimer {
    using clk         = std::chrono::steady_clock;
    using nano_t      = std::chrono::duration<uint64_t, std::nano>;
    using timepoint_t = std::chrono::time_point<clk, nano_t>;

    explicit GameTimer() noexcept;
    void start() noexcept;
    uint64_t elapsedNano() noexcept;
    double elapsedSecond() noexcept;
    uint64_t waitUntil_ns(uint64_t );
    int64_t currentFPS() noexcept;

private:
    timepoint_t m_start;
    uint64_t nbFrames { 0 };

};