
/////////////////////////////// COMMAND COMPILATION ///////////////////////////////
// 						alias m="make -j9 && ./VikinGO"							 //
// 				alias v="make cleanall && make -j9 && ./VikinGO"				 //
///////////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <util/Timer.hpp>
#include <manager/MainMenu.hpp>


constexpr uint64_t FPS  { 60			   };
constexpr uint64_t NSPF { 1000000000UL/FPS };


int main() {


	// Game States
	ARCS::StateManager States;
	ARCS::RenderSystem RenderSys;
	States.pushState<MainMenu>(States, RenderSys);

	// Frame Rate Settings
	GameTimer timer { };
	auto deltaTime { 1.0/FPS };

	while (States.alive())
	{
		States.update(deltaTime);
		timer.waitUntil_ns(NSPF);
		deltaTime = timer.elapsedSecond();
		timer.start();
	}

	return 0;
}