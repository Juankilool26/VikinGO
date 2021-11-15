
#pragma once

#include <glm/vec3.hpp>
#include <manager/StateManager.hpp>



struct PauseMenu : ARCS::StateBase{
	explicit PauseMenu(bool);
	~PauseMenu();
	void update(float delta) final;
    bool alive() final {return m_alive;}

	private:
		bool gameOver;
		bool m_alive {true};
        float timeToQuitPause = 0.5;
};