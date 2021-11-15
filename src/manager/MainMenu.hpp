
#pragma once

#include <glm/vec3.hpp>
#include <manager/StateManager.hpp>
#include <manager/GameManager.hpp>

struct MainMenu : ARCS::StateBase{
	explicit MainMenu(ARCS::StateManager& sm, ARCS::RenderSystem& rs);
	~MainMenu();
	void update(float delta) final;
    bool alive() final {return m_alive;}

	private:
		bool m_alive {true};
		int option = 1;
		float timeToChangeOption = 0.25;
		ARCS::StateManager& SM;
        // Systems
        ARCS::RenderSystem& render_sys;
};