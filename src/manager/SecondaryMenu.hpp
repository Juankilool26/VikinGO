
#pragma once

#include <glm/vec3.hpp>
#include <manager/StateManager.hpp>
#include <manager/GameManager.hpp>

struct SecondaryMenu : ARCS::StateBase{
	explicit SecondaryMenu(ARCS::StateManager&, ARCS::RenderSystem&,int);
	~SecondaryMenu();
	void update(float delta) final;
    bool alive() final {return m_alive;}

	private:
		bool m_alive {true};
		int option = 1;
		int gender = 4;
		float timeToChangeOption = 0.25;
		ARCS::StateManager& SM;
        ARCS::RenderSystem &render_sys;
            
};