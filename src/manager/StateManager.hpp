#pragma once

#include <stack>
#include <memory>
#include <util/Timer.hpp>



namespace ARCS {



struct StateBase {
    virtual void update(float) = 0;
    virtual bool alive() = 0;
    virtual ~StateBase() = default;
};

struct StateManager{
    explicit StateManager();

    template <typename State, typename... Ts>
    void pushState(Ts&&... args) {
        static_assert(std::is_base_of<StateBase,State>::value);
        m_States.push( std::make_unique<State>(std::forward<decltype(args)>(args)... ));
    }

    void update(float delta);
    bool alive();

private:
    std::stack<std::unique_ptr<StateBase>> m_States;
    GameTimer fpsTimer { };
};



} // namespace ARCS