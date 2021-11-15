#pragma once
#include <irrlicht/src/irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



// struct mouse info
struct SMouseState {
	core::position2di Position;
	bool LeftButtonDown;

	SMouseState() : LeftButtonDown { false } { }
};



// Event Receiver
struct IrrEventReceiver : public IEventReceiver
{

public:

	explicit IrrEventReceiver();
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event);

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;

	bool IsLeftMouseDown() const;
	const core::vector2di& getScreenMousePosition() const;

private:

	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	SMouseState MouseState { };

};
