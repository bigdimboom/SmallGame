#ifndef TEST_C_APPLICATION_H
#define TEST_C_APPLICATION_H

#include "game/clock_sprite.h"
#include "game/cannon_sprite.h"
#include "engine/rendering/renderer.h"
#include "engine/events/event_bus.h"
#include "engine/scene/scene.h"
#include <iostream>

using namespace hctr;
using namespace hctm;

namespace hctg
{

class C_Application
{
public:

	typedef unsigned int T_PressedKey;

	C_Application(int screenWidth, int screenHeight);
	~C_Application();

	// Tick is called on fix framerate (50fps)
	void init();
	void handleInput(T_PressedKey pressedKeys);
	void tick();
	void draw();

	static const T_PressedKey s_KeyLeft = 0x01;
	static const T_PressedKey s_KeyUp = 0x02;
	static const T_PressedKey s_KeyRight = 0x04;
	static const T_PressedKey s_KeyDown = 0x08;
	static const T_PressedKey s_KeySpace = 0x10;

private:

	const int	m_ScreenWidth;
	const int	m_ScreenHeight;

	// Members for sample tick

	hctr::Renderer d_render;

	mygame::ClockSprite d_clock;
	mygame::CannonSprite d_cann;
};

} // end namespace hctg

#endif // #ifndef TEST_C_APPLICATION_H
