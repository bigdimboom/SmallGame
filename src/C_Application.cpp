#include "C_Application.h"

namespace hctg
{

static const float k_PI = 3.1415926536f;


C_Application::C_Application(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
	, d_playerContrl(hctm::Point2f(m_ScreenWidth / 2, m_ScreenHeight / 2 + 200.0f))
{
	init();
}


C_Application::~C_Application()
{

}

void C_Application::init()
{
	// Read config file
	d_render.setView(hctm::Point2f(0.0f,0.0f), m_ScreenWidth, m_ScreenHeight);
	hcts::Scene::inst().setRenderer(&d_render);

	d_playerContrl.init();
	d_render.addDrawable(&d_playerContrl.d_sprite);
	hcts::Scene::inst().addTickable(&d_playerContrl.d_cannon);
}

void C_Application::handleInput(T_PressedKey pressedKeys)
{
	//Key processing

	if(pressedKeys & s_KeyLeft)
	{
		hcte::BasicEvent ev(hcte::EventType::PLAYER_CMD, "TURN_LEFT");
		hcte::EventBus::inst().enQueueEvent(ev);

	}

	if(pressedKeys & s_KeyRight)
	{
		hcte::BasicEvent ev(hcte::EventType::PLAYER_CMD, "TURN_RIGHT");
		hcte::EventBus::inst().enQueueEvent(ev);
	}

	if(pressedKeys & s_KeyUp)
	{
	}

	if(pressedKeys & s_KeyDown)
	{

	}

	if(pressedKeys & s_KeySpace)
	{
		hcte::BasicEvent ev(hcte::EventType::PLAYER_CMD, "FIRE");
		hcte::EventBus::inst().enQueueEvent(ev);
	}
}

void C_Application::tick()
{
	hcts::Scene::inst().tick();
}

void C_Application::draw()
{
	hcts::Scene::inst().draw();
}

} // end namespace hctg
