// event_bus.cpp
#include "event_bus.h"

namespace hcte
{

EventBus::EventBus()
{
	d_qSize = EVENT_QUEUE_SIZE;
}

//ACCESSORS
EventBus& EventBus::inst()
{
	static EventBus inst;
	return inst;
}

// MUTATORS
void EventBus::setQueueSize(unsigned int size)
{
	d_qSize = size;
}

// MEMBER FUNCTIONDS
bool EventBus::enQueueEvent(const IEvent & ev)
{
	if (d_qSize == d_eventQ.size())
	{
		// this makes d_eventQ fixed size.
		return false;
	}
	d_eventQ.push_back(&ev);
	return true;
}

bool EventBus::deQueueEvent(const IEvent & ev)
{
	unsigned int size = d_eventQ.size();
	bool ret = false;
	for (auto iter = d_eventQ.begin(); iter != d_eventQ.end(); ++iter)
	{
		if ((*iter)->name() == ev.name()) 
		{
			d_eventQ.erase(iter);
			ret = true;
		}
		// if I implement type() in IEvent in stead of comparing names,
		// then it would compare numbers, faster than comparing strings.
	}
	return ret;
}

void EventBus::registerListener(const IEvent & ev,
					  EventListenerCallbacksPtr listener)
{
	d_evDispatcher.add(ev.name(), listener);
}

void EventBus::deRegisterListener(const IEvent & ev,
						EventListenerCallbacksPtr listener)
{
	d_evDispatcher.remove(ev.name(), listener);
}

void EventBus::triggerEvent(const IEvent & ev)
{
	d_evDispatcher.dispatch(ev);
}

void EventBus::preTick()
{
}

void EventBus::tick()
{
	unsigned int size = d_eventQ.size();
	for (unsigned int i = 0; i < size; ++i)
	{
		d_evDispatcher.dispatch(*(d_eventQ[i]));
	}
	d_eventQ.clear();
}

#ifdef DEBUG

class BasicEvent : public sgde::IEvent
{

public:
	std::string d_name;
	sgde::EventType d_type;

	BasicEvent()
	{
		d_name = "hahah";
		d_type = 123231514; // fake guid
	}
	~BasicEvent(){}
	const sgde::EventType & type() const
	{
		return d_type;
	}

	const std::string name() const
	{
		return d_name;
	}
};

void unitTest() // test for control and sprite interaction
{
	BasicEvent be;
	be.d_name = "beHeee";
	std::string str = "wowowowow";
	auto func = ([&](const sgde::IEvent & ev) {  std::cout << str + "****" + ev.name() << std::endl; });
	std::function<void(const sgde::IEvent &)> callback = std::bind(func, be);
	sgde::EventBus::inst().registerListener(be, &callback);

	sgdr::Renderer render;
	sgds::Scene::inst().setRenderer(&render);
	sgdr::RenderableSprite sprite2D;
	render.setupWindow("Hello World", 800, 600);
	bool ret = render.loadTexture("test", "mario-jump.png");

	if (ret == false)
	{
		return EXIT_FAILURE;
	}

	render.addSprite(&sprite2D);

	sprite2D.sprite().setTexture(render.getTexture("test"));
	sgds::Scene::inst().addTickable(&sgdi::Input::inst());

	while (render.isActive())
	{
		sgdi::Input::inst().preTick();

		if (sgdi::Input::inst().wasPressed(sgdi::InputType::A_KEY))
		{
			sgde::EventBus::inst().enQueueEvent(be);
		}
		if (sgdi::Input::inst().wasPressed(sgdi::InputType::RETURN_KEY))
		{
			sgde::EventBus::inst().postTick();
		}

		sgds::Scene::inst().tick();
	}
}
#endif

} // end namespace sgde