// cullet_controller.h
#pragma once
#include "../engine/gameplay/acontroller.h"
#include "../game/bullet_sprite.h"
#include "../engine/gameplay/collidable_pawn.h"

namespace mygame
{

class BulletController : public hctg::AController
{
private:


public:
	BulletController();

	virtual ~BulletController();

	virtual void preTick() override;
	virtual void tick() override;
	virtual void postTick() override;

	//const std::string kBulletHit = "BULLET_HIT";

};

} //end namespace mygame