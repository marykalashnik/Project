#include "c_buter.h"

HGE* c_buter::hge = 0;

c_buter::c_buter(hgeVector position,hgeVector velocity,HTEXTURE &Texture) : Position(position), Velocity(velocity)
{
	hge = hgeCreate(HGE_VERSION);

	Sprite = new hgeAnimation(Texture,1,1,0,0,62,31);
	Sprite->SetHotSpot(31,15.5);
	Sprite->Play();
	
	Speed = hge->Random_Float(0.150,0.350);
}

c_buter::~c_buter()
{
	delete Sprite;

	hge->Release();
}

bool c_buter::Update(float delta)
{
	Velocity.y *= BUTER_FRICTION;
	Velocity.x *= BUTER_FRICTION;
	Position.y -= Velocity.y;
	Sprite->Update(delta);
	Velocity.y -= Speed;
	Sprite->GetBoundingBox(Position.x,Position.y, &BoundingBox);
	return false;
}
void c_buter::Render()
{
	Sprite->Render(Position.x, Position.y);
}
