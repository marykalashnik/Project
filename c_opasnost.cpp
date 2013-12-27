#include "c_opasnost.h"

HGE* c_opasnost::hge = 0;

c_opasnost::c_opasnost(hgeVector position,hgeVector velocity,HTEXTURE &Texture) : Position(position), Velocity(velocity)
{
	hge = hgeCreate(HGE_VERSION);

	Sprite = new hgeAnimation(Texture,1,1,0,0,65,57);
	Sprite->SetHotSpot(32.5,28.5);
	Sprite->Play();
	
	Speed = hge->Random_Float(0.150,0.350);
}
c_opasnost::~c_opasnost()
{
	delete Sprite;

	hge->Release();
}

bool c_opasnost::Update(float delta)
{
	Velocity.y *= OPASNOST_FRICTION;
	Velocity.x *= OPASNOST_FRICTION;

	Position.y -= Velocity.y;
	Sprite->Update(delta);
	Velocity.y -= Speed;
	Sprite->GetBoundingBox(Position.x,Position.y, &BoundingBox);
	return false;
}
void c_opasnost::Render()
{
	Sprite->Render(Position.x, Position.y);
}
