#ifndef C_PLAYER_H
#define C_PLAYER_H
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>

#define PLAYER_FRICTION 0.8

class c_player
{
private:
	static HGE*		hge;
	hgeVector		Position;
	hgeVector		Velocity;
	HTEXTURE		Texture;
	hgeAnimation*	Sprite;
	hgeRect			BoundingBox;
	float			Speed;
	
public:
	c_player(hgeVector Position, hgeVector Velocity);
	~c_player();

	bool Update(float delta);
	void Render();

	void SetVelocity(hgeVector velocity) {Velocity = velocity;};
	void SetPosition(hgeVector position){Position = position;};
	hgeRect	GetBoundingBox() {return BoundingBox;};
	hgeVector GetPosition(){return Position;};
};

#endif
