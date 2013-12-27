#ifndef C_BUTER_H
#define C_BUTER_H
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>
#include <hgerect.h>

#define BUTER_FRICTION 0.95

class c_buter
{
public:
//private:
	static			HGE*hge;
	hgeVector		Position;
	hgeVector		Velocity;
	HTEXTURE		Texture;
	hgeAnimation*	Sprite;
	hgeRect			BoundingBox;
	float			Speed;
	bool			exists;

//public:
	c_buter(hgeVector Position, hgeVector Velocity, HTEXTURE &Texture);
	~c_buter();
	
	bool		Update(float delta);
	void		Render();
	float		GetSpeed(){return Speed;};
	void		SetSpeed(float bspeed){Speed = bspeed;};
	hgeRect		GetBoundingBox(){return BoundingBox;};
	hgeVector	GetPosition(){return Position;};	
};

#endif 
