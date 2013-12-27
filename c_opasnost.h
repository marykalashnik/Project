#ifndef C_OPASNOST_H
#define C_OPASNOST_H
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>
#include <hgerect.h>

#define OPASNOST_FRICTION 0.95

class c_opasnost
{public:
//private:
	static HGE*		hge;
	hgeVector		Position;
	hgeVector		Velocity;
	HTEXTURE		Texture;
	hgeAnimation*	Sprite;
	hgeRect			BoundingBox;
	float			Speed;
	bool			exists;

//public:
	c_opasnost(hgeVector Position, hgeVector Velocity, HTEXTURE &Texture);
	~c_opasnost();
	
	bool		Update(float delta);
	void		Render();
	float		GetSpeed(){return Speed;};
	void		SetSpeed(float speed){Speed = speed;};
	hgeRect		GetBoundingBox(){return BoundingBox;};
	hgeVector	GetPosition(){return Position;};
};

#endif 
