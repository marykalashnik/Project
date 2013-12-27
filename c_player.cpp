#include "c_player.h"

HGE* c_player::hge = 0;

c_player::c_player(hgeVector position, hgeVector velocity) : Position(position), Velocity(velocity)
{
	hge = hgeCreate(HGE_VERSION);
	//грузим текстурку и задаем позиции где она будет и где будет её центр
	Texture = hge->Texture_Load("images/nikita.png");
	Sprite	= new hgeAnimation(Texture,1,1,0,0,150,172);
	Sprite->SetHotSpot(75,86.5);
	Sprite->Play();

	Speed		= 1.3;
}

c_player::~c_player()//деструктор, чё уж тут
{
	hge->Texture_Free(Texture);
	delete Sprite;
	hge->Release();
}

bool c_player::Update(float delta)//физика
{
	Velocity.x *= PLAYER_FRICTION;

	Position.x += Velocity.x;

	if(hge->Input_GetKeyState(HGEK_A) || hge->Input_GetKeyState(HGEK_LEFT)     && Position.x > 32) Velocity.x -= (Speed * M_PI) /2;
	if(hge->Input_GetKeyState(HGEK_D) || hge->Input_GetKeyState(HGEK_RIGHT)  && Position.x < 800) Velocity.x += (Speed * M_PI) /2;

	//не улетаем за пределы экрана
	if(Position.x > 800) { Position.x -= 1; Velocity.x = -Velocity.x; };
	if(Position.x < 0)   { Position.x += 1; Velocity.x = -Velocity.x; };

	Sprite->Update(delta);//обновляем через каждый промежуток дельта
	Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);//проверяем не столкнулись ли Никита и еда
	return false;
}

void c_player::Render()//рисуем
{
	Sprite->Render(Position.x,Position.y);
}
