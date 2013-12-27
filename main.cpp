#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <list>
#include <hgefont.h>
#include <time.h>
#include <hgeanim.h>
#include <hgefont.h>
#include <hgerect.h>
#include <cstring>
#include <hgegui.h>
#include <hgeguictrls.h>
#include "c_player.h"
#include "c_buter.h"
#include "c_opasnost.h"
using namespace std;

HGE* hge = NULL;
int oops = 0;
int count = 0;//счет
int propusk = 0;//пропущеные бутеры
//Buter&Opasnost/////////////////////////////////////////////////
std::list<c_buter*> Buters;
std::list<c_opasnost*> Opasnosts;
HTEXTURE	g_tButer[3] = {0};
HTEXTURE	g_tOpasnost = 0;
//Player///////////////////////////////////////////////
c_player*   Player1 = NULL;

//Fresh////////////////////////////////////////////////
HTEXTURE	g_tBackground = 0;
hgeSprite*  g_sBackground = NULL;

hgeVector   g_vBGPosition = hgeVector(0,0);
hgeFont*	fnt;// шрифт

HTEXTURE	g_tOops	  = 0;
hgeSprite*  g_sOops   = NULL;

HTEXTURE	g_tFinish = 0;
hgeSprite*	g_sFinish = NULL;

HTEXTURE	g_tLearn  = 0;
hgeSprite*  g_sLearn  = NULL;
hgeGUI *gui;
hgeGUIButton* start=0;
HTEXTURE tstart=0;
HTEXTURE cur=0;
hgeSprite *cursor = NULL;

//HEFFECT snd;
//HEFFECT back;
float delta = 0;
bool pause =0;
bool checker_menu=true;
bool MenuUpgrade(float time);
bool FrameFunc()
{
	//snd = hge->Effect_PlayEx(back,50,0,14.0,true);
	delta = hge->Timer_GetDelta();
	if(checker_menu)	
	{
		gui->Update(delta);
		if(MenuUpgrade(delta))return true;
	}
	else
	{
		if (hge->Input_GetKeyState(HGEK_P))pause=1;
		if (hge->Input_GetKeyState(HGEK_S))pause=0;
		if(!pause)
		{
		if(count<=5)
		{
			if(Buters.size()<1)//к-во бутербродов
			{
				c_buter* Buter = new c_buter(hgeVector(hge->Random_Int(50,750),350),hgeVector(2,25), g_tButer[hge->Random_Int(0,2)]);//новый бутер
				Buters.push_back(Buter);//добавляет в конец
			}
		}
		if(count>5&&count<=50)
		{
			if(Buters.size()<2)//к-во бутербродов
			{
				c_buter* Buter = new c_buter(hgeVector(hge->Random_Int(50,750),350),hgeVector(2,25), g_tButer[hge->Random_Int(0,2)]);//новый бутер
				Buters.push_back(Buter);//добавляет в конец
			}
		}
		if(count>50&&count<=500)
		{
			if(Buters.size()<3)//к-во бутербродов
			{
				c_buter* Buter = new c_buter(hgeVector(hge->Random_Int(50,750),350),hgeVector(2,25), g_tButer[hge->Random_Int(0,2)]);//новый бутер
				Buters.push_back(Buter);//добавляет в конец
			}
		}
		if(count>500)
		{
			if(Buters.size()<4)//к-во бутербродов
			{
				c_buter* Buter = new c_buter(hgeVector(hge->Random_Int(50,750),350),hgeVector(2,25), g_tButer[hge->Random_Int(0,2)]);//новый бутер
				Buters.push_back(Buter);//добавляет в конец
			}
		}
		if(count==10||count == 50||count==100||count==150||count==200||count==250||count==300)
		{
			if(Opasnosts.size()<1)
			{
				c_opasnost* Opasnost = new c_opasnost(hgeVector(hge->Random_Int(50,750),350),hgeVector(2,25), g_tOpasnost);
				Opasnosts.push_back(Opasnost);
			}
		}
		for(std::list<c_buter*>::iterator i = Buters.begin(); i!= Buters.end(); )
		{
			if((*i)->GetPosition().y > 580 || (*i)->GetPosition().x > 780 || (*i)->GetPosition().x < 20)//если за пределами экрана
			{
				delete (*i);//удаляем бутер и сдвигаем список
				i = Buters.erase(i);
				propusk+=1;
				count-=1;
			}
			else
			{
				(*i)->Update(delta);
				i++;
			}
	
		}
		for(std::list<c_opasnost*>::iterator i = Opasnosts.begin(); i!= Opasnosts.end(); )
		{
		if((*i)->GetPosition().y > 580 || (*i)->GetPosition().x > 780 || (*i)->GetPosition().x < 20)//если за пределами экрана
		{
			delete (*i);//удаляем и сдвигаем список
			i = Opasnosts.erase(i);
		}
		else
		{
			(*i)->Update(delta);
			i++;
		}
	
	}
	Player1->Update(delta);

	//Buterbrod & Nikita
	for( std::list<c_buter*>::iterator i = Buters.begin(); i!= Buters.end(); )
	{
		if((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))//если бокс бутера и бокс игрока столкнулись
		{
			delete(*i);//удаляем бутер, сдвигаем их и прибавляем счетчик
			i = Buters.erase(i);
			count+=1;
		}
		else 
		{
			i++;
		}
	}
	for( std::list<c_opasnost*>::iterator i = Opasnosts.begin(); i!= Opasnosts.end(); )
	{
		if((*i)->GetBoundingBox().Intersect(&Player1->GetBoundingBox()))//если бокс опасности и бокс игрока столкнулись
		{
			delete(*i);//удаляем опасность, сдвигаем их и прибавляем счетчик
			i = Opasnosts.erase(i);
			oops+=1;
		}
		else 
		{
			i++;
		}
	}
	
	if(propusk>30)
	{
		if(hge->Input_GetKeyState(HGEK_1)) return true;
	}
	if(oops>3)
	{
		
		if(hge->Input_GetKeyState(HGEK_1)) return true;
	}
	if(hge->Input_GetKeyState(HGEK_ESCAPE))return true;//условие выхода из игры
	}
	}
	return false;
}

bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);//0 - black (ARBG)
	//g_sLearn->Render(g_vBGPosition.x,g_vBGPosition.y);
	
	//g_sBackground->Render(g_vBGPosition.x,g_vBGPosition.y);//рисуем фон
	
		//gui->Render();
	//Player1->Render();//рисуем игрока
	if(checker_menu)
	{
		g_sLearn->Render(g_vBGPosition.x,g_vBGPosition.y);
		gui->Render();
		//fnt->SetColor(ARGB(255,255,255,255));
		fnt->printf(5,5,HGETEXT_LEFT,"Press P to pause an to show tutorial, press S finish pause");
	}
	else
	{
		g_sBackground->Render(g_vBGPosition.x,g_vBGPosition.y);//рисуем фон
		Player1->Render();//рисуем игрока
	if(pause==1)
	{
			g_sLearn->Render(g_vBGPosition.x,g_vBGPosition.y);
			//fnt->printf(400,300,HGETEXT_CENTER,"PAUSE");
			fnt->printf(5, 5, HGETEXT_LEFT, "Score:%d ", count);//выводим счетчик
			fnt->printf(5, 30, HGETEXT_LEFT, "Lost:%d", propusk);
			fnt->printf(5, 55, HGETEXT_LEFT, "Tomato:%d", oops);
			
	}
	else
	{
		for(std::list<c_buter*>::iterator i = Buters.begin(); i!= Buters.end(); i++)//проходимся по списку и рисуем будеты
		{
			(*i)->Render();
		}
		for(std::list<c_opasnost*>::iterator i = Opasnosts.begin();i!= Opasnosts.end();i++)
		{
			(*i)->Render();
		}
		fnt->printf(5, 5, HGETEXT_LEFT, "Score:%d ", count);//выводим счетчик
		fnt->printf(5, 30, HGETEXT_LEFT, "Lost:%d", propusk);
		fnt->printf(5, 55, HGETEXT_LEFT, "Tomato:%d", oops);
		fnt->printf(795, 5, HGETEXT_RIGHT, "PRESS 'P' TO PAUSE");
		if(propusk>30)
		{
		
			g_sFinish->Render(g_vBGPosition.x,g_vBGPosition.y);
		}
		if(oops>3)
		{
			g_sOops->Render(g_vBGPosition.x,g_vBGPosition.y);
		}
	}
	}
		hge->Gfx_EndScene();
		return false;
	
}


int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{

	hge = hgeCreate(HGE_VERSION);//Создает объект HGE, если требуется, и возвращает указатель на интерфейс HGE

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);//функция которая отвечает за фреймы
	hge->System_SetState(HGE_RENDERFUNC,RenderFunc);//за вывод на экран
	hge->System_SetState(HGE_WINDOWED, true);//оконный режим вкл/выкл
	hge->System_SetState(HGE_USESOUND, false);//не использовать библеотеку басс
	hge->System_SetState(HGE_FPS, HGEFPS_VSYNC);// частота, с которой будет вызываться функция кадра.
												//HGEFPS_VSYNC - частота синхронизируется с частотой обновления.
	hge->System_SetState(HGE_TITLE,"Nikita & Food");

	if(hge->System_Initiate())//Если все инициализировано правильно
	{	
		tstart=hge->Texture_Load("images/start.png");
		cur=hge->Texture_Load("images/kursor.png");
		cursor=new hgeSprite(cur,0,0,19,24);
		//hgeGUIButton
		start = new hgeGUIButton(1,240,430,204,197,tstart,0,0);
		
		g_tLearn		= hge->Texture_Load("images/learn.jpg");
		g_sLearn		= new hgeSprite(g_tLearn,0,0,800,600);
		g_tBackground   = hge->Texture_Load("images/freshline.jpg");
		g_sBackground   = new hgeSprite(g_tBackground,0,0,800,600);
		g_vBGPosition   = hgeVector(0, 0);
		g_tOops			= hge->Texture_Load("images/oops.bmp");
		g_sOops			= new hgeSprite(g_tOops,0,0,800,600);
		g_tFinish		= hge->Texture_Load("images/finish.png");
		g_sFinish		= new hgeSprite(g_tFinish,0,0,800,600);
		
		Player1			= new c_player(hgeVector(400,550),hgeVector(5,0));

		g_tButer[0]		= hge->Texture_Load("images/buter.png");
		g_tButer[1]		= hge->Texture_Load("images/buter2.png");
		g_tButer[2]		= hge->Texture_Load("images/buter3.png");
		g_tOpasnost		= hge->Texture_Load("images/opasnost.png");
		fnt				= new hgeFont("images/font1.fnt");//грузим шрифт

		gui=new hgeGUI();
		gui->AddCtrl(start);
		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(cursor);
		gui->SetFocus(1);
		gui->Enter();

		//fntpause=new hgeFont("font1.fnt");
		//file = fopen("best.txt","a+t");
		//char co=(char)count;
		//fputc(co,file);

		hge->System_Start();//То потекла моча по трубам
		//Выкидываем мусор
		hge->Texture_Free(g_tBackground);
		hge->Texture_Free(g_tFinish);
		hge->Texture_Free(g_tLearn);
		hge->Texture_Free(g_tOops);
		for(int i=0;i<3;i++)
		{
			hge->Texture_Free(g_tButer[i]);
		}
		hge->Texture_Free(g_tOpasnost);
		delete g_sLearn;
		delete g_sBackground;
		delete Player1;
		delete gui;
		for(std::list<c_buter*>::iterator i = Buters.begin();i != Buters.end();)
		{
			delete(*i);
			i = Buters.erase(i);
		}
		for(std::list<c_opasnost*>::iterator i = Opasnosts.begin();i!= Opasnosts.end();)
		{
			delete(*i);
			i = Opasnosts.erase(i);
		}
	}
	else//иначе выдаем сообщение об ошибке, определяемое HGE
	{
		 MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	//Если клавиша ESC была нажата, или окно было закрыто, то цикл игры завершится. Освобождаем все занятые ресурсы и HGE интерфейс
	hge->System_Shutdown();//Восстанавливает видеорежим, освобождает все выделенные ресурсы и разрушает окно приложения
	hge->Release();//Ложимся спать

	return 0;
}
bool MenuUpgrade(float time)
{
	gui->Update(time);
	if(start->GetState()||hge->Input_GetKeyState(HGEK_ENTER))checker_menu=false;
	return false;
}
