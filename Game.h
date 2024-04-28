#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <easyx.h>
#include <graphics.h>
#include <time.h>
#include <mmsystem.h>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <cstring>
#pragma comment(lib, "winmm.lib")
#pragma comment( lib, "MSIMG32.LIB")
using namespace std;



/*
	玩家数据:
		uid表示玩家的账号
		password表示密码
		name表示玩家的名字
		skin表示玩家当前的皮肤
		x,y表示玩家的坐标
		size表示玩家的半径
		hp表示玩家的血量
		is_live表示玩家是否存活
		cd表示玩家的攻击速度
		speed表示玩家的移动速度
		bullet_type表示玩家的子弹样式
		score表示玩家的得分
*/
struct player {
	string uid;
	string password;
	string name;
	IMAGE skin;
	int skin_number;
	int direct;//玩家朝向
	int x, y;
	int size;
	int hp;
	bool is_live;
	int cd;
	int speed;
	int bullet_type;
	int score;
	int luck;
};


/*
	子弹数据:
		x,y表示子弹的坐标
		size表示子弹的半径
		speed表示子弹的速度
		attack表示子弹的伤害
		angle表示子弹的角度,小键盘上的8个数
		is_live表示子弹是否还存在
		type表示子弹的类型
*/
struct Bullet {
	int x, y;
	int size;
	int speed;
	int attack;
	int angle;
	bool is_live;
};

/*
	敌人数据:
		skin表示敌人的皮肤
		x,y表示敌人的坐标
		size表敌人的半径
		speed表示敌人的速度
		hp表示敌人的血量
		attack表示敌人的碰撞伤害
		is_live表示敌人是否存活
		type表示敌人的类型
		score表示击杀该敌人时的得分
*/
struct Enemy {
	int x, y;
	int size;
	int speed;
	int hp;
	int attack;
	bool is_live;
	int type;
	int score;
	int drop;
};


/*
	skin表示该掉落物的皮肤
	x,y表示该掉落物的坐标
	size表示该掉落物的半径;
	is_live表示该掉落物是否存在
	type表示该掉落物的类型
*/
struct Drops {
	IMAGE skin;
	int x, y;
	int size;
	bool is_live;
	int type;
};


//按钮结构体
struct Button {
	int B_x;//左上角x坐标
	int B_y;//左上角y坐标
	int B_width;//按钮宽
	int B_height;//按钮高

	Button(int x, int y, int width, int height) {
		B_x = x;
		B_y = y;
		B_width = width;
		B_height = height;
	}

	void Creat_Button(string text, int t_height) {

		//设置按钮样式
		setfillcolor(WHITE);
		setlinecolor(RGB(100, 77, 77));

		//绘制矩形
		fillrectangle(B_x, B_y, B_x + B_width, B_y + B_height);

		//调整文字字样
		//背景设置为透明
		setbkmode(TRANSPARENT);
		//字体样式
		settextcolor(BLACK);
		settextstyle(t_height, 0, "楷体");

		//打印文字
		int t_x = B_x + B_width / 2 - textwidth(text.c_str()) / 2;
		int t_y = B_y + B_height / 2 - textheight(text.c_str()) / 2;


		//打印
		outtextxy(t_x, t_y, text.c_str());

	}

};



