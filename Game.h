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
	�������:
		uid��ʾ��ҵ��˺�
		password��ʾ����
		name��ʾ��ҵ�����
		skin��ʾ��ҵ�ǰ��Ƥ��
		x,y��ʾ��ҵ�����
		size��ʾ��ҵİ뾶
		hp��ʾ��ҵ�Ѫ��
		is_live��ʾ����Ƿ���
		cd��ʾ��ҵĹ����ٶ�
		speed��ʾ��ҵ��ƶ��ٶ�
		bullet_type��ʾ��ҵ��ӵ���ʽ
		score��ʾ��ҵĵ÷�
*/
struct player {
	string uid;
	string password;
	string name;
	IMAGE skin;
	int skin_number;
	int direct;//��ҳ���
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
	�ӵ�����:
		x,y��ʾ�ӵ�������
		size��ʾ�ӵ��İ뾶
		speed��ʾ�ӵ����ٶ�
		attack��ʾ�ӵ����˺�
		angle��ʾ�ӵ��ĽǶ�,С�����ϵ�8����
		is_live��ʾ�ӵ��Ƿ񻹴���
		type��ʾ�ӵ�������
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
	��������:
		skin��ʾ���˵�Ƥ��
		x,y��ʾ���˵�����
		size����˵İ뾶
		speed��ʾ���˵��ٶ�
		hp��ʾ���˵�Ѫ��
		attack��ʾ���˵���ײ�˺�
		is_live��ʾ�����Ƿ���
		type��ʾ���˵�����
		score��ʾ��ɱ�õ���ʱ�ĵ÷�
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
	skin��ʾ�õ������Ƥ��
	x,y��ʾ�õ����������
	size��ʾ�õ�����İ뾶;
	is_live��ʾ�õ������Ƿ����
	type��ʾ�õ����������
*/
struct Drops {
	IMAGE skin;
	int x, y;
	int size;
	bool is_live;
	int type;
};


//��ť�ṹ��
struct Button {
	int B_x;//���Ͻ�x����
	int B_y;//���Ͻ�y����
	int B_width;//��ť��
	int B_height;//��ť��

	Button(int x, int y, int width, int height) {
		B_x = x;
		B_y = y;
		B_width = width;
		B_height = height;
	}

	void Creat_Button(string text, int t_height) {

		//���ð�ť��ʽ
		setfillcolor(WHITE);
		setlinecolor(RGB(100, 77, 77));

		//���ƾ���
		fillrectangle(B_x, B_y, B_x + B_width, B_y + B_height);

		//������������
		//��������Ϊ͸��
		setbkmode(TRANSPARENT);
		//������ʽ
		settextcolor(BLACK);
		settextstyle(t_height, 0, "����");

		//��ӡ����
		int t_x = B_x + B_width / 2 - textwidth(text.c_str()) / 2;
		int t_y = B_y + B_height / 2 - textheight(text.c_str()) / 2;


		//��ӡ
		outtextxy(t_x, t_y, text.c_str());

	}

};



