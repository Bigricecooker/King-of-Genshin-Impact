#pragma once
#include "Game.h"

using namespace std;






//���õ�ȫ�ֱ�����
extern player Me;//���
extern Bullet bullets[50];//�ӵ�����
extern Enemy enemies[20];//��������
extern Drops drops[20];//����������
extern multimap<int, string,greater<int>> m_Record;//��ȡ��Ϸ��ʷ����






//��ӵ����õ�ȫ�ֱ�����
extern int game_time;
extern int flag;
extern int idx_currentanim;
extern const int player_anim_num;
extern int Spawn;
extern bool music_open;

//��������
inline void putimage_alpha(int x, int y, IMAGE* img);//��ӡ͸������ͼƬ
void Login_screen();//��¼����
void Login_input(ExMessage& Login_msg, Button& LB, Button& EB, Button& RB, HWND& hwd);//��¼����
bool Login_is_successful();//�жϵ�¼�Ƿ�ɹ�����
void Registration_screen();//ע�����
void Registration_input(ExMessage& re_msg, Button su_Re);//ע������
void Registration_is_successful();//�ж�ע���Ƿ�ɹ�����
void add_Account();//��ע����˺�д�뱾������
void Menu_screen();//�˵�����
void Leaderboard();//���а����
void Developer_Profile();//������Ա����
void Skin_selection_screen();//Ƥ��ѡ�����
//-------------------------------------
void Play_the_game();//��Ϸ��ʼ
void Game_bk();//��ӡ��Ϸ����ı���
void Game_time();//��ӡ��Ϸ��ʣ��ʱ��
void Game_player();//��ӡ���
void Game_bullets();//��ӡ�ӵ�
void Game_enemies();//��ӡ����
void Game_drops();//��ӡ������
void Pause_the_game();//��ӡ��ͣ����
void Failure_screen();//��ӡ��Ϸʧ�ܽ���
void Victory_screen();//��ӡ��Ϸʤ������
