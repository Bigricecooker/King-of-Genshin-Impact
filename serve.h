#pragma once
#include "Game.h"
#include "view.h"

using namespace std;

//���õ�ȫ�ֱ�����
extern player Me;//���
extern Bullet bullets[50];//�ӵ�����
extern Enemy enemies[20];//��������
extern Drops drops[20];//����������
extern multimap<int, string, greater<int>> m_Record;//��ȡ��Ϸ��ʷ����

extern IMAGE img_Login;//��¼���汳��--���˵�����Ҳ������
extern IMAGE img_Login_character;//ԭ��֮���Ǹ��ֵ�ͼ
extern IMAGE img_Registration_Victory_bk;//ע��ɹ���ͼ
extern IMAGE img_Menu_kaifatandui_bk;//�����Ŷӽ��汳��ͼ
extern IMAGE img_member[9];//С���Ա��ͷ��ͼ
extern IMAGE img_Leaderboard_bk;//���а񱳾�ͼ
extern IMAGE img_skin_bk;//Ƥ��ѡ����汳��ͼ
extern IMAGE img_play_game_bk;//��Ϸ���汳��ͼ
extern IMAGE img_Skin_selection[3];//Ƥ��ѡ����������������ѡ��ͼ
extern IMAGE img_Failure_bk;//ʧ�ܽ��汳��ͼ
extern IMAGE img_Victory_bk;//ʤ�����汳��ͼ
extern IMAGE img_Pause_the_game_bk;//��ͣ���汳��ͼ
extern IMAGE img_Drops[5];//���ֵ��ߵ�ͼ
extern IMAGE img_hp;

extern IMAGE img_bullet;//�ӵ���ͼ

extern IMAGE img_Enemy_2[4];//��Ѫ�ֵ�ͼ
extern IMAGE img_Enemy_3[4];//���ٹֵ�ͼ

extern IMAGE img_player_1_up[4];//Ƥ��1������
extern IMAGE img_player_1_down[4];//Ƥ��1������
extern IMAGE img_player_1_left[4];//Ƥ��1������
extern IMAGE img_player_1_right[4];//Ƥ��1������

extern IMAGE img_player_2_up[4];//Ƥ��2������
extern IMAGE img_player_2_down[4];//Ƥ��2������
extern IMAGE img_player_2_left[4];//Ƥ��2������
extern IMAGE img_player_2_right[4];//Ƥ��2������

extern IMAGE img_player_3_up[4];//Ƥ��3������
extern IMAGE img_player_3_down[4];//Ƥ��3������
extern IMAGE img_player_3_left[4];//Ƥ��3������
extern IMAGE img_player_3_right[4];//Ƥ��3������

extern IMAGE img_Enemy_1[4];//��ͨ�ֵ�ͼ
extern IMAGE img_Enemy_2[4];//��Ѫ�ֵ�ͼ
extern IMAGE img_Enemy_3[4];//���ٹֵ�ͼ

extern IMAGE img_music_yes;
extern IMAGE img_music_no;

extern bool is_move_w;
extern bool is_move_s;
extern bool is_move_a;
extern bool is_move_d;

extern IMAGE img_tutorial;
//��ӵ����õ�ȫ�ֱ�����
extern int flag;
extern int idx_currentanim;
extern const int player_anim_num;
extern int Spawn;
extern bool music_open;

//��������
void clearBufferOnEscape();//��հ�����Ϣ�е�ESC
void playBackgroundMusic(const char* music);//��������
void loadImgResource();//��������ͼƬ
void loadRecord();//��ȡ��Ϸ��¼
void saveRecord();//������Ϸ����
void init();//��ʼ������
void Shoot_bullets();//�����ӵ�
void Spawn_enemies();//���ɵ���
void Data_move();//��װ�ĸ����ƶ�����
void player_move();//����ƶ�
void bullets_move();//�ӵ��ƶ�
void enemies_move();//�����ƶ�
void Collision_detection();//��װ�ĸ�����ײ��⺯��
void player_whit_drops();//����������
void player_with_enemies();//��������
void enemies_with_bullets();//�ӵ������
void bullets_with_boundary();//�ӵ�����
bool is_win();//ʤ���ж�
bool is_fail();//ʧ���ж�