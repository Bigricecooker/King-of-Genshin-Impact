#include "Game.h"
#include "view.h"
#include "serve.h"
using namespace std;


//����putimage()����ʹ��--����ͼ������putimage()
inline void putimage_alpha(int x, int y, IMAGE* img);


//ͼƬ����
IMAGE img_Login;//��¼���汳��--���˵�����Ҳ������
IMAGE img_Login_character;//ԭ��֮���Ǹ��ֵ�ͼ
IMAGE img_Registration_Victory_bk;//ע��ɹ���ͼ
IMAGE img_Menu_kaifatandui_bk;//�����Ŷӽ��汳��ͼ
IMAGE img_member[9];//С���Ա��ͷ��ͼ
IMAGE img_Leaderboard_bk;//���а񱳾�ͼ
IMAGE img_skin_bk;//Ƥ��ѡ����汳��ͼ
IMAGE img_Skin_selection[3];//Ƥ��ѡ����������������ѡ��ͼ
IMAGE img_play_game_bk;//��Ϸ���汳��ͼ
IMAGE img_Failure_bk;//ʧ�ܽ��汳��ͼ
IMAGE img_Victory_bk;//ʤ�����汳��ͼ
IMAGE img_Pause_the_game_bk;//��ͣ���汳��ͼ
IMAGE img_Drops[5];//���ֵ��ߵ�ͼ
IMAGE img_hp;//Ѫ��
IMAGE img_bullet;//�ӵ���ͼ

IMAGE img_Enemy_1[4];//��ͨ�ֵ�ͼ
IMAGE img_Enemy_2[4];//��Ѫ�ֵ�ͼ
IMAGE img_Enemy_3[4];//���ٹֵ�ͼ

IMAGE img_player_1_up[4];//Ƥ��1������
IMAGE img_player_1_down[4];//Ƥ��1������
IMAGE img_player_1_left[4];//Ƥ��1������
IMAGE img_player_1_right[4];//Ƥ��1������

IMAGE img_player_2_up[4];//Ƥ��2������
IMAGE img_player_2_down[4];//Ƥ��2������
IMAGE img_player_2_left[4];//Ƥ��2������
IMAGE img_player_2_right[4];//Ƥ��2������

IMAGE img_player_3_up[4];//Ƥ��3������
IMAGE img_player_3_down[4];//Ƥ��3������
IMAGE img_player_3_left[4];//Ƥ��3������
IMAGE img_player_3_right[4];//Ƥ��3������

//��������ͼ��
IMAGE img_music_yes;
IMAGE img_music_no;

IMAGE img_tutorial;






//ȫ�ֱ�����
struct player Me;//���
Bullet bullets[50];//�ӵ�����
Enemy enemies[20];//��������
Drops drops[20];//����������
multimap<int, string, greater<int>> m_Record;//��ȡ��Ϸ��ʷ����
int flag = 0;//�����л�


bool is_move_w = false;
bool is_move_s = false;
bool is_move_a = false;
bool is_move_d = false;//�ж��Ƿ����ƶ�

int game_time = 120;//��Ϸʱ��

int idx_currentanim = 0;
const int player_anim_num = 4;

bool music_open = true;//�Ƿ�������

int Spawn = 80;//ˢ���ٶ�



void controller()
{
	while (true)
	{
		switch (flag)
		{
		case 0:
			clearBufferOnEscape();
			Login_screen();//��¼����
			break;
		case 1:
			clearBufferOnEscape();
			Registration_screen();//ע�����
			break;
		case 2:
			clearBufferOnEscape();
			Registration_is_successful();//ע��ɹ�����
			break;
		case 3:
			cleardevice();
			Menu_screen();//�˵�����
			break;
		case 4:
			clearBufferOnEscape();
			Skin_selection_screen();//Ƥ��ѡ��
			break;
		case 5:
			loadRecord();
			clearBufferOnEscape();
			Leaderboard();//���а�
			break;
		case 6:
			clearBufferOnEscape();
			Developer_Profile();//������Ա����
			break;
		case 7:
			init();
			clearBufferOnEscape();
			Play_the_game();//��Ϸ����
			break;
		case 8:
			clearBufferOnEscape();
			Victory_screen();//ʤ������
			break;
		case 9:
			clearBufferOnEscape();
			Failure_screen();//ʧ�ܽ���
			break;
		case 10:
			clearBufferOnEscape();
			Pause_the_game();
			break;//��ͣ����
		case 11:
			clearBufferOnEscape();
			Play_the_game();//����ͣ���浽��Ϸ����
			break;
		}
	}
}





int main()
{

	//���ɴ���
	initgraph(800, 800, EX_SHOWCONSOLE);
	cleardevice();

	//��ֹ�������
	mciSendString("open bgm/ռλ.mp3 alias nihao", NULL, 0, 0);
	mciSendString("play nihao repeat", NULL, 0, 0);


	//��������ͼƬ
	loadImgResource();//�Ȳ���

	//��ȡ֮ǰ�������¼
	loadRecord();

	playBackgroundMusic("bgm/����Ϸ&���а�&����&������Ա.mp3");

	controller();
	return 0;
}