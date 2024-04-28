#include "Game.h"
#include "view.h"
#include "serve.h"
using namespace std;


//代替putimage()函数使用--背景图还是用putimage()
inline void putimage_alpha(int x, int y, IMAGE* img);


//图片变量
IMAGE img_Login;//登录界面背景--主菜单界面也可以用
IMAGE img_Login_character;//原神之王那个字的图
IMAGE img_Registration_Victory_bk;//注册成功的图
IMAGE img_Menu_kaifatandui_bk;//开发团队界面背景图
IMAGE img_member[9];//小组成员的头像图
IMAGE img_Leaderboard_bk;//排行榜背景图
IMAGE img_skin_bk;//皮肤选择界面背景图
IMAGE img_Skin_selection[3];//皮肤选择界面的那三张人物选择图
IMAGE img_play_game_bk;//游戏界面背景图
IMAGE img_Failure_bk;//失败界面背景图
IMAGE img_Victory_bk;//胜利界面背景图
IMAGE img_Pause_the_game_bk;//暂停界面背景图
IMAGE img_Drops[5];//各种道具的图
IMAGE img_hp;//血量
IMAGE img_bullet;//子弹的图

IMAGE img_Enemy_1[4];//普通怪的图
IMAGE img_Enemy_2[4];//厚血怪的图
IMAGE img_Enemy_3[4];//移速怪的图

IMAGE img_player_1_up[4];//皮肤1向上走
IMAGE img_player_1_down[4];//皮肤1向下走
IMAGE img_player_1_left[4];//皮肤1向左走
IMAGE img_player_1_right[4];//皮肤1向右走

IMAGE img_player_2_up[4];//皮肤2向上走
IMAGE img_player_2_down[4];//皮肤2向下走
IMAGE img_player_2_left[4];//皮肤2向左走
IMAGE img_player_2_right[4];//皮肤2向右走

IMAGE img_player_3_up[4];//皮肤3向上走
IMAGE img_player_3_down[4];//皮肤3向下走
IMAGE img_player_3_left[4];//皮肤3向左走
IMAGE img_player_3_right[4];//皮肤3向右走

//开关音乐图标
IMAGE img_music_yes;
IMAGE img_music_no;

IMAGE img_tutorial;






//全局变量区
struct player Me;//玩家
Bullet bullets[50];//子弹数组
Enemy enemies[20];//敌人数组
Drops drops[20];//掉落物数组
multimap<int, string, greater<int>> m_Record;//读取游戏历史分数
int flag = 0;//界面切换


bool is_move_w = false;
bool is_move_s = false;
bool is_move_a = false;
bool is_move_d = false;//判断是否在移动

int game_time = 120;//游戏时间

int idx_currentanim = 0;
const int player_anim_num = 4;

bool music_open = true;//是否开启音乐

int Spawn = 80;//刷新速度



void controller()
{
	while (true)
	{
		switch (flag)
		{
		case 0:
			clearBufferOnEscape();
			Login_screen();//登录界面
			break;
		case 1:
			clearBufferOnEscape();
			Registration_screen();//注册界面
			break;
		case 2:
			clearBufferOnEscape();
			Registration_is_successful();//注册成功界面
			break;
		case 3:
			cleardevice();
			Menu_screen();//菜单界面
			break;
		case 4:
			clearBufferOnEscape();
			Skin_selection_screen();//皮肤选择
			break;
		case 5:
			loadRecord();
			clearBufferOnEscape();
			Leaderboard();//排行榜
			break;
		case 6:
			clearBufferOnEscape();
			Developer_Profile();//开发人员界面
			break;
		case 7:
			init();
			clearBufferOnEscape();
			Play_the_game();//游戏界面
			break;
		case 8:
			clearBufferOnEscape();
			Victory_screen();//胜利界面
			break;
		case 9:
			clearBufferOnEscape();
			Failure_screen();//失败界面
			break;
		case 10:
			clearBufferOnEscape();
			Pause_the_game();
			break;//暂停界面
		case 11:
			clearBufferOnEscape();
			Play_the_game();//从暂停界面到游戏界面
			break;
		}
	}
}





int main()
{

	//生成窗口
	initgraph(800, 800, EX_SHOWCONSOLE);
	cleardevice();

	//防止程序变慢
	mciSendString("open bgm/占位.mp3 alias nihao", NULL, 0, 0);
	mciSendString("play nihao repeat", NULL, 0, 0);


	//加载所有图片
	loadImgResource();//先不管

	//获取之前的游玩记录
	loadRecord();

	playBackgroundMusic("bgm/打开游戏&排行榜&设置&开发人员.mp3");

	controller();
	return 0;
}