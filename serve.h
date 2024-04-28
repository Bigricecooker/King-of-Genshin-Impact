#pragma once
#include "Game.h"
#include "view.h"

using namespace std;

//引用的全局变量区
extern player Me;//玩家
extern Bullet bullets[50];//子弹数组
extern Enemy enemies[20];//敌人数组
extern Drops drops[20];//掉落物数组
extern multimap<int, string, greater<int>> m_Record;//读取游戏历史分数

extern IMAGE img_Login;//登录界面背景--主菜单界面也可以用
extern IMAGE img_Login_character;//原神之王那个字的图
extern IMAGE img_Registration_Victory_bk;//注册成功的图
extern IMAGE img_Menu_kaifatandui_bk;//开发团队界面背景图
extern IMAGE img_member[9];//小组成员的头像图
extern IMAGE img_Leaderboard_bk;//排行榜背景图
extern IMAGE img_skin_bk;//皮肤选择界面背景图
extern IMAGE img_play_game_bk;//游戏界面背景图
extern IMAGE img_Skin_selection[3];//皮肤选择界面的那两张人物选择图
extern IMAGE img_Failure_bk;//失败界面背景图
extern IMAGE img_Victory_bk;//胜利界面背景图
extern IMAGE img_Pause_the_game_bk;//暂停界面背景图
extern IMAGE img_Drops[5];//各种道具的图
extern IMAGE img_hp;

extern IMAGE img_bullet;//子弹的图

extern IMAGE img_Enemy_2[4];//厚血怪的图
extern IMAGE img_Enemy_3[4];//移速怪的图

extern IMAGE img_player_1_up[4];//皮肤1向上走
extern IMAGE img_player_1_down[4];//皮肤1向下走
extern IMAGE img_player_1_left[4];//皮肤1向左走
extern IMAGE img_player_1_right[4];//皮肤1向右走

extern IMAGE img_player_2_up[4];//皮肤2向上走
extern IMAGE img_player_2_down[4];//皮肤2向下走
extern IMAGE img_player_2_left[4];//皮肤2向左走
extern IMAGE img_player_2_right[4];//皮肤2向右走

extern IMAGE img_player_3_up[4];//皮肤3向上走
extern IMAGE img_player_3_down[4];//皮肤3向下走
extern IMAGE img_player_3_left[4];//皮肤3向左走
extern IMAGE img_player_3_right[4];//皮肤3向右走

extern IMAGE img_Enemy_1[4];//普通怪的图
extern IMAGE img_Enemy_2[4];//厚血怪的图
extern IMAGE img_Enemy_3[4];//移速怪的图

extern IMAGE img_music_yes;
extern IMAGE img_music_no;

extern bool is_move_w;
extern bool is_move_s;
extern bool is_move_a;
extern bool is_move_d;

extern IMAGE img_tutorial;
//后加的引用的全局变量区
extern int flag;
extern int idx_currentanim;
extern const int player_anim_num;
extern int Spawn;
extern bool music_open;

//函数声明
void clearBufferOnEscape();//清空按键消息中的ESC
void playBackgroundMusic(const char* music);//播放音乐
void loadImgResource();//加载所有图片
void loadRecord();//读取游戏记录
void saveRecord();//保存游戏分数
void init();//初始化数据
void Shoot_bullets();//发射子弹
void Spawn_enemies();//生成敌人
void Data_move();//封装的各种移动函数
void player_move();//玩家移动
void bullets_move();//子弹移动
void enemies_move();//敌人移动
void Collision_detection();//封装的各种碰撞检测函数
void player_whit_drops();//玩家与掉落物
void player_with_enemies();//玩家与敌人
void enemies_with_bullets();//子弹与敌人
void bullets_with_boundary();//子弹出界
bool is_win();//胜利判断
bool is_fail();//失败判断