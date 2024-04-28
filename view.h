#pragma once
#include "Game.h"

using namespace std;






//引用的全局变量区
extern player Me;//玩家
extern Bullet bullets[50];//子弹数组
extern Enemy enemies[20];//敌人数组
extern Drops drops[20];//掉落物数组
extern multimap<int, string,greater<int>> m_Record;//读取游戏历史分数






//后加的引用的全局变量区
extern int game_time;
extern int flag;
extern int idx_currentanim;
extern const int player_anim_num;
extern int Spawn;
extern bool music_open;

//函数声明
inline void putimage_alpha(int x, int y, IMAGE* img);//打印透明背景图片
void Login_screen();//登录界面
void Login_input(ExMessage& Login_msg, Button& LB, Button& EB, Button& RB, HWND& hwd);//登录输入
bool Login_is_successful();//判断登录是否成功界面
void Registration_screen();//注册界面
void Registration_input(ExMessage& re_msg, Button su_Re);//注册输入
void Registration_is_successful();//判断注册是否成功界面
void add_Account();//将注册的账号写入本地数据
void Menu_screen();//菜单界面
void Leaderboard();//排行榜界面
void Developer_Profile();//开发人员界面
void Skin_selection_screen();//皮肤选择界面
//-------------------------------------
void Play_the_game();//游戏开始
void Game_bk();//打印游戏界面的背景
void Game_time();//打印游戏的剩余时间
void Game_player();//打印玩家
void Game_bullets();//打印子弹
void Game_enemies();//打印怪物
void Game_drops();//打印掉落物
void Pause_the_game();//打印暂停界面
void Failure_screen();//打印游戏失败界面
void Victory_screen();//打印游戏胜利界面
