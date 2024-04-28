#include "serve.h"
using namespace std;



/*
	负责人:电饭煲
	功能:清空缓冲区里的ESC
*/
void clearBufferOnEscape()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // 检测是否按下了 ESC 键
		while (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // 清空键盘缓冲区
			;
	}
	ExMessage msg;
	while (peekmessage(&msg));
}


/*
	负责人:电饭煲
	功能:播放音乐
*/
void playBackgroundMusic(const char* music)
{
	if (music_open)
	{
		char cmd[100] = { 0 };
		MCIERROR ret;
		sprintf_s(cmd, "open %s", music);

		ret = mciSendString(cmd, NULL, 0, NULL);
		if (ret != 0)
		{
			//获取一下错误信息
			char err[100] = { 0 };
			mciGetErrorString(ret, err, sizeof(err));
			printf("oper: %s", err);
		}

		sprintf_s(cmd, "play %s repeat", music);
		mciSendString(cmd, NULL, 0, NULL);//如果要重复播放则再加一个repeat
	}
}

/*
	负责人:电饭煲
	功能
		随机返回min到max之间的数

		参数:int min, int max
		返回值:int
*/
int getRandomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}



/*
	负责人:电饭煲
	功能:
	加载所有图片
*/
void loadImgResource()
{
	loadimage(&img_Login,"img/BK/可莉.png" );
	loadimage(&img_Login_character,"img/BK/可莉有文字.png");
	loadimage(&img_Registration_Victory_bk, "img/BK/注册成功.png");
	loadimage(&img_Menu_kaifatandui_bk,"img/BK/制作人员名单背景图.png",800,800);
	loadimage(&img_member[0], "img/头像/牢胡.jpg", 70, 70);
	loadimage(&img_member[1], "img/头像/小于.jpg", 70, 70);
	loadimage(&img_member[2], "img/头像/吃茶.jpg", 70, 70);
	loadimage(&img_member[3], "img/头像/汉明.jpg", 70, 70);
	loadimage(&img_member[4], "img/头像/小7.jpg", 70, 70);
	loadimage(&img_member[5], "img/头像/晓酥.jpg", 70, 70);
	loadimage(&img_member[6], "img/头像/启宇.jpg", 70, 70);
	loadimage(&img_member[7], "img/头像/电饭煲.jpg", 70, 70);
	loadimage(&img_member[8], "img/头像/学长.jpg", 70, 70);
	loadimage(&img_Leaderboard_bk,"img/BK/皮肤选择界面背景图.png",800,800);
	loadimage(&img_Leaderboard_bk, "img/BK/排行榜.png",800,800);
	loadimage(&img_play_game_bk, "img/BK/地图.png");
	loadimage(&img_Skin_selection[0], "img/皮肤/anbo.jpg", 50 * 3, 100 * 3);
	loadimage(&img_Skin_selection[1], "img/皮肤/ganyu.jpg", 50 * 3, 100 * 3);
	loadimage(&img_Skin_selection[2], "img/皮肤/xiangling.jpg", 50 * 3, 100 * 3);
	loadimage(&img_hp, "img/BK/血量.png");
	loadimage(&img_music_no,"img/BK/静音.png",50,50);
	loadimage(&img_music_yes, "img/BK/声音.png",50,50);

	//角色1
	for (size_t i = 0; i < 4; i++)
	{
		string path;
		path = "img/anbo/imgdown" + to_string(i+1) + ".png";
		loadimage(&img_player_1_down[i], path.c_str());
	}
	for (size_t i = 0; i <4; i++)
	{
		string path;
		path = "img/anbo/imgup" + to_string(i + 1) + ".png";
		loadimage(&img_player_1_up[i], path.c_str());
	}
	for (size_t i = 0; i < 4; i++) {
		string path;
		path = "img/anbo/imgleft" + to_string(i + 1) + ".png";
		loadimage(&img_player_1_left[i], path.c_str());
	}
	for (size_t i = 0; i < 4; i++)
	{
		string path;
		path = "img/anbo/imgright" + to_string(i + 1) + ".png";
		loadimage(&img_player_1_right[i], path.c_str());
	}


	//角色2
	for (size_t i = 0; i < 4; i++)
	{
		string path;
		path = "img/ganyu/imgdown" + to_string(i+1) + ".png";
		loadimage(&img_player_2_down[i], path.c_str());
	}
	for (size_t i = 0; i < 4; i++)
	{
		string path;
		path = "img/ganyu/imgup" + to_string(i+1) + ".png";
		loadimage(&img_player_2_up[i], path.c_str());
	}
	for (size_t i = 0; i < 4; i++)
	{
		string path;
		path = "img/ganyu/imgleft" + to_string(i+1) + ".png";
		loadimage(&img_player_2_left[i], path.c_str());
	}
	for (size_t i = 0; i < 4; i++)
	{
		string path;
		path = "img/ganyu/imgright" + to_string(i+1) + ".png";
		loadimage(&img_player_2_right[i], path.c_str());
	}



	//角色3
	for (size_t i = 0; i < 4; i++)
	{
		string path;
		path = "img/ixangling/imgdown" + to_string(i+1) + ".png";
		loadimage(&img_player_3_down[i], path.c_str());
	}
	for (size_t i = 0; i < 4; i++)
	{
		string path;
		path = "img/ixangling/imgup" + to_string(i+1) + ".png";
		loadimage(&img_player_3_up[i], path.c_str());
	}
	for (size_t i = 0; i <4; i++)
	{
		string path;
		path = "img/ixangling/imgleft" + to_string(i+1) + ".png";
		loadimage(&img_player_3_left[i], path.c_str());
	}
	for (size_t i = 0; i < 4; i++)
	{
		string path;
		path = "img/ixangling/imgright" + to_string(i+1) + ".png";
		loadimage(&img_player_3_right[i], path.c_str());
	}

	loadimage(&img_Enemy_1[0], "img/小怪/img1.png");
	loadimage(&img_Enemy_1[1], "img/小怪/img2.png");
	loadimage(&img_Enemy_1[2], "img/小怪/img3.png");
	loadimage(&img_Enemy_1[3], "img/小怪/img4.png");
	loadimage(&img_Enemy_3[0], "img/小怪/img6.png",40,40);
	loadimage(&img_Enemy_3[1], "img/小怪/img7.png", 40, 40);
	loadimage(&img_Enemy_3[2], "img/小怪/img8.png", 40, 40);
	loadimage(&img_Enemy_3[3], "img/小怪/img9.png", 40, 40);
	loadimage(&img_Enemy_2[0], "img/小怪/img10.png");
	loadimage(&img_Enemy_2[1], "img/小怪/img11.png");
	loadimage(&img_Enemy_2[2], "img/小怪/img12.png");
	loadimage(&img_Enemy_2[3], "img/小怪/img13.png");

	//道具
	loadimage(&img_Drops[0], "img/道具/hp.png");
	loadimage(&img_Drops[1], "img/道具/speed.png");
	loadimage(&img_Drops[2], "img/道具/cd.png");
	loadimage(&img_Drops[3], "img/道具/luck.png");
	loadimage(&img_Drops[4], "img/道具/200.png");

	loadimage(&img_bullet, "img/bullet.png",28,28);
	loadimage(&img_Failure_bk,"img/BK/失败.png");
	loadimage(&img_Victory_bk,"img/BK/胜利.png" );
	loadimage(&img_Pause_the_game_bk,"img/BK/暂停.png" );
	loadimage(&img_tutorial, "img/BK/教程.png");
}


/*
	负责人:小于
	功能:
	将之前的记录都放入一个multimap<int, vector<string>> m_Record;的全局变量中(分数,名字),同时使其降序排列
	该函数有类似黑马c++中演讲比赛管理系统中的一个函数
*/
void loadRecord()
{
	m_Record.clear();
	ifstream score_file("scores.txt", ios::in);
	if (!score_file.is_open())
	{
		return;
	}
	string name;
	string s_score;
	int score=0;
	while ( getline(score_file, name)&&(!score_file.eof()))
	{
		//名字和分数是分两行存的

		getline(score_file, s_score);//读取下一行紧跟着的该用户的分数
		int pos = 1;
		for (int i = s_score.length() - 1; i >= 0; i--) {
			score += (s_score[i] - '0') * pos;
			pos *= 10;

		}
		m_Record.insert(pair<int, string>(score, name));
		score = 0;
	}
	score_file.close();
}

/*
	负责人:小于
	功能:
	将游戏分数,玩家名称一起存入保存游戏分数的文件中
*/
void saveRecord()
{
	ofstream score_file("scores.txt", ios::app);
	if (!score_file.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}
	score_file << Me.name << endl << Me.score << endl;
	score_file.close();
}



/*
	负责人:电饭煲
	功能:
		初始化玩家数据

		初始化敌人数组
		(将敌人结构数组中的敌人结构元素的is_live全部初始化为false(其他数据应该不用))
		初始话子弹数组
		(和敌人一样)
		初始化掉落物数组
*/
void init()
{
	Spawn = 80;
	game_time = 120;
	//玩家
	Me.hp = 100;
	Me.is_live = true;
	Me.score = 0;
	Me.cd = 15;
	Me.size = 15;
	Me.speed = 3;
	Me.x = 400;
	Me.y = 400;
	Me.luck = 9;

	//敌人数组
	for (size_t i = 0; i < 20; i++)
	{
		enemies[i].is_live = false;
	}

	//子弹数组
	for (size_t i = 0; i < 50; i++)
	{
		bullets[i].is_live = false;
		bullets[i].attack = 20;
		bullets[i].speed = 6;
		bullets[i].size = 14;
		bullets[i].angle = -1;
	}

	//掉落物数组
	for (size_t i = 0; i < 20; i++)
	{
		drops[i].is_live = false;
		drops[i].size = 16;
	}
}


/*
	负责人:电饭煲
	功能:

	接收一个消息参数
	该消息参数为上下左右等8个方向按键时遍历子弹数组
	当该子弹is_live==false时将其变为true,并为该子弹初始化(如果捡了道具的话不一样,应该可以弄几个全局变量,我先想一下)


	参数:ExMessage*
	返回值:void
*/
void Shoot_bullets()
{
	
	if (GetAsyncKeyState(VK_UP) )
	{
		if (GetAsyncKeyState(VK_LEFT))//左上
		{
			PlaySound("bgm/bullet.wav", NULL, SND_FILENAME | SND_ASYNC);
			Me.direct = 2;
			for (size_t i = 0; i < 50; i++)
			{
				if (bullets[i].is_live == false)
				{
					bullets[i].is_live = true;
					bullets[i].angle = 7;
					bullets[i].x = Me.x;
					bullets[i].y = Me.y;
					break;
				}
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT))//右上
		{
			PlaySound("bgm/bullet.wav", NULL, SND_FILENAME | SND_ASYNC);
			Me.direct = 3;
			for (size_t i = 0; i < 50; i++)
			{
				if (bullets[i].is_live == false)
				{
					bullets[i].is_live = true;
					bullets[i].angle = 9;
					bullets[i].x = Me.x;
					bullets[i].y = Me.y;
					break;
				}
			}
		}
		else//上
		{
			PlaySound("bgm/bullet.wav", NULL, SND_FILENAME | SND_ASYNC);
			Me.direct = 1;
			for (size_t i = 0; i < 50; i++)
			{
				if (bullets[i].is_live == false)
				{
					bullets[i].is_live = true;
					bullets[i].angle = 8;
					bullets[i].x = Me.x;
					bullets[i].y = Me.y;
					break;
				}
			}
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) )
	{
		if (GetAsyncKeyState(VK_LEFT))//左下
		{
			PlaySound("bgm/bullet.wav", NULL, SND_FILENAME | SND_ASYNC);
			Me.direct = 2;
			for (size_t i = 0; i < 50; i++)
			{
				if (bullets[i].is_live == false)
				{
					bullets[i].is_live = true;
					bullets[i].angle = 1;
					bullets[i].x = Me.x;
					bullets[i].y = Me.y;
					break;
				}
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT))//右下
		{
			PlaySound("bgm/bullet.wav", NULL, SND_FILENAME | SND_ASYNC);
			Me.direct = 3;
			for (size_t i = 0; i < 50; i++)
			{
				if (bullets[i].is_live == false)
				{
					bullets[i].is_live = true;
					bullets[i].angle = 3;
					bullets[i].x = Me.x;
					bullets[i].y = Me.y;
					break;
				}
			}
		}
		else//下
		{
			PlaySound("bgm/bullet.wav", NULL, SND_FILENAME | SND_ASYNC);
			Me.direct = 0;
			for (size_t i = 0; i < 50; i++)
			{
				if (bullets[i].is_live == false)
				{
					bullets[i].is_live = true;
					bullets[i].angle = 2;
					bullets[i].x = Me.x;
					bullets[i].y = Me.y;
					break;
				}
			}
		}
	}
	else if (GetAsyncKeyState(VK_LEFT))//左
	{
		PlaySound("bgm/bullet.wav", NULL, SND_FILENAME | SND_ASYNC);
		Me.direct = 2;
		for (size_t i = 0; i < 50; i++)
		{
			if (bullets[i].is_live == false)
			{
				bullets[i].is_live = true;
				bullets[i].angle = 4;
				bullets[i].x = Me.x;
				bullets[i].y = Me.y;
				break;
			}
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) )//右
	{
		PlaySound("bgm/bullet.wav", NULL, SND_FILENAME | SND_ASYNC);
		Me.direct = 3;
		for (size_t i = 0; i < 50; i++)
		{
			if (bullets[i].is_live == false)
			{
				bullets[i].is_live = true;
				bullets[i].angle = 6;
				bullets[i].x = Me.x;
				bullets[i].y = Me.y;
				break;
			}
		}
	}
	
}



/*
	负责人:电饭煲
	功能:
	遍历敌人数组,当该敌人is_live==false时将其变为true,并用随机函数决定它类型和生成位置(4个方向)
*/
void Spawn_enemies()
{
	for (size_t i = 0; i < 20; i++)
	{
		if (!enemies[i].is_live)
		{

			enemies[i].is_live = true;
			int random_1 = getRandomNumber(0, 3);//生成方向
			enemies[i].type = getRandomNumber(0, 2);//怪物类型
			if(!drops[i].is_live)
				enemies[i].drop= getRandomNumber(0, 4);//掉落的道具种类
			if (random_1 == 0)//上
			{
				enemies[i].x = getRandomNumber(350, 450);//400
				enemies[i].y = 120;
				if (enemies[i].type == 0)//普通
				{
					enemies[i].hp = 20;
					enemies[i].speed = 3;
					enemies[i].score = 20;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 1)//移速
				{
					enemies[i].hp = 20;
					enemies[i].speed = 5;
					enemies[i].score = 30;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 2)//血量
				{
					enemies[i].hp = 60;
					enemies[i].speed = 2;
					enemies[i].score = 50;
					enemies[i].size = 20;
					return;
				}
			}
			else if (random_1 == 1)//下
			{
				enemies[i].x = getRandomNumber(350, 450);//400
				enemies[i].y = 680;
				if (enemies[i].type == 0)//普通
				{
					enemies[i].hp = 20;
					enemies[i].speed = 3;
					enemies[i].score = 20;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 1)//移速
				{
					enemies[i].hp = 20;
					enemies[i].speed = 5;
					enemies[i].score = 30;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 2)//血量
				{
					enemies[i].hp = 60;
					enemies[i].speed = 2;
					enemies[i].score = 50;
					enemies[i].size = 20;
					return;
				}
			}
			else if (random_1 == 2)//左
			{
				enemies[i].x = 120;
				enemies[i].y = getRandomNumber(350, 450);//400
				if (enemies[i].type == 0)//普通
				{
					enemies[i].hp = 20;
					enemies[i].speed = 3;
					enemies[i].score = 20;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 1)//移速
				{
					enemies[i].hp = 20;
					enemies[i].speed = 5;
					enemies[i].score = 30;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 2)//血量
				{
					enemies[i].hp = 60;
					enemies[i].speed = 2;
					enemies[i].score = 50;
					enemies[i].size = 20;
					return;
				}
			}
			else if (random_1 == 3)//右
			{
				enemies[i].x = 680;
				enemies[i].y = getRandomNumber(350, 450);//400
				if (enemies[i].type == 0)//普通
				{
					enemies[i].hp = 20;
					enemies[i].speed = 3;
					enemies[i].score = 20;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 1)//移速
				{
					enemies[i].hp = 20;
					enemies[i].speed = 5;
					enemies[i].score = 30;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 2)//血量
				{
					enemies[i].hp = 60;
					enemies[i].speed = 2;
					enemies[i].score = 50;
					enemies[i].size = 20;
					return;
				}
			}
		}
	}


}


/*
	负责人:电饭煲
	功能:封装玩家,子弹,敌人移动函数的函数

	参数:ExMessage*
	返回值:void
*/
void Data_move()
{
	player_move();
	bullets_move();
	enemies_move();
}



/*
	负责人:电饭煲
	功能:
	接收一个消息参数
	当该消息参数为按下wasd键时分别将is_move_方向这几个bool类型的全局变量变为true
	当该消息参数为松开按键时重新变为false

	分别判断4个变量是否为true
	如果为真,则改变玩家坐标
	例:if (is_move_up) Me.y -= Me.speed;()
*/
void player_move()
{
	if (GetAsyncKeyState('W')) 
	{
		if(Me.y > 150)
			Me.y -= Me.speed;
		Me.direct = 1;
	}
	if (GetAsyncKeyState('S')) {
		if (Me.y < 635)
			Me.y += Me.speed;
		Me.direct = 0;
	}
	if (GetAsyncKeyState('A')) {
		if (Me.x > 175 )
			Me.x -= Me.speed;
		Me.direct = 2;
	}
	if (GetAsyncKeyState('D')) {
		if ( Me.x < 625 )
			Me.x += Me.speed;
		Me.direct = 3;
	}
}

/*
	负责人:电饭煲
	功能:

	遍历子弹数组,根据每个存在的子弹的角度和方向改变该子弹的坐标
*/
void bullets_move()
{
	for (size_t i = 0; i < 50; i++)
	{
		if (bullets[i].is_live)
		{
			if (bullets[i].angle == 8)//8为上
				bullets[i].y -= bullets[i].speed;
			else if (bullets[i].angle == 2)//2为下
				bullets[i].y += bullets[i].speed;
			else if (bullets[i].angle == 4)//4为左
				bullets[i].x -= bullets[i].speed;
			else if (bullets[i].angle == 6)//6为右
				bullets[i].x += bullets[i].speed;
			else if (bullets[i].angle == 7)//7为左上
			{
				bullets[i].x -= (bullets[i].speed / 1.4);
				bullets[i].y -= (bullets[i].speed / 1.4);
			}
			else if (bullets[i].angle == 1)//1为左下
			{
				bullets[i].x -= (bullets[i].speed / 1.4);
				bullets[i].y += (bullets[i].speed / 1.4);
			}
			else if (bullets[i].angle == 9)//9为右上
			{
				bullets[i].x += (bullets[i].speed / 1.4);
				bullets[i].y -= (bullets[i].speed / 1.4);
			}
			else if (bullets[i].angle == 3)//3为右下
			{
				bullets[i].x += (bullets[i].speed/1.4);
				bullets[i].y +=(bullets[i].speed/1.4);
			}
		}
	}
}


/*
	负责人:牢胡
	功能:
	遍历敌人数组,根据玩家的坐标来改变每个存在的敌人的坐标值

	例如:水平方向的敌人优先水平接近玩家,纵向反向出现的敌人优先纵向接近玩家
*/
void enemies_move()
{
	for (size_t i = 0; i < 20; i++)
	{
		// 如果怪物活着
		if (enemies[i].is_live) {
			// 计算两点之间的距离（斜边）
			int dx = Me.x - enemies[i].x;
			int dy = Me.y - enemies[i].y;
			int distance = sqrt(dx * dx + dy * dy);

			// 如果距离不为0，计算两个方向的变化量
			if (distance != 0) {
				// 计算 x 方向的变化量
				double delta_x = enemies[i].speed * dx / distance;
				// 计算 y 方向的变化量
				double delta_y = enemies[i].speed * dy / distance;
				// 更新位置
				enemies[i].x += delta_x;
				enemies[i].y += delta_y;
			}
		}
	}

}



/*
	负责人:电饭煲
	功能:
	封装各种碰撞检测
*/
void Collision_detection()
{
	player_with_enemies();
	enemies_with_bullets();
	bullets_with_boundary();
	player_whit_drops();
}

/*
	负责人:电饭煲
	功能:
	玩家与掉落物的处理
*/
void player_whit_drops()
{
	for (size_t i = 0; i < 20; i++)
	{
		if (drops[i].is_live)
		{
			if ((Me.x - drops[i].x) * (Me.x - drops[i].x) + (Me.y - drops[i].y) * (Me.y - drops[i].y) <= (Me.size + drops[i].size) * (Me.size + drops[i].size))
			{
				PlaySound("bgm/道具.wav", NULL, SND_FILENAME | SND_ASYNC);
				drops[i].is_live = false;
				if (drops[i].type == 0)//血瓶
				{
					if (Me.hp > 60)
						Me.hp = 100;
					else
						Me.hp += 40;
				}
				else if (drops[i].type == 1)//鞋子
				{
					if (Me.speed < 5)
						Me.speed++;
					else
						Me.score += 50;
				}
				else if (drops[i].type == 2)//cd
				{
					if (Me.cd >7)
						Me.cd--;
					else
						Me.score += 50;
				}
				else if (drops[i].type == 3)
				{
					if (Me.luck > 5)
						Me.luck--;
					else
						Me.score += 50;
				}
				else if (drops[i].type == 4)
				{
					Me.score += 200;
				}
			}
		}
	}
}


/*
	负责人:启宇
	功能:
		遍历敌人数组
		判断每一个敌人与玩家的位置关系
		如果玩家与敌人的坐标距离小于半径之和
		则扣除玩家相应的血量,且该敌人直接死亡(即将enemies[i].is_live=false)并为玩家加上对应的分数
*/
void player_with_enemies()
{
	for (int i = 0; i < 20; i++)
	{
		if (enemies[i].is_live)
		{
			if ((Me.x - enemies[i].x) * (Me.x - enemies[i].x) + (Me.y - enemies[i].y) * (Me.y - enemies[i].y) <= (Me.size + enemies[i].size) * (Me.size + enemies[i].size))
			{
				if (Me.skin_number == 1)
				{
					PlaySound("bgm/hurt1.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				else if (Me.skin_number == 2)
				{
					PlaySound("bgm/hurt2.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				else if (Me.skin_number == 3)
				{
					PlaySound("bgm/hurt3.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				Me.hp -= 20;
				enemies[i].is_live = false;
				if (Me.hp <= 0)
				{
					Me.is_live = false;
				}
			}
		}
	}
}



/*
	负责人:启宇
	功能:
	判断敌人与玩家发射的子弹是否碰撞
	如发生碰撞,则该子弹消失,该敌人减少对应的血量并判断敌人是否死亡
	如该敌人死亡,则同时为玩家加上对应的分数
*/
void enemies_with_bullets()
{
	//子弹与敌人是否碰撞检测
	for (int i = 0; i < 50; i++)
	{
		if (bullets[i].is_live)
		{
			for (int j = 0; j < 20; j++)
			{
				if (enemies[j].is_live)
				{
					if ((bullets[i].x - enemies[j].x) * (bullets[i].x - enemies[j].x) + (bullets[i].y - enemies[j].y) * (bullets[i].y - enemies[j].y) <= (bullets[i].size + enemies[j].size) * (bullets[i].size + enemies[j].size))
					{
						enemies[j].hp -= bullets[i].attack;
						bullets[i].is_live = false;
						if (enemies[j].hp <= 0)
						{
							enemies[j].is_live = false;
							Me.score += enemies[j].score;
							if (enemies[j].type == 0)
							{
								PlaySound("bgm/1.wav", NULL, SND_FILENAME | SND_ASYNC);
							}
							else if (enemies[j].type == 1)
							{
								PlaySound("bgm/2.wav", NULL, SND_FILENAME | SND_ASYNC);
							}
							else if (enemies[j].type == 2)
							{
								PlaySound("bgm/3.wav", NULL, SND_FILENAME | SND_ASYNC);
							}


							if (getRandomNumber(0, Me.luck) == 5)//十分之一的概率掉落
							{
								if (!drops[j].is_live)
								{
									drops[j].x = enemies[j].x;
									drops[j].y = enemies[j].y;
									drops[j].type = enemies[j].drop;
								}
								drops[j].is_live = true;
							}
							
							
						}
					}
				}
			}
		}
	}
}




/*
	负责人:启宇
	功能:
	遍历子弹数组,判断子弹是否超出边界
	如超出了边界则该子弹消失

*/
void bullets_with_boundary()
{
	for (int i = 0; i < 50; i++)
	{
		if (bullets[i].x > 680 || bullets[i].x < 130 || bullets[i].y>680 || bullets[i].y < 130)
		{
			bullets[i].is_live = false;
		}
	}
}






/*
	负责人:小于
	功能:
	当游戏时间为0时返回true
	否则返回false

	参数:void
	返回值:bool
*/
bool is_win()
{
	if (game_time <=0)
		return true;
	return false;
}


/*
	负责人:小于
	功能:
	当玩家血量小于等于0时返回true
	否则返回false

	参数:void
	返回值:bool
*/
bool is_fail()
{
	if (Me.hp <= 0)
		return true;
	return false;
}