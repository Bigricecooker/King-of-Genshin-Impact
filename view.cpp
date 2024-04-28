#include "view.h"
#include "serve.h"



inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

/*--------------------------------登录----------------------------------*/
/*
	负责人:牢胡
	功能:

	打印登录界面并绘制各种按键

	while(true)
	{
		接收用户鼠标消息
		判断用户是否点到按钮并调用该按钮的功能函数

		调用Login_input(&msg);

		点击登录:调用Login_is_successful()
		点击注册新账号:调用Registration_screen()
		点击退出游戏,调用exit(0);退出游戏
	}
	参数:void
	返回值:void

*/
void Login_screen()
{
	BeginBatchDraw();
	//修改窗口标题
	HWND hwd = GetHWnd();
	SetWindowText(hwd, "原神之王");

	putimage(0, 0, &img_Login_character);
	string ac_text = "账号";
	string pw_text = "密码";

	//设置打印样式
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "楷体");
	setfillcolor(WHITE);
	setlinecolor(RGB(100, 77, 77));

	//打印输入输出提示字及框
	outtextxy(260, 300, ac_text.c_str());
	fillrectangle(260, 330, 540, 350);
	outtextxy(260, 370, pw_text.c_str());
	fillrectangle(260, 400, 540, 420);

	//三个按钮

	Button RB(260, 480, 60, 20);//Register_Button
	RB.Creat_Button("注册新账号", 12);
	Button LB(370, 480, 60, 20);//Login_Button
	LB.Creat_Button("登录", 12);
	Button EB(480, 480, 60, 20);//Exit_Button
	EB.Creat_Button("退出游戏", 12);

	if (music_open)
	{
		putimage_alpha(0, 630, &img_music_yes);
	}
	else
		putimage_alpha(0, 630, &img_music_no);
	EndBatchDraw();
	//逻辑判断 -- 接收鼠标信息

	ExMessage Login_msg;
	Login_input(Login_msg, LB, EB, RB, hwd);

}



/*
	负责人:牢胡
	功能:
	接收一个消息指针, 判断点击的位置
	当点击输入框时调出白框输入名称或密码(可先用全局变量保存)
	同时将用户输入打印到对应的输入框中

	参数 : ExMessage * msg
	返回值 : void
*/
void Login_input(ExMessage& Login_msg, Button& LB, Button& EB, Button& RB, HWND& hwd)
{
	//初始化方便后面逻辑判断
	Me.uid = "0";
	Me.password = "0";
	bool ac_is_input = false;
	bool ps_is_input = false;

	while (1) {

		
		if (peekmessage(&Login_msg, EM_MOUSE))
		{
			switch (Login_msg.message)
			{
				//如果左键点击
			case WM_LBUTTONDOWN:
				//五个区域，两个输入，三个按钮
				//账号输入
				if (Login_msg.x >= 260 && Login_msg.y >= 330 && Login_msg.x <= 540 && Login_msg.y <= 350) {
					char ac[10];
					InputBox(ac, 10, "请输入账号", "提示", NULL, 0, 0, true);
					string emp(ac);
					Me.uid = emp;
					if (Me.uid.compare("0")) {
						ac_is_input = true;
					}
					//打印账号
					setbkcolor(WHITE);
					setbkmode(OPAQUE);
					fillrectangle(260, 330, 540, 350);
					outtextxy(262, 335, Me.uid.c_str());
				}
				//密码输入
				else if (Login_msg.x >= 260 && Login_msg.y >= 400 && Login_msg.x <= 540 && Login_msg.y <= 420) {
					char ps[10];
					InputBox(ps, 9, "请输入密码（密码不超过8位）", "提示", NULL, 0, 0, true);
					string emp(ps);
					Me.password = emp;
					if (Me.password.compare("0")) {
						ps_is_input = true;
					}
					//打印密码
					setbkcolor(WHITE);
					setbkmode(OPAQUE);
					fillrectangle(260, 400, 540, 420);
					outtextxy(262, 405, Me.password.c_str());
				}
				//登录
				else if (Login_msg.x >= LB.B_x && Login_msg.y >= LB.B_y && Login_msg.x <= LB.B_x + LB.B_width && Login_msg.y <= LB.B_y + LB.B_height) 
				{
					//登录

					if (!ac_is_input) {
						MessageBox(hwd, "请输入账号", "提示", MB_OK);
					}
					else if (!ps_is_input) {
						MessageBox(hwd, "请输入密码", "提示", MB_OK);
					}
					else if (!ac_is_input && !ps_is_input) {
						MessageBox(hwd, "请输入账号密码", "提示", MB_OK);
					}
					else {
						if (Login_is_successful()) 
						{
							flag = 3;
							return;
						}
						else {
							MessageBox(hwd, "账号密码有误，请重新输入", "提示", MB_OK);
						}
					}

				}
				//退出游戏
				else if (Login_msg.x >= EB.B_x && Login_msg.y >= EB.B_y && Login_msg.x <= EB.B_x + EB.B_width && Login_msg.y <= EB.B_y + EB.B_height) {
					exit(0);
				}
				//注册
				else if (Login_msg.x >= RB.B_x && Login_msg.y >= RB.B_y && Login_msg.x <= RB.B_x + RB.B_width && Login_msg.y <= RB.B_y + RB.B_height) {
					flag=1;
					return;
				}
				else if (Login_msg.x > 0 && Login_msg.x < 50 && Login_msg.y>630 && Login_msg.y < 630 + 50)
				{
					if (music_open)
					{
						music_open = false;
						mciSendString("close bgm/打开游戏&排行榜&设置&开发人员.mp3", 0, 0, 0);
						return;
					}
					else
					{
						music_open = true;
						playBackgroundMusic("bgm/打开游戏&排行榜&设置&开发人员.mp3");
						return;
					}
				}

			}
		}
	}
}

/*
	负责人:牢胡
	功能:
	遍历账号文件,判断玩家的输入是否正确
	输入正确:调用Menu_screen()函数进入菜单

	输入错误:弹出账号或密码错误弹窗,如果玩家不点击弹窗中的确认则程序不动
	调用Login_screen();

*/
bool Login_is_successful()
{
	ifstream ifs;
	ifs.open("account.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return false;
	}

	char buf[20];
	int cnt = 1;
	bool id_is_true = false;
	bool pa_is_true = false;
	while (ifs >> buf) {
		if (cnt % 3 == 1) {
			if (!Me.uid.compare(buf))
				id_is_true = true;
		}
		else if (cnt % 3 == 2) {
			if (!Me.password.compare(buf))
				pa_is_true = true;
		}
		else if (cnt % 3 == 0) {
			Me.name = buf;
			if (id_is_true && pa_is_true) {
				return true;
			}
		}
		cnt++;
	}
	ifs.close();
	return false;
}



/*--------------------------------注册----------------------------------*/
/*
	负责人:牢胡
	功能:

	打印注册界面并绘制各种按键
	while(true)
	{
		接收用户鼠标消息
		判断用户是否点到按钮并调用该按钮的功能函数

		调用Registration_input(&msg);

		点击注册按钮:调用Registration_is_successful();
		点击返回:调用Login_screen()函数
	}



*/
void Registration_screen()
{
	
	putimage(0, 0, &img_Login_character);

	string name = "名称";
	string password = "密码";

	
	//设置打印样式
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "楷体");
	setfillcolor(WHITE);
	setlinecolor(RGB(100, 77, 77));

	//打印输入输出提示字及框
	
	outtextxy(260, 300, name.c_str());
	fillrectangle(260, 330, 540, 350);
	outtextxy(260, 370, password.c_str());
	fillrectangle(260, 400, 540, 420);
	settextstyle(20, 0, "黑体");
	outtextxy(0, 650, "按esc返回登录界面");
	Button su_Re(370, 500, 60, 20);
	su_Re.Creat_Button("注册", 12);
	ExMessage re_msg;
	Registration_input(re_msg, su_Re);
}

/*
	负责人:牢胡
	功能:
		接收一个消息指针,判断点击的位置
		当点击输入框时调出白框输入名称或密码(可先用全局变量保存)
		同时将用户输入打印到对应的输入框中

		参数:ExMessage* msg
		返回值:void
*/
void Registration_input(ExMessage& re_msg, Button su_Re)
{
	//设置两个bool检测是否输入了
	bool ac_is_input = false;
	bool pa_is_input = false;

	HWND hwd = GetHWnd();
	SetWindowText(hwd, "原神之王");

	while (1) {
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			flag = 0;
			return;
		}
		if (peekmessage(&re_msg, EM_MOUSE))
		{
			//两个输入，一个按钮
			switch (re_msg.message)
			{
				//按下左键
			case WM_LBUTTONDOWN:
				//账号输入
				if (re_msg.x >= 260 && re_msg.y >= 330 && re_msg.x <= 540 && re_msg.y <= 350) {
					char name[10];
					InputBox(name, 10, NULL, "请输入名称", NULL, 0, 0, true);
					string emp(name);
					Me.name = emp;
					if (!emp.empty())
						ac_is_input = true;
					//打印名称
					setbkcolor(WHITE);
					setbkmode(OPAQUE);
					fillrectangle(260, 330, 540, 350);
					outtextxy(262, 335, Me.name.c_str());
				}
				//密码输入
				else if (re_msg.x >= 260 && re_msg.y >= 400 && re_msg.x <= 540 && re_msg.y <= 420) {
					char ps[10];
					InputBox(ps, 9, "密码不超过8位", "请输入密码", NULL, 0, 0, true);
					string emp2(ps);
					Me.password = emp2;
					if (!emp2.empty())
						pa_is_input = true;
					//打印密码
					setbkcolor(WHITE);
					setbkmode(OPAQUE);
					fillrectangle(260, 400, 540, 420);
					outtextxy(262, 405, Me.password.c_str());
				}
				//注册
				else if (re_msg.x >= su_Re.B_x && re_msg.y >= su_Re.B_y && re_msg.x <= su_Re.B_x + su_Re.B_width && re_msg.y <= su_Re.B_y + su_Re.B_height) {

					//跳转到注册成功
					if (ac_is_input && pa_is_input)
					{
						
						flag = 2;
						return;
					}
					else
					{
						MessageBox(hwd, "请输入正确的名称和密码", "注册失败", MB_OK);
					}
				}
			}
		}
	}
}


/*
	负责人:牢胡
	功能:
		 判断玩家输入的名称和密码是否符合要求

		 符合要求
		 {
		 同时生成一个账号给用户
		 打印注册成功界面
		 并将玩家之前输入的名称、密码和生成的账号存入账号文件中

		 }
		 不符合要求则弹出注册失败窗口并return;
*/
void Registration_is_successful()
{
	//加载背景
	
	putimage(0, 0, &img_Registration_Victory_bk);

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(100000, 999999);
	int random_number = dis(gen);
	Me.uid = to_string(random_number);


	//
	string tips = "您的账号为：";
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, "楷体");
	outtextxy(100, 400, tips.c_str());
	outtextxy(120 + textwidth(tips.c_str()), 400, Me.uid.c_str());


	//将创建的账号写入本地文件
	add_Account();


	//按钮
	Button back_B(370, 500, 60, 20);
	back_B.Creat_Button("返回主界面", 12);

	ExMessage Suf_msg;
	while (1) {
		if (peekmessage(&Suf_msg, EM_MOUSE)) {
			switch (Suf_msg.message)
			{
			case WM_LBUTTONDOWN:
				//返回
				if (Suf_msg.x >= back_B.B_x && Suf_msg.y >= back_B.B_y && Suf_msg.x <= back_B.B_x + back_B.B_width && Suf_msg.y <= back_B.B_y + back_B.B_height) {
					flag = 0;
					return;
				}
			}
		}
	}

}


/*
	负责人:牢胡
	功能:
	创建的账号写入本地文件
*/
void add_Account()
{
	ofstream ofs;
	ofs.open("account.txt", ios::app);
	ofs << Me.uid << " " << Me.password << " " << Me.name << endl;
	ofs.close();
}


/*--------------------------------主菜单----------------------------------*/
/*
	负责人:晓酥
	功能:
	打印菜单界面并绘制各种按键
	while(true)
	{
		接收用户鼠标消息
		判断用户是否点到按钮并调用该按钮的功能函数

		点击开始游戏:调用Skin_selection_screen()
		点击排行榜:调用Leaderboard();
		点击开发人员简介:Developer_Profile();
		点击退出游戏:调用exit(0);退出游戏
	}
*/
void Menu_screen()
{
	//绘制背景图
	putimage(0, 0, &img_Login_character);

	//设置背景模式
	setbkmode(TRANSPARENT);

	//设置最上方按钮位置
	int x = 320;
	int y = 320;
	int w = 160;
	int h = 30;

	//设置颜色按钮填充颜色和文字颜色与样式
	setfillcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(0, 0, "微软雅黑");
	//绘制按钮和按钮中的文字
	solidrectangle(x, y, x + w, y + h);
	int hSpace = (w - textwidth("开始游戏")) / 2;
	int vSpace = (h - textheight("开始游戏")) / 2;
	outtextxy(x + hSpace, y + vSpace, "开始游戏");

	solidrectangle(x, y + 60, x + w, y + 60 + h);
	hSpace = (w - textwidth("排行榜")) / 2;
	vSpace = (h - textheight("排行榜")) / 2;
	outtextxy(x + hSpace, y + 60 + vSpace, "排行榜");

	solidrectangle(x, y + 60 * 2, x + w, y + 60 * 2 + h);
	hSpace = (w - textwidth("开发人员")) / 2;
	vSpace = (h - textheight("开发人员")) / 2;
	outtextxy(x + hSpace, y + 60 * 2 + vSpace, "开发人员");

	solidrectangle(x, y + 60 * 3, x + w, y + 60 * 3 + h);
	hSpace = (w - textwidth("退出游戏")) / 2;
	vSpace = (h - textheight("退出游戏")) / 2;
	outtextxy(x + hSpace, y + 60 * 3 + vSpace, "退出游戏");

	//音量
	if (music_open)
	{
		putimage_alpha(0, 630, &img_music_yes);
	}
	else
		putimage_alpha(0, 630, &img_music_no);

	FlushBatchDraw();
	clearBufferOnEscape();
	//接收玩家鼠标点击
	ExMessage msg = { 0 };
	while (true)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x > x && msg.x<x + w && msg.y>y && msg.y < y + h)//开始游戏
				{
					flag = 4;
					return;
				}
				else if (msg.x > x && msg.x<x + w && msg.y>y + 60 && msg.y < y + 60 + h)//排行榜
				{
					flag = 5;
					return;
				}
				else if (msg.x > x && msg.x<x + w && msg.y>y + 60 * 2 && msg.y < y + 60 * 2 + h)//开发人员
				{
					flag = 6;
					return;
				}
				else if (msg.x > 0 && msg.x < 50 && msg.y>630 && msg.y < 630 + 50)
				{
					if (music_open)
					{
						music_open = false;
						mciSendString("close bgm/打开游戏&排行榜&设置&开发人员.mp3", 0, 0, 0);
						return;
					}
					else
					{
						music_open = true;
						playBackgroundMusic("bgm/打开游戏&排行榜&设置&开发人员.mp3");
						return;
					}
				}
				else if (msg.x > x && msg.x<x + w && msg.y>y + 60 * 3 && msg.y < y + 60 * 3 + h)//退出游戏
				{
					exit(0);
				}
			}
		}
	}
}

/*
	负责人:小于
	功能:
	将全局变量map<int, vector<string>> m_Record;的数据根据原型图打印前5或前10条出来

	while(true)
	{
		判断用户是否有输入
		当用户输入esc时:调用Menu_screen();
	}
*/
void Leaderboard()
{

	//输入图片
	putimage(0, 0, &img_Leaderboard_bk);

	setbkmode(TRANSPARENT);//防止字体背景遮挡背景图片
	setcolor(BLACK); // 设置文本颜色为黑色  
	settextstyle(60, 60, "宋体"); // 设置字体大小和样式

	string text;
	text = "排行榜";
	outtextxy(230, 100, text.c_str());
	int text_x = 100;
	int text_y = 250;
	//我觉得下面代码是没问题的，可能就是上面图形化出问题了
	//循环输出前五的name和score
	settextstyle(20, 15, "宋体");
	multimap<int, string>::iterator j = m_Record.begin();
	for (int i = 0; i < 5; i++)
	{
		if (j == m_Record.end())
			break;
		string text_no = "No" + to_string(i + 1) + ".";
		string text_name = j->second;
		string text_score = to_string(j->first);
		outtextxy(text_x, text_y, text_no.c_str());
		outtextxy(text_x+100, text_y, text_name.c_str());
		outtextxy(text_x+400, text_y, text_score.c_str());
		text_y += 100;
		j++;
	}
	FlushBatchDraw();
	char input;
	// 等待用户按键盘ESC键退出排行榜界面回到主菜单 
	while (true)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			flag = 3;
			return;
		}
	}
}


/*
	负责人:吃茶
	功能:
	打印开发人员简介,具体界面看原型图

	while(true)
	{
		判断用户是否有输入
		当用户输入esc时:调用Menu_screen();
	}
*/
void Developer_Profile()
{
	putimage(0, 0, &img_Menu_kaifatandui_bk);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(25, 10, "宋体加粗");
	putimage(50, 150, &img_member[0]);
	outtextxy(50 + 80, 150 + 20, "组长：牢胡");
	putimage(300, 150, &img_member[1]);
	outtextxy(300 + 80, 150 + 20, "副组长：小于");
	putimage(550, 150, &img_member[2]);
	outtextxy(550 + 80, 150 + 20, "产品经理：吃茶");
	putimage(50, 350, &img_member[3]);
	outtextxy(50 + 80, 350 + 20, "信息官：汉明");
	putimage(300, 350, &img_member[4]);
	outtextxy(300 + 80, 350 + 20, "监督官：小7");
	putimage(550, 350, &img_member[5]);
	outtextxy(550 + 80, 350 + 20, "产品经理：晓酥");
	putimage(50, 550, &img_member[6]);
	outtextxy(50 + 80, 550 + 20, "技术官：启宇");
	putimage(300, 550, &img_member[7]);
	outtextxy(300 + 80, 550 + 20, "技术官：电饭煲");
	putimage(550, 550, &img_member[8]);
	outtextxy(550 + 80, 550 + 20, "特别鸣谢：");
	outtextxy(550 + 80, 550 + 40, "望仔小学长");
	outtextxy(2, 2, "按ESC键返回主菜单");
	FlushBatchDraw();
	char input;
	while (true)
	{
		
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			flag = 3;
			return;
		}
	}
}



/*--------------------------------游戏界面----------------------------------*/
/*
	负责人:吃茶
	功能:
	打印皮肤选择界面,具体根据原型图
	while(true)
	{
	接收用户鼠标消息和按键消息
	当用户点击选择皮肤按钮时,根据选择的皮肤改变玩家结构变量中的IMAGE,同时调用init();初始化游戏数据
	当用用户输入esc时调用Menu_screen();回到主菜单
	当用户输入enter是调用
	}
*/
void Skin_selection_screen()
{
	mciSendString("close bgm/打开游戏&排行榜&设置&开发人员.mp3", 0, 0, 0);
	playBackgroundMusic("bgm/角色选择&游戏内打怪.mp3");
	putimage(0, 0, &img_Leaderboard_bk);
	putimage_alpha(200, 590, &img_tutorial);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(25 * 4, 10 * 4, "宋体加粗");
	outtextxy(120, 60, "请选择你的角色");
	putimage(80, 200, &img_Skin_selection[0]);
	putimage(320, 200, &img_Skin_selection[1]);
	putimage(560, 200, &img_Skin_selection[2]);

	settextstyle(20, 0, "黑体");
	outtextxy(0, 700, "按esc返回主菜单界面");
	
	FlushBatchDraw();
	ExMessage msg = { 0 };
	char input;
	// 等待用户按键盘ESC键退出排行榜界面回到主菜单 
	
	
	while (true)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			mciSendString("close bgm/角色选择&游戏内打怪.mp3",0,0,0);
			playBackgroundMusic("bgm/打开游戏&排行榜&设置&开发人员.mp3");
			flag = 3;
			return;
		}
		//Me.hp = 100;
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if ((msg.x >= 80 && msg.x <= 80 + 50 * 3) && (msg.y >= 200 && msg.y <= 200 + 100 * 3))
				{
					Me.skin_number = 1;
					flag = 7;
					return;
				}
				if ((msg.x >= 320 && msg.x <= 320 + 50 * 3) && (msg.y >= 200 && msg.y <= 200 + 100 * 3))
				{
					Me.skin_number = 2;
					flag = 7;
					return;
				}
				if ((msg.x >= 560 && msg.x <= 560 + 50 * 3) && (msg.y >= 200 && msg.y <= 200 + 100 * 3))
				{
					Me.skin_number = 3;
					flag = 7;
					return;
				}
			}
		}
	}
}


/*
	负责人:电饭煲
	功能:游戏主循环

	while(true)
	{
		接收用户按键输入;

		调用Shoot_bullets(&msg);发射子弹
		调用Spawn_enemies();函数自动生成敌人

		调用封装好的玩家,敌人,子弹移动的函数Data_move(&msg);
		调用Game_screen();打印整个游戏界面()
		调用Game_time();打印剩余时间

		调用封装碰撞检测函数Collision_detection()


		调用is_win()函数判断游戏是否胜利(if语句)
		如返回true,调用Victory_screen()打印游戏胜利界面

		调用is_fail()函数判断游戏是否失败(if语句)
		如返回true,调用Failure_screen()打印游戏失败界面
	}
*/
void Play_the_game()
{
	ExMessage msg;//消息指针
	BeginBatchDraw();
	while (true)//主循环
	{
		DWORD start_time = GetTickCount();//开始时间
		static int count = 0;
		
		//时间越少,刷怪越快
		if (game_time <= 30)
		{
			Spawn = 25;
		}
		else if (game_time <= 60)
		{
			Spawn = 50;
		}
		else if (game_time <= 90)
		{
			Spawn = 60;
		}
		//刷新怪物
		if (count % Spawn == 0)
			Spawn_enemies();

		//数据移动整合
		Data_move();

		//发射子弹
		if (count % Me.cd == 0)
			Shoot_bullets();


		//时间
		if (count % 60 == 0)
			game_time -= 1;//char game_time='60';
		count++;


		//玩家动画帧
		static int counter = 0;
		counter++;
		if (counter % 10 == 0)
		{
			idx_currentanim++;
			idx_currentanim = idx_currentanim % player_anim_num;
		}
		

		//绘制画面
		cleardevice();

		Game_bk();//背景
		Game_time();//时间
		Collision_detection();//各种碰撞检测
		Game_player();//打印玩家
		Game_bullets();//打印子弹
		Game_enemies();//打印敌人
		Game_drops();//打印掉落物
		char input;
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			flag = 10;
			return;
		}

		FlushBatchDraw();


		if (is_win())
		{
			flag = 8;
			return;
		}
		if (is_fail())
		{
			flag = 9;
			return;
		}




		//动态延时--保证1秒执行60次主循环
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();
}




/*
	负责人:晓酥
	功能:
	打印游戏背景图和界面中的各种字和值

*/
void Game_bk()
{
	//输入图片
	putimage(0, 0, &img_play_game_bk);
	putimage_alpha(650, 60, &img_hp);
	
	//转化为字符串
	ostringstream scoreStream;
	scoreStream << Me.score;
	string scorestr = scoreStream.str();
	ostringstream playerhp;
	playerhp << Me.hp;
	string playerhpstr = playerhp.str();


	// 设置字体和颜色  
	setbkcolor(BLACK); // 背景为黑  
	setcolor(WHITE); // 字体颜色为白  
	settextstyle(20, 0, "黑体");

	// 在屏幕上绘制分数字符串  
	outtextxy(180, 702, scorestr.c_str());
	outtextxy(680, 65, playerhpstr.c_str());
}


/*
	负责人:汉明
	功能:
	打印界面中剩余的时间(可以是倒计时也可以是进度条)
*/
void Game_time()
{
	ostringstream TIME;
	TIME << game_time;
	string scorestr = TIME.str();
	// 设置字体和颜色  
	setbkcolor(BLACK); // 背景为黑  
	setcolor(WHITE); // 字体颜色为白  
	settextstyle(25, 0, "黑体");
	outtextxy(330,60 , scorestr.c_str());
}


/*
	负责人:汉明
	功能:
	根据玩家位置打印玩家
*/
void Game_player()
{
	if (Me.skin_number == 1)
	{
		if (Me.direct == 1)
			putimage_alpha(Me.x-16, Me.y-24, &img_player_1_up[idx_currentanim]);
		else if (Me.direct == 0)
			putimage_alpha(Me.x - 16, Me.y - 24, &img_player_1_down[idx_currentanim]);
		else if (Me.direct == 2)
			putimage_alpha(Me.x - 16, Me.y - 24, &img_player_1_left[idx_currentanim]);
		else if (Me.direct == 3)
			putimage_alpha(Me.x - 16, Me.y - 24, &img_player_1_right[idx_currentanim]);
	}
	else if (Me.skin_number == 2)
	{
		if (Me.direct == 1)
			putimage_alpha(Me.x - 16, Me.y - 24, &img_player_2_up[idx_currentanim]);
		else if (Me.direct == 0)
			putimage_alpha(Me.x - 16, Me.y - 24, &img_player_2_down[idx_currentanim]);
		else if (Me.direct == 2)
			putimage_alpha(Me.x - 16, Me.y - 24, &img_player_2_left[idx_currentanim]);
		else if (Me.direct == 3)
			putimage_alpha(Me.x - 16, Me.y - 24, &img_player_2_right[idx_currentanim]);
	}
	else if (Me.skin_number == 3)
	{
		if (Me.direct == 1)
			putimage_alpha(Me.x - 16, Me.y - 24, &img_player_3_up[idx_currentanim]);
		else if (Me.direct == 0)
			putimage_alpha(Me.x - 16, Me.y - 24, &img_player_3_down[idx_currentanim]);
		else if (Me.direct == 2)
			putimage_alpha(Me.x - 16, Me.y - 24, &img_player_3_left[idx_currentanim]);
		else if (Me.direct == 3)
			putimage_alpha(Me.x - 16, Me.y - 24, &img_player_3_right[idx_currentanim]);
	}

}

/*
	负责人:汉明
	功能:
	遍历子弹数组,当子弹存在时打印子弹
*/
void Game_bullets()
{
	for (size_t i = 0; i < 50; i++)
	{
		if (bullets[i].is_live)
		{
			putimage_alpha(bullets[i].x-14, bullets[i].y-14, &img_bullet);
		}
		
	}
}

/*
	负责人:电饭煲
	功能:
	遍历敌人数组,当敌人存在时打印敌人
*/
void Game_enemies()
{
	for (size_t i = 0; i < 20; i++)
	{
		if (enemies[i].is_live)
		{
			if(enemies[i].type==0)
				putimage_alpha(enemies[i].x-15, enemies[i].y-15, &img_Enemy_1[idx_currentanim]);
			else if(enemies[i].type == 1)
				putimage_alpha(enemies[i].x-20, enemies[i].y-20, &img_Enemy_2[idx_currentanim]);
			else if(enemies[i].type == 2)
				putimage_alpha(enemies[i].x-15, enemies[i].y-15, &img_Enemy_3[idx_currentanim]);
		}
	}
}


/*
	负责人:电饭煲
	功能:
	遍历掉落物数组,当掉落物存在时打印掉落物
*/
void Game_drops()
{
	for (size_t i = 0; i < 20; i++)
	{
		if (drops[i].is_live)
		{
			if (drops[i].type == 0)//血瓶
				putimage_alpha(drops[i].x - 16, drops[i].y - 16, &img_Drops[0]);
			else if (drops[i].type == 1)//鞋子
				putimage_alpha(drops[i].x - 16, drops[i].y - 16, &img_Drops[1]);
			else if (drops[i].type == 2)//cd
				putimage_alpha(drops[i].x - 16, drops[i].y - 16, &img_Drops[2]);
			else if (drops[i].type == 3)//luck
				putimage_alpha(drops[i].x - 16, drops[i].y - 16, &img_Drops[3]);
			else if (drops[i].type == 4)//score
				putimage_alpha(drops[i].x - 16, drops[i].y - 16, &img_Drops[4]);
		}
	}
}



/*
	负责人:小7
	功能:
	打印暂停界面

	while(true)
	{
		接收用户鼠标消息
		判断用户是否点到按钮并调用该按钮的功能函数

		点击到续游戏:调用Play_the_game()回到游戏主循环
		点击回到主菜单:
		先调用saveRecord()函数保存本局游戏分数
		再调用Menu_screen()函数回到主菜单
	}
*/
void Pause_the_game()
{
	mciSendString("close bgm/角色选择&游戏内打怪.mp3", 0, 0, 0);
	
	//输入图片
	putimage(0, 0, &img_Failure_bk);

	//绘制矩形
	//白色
	setfillcolor(WHITE);
	fillrectangle(150, 300, 650, 500);

	//显示文本
	// 设置文本颜色和字体（可选）  
	setbkcolor(WHITE); // 设置背景色为白色，这样文本背景就是透明的  
	setcolor(BLACK); // 设置文本颜色为黑色  
	settextstyle(30, 0, "微软雅黑"); // 设置字体大小和样式，这里使用的是20号黑体  


	// 计算矩形的中心点  
	int rect_width = 650 - 150; // 矩形的宽度  
	int rect_height = 500 - 300; // 矩形的高度  
	int rect_center_x = 150 + rect_width / 2; // 矩形中心的x坐标  
	int rect_center_y = 300 + rect_height / 2; // 矩形中心的y坐标  

	// 计算文本宽度和高度，以便正确居中  
	char text[] = "游戏已暂停";
	int text_width = textwidth(text);
	int text_height = textheight(text);

	// 在矩形中心输出文本  
	outtextxy(rect_center_x - text_width / 2, rect_center_y - text_height / 2 - 20, text);


	// 绘制按钮
	// / 定义按钮的位置和大小  
	const int BUTTON_WIDTH = 100;
	const int BUTTON_HEIGHT = 30;
	const int BUTTON_SPACING = 200; // 按钮之间的间距  
	const int BUTTON_TOP_MARGIN = -60; // 按钮距离矩形顶部的间距  
	const int CONTINUE_BUTTON_LEFT = (rect_width - BUTTON_WIDTH) / 2; // 继续游戏按钮左边界  
	const int BACK_BUTTON_LEFT = CONTINUE_BUTTON_LEFT + BUTTON_WIDTH + BUTTON_SPACING; // 回到主菜单按钮左边界  
	int button_top = rect_center_y + rect_height / 2 + BUTTON_TOP_MARGIN; // 按钮顶部位置  
	// 设置按钮的颜色  
	setfillcolor(LIGHTGRAY); // 浅灰色  
	setbkcolor(LIGHTGRAY); // 文本背景色与按钮颜色相同，实现透明效果  
	setcolor(WHITE); // 白色文本  
	settextstyle(16, 0, "微软雅黑"); // 字体大小和样式，这里使用16号黑体  

	// 绘制继续游戏按钮并显示文本  
	fillrectangle(CONTINUE_BUTTON_LEFT, button_top, CONTINUE_BUTTON_LEFT + BUTTON_WIDTH, button_top + BUTTON_HEIGHT);
	char continue_text[] = "继续游戏";
	int continue_text_width = textwidth(continue_text);
	int continue_text_height = textheight(continue_text);
	outtextxy(CONTINUE_BUTTON_LEFT + (BUTTON_WIDTH - continue_text_width) / 2,
		button_top + (BUTTON_HEIGHT - continue_text_height) / 2,
		continue_text);

	// 绘制回到主菜单按钮并显示文本  
	fillrectangle(BACK_BUTTON_LEFT, button_top, BACK_BUTTON_LEFT + BUTTON_WIDTH, button_top + BUTTON_HEIGHT);
	char back_text[] = "回到主菜单";
	int back_text_width = textwidth(back_text);
	int back_text_height = textheight(back_text);
	outtextxy(BACK_BUTTON_LEFT + (BUTTON_WIDTH - back_text_width) / 2,
		button_top + (BUTTON_HEIGHT - back_text_height) / 2,
		back_text);


	FlushBatchDraw();
	// 等待用户点击  
	ExMessage msg = { 0 };
		while (true)
		{
			// 如果没有键盘输入，则等待鼠标事件 
			if (peekmessage(&msg))
			{

				if (msg.message == WM_LBUTTONDOWN)
				{
					// 检查点击是否在“继续游戏”按钮上  
					if (msg.x >= CONTINUE_BUTTON_LEFT && msg.x <= CONTINUE_BUTTON_LEFT + BUTTON_WIDTH &&
						msg.y >= button_top && msg.y <= button_top + BUTTON_HEIGHT)
					{
						// 调用继续游戏的函数
						flag=11;   
						playBackgroundMusic("bgm/角色选择&游戏内打怪.mp3");
						break; // 退出循环  
					}
					// 检查点击是否在“返回主菜单”按钮上  
					else if (msg.x >= BACK_BUTTON_LEFT && msg.x <= BACK_BUTTON_LEFT + BUTTON_WIDTH &&
						msg.y >= button_top && msg.y <= button_top + BUTTON_HEIGHT)
					{
						playBackgroundMusic("bgm/打开游戏&排行榜&设置&开发人员.mp3");
						//保存分数
						saveRecord();
						flag = 3;
						return; // 调用返回主菜单的函数 
						//cout << "调用保存分数函数和主菜单函数" << endl << "回到主菜单" << endl;
					}
				}
			}
		}

}




/*
	负责人:小7
	功能:

	打印游戏失败界面

	调用saveRecord()函数保存本局游戏分数
	while(true)
	{
		接收用户鼠标消息
		判断用户是否点到按钮并调用该按钮的功能函数

		点击再来一局时:
		先调用init()函数初始化游戏数据
		再调用Play_the_game()函数回到游戏主循环

		点击回到主菜单:调用Menu_screen()函数回到主菜单

	}
*/
void Failure_screen()
{
	mciSendString("close bgm/角色选择&游戏内打怪.mp3", 0, 0, 0);
	playBackgroundMusic("bgm/失败.mp3");

	//先保存本局分数
	saveRecord();


	//输入图片
	putimage(0, 0, &img_Failure_bk);


	//显示文本
	setbkmode(TRANSPARENT);
	settextstyle(130, 0, "黑体"); // 设置字体大小和样式  

	//计算窗口的中心点
	int center_x = 800 / 2; // 矩形中心的x坐标  
	int center_y = 800 / 2; // 矩形中心的y坐标 
	// 计算文本宽度和高度，以便正确居中  
	char text1[] = " 菜就多练!";
	int text_width1 = textwidth(text1);
	int text_height1 = textheight(text1);
	//输出文字
	outtextxy(center_x - text_width1 / 2, center_y - text_height1 / 2 - 20, text1);

	//按钮
	// 假设按钮的宽度和高度  
	// 绘制按钮
	// 定义按钮的位置和大小  
	const int width = 200;
	const int height = 40;
	const int spaing = 200; // 按钮之间的间距  
	const int leftspacing = 100; // 再来一局按钮左边界  
	const int leftspacing1 = leftspacing + width + spaing; // 回到主菜单按钮左边界  
	int button_top1 = 600; // 按钮y  
	// 设置按钮的颜色  
	setfillcolor(LIGHTGRAY); // 浅灰色  
	setbkcolor(LIGHTGRAY); // 文本背景色与按钮颜色相同，实现透明效果  
	setcolor(WHITE); // 白色文本  
	settextstyle(14, 0, "黑体"); // 字体大小和样式  

	// 绘制继续游戏按钮并显示文本  
	fillrectangle(leftspacing, button_top1, leftspacing + width, button_top1 + height);
	char game_text[] = "我不服，再来一局";
	int game_text_width = textwidth(game_text);
	int game_text_height = textheight(game_text);
	outtextxy(leftspacing + (width - game_text_width) / 2,
		button_top1 + (height - game_text_height) / 2,
		game_text);

	// 绘制回到主菜单按钮并显示文本  
	fillrectangle(leftspacing1, button_top1, leftspacing1 + width, button_top1 + height);
	char back_text1[] = "回到主菜单";
	int back_text_width1 = textwidth(back_text1);
	int back_text_height1 = textheight(back_text1);
	outtextxy(leftspacing1 + (width - back_text_width1) / 2,
		button_top1 + (height - back_text_height1) / 2,
		back_text1);

	FlushBatchDraw();
	// 等待用户点击  
	while (true)
	{
		MOUSEMSG m;
		while (!_kbhit())
		{
			// 如果没有键盘输入，则等待鼠标事件 
			if (MouseHit())
			{
				m = GetMouseMsg();
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					// 检查点击是否在“继续游戏”按钮上  
					if (m.x >= leftspacing && m.x <= leftspacing + width &&
						m.y >= button_top1 && m.y <= button_top1 + height)
					{
						mciSendString("close bgm/失败.mp3", 0, 0, 0);
						playBackgroundMusic("bgm/角色选择&游戏内打怪.mp3");
						//调用init()函数初始化游戏数据
						init();
						flag = 7;
						return;

					}
					// 检查点击是否在“返回主菜单”按钮上  
					else if (m.x >= leftspacing1 && m.x <= leftspacing1 + width &&
						m.y >= button_top1 && m.y <= button_top1 + height)
					{
						mciSendString("close bgm/失败.mp3", 0, 0, 0);
						playBackgroundMusic("bgm/打开游戏&排行榜&设置&开发人员.mp3");
						flag = 3;
						return;
						
					}

				}
			}
		}
	}
}



/*
	负责人:小7
	功能:

	打印游戏胜利界面

	调用saveRecord()函数保存本局游戏分数
	while(true)
	{

		接收用户鼠标消息
		判断用户是否点到按钮并调用该按钮的功能函数

		点击回到主菜单:调用Menu_screen()函数回到主菜单
	}
*/
void Victory_screen()
{
	mciSendString("close bgm/角色选择&游戏内打怪.mp3", 0, 0, 0);
	playBackgroundMusic("bgm/胜利.mp3");
	//先保存本局分数
	saveRecord();

	//输入图片
	putimage(0, 0, &img_Victory_bk);


	//显示文本
	setcolor(BLACK); // 黑色文本 
	settextstyle(150, 0, "黑体"); // 设置字体大小和样式  

	//计算窗口的中心点
	int center_x1 = 800 / 2; // 矩形中心的x坐标  
	int center_y1 = 800 / 2; // 矩形中心的y坐标 
	// 计算文本宽度和高度，以便正确居中  
	char text2[] = " 胜利!";
	int text_width2 = textwidth(text2);
	int text_height2 = textheight(text2);
	//输出文字
	outtextxy(center_x1 - text_width2 / 2, center_y1 - text_height2 / 2 - 20, text2);

	//按钮
	// 假设按钮的宽度和高度  
	// 绘制按钮
	// 定义按钮的位置和大小  
	const int width1 = 200;
	const int height1 = 50;
	const int leftspacing2 = 300; // 回到主菜单按钮左边界    
	int button_top2 = 550; // 按钮y  
	// 设置按钮的颜色  
	setfillcolor(LIGHTGRAY); // 浅灰色  
	setbkcolor(LIGHTGRAY); // 文本背景色与按钮颜色相同，实现透明效果  
	setcolor(BLACK); // 白色文本  
	settextstyle(14, 0, "黑体"); // 字体大小和样式  

	// 绘制回到主菜单按钮并显示文本  
	fillrectangle(leftspacing2, button_top2, leftspacing2 + width1, button_top2 + height1);
	char back_text2[] = "回到主菜单";
	int back_text_width2 = textwidth(back_text2);
	int back_text_height2 = textheight(back_text2);
	outtextxy(leftspacing2 + (width1 - back_text_width2) / 2,
		button_top2 + (height1 - back_text_height2) / 2,
		back_text2);

	FlushBatchDraw();
	ExMessage msg = { 0 };
	// 等待用户点击  
	while (true)
	{
		if (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				// 检查点击是否在“返回主菜单”按钮上  
				if (msg.x >= leftspacing2 && msg.x <= leftspacing2 + width1 &&
					msg.y >= button_top2 && msg.y <= button_top2 + height1)
				{
					mciSendString("close bgm/胜利.mp3", 0, 0, 0);
					playBackgroundMusic("bgm/打开游戏&排行榜&设置&开发人员.mp3");
					flag = 3;
					return;
				}

			}
		}
	}
	
}