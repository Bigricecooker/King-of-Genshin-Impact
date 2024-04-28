#include "serve.h"
using namespace std;



/*
	������:�緹��
	����:��ջ��������ESC
*/
void clearBufferOnEscape()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // ����Ƿ����� ESC ��
		while (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // ��ռ��̻�����
			;
	}
	ExMessage msg;
	while (peekmessage(&msg));
}


/*
	������:�緹��
	����:��������
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
			//��ȡһ�´�����Ϣ
			char err[100] = { 0 };
			mciGetErrorString(ret, err, sizeof(err));
			printf("oper: %s", err);
		}

		sprintf_s(cmd, "play %s repeat", music);
		mciSendString(cmd, NULL, 0, NULL);//���Ҫ�ظ��������ټ�һ��repeat
	}
}

/*
	������:�緹��
	����
		�������min��max֮�����

		����:int min, int max
		����ֵ:int
*/
int getRandomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}



/*
	������:�緹��
	����:
	��������ͼƬ
*/
void loadImgResource()
{
	loadimage(&img_Login,"img/BK/����.png" );
	loadimage(&img_Login_character,"img/BK/����������.png");
	loadimage(&img_Registration_Victory_bk, "img/BK/ע��ɹ�.png");
	loadimage(&img_Menu_kaifatandui_bk,"img/BK/������Ա��������ͼ.png",800,800);
	loadimage(&img_member[0], "img/ͷ��/�κ�.jpg", 70, 70);
	loadimage(&img_member[1], "img/ͷ��/С��.jpg", 70, 70);
	loadimage(&img_member[2], "img/ͷ��/�Բ�.jpg", 70, 70);
	loadimage(&img_member[3], "img/ͷ��/����.jpg", 70, 70);
	loadimage(&img_member[4], "img/ͷ��/С7.jpg", 70, 70);
	loadimage(&img_member[5], "img/ͷ��/����.jpg", 70, 70);
	loadimage(&img_member[6], "img/ͷ��/����.jpg", 70, 70);
	loadimage(&img_member[7], "img/ͷ��/�緹��.jpg", 70, 70);
	loadimage(&img_member[8], "img/ͷ��/ѧ��.jpg", 70, 70);
	loadimage(&img_Leaderboard_bk,"img/BK/Ƥ��ѡ����汳��ͼ.png",800,800);
	loadimage(&img_Leaderboard_bk, "img/BK/���а�.png",800,800);
	loadimage(&img_play_game_bk, "img/BK/��ͼ.png");
	loadimage(&img_Skin_selection[0], "img/Ƥ��/anbo.jpg", 50 * 3, 100 * 3);
	loadimage(&img_Skin_selection[1], "img/Ƥ��/ganyu.jpg", 50 * 3, 100 * 3);
	loadimage(&img_Skin_selection[2], "img/Ƥ��/xiangling.jpg", 50 * 3, 100 * 3);
	loadimage(&img_hp, "img/BK/Ѫ��.png");
	loadimage(&img_music_no,"img/BK/����.png",50,50);
	loadimage(&img_music_yes, "img/BK/����.png",50,50);

	//��ɫ1
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


	//��ɫ2
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



	//��ɫ3
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

	loadimage(&img_Enemy_1[0], "img/С��/img1.png");
	loadimage(&img_Enemy_1[1], "img/С��/img2.png");
	loadimage(&img_Enemy_1[2], "img/С��/img3.png");
	loadimage(&img_Enemy_1[3], "img/С��/img4.png");
	loadimage(&img_Enemy_3[0], "img/С��/img6.png",40,40);
	loadimage(&img_Enemy_3[1], "img/С��/img7.png", 40, 40);
	loadimage(&img_Enemy_3[2], "img/С��/img8.png", 40, 40);
	loadimage(&img_Enemy_3[3], "img/С��/img9.png", 40, 40);
	loadimage(&img_Enemy_2[0], "img/С��/img10.png");
	loadimage(&img_Enemy_2[1], "img/С��/img11.png");
	loadimage(&img_Enemy_2[2], "img/С��/img12.png");
	loadimage(&img_Enemy_2[3], "img/С��/img13.png");

	//����
	loadimage(&img_Drops[0], "img/����/hp.png");
	loadimage(&img_Drops[1], "img/����/speed.png");
	loadimage(&img_Drops[2], "img/����/cd.png");
	loadimage(&img_Drops[3], "img/����/luck.png");
	loadimage(&img_Drops[4], "img/����/200.png");

	loadimage(&img_bullet, "img/bullet.png",28,28);
	loadimage(&img_Failure_bk,"img/BK/ʧ��.png");
	loadimage(&img_Victory_bk,"img/BK/ʤ��.png" );
	loadimage(&img_Pause_the_game_bk,"img/BK/��ͣ.png" );
	loadimage(&img_tutorial, "img/BK/�̳�.png");
}


/*
	������:С��
	����:
	��֮ǰ�ļ�¼������һ��multimap<int, vector<string>> m_Record;��ȫ�ֱ�����(����,����),ͬʱʹ�併������
	�ú��������ƺ���c++���ݽ���������ϵͳ�е�һ������
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
		//���ֺͷ����Ƿ����д��

		getline(score_file, s_score);//��ȡ��һ�н����ŵĸ��û��ķ���
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
	������:С��
	����:
	����Ϸ����,�������һ����뱣����Ϸ�������ļ���
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
	������:�緹��
	����:
		��ʼ���������

		��ʼ����������
		(�����˽ṹ�����еĵ��˽ṹԪ�ص�is_liveȫ����ʼ��Ϊfalse(��������Ӧ�ò���))
		��ʼ���ӵ�����
		(�͵���һ��)
		��ʼ������������
*/
void init()
{
	Spawn = 80;
	game_time = 120;
	//���
	Me.hp = 100;
	Me.is_live = true;
	Me.score = 0;
	Me.cd = 15;
	Me.size = 15;
	Me.speed = 3;
	Me.x = 400;
	Me.y = 400;
	Me.luck = 9;

	//��������
	for (size_t i = 0; i < 20; i++)
	{
		enemies[i].is_live = false;
	}

	//�ӵ�����
	for (size_t i = 0; i < 50; i++)
	{
		bullets[i].is_live = false;
		bullets[i].attack = 20;
		bullets[i].speed = 6;
		bullets[i].size = 14;
		bullets[i].angle = -1;
	}

	//����������
	for (size_t i = 0; i < 20; i++)
	{
		drops[i].is_live = false;
		drops[i].size = 16;
	}
}


/*
	������:�緹��
	����:

	����һ����Ϣ����
	����Ϣ����Ϊ�������ҵ�8�����򰴼�ʱ�����ӵ�����
	�����ӵ�is_live==falseʱ�����Ϊtrue,��Ϊ���ӵ���ʼ��(������˵��ߵĻ���һ��,Ӧ�ÿ���Ū����ȫ�ֱ���,������һ��)


	����:ExMessage*
	����ֵ:void
*/
void Shoot_bullets()
{
	
	if (GetAsyncKeyState(VK_UP) )
	{
		if (GetAsyncKeyState(VK_LEFT))//����
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
		else if (GetAsyncKeyState(VK_RIGHT))//����
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
		else//��
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
		if (GetAsyncKeyState(VK_LEFT))//����
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
		else if (GetAsyncKeyState(VK_RIGHT))//����
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
		else//��
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
	else if (GetAsyncKeyState(VK_LEFT))//��
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
	else if (GetAsyncKeyState(VK_RIGHT) )//��
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
	������:�緹��
	����:
	������������,���õ���is_live==falseʱ�����Ϊtrue,��������������������ͺ�����λ��(4������)
*/
void Spawn_enemies()
{
	for (size_t i = 0; i < 20; i++)
	{
		if (!enemies[i].is_live)
		{

			enemies[i].is_live = true;
			int random_1 = getRandomNumber(0, 3);//���ɷ���
			enemies[i].type = getRandomNumber(0, 2);//��������
			if(!drops[i].is_live)
				enemies[i].drop= getRandomNumber(0, 4);//����ĵ�������
			if (random_1 == 0)//��
			{
				enemies[i].x = getRandomNumber(350, 450);//400
				enemies[i].y = 120;
				if (enemies[i].type == 0)//��ͨ
				{
					enemies[i].hp = 20;
					enemies[i].speed = 3;
					enemies[i].score = 20;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 1)//����
				{
					enemies[i].hp = 20;
					enemies[i].speed = 5;
					enemies[i].score = 30;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 2)//Ѫ��
				{
					enemies[i].hp = 60;
					enemies[i].speed = 2;
					enemies[i].score = 50;
					enemies[i].size = 20;
					return;
				}
			}
			else if (random_1 == 1)//��
			{
				enemies[i].x = getRandomNumber(350, 450);//400
				enemies[i].y = 680;
				if (enemies[i].type == 0)//��ͨ
				{
					enemies[i].hp = 20;
					enemies[i].speed = 3;
					enemies[i].score = 20;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 1)//����
				{
					enemies[i].hp = 20;
					enemies[i].speed = 5;
					enemies[i].score = 30;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 2)//Ѫ��
				{
					enemies[i].hp = 60;
					enemies[i].speed = 2;
					enemies[i].score = 50;
					enemies[i].size = 20;
					return;
				}
			}
			else if (random_1 == 2)//��
			{
				enemies[i].x = 120;
				enemies[i].y = getRandomNumber(350, 450);//400
				if (enemies[i].type == 0)//��ͨ
				{
					enemies[i].hp = 20;
					enemies[i].speed = 3;
					enemies[i].score = 20;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 1)//����
				{
					enemies[i].hp = 20;
					enemies[i].speed = 5;
					enemies[i].score = 30;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 2)//Ѫ��
				{
					enemies[i].hp = 60;
					enemies[i].speed = 2;
					enemies[i].score = 50;
					enemies[i].size = 20;
					return;
				}
			}
			else if (random_1 == 3)//��
			{
				enemies[i].x = 680;
				enemies[i].y = getRandomNumber(350, 450);//400
				if (enemies[i].type == 0)//��ͨ
				{
					enemies[i].hp = 20;
					enemies[i].speed = 3;
					enemies[i].score = 20;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 1)//����
				{
					enemies[i].hp = 20;
					enemies[i].speed = 5;
					enemies[i].score = 30;
					enemies[i].size = 15;
					return;
				}
				else if (enemies[i].type == 2)//Ѫ��
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
	������:�緹��
	����:��װ���,�ӵ�,�����ƶ������ĺ���

	����:ExMessage*
	����ֵ:void
*/
void Data_move()
{
	player_move();
	bullets_move();
	enemies_move();
}



/*
	������:�緹��
	����:
	����һ����Ϣ����
	������Ϣ����Ϊ����wasd��ʱ�ֱ�is_move_�����⼸��bool���͵�ȫ�ֱ�����Ϊtrue
	������Ϣ����Ϊ�ɿ�����ʱ���±�Ϊfalse

	�ֱ��ж�4�������Ƿ�Ϊtrue
	���Ϊ��,��ı��������
	��:if (is_move_up) Me.y -= Me.speed;()
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
	������:�緹��
	����:

	�����ӵ�����,����ÿ�����ڵ��ӵ��ĽǶȺͷ���ı���ӵ�������
*/
void bullets_move()
{
	for (size_t i = 0; i < 50; i++)
	{
		if (bullets[i].is_live)
		{
			if (bullets[i].angle == 8)//8Ϊ��
				bullets[i].y -= bullets[i].speed;
			else if (bullets[i].angle == 2)//2Ϊ��
				bullets[i].y += bullets[i].speed;
			else if (bullets[i].angle == 4)//4Ϊ��
				bullets[i].x -= bullets[i].speed;
			else if (bullets[i].angle == 6)//6Ϊ��
				bullets[i].x += bullets[i].speed;
			else if (bullets[i].angle == 7)//7Ϊ����
			{
				bullets[i].x -= (bullets[i].speed / 1.4);
				bullets[i].y -= (bullets[i].speed / 1.4);
			}
			else if (bullets[i].angle == 1)//1Ϊ����
			{
				bullets[i].x -= (bullets[i].speed / 1.4);
				bullets[i].y += (bullets[i].speed / 1.4);
			}
			else if (bullets[i].angle == 9)//9Ϊ����
			{
				bullets[i].x += (bullets[i].speed / 1.4);
				bullets[i].y -= (bullets[i].speed / 1.4);
			}
			else if (bullets[i].angle == 3)//3Ϊ����
			{
				bullets[i].x += (bullets[i].speed/1.4);
				bullets[i].y +=(bullets[i].speed/1.4);
			}
		}
	}
}


/*
	������:�κ�
	����:
	������������,������ҵ��������ı�ÿ�����ڵĵ��˵�����ֵ

	����:ˮƽ����ĵ�������ˮƽ�ӽ����,��������ֵĵ�����������ӽ����
*/
void enemies_move()
{
	for (size_t i = 0; i < 20; i++)
	{
		// ����������
		if (enemies[i].is_live) {
			// ��������֮��ľ��루б�ߣ�
			int dx = Me.x - enemies[i].x;
			int dy = Me.y - enemies[i].y;
			int distance = sqrt(dx * dx + dy * dy);

			// ������벻Ϊ0��������������ı仯��
			if (distance != 0) {
				// ���� x ����ı仯��
				double delta_x = enemies[i].speed * dx / distance;
				// ���� y ����ı仯��
				double delta_y = enemies[i].speed * dy / distance;
				// ����λ��
				enemies[i].x += delta_x;
				enemies[i].y += delta_y;
			}
		}
	}

}



/*
	������:�緹��
	����:
	��װ������ײ���
*/
void Collision_detection()
{
	player_with_enemies();
	enemies_with_bullets();
	bullets_with_boundary();
	player_whit_drops();
}

/*
	������:�緹��
	����:
	����������Ĵ���
*/
void player_whit_drops()
{
	for (size_t i = 0; i < 20; i++)
	{
		if (drops[i].is_live)
		{
			if ((Me.x - drops[i].x) * (Me.x - drops[i].x) + (Me.y - drops[i].y) * (Me.y - drops[i].y) <= (Me.size + drops[i].size) * (Me.size + drops[i].size))
			{
				PlaySound("bgm/����.wav", NULL, SND_FILENAME | SND_ASYNC);
				drops[i].is_live = false;
				if (drops[i].type == 0)//Ѫƿ
				{
					if (Me.hp > 60)
						Me.hp = 100;
					else
						Me.hp += 40;
				}
				else if (drops[i].type == 1)//Ь��
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
	������:����
	����:
		������������
		�ж�ÿһ����������ҵ�λ�ù�ϵ
		����������˵��������С�ڰ뾶֮��
		��۳������Ӧ��Ѫ��,�Ҹõ���ֱ������(����enemies[i].is_live=false)��Ϊ��Ҽ��϶�Ӧ�ķ���
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
	������:����
	����:
	�жϵ�������ҷ�����ӵ��Ƿ���ײ
	�緢����ײ,����ӵ���ʧ,�õ��˼��ٶ�Ӧ��Ѫ�����жϵ����Ƿ�����
	��õ�������,��ͬʱΪ��Ҽ��϶�Ӧ�ķ���
*/
void enemies_with_bullets()
{
	//�ӵ�������Ƿ���ײ���
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


							if (getRandomNumber(0, Me.luck) == 5)//ʮ��֮һ�ĸ��ʵ���
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
	������:����
	����:
	�����ӵ�����,�ж��ӵ��Ƿ񳬳��߽�
	�糬���˱߽�����ӵ���ʧ

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
	������:С��
	����:
	����Ϸʱ��Ϊ0ʱ����true
	���򷵻�false

	����:void
	����ֵ:bool
*/
bool is_win()
{
	if (game_time <=0)
		return true;
	return false;
}


/*
	������:С��
	����:
	�����Ѫ��С�ڵ���0ʱ����true
	���򷵻�false

	����:void
	����ֵ:bool
*/
bool is_fail()
{
	if (Me.hp <= 0)
		return true;
	return false;
}