#include "view.h"
#include "serve.h"



inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

/*--------------------------------��¼----------------------------------*/
/*
	������:�κ�
	����:

	��ӡ��¼���沢���Ƹ��ְ���

	while(true)
	{
		�����û������Ϣ
		�ж��û��Ƿ�㵽��ť�����øð�ť�Ĺ��ܺ���

		����Login_input(&msg);

		�����¼:����Login_is_successful()
		���ע�����˺�:����Registration_screen()
		����˳���Ϸ,����exit(0);�˳���Ϸ
	}
	����:void
	����ֵ:void

*/
void Login_screen()
{
	BeginBatchDraw();
	//�޸Ĵ��ڱ���
	HWND hwd = GetHWnd();
	SetWindowText(hwd, "ԭ��֮��");

	putimage(0, 0, &img_Login_character);
	string ac_text = "�˺�";
	string pw_text = "����";

	//���ô�ӡ��ʽ
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "����");
	setfillcolor(WHITE);
	setlinecolor(RGB(100, 77, 77));

	//��ӡ���������ʾ�ּ���
	outtextxy(260, 300, ac_text.c_str());
	fillrectangle(260, 330, 540, 350);
	outtextxy(260, 370, pw_text.c_str());
	fillrectangle(260, 400, 540, 420);

	//������ť

	Button RB(260, 480, 60, 20);//Register_Button
	RB.Creat_Button("ע�����˺�", 12);
	Button LB(370, 480, 60, 20);//Login_Button
	LB.Creat_Button("��¼", 12);
	Button EB(480, 480, 60, 20);//Exit_Button
	EB.Creat_Button("�˳���Ϸ", 12);

	if (music_open)
	{
		putimage_alpha(0, 630, &img_music_yes);
	}
	else
		putimage_alpha(0, 630, &img_music_no);
	EndBatchDraw();
	//�߼��ж� -- ���������Ϣ

	ExMessage Login_msg;
	Login_input(Login_msg, LB, EB, RB, hwd);

}



/*
	������:�κ�
	����:
	����һ����Ϣָ��, �жϵ����λ��
	����������ʱ�����׿��������ƻ�����(������ȫ�ֱ�������)
	ͬʱ���û������ӡ����Ӧ���������

	���� : ExMessage * msg
	����ֵ : void
*/
void Login_input(ExMessage& Login_msg, Button& LB, Button& EB, Button& RB, HWND& hwd)
{
	//��ʼ����������߼��ж�
	Me.uid = "0";
	Me.password = "0";
	bool ac_is_input = false;
	bool ps_is_input = false;

	while (1) {

		
		if (peekmessage(&Login_msg, EM_MOUSE))
		{
			switch (Login_msg.message)
			{
				//���������
			case WM_LBUTTONDOWN:
				//��������������룬������ť
				//�˺�����
				if (Login_msg.x >= 260 && Login_msg.y >= 330 && Login_msg.x <= 540 && Login_msg.y <= 350) {
					char ac[10];
					InputBox(ac, 10, "�������˺�", "��ʾ", NULL, 0, 0, true);
					string emp(ac);
					Me.uid = emp;
					if (Me.uid.compare("0")) {
						ac_is_input = true;
					}
					//��ӡ�˺�
					setbkcolor(WHITE);
					setbkmode(OPAQUE);
					fillrectangle(260, 330, 540, 350);
					outtextxy(262, 335, Me.uid.c_str());
				}
				//��������
				else if (Login_msg.x >= 260 && Login_msg.y >= 400 && Login_msg.x <= 540 && Login_msg.y <= 420) {
					char ps[10];
					InputBox(ps, 9, "���������루���벻����8λ��", "��ʾ", NULL, 0, 0, true);
					string emp(ps);
					Me.password = emp;
					if (Me.password.compare("0")) {
						ps_is_input = true;
					}
					//��ӡ����
					setbkcolor(WHITE);
					setbkmode(OPAQUE);
					fillrectangle(260, 400, 540, 420);
					outtextxy(262, 405, Me.password.c_str());
				}
				//��¼
				else if (Login_msg.x >= LB.B_x && Login_msg.y >= LB.B_y && Login_msg.x <= LB.B_x + LB.B_width && Login_msg.y <= LB.B_y + LB.B_height) 
				{
					//��¼

					if (!ac_is_input) {
						MessageBox(hwd, "�������˺�", "��ʾ", MB_OK);
					}
					else if (!ps_is_input) {
						MessageBox(hwd, "����������", "��ʾ", MB_OK);
					}
					else if (!ac_is_input && !ps_is_input) {
						MessageBox(hwd, "�������˺�����", "��ʾ", MB_OK);
					}
					else {
						if (Login_is_successful()) 
						{
							flag = 3;
							return;
						}
						else {
							MessageBox(hwd, "�˺�������������������", "��ʾ", MB_OK);
						}
					}

				}
				//�˳���Ϸ
				else if (Login_msg.x >= EB.B_x && Login_msg.y >= EB.B_y && Login_msg.x <= EB.B_x + EB.B_width && Login_msg.y <= EB.B_y + EB.B_height) {
					exit(0);
				}
				//ע��
				else if (Login_msg.x >= RB.B_x && Login_msg.y >= RB.B_y && Login_msg.x <= RB.B_x + RB.B_width && Login_msg.y <= RB.B_y + RB.B_height) {
					flag=1;
					return;
				}
				else if (Login_msg.x > 0 && Login_msg.x < 50 && Login_msg.y>630 && Login_msg.y < 630 + 50)
				{
					if (music_open)
					{
						music_open = false;
						mciSendString("close bgm/����Ϸ&���а�&����&������Ա.mp3", 0, 0, 0);
						return;
					}
					else
					{
						music_open = true;
						playBackgroundMusic("bgm/����Ϸ&���а�&����&������Ա.mp3");
						return;
					}
				}

			}
		}
	}
}

/*
	������:�κ�
	����:
	�����˺��ļ�,�ж���ҵ������Ƿ���ȷ
	������ȷ:����Menu_screen()��������˵�

	�������:�����˺Ż�������󵯴�,�����Ҳ���������е�ȷ������򲻶�
	����Login_screen();

*/
bool Login_is_successful()
{
	ifstream ifs;
	ifs.open("account.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
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



/*--------------------------------ע��----------------------------------*/
/*
	������:�κ�
	����:

	��ӡע����沢���Ƹ��ְ���
	while(true)
	{
		�����û������Ϣ
		�ж��û��Ƿ�㵽��ť�����øð�ť�Ĺ��ܺ���

		����Registration_input(&msg);

		���ע�ᰴť:����Registration_is_successful();
		�������:����Login_screen()����
	}



*/
void Registration_screen()
{
	
	putimage(0, 0, &img_Login_character);

	string name = "����";
	string password = "����";

	
	//���ô�ӡ��ʽ
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "����");
	setfillcolor(WHITE);
	setlinecolor(RGB(100, 77, 77));

	//��ӡ���������ʾ�ּ���
	
	outtextxy(260, 300, name.c_str());
	fillrectangle(260, 330, 540, 350);
	outtextxy(260, 370, password.c_str());
	fillrectangle(260, 400, 540, 420);
	settextstyle(20, 0, "����");
	outtextxy(0, 650, "��esc���ص�¼����");
	Button su_Re(370, 500, 60, 20);
	su_Re.Creat_Button("ע��", 12);
	ExMessage re_msg;
	Registration_input(re_msg, su_Re);
}

/*
	������:�κ�
	����:
		����һ����Ϣָ��,�жϵ����λ��
		����������ʱ�����׿��������ƻ�����(������ȫ�ֱ�������)
		ͬʱ���û������ӡ����Ӧ���������

		����:ExMessage* msg
		����ֵ:void
*/
void Registration_input(ExMessage& re_msg, Button su_Re)
{
	//��������bool����Ƿ�������
	bool ac_is_input = false;
	bool pa_is_input = false;

	HWND hwd = GetHWnd();
	SetWindowText(hwd, "ԭ��֮��");

	while (1) {
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			flag = 0;
			return;
		}
		if (peekmessage(&re_msg, EM_MOUSE))
		{
			//�������룬һ����ť
			switch (re_msg.message)
			{
				//�������
			case WM_LBUTTONDOWN:
				//�˺�����
				if (re_msg.x >= 260 && re_msg.y >= 330 && re_msg.x <= 540 && re_msg.y <= 350) {
					char name[10];
					InputBox(name, 10, NULL, "����������", NULL, 0, 0, true);
					string emp(name);
					Me.name = emp;
					if (!emp.empty())
						ac_is_input = true;
					//��ӡ����
					setbkcolor(WHITE);
					setbkmode(OPAQUE);
					fillrectangle(260, 330, 540, 350);
					outtextxy(262, 335, Me.name.c_str());
				}
				//��������
				else if (re_msg.x >= 260 && re_msg.y >= 400 && re_msg.x <= 540 && re_msg.y <= 420) {
					char ps[10];
					InputBox(ps, 9, "���벻����8λ", "����������", NULL, 0, 0, true);
					string emp2(ps);
					Me.password = emp2;
					if (!emp2.empty())
						pa_is_input = true;
					//��ӡ����
					setbkcolor(WHITE);
					setbkmode(OPAQUE);
					fillrectangle(260, 400, 540, 420);
					outtextxy(262, 405, Me.password.c_str());
				}
				//ע��
				else if (re_msg.x >= su_Re.B_x && re_msg.y >= su_Re.B_y && re_msg.x <= su_Re.B_x + su_Re.B_width && re_msg.y <= su_Re.B_y + su_Re.B_height) {

					//��ת��ע��ɹ�
					if (ac_is_input && pa_is_input)
					{
						
						flag = 2;
						return;
					}
					else
					{
						MessageBox(hwd, "��������ȷ�����ƺ�����", "ע��ʧ��", MB_OK);
					}
				}
			}
		}
	}
}


/*
	������:�κ�
	����:
		 �ж������������ƺ������Ƿ����Ҫ��

		 ����Ҫ��
		 {
		 ͬʱ����һ���˺Ÿ��û�
		 ��ӡע��ɹ�����
		 �������֮ǰ��������ơ���������ɵ��˺Ŵ����˺��ļ���

		 }
		 ������Ҫ���򵯳�ע��ʧ�ܴ��ڲ�return;
*/
void Registration_is_successful()
{
	//���ر���
	
	putimage(0, 0, &img_Registration_Victory_bk);

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(100000, 999999);
	int random_number = dis(gen);
	Me.uid = to_string(random_number);


	//
	string tips = "�����˺�Ϊ��";
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, "����");
	outtextxy(100, 400, tips.c_str());
	outtextxy(120 + textwidth(tips.c_str()), 400, Me.uid.c_str());


	//���������˺�д�뱾���ļ�
	add_Account();


	//��ť
	Button back_B(370, 500, 60, 20);
	back_B.Creat_Button("����������", 12);

	ExMessage Suf_msg;
	while (1) {
		if (peekmessage(&Suf_msg, EM_MOUSE)) {
			switch (Suf_msg.message)
			{
			case WM_LBUTTONDOWN:
				//����
				if (Suf_msg.x >= back_B.B_x && Suf_msg.y >= back_B.B_y && Suf_msg.x <= back_B.B_x + back_B.B_width && Suf_msg.y <= back_B.B_y + back_B.B_height) {
					flag = 0;
					return;
				}
			}
		}
	}

}


/*
	������:�κ�
	����:
	�������˺�д�뱾���ļ�
*/
void add_Account()
{
	ofstream ofs;
	ofs.open("account.txt", ios::app);
	ofs << Me.uid << " " << Me.password << " " << Me.name << endl;
	ofs.close();
}


/*--------------------------------���˵�----------------------------------*/
/*
	������:����
	����:
	��ӡ�˵����沢���Ƹ��ְ���
	while(true)
	{
		�����û������Ϣ
		�ж��û��Ƿ�㵽��ť�����øð�ť�Ĺ��ܺ���

		�����ʼ��Ϸ:����Skin_selection_screen()
		������а�:����Leaderboard();
		���������Ա���:Developer_Profile();
		����˳���Ϸ:����exit(0);�˳���Ϸ
	}
*/
void Menu_screen()
{
	//���Ʊ���ͼ
	putimage(0, 0, &img_Login_character);

	//���ñ���ģʽ
	setbkmode(TRANSPARENT);

	//�������Ϸ���ťλ��
	int x = 320;
	int y = 320;
	int w = 160;
	int h = 30;

	//������ɫ��ť�����ɫ��������ɫ����ʽ
	setfillcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(0, 0, "΢���ź�");
	//���ư�ť�Ͱ�ť�е�����
	solidrectangle(x, y, x + w, y + h);
	int hSpace = (w - textwidth("��ʼ��Ϸ")) / 2;
	int vSpace = (h - textheight("��ʼ��Ϸ")) / 2;
	outtextxy(x + hSpace, y + vSpace, "��ʼ��Ϸ");

	solidrectangle(x, y + 60, x + w, y + 60 + h);
	hSpace = (w - textwidth("���а�")) / 2;
	vSpace = (h - textheight("���а�")) / 2;
	outtextxy(x + hSpace, y + 60 + vSpace, "���а�");

	solidrectangle(x, y + 60 * 2, x + w, y + 60 * 2 + h);
	hSpace = (w - textwidth("������Ա")) / 2;
	vSpace = (h - textheight("������Ա")) / 2;
	outtextxy(x + hSpace, y + 60 * 2 + vSpace, "������Ա");

	solidrectangle(x, y + 60 * 3, x + w, y + 60 * 3 + h);
	hSpace = (w - textwidth("�˳���Ϸ")) / 2;
	vSpace = (h - textheight("�˳���Ϸ")) / 2;
	outtextxy(x + hSpace, y + 60 * 3 + vSpace, "�˳���Ϸ");

	//����
	if (music_open)
	{
		putimage_alpha(0, 630, &img_music_yes);
	}
	else
		putimage_alpha(0, 630, &img_music_no);

	FlushBatchDraw();
	clearBufferOnEscape();
	//������������
	ExMessage msg = { 0 };
	while (true)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x > x && msg.x<x + w && msg.y>y && msg.y < y + h)//��ʼ��Ϸ
				{
					flag = 4;
					return;
				}
				else if (msg.x > x && msg.x<x + w && msg.y>y + 60 && msg.y < y + 60 + h)//���а�
				{
					flag = 5;
					return;
				}
				else if (msg.x > x && msg.x<x + w && msg.y>y + 60 * 2 && msg.y < y + 60 * 2 + h)//������Ա
				{
					flag = 6;
					return;
				}
				else if (msg.x > 0 && msg.x < 50 && msg.y>630 && msg.y < 630 + 50)
				{
					if (music_open)
					{
						music_open = false;
						mciSendString("close bgm/����Ϸ&���а�&����&������Ա.mp3", 0, 0, 0);
						return;
					}
					else
					{
						music_open = true;
						playBackgroundMusic("bgm/����Ϸ&���а�&����&������Ա.mp3");
						return;
					}
				}
				else if (msg.x > x && msg.x<x + w && msg.y>y + 60 * 3 && msg.y < y + 60 * 3 + h)//�˳���Ϸ
				{
					exit(0);
				}
			}
		}
	}
}

/*
	������:С��
	����:
	��ȫ�ֱ���map<int, vector<string>> m_Record;�����ݸ���ԭ��ͼ��ӡǰ5��ǰ10������

	while(true)
	{
		�ж��û��Ƿ�������
		���û�����escʱ:����Menu_screen();
	}
*/
void Leaderboard()
{

	//����ͼƬ
	putimage(0, 0, &img_Leaderboard_bk);

	setbkmode(TRANSPARENT);//��ֹ���屳���ڵ�����ͼƬ
	setcolor(BLACK); // �����ı���ɫΪ��ɫ  
	settextstyle(60, 60, "����"); // ���������С����ʽ

	string text;
	text = "���а�";
	outtextxy(230, 100, text.c_str());
	int text_x = 100;
	int text_y = 250;
	//�Ҿ������������û����ģ����ܾ�������ͼ�λ���������
	//ѭ�����ǰ���name��score
	settextstyle(20, 15, "����");
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
	// �ȴ��û�������ESC���˳����а����ص����˵� 
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
	������:�Բ�
	����:
	��ӡ������Ա���,������濴ԭ��ͼ

	while(true)
	{
		�ж��û��Ƿ�������
		���û�����escʱ:����Menu_screen();
	}
*/
void Developer_Profile()
{
	putimage(0, 0, &img_Menu_kaifatandui_bk);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(25, 10, "����Ӵ�");
	putimage(50, 150, &img_member[0]);
	outtextxy(50 + 80, 150 + 20, "�鳤���κ�");
	putimage(300, 150, &img_member[1]);
	outtextxy(300 + 80, 150 + 20, "���鳤��С��");
	putimage(550, 150, &img_member[2]);
	outtextxy(550 + 80, 150 + 20, "��Ʒ�����Բ�");
	putimage(50, 350, &img_member[3]);
	outtextxy(50 + 80, 350 + 20, "��Ϣ�٣�����");
	putimage(300, 350, &img_member[4]);
	outtextxy(300 + 80, 350 + 20, "�ල�٣�С7");
	putimage(550, 350, &img_member[5]);
	outtextxy(550 + 80, 350 + 20, "��Ʒ��������");
	putimage(50, 550, &img_member[6]);
	outtextxy(50 + 80, 550 + 20, "�����٣�����");
	putimage(300, 550, &img_member[7]);
	outtextxy(300 + 80, 550 + 20, "�����٣��緹��");
	putimage(550, 550, &img_member[8]);
	outtextxy(550 + 80, 550 + 20, "�ر���л��");
	outtextxy(550 + 80, 550 + 40, "����Сѧ��");
	outtextxy(2, 2, "��ESC���������˵�");
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



/*--------------------------------��Ϸ����----------------------------------*/
/*
	������:�Բ�
	����:
	��ӡƤ��ѡ�����,�������ԭ��ͼ
	while(true)
	{
	�����û������Ϣ�Ͱ�����Ϣ
	���û����ѡ��Ƥ����ťʱ,����ѡ���Ƥ���ı���ҽṹ�����е�IMAGE,ͬʱ����init();��ʼ����Ϸ����
	�����û�����escʱ����Menu_screen();�ص����˵�
	���û�����enter�ǵ���
	}
*/
void Skin_selection_screen()
{
	mciSendString("close bgm/����Ϸ&���а�&����&������Ա.mp3", 0, 0, 0);
	playBackgroundMusic("bgm/��ɫѡ��&��Ϸ�ڴ��.mp3");
	putimage(0, 0, &img_Leaderboard_bk);
	putimage_alpha(200, 590, &img_tutorial);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(25 * 4, 10 * 4, "����Ӵ�");
	outtextxy(120, 60, "��ѡ����Ľ�ɫ");
	putimage(80, 200, &img_Skin_selection[0]);
	putimage(320, 200, &img_Skin_selection[1]);
	putimage(560, 200, &img_Skin_selection[2]);

	settextstyle(20, 0, "����");
	outtextxy(0, 700, "��esc�������˵�����");
	
	FlushBatchDraw();
	ExMessage msg = { 0 };
	char input;
	// �ȴ��û�������ESC���˳����а����ص����˵� 
	
	
	while (true)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			mciSendString("close bgm/��ɫѡ��&��Ϸ�ڴ��.mp3",0,0,0);
			playBackgroundMusic("bgm/����Ϸ&���а�&����&������Ա.mp3");
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
	������:�緹��
	����:��Ϸ��ѭ��

	while(true)
	{
		�����û���������;

		����Shoot_bullets(&msg);�����ӵ�
		����Spawn_enemies();�����Զ����ɵ���

		���÷�װ�õ����,����,�ӵ��ƶ��ĺ���Data_move(&msg);
		����Game_screen();��ӡ������Ϸ����()
		����Game_time();��ӡʣ��ʱ��

		���÷�װ��ײ��⺯��Collision_detection()


		����is_win()�����ж���Ϸ�Ƿ�ʤ��(if���)
		�緵��true,����Victory_screen()��ӡ��Ϸʤ������

		����is_fail()�����ж���Ϸ�Ƿ�ʧ��(if���)
		�緵��true,����Failure_screen()��ӡ��Ϸʧ�ܽ���
	}
*/
void Play_the_game()
{
	ExMessage msg;//��Ϣָ��
	BeginBatchDraw();
	while (true)//��ѭ��
	{
		DWORD start_time = GetTickCount();//��ʼʱ��
		static int count = 0;
		
		//ʱ��Խ��,ˢ��Խ��
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
		//ˢ�¹���
		if (count % Spawn == 0)
			Spawn_enemies();

		//�����ƶ�����
		Data_move();

		//�����ӵ�
		if (count % Me.cd == 0)
			Shoot_bullets();


		//ʱ��
		if (count % 60 == 0)
			game_time -= 1;//char game_time='60';
		count++;


		//��Ҷ���֡
		static int counter = 0;
		counter++;
		if (counter % 10 == 0)
		{
			idx_currentanim++;
			idx_currentanim = idx_currentanim % player_anim_num;
		}
		

		//���ƻ���
		cleardevice();

		Game_bk();//����
		Game_time();//ʱ��
		Collision_detection();//������ײ���
		Game_player();//��ӡ���
		Game_bullets();//��ӡ�ӵ�
		Game_enemies();//��ӡ����
		Game_drops();//��ӡ������
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




		//��̬��ʱ--��֤1��ִ��60����ѭ��
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
	������:����
	����:
	��ӡ��Ϸ����ͼ�ͽ����еĸ����ֺ�ֵ

*/
void Game_bk()
{
	//����ͼƬ
	putimage(0, 0, &img_play_game_bk);
	putimage_alpha(650, 60, &img_hp);
	
	//ת��Ϊ�ַ���
	ostringstream scoreStream;
	scoreStream << Me.score;
	string scorestr = scoreStream.str();
	ostringstream playerhp;
	playerhp << Me.hp;
	string playerhpstr = playerhp.str();


	// �����������ɫ  
	setbkcolor(BLACK); // ����Ϊ��  
	setcolor(WHITE); // ������ɫΪ��  
	settextstyle(20, 0, "����");

	// ����Ļ�ϻ��Ʒ����ַ���  
	outtextxy(180, 702, scorestr.c_str());
	outtextxy(680, 65, playerhpstr.c_str());
}


/*
	������:����
	����:
	��ӡ������ʣ���ʱ��(�����ǵ���ʱҲ�����ǽ�����)
*/
void Game_time()
{
	ostringstream TIME;
	TIME << game_time;
	string scorestr = TIME.str();
	// �����������ɫ  
	setbkcolor(BLACK); // ����Ϊ��  
	setcolor(WHITE); // ������ɫΪ��  
	settextstyle(25, 0, "����");
	outtextxy(330,60 , scorestr.c_str());
}


/*
	������:����
	����:
	�������λ�ô�ӡ���
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
	������:����
	����:
	�����ӵ�����,���ӵ�����ʱ��ӡ�ӵ�
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
	������:�緹��
	����:
	������������,�����˴���ʱ��ӡ����
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
	������:�緹��
	����:
	��������������,�����������ʱ��ӡ������
*/
void Game_drops()
{
	for (size_t i = 0; i < 20; i++)
	{
		if (drops[i].is_live)
		{
			if (drops[i].type == 0)//Ѫƿ
				putimage_alpha(drops[i].x - 16, drops[i].y - 16, &img_Drops[0]);
			else if (drops[i].type == 1)//Ь��
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
	������:С7
	����:
	��ӡ��ͣ����

	while(true)
	{
		�����û������Ϣ
		�ж��û��Ƿ�㵽��ť�����øð�ť�Ĺ��ܺ���

		���������Ϸ:����Play_the_game()�ص���Ϸ��ѭ��
		����ص����˵�:
		�ȵ���saveRecord()�������汾����Ϸ����
		�ٵ���Menu_screen()�����ص����˵�
	}
*/
void Pause_the_game()
{
	mciSendString("close bgm/��ɫѡ��&��Ϸ�ڴ��.mp3", 0, 0, 0);
	
	//����ͼƬ
	putimage(0, 0, &img_Failure_bk);

	//���ƾ���
	//��ɫ
	setfillcolor(WHITE);
	fillrectangle(150, 300, 650, 500);

	//��ʾ�ı�
	// �����ı���ɫ�����壨��ѡ��  
	setbkcolor(WHITE); // ���ñ���ɫΪ��ɫ�������ı���������͸����  
	setcolor(BLACK); // �����ı���ɫΪ��ɫ  
	settextstyle(30, 0, "΢���ź�"); // ���������С����ʽ������ʹ�õ���20�ź���  


	// ������ε����ĵ�  
	int rect_width = 650 - 150; // ���εĿ��  
	int rect_height = 500 - 300; // ���εĸ߶�  
	int rect_center_x = 150 + rect_width / 2; // �������ĵ�x����  
	int rect_center_y = 300 + rect_height / 2; // �������ĵ�y����  

	// �����ı���Ⱥ͸߶ȣ��Ա���ȷ����  
	char text[] = "��Ϸ����ͣ";
	int text_width = textwidth(text);
	int text_height = textheight(text);

	// �ھ�����������ı�  
	outtextxy(rect_center_x - text_width / 2, rect_center_y - text_height / 2 - 20, text);


	// ���ư�ť
	// / ���尴ť��λ�úʹ�С  
	const int BUTTON_WIDTH = 100;
	const int BUTTON_HEIGHT = 30;
	const int BUTTON_SPACING = 200; // ��ť֮��ļ��  
	const int BUTTON_TOP_MARGIN = -60; // ��ť������ζ����ļ��  
	const int CONTINUE_BUTTON_LEFT = (rect_width - BUTTON_WIDTH) / 2; // ������Ϸ��ť��߽�  
	const int BACK_BUTTON_LEFT = CONTINUE_BUTTON_LEFT + BUTTON_WIDTH + BUTTON_SPACING; // �ص����˵���ť��߽�  
	int button_top = rect_center_y + rect_height / 2 + BUTTON_TOP_MARGIN; // ��ť����λ��  
	// ���ð�ť����ɫ  
	setfillcolor(LIGHTGRAY); // ǳ��ɫ  
	setbkcolor(LIGHTGRAY); // �ı�����ɫ�밴ť��ɫ��ͬ��ʵ��͸��Ч��  
	setcolor(WHITE); // ��ɫ�ı�  
	settextstyle(16, 0, "΢���ź�"); // �����С����ʽ������ʹ��16�ź���  

	// ���Ƽ�����Ϸ��ť����ʾ�ı�  
	fillrectangle(CONTINUE_BUTTON_LEFT, button_top, CONTINUE_BUTTON_LEFT + BUTTON_WIDTH, button_top + BUTTON_HEIGHT);
	char continue_text[] = "������Ϸ";
	int continue_text_width = textwidth(continue_text);
	int continue_text_height = textheight(continue_text);
	outtextxy(CONTINUE_BUTTON_LEFT + (BUTTON_WIDTH - continue_text_width) / 2,
		button_top + (BUTTON_HEIGHT - continue_text_height) / 2,
		continue_text);

	// ���ƻص����˵���ť����ʾ�ı�  
	fillrectangle(BACK_BUTTON_LEFT, button_top, BACK_BUTTON_LEFT + BUTTON_WIDTH, button_top + BUTTON_HEIGHT);
	char back_text[] = "�ص����˵�";
	int back_text_width = textwidth(back_text);
	int back_text_height = textheight(back_text);
	outtextxy(BACK_BUTTON_LEFT + (BUTTON_WIDTH - back_text_width) / 2,
		button_top + (BUTTON_HEIGHT - back_text_height) / 2,
		back_text);


	FlushBatchDraw();
	// �ȴ��û����  
	ExMessage msg = { 0 };
		while (true)
		{
			// ���û�м������룬��ȴ�����¼� 
			if (peekmessage(&msg))
			{

				if (msg.message == WM_LBUTTONDOWN)
				{
					// ������Ƿ��ڡ�������Ϸ����ť��  
					if (msg.x >= CONTINUE_BUTTON_LEFT && msg.x <= CONTINUE_BUTTON_LEFT + BUTTON_WIDTH &&
						msg.y >= button_top && msg.y <= button_top + BUTTON_HEIGHT)
					{
						// ���ü�����Ϸ�ĺ���
						flag=11;   
						playBackgroundMusic("bgm/��ɫѡ��&��Ϸ�ڴ��.mp3");
						break; // �˳�ѭ��  
					}
					// ������Ƿ��ڡ��������˵�����ť��  
					else if (msg.x >= BACK_BUTTON_LEFT && msg.x <= BACK_BUTTON_LEFT + BUTTON_WIDTH &&
						msg.y >= button_top && msg.y <= button_top + BUTTON_HEIGHT)
					{
						playBackgroundMusic("bgm/����Ϸ&���а�&����&������Ա.mp3");
						//�������
						saveRecord();
						flag = 3;
						return; // ���÷������˵��ĺ��� 
						//cout << "���ñ���������������˵�����" << endl << "�ص����˵�" << endl;
					}
				}
			}
		}

}




/*
	������:С7
	����:

	��ӡ��Ϸʧ�ܽ���

	����saveRecord()�������汾����Ϸ����
	while(true)
	{
		�����û������Ϣ
		�ж��û��Ƿ�㵽��ť�����øð�ť�Ĺ��ܺ���

		�������һ��ʱ:
		�ȵ���init()������ʼ����Ϸ����
		�ٵ���Play_the_game()�����ص���Ϸ��ѭ��

		����ص����˵�:����Menu_screen()�����ص����˵�

	}
*/
void Failure_screen()
{
	mciSendString("close bgm/��ɫѡ��&��Ϸ�ڴ��.mp3", 0, 0, 0);
	playBackgroundMusic("bgm/ʧ��.mp3");

	//�ȱ��汾�ַ���
	saveRecord();


	//����ͼƬ
	putimage(0, 0, &img_Failure_bk);


	//��ʾ�ı�
	setbkmode(TRANSPARENT);
	settextstyle(130, 0, "����"); // ���������С����ʽ  

	//���㴰�ڵ����ĵ�
	int center_x = 800 / 2; // �������ĵ�x����  
	int center_y = 800 / 2; // �������ĵ�y���� 
	// �����ı���Ⱥ͸߶ȣ��Ա���ȷ����  
	char text1[] = " �˾Ͷ���!";
	int text_width1 = textwidth(text1);
	int text_height1 = textheight(text1);
	//�������
	outtextxy(center_x - text_width1 / 2, center_y - text_height1 / 2 - 20, text1);

	//��ť
	// ���谴ť�Ŀ�Ⱥ͸߶�  
	// ���ư�ť
	// ���尴ť��λ�úʹ�С  
	const int width = 200;
	const int height = 40;
	const int spaing = 200; // ��ť֮��ļ��  
	const int leftspacing = 100; // ����һ�ְ�ť��߽�  
	const int leftspacing1 = leftspacing + width + spaing; // �ص����˵���ť��߽�  
	int button_top1 = 600; // ��ťy  
	// ���ð�ť����ɫ  
	setfillcolor(LIGHTGRAY); // ǳ��ɫ  
	setbkcolor(LIGHTGRAY); // �ı�����ɫ�밴ť��ɫ��ͬ��ʵ��͸��Ч��  
	setcolor(WHITE); // ��ɫ�ı�  
	settextstyle(14, 0, "����"); // �����С����ʽ  

	// ���Ƽ�����Ϸ��ť����ʾ�ı�  
	fillrectangle(leftspacing, button_top1, leftspacing + width, button_top1 + height);
	char game_text[] = "�Ҳ���������һ��";
	int game_text_width = textwidth(game_text);
	int game_text_height = textheight(game_text);
	outtextxy(leftspacing + (width - game_text_width) / 2,
		button_top1 + (height - game_text_height) / 2,
		game_text);

	// ���ƻص����˵���ť����ʾ�ı�  
	fillrectangle(leftspacing1, button_top1, leftspacing1 + width, button_top1 + height);
	char back_text1[] = "�ص����˵�";
	int back_text_width1 = textwidth(back_text1);
	int back_text_height1 = textheight(back_text1);
	outtextxy(leftspacing1 + (width - back_text_width1) / 2,
		button_top1 + (height - back_text_height1) / 2,
		back_text1);

	FlushBatchDraw();
	// �ȴ��û����  
	while (true)
	{
		MOUSEMSG m;
		while (!_kbhit())
		{
			// ���û�м������룬��ȴ�����¼� 
			if (MouseHit())
			{
				m = GetMouseMsg();
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					// ������Ƿ��ڡ�������Ϸ����ť��  
					if (m.x >= leftspacing && m.x <= leftspacing + width &&
						m.y >= button_top1 && m.y <= button_top1 + height)
					{
						mciSendString("close bgm/ʧ��.mp3", 0, 0, 0);
						playBackgroundMusic("bgm/��ɫѡ��&��Ϸ�ڴ��.mp3");
						//����init()������ʼ����Ϸ����
						init();
						flag = 7;
						return;

					}
					// ������Ƿ��ڡ��������˵�����ť��  
					else if (m.x >= leftspacing1 && m.x <= leftspacing1 + width &&
						m.y >= button_top1 && m.y <= button_top1 + height)
					{
						mciSendString("close bgm/ʧ��.mp3", 0, 0, 0);
						playBackgroundMusic("bgm/����Ϸ&���а�&����&������Ա.mp3");
						flag = 3;
						return;
						
					}

				}
			}
		}
	}
}



/*
	������:С7
	����:

	��ӡ��Ϸʤ������

	����saveRecord()�������汾����Ϸ����
	while(true)
	{

		�����û������Ϣ
		�ж��û��Ƿ�㵽��ť�����øð�ť�Ĺ��ܺ���

		����ص����˵�:����Menu_screen()�����ص����˵�
	}
*/
void Victory_screen()
{
	mciSendString("close bgm/��ɫѡ��&��Ϸ�ڴ��.mp3", 0, 0, 0);
	playBackgroundMusic("bgm/ʤ��.mp3");
	//�ȱ��汾�ַ���
	saveRecord();

	//����ͼƬ
	putimage(0, 0, &img_Victory_bk);


	//��ʾ�ı�
	setcolor(BLACK); // ��ɫ�ı� 
	settextstyle(150, 0, "����"); // ���������С����ʽ  

	//���㴰�ڵ����ĵ�
	int center_x1 = 800 / 2; // �������ĵ�x����  
	int center_y1 = 800 / 2; // �������ĵ�y���� 
	// �����ı���Ⱥ͸߶ȣ��Ա���ȷ����  
	char text2[] = " ʤ��!";
	int text_width2 = textwidth(text2);
	int text_height2 = textheight(text2);
	//�������
	outtextxy(center_x1 - text_width2 / 2, center_y1 - text_height2 / 2 - 20, text2);

	//��ť
	// ���谴ť�Ŀ�Ⱥ͸߶�  
	// ���ư�ť
	// ���尴ť��λ�úʹ�С  
	const int width1 = 200;
	const int height1 = 50;
	const int leftspacing2 = 300; // �ص����˵���ť��߽�    
	int button_top2 = 550; // ��ťy  
	// ���ð�ť����ɫ  
	setfillcolor(LIGHTGRAY); // ǳ��ɫ  
	setbkcolor(LIGHTGRAY); // �ı�����ɫ�밴ť��ɫ��ͬ��ʵ��͸��Ч��  
	setcolor(BLACK); // ��ɫ�ı�  
	settextstyle(14, 0, "����"); // �����С����ʽ  

	// ���ƻص����˵���ť����ʾ�ı�  
	fillrectangle(leftspacing2, button_top2, leftspacing2 + width1, button_top2 + height1);
	char back_text2[] = "�ص����˵�";
	int back_text_width2 = textwidth(back_text2);
	int back_text_height2 = textheight(back_text2);
	outtextxy(leftspacing2 + (width1 - back_text_width2) / 2,
		button_top2 + (height1 - back_text_height2) / 2,
		back_text2);

	FlushBatchDraw();
	ExMessage msg = { 0 };
	// �ȴ��û����  
	while (true)
	{
		if (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				// ������Ƿ��ڡ��������˵�����ť��  
				if (msg.x >= leftspacing2 && msg.x <= leftspacing2 + width1 &&
					msg.y >= button_top2 && msg.y <= button_top2 + height1)
				{
					mciSendString("close bgm/ʤ��.mp3", 0, 0, 0);
					playBackgroundMusic("bgm/����Ϸ&���а�&����&������Ա.mp3");
					flag = 3;
					return;
				}

			}
		}
	}
	
}