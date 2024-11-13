#include <iostream>
#include <cstring>
#include <Windows.h>
using namespace std;

#define Width 600//cmdâ ���� ũ��
#define Height 800//cmdâ ���� ũ��
#define MAX_Phone_Num 100 // �ִ�� ������ �� �ִ� ��ȭ��ȣ ����

/*
- ID, ��й�ȣ ��� ��� ���� �Ϸ�
- ��ȭ��ȣ ��� ��� ���� �Ϸ�
- ��ȭ��ȣ�� ���� ��� ���� �Ϸ�
- ��ȭ��ȣ�� �̸�, ��ȭ��ȣ, ������ �˻��ϴ� ��� ���� �Ϸ�
*/

/*
������
1. �α��� ��� ����, �ʱ� ��й�ȣ �����ϰ� �� �� �α��� �ϸ� ID, ��й�ȣ ���� �����ϰ� �ϴ°� ���� ����
2. ��ȭ��ȣ ���� ��� �߰��ϱ�
3. �Է��� ��ȭ��ȣ�� abcd ...... xtz ��������.....�� ������ �����ϴ� ��� �߰��ϱ�
4. �������� User�� ���� �� �ְ� �Ͽ� �� User���� �ٸ� ��ȭ��ȣ�� ������ �� �ְ� �ϱ�
5. ���� �Է� �κп��� ���� �Էµ� ���� �� �ֵ��� �ϱ�
6. ����ڰ� ����� �˻��� �� ��/�ҹ��� ���� ���� �˻��� �� �ְ� �ϱ�
*/

//==============================����� ���� Ŭ����=========================================================
class User_Info {//���α׷� ������� ������ ��Ÿ���� Ŭ����
private:
	char* User_ID;//����� �̸�, �ѱ� 5��, ���� 10�ڱ��� ����
	int Pwd;//����� ��й�ȣ, 8�ڸ�
public:
	User_Info();//�⺻ ������
	User_Info(const char* id, int pwd);//�Ϲ� ������
	~User_Info();//�Ҹ���
	void Change_Info(const char* id, int pwd);// User_ID�� Pwd�� �ٲٴ� �Լ�
	void Show_Info();//User_ID�� Pwd�� ����ϴ� �Լ�
	bool Compare_Info(const char* id, const int pwd);//User_ID�� Pwd�� ���Ͽ� ��ġ�ϸ� 1 ��ġ���� ������ 0�� return�ϴ� �Լ�
};


User_Info::User_Info() {//�⺻ ������
	User_ID = new char[1+1];
	User_ID = NULL;
	Pwd = 0;
}


User_Info::User_Info(const char* id, int pwd) {//�Ϲ� ������
	User_ID = new char[strlen(id) + 1];//���� �޸� �Ҵ�
	strcpy_s(User_ID, strlen(id) + 1 , id);//���� �̸� ����
	Pwd = pwd;// ���� ��й�ȣ ����
}


User_Info::~User_Info() {//�Ҹ���
	delete[] User_ID;
}


void User_Info::Change_Info(const char* id, int pwd) {
	delete[] User_ID;//User_ID���� �޸� ����
	User_ID = new char[strlen(id) + 1];//�Է��� �Ű����� id�� ���̿� �°� ���� �޸� �Ҵ�
	strcpy_s(User_ID, strlen(id ) + 1, id);//User_ID�� �Ű����� id�� �Է�
	Pwd = pwd;//Pwd �� �Ű����� pwd�� �Է�
}


bool User_Info::Compare_Info(const char* id, const int pwd) {//�Է��� ID�� ��й�ȣ�� ���Ͽ� ������ 1, �ٸ��� 0 return
	if ((strcmp(id, User_ID) == 0) && (pwd == Pwd)) {//�Է��� id�� pwd�� Ŭ���� ���� ����� User_ID�� Pwd�� ������ 
		return true;//1 ����
	}
	else {//���� ������
		return false;//0 ����
	}
}

void User_Info:: Show_Info() {//private ���� User_ID�� Pwd�� ���
	cout << "ID : " << User_ID << endl;
	cout << "PW : " << Pwd << endl;
}


//==============================����� ���� Ŭ���� ��============================================================




//=============================��ȭ��ȣ ���� Ŭ����==============================================================

class Phone_Info {//�Է��� ��ȭ��ȣ�� �������� ��Ÿ���� Ŭ����, ���ι������� ��ü�� �迭�� ���� Ȱ���� ���� => �ϳ��� ��ü�� ���� �Ѹ��� ������ ����
private:
	char* Name;//��ȭ��ȣ ������� �̸�
	char* Number;//��ȭ��ȣ
	char* Info;//������ ����
public:
	Phone_Info();//�⺻ ������
	Phone_Info(const char* name, const char* number, const char* info);//�Ϲ� ������
	~Phone_Info();//�Ҹ��� 
	void Input_Phone_Info(const char* name, const char* number, const char* info);//��ȭ��ȣ ���� ������ �Է¹޴� �Լ�
	void Show_Phone_Info();//�̸�, ��ȭ��ȣ, ������ ����ϴ� �Լ�
	void Search_Phone_With_Num(const char* num, int i);//�Է��� ��ȭ��ȣ�� ������ �� ��ȭ��ȣ ������ ����ϴ� �Լ�
	void Search_Phone_With_Name(const char* name, int i);//�Է��� �̸��� ������ �� ��ȭ��ȣ ������ ����ϴ� �Լ�
	void Search_Phone_With_Info(const char* info, int i);//�Է��� ������ ������ �� ��ȭ��ȣ ������ ����ϴ� �Լ�
};

Phone_Info::Phone_Info() {//�⺻ ������
	Name = new char[1 + 1];
	Name = NULL;
	Number = new char[1 + 1];
	Number = NULL;
	Info = new char[1 + 1];
	Info = NULL;
}

Phone_Info::Phone_Info(const char* name, const char* number, const char* info) {//�Ϲ� ������
	Name = new char[strlen(name)+1];//�Ű����� name�� ���� + 1 ��ŭ ���� �޸� �Ҵ�
	strcpy_s(Name, strlen(name)+1, name);//private ���� Name�� �Ű����� name �� ���� ����
	Number = new char[strlen(number)+1];//�Ű����� number�� ���� + 1 ��ŭ ���� �޸� �Ҵ�
	strcpy_s(Number, strlen(number) + 1, number);//private ���� Number�� �Ű����� number�� ���� ����
	Info = new char[strlen(info) + 1];//�Ű����� info�� ���� + 1 ��ŭ ���� �޸� �Ҵ�
	strcpy_s(Info, strlen(info) + 1, info);//private ���� Info�� �Ű����� info�� ���� ����
}

Phone_Info::~Phone_Info() {//�Ҹ���
	delete[] Name;
	delete[] Number;
	delete[] Info;
}

void Phone_Info::Input_Phone_Info(const char* name, const char* number, const char* info) {
	delete[] Name;//������ Name �޸� ����
	Name = new char[strlen(name) + 1];//�Ű����� name�� ���� + 1��ŭ ���ο� ���� �޸� �Ҵ�
	delete[] Number;//������ Number �޸� ���� 
	Number = new char[strlen(number) + 1];//�Ű����� number�� ���� + 1��ŭ ���ο� ���� �޸� �Ҵ�
	delete[] Info;//������ Info �޸� ����
	Info = new char[strlen(info) + 1];//�ŰԺ��� info�� ���� + 1��ŭ ���ο� ���� �޸� �Ҵ�
	strcpy_s(Name, strlen(name) + 1, name);//private ���� Name�� �Ű����� name �� ���� ����
	strcpy_s(Number, strlen(number) + 1, number);//private ���� Number�� �Ű����� number�� ���� ����
	strcpy_s(Info, strlen(info) + 1, info);//private ���� Info�� �Ű����� info�� ���� ����
}

void Phone_Info::Show_Phone_Info() {//Ŭ���� ���� private ���� Name, Number, Info ���� ���
	cout << "�̸� : " << Name << "   ��ȣ : " << Number << endl;
	cout << "�޸� : " << Info << endl << endl;
}

void Phone_Info::Search_Phone_With_Num(const char* num, int i) {//<== �Ű����� i �� main������ for���� i���� ������ ����
	if (strcmp(num, Number) == 0) {//�Էµ� �Ű����� num�� private ���� Number�� ���Ͽ��� �� ������
		cout << i + 1 << "�� °�� ������ ��ȭ��ȣ ���" << endl << endl;//i�� for�� �ݺ����� ���ư� �� �� ��° ��ü �迭�� ������ ����ϴ��� ��Ÿ��
		Show_Phone_Info();//��ȭ��ȣ ���� ���
	}
}

void Phone_Info::Search_Phone_With_Name(const char* name, int i) {//<== �Ű����� i �� main������ for���� i���� ������ ����
	if (strcmp(name, Name) == 0) {//�Էµ� �Ű����� name�� private ���� Name�� ���Ͽ��� �� ������
		cout << i + 1 << "�� °�� ������ ��ȭ��ȣ ���" << endl << endl;//i�� for�� �ݺ����� ���ư� �� �� ��° ��ü �迭�� ������ ����ϴ��� ��Ÿ��
		Show_Phone_Info();//��ȭ��ȣ ���� ���
	}
}

void Phone_Info::Search_Phone_With_Info(const char* info, int i) {//<== �Ű����� i �� main������ for���� i���� ������ ����
	if (strcmp(info, Info) == 0) {//�Էµ� �Ű����� info�� private ���� Info�� ���Ͽ��� �� ������
		cout << i + 1 << "�� °�� ������ ��ȭ��ȣ ���" << endl << endl;//i�� for�� �ݺ����� ���ư� �� �� ��° ��ü �迭�� ������ ����ϴ��� ��Ÿ��
		Show_Phone_Info();//��ȭ��ȣ ���� ���
	}
}

//=============================��ȭ��ȣ ���� Ŭ���� ��=========================================================




//=============================cmdâ ����=======================================================================
void cmd_init() {//cmdâ ũ�� ����
	HWND hwnd = GetConsoleWindow();//�ܼ� â�� �ڵ� ���
	RECT rect;
	GetWindowRect(hwnd, &rect);
	MoveWindow(hwnd, rect.left, rect.top, Width, Height, TRUE);
}
//=============================cmdâ ����=======================================================================


//=============================�ζ��� �Լ�======================================================================
inline void System_Stop_Cmd_Clear() {//���� ���� �Լ���, ���̰� ª�� ������ inline�Լ��� ��
	system("pause");//�ý��� ����(����ҷ��� �ƹ�Ű�� �����ÿ�) ��½�Ŵ
	system("cls");//cmdâ clear
}
//=============================�ζ��� �Լ�=======================================================================



//=============================���� �޴�=========================================================================
int Main_Menu() {
	int InputNum;//����ڿ��� �Է¹��� ����(1 ~ 4)�� ��



	//======================���� UI=============================================
	cout << "��ȭ��ȣ��" << endl << endl;
	cout << "1. ����� ID/PW �Է�" << endl << endl;
	cout << "2. ��ȭ��ȣ �Է�" << endl << endl;
	cout << "3. ��ȭ��ȣ ����" << endl << endl;
	cout << "4. ��ȭ��ȣ �˻�" << endl << endl;
	cout << "5. ����" << endl << endl;
	cout << "�Է� : ";
	//==========================================================================
	cin >> InputNum;//����ڿ��� InputNum ���� �Է¹���
	if ((InputNum < 1) || (InputNum > 5)) {//���� ����ڰ� (1 ~ 5)�� ���� �Է����� �ʾ�����
		cout << "�ٽ� �Է��Ͻÿ�" << endl;
		System_Stop_Cmd_Clear();
		return 0;//0�� return�Ͽ� �ʱ�ȭ������ ��ȯ��
	}
	else {//����ڰ� (1 ~ 5)�� ���� ����� �Է��Ͽ��ٸ�
		system("cls");//cmd Ŭ����
		return InputNum;//�Է��� InputNum�� return �Ͽ� ������ ������� ȭ���� ��ȯ��
	}
}
//=============================���� �޴�=========================================================================



//============================��й�ȣ �Է¹޴� �Լ�=============================================================
int Input_UserInfo(User_Info& U) {
	//ID ���� �޸� �Ҵ�
	char* ID;
	ID = new char[10 + 1];

	int PW;//�Է¹��� PW����
	int PW_Check;//�Է¹��� PW_Check����, PW�� ���Ͽ� ����ڰ� PW�� ����� �Է��Ͽ����� Ȯ����



	//===========================ù ��° ȭ��===========================
	cout << "ID�� �Է��Ͻÿ�(10�ڸ�,����/���ڸ�) : ";
	cin >> ID;
	cout << "��й�ȣ�� �Է��Ͻÿ�(���ڷθ�, 8�ڸ�) : ";
	cin >> PW;
	//===========================ù ��° ȭ�� ��=========================



	//========================��й�ȣ check=============================
	while (1) {//�ݺ������� ����� ���ؿ� �´� ��й�ȣ�� �Է��� �� ���� �ݺ���Ŵ
		if ((PW < 10000000) || (PW > 99999999)) {//�Է��� ��й�ȣ�� 8�ڸ��� �ƴ� ��(10000000 ~ 99999999 ������ ���ڰ� �ƴ� ��)
			cout << "8�ڸ� ���ڷ� �̷���� ��й�ȣ�� �ƴմϴ�." << endl;
			cout << "�ٽ� �Է��ϼ��� : ";
			cin >> PW;//�ٽ� ��й�ȣ�� �Է¹���
		}
		else {//�Է��� ��й�ȣ�� 8�ڸ��� ��
			break;//while���� break�Ͽ� ���α׷��� �����ܰ�� ����
		}
	}
	//========================��й�ȣ check ��===========================



	//========================��й�ȣ ��ġ check=========================
	cout << "��й�ȣ Ȯ�� : ";
	cin >> PW_Check;//��й�ȣ üũ�� ���Ͽ� PW_Check�� �Է¹���
	if (PW == PW_Check) {//���� �Է��� PW�� PW_Ckeck�� ��ġ�ϸ� ��й�ȣ�� �ùٸ��� �Է��� ������
		U.Change_Info(ID, PW);//User_Info��ü�� private ���� User_ID, Pwd�� ����ڰ� �Է��� ID, PW �Է�
		cout << "�Է� �Ϸ�" << endl;
		U.Show_Info();//�Էµ� ������ ����Ͽ� �Է��� ����� �Ǿ����� Ȯ��
		System_Stop_Cmd_Clear();//�ζ��� �Լ�
	}
	else {//PW�� PW_Check�� ��ġ���� ������ �ƹ��� �۾��� ���� �ʰ� ó������ ��������
		cout << "��й�ȣ Ʋ��, ó������ �ٽ� ���ư��ϴ�." << endl;
		System_Stop_Cmd_Clear();
	}
	//========================��й�ȣ ��ġ check ��=======================


	return 0;//0�� return�Ͽ� �ʱ� ȭ������ ��������
	delete[] ID;//�̿��� ���� �޸� ����
}
//============================��й�ȣ �Է¹޴� �Լ� ��===========================================================



//============================��ȭ��ȣ �Է¹޴� �Լ�==============================================================
int Input_Phone_Num(User_Info& U, Phone_Info *PI, int& used_phone_num) {
	bool Info_Check = 0;//bool �� Info_Check ���� User_InfoŬ���� ���� Compare_Info �Լ��� �̿��ϱ� ����
	//���� �޸� �Ҵ�
	char* ID;
	ID = new char[10 + 1];

	int PW = 0;//�Է¹��� PW ����

	cout << "ID�� �Է��Ͻÿ� : ";
	cin >> ID;//ID �Է¹���
	cout << endl << endl << "��й�ȣ�� �Է��Ͻÿ� : ";
	cin >> PW;//PW �Է¹���
	Info_Check = U.Compare_Info(ID, PW);//�Է��� ID�� PW�� �Է��Ͽ� Compare_Info �Լ��� �־� 
	//User_Info�� private ���� User_ID�� Pwd�� ��ġ�ϸ� 1 ��ġ���� ������ 0�� ��

	//��й�ȣ üũ ����=================================================
	if (Info_Check == 0) {//���� ID�� ��й�ȣ�� ��ġ���� ������
		cout << "ID/��й�ȣ Ʋ��, ó������ ���ư��ϴ�." << endl;
		System_Stop_Cmd_Clear();
		delete[] ID;//�̿��� ���� �޸� ����
		return 0;//0�� return�Ͽ� �ʱ� ȭ������ ��ȯ��Ŵ
	}
	else {//���� ID�� ��й�ȣ�� ��ġ�ϸ�
		cout << "�α��� �Ϸ�" << endl;
		System_Stop_Cmd_Clear();
		int input_num = 0;//����ڿ��� �Է¹��� ����, �� ���� ��ȭ��ȣ�� �Է¹�����

		//��ȭ��ȣ �Է� ȭ��===============================================
		cout << "�� ���� ��ȭ��ȣ�� �Է��� ������ ���ڷ� �Է��Ͻÿ�(�ִ� 100������ �Է� ����)" << endl << endl;
		cout << "���� �Էµ� ��ȭ��ȣ�� ���� : " << used_phone_num << endl << endl;//�� ���� ��ȭ��ȣ�� �ԷµǾ����� ���
		cout << "�Է� ������ ��ȭ��ȣ�� ���� : " << (MAX_Phone_Num - used_phone_num) << endl << endl;//define���� ������ MAX_Phone_Num - �Էµ� ��ȭ��ȣ = �Է� ������ ��ȭ��ȣ 
		cout << "�Է� : ";
		//��ȭ��ȣ �Է� ȭ�� ��=============================================
		cin >> input_num;//input_num �Է¹���

		System_Stop_Cmd_Clear();

		//��ȭ��ȣ �Է� ó��(�Է� ������ ���ڸ� �Ѿ�� ��)================
		if (input_num > (MAX_Phone_Num - used_phone_num)) {//�Է��� ���ڰ� �Է� ������ ���ں��� Ŭ ��
			cout << endl << endl << "�Է� ������ ������ �ʰ��߽��ϴ�. ó������ �ٽ� ���ư��ϴ�." << endl;
			System_Stop_Cmd_Clear();
			delete[] ID;
			return 0;//0�� return�Ͽ� ó������ ��������
		}

		//��ȭ��ȣ �Է� ó��(�Է� ������ ���ڸ� �Է����� ��)================
		else {
			for (int i = used_phone_num; i < used_phone_num + input_num; i++) {//�̹� ����� ��ȭ��ȣ�� ���� ��� �� ���ĺ��� ������
				//��ȭ��ȣ ���� �ϳ����� Phone_Info��ü �ϳ��� ���, ��ü �迭�� �����
				
				//���� �޸� �Ҵ�
				char* Name_buffer = new char[10 + 1];
				char* Num_buffer = new char[11 + 1];
				char* Info_buffer = new char[20 + 1];

				//��ȭ��ȣ �Է� �޴� ȭ��====================================
				cout << endl << "==========" << i + 1 << "�� ° ��ȭ��ȣ ���� �Է�==========" << endl << endl;
				cout << "�̸� �Է� : ";
				cin >> Name_buffer;
				cout << endl << "��ȭ��ȣ �Է�(-)���� : ";
				cin >> Num_buffer;
				cout << endl << "�޸� �Է� : ";
				cin >> Info_buffer;
				//��ȭ��ȣ �Է� �޴� ȭ�� ��=================================


				PI[i].Input_Phone_Info(Name_buffer, Num_buffer, Info_buffer);//��ü �迭�� ���� �Է�
				
				//�̿��� ���� �޸� ����
				delete[] Name_buffer;
				delete[] Num_buffer;
				delete[] Info_buffer;
			}
			System_Stop_Cmd_Clear();
			delete[] ID;//�̿��� ���� �޸� ����
			used_phone_num = input_num + used_phone_num;//used_phone_num�� ������Ʈ �Ͽ� ����ڰ� �� ���� ��ȭ��ȣ�� �Է��ߴ��� �˸�
			return 0;//�ʱ� ȭ������ ��ȯ��Ŵ
		}
	}
}
//============================��ȭ��ȣ �Է¹޴� �Լ� ��===========================================================




//============================��ȭ��ȣ ���� �Լ�==================================================================
int Open_Phone_Num(User_Info& U, Phone_Info* P, const int used_phone_num) {
	bool Info_Check = 0;//bool �� Info_Check ���� User_InfoŬ���� ���� Compare_Info �Լ��� �̿��ϱ� ����
	//���� �޸� �Ҵ�
	char* ID;
	ID = new char[10 + 1];

	int PW = 0;//�Է¹��� PW ����

	cout << "ID�� �Է��Ͻÿ� : ";
	cin >> ID;//ID �Է¹���
	cout << endl << endl << "��й�ȣ�� �Է��Ͻÿ� : ";
	cin >> PW;//PW �Է¹���
	Info_Check = U.Compare_Info(ID, PW);//�Է��� ID�� PW�� �Է��Ͽ� Compare_Info �Լ��� �־� 
	//User_Info�� private ���� User_ID�� Pwd�� ��ġ�ϸ� 1 ��ġ���� ������ 0�� ��

	//��й�ȣ üũ ����=================================================
	if (Info_Check == 0) {//���� ID�� ��й�ȣ�� ��ġ���� ������
		cout << "ID/��й�ȣ Ʋ��, ó������ ���ư��ϴ�." << endl;
		System_Stop_Cmd_Clear();
		delete[] ID;//�̿��� ���� �޸� ����
		return 0;//0�� return�Ͽ� �ʱ� ȭ������ ��ȯ��Ŵ
	}
	else {//���� ID�� ��й�ȣ�� ��ġ�ϸ�
		cout << "�α��� �Ϸ�" << endl;
		System_Stop_Cmd_Clear();
		int pages = used_phone_num / 10;//����ڰ� �Է��� ��ȭ��ȣ�� ����ڿ��� �����ֱ� ���� �� �������� 10���� ��ȭ��ȣ�� ǥ����
		int last_pages_phone_num = used_phone_num % 10;//������ �������� �� ���� ��ȭ��ȣ�� ����ؾ� �ϴ��� ������ ������ ��
		int i = 0;
		for (i = 0; i < pages; i++) {//10���� ����ϴ� �������� ��ȭ��ȣ�� ���
			cout << "��ȭ��ȣ�� ����" << "  (" << i + 1 << " page)" << endl;
			for (int j = i * 10; j < (i * 10) + 10; j++) {//��ȭ��ȣ ��ü �迭�� (page * 10) + 0��° ���� (page * 10) + 9��° ���� ���� ���
				P[j].Show_Phone_Info();//�迭�� ���� ���
			}
			System_Stop_Cmd_Clear();
		}
		//���� ��ȭ��ȣ�� 1�������� ���
		cout << "��ȭ��ȣ�� ����" << "  (" << i + 1 << " page)" << endl;
		for (int z = pages * 10; z < (pages * 10) + last_pages_phone_num; z++) {//������ �������� ������ ���, ������ �������� ��ȭ��ȣ ������� �����
			P[z].Show_Phone_Info();//�迭�� ���� ���
		}
		System_Stop_Cmd_Clear();
		delete[] ID;//�̿��� ���� �޸� ����
		return 0;//�ʱ� ȭ������ ��ȯ��Ŵ
	}
	
}
//============================��ȭ��ȣ ���� �Լ� ��================================================================


//============================��ȭ��ȣ �˻� �Լ�==================================================================
int Search_Phone_num(User_Info& U, Phone_Info* P, int& used_phone_num) {
	bool Info_Check = 0;//bool �� Info_Check ���� User_InfoŬ���� ���� Compare_Info �Լ��� �̿��ϱ� ����
	//���� �޸� �Ҵ�
	char* ID;
	ID = new char[10 + 1];

	int PW = 0;//�Է¹��� PW ����

	cout << "ID�� �Է��Ͻÿ� : ";
	cin >> ID;//ID �Է¹���
	cout << endl << endl << "��й�ȣ�� �Է��Ͻÿ� : ";
	cin >> PW;//PW �Է¹���
	Info_Check = U.Compare_Info(ID, PW);//�Է��� ID�� PW�� �Է��Ͽ� Compare_Info �Լ��� �־� 
	//User_Info�� private ���� User_ID�� Pwd�� ��ġ�ϸ� 1 ��ġ���� ������ 0�� ��

	//��й�ȣ üũ ����=================================================
	if (Info_Check == 0) {//���� ID�� ��й�ȣ�� ��ġ���� ������
		cout << "ID/��й�ȣ Ʋ��, ó������ ���ư��ϴ�." << endl;
		System_Stop_Cmd_Clear();
		delete[] ID;//�̿��� ���� �޸� ����
		return 0;//0�� return�Ͽ� �ʱ� ȭ������ ��ȯ��Ŵ
	}
	else {//���� ID�� ��й�ȣ�� ��ġ�ϸ�
		cout << "�α��� �Ϸ�" << endl;
		System_Stop_Cmd_Clear();
		int state = 0;//����ڿ��� �Է¹��� ����

		//===================��ȭ��ȣ �˻� ��� ����=========================
		while (1) {

			//��ȭ��ȣ �˻� �޴�=========================
			cout << "��    ��" << endl << endl;
			cout << "1. �̸����� ã��" << endl;
			cout << "2. ��ȣ�� ã��" << endl;
			cout << "3. �޸�� ã��" << endl;
			cout << "4. ���ư���" << endl;
			cout << "�Է� : ";
			//===========================================

			cin >> state;//state ���� �Է¹��� (1 ~ 4�� ��)
			if ((state > 4) || (state < 1)) {//1~4�� ���� �Է¹��� ������
				cout << "�߸� �Է��߽��ϴ�. 1~3�� ���� �ٽ� �Է��ϼ���" << endl;
				System_Stop_Cmd_Clear();//�Է¹��� �� ���� ������ ������
			}
			else {
				break;//1 ~ 4�� ���� ������ break�� while���� ������
			}
		}
		//===================��ȭ��ȣ �˻� ��� ���� ��=======================

		//===================�� state�� ���� �۵�=============================
		if (state == 1) {
			//=============�̸����� �˻��� ��===============
			//���� �޸� �Ҵ�
			char* name;
			name = new char[10 + 1];
			cout << "�̸��� �Է��ϼ��� : ";
			cin >> name;//�̸� �Է¹ޱ�
			System_Stop_Cmd_Clear();
			for (int i = 0; i < used_phone_num; i++) {//�Էµ� ��ȭ��ȣ �� ��ŭ �˻�
				P[i].Search_Phone_With_Name(name, i);//��ġ�ϴ� ��ȭ��ȣ ���� ���� ���
			}
			System_Stop_Cmd_Clear();
			delete[] name;//���� �޸� ����
			return 0;//0�� return�Ͽ� ���� �޴��� ��ȯ
			//=============�̸����� �˻��� �� ��=============
		}


		else if (state == 2) {
			//=============��ȭ��ȣ�� �˻��� ��==============
			//���� �޸� �Ҵ�
			char* num;
			num = new char[11 + 1];
			cout << "��ȭ��ȣ�� �Է��ϼ���(- �����ϰ� �Է�) : ";
			cin >> num;//��ȭ��ȣ �Է¹ޱ�
			System_Stop_Cmd_Clear();
			for (int i = 0; i < used_phone_num; i++) {//�Էµ� ��ȭ��ȣ �� ��ŭ �˻�
				P[i].Search_Phone_With_Num(num, i);//��ġ�ϴ� ��ȭ��ȣ ���� ���� ���
			}
			System_Stop_Cmd_Clear();
			delete[] num;//���� �޸� ����
			return 0;//0�� return�Ͽ� ���� �޴��� ��ȯ
			//=============��ȭ��ȣ�� �˻��� �� ��============
		}


		else if (state == 3) {
			//=============������ �˻��� ��===================
			//���� �޸� �Ҵ�
			char* info;
			info = new char[20 + 1];
			cout << "�޸� �Է��Ͻÿ� : ";
			cin >> info;//���� �Է¹ޱ�
			System_Stop_Cmd_Clear();
			for (int i = 0; i < used_phone_num; i++) {//�Էµ� ��ȭ��ȣ �� ��ŭ �˻�
				P[i].Search_Phone_With_Info(info, i);//��ġ�ϴ� ��ȭ��ȣ ���� ���� ���
			}
			System_Stop_Cmd_Clear();
			delete[] info;//���� �޸� ����
			return 0;//0�� return�Ͽ� ���� �޴��� ��ȯ
			//=============������ �˻��� �� ��=================
		}


		else {//����ڰ� "4. ���ư���"�� �����Ͽ��� ��
			system("cls");
			return 0;//0�� return�Ͽ� ���� �޴��� ��ȯ
		}
		//===================�� state�� ���� �۵� ��===========================
		delete[] ID;//���� �޸� ����
	}
	
}
//============================��ȭ��ȣ �˻� �Լ� ��================================================================



//==========================================���� ��================================================================
int main() {
	
	//==================���α׷� ȯ�� ���� ����=======================

	int Menu_num = 0;//�޴��� �����ϴ� ����, �ʱ갪 0���� �Ͽ� ù ȭ���� ���� �޴��̰� ��
	User_Info U;//U ��ü ����
	Phone_Info P[MAX_Phone_Num];//P ��ü �迭�� ����, #define MAX_Phone_Num�� ����ŭ ������
	int Save_Phone_num = 0;//����ڰ� �� ���� ��ȭ��ȣ�� �Է��Ͽ����� ��Ÿ���� ����
	cmd_init();
	//==================���α׷� ȯ�� ���� ���� ��=====================


	//=================��ȭ��ȣ�� ���α׷�=============================
	while (1) {
		if (Menu_num == 0) {//���� �޴�
			Menu_num = Main_Menu();//����ڰ� Ư�� �۵��� ���� �Ϸ��ϸ� �� ��Ȳ�� �˸´� return���� �޾Ƽ� �ٸ� if������ �ѱ�
		}
		if (Menu_num == 1) {
			Menu_num = Input_UserInfo(U);//����ڰ� Ư�� �۵��� ���� �Ϸ��ϸ� �� ��Ȳ�� �˸´� return���� �޾Ƽ� �ٸ� if������ �ѱ�
		}
		if (Menu_num == 2) {
			Menu_num = Input_Phone_Num(U, P, Save_Phone_num);//����ڰ� Ư�� �۵��� ���� �Ϸ��ϸ� �� ��Ȳ�� �˸´� return���� �޾Ƽ� �ٸ� if������ �ѱ�
		}
		if (Menu_num == 3) {
			Menu_num = Open_Phone_Num(U, P, Save_Phone_num);//����ڰ� Ư�� �۵��� ���� �Ϸ��ϸ� �� ��Ȳ�� �˸´� return���� �޾Ƽ� �ٸ� if������ �ѱ�
		}
		if (Menu_num == 4) {
			Menu_num = Search_Phone_num(U, P, Save_Phone_num);//����ڰ� Ư�� �۵��� ���� �Ϸ��ϸ� �� ��Ȳ�� �˸´� return���� �޾Ƽ� �ٸ� if������ �ѱ�
		}
		if (Menu_num == 5) {//����ڰ� ���Ḧ �����ϸ�
			break;//while���� break�Ͽ� ���α׷��� ������
		}
	}
	//=================��ȭ��ȣ�� ���α׷� ��===========================

}
//==========================================���� �� ��==============================================================