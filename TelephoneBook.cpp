#include <iostream>
#include <cstring>
#include <Windows.h>
using namespace std;

#define Width 600//cmd창 가로 크기
#define Height 800//cmd창 세로 크기
#define MAX_Phone_Num 100 // 최대로 저장할 수 있는 전화번호 갯수

/*
- ID, 비밀번호 등록 기능 개발 완료
- 전화번호 등록 기능 개발 완료
- 전화번호부 열람 기능 개발 완료
- 전화번호를 이름, 전화번호, 정보로 검색하는 기능 개발 완료
*/

/*
보완점
1. 로그인 방법 변경, 초기 비밀번호 설정하고 한 번 로그인 하면 ID, 비밀번호 변경 가능하게 하는게 좋아 보임
2. 전화번호 삭제 기능 추가하기
3. 입력한 전화번호를 abcd ...... xtz ㄱㄴㄷㄹ.....ㅎ 순으로 정렬하는 기능 추가하기
4. 여러개의 User을 만들 수 있게 하여 각 User마다 다른 전화번호를 저장할 수 있게 하기
5. 정보 입력 부분에서 띄어쓰기 입력도 받을 수 있도록 하기
6. 사용자가 영어로 검색할 때 대/소문자 구별 없이 검색할 수 있게 하기
*/

//==============================사용자 정보 클래스=========================================================
class User_Info {//프로그램 사용자의 정보를 나타내는 클래스
private:
	char* User_ID;//사용자 이름, 한글 5자, 영어 10자까지 가능
	int Pwd;//사용자 비밀번호, 8자리
public:
	User_Info();//기본 생성자
	User_Info(const char* id, int pwd);//일반 생성자
	~User_Info();//소멸자
	void Change_Info(const char* id, int pwd);// User_ID와 Pwd를 바꾸는 함수
	void Show_Info();//User_ID와 Pwd를 출력하는 함수
	bool Compare_Info(const char* id, const int pwd);//User_ID와 Pwd를 비교하여 일치하면 1 일치하지 않으면 0을 return하는 함수
};


User_Info::User_Info() {//기본 생성자
	User_ID = new char[1+1];
	User_ID = NULL;
	Pwd = 0;
}


User_Info::User_Info(const char* id, int pwd) {//일반 생성자
	User_ID = new char[strlen(id) + 1];//동적 메모리 할당
	strcpy_s(User_ID, strlen(id) + 1 , id);//유저 이름 저장
	Pwd = pwd;// 유저 비밀번호 저장
}


User_Info::~User_Info() {//소멸자
	delete[] User_ID;
}


void User_Info::Change_Info(const char* id, int pwd) {
	delete[] User_ID;//User_ID동적 메모리 해제
	User_ID = new char[strlen(id) + 1];//입력한 매개변수 id의 길이에 맞게 동적 메모리 할당
	strcpy_s(User_ID, strlen(id ) + 1, id);//User_ID에 매개변수 id값 입력
	Pwd = pwd;//Pwd 에 매개변수 pwd값 입력
}


bool User_Info::Compare_Info(const char* id, const int pwd) {//입력한 ID와 비밀번호를 비교하여 같으면 1, 다르면 0 return
	if ((strcmp(id, User_ID) == 0) && (pwd == Pwd)) {//입력한 id와 pwd가 클래스 내에 저장된 User_ID와 Pwd와 같으면 
		return true;//1 리턴
	}
	else {//같지 않으면
		return false;//0 리턴
	}
}

void User_Info:: Show_Info() {//private 변수 User_ID와 Pwd를 출력
	cout << "ID : " << User_ID << endl;
	cout << "PW : " << Pwd << endl;
}


//==============================사용자 정보 클래스 끝============================================================




//=============================전화번호 정보 클래스==============================================================

class Phone_Info {//입력한 전화번호와 정보들을 나타내는 클래스, 메인문에서는 객체의 배열로 만들어서 활용할 예정 => 하나의 객체당 유저 한명의 정보를 담음
private:
	char* Name;//전화번호 사용자의 이름
	char* Number;//전화번호
	char* Info;//간단한 설명
public:
	Phone_Info();//기본 생성자
	Phone_Info(const char* name, const char* number, const char* info);//일반 생성자
	~Phone_Info();//소멸자 
	void Input_Phone_Info(const char* name, const char* number, const char* info);//전화번호 등의 정보를 입력받는 함수
	void Show_Phone_Info();//이름, 전화번호, 정보를 출력하는 함수
	void Search_Phone_With_Num(const char* num, int i);//입력한 전화번호가 같으면 그 전화번호 정보를 출력하는 함수
	void Search_Phone_With_Name(const char* name, int i);//입력한 이름이 같으면 그 전화번호 정보를 출력하는 함수
	void Search_Phone_With_Info(const char* info, int i);//입력한 정보가 같으면 그 전화번호 정보를 출력하는 함수
};

Phone_Info::Phone_Info() {//기본 생성자
	Name = new char[1 + 1];
	Name = NULL;
	Number = new char[1 + 1];
	Number = NULL;
	Info = new char[1 + 1];
	Info = NULL;
}

Phone_Info::Phone_Info(const char* name, const char* number, const char* info) {//일반 생성자
	Name = new char[strlen(name)+1];//매개변수 name의 길이 + 1 만큼 동적 메모리 할당
	strcpy_s(Name, strlen(name)+1, name);//private 변수 Name에 매개변수 name 의 내용 저장
	Number = new char[strlen(number)+1];//매개변수 number의 길이 + 1 만큼 동적 메모리 할당
	strcpy_s(Number, strlen(number) + 1, number);//private 변수 Number에 매개변수 number의 내용 저장
	Info = new char[strlen(info) + 1];//매개변수 info의 길이 + 1 만큼 동적 메모리 할당
	strcpy_s(Info, strlen(info) + 1, info);//private 변수 Info에 매개변수 info의 내용 저장
}

Phone_Info::~Phone_Info() {//소멸자
	delete[] Name;
	delete[] Number;
	delete[] Info;
}

void Phone_Info::Input_Phone_Info(const char* name, const char* number, const char* info) {
	delete[] Name;//기존의 Name 메모리 해제
	Name = new char[strlen(name) + 1];//매개변수 name의 길이 + 1만큼 새로운 동적 메모리 할당
	delete[] Number;//기존의 Number 메모리 해제 
	Number = new char[strlen(number) + 1];//매개변수 number의 길이 + 1만큼 새로운 동적 메모리 할당
	delete[] Info;//기존의 Info 메모리 해제
	Info = new char[strlen(info) + 1];//매게변수 info의 길이 + 1만큼 새로운 동적 메모리 할당
	strcpy_s(Name, strlen(name) + 1, name);//private 변수 Name에 매개변수 name 의 내용 저장
	strcpy_s(Number, strlen(number) + 1, number);//private 변수 Number에 매개변수 number의 내용 저장
	strcpy_s(Info, strlen(info) + 1, info);//private 변수 Info에 매개변수 info의 내용 저장
}

void Phone_Info::Show_Phone_Info() {//클래스 내의 private 변수 Name, Number, Info 정보 출력
	cout << "이름 : " << Name << "   번호 : " << Number << endl;
	cout << "메모 : " << Info << endl << endl;
}

void Phone_Info::Search_Phone_With_Num(const char* num, int i) {//<== 매개변수 i 는 main문에서 for문의 i값을 대입할 예정
	if (strcmp(num, Number) == 0) {//입력된 매개변수 num과 private 변수 Number을 비교하였을 때 같으면
		cout << i + 1 << "번 째로 저장한 전화번호 출력" << endl << endl;//i는 for문 반복문이 돌아갈 때 몇 번째 객체 배열의 정보를 출력하는지 나타냄
		Show_Phone_Info();//전화번호 정보 출력
	}
}

void Phone_Info::Search_Phone_With_Name(const char* name, int i) {//<== 매개변수 i 는 main문에서 for문의 i값을 대입할 예정
	if (strcmp(name, Name) == 0) {//입력된 매개변수 name과 private 변수 Name을 비교하였을 때 같으면
		cout << i + 1 << "번 째로 저장한 전화번호 출력" << endl << endl;//i는 for문 반복문이 돌아갈 때 몇 번째 객체 배열의 정보를 출력하는지 나타냄
		Show_Phone_Info();//전화번호 정보 출력
	}
}

void Phone_Info::Search_Phone_With_Info(const char* info, int i) {//<== 매개변수 i 는 main문에서 for문의 i값을 대입할 예정
	if (strcmp(info, Info) == 0) {//입력된 매개변수 info와 private 변수 Info을 비교하였을 때 같으면
		cout << i + 1 << "번 째로 저장한 전화번호 출력" << endl << endl;//i는 for문 반복문이 돌아갈 때 몇 번째 객체 배열의 정보를 출력하는지 나타냄
		Show_Phone_Info();//전화번호 정보 출력
	}
}

//=============================전화번호 정보 클래스 끝=========================================================




//=============================cmd창 설정=======================================================================
void cmd_init() {//cmd창 크기 설정
	HWND hwnd = GetConsoleWindow();//콘솔 창의 핸들 얻기
	RECT rect;
	GetWindowRect(hwnd, &rect);
	MoveWindow(hwnd, rect.left, rect.top, Width, Height, TRUE);
}
//=============================cmd창 설정=======================================================================


//=============================인라인 함수======================================================================
inline void System_Stop_Cmd_Clear() {//자주 쓰는 함수로, 길이가 짧기 때문에 inline함수로 함
	system("pause");//시스템 멈춤(계속할려면 아무키나 누르시오) 출력시킴
	system("cls");//cmd창 clear
}
//=============================인라인 함수=======================================================================



//=============================메인 메뉴=========================================================================
int Main_Menu() {
	int InputNum;//사용자에게 입력받을 변수(1 ~ 4)의 값



	//======================메인 UI=============================================
	cout << "전화번호부" << endl << endl;
	cout << "1. 사용자 ID/PW 입력" << endl << endl;
	cout << "2. 전화번호 입력" << endl << endl;
	cout << "3. 전화번호 열람" << endl << endl;
	cout << "4. 전화번호 검색" << endl << endl;
	cout << "5. 종료" << endl << endl;
	cout << "입력 : ";
	//==========================================================================
	cin >> InputNum;//사용자에게 InputNum 변수 입력받음
	if ((InputNum < 1) || (InputNum > 5)) {//만약 사용자가 (1 ~ 5)의 값을 입력하지 않았으면
		cout << "다시 입력하시오" << endl;
		System_Stop_Cmd_Clear();
		return 0;//0을 return하여 초기화면으로 전환함
	}
	else {//사용자가 (1 ~ 5)의 값을 제대로 입력하였다면
		system("cls");//cmd 클리어
		return InputNum;//입력한 InputNum을 return 하여 각각의 기능으로 화면을 전환함
	}
}
//=============================메인 메뉴=========================================================================



//============================비밀번호 입력받는 함수=============================================================
int Input_UserInfo(User_Info& U) {
	//ID 동적 메모리 할당
	char* ID;
	ID = new char[10 + 1];

	int PW;//입력받을 PW변수
	int PW_Check;//입력받을 PW_Check변수, PW와 비교하여 사용자가 PW를 제대로 입력하였는지 확인함



	//===========================첫 번째 화면===========================
	cout << "ID를 입력하시오(10자리,영문/숫자만) : ";
	cin >> ID;
	cout << "비밀번호를 입력하시오(숫자로만, 8자리) : ";
	cin >> PW;
	//===========================첫 번째 화면 끝=========================



	//========================비밀번호 check=============================
	while (1) {//반복문으로 만들어 기준에 맞는 비밀번호를 입력할 때 까지 반복시킴
		if ((PW < 10000000) || (PW > 99999999)) {//입력한 비밀번호가 8자리가 아닐 때(10000000 ~ 99999999 사이의 숫자가 아닐 때)
			cout << "8자리 숫자로 이루어진 비밀번호가 아닙니다." << endl;
			cout << "다시 입력하세요 : ";
			cin >> PW;//다시 비밀번호를 입력받음
		}
		else {//입력한 비밀번호가 8자리일 때
			break;//while문을 break하여 프로그램의 다음단계로 진행
		}
	}
	//========================비밀번호 check 끝===========================



	//========================비밀번호 일치 check=========================
	cout << "비밀번호 확인 : ";
	cin >> PW_Check;//비밀번호 체크를 위하여 PW_Check를 입력받음
	if (PW == PW_Check) {//만약 입력한 PW와 PW_Ckeck가 일치하면 비밀번호를 올바르게 입력한 것으로
		U.Change_Info(ID, PW);//User_Info객체의 private 변수 User_ID, Pwd에 사용자가 입력한 ID, PW 입력
		cout << "입력 완료" << endl;
		U.Show_Info();//입력된 정보를 출력하여 입력이 제대로 되었는지 확인
		System_Stop_Cmd_Clear();//인라인 함수
	}
	else {//PW와 PW_Check가 일치하지 않으면 아무런 작업을 하지 않고 처음으로 돌려보냄
		cout << "비밀번호 틀림, 처음으로 다시 돌아갑니다." << endl;
		System_Stop_Cmd_Clear();
	}
	//========================비밀번호 일치 check 끝=======================


	return 0;//0을 return하여 초기 화면으로 돌려보냄
	delete[] ID;//이용한 동적 메모리 해제
}
//============================비밀번호 입력받는 함수 끝===========================================================



//============================전화번호 입력받는 함수==============================================================
int Input_Phone_Num(User_Info& U, Phone_Info *PI, int& used_phone_num) {
	bool Info_Check = 0;//bool 형 Info_Check 변수 User_Info클래스 내의 Compare_Info 함수를 이용하기 위함
	//동적 메모리 할당
	char* ID;
	ID = new char[10 + 1];

	int PW = 0;//입력받을 PW 변수

	cout << "ID를 입력하시오 : ";
	cin >> ID;//ID 입력받음
	cout << endl << endl << "비밀번호를 입력하시오 : ";
	cin >> PW;//PW 입력받음
	Info_Check = U.Compare_Info(ID, PW);//입력한 ID와 PW를 입력하여 Compare_Info 함수에 넣어 
	//User_Info의 private 변수 User_ID와 Pwd와 일치하면 1 일치하지 않으면 0이 됨

	//비밀번호 체크 과정=================================================
	if (Info_Check == 0) {//만약 ID와 비밀번호가 일치하지 않으면
		cout << "ID/비밀번호 틀림, 처음으로 돌아갑니다." << endl;
		System_Stop_Cmd_Clear();
		delete[] ID;//이용한 동적 메모리 해제
		return 0;//0을 return하여 초기 화면으로 전환시킴
	}
	else {//만약 ID와 비밀번호가 일치하면
		cout << "로그인 완료" << endl;
		System_Stop_Cmd_Clear();
		int input_num = 0;//사용자에게 입력받을 변수, 몇 개의 전화번호를 입력받을지

		//전화번호 입력 화면===============================================
		cout << "몇 개의 전화번호를 입력할 것인지 숫자로 입력하시오(최대 100개까지 입력 가능)" << endl << endl;
		cout << "현재 입력된 전화번호의 개수 : " << used_phone_num << endl << endl;//몇 개의 전화번호가 입력되었는지 출력
		cout << "입력 가능한 전화번호의 개수 : " << (MAX_Phone_Num - used_phone_num) << endl << endl;//define으로 정의한 MAX_Phone_Num - 입력된 전화번호 = 입력 가능한 전화번호 
		cout << "입력 : ";
		//전화번호 입력 화면 끝=============================================
		cin >> input_num;//input_num 입력받음

		System_Stop_Cmd_Clear();

		//전화번호 입력 처리(입력 가능한 숫자를 넘어섰을 때)================
		if (input_num > (MAX_Phone_Num - used_phone_num)) {//입력한 숫자가 입력 가능한 숫자보다 클 때
			cout << endl << endl << "입력 가능한 개수를 초과했습니다. 처음으로 다시 돌아갑니다." << endl;
			System_Stop_Cmd_Clear();
			delete[] ID;
			return 0;//0을 return하여 처음으로 돌려보냄
		}

		//전화번호 입력 처리(입력 가능한 숫자를 입력했을 때)================
		else {
			for (int i = used_phone_num; i < used_phone_num + input_num; i++) {//이미 저장된 전화번호가 있을 경우 그 이후부터 저장함
				//전화번호 정보 하나마다 Phone_Info객체 하나를 사용, 객체 배열을 사용함
				
				//동적 메모리 할당
				char* Name_buffer = new char[10 + 1];
				char* Num_buffer = new char[11 + 1];
				char* Info_buffer = new char[20 + 1];

				//전화번호 입력 받는 화면====================================
				cout << endl << "==========" << i + 1 << "번 째 전화번호 정보 입력==========" << endl << endl;
				cout << "이름 입력 : ";
				cin >> Name_buffer;
				cout << endl << "전화번호 입력(-)제외 : ";
				cin >> Num_buffer;
				cout << endl << "메모 입력 : ";
				cin >> Info_buffer;
				//전화번호 입력 받는 화면 끝=================================


				PI[i].Input_Phone_Info(Name_buffer, Num_buffer, Info_buffer);//객체 배열에 정보 입력
				
				//이용한 동적 메모리 해제
				delete[] Name_buffer;
				delete[] Num_buffer;
				delete[] Info_buffer;
			}
			System_Stop_Cmd_Clear();
			delete[] ID;//이용한 동적 메모리 해제
			used_phone_num = input_num + used_phone_num;//used_phone_num값 업데이트 하여 사용자가 몇 개의 전화번호를 입력했는지 알림
			return 0;//초기 화면으로 전환시킴
		}
	}
}
//============================전화번호 입력받는 함수 끝===========================================================




//============================전화번호 열람 함수==================================================================
int Open_Phone_Num(User_Info& U, Phone_Info* P, const int used_phone_num) {
	bool Info_Check = 0;//bool 형 Info_Check 변수 User_Info클래스 내의 Compare_Info 함수를 이용하기 위함
	//동적 메모리 할당
	char* ID;
	ID = new char[10 + 1];

	int PW = 0;//입력받을 PW 변수

	cout << "ID를 입력하시오 : ";
	cin >> ID;//ID 입력받음
	cout << endl << endl << "비밀번호를 입력하시오 : ";
	cin >> PW;//PW 입력받음
	Info_Check = U.Compare_Info(ID, PW);//입력한 ID와 PW를 입력하여 Compare_Info 함수에 넣어 
	//User_Info의 private 변수 User_ID와 Pwd와 일치하면 1 일치하지 않으면 0이 됨

	//비밀번호 체크 과정=================================================
	if (Info_Check == 0) {//만약 ID와 비밀번호가 일치하지 않으면
		cout << "ID/비밀번호 틀림, 처음으로 돌아갑니다." << endl;
		System_Stop_Cmd_Clear();
		delete[] ID;//이용한 동적 메모리 해제
		return 0;//0을 return하여 초기 화면으로 전환시킴
	}
	else {//만약 ID와 비밀번호가 일치하면
		cout << "로그인 완료" << endl;
		System_Stop_Cmd_Clear();
		int pages = used_phone_num / 10;//사용자가 입력한 전화번호를 사용자에게 보여주기 위해 한 페이지에 10개의 전화번호를 표시함
		int last_pages_phone_num = used_phone_num % 10;//마지막 페이지에 몇 개의 전화번호를 출력해야 하는지 나머지 연산을 함
		int i = 0;
		for (i = 0; i < pages; i++) {//10개씩 출력하는 페이지의 전화번호를 출력
			cout << "전화번호부 열람" << "  (" << i + 1 << " page)" << endl;
			for (int j = i * 10; j < (i * 10) + 10; j++) {//전화번호 객체 배열의 (page * 10) + 0번째 부터 (page * 10) + 9번째 정보 까지 출력
				P[j].Show_Phone_Info();//배열의 정보 출력
			}
			System_Stop_Cmd_Clear();
		}
		//남은 전화번호를 1페이지에 출력
		cout << "전화번호부 열람" << "  (" << i + 1 << " page)" << endl;
		for (int z = pages * 10; z < (pages * 10) + last_pages_phone_num; z++) {//마지막 페이지의 정보를 출력, 마지막 페이지의 전화번호 갯수대로 출력함
			P[z].Show_Phone_Info();//배열의 정보 출력
		}
		System_Stop_Cmd_Clear();
		delete[] ID;//이용한 동적 메모리 해제
		return 0;//초기 화면으로 전환시킴
	}
	
}
//============================전화번호 열람 함수 끝================================================================


//============================전화번호 검색 함수==================================================================
int Search_Phone_num(User_Info& U, Phone_Info* P, int& used_phone_num) {
	bool Info_Check = 0;//bool 형 Info_Check 변수 User_Info클래스 내의 Compare_Info 함수를 이용하기 위함
	//동적 메모리 할당
	char* ID;
	ID = new char[10 + 1];

	int PW = 0;//입력받을 PW 변수

	cout << "ID를 입력하시오 : ";
	cin >> ID;//ID 입력받음
	cout << endl << endl << "비밀번호를 입력하시오 : ";
	cin >> PW;//PW 입력받음
	Info_Check = U.Compare_Info(ID, PW);//입력한 ID와 PW를 입력하여 Compare_Info 함수에 넣어 
	//User_Info의 private 변수 User_ID와 Pwd와 일치하면 1 일치하지 않으면 0이 됨

	//비밀번호 체크 과정=================================================
	if (Info_Check == 0) {//만약 ID와 비밀번호가 일치하지 않으면
		cout << "ID/비밀번호 틀림, 처음으로 돌아갑니다." << endl;
		System_Stop_Cmd_Clear();
		delete[] ID;//이용한 동적 메모리 해제
		return 0;//0을 return하여 초기 화면으로 전환시킴
	}
	else {//만약 ID와 비밀번호가 일치하면
		cout << "로그인 완료" << endl;
		System_Stop_Cmd_Clear();
		int state = 0;//사용자에게 입력받을 변수

		//===================전화번호 검색 방법 고르기=========================
		while (1) {

			//전화번호 검색 메뉴=========================
			cout << "선    택" << endl << endl;
			cout << "1. 이름으로 찾기" << endl;
			cout << "2. 번호로 찾기" << endl;
			cout << "3. 메모로 찾기" << endl;
			cout << "4. 돌아가기" << endl;
			cout << "입력 : ";
			//===========================================

			cin >> state;//state 값을 입력받음 (1 ~ 4의 값)
			if ((state > 4) || (state < 1)) {//1~4의 값을 입력받지 않으면
				cout << "잘못 입력했습니다. 1~3의 수를 다시 입력하세요" << endl;
				System_Stop_Cmd_Clear();//입력받을 때 까지 뺑뺑이 돌리기
			}
			else {
				break;//1 ~ 4의 값을 받으면 break로 while문을 해제함
			}
		}
		//===================전화번호 검색 방법 고르기 끝=======================

		//===================고른 state에 따른 작동=============================
		if (state == 1) {
			//=============이름으로 검색할 때===============
			//동적 메모리 할당
			char* name;
			name = new char[10 + 1];
			cout << "이름을 입력하세요 : ";
			cin >> name;//이름 입력받기
			System_Stop_Cmd_Clear();
			for (int i = 0; i < used_phone_num; i++) {//입력된 전화번호 수 만큼 검색
				P[i].Search_Phone_With_Name(name, i);//일치하는 전화번호 정보 전부 출력
			}
			System_Stop_Cmd_Clear();
			delete[] name;//동적 메모리 해제
			return 0;//0을 return하여 메인 메뉴로 전환
			//=============이름으로 검색할 때 끝=============
		}


		else if (state == 2) {
			//=============전화번호로 검색할 때==============
			//동적 메모리 할당
			char* num;
			num = new char[11 + 1];
			cout << "전화번호를 입력하세요(- 제외하고 입력) : ";
			cin >> num;//전화번호 입력받기
			System_Stop_Cmd_Clear();
			for (int i = 0; i < used_phone_num; i++) {//입력된 전화번호 수 만큼 검색
				P[i].Search_Phone_With_Num(num, i);//일치하는 전화번호 정보 전부 출력
			}
			System_Stop_Cmd_Clear();
			delete[] num;//동적 메모리 해제
			return 0;//0을 return하여 메인 메뉴로 전환
			//=============전화번호로 검색할 때 끝============
		}


		else if (state == 3) {
			//=============정보로 검색할 때===================
			//동적 메모리 할당
			char* info;
			info = new char[20 + 1];
			cout << "메모를 입력하시오 : ";
			cin >> info;//정보 입력받기
			System_Stop_Cmd_Clear();
			for (int i = 0; i < used_phone_num; i++) {//입력된 전화번호 수 만큼 검색
				P[i].Search_Phone_With_Info(info, i);//일치하는 전화번호 정보 전부 출력
			}
			System_Stop_Cmd_Clear();
			delete[] info;//동적 메모리 해제
			return 0;//0을 return하여 메인 메뉴로 전환
			//=============정보로 검색할 때 끝=================
		}


		else {//사용자가 "4. 돌아가기"를 선택하였을 때
			system("cls");
			return 0;//0을 return하여 메인 메뉴로 전환
		}
		//===================고른 state에 따른 작동 끝===========================
		delete[] ID;//동적 메모리 해제
	}
	
}
//============================전화번호 검색 함수 끝================================================================



//==========================================메인 문================================================================
int main() {
	
	//==================프로그램 환경 설정 관련=======================

	int Menu_num = 0;//메뉴를 제어하는 변수, 초깃값 0으로 하여 첫 화면이 메인 메뉴이게 함
	User_Info U;//U 객체 생성
	Phone_Info P[MAX_Phone_Num];//P 객체 배열을 생성, #define MAX_Phone_Num의 수만큼 생성함
	int Save_Phone_num = 0;//사용자가 몇 개의 전화번호를 입력하였는지 나타내는 변수
	cmd_init();
	//==================프로그램 환경 설정 관련 끝=====================


	//=================전화번호부 프로그램=============================
	while (1) {
		if (Menu_num == 0) {//메인 메뉴
			Menu_num = Main_Menu();//사용자가 특정 작동을 전부 완료하면 그 상황에 알맞는 return값을 받아서 다른 if문으로 넘김
		}
		if (Menu_num == 1) {
			Menu_num = Input_UserInfo(U);//사용자가 특정 작동을 전부 완료하면 그 상황에 알맞는 return값을 받아서 다른 if문으로 넘김
		}
		if (Menu_num == 2) {
			Menu_num = Input_Phone_Num(U, P, Save_Phone_num);//사용자가 특정 작동을 전부 완료하면 그 상황에 알맞는 return값을 받아서 다른 if문으로 넘김
		}
		if (Menu_num == 3) {
			Menu_num = Open_Phone_Num(U, P, Save_Phone_num);//사용자가 특정 작동을 전부 완료하면 그 상황에 알맞는 return값을 받아서 다른 if문으로 넘김
		}
		if (Menu_num == 4) {
			Menu_num = Search_Phone_num(U, P, Save_Phone_num);//사용자가 특정 작동을 전부 완료하면 그 상황에 알맞는 return값을 받아서 다른 if문으로 넘김
		}
		if (Menu_num == 5) {//사용자가 종료를 선택하면
			break;//while문을 break하여 프로그램을 종료함
		}
	}
	//=================전화번호부 프로그램 끝===========================

}
//==========================================메인 문 끝==============================================================