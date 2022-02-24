//C++로 ATM
#include <iostream>
#include <string> // string 사용 위해
#include <cstring>// strcmp 등 사용 위해
#include <mysql.h> //MySQL 연동 위해
#include <fstream>
#include <time.h>//srand가 시간에 따라 다른 랜덤한 값을 받기 위해
#include "atm.h"

using namespace std;


MYSQL* conn;//MySQL과 연결을 담당
MYSQL_RES* res;//쿼리에 대한 결과를 받는 변수
MYSQL_ROW row; //쿼리에 대한 실제 데이터 값이 들어있는 변수


int main() {
	Atm atm;
	User user;
	Account acc;
	
	for (;;) {
		cout << "\n=============== ATM ================\n";
		cout << "1.입금\n" << "2.출금\n" << "3.송금\n" << "4.잔액조회\n" << "5.계좌 생성\n" << "6.비밀번호 변경\n" << "7.관리자\n" << "8.종료\n";
		cout << "\n====================================\n";
		cout << "\n>> ";
		
		string atmmenu;
		cin >> atmmenu;
		
		//길이 예외
		int menu_len = atmmenu.length();
		if (menu_len != 1) {
			cout << "\n잘못된 형식의 입력입니다. 다시 입력해주세요\n";
			continue;
		}
		//숫자 범위 예외
		if (!(atmmenu[0]>=49 && atmmenu[0] <= 56)) {
			cout << "\n잘못된 형식의 입력입니다. 다시 입력해주세요\n";
			continue;
		}
		
		int menu = stoi(atmmenu);
		
		if (menu == 1) {
			
			user.deposit();

			
			continue;
		}
		else if (menu == 2) {
			user.withdraw();

			continue;
		}
		else if (menu == 3) {
			user.sending();

			continue;
		}
		else if (menu == 4) {
			acc.check_balance();

			continue;
		}
		else if (menu == 5) {
			acc.open_account();

			continue;
		}
		else if (menu == 6) {
			acc.change_password();

			continue;
		}
		else if (menu == 7) {
			atm.management();

			continue;
		}
		else if (menu == 8) {
			cout << "\n감사합니다. 다음에 또 이용해주세요(^^)(__)(^^)\n";
			mysql_free_result(res);//데이터 누수를 막기 위한 용도
			mysql_close(conn);//mysql 연결 해제

			break;
		}
	}
	return 0;
}

