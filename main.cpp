//C++�� ATM
#include <iostream>
#include <string> // string ��� ����
#include <cstring>// strcmp �� ��� ����
#include <mysql.h> //MySQL ���� ����
#include <fstream>
#include <time.h>//srand�� �ð��� ���� �ٸ� ������ ���� �ޱ� ����
#include "atm.h"

using namespace std;


MYSQL* conn;//MySQL�� ������ ���
MYSQL_RES* res;//������ ���� ����� �޴� ����
MYSQL_ROW row; //������ ���� ���� ������ ���� ����ִ� ����


int main() {
	Atm atm;
	User user;
	Account acc;
	
	for (;;) {
		cout << "\n=============== ATM ================\n";
		cout << "1.�Ա�\n" << "2.���\n" << "3.�۱�\n" << "4.�ܾ���ȸ\n" << "5.���� ����\n" << "6.��й�ȣ ����\n" << "7.������\n" << "8.����\n";
		cout << "\n====================================\n";
		cout << "\n>> ";
		
		string atmmenu;
		cin >> atmmenu;
		
		//���� ����
		int menu_len = atmmenu.length();
		if (menu_len != 1) {
			cout << "\n�߸��� ������ �Է��Դϴ�. �ٽ� �Է����ּ���\n";
			continue;
		}
		//���� ���� ����
		if (!(atmmenu[0]>=49 && atmmenu[0] <= 56)) {
			cout << "\n�߸��� ������ �Է��Դϴ�. �ٽ� �Է����ּ���\n";
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
			cout << "\n�����մϴ�. ������ �� �̿����ּ���(^^)(__)(^^)\n";
			mysql_free_result(res);//������ ������ ���� ���� �뵵
			mysql_close(conn);//mysql ���� ����

			break;
		}
	}
	return 0;
}

