#include <iostream>
#include <string> // string ��� ����
#include <cstring>// strcmp �� ��� ����
#include <mysql.h> //MySQL ���� ����
#include <fstream>
#include <time.h>//srand�� �ð��� ���� �ٸ� ������ ���� �ޱ� ����
#include "atm.h"

using namespace std;

#define HOST "localhost" // ���� ȣ��Ʈ �ּ�
#define USER "root" //����� �̸�
#define PASS "dsy4042" //MYSQL �н�����
#define NAME "bank" //������ �����ͺ��̽� �̸�

//�Ա� �Ϸ�
void User :: deposit() {
	
	MYSQL* conn;//MySQL�� ������ ���
	MYSQL_RES* res;//������ ���� ����� �޴� ����
	MYSQL_ROW row; //������ ���� ���� ������ ���� ����ִ� ����

	conn = mysql_init(NULL);//�ʱ�ȭ

	//MySQl�� ����
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL ���� ����\n";
	}
	
	string line;
	ifstream file("������.txt"); // txt ������ ����. 
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close(); // ������ ������ �ݴ´�. 
	}

	cout << "\n\n������ �������ּ���: ";
	cin >> bank_name;

	sprintf(fbank, "select*from newclient where bank ='%s'", bank_name);
	int len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		//������ �´��� �˻�
		if (strcmp(bank_name, row[1]) == 0) {
			cout << "\n���¹�ȣ�� �Է����ּ��� : ";
			char account[15];
			cin >> account;

			sprintf(faccount,"select*from newclient where bank = '%s' and account = '%s'",bank_name,account);
			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			
			//���°� �´��� �˻�
			if (row != NULL) {
								
				error = atoi(row[5]);
				
				if (strcmp(account,row[0])==0,error <=2) {
					cout << "\n��й�ȣ�� �Է����ּ��� : ";
					cin >> password;

					for (count = error; count < 2;count++) {
						if (strcmp(password,row[3]) != 0) {							

							uperror = ++error;

							sprintf(error_count,"update newclient set error = %d where bank ='%s' and account = '%s'",uperror,bank_name,account);
							len = mysql_query(conn, error_count);

							cout << "\n��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ��� : ";
							cin >> password;

						}
						else if (error == 3) {
							break;
						}
						else {
							break;
						}
					}
					//��й�ȣ ������ �˻�
					if (strcmp(password,row[3]) == 0) {
						cout << "\n�Ա� �ݾ��� �Է����ּ��� : ";
						cin >> money;

						balance = atoi(row[4]);
						
						total_money = balance + money;

						cout << "\n" << row[1] << " �ŷ���ǥ" << endl;
						cout << "[���� �Ա�]" << endl;
						cout << "---------------------------" << endl;
						cout << "��û �ݾ�: " << money <<"��" << endl;
						cout << "ó����� : ����ó��\n"<< endl;
						cout << "�ŷ� �� �ܾ�: " << total_money << "��" << endl;
						cout << "\n---------------------------\n";

						char* query_date = "select now()";
						len = mysql_query(conn, query_date);
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						cout << "�ŷ��Ͻ�: " << row[0] << endl;
						cout << "���¹�ȣ: " << bank_name <<" "<< account << endl;

						sprintf(update_money, "update newclient set money = %d where account = '%s'", total_money, account);
						len = mysql_query(conn, update_money);

					}
					else {
						cout << "\n��й�ȣ�� 3ȸ Ʋ�Ƚ��ϴ�.���� ���� �� �ʱ�ȭ������ ���ư��ϴ�.\n";


						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = '%s'", bank_name, account);
						len = mysql_query(conn, update_error);
					}

				}else if(strcmp(account, row[0]) == 0 && error ==3) {
					cout << "\n������ �����Դϴ�. ���� ������ ������ �� �̿����ּ���^^\n";
				}

			}
			else {
				cout << "\n�Է��Ͻ� ���¸� ã�� �� �����ϴ�. �������� �ùٸ� ���¸� �Է����ּ���\n";
			}

		}
	}
	else if (row == NULL) {
		cout << "\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. �������� �ùٸ� ������� �Է����ּ���\n";
	}

}

//��� �Ϸ�
void User::withdraw() {
	
	MYSQL* conn;//MySQL�� ������ ���
	MYSQL_RES* res;//������ ���� ����� �޴� ����
	MYSQL_ROW row; //������ ���� ���� ������ ���� ����ִ� ����

	conn = mysql_init(NULL);//�ʱ�ȭ

	//MySQl�� ����
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL ���� ����\n";
	}

	string line;
	ifstream file("������.txt"); // txt ������ ����. 
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close(); // ������ ������ �ݴ´�. 
	}

	cout << "\n\n������ �������ּ���: ";
	char bank_name[15];
	cin >> bank_name;

	sprintf(fbank, "select*from newclient where bank ='%s'", bank_name);
	int len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		//������ �´��� �˻�
		if (strcmp(bank_name, row[1]) == 0) {
			cout << "\n���¹�ȣ�� �Է����ּ��� : ";
			char account[15];
			cin >> account;

			sprintf(faccount, "select*from newclient where bank = '%s' and account = '%s'", bank_name, account);
			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			//���°� �´��� �˻�
			if (row != NULL) {				

				error = atoi(row[5]);

				if (strcmp(account, row[0]) == 0, error <= 2) {
					cout << "\n��й�ȣ�� �Է����ּ��� : ";
					cin >> password;

					for (count = error; count < 2;count++) {
						if (strcmp(password, row[3]) != 0) {							

							uperror = ++error;

							sprintf(error_count, "update newclient set error = %d where bank ='%s' and account = '%s'", uperror, bank_name, account);
							len = mysql_query(conn, error_count);

							cout << "\n��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ��� : ";
							cin >> password;

						}
						else if(error ==3) {
							break;
						}
						else {
							break;
						}
					}
					//��й�ȣ ������ �˻�
					if (strcmp(password, row[3]) == 0) {
						cout << "\n��� �ݾ��� �Է����ּ��� : ";
						cin >> money;

						balance = atoi(row[4]);

						total_money = balance - money;

						cout <<"\n" << row[1] << " �ŷ���ǥ" << endl;
						cout << "[���� ���]" << endl;
						cout << "---------------------------" << endl;
						cout << "��û �ݾ�: " << money << "��" << endl;
						cout << "ó����� : ����ó��\n" << endl;
						cout << "�ŷ� �� �ܾ�: " << total_money << "��" << endl;
						cout << "\n---------------------------\n";

						char* query_date = "select now()";
						len = mysql_query(conn, query_date);
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						cout << "�ŷ��Ͻ�: " << row[0] << endl;
						cout << "���¹�ȣ: " << bank_name << " " << account << endl;

						sprintf(update_money, "update newclient set money = %d where account = '%s'", total_money, account);
						len = mysql_query(conn, update_money);

					}
					else {
						cout << "\n��й�ȣ�� 3ȸ Ʋ�Ƚ��ϴ�.���� ���� �� �ʱ�ȭ������ ���ư��ϴ�.\n";


						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = '%s'", bank_name, account);
						len = mysql_query(conn, update_error);
					}

				}
				else if (strcmp(account, row[0]) == 0 && error == 3) {
					cout << "\n������ �����Դϴ�. ���� ������ ������ �� �̿����ּ���^^\n";
				}

			}
			else {
				cout << "\n�Է��Ͻ� ���¸� ã�� �� �����ϴ�. �������� �ùٸ� ���¸� �Է����ּ���\n";
			}

		}
	}
	else if (row == NULL) {
		cout << "\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. �������� �ùٸ� ������� �Է����ּ���\n";
	}

}

//�۱� �Ϸ�
void User::sending() {
	
	MYSQL* conn;//MySQL�� ������ ���
	MYSQL_RES* res;//������ ���� ����� �޴� ����
	MYSQL_ROW row; //������ ���� ���� ������ ���� ����ִ� ����

	conn = mysql_init(NULL);//�ʱ�ȭ

	//MySQl�� ����
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL ���� ����\n";
	}

	cout << "\n----------------------�۱�------------------------\n";
	cout << "������ ������ �Է����ּ��� : ";
	cin >> bank_name;

	sprintf(fbank, "select*from newclient where bank = '%s'", bank_name);

	int len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		//���� �̸� �ִ��� �˻�
		if (strcmp(bank_name, row[1]) == 0) {
			
			cout << "\n������ ���� ��ȣ�� �Է����ּ��� : ";
			cin >> account;


			sprintf(faccount, "select* from newclient where bank = '%s' and account = '%s'", bank_name, account);

			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			if (row != NULL) {
				
				error = atoi(row[5]);
				//���� �ִ��� �˻�,������ �������� Ȯ��
				if (strcmp(account, row[0]) == 0 && error < 3) {
					cout << "\n��й�ȣ�� �Է����ּ��� : ";
					cin >> password;
					//��й�ȣ Ȯ��
					for (count = error; count < 2;count++) {
						if (strcmp(password,row[3])!=0) {
						
							uperror = ++error;

							sprintf(error_count, "update newclient set error = %d where bank ='%s' and account = '%s'", uperror, bank_name, account);
							len = mysql_query(conn, error_count);

							cout << "\n��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ��� : ";
							cin >> password;

						}
						else if (strcmp(password,row[3]) == 0) {
							break;
						}
					}
					//��й�ȣ Ȯ��2
					if (strcmp(password, row[3]) == 0) {
						cout << "\n�۱��� ������ �Է����ּ��� : ";
						cin >> bank_name2;

						sprintf(fbank2, "select*from newclient where bank = '%s'", bank_name2);

						len = mysql_query(conn, fbank2);
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						if (row != NULL) {
							if (strcmp(bank_name2, row[1]) == 0) {
								cout << "\n�۱��� ���¸� �Է����ּ��� : ";
								cin >> account2;

								sprintf(faccount2, "select*from newclient where bank = '%s' and account = '%s'", bank_name2, account2);

								len = mysql_query(conn, faccount2);
								res = mysql_store_result(conn);
								row = mysql_fetch_row(res);
								if (row != NULL) {
									cout << "\n�۱��� �ݾ��� �Է����ּ��� : ";
									cin >> send_money;

									//������ ���� ������
									len = mysql_query(conn, faccount);
									res = mysql_store_result(conn);
									row = mysql_fetch_row(res);

									int balance_s = atoi(row[4]);
									money = balance_s - send_money;

									if (money >= 0) {
										sprintf(update_money, "update newclient set money = %d where account = '%s'", money, account);
										len = mysql_query(conn, update_money);
										//�۱ݹ��� ���� ������
										
										char plus[255];

										sprintf(plus, "select* from newclient where bank = '%s' and account = '%s'", bank_name2, account2);

										int len2 = mysql_query(conn, plus);
										res = mysql_store_result(conn);
										row = mysql_fetch_row(res);

										int balance_r = atoi(row[4]);

										int receive = balance_r + send_money;

										sprintf(update_money2, "update newclient set money = %d where account = '%s'", receive, account2);
										len2 = mysql_query(conn, update_money2);

										cout << "[���� �۱�]";
										cout << "\n---------------------------\n";
										cout << "��û �ݾ�: " << send_money << "��\n";
										cout << "ó����� : ���� ó��\n";

										if (strcmp(bank_name, bank_name2) == 0) {

											cout << "�ŷ� �� �ܾ�: " << money << "��\n";
											cout << "������: 0 ��\n";
										}
										else if (strcmp(bank_name, bank_name2) != 0) {
											fee = money - 500;
											printf("�ŷ� �� �ܾ�: %d ��\n", fee);
											printf("������: 500 ��\n");
											char fee2[255];
											sprintf(fee2, "update newclient set money = %d where account = '%s'", fee, account);
											len = mysql_query(conn, fee2);
										}
										cout << "---------------------------\n";

										char* query_date = "select now()";
										len = mysql_query(conn, query_date);
										res = mysql_store_result(conn);
										row = mysql_fetch_row(res);
										cout << "�ŷ��Ͻ�: " << row[0] << "\n";
									}
									else {
										cout << "\n������ ������ �ܾ��� �����մϴ�.\n";
										cout << "\n�ʱ�ȭ������ ���ư��ϴ�.\n";										
									}
								}
								else if (row == NULL) {
									cout << "\n�Է��Ͻ� ���°� �������� �ʽ��ϴ�. �������� �ùٸ� ���¸� �Է����ּ���\n";
								}
							}
						}
						else if (row == NULL) {
							cout << "\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. �������� �ùٸ� ������� �Է����ּ���\n";
						}
					}
					//���� 3ȸ ���� �� ����
					else if (strcmp(password, row[3]) != 0) {
						cout << "\n��й�ȣ�� 3ȸ Ʋ�Ƚ��ϴ�.���� ���� �� �ʱ�ȭ������ ���ư��ϴ�.\n";
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = '%s'", bank_name, account);
						len = mysql_query(conn, update_error);
					}

				}
				//error = 3�̸� ������ ����
				else if (strcmp(account, row[0]) == 0 && error == 3) {
					cout << "\n������ �����Դϴ�. ���� ������ ������ �� �̿����ּ���^^\n";
				}
			}
			//���� ã�� ���� ���
			else if (row == NULL) {
				cout << "\n�Է��Ͻ� ���¸� ã�� ���߽��ϴ�.������ �����ϰ� �Է����ּ��� ^^\n";
				cout << "�ʱ�ȭ������ ���ư��ϴ�.\n";
			}

		}
	}
	//���� ã�� ���� ���
	else if (row == NULL) {		
		cout << "\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. �������� �ùٸ� ������� �Է����ּ���\n";
	}

}

//���� ��ȸ �Ϸ�
void Account::check_balance() {
	
	MYSQL* conn;//MySQL�� ������ ���
	MYSQL_RES* res;//������ ���� ����� �޴� ����
	MYSQL_ROW row; //������ ���� ���� ������ ���� ����ִ� ����

	conn = mysql_init(NULL);//�ʱ�ȭ

	//MySQl�� ����
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL ���� ����\n";
	}

	
	cout << "\n--------------�ܾ���ȸ--------------\n";
	cout << "\n��ȸ�� ������ �Է����ּ��� : ";
	cin >> bank_name;

	sprintf(fbank,"select*from newclient where bank = '%s'",bank_name);
	int len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		if (strcmp(bank_name, row[1]) == 0) {
			cout << "\n��ȸ�� ���¹�ȣ�� �Է����ּ��� : ";
			cin >> account;

			sprintf(faccount, "select* from newclient where account = '%s' and bank = '%s'", account, bank_name);

			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (row != NULL) {
				
				if (strcmp(account,row[0])==0) {
					cout << "\n��й�ȣ�� �Է����ּ��� : ";
					cin >> password;					

					error = atoi(row[5]);
					
					//��й�ȣƲ�� �ݺ�
					for (count = error; count < 2;count++) {
						if (strcmp(password,row[3])!=0) {
							char errorcount[255];

							uperror = ++error;
							sprintf(errorcount, "update newclient set error = %d where bank ='%s' and account = '%s'", uperror, bank_name, account);
							len = mysql_query(conn, errorcount);

							cout << "\n��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ��� : ";
							cin >> password;

						}
						else if (strcmp(password, row[3]) == 0) {
							break;
						}
					}
					if (strcmp(password, row[3]) == 0) {
						
						cout << "\n------------------------------------\n";
						cout << row[2] << "���� ����" << endl;
						cout << "\n���� �ܾ�: " << row[1] << " " << row[0] << " " << row[4] << " ��\n";
						
					}
					else {
						cout << "\n��й�ȣ�� 3ȸ Ʋ�Ƚ��ϴ�.���� ���� �� �ʱ�ȭ������ ���ư��ϴ�. ^^\n";
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = '%s'", bank_name, account);
						len = mysql_query(conn, update_error);
						
					}
				}

			}
			else {
				cout << "\n�Է��Ͻ� ���¸� ã�� ���߽��ϴ�. ������ �����ϰ� �Է����ּ���^^\n";
				cout << "�ʱ�ȭ������ ���ư��ϴ�.\n";
			}
		}
	}
	else if (row == NULL) {
		cout << "\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. �������� �ùٸ� ������� �Է����ּ���^^\n";
	}
}

//���� ���� �Ϸ�
void Account::open_account() {

	MYSQL* conn;//MySQL�� ������ ���
	MYSQL_RES* res;//������ ���� ����� �޴� ����
	MYSQL_ROW row; //������ ���� ���� ������ ���� ����ִ� ����

	conn = mysql_init(NULL);//�ʱ�ȭ

	//MySQl�� ����
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL ���� ����\n";
	}

	cout << "\n--------------���� ����--------------\n";
	cout << "\n�̸��� �Է����ּ��� : ";
	cin >> name;

	string line;
	ifstream file("������.txt"); // txt ������ ����. 
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close(); // ������ ������ �ݴ´�. 
	}
	

	cout << "\n\n����Ͻ� ������ �������ּ���: ";
	cin >> bank_name;
	char txt[255];
	
	file.seekg(0, ios::beg); //���� ������ ��ġ ó������ ��������?

	
	file.open("������.txt");
	if (file.is_open()) {
		char heat[255];
		while (getline(file, line)) {
			
			strcpy(heat, line.c_str());
			if (strcmp(bank_name, heat) == 0) {
				cout << "\n����Ͻ� ��й�ȣ�� �Է����ּ���(4�ڸ�) : ";
				cin >> password;
				if (strlen(password) >= 5 || strlen(password) <= 3) {
					cout << "\n��й�ȣ�� ���̰� �ʹ� ��ϴ�. ������ �ٽ� �Է����ּ���";
					break;
				}
				srand((unsigned)time(NULL));// �ð��� ���� �ٸ� ���� ������ ���� ���
				int newaccount = rand() % (99999999 - 10000000) + 10000000;
				cout << "������ ���� : ����  ���¹�ȣ  �̸�  ��й�ȣ";
				cout << "\n������ ���� : " << bank_name << " " << newaccount << " " << name << " " << password << "\n";
				
				sprintf(open, "insert into newclient values (%d, '%s', '%s', '%s', %d, %d)", newaccount, bank_name, name, password, 0, 0);
				int len = mysql_query(conn, open);

				return;
			}			
		}
		if (strcmp(bank_name, heat) != 0) {
			cout << "\n�Է��Ͻ� ������ ��Ͽ� �������� �ʽ��ϴ�. ����� �� ����� �ּ���\n";
		}
		file.close(); // ������ ������ �ݴ´�.
	}

}

//��й�ȣ ���� �Ϸ�
void Account::change_password() {
	
	MYSQL* conn;//MySQL�� ������ ���
	MYSQL_RES* res;//������ ���� ����� �޴� ����
	MYSQL_ROW row; //������ ���� ���� ������ ���� ����ִ� ����

	conn = mysql_init(NULL);//�ʱ�ȭ

	//MySQl�� ����
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL ���� ����\n";
	}
	
	cout << "\n--------------��й�ȣ ����--------------\n";
	cout << "\n������ ����ϴ� ������ ������ �Է����ּ��� : ";
	cin >> bank_name;
		
	sprintf(fbank, "select*from newclient where bank = '%s'", bank_name);
	int len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	if (row != NULL) {
		//���� ã��
		if (strcmp(bank_name, row[1]) == 0) {

			cout << "\n������ ����ϴ� ���¹�ȣ�� �Է����ּ��� : ";
			cin >> account;

			sprintf(faccount, "select*from newclient where bank = '%s' and account = '%s'", bank_name, account);
			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			
			if (row != NULL) {
				//���� ã��
				if (strcmp(account, row[0]) == 0) {
					cout << "\n������ ��й�ȣ�� �Է����ּ��� : ";
					cin >> password;
					error = atoi(row[5]);

					if (strcmp(password, row[3]) != 0) {

						for (count = error; count < 2;count++) {
							if (strcmp(password, row[3]) != 0) {

								uperror = ++error;

								sprintf(error_count, "update newclient set error = %d where bank ='%s' and account = '%s'", uperror, bank_name, account);
								len = mysql_query(conn, error_count);

								cout << "\n��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ��� : ";
								cin >> password;

							}
							else if (strcmp(password, row[3]) == 0) {
								break;
							}
						}
					}
					if(strcmp(password, row[3]) == 0) {
						cout << "\n�����Ͻ� ��й�ȣ�� �Է����ּ��� (4�ڸ�): ";
						char change_password[15];
						cin >> change_password;

						if (strcmp(change_password,password) == 0) {
							cout << "\n���� ��й�ȣ�� ���� ��й�ȣ�Դϴ�.";
						}
						else if (strlen(change_password) >= 5 || strlen(change_password)<= 3) {
							cout << "\n4�ڸ��� �ƴմϴ�. ������ �ٽ� �Է����ּ���";
						}
						else if(strcmp(change_password,password) != 0) {
							cout << "\n���� ��й�ȣ : " << password;
							cout << "\n����� ��й�ȣ : " << change_password;

						
							sprintf(pwc,"update newclient set password = '%s' where account = '%s'",change_password,account);
							len = mysql_query(conn, pwc);
						}
						
					}
					else {
						cout << "\n��й�ȣ�� 3ȸ Ʋ�Ƚ��ϴ�. ���� ���� �� �ʱ�ȭ������ ���ư��ϴ�.\n";
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = '%s'", bank_name, account);
						len = mysql_query(conn, update_error);
					}

				}
			}
			else {
				cout << "\n�Է��Ͻ� ���¸� ã�� �� �����ϴ�. ������ �ٽ� �Է����ּ���\n";
			}

		}
	}
	else {
		cout << "\n�Է��Ͻ� ������ ã�� �� �����ϴ�. ������ �ٽ� �Է����ּ���\n";
	}
}

//������ �޴�
void Atm::management() {
	
	MYSQL* conn;//MySQL�� ������ ���
	MYSQL_RES* res;//������ ���� ����� �޴� ����
	MYSQL_ROW row; //������ ���� ���� ������ ���� ����ִ� ����

	conn = mysql_init(NULL);//�ʱ�ȭ

	//MySQl�� ����
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL ���� ����\n";
	}
	
	
	cout << "\n������ ��й�ȣ�� �����ּ���(4�ڸ�) : ";
	cin >> password;
	

	sprintf(mana,"select*from manpass where management = '%s'",password);

	int len = mysql_query(conn, mana);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		if (strcmp(password, row[0]) == 0) {
			cout << "\n===================������ ���=====================\n";
			cout << "1. ���� �߰�\n";
			cout << "2. ���� ���� ����\n";
			cout << "3. ������ ��й�ȣ ����\n";
			cout << "4. �޴��� ���ư���";
			cout << "\n===================================================\n";
			cout << "\n>> ";
			string man_menu;
			cin >> man_menu;

			int mnm = stoi(man_menu);
			//1��
			if (mnm == 1) {
				string line;
				ifstream file("������.txt"); // txt ������ ����. 
				if (file.is_open()) {
					while (getline(file, line)) {
						cout << line << endl;
					}
					file.close();
				}
				cout << "\n�߰��Ͻ� ������ �Է����ּ��� : ";
				cin >> bank_name;
				
			
				file.open("������.txt");
				if (file.is_open()) {
					char heat[255];
					while (getline(file, line)) {

						strcpy(heat, line.c_str());
						if (strcmp(bank_name, heat) == 0) {
							cout << "\n�̹� �����ϴ� �����Դϴ�.\n";
							return;
						}
						
					}
					if (strcmp(bank_name, heat) != 0) {
						file.close();
												
						string filename("������.txt");
						ofstream file2;
						file2.open(filename, ios_base::out | ios_base::app);
						file2 << "\n" << bank_name;
						

						cout << "\n���������� �߰��Ǿ����ϴ�.\n";
						file2.close();
						return;
					}

					file.close();
				}				
			}
			//2��
			else if (mnm == 2) {
				
				cout << "\n������ ������ ���¿� ������ �Է����ּ��� : ";
				cin >> account >> bank_name;


				sprintf(faccount, "select*from newclient where bank = '%s' and account = '%s'",bank_name,account);

				len = mysql_query(conn, faccount);
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);

				if (row != NULL) {
					error = atoi(row[5]);

					if (strcmp(account, row[0]) == 0 && error == 3) {
						cout << "\n������ ��й�ȣ�� �Է����ּ��� : ";
						cin >> password;

						char management[255];

						sprintf(management, "select*from manpass where management = '%s'", password);

						len = mysql_query(conn, management);
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);

						if (strcmp(password, row[0]) == 0) {
							cout << "\n���� ������ �����մϴ�. �������� �����ϰ� �Է����ּ��� ^^\n";

							sprintf(update_error, "update newclient set error = 0 where bank = '%s' and account = '%s'",bank_name ,account);
							len = mysql_query(conn, update_error);
						}
						else {
							cout << "\n������ ��й�ȣ�� Ʋ�Ƚ��ϴ�. �������� �� �Է����ּ���\n";
						}

					}
					else {
						cout << "\n���� ���°� �ƴ� �����̰ų� ���� �����Դϴ�.\n";
						cout << "�ʱ�ȭ������ ���ư��ϴ�.\n";
					}
					
				}					
			}
			//3��
			else if (mnm == 3) {
				cout << "\n\n���� ������ ��й�ȣ�� �Է����ּ���(4�ڸ�) : ";
				cin >> password;

				char newman[255];

				sprintf(newman, "select*from manpass where management = '%s'", password);

				len = mysql_query(conn, newman);
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				if (row != NULL) {
					if (strcmp(password, row[0]) == 0) {
						cout << "\n�����Ͻ� ��й�ȣ�� �Է����ּ��� (4�ڸ�): ";

						char newmannum[15];
						cin >> newmannum;
						if (strlen(newmannum) == 4) {
							char update_newman[255];
							sprintf(update_newman, "update manpass set management = '%s'", newmannum);
							len = mysql_query(conn, update_newman);

							cout << "\n����ó�� �Ǿ����ϴ�.\n";
						}
						else {
							cout << "\n��й�ȣ�� ���Ŀ� ���� �ʽ��ϴ� ������ �ٽ� �Է����ּ���\n";
						}
					}
				}
				else {
					cout << "\n�Է��Ͻ� ������ ��й�ȣ�� �ٸ��ϴ�. ������ �ٽ� �Է����ּ���^^\n";
				}
			}
			//4��
			else if(mnm ==4) {
				cout << "\n�ʱ�ȭ������ ���ư��ϴ�";
				return;
			}
			else {
				cout << "\n�ùٸ� �Է��� �ƴմϴ�.";
					return;
			}
		}
	}
	else {
		cout << "\n������ ��й�ȣ�� Ʋ�Ƚ��ϴ�. �ʱ�ȭ������ ���ư��ϴ�.\n";
	}
	
}