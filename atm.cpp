#include <iostream>
#include <string> // string 사용 위해
#include <cstring>// strcmp 등 사용 위해
#include <mysql.h> //MySQL 연동 위해
#include <fstream>
#include <time.h>//srand가 시간에 따라 다른 랜덤한 값을 받기 위해
#include "atm.h"

using namespace std;

#define HOST "localhost" // 연결 호스트 주소
#define USER "root" //사용자 이름
#define PASS "dsy4042" //MYSQL 패스워드
#define NAME "bank" //접속할 데이터베이스 이름

//입금 완료
void User :: deposit() {
	
	MYSQL* conn;//MySQL과 연결을 담당
	MYSQL_RES* res;//쿼리에 대한 결과를 받는 변수
	MYSQL_ROW row; //쿼리에 대한 실제 데이터 값이 들어있는 변수

	conn = mysql_init(NULL);//초기화

	//MySQl에 연결
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL 연결 실패\n";
	}
	
	string line;
	ifstream file("은행목록.txt"); // txt 파일을 연다. 
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close(); // 열었던 파일을 닫는다. 
	}

	cout << "\n\n은행을 선택해주세요: ";
	cin >> bank_name;

	sprintf(fbank, "select*from newclient where bank ='%s'", bank_name);
	int len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		//은행이 맞는지 검사
		if (strcmp(bank_name, row[1]) == 0) {
			cout << "\n계좌번호를 입력해주세요 : ";
			char account[15];
			cin >> account;

			sprintf(faccount,"select*from newclient where bank = '%s' and account = '%s'",bank_name,account);
			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			
			//계좌가 맞는지 검사
			if (row != NULL) {
								
				error = atoi(row[5]);
				
				if (strcmp(account,row[0])==0,error <=2) {
					cout << "\n비밀번호를 입력해주세요 : ";
					cin >> password;

					for (count = error; count < 2;count++) {
						if (strcmp(password,row[3]) != 0) {							

							uperror = ++error;

							sprintf(error_count,"update newclient set error = %d where bank ='%s' and account = '%s'",uperror,bank_name,account);
							len = mysql_query(conn, error_count);

							cout << "\n비밀번호가 틀렸습니다. 다시 입력해주세요 : ";
							cin >> password;

						}
						else if (error == 3) {
							break;
						}
						else {
							break;
						}
					}
					//비밀번호 같은지 검사
					if (strcmp(password,row[3]) == 0) {
						cout << "\n입금 금액을 입력해주세요 : ";
						cin >> money;

						balance = atoi(row[4]);
						
						total_money = balance + money;

						cout << "\n" << row[1] << " 거래명세표" << endl;
						cout << "[예금 입금]" << endl;
						cout << "---------------------------" << endl;
						cout << "요청 금액: " << money <<"원" << endl;
						cout << "처리결과 : 정상처리\n"<< endl;
						cout << "거래 후 잔액: " << total_money << "원" << endl;
						cout << "\n---------------------------\n";

						char* query_date = "select now()";
						len = mysql_query(conn, query_date);
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						cout << "거래일시: " << row[0] << endl;
						cout << "계좌번호: " << bank_name <<" "<< account << endl;

						sprintf(update_money, "update newclient set money = %d where account = '%s'", total_money, account);
						len = mysql_query(conn, update_money);

					}
					else {
						cout << "\n비밀번호를 3회 틀렸습니다.계좌 정지 후 초기화면으로 돌아갑니다.\n";


						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = '%s'", bank_name, account);
						len = mysql_query(conn, update_error);
					}

				}else if(strcmp(account, row[0]) == 0 && error ==3) {
					cout << "\n정지된 계좌입니다. 계좌 정지를 해제한 후 이용해주세요^^\n";
				}

			}
			else {
				cout << "\n입력하신 계좌를 찾을 수 없습니다. 다음에는 올바른 계좌를 입력해주세요\n";
			}

		}
	}
	else if (row == NULL) {
		cout << "\n입력하신 은행이 존재하지 않습니다. 다음에는 올바른 은행명을 입력해주세요\n";
	}

}

//출금 완료
void User::withdraw() {
	
	MYSQL* conn;//MySQL과 연결을 담당
	MYSQL_RES* res;//쿼리에 대한 결과를 받는 변수
	MYSQL_ROW row; //쿼리에 대한 실제 데이터 값이 들어있는 변수

	conn = mysql_init(NULL);//초기화

	//MySQl에 연결
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL 연결 실패\n";
	}

	string line;
	ifstream file("은행목록.txt"); // txt 파일을 연다. 
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close(); // 열었던 파일을 닫는다. 
	}

	cout << "\n\n은행을 선택해주세요: ";
	char bank_name[15];
	cin >> bank_name;

	sprintf(fbank, "select*from newclient where bank ='%s'", bank_name);
	int len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		//은행이 맞는지 검사
		if (strcmp(bank_name, row[1]) == 0) {
			cout << "\n계좌번호를 입력해주세요 : ";
			char account[15];
			cin >> account;

			sprintf(faccount, "select*from newclient where bank = '%s' and account = '%s'", bank_name, account);
			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			//계좌가 맞는지 검사
			if (row != NULL) {				

				error = atoi(row[5]);

				if (strcmp(account, row[0]) == 0, error <= 2) {
					cout << "\n비밀번호를 입력해주세요 : ";
					cin >> password;

					for (count = error; count < 2;count++) {
						if (strcmp(password, row[3]) != 0) {							

							uperror = ++error;

							sprintf(error_count, "update newclient set error = %d where bank ='%s' and account = '%s'", uperror, bank_name, account);
							len = mysql_query(conn, error_count);

							cout << "\n비밀번호가 틀렸습니다. 다시 입력해주세요 : ";
							cin >> password;

						}
						else if(error ==3) {
							break;
						}
						else {
							break;
						}
					}
					//비밀번호 같은지 검사
					if (strcmp(password, row[3]) == 0) {
						cout << "\n출금 금액을 입력해주세요 : ";
						cin >> money;

						balance = atoi(row[4]);

						total_money = balance - money;

						cout <<"\n" << row[1] << " 거래명세표" << endl;
						cout << "[예금 출금]" << endl;
						cout << "---------------------------" << endl;
						cout << "요청 금액: " << money << "원" << endl;
						cout << "처리결과 : 정상처리\n" << endl;
						cout << "거래 후 잔액: " << total_money << "원" << endl;
						cout << "\n---------------------------\n";

						char* query_date = "select now()";
						len = mysql_query(conn, query_date);
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						cout << "거래일시: " << row[0] << endl;
						cout << "계좌번호: " << bank_name << " " << account << endl;

						sprintf(update_money, "update newclient set money = %d where account = '%s'", total_money, account);
						len = mysql_query(conn, update_money);

					}
					else {
						cout << "\n비밀번호를 3회 틀렸습니다.계좌 정지 후 초기화면으로 돌아갑니다.\n";


						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = '%s'", bank_name, account);
						len = mysql_query(conn, update_error);
					}

				}
				else if (strcmp(account, row[0]) == 0 && error == 3) {
					cout << "\n정지된 계좌입니다. 계좌 정지를 해제한 후 이용해주세요^^\n";
				}

			}
			else {
				cout << "\n입력하신 계좌를 찾을 수 없습니다. 다음에는 올바른 계좌를 입력해주세요\n";
			}

		}
	}
	else if (row == NULL) {
		cout << "\n입력하신 은행이 존재하지 않습니다. 다음에는 올바른 은행명을 입력해주세요\n";
	}

}

//송금 완료
void User::sending() {
	
	MYSQL* conn;//MySQL과 연결을 담당
	MYSQL_RES* res;//쿼리에 대한 결과를 받는 변수
	MYSQL_ROW row; //쿼리에 대한 실제 데이터 값이 들어있는 변수

	conn = mysql_init(NULL);//초기화

	//MySQl에 연결
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL 연결 실패\n";
	}

	cout << "\n----------------------송금------------------------\n";
	cout << "인출할 은행을 입력해주세요 : ";
	cin >> bank_name;

	sprintf(fbank, "select*from newclient where bank = '%s'", bank_name);

	int len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		//은행 이름 있는지 검사
		if (strcmp(bank_name, row[1]) == 0) {
			
			cout << "\n인출할 계좌 번호를 입력해주세요 : ";
			cin >> account;


			sprintf(faccount, "select* from newclient where bank = '%s' and account = '%s'", bank_name, account);

			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			if (row != NULL) {
				
				error = atoi(row[5]);
				//계좌 있는지 검사,정지된 계좌인지 확인
				if (strcmp(account, row[0]) == 0 && error < 3) {
					cout << "\n비밀번호를 입력해주세요 : ";
					cin >> password;
					//비밀번호 확인
					for (count = error; count < 2;count++) {
						if (strcmp(password,row[3])!=0) {
						
							uperror = ++error;

							sprintf(error_count, "update newclient set error = %d where bank ='%s' and account = '%s'", uperror, bank_name, account);
							len = mysql_query(conn, error_count);

							cout << "\n비밀번호가 틀렸습니다. 다시 입력해주세요 : ";
							cin >> password;

						}
						else if (strcmp(password,row[3]) == 0) {
							break;
						}
					}
					//비밀번호 확인2
					if (strcmp(password, row[3]) == 0) {
						cout << "\n송금할 은행을 입력해주세요 : ";
						cin >> bank_name2;

						sprintf(fbank2, "select*from newclient where bank = '%s'", bank_name2);

						len = mysql_query(conn, fbank2);
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						if (row != NULL) {
							if (strcmp(bank_name2, row[1]) == 0) {
								cout << "\n송금할 계좌를 입력해주세요 : ";
								cin >> account2;

								sprintf(faccount2, "select*from newclient where bank = '%s' and account = '%s'", bank_name2, account2);

								len = mysql_query(conn, faccount2);
								res = mysql_store_result(conn);
								row = mysql_fetch_row(res);
								if (row != NULL) {
									cout << "\n송금할 금액을 입력해주세요 : ";
									cin >> send_money;

									//인출할 계좌 쿼리문
									len = mysql_query(conn, faccount);
									res = mysql_store_result(conn);
									row = mysql_fetch_row(res);

									int balance_s = atoi(row[4]);
									money = balance_s - send_money;

									if (money >= 0) {
										sprintf(update_money, "update newclient set money = %d where account = '%s'", money, account);
										len = mysql_query(conn, update_money);
										//송금받을 계좌 쿼리문
										
										char plus[255];

										sprintf(plus, "select* from newclient where bank = '%s' and account = '%s'", bank_name2, account2);

										int len2 = mysql_query(conn, plus);
										res = mysql_store_result(conn);
										row = mysql_fetch_row(res);

										int balance_r = atoi(row[4]);

										int receive = balance_r + send_money;

										sprintf(update_money2, "update newclient set money = %d where account = '%s'", receive, account2);
										len2 = mysql_query(conn, update_money2);

										cout << "[예금 송금]";
										cout << "\n---------------------------\n";
										cout << "요청 금액: " << send_money << "원\n";
										cout << "처리결과 : 정상 처리\n";

										if (strcmp(bank_name, bank_name2) == 0) {

											cout << "거래 후 잔액: " << money << "원\n";
											cout << "수수료: 0 원\n";
										}
										else if (strcmp(bank_name, bank_name2) != 0) {
											fee = money - 500;
											printf("거래 후 잔액: %d 원\n", fee);
											printf("수수료: 500 원\n");
											char fee2[255];
											sprintf(fee2, "update newclient set money = %d where account = '%s'", fee, account);
											len = mysql_query(conn, fee2);
										}
										cout << "---------------------------\n";

										char* query_date = "select now()";
										len = mysql_query(conn, query_date);
										res = mysql_store_result(conn);
										row = mysql_fetch_row(res);
										cout << "거래일시: " << row[0] << "\n";
									}
									else {
										cout << "\n인출할 계좌의 잔액이 부족합니다.\n";
										cout << "\n초기화면으로 돌아갑니다.\n";										
									}
								}
								else if (row == NULL) {
									cout << "\n입력하신 계좌가 존재하지 않습니다. 다음에는 올바른 계좌를 입력해주세요\n";
								}
							}
						}
						else if (row == NULL) {
							cout << "\n입력하신 은행이 존재하지 않습니다. 다음에는 올바른 은행명을 입력해주세요\n";
						}
					}
					//누적 3회 오류 시 정지
					else if (strcmp(password, row[3]) != 0) {
						cout << "\n비밀번호를 3회 틀렸습니다.계좌 정지 후 초기화면으로 돌아갑니다.\n";
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = '%s'", bank_name, account);
						len = mysql_query(conn, update_error);
					}

				}
				//error = 3이면 정지된 계좌
				else if (strcmp(account, row[0]) == 0 && error == 3) {
					cout << "\n정지된 계좌입니다. 계좌 정지를 해제한 후 이용해주세요^^\n";
				}
			}
			//계좌 찾지 못한 경우
			else if (row == NULL) {
				cout << "\n입력하신 계좌를 찾지 못했습니다.다음엔 신중하게 입력해주세요 ^^\n";
				cout << "초기화면으로 돌아갑니다.\n";
			}

		}
	}
	//은행 찾지 못한 경우
	else if (row == NULL) {		
		cout << "\n입력하신 은행이 존재하지 않습니다. 다음에는 올바른 은행명을 입력해주세요\n";
	}

}

//계좌 조회 완료
void Account::check_balance() {
	
	MYSQL* conn;//MySQL과 연결을 담당
	MYSQL_RES* res;//쿼리에 대한 결과를 받는 변수
	MYSQL_ROW row; //쿼리에 대한 실제 데이터 값이 들어있는 변수

	conn = mysql_init(NULL);//초기화

	//MySQl에 연결
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL 연결 실패\n";
	}

	
	cout << "\n--------------잔액조회--------------\n";
	cout << "\n조회할 은행을 입력해주세요 : ";
	cin >> bank_name;

	sprintf(fbank,"select*from newclient where bank = '%s'",bank_name);
	int len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		if (strcmp(bank_name, row[1]) == 0) {
			cout << "\n조회할 계좌번호를 입력해주세요 : ";
			cin >> account;

			sprintf(faccount, "select* from newclient where account = '%s' and bank = '%s'", account, bank_name);

			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (row != NULL) {
				
				if (strcmp(account,row[0])==0) {
					cout << "\n비밀번호를 입력해주세요 : ";
					cin >> password;					

					error = atoi(row[5]);
					
					//비밀번호틀림 반복
					for (count = error; count < 2;count++) {
						if (strcmp(password,row[3])!=0) {
							char errorcount[255];

							uperror = ++error;
							sprintf(errorcount, "update newclient set error = %d where bank ='%s' and account = '%s'", uperror, bank_name, account);
							len = mysql_query(conn, errorcount);

							cout << "\n비밀번호가 틀렸습니다. 다시 입력해주세요 : ";
							cin >> password;

						}
						else if (strcmp(password, row[3]) == 0) {
							break;
						}
					}
					if (strcmp(password, row[3]) == 0) {
						
						cout << "\n------------------------------------\n";
						cout << row[2] << "님의 계좌" << endl;
						cout << "\n현재 잔액: " << row[1] << " " << row[0] << " " << row[4] << " 원\n";
						
					}
					else {
						cout << "\n비밀번호를 3회 틀렸습니다.계좌 정지 후 초기화면으로 돌아갑니다. ^^\n";
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = '%s'", bank_name, account);
						len = mysql_query(conn, update_error);
						
					}
				}

			}
			else {
				cout << "\n입력하신 계좌를 찾지 못했습니다. 다음엔 신중하게 입력해주세요^^\n";
				cout << "초기화면으로 돌아갑니다.\n";
			}
		}
	}
	else if (row == NULL) {
		cout << "\n입력하신 은행이 존재하지 않습니다. 다음에는 올바른 은행명을 입력해주세요^^\n";
	}
}

//계좌 생성 완료
void Account::open_account() {

	MYSQL* conn;//MySQL과 연결을 담당
	MYSQL_RES* res;//쿼리에 대한 결과를 받는 변수
	MYSQL_ROW row; //쿼리에 대한 실제 데이터 값이 들어있는 변수

	conn = mysql_init(NULL);//초기화

	//MySQl에 연결
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL 연결 실패\n";
	}

	cout << "\n--------------계좌 생성--------------\n";
	cout << "\n이름을 입력해주세요 : ";
	cin >> name;

	string line;
	ifstream file("은행목록.txt"); // txt 파일을 연다. 
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close(); // 열었던 파일을 닫는다. 
	}
	

	cout << "\n\n사용하실 은행을 선택해주세요: ";
	cin >> bank_name;
	char txt[255];
	
	file.seekg(0, ios::beg); //파일 포인터 위치 처음으로 돌려놓음?

	
	file.open("은행목록.txt");
	if (file.is_open()) {
		char heat[255];
		while (getline(file, line)) {
			
			strcpy(heat, line.c_str());
			if (strcmp(bank_name, heat) == 0) {
				cout << "\n사용하실 비밀번호를 입력해주세요(4자리) : ";
				cin >> password;
				if (strlen(password) >= 5 || strlen(password) <= 3) {
					cout << "\n비밀번호의 길이가 너무 깁니다. 다음에 다시 입력해주세요";
					break;
				}
				srand((unsigned)time(NULL));// 시간에 따라 다른 난수 생성을 위해 사용
				int newaccount = rand() % (99999999 - 10000000) + 10000000;
				cout << "생성된 계좌 : 은행  계좌번호  이름  비밀번호";
				cout << "\n생성된 계좌 : " << bank_name << " " << newaccount << " " << name << " " << password << "\n";
				
				sprintf(open, "insert into newclient values (%d, '%s', '%s', '%s', %d, %d)", newaccount, bank_name, name, password, 0, 0);
				int len = mysql_query(conn, open);

				return;
			}			
		}
		if (strcmp(bank_name, heat) != 0) {
			cout << "\n입력하신 은행이 목록에 존재하지 않습니다. 목록을 잘 살펴봐 주세요\n";
		}
		file.close(); // 열었던 파일을 닫는다.
	}

}

//비밀번호 변경 완료
void Account::change_password() {
	
	MYSQL* conn;//MySQL과 연결을 담당
	MYSQL_RES* res;//쿼리에 대한 결과를 받는 변수
	MYSQL_ROW row; //쿼리에 대한 실제 데이터 값이 들어있는 변수

	conn = mysql_init(NULL);//초기화

	//MySQl에 연결
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL 연결 실패\n";
	}
	
	cout << "\n--------------비밀번호 변경--------------\n";
	cout << "\n변경을 희망하는 계좌의 은행을 입력해주세요 : ";
	cin >> bank_name;
		
	sprintf(fbank, "select*from newclient where bank = '%s'", bank_name);
	int len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	if (row != NULL) {
		//은행 찾기
		if (strcmp(bank_name, row[1]) == 0) {

			cout << "\n변경을 희망하는 계좌번호를 입력해주세요 : ";
			cin >> account;

			sprintf(faccount, "select*from newclient where bank = '%s' and account = '%s'", bank_name, account);
			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			
			if (row != NULL) {
				//계좌 찾기
				if (strcmp(account, row[0]) == 0) {
					cout << "\n기존의 비밀번호를 입력해주세요 : ";
					cin >> password;
					error = atoi(row[5]);

					if (strcmp(password, row[3]) != 0) {

						for (count = error; count < 2;count++) {
							if (strcmp(password, row[3]) != 0) {

								uperror = ++error;

								sprintf(error_count, "update newclient set error = %d where bank ='%s' and account = '%s'", uperror, bank_name, account);
								len = mysql_query(conn, error_count);

								cout << "\n비밀번호가 틀렸습니다. 다시 입력해주세요 : ";
								cin >> password;

							}
							else if (strcmp(password, row[3]) == 0) {
								break;
							}
						}
					}
					if(strcmp(password, row[3]) == 0) {
						cout << "\n변경하실 비밀번호를 입력해주세요 (4자리): ";
						char change_password[15];
						cin >> change_password;

						if (strcmp(change_password,password) == 0) {
							cout << "\n현재 비밀번호와 같은 비밀번호입니다.";
						}
						else if (strlen(change_password) >= 5 || strlen(change_password)<= 3) {
							cout << "\n4자리가 아닙니다. 다음에 다시 입력해주세요";
						}
						else if(strcmp(change_password,password) != 0) {
							cout << "\n기존 비밀번호 : " << password;
							cout << "\n변경된 비밀번호 : " << change_password;

						
							sprintf(pwc,"update newclient set password = '%s' where account = '%s'",change_password,account);
							len = mysql_query(conn, pwc);
						}
						
					}
					else {
						cout << "\n비밀번호를 3회 틀렸습니다. 계좌 정지 후 초기화면으로 돌아갑니다.\n";
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = '%s'", bank_name, account);
						len = mysql_query(conn, update_error);
					}

				}
			}
			else {
				cout << "\n입력하신 계좌를 찾을 수 없습니다. 다음에 다시 입력해주세요\n";
			}

		}
	}
	else {
		cout << "\n입력하신 은행을 찾을 수 없습니다. 다음에 다시 입력해주세요\n";
	}
}

//관리자 메뉴
void Atm::management() {
	
	MYSQL* conn;//MySQL과 연결을 담당
	MYSQL_RES* res;//쿼리에 대한 결과를 받는 변수
	MYSQL_ROW row; //쿼리에 대한 실제 데이터 값이 들어있는 변수

	conn = mysql_init(NULL);//초기화

	//MySQl에 연결
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);

	if (!conn) {
		cout << "MySQL 연결 실패\n";
	}
	
	
	cout << "\n관리자 비밀번호를 눌러주세요(4자리) : ";
	cin >> password;
	

	sprintf(mana,"select*from manpass where management = '%s'",password);

	int len = mysql_query(conn, mana);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		if (strcmp(password, row[0]) == 0) {
			cout << "\n===================관리자 모드=====================\n";
			cout << "1. 은행 추가\n";
			cout << "2. 계좌 정지 해제\n";
			cout << "3. 관리자 비밀번호 변경\n";
			cout << "4. 메뉴로 돌아가기";
			cout << "\n===================================================\n";
			cout << "\n>> ";
			string man_menu;
			cin >> man_menu;

			int mnm = stoi(man_menu);
			//1번
			if (mnm == 1) {
				string line;
				ifstream file("은행목록.txt"); // txt 파일을 연다. 
				if (file.is_open()) {
					while (getline(file, line)) {
						cout << line << endl;
					}
					file.close();
				}
				cout << "\n추가하실 은행을 입력해주세요 : ";
				cin >> bank_name;
				
			
				file.open("은행목록.txt");
				if (file.is_open()) {
					char heat[255];
					while (getline(file, line)) {

						strcpy(heat, line.c_str());
						if (strcmp(bank_name, heat) == 0) {
							cout << "\n이미 존재하는 은행입니다.\n";
							return;
						}
						
					}
					if (strcmp(bank_name, heat) != 0) {
						file.close();
												
						string filename("은행목록.txt");
						ofstream file2;
						file2.open(filename, ios_base::out | ios_base::app);
						file2 << "\n" << bank_name;
						

						cout << "\n정상적으로 추가되었습니다.\n";
						file2.close();
						return;
					}

					file.close();
				}				
			}
			//2번
			else if (mnm == 2) {
				
				cout << "\n정지를 해제할 계좌와 은행을 입력해주세요 : ";
				cin >> account >> bank_name;


				sprintf(faccount, "select*from newclient where bank = '%s' and account = '%s'",bank_name,account);

				len = mysql_query(conn, faccount);
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);

				if (row != NULL) {
					error = atoi(row[5]);

					if (strcmp(account, row[0]) == 0 && error == 3) {
						cout << "\n관리자 비밀번호를 입력해주세요 : ";
						cin >> password;

						char management[255];

						sprintf(management, "select*from manpass where management = '%s'", password);

						len = mysql_query(conn, management);
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);

						if (strcmp(password, row[0]) == 0) {
							cout << "\n계좌 정지를 해제합니다. 다음에는 신중하게 입력해주세요 ^^\n";

							sprintf(update_error, "update newclient set error = 0 where bank = '%s' and account = '%s'",bank_name ,account);
							len = mysql_query(conn, update_error);
						}
						else {
							cout << "\n관리자 비밀번호가 틀렸습니다. 다음에는 잘 입력해주세요\n";
						}

					}
					else {
						cout << "\n정지 상태가 아닌 계좌이거나 없는 계좌입니다.\n";
						cout << "초기화면으로 돌아갑니다.\n";
					}
					
				}					
			}
			//3번
			else if (mnm == 3) {
				cout << "\n\n기존 관리자 비밀번호를 입력해주세요(4자리) : ";
				cin >> password;

				char newman[255];

				sprintf(newman, "select*from manpass where management = '%s'", password);

				len = mysql_query(conn, newman);
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				if (row != NULL) {
					if (strcmp(password, row[0]) == 0) {
						cout << "\n변경하실 비밀번호를 입력해주세요 (4자리): ";

						char newmannum[15];
						cin >> newmannum;
						if (strlen(newmannum) == 4) {
							char update_newman[255];
							sprintf(update_newman, "update manpass set management = '%s'", newmannum);
							len = mysql_query(conn, update_newman);

							cout << "\n정상처리 되었습니다.\n";
						}
						else {
							cout << "\n비밀번호의 형식에 맞지 않습니다 다음에 다시 입력해주세요\n";
						}
					}
				}
				else {
					cout << "\n입력하신 관리자 비밀번호가 다릅니다. 다음에 다시 입력해주세요^^\n";
				}
			}
			//4번
			else if(mnm ==4) {
				cout << "\n초기화면으로 돌아갑니다";
				return;
			}
			else {
				cout << "\n올바른 입력이 아닙니다.";
					return;
			}
		}
	}
	else {
		cout << "\n관리자 비밀번호가 틀렸습니다. 초기화면으로 돌아갑니다.\n";
	}
	
}