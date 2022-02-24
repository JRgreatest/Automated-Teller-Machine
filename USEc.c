//C로 ATM
#include <stdio.h>
#include <mysql.h> //MySQL을 연결하기 위해 필요한 해더파일
#include <string.h>
#include <stdlib.h>// atoi, itoa 사용을 위해
#include <time.h>//srand가 시간에 따라 다른 랜덤한 값을 받기 위해

#define HOST "localhost" // 연결 호스트 주소
#define USER "root" //사용자 이름
#define PASS "dsy4042" //MYSQL 패스워드
#define NAME "bank" //접속할 데이터베이스 이름
#define _CRT_SECURE_NO_WARNINGS //fopen 보안 경고로 인한 컴파일 에러 방지
#define MAX 1000

int amenu;
char bank_name[11];
char update_error[255];
char fee2[255];
int password;
int account1, account2, money ,money1, money2, count;
int fee;
char atmmenu[100];
int len;// query 사용을 위해

MYSQL* conn;//MySQL과 연결을 담당
MYSQL_RES* res;//쿼리에 대한 결과를 받는 변수
MYSQL_ROW row; //쿼리에 대한 실제 데이터 값이 들어있는 변수

//1번 입금=완료
void deposit() {
	char update_money[255];
	char fbank[255];
	char faccount[255];
	int acc = 0;
	int balance = 0;
	int pw = 0;
	int len2;
	int error = 0;

	printf("\n-------------입금--------------\n\n");
	FILE* fp = fopen("은행목록.txt", "r"); //은행 목록을 가져오기 위해 읽기 및 추가모드
	char buffer[MAX] = { 0, };

	fread(buffer, 1, MAX, fp);// 전체 읽어오기
	printf("% s", buffer);
	fclose(fp);//파일 닫기

	printf("\n\n은행을 선택해주세요: ");
	scanf("%s", &bank_name);

	sprintf(fbank, "select*from newclient where bank ='%s'", bank_name);
	len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	//row 값이 NULL인지 아닌지 검사
	if (row != NULL) {
		//은행 맞는지 검사
		if (strcmp(bank_name, row[1]) == 0) {
			
			printf("\n계좌번호를 입력해주세요: ");
			scanf("%d", &account1);

			sprintf(faccount, "select * from newclient where bank = '%s' and account = %d", bank_name, account1);

			len2 = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			
			//계좌가 올바른지 검사
			if (row != NULL) {
				
				error = atoi(row[5]);
				acc = atoi(row[0]);
				if (account1 == acc,error <=2) { 
					
					printf("\n비밀번호를 입력해주세요 : ");
					scanf("%d", &password);
					getchar();
					
					pw = atoi(row[3]);
					for (count = 0; count < 2;count++) {
						if (password != pw) {
							char errorcount[255];
							int uperror;
							uperror = ++error;
							sprintf(errorcount, "update newclient set error = %d where bank ='%s' and account = %d", uperror, bank_name, account1);
							len = mysql_query(conn, errorcount);

							printf("\n비밀번호가 틀렸습니다. 다시 입력해주세요 : ");
							scanf("%d",&password);

						}
						else if (password == pw) {
							break;
						}
					}
					//비밀번호가 올바른지 검사
					if (password == pw) {
						printf("\n입금 금액을 입력해주세요 : ");
						scanf("%d", &money1);

						balance = atoi(row[4]);

						money = balance + money1;
						
						printf("\n%s 거래명세표\n", row[1]);
						printf("[예금 입금]");
						printf("\n---------------------------\n");
						printf("요청 금액: %d 원\n", money1);
						printf("처리결과 : 정상처리\n");
						printf("거래 후 잔액: %d 원\n", money);						
						printf("\n---------------------------\n");

						char* query_date = "select now()";

						len = mysql_query(conn, query_date);
						res = mysql_store_result(conn);
						while ((row = mysql_fetch_row(res)) != NULL) {
							printf("거래일시: %s", row[0]);
							printf("\n계좌번호: %s %d\n\n", bank_name, account1);
						}
						sprintf(update_money, "update newclient set money = %d where account = %d", money, account1);
						len = mysql_query(conn, update_money);
					}
					else {
						
						printf("\n비밀번호를 3회 틀렸습니다. 계좌 정지 후 초기화면으로 돌아갑니다.\n");

						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = %d", bank_name, account1);
						len = mysql_query(conn, update_error);
						
						system("pause");
						system("cls");
					}

				}			
				else if (account1 == acc,error == 3) {
					printf("\n정지된 계좌입니다. 계좌 정지를 해제한 후 이용해주세요^^\n");
					system("pause");
					system("cls");
				}
				
			}
			else if (row == NULL) {
				
				printf("\n입력하신 계좌를 찾을 수 없습니다. 다음에는 올바른 계좌를 입력해주세요\n");
				system("pause");
				system("cls");
					
			}
		}		
	}
	else if(row == NULL) {
		printf("\n입력하신 은행이 존재하지 않습니다. 다음에는 올바른 은행명을 입력해주세요\n");
		system("pause");
		system("cls");
	}
	
}

//2번 출금=완료
void withdraw() {
	char withdraw[255];
	char fbank[255];
	char update_money[255];
	int faccount = 0;
	int balance = 0;
	int pw = 0;
	int error = 0;
	printf("\n-------------출금--------------\n");
	FILE* fp = fopen("은행목록.txt", "r"); //은행 목록을 가져오기 위해 읽기 및 추가모드
	char buffer[MAX] = { 0, };

	fread(buffer, 1, MAX, fp);// 전체 읽어오기
	printf("% s", buffer);
	fclose(fp);//파일 닫기

	printf("\n\n은행을 선택해주세요: ");
	scanf("%s", &bank_name);
	
	sprintf(fbank,"select*from newclient where bank = '%s'",bank_name);

	len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	if (row != NULL) {
		//은행 맞는지 검사
		if (strcmp(bank_name, row[1]) == 0) {

			printf("\n계좌번호를 입력해주세요: ");
			scanf("%d", &account1);

			sprintf(withdraw, "select * from newclient where bank = '%s' and account = %d", bank_name, account1);

			len = mysql_query(conn, withdraw);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			
			if (row != NULL) {
				error = atoi(row[5]);
				faccount = atoi(row[0]);
				//계좌 맞는지 검사
				if (account1 == faccount, error ==0) {
					printf("\n비밀번호를 입력해주세요 : ");
					scanf("%d", &password);
					getchar();

					pw = atoi(row[3]);
					
					for (count = 0; count < 2;count++) {
						if (password != pw) {
							char errorcount[255];
							int uperror;
							uperror = ++error;
							sprintf(errorcount, "update newclient set error = %d where bank ='%s' and account = %d", uperror, bank_name, account1);
							len = mysql_query(conn, errorcount);

							printf("\n비밀번호가 틀렸습니다. 다시 입력해주세요 : ");
							scanf("%d", &password);

						}
						else if (password == pw) {
							break;
						}
					}
					//비밀번호 맞는지 검사
					if (password == pw) {
						printf("\n출금 금액을 입력해주세요 : ");
						scanf("%d", &money1);

						balance = atoi(row[4]);

						money = balance - money1;
						//출금 가능한지 검사
						if (money >= 0) {
							printf("\n%s 거래명세표\n", row[1]);
							printf("[예금 출금]");
							printf("\n---------------------------\n");
							printf("요청 금액: %d 원\n", money1);
							printf("처리결과 : 정상 처리\n");
							printf("거래 후 잔액: %d 원\n", money);
							printf("수수료: 0 원\n");
							printf("---------------------------\n");

							char* query_date = "select now()";

							len = mysql_query(conn, query_date);
							res = mysql_store_result(conn);
							while ((row = mysql_fetch_row(res)) != NULL) {
								printf("거래일시: %s", row[0]);
								printf("\n계좌번호: %d\n\n", account1);
							}
							sprintf(update_money, "update newclient set money = %d where account = %d", money, account1);
							len = mysql_query(conn, update_money);
						}
						else {
							printf("XXXXXXXXXX 경고: 잔액 부족 XXXXXXXXXXXX\n");
							printf("초기화면으로 돌아갑니다.\n");
							system("pause");
							system("cls");

						}
					}
					else {
						printf("\n비밀번호를 3회 틀렸습니다. 계좌 정지 후 초기화면으로 돌아갑니다.");
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = %d", bank_name, account1);
						len = mysql_query(conn, update_error);
						system("pause");
						system("cls");
					}
				}
				else if (account1 == faccount, error == 3) {
					printf("\n정지된 계좌입니다. 계좌 정지를 해제한 후 이용해주세요^^\n");
					system("pause");
					system("cls");
				}
			}
			else if (row == NULL) {
				printf("\n입력하신 계좌를 찾지 못했습니다. 다음엔 신중하게 입력해주세요^^\n");
				printf("초기화면으로 돌아갑니다.\n");
				system("pause");
				system("cls");
			}
		}
		
	}
	else if (row == NULL) {
		printf("\n입력하신 은행이 존재하지 않습니다. 다음에는 올바른 은행명을 입력해주세요\n");
		system("pause");
		system("cls");
	}
}

//3번 송금=완료
void sending() {
	char plus[255], fname[255];
	char bank_name2[11];
	char update_money1[255], update_money2[255];
	char fbank[255],faccount[255], faccount2[255];
	int len2 , send;
	int balance_f = 0, balance_l = 0;
	int pw = 0,error = 0,facc = 0, facc2 = 0;

	printf("\n----------------------송금------------------------\n");
	printf("인출할 은행을 입력해주세요 : ");
	scanf("%s",&bank_name);
	
	sprintf(fbank, "select*from newclient where bank = '%s'", bank_name);

	len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	if (row != NULL) {
		
		if (strcmp(bank_name, row[1]) == 0) {
			printf("\n인출할 계좌 번호를 입력해주세요 : ");
			scanf("%d", &account1);

			sprintf(faccount, "select* from newclient where bank = '%s' and account = %d", bank_name, account1);
			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (row != NULL) {
				error = atoi(row[5]);
				facc = atoi(row[0]);
				if (account1 == facc, error >= 0,error<3) {
					printf("\n비밀번호를 입력해주세요 : ");
					scanf("%d", &password);

					pw = atoi(row[3]);
					//비밀번호틀림 반복
					for (count = 0; count < 2;count++) {
						if (password != pw) {
							char errorcount[255];
							int uperror;
							uperror = ++error;
							sprintf(errorcount,"update newclient set error = %d where bank ='%s' and account = %d",uperror,bank_name,account1);
							len = mysql_query(conn, errorcount);

							printf("\n비밀번호가 틀렸습니다. 다시 입력해주세요 : ");
							scanf("%d", &password);
							
						}
						else if (password == pw) {
							break;
						}
					}
					if (password == pw) {
						printf("\n송금할 은행을 입력해주세요 : ");
						scanf("%s", &bank_name2);
						
						sprintf(fname,"select*from newclient where bank = '%s'",bank_name2);

						len = mysql_query(conn, fname);
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						if (row != NULL) {

							if (strcmp(bank_name2, row[1]) == 0) {
								printf("\n송금할 계좌를 입력해주세요 : ");
								scanf("%d", &account2);

								sprintf(faccount2,"select*from newclient where bank = '%s' and account = %d",bank_name2,account2);

								len = mysql_query(conn, faccount2);
								res = mysql_store_result(conn);
								row = mysql_fetch_row(res);

								if (row != NULL) {
									facc2 = atoi(row[0]);
									printf("\n송금할 금액을 입력해주세요 : ");
									scanf("%d", &money1);

									//인출할 계좌 쿼리문
									len = mysql_query(conn, faccount);
									res = mysql_store_result(conn);
									row = mysql_fetch_row(res);

									balance_f = atoi(row[4]);

									money = balance_f - money1;

									//잔고가 넉넉할 경우
									if (money >= 0) {
										sprintf(update_money1, "update newclient set money = %d where account = %d", money, account1);
										len = mysql_query(conn, update_money1);

										//송금받을 계좌 쿼리문
										sprintf(plus, "select* from newclient where bank = '%s' and account = %d", bank_name2, account2);
										len2 = mysql_query(conn, plus);
										res = mysql_store_result(conn);
										row = mysql_fetch_row(res);

										balance_l = atoi(row[4]);

										send = balance_l + money1;

										sprintf(update_money2, "update newclient set money = %d where account = %d", send, account2);
										len2 = mysql_query(conn, update_money2);

										printf("[예금 송금]");
										printf("\n---------------------------\n");
										printf("요청 금액: %d 원\n", money1);
										printf("처리결과 : 정상 처리\n");
										
										if (strcmp(bank_name,bank_name2) == 0) {

											printf("거래 후 잔액: %d 원\n", money);
											printf("수수료: 0 원\n");
										}
										else if (strcmp(bank_name,bank_name2) != 0) {
											fee = money - 500;
											printf("거래 후 잔액: %d 원\n", fee);
											printf("수수료: 500 원\n");
											sprintf(fee2, "update newclient set money = %d where account = %d", fee, account1);
											len = mysql_query(conn, fee2);
										}
										printf("---------------------------\n");


										char* query_date = "select now()";
										len = mysql_query(conn, query_date);
										res = mysql_store_result(conn);
										row = mysql_fetch_row(res);
										printf("거래일시: %s\n", row[0]);

									}
									else {
										printf("\n인출할 계좌의 잔액이 부족합니다.\n");
										printf("\n초기화면으로 돌아갑니다.\n");
										system("pause");
										system("cls");
									}
								}
								else if (row == NULL) {
									printf("\n입력하신 계좌를 찾지 못했습니다. 다음엔 신중하게 입력해주세요^^\n");
									printf("초기화면으로 돌아갑니다.\n");
									system("pause");
									system("cls");
								}
							}
						}
						else if (row == NULL) {
							printf("\n입력하신 은행이 존재하지 않습니다. 다음에는 올바른 은행명을 입력해주세요\n");
							system("pause");
							system("cls");
						}
					}
					else {
						printf("\n비밀번호를 3회 틀렸습니다. 계좌 정지 후 초기화면으로 돌아갑니다.\n");
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = %d", bank_name, account1);
						len = mysql_query(conn, update_error);
						system("pause");
						system("cls");
					}
				}
				else if (account1 == facc, error == 3) {
					printf("\n정지된 계좌입니다. 계좌 정지를 해제한 후 이용해주세요^^\n");
					system("pause");
					system("cls");
				}
			}
			else if (row == NULL) {
				printf("\n입력하신 계좌를 찾지 못했습니다. 다음엔 신중하게 입력해주세요^^\n");
				printf("초기화면으로 돌아갑니다.\n");
				system("pause");
				system("cls");
			}
		}
	}
	else if (row == NULL) {
		printf("\n입력하신 은행이 존재하지 않습니다. 다음에는 올바른 은행명을 입력해주세요\n");
		system("pause");
		system("cls");
	}
}

//4번 잔액조회=완료
void check_balance() {
	
	char balance[255];
	char fbank[255];
	int faccount = 0;
	int pw = 0, error;

	
	printf("\n--------------잔액조회--------------\n");
	printf("\n조회할 은행을 입력해주세요 : ");
	scanf("%s",&bank_name);
	
	sprintf(fbank,"select*from newclient where bank ='%s'",bank_name);

	len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		if (strcmp(bank_name, row[1]) == 0) {
			printf("\n조회할 계좌번호를 입력해주세요 : ");
			scanf("%d", &account1);

			sprintf(balance, "select* from newclient where account = % d and bank = '%s'", account1, bank_name);

			len = mysql_query(conn, balance);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			
			if (row != NULL) {
				
				faccount = atoi(row[0]);
				
				if (faccount == account1) {
					printf("\n비밀번호를 입력해주세요 : ");
					scanf("%d", &password);
					getchar();
					
					error = atoi(row[5]);
					pw = atoi(row[3]);
					//비밀번호틀림 반복
					for (count = 0; count < 2;count++) {
						if (password != pw) {
							char errorcount[255];
							int uperror;
							uperror = ++error;
							sprintf(errorcount, "update newclient set error = %d where bank ='%s' and account = %d", uperror, bank_name, account1);
							len = mysql_query(conn, errorcount);

							printf("\n비밀번호가 틀렸습니다. 다시 입력해주세요 : ");
							scanf("%d", &password);

						}
						else if (password == pw) {
							break;
						}
					}
					if (password == pw) {
						printf("\n------------------------------------\n");
						printf("\n현재 잔액: %s %s %s 원\n", row[1], row[0], row[4]);
						system("pause");
					}
					else {
						printf("\n비밀번호를 3회 틀렸습니다. 계좌 정지 후 초기화면으로 돌아갑니다.^^\n");
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = %d", bank_name, account1);
						len = mysql_query(conn, update_error);
						system("pause");
						system("cls");
					}
				}
				
			}
			else {
				printf("\n입력하신 계좌를 찾지 못했습니다. 다음엔 신중하게 입력해주세요^^\n");
				printf("초기화면으로 돌아갑니다.\n");
				system("pause");
				system("cls");
			}
		}
	}
	else if (row == NULL) {
		printf("\n입력하신 은행이 존재하지 않습니다. 다음에는 올바른 은행명을 입력해주세요^^\n");
		system("pause");
		system("cls");
	}
}

//5번 계좌 생성 = 완료
void open_account() {
	char open[255];
	char fbank[255];
	char name[30];
	int newaccount = 0;
	int ps = 0;
	printf("\n--------------계좌 생성--------------\n");
	printf("\n이름을 입력해주세요 : ");
	scanf("%s", &name);

	FILE* fp;
	fp = fopen("은행목록.txt", "r"); //은행 목록을 가져오기 위해 읽기 및 추가모드
	char buffer[MAX] = { 0, };

	fread(buffer, 1, MAX, fp);// 전체 읽어오기
	printf("\n%s", buffer);
	
	fclose(fp);

	printf("\n\n사용하실 은행을 입력해주세요 : ");
	scanf("%s",&bank_name);
	getchar();
	
	char* ptr = strtok(buffer,"\n");
	while (true) {
		ptr = strtok(NULL, "\n");// 다음 문자열을 잘라서 포인터를 반환

		if (ptr == NULL) {
			break;
		}
		else if (strcmp(ptr, bank_name) == 0) {
			printf("\n사용하실 비밀번호를 입력해주세요(4자리) : ");
			scanf("%d", &password);

			srand((unsigned)time(NULL));// 시간에 따라 다른 난수 생성을 위해 사용
			newaccount = rand() % (99999999 - 10000000) + 10000000;
			printf("생성된 계좌 : 은행  계좌번호  이름  비밀번호");
			printf("\n생성된 계좌 : %s %d  %s  %d \n", bank_name, newaccount, name, password);



			sprintf(open, "insert into newclient values (%d, '%s', '%s', %d, %d, %d)", newaccount, bank_name, name, password, 0, 0);
			len = mysql_query(conn, open);

			system("pause");
			system("cls");
			return;
		}
	}		 
	printf("\n입력하신 은행이 존재하지 않습니다. 목록을 잘 살펴봐 주세요\n");
	system("pause");
	system("cls");
				
	fclose(fp);
	
}

//6번 비밀번호 변경
void change_password() {
	char pwc[255],fbank[255],faccount[255];
	char update_pw[255];
	int pw = 0;
	int change = 0;
	int acc, error;

	printf("\n--------------비밀번호 변경--------------\n");
	printf("\n변경을 희망하는 계좌의 은행을 입력해주세요 : ");
	scanf("%s",&bank_name);

	sprintf(fbank, "select*from newclient where bank ='%s'", bank_name);

	len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		if (strcmp(bank_name, row[1]) == 0) {
			printf("\n변경을 희망하는 계좌번호를 입력해주세요 : ");
			scanf("%d", &account1);

			sprintf(faccount, "select * from newclient where bank = '%s' and account = %d", bank_name, account1);

			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (row != NULL) {
				acc = atoi(row[0]);
				if (account1 == acc) {
					printf("\n계좌의 기존 4자리 비밀번호를 입력해주세요 : ");
					scanf("%d", &password);

					sprintf(pwc, "select*from newclient where account = %d", account1);

					len = mysql_query(conn, pwc);
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					error = atoi(row[5]);
					pw = atoi(row[3]);
					
					//비밀번호틀림 반복
					for (count = 0; count < 2;count++) {
						if (password != pw) {
							char errorcount[255];
							int uperror;
							uperror = ++error;
							sprintf(errorcount, "update newclient set error = %d where bank ='%s' and account = %d", uperror, bank_name, account1);
							len = mysql_query(conn, errorcount);

							printf("\n비밀번호가 틀렸습니다. 다시 입력해주세요 : ");
							scanf("%d", &password);

						}
						else if (password == pw) {
							break;
						}
					}
					if (password == pw) {
						printf("\n변경하실 4자리 비밀번호를 입력해주세요 : ");
						scanf("%d", &change);
						if(password == change){
							printf("\n현재 비밀번호와 같은 비밀번호 입니다. 초기화면으로 돌아갑니다.\n");

						}
						else if (change>9999 || change<1000) {
							printf("\n4자리 비밀번호가 아닙니다. 초기화면으로 돌아갑니다.\n");
						}
						else {
							printf("\n기존 비밀번호 : %s\n", row[3]);
							printf("\n변경된 비밀번호 : %d\n", change);

							sprintf(update_pw, "update newclient set password = %d where account = %d", change, account1);
							len = mysql_query(conn, update_pw);
						}
					}
					else {
						printf("\n비밀번호를 3회 틀렸습니다. 계좌 정지 후 초기화면으로 돌아갑니다.\n");
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = %d", bank_name, account1);
						len = mysql_query(conn, update_error);
						system("pause");
						system("cls");
					}

				}
			}
			else if (row == NULL) {
				
				printf("\n입력하신 계좌를 찾을 수 없습니다. 다음에는 올바른 계좌를 입력해주세요\n");
				system("pause");
				system("cls");
				
			}
		}
	}
	else if (row == NULL) {
		printf("\n입력하신 은행이 존재하지 않습니다. 다음에는 올바른 은행명을 입력해주세요\n");
		system("pause");
		system("cls");
	}
}

//7번 관리자 메뉴 = 완료
void management() {
	int mnm = 0;
	int pass = 0;
	int man_password = 0;
	char manpass[255];

	printf("\n관리자 비밀번호를 눌러주세요(4자리) : ");
	scanf("%d",&pass);
	
	sprintf(manpass,"select*from manpass where management = %d",pass);
	len = mysql_query(conn, manpass);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	if(row != NULL){
		
		man_password = atoi(row[0]);

		if (pass == man_password) {
			printf("\n===================관리자 모드=====================\n");
			printf("1. 은행 추가\n");
			printf("2. 계좌 정지 해제\n");
			printf("3. 관리자 비밀번호 변경\n");
			printf("4. 메뉴로 돌아가기");
			printf("\n===================================================\n");
			printf("\n>> ");
			scanf("%d", &mnm);
			//1번 완료
			if (mnm == 1) {
				
				FILE* fp;
				fp = fopen("은행목록.txt", "r"); //은행 목록을 가져오기 위해 읽기 모드
				char buffer[MAX] = { 0, };

				fread(buffer, 1, MAX, fp);// 전체 읽어오기
				printf("% s",buffer);
				
				fclose(fp);

				printf("\n추가하실 은행을 입력해주세요 : ");
				scanf("%s",&bank_name);
				
				FILE* fp2;
				fp2 = fopen("은행목록.txt", "a+"); //은행 목록에 추가하기 위해 읽기 및 추가모드
				
				char* ptr = strtok(buffer, "\n");
				while (true) {
					ptr = strtok(NULL, "\n");// 다음 문자열을 잘라서 포인터를 반환

					if (ptr == NULL) {
						break;
					}
					else if (strcmp(ptr, bank_name) == 0) {
						printf("\n이미 존재하는 은행입니다.\n");
						return;
					}
					
				}
				fprintf(fp2, "\n%s", bank_name);

				printf("\n정상적으로 추가되었습니다\n");
				system("pause");
				system("cls");

				fclose(fp2);
			}
			//2번
			else if (mnm == 2) {
				char faccount[255];
				int find = 0;
				int pw = 0;
				char man[255];

				printf("\n정지를 해제하실 은행과 계좌를 입력해주세요 : ");
				scanf("%s %d",&bank_name,&account1);

				sprintf(faccount,"select*from newclient where bank = '%s' and account = %d and error = 3",bank_name,account1);

				len = mysql_query(conn, faccount);
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);

				if (row != NULL) {
					find = atoi(row[0]);
					if (strcmp(bank_name,row[1]) == 0, find == account1) {
						printf("\n관리자 비밀번호를 입력해주세요 : ");
						scanf("%d",&password);
						
						sprintf(man,"select*from manpass where management = %d",password);

						pw = atoi(row[0]);

						if (password == pw) {
							printf("\n계좌 정지를 해제합니다. 다음에는 신중하게 입력해주세요 ^^\n");
							
							sprintf(update_error,"update newclient set error = 0 where bank = '%s' and account = %d",bank_name,account1);
							len = mysql_query(conn, update_error);
							system("pause");
							system("cls");
						}
						else {
							printf("\n비밀번호가 틀렸습니다. 다음에는 잘 입력해주세요\n");
							system("pause");
							system("cls");
						}
					}
				
				}
				else {
					printf("\n정지 상태가 아닌 계좌이거나 없는 계좌입니다.\n");
					printf("초기화면으로 돌아갑니다.\n");
					system("pause");
					system("cls");
				}
			}
			//3번
			else if (mnm == 3) {
				char newman[255];
				char update_newman[255];
				int mannum = 0;
				int newmannum = 0;
				printf("\n\n기존 관리자 비밀번호를 입력해주세요 : ");
				scanf("%d",&pass);
				
				sprintf(newman,"select*from manpass where management = %d",pass);
				len = mysql_query(conn, newman);
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);

				if (row != NULL) {
					
					mannum = atoi(row[0]);

					if (pass == mannum) {
						printf("\n변경하실 비밀번호를 입력해주세요 : ");
						scanf("%d",&newmannum);

						sprintf(update_newman,"update manpass set management = %d",newmannum);
						len = mysql_query(conn, update_newman);

						printf("\n정상처리 되었습니다.\n");
						system("pause");
						system("cls");
					}
					
				}
				else {
					printf("\n입력하신 관리자 비밀번호가 다릅니다. 다음에 다시 입력해주세요^^\n");
					system("pause");
					system("cls");
				}
				

			}
			else {
				printf("\n메뉴로 돌아갑니다.\n");
				system("pause");
				system("cls");				
			}
		}	
	}
	else {
		printf("\n관리자 비밀번호가 틀렸습니다. 초기화면으로 돌아갑니다.\n");
		system("pause");
		system("cls");

	}
	
}

//메인 문
int main(void)
{
	conn = mysql_init(NULL);//초기화
	
	//MySQl에 연결
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);
	if (!conn) {
		printf("mysql 연결 실패");
	}
	for (;;) {
		printf("\n=============== ATM ================\n");
		printf("1.입금\n");
		printf("2.출금\n");
		printf("3.송금\n");
		printf("4.잔액조회\n");
		printf("5.계좌 생성\n");
		printf("6.비밀번호 변경\n");
		printf("7.관리자\n");
		printf("8.종료\n");
		printf("\n====================================\n");
		printf("\n>> ");
		scanf("%s", &atmmenu);

		amenu = atoi(atmmenu);

		if (amenu == 1) {
			deposit();

			continue;
		}
		else if (amenu == 2) {
			withdraw();

			continue;
		}
		else if (amenu == 3) {
			sending();

			continue;
		}
		else if (amenu == 4) {
			check_balance();

			continue;
		}
		else if (amenu == 5) {
			open_account();

			continue;
		}
		else if (amenu == 6) {
			change_password();

			continue;
		}
		else if (amenu == 7) {
			management();

			continue;
		}
		else if (amenu == 8) {
			printf("\n감사합니다. 다음에 또 이용해주세요(^^)(__)(^^)\n");
			mysql_free_result(res);//데이터 누수를 막기 위한 용도
			mysql_close(conn);//mysql 연결 해제

			break;
		}
		else {
			printf("\n잘못된 형식의 입력입니다. 다시 입력해주세요\n");
			getchar();


			continue;
		}
	}

	return 0;
}
	
