//C�� ATM
#include <stdio.h>
#include <mysql.h> //MySQL�� �����ϱ� ���� �ʿ��� �ش�����
#include <string.h>
#include <stdlib.h>// atoi, itoa ����� ����
#include <time.h>//srand�� �ð��� ���� �ٸ� ������ ���� �ޱ� ����

#define HOST "localhost" // ���� ȣ��Ʈ �ּ�
#define USER "root" //����� �̸�
#define PASS "dsy4042" //MYSQL �н�����
#define NAME "bank" //������ �����ͺ��̽� �̸�
#define _CRT_SECURE_NO_WARNINGS //fopen ���� ���� ���� ������ ���� ����
#define MAX 1000

int amenu;
char bank_name[11];
char update_error[255];
char fee2[255];
int password;
int account1, account2, money ,money1, money2, count;
int fee;
char atmmenu[100];
int len;// query ����� ����

MYSQL* conn;//MySQL�� ������ ���
MYSQL_RES* res;//������ ���� ����� �޴� ����
MYSQL_ROW row; //������ ���� ���� ������ ���� ����ִ� ����

//1�� �Ա�=�Ϸ�
void deposit() {
	char update_money[255];
	char fbank[255];
	char faccount[255];
	int acc = 0;
	int balance = 0;
	int pw = 0;
	int len2;
	int error = 0;

	printf("\n-------------�Ա�--------------\n\n");
	FILE* fp = fopen("������.txt", "r"); //���� ����� �������� ���� �б� �� �߰����
	char buffer[MAX] = { 0, };

	fread(buffer, 1, MAX, fp);// ��ü �о����
	printf("% s", buffer);
	fclose(fp);//���� �ݱ�

	printf("\n\n������ �������ּ���: ");
	scanf("%s", &bank_name);

	sprintf(fbank, "select*from newclient where bank ='%s'", bank_name);
	len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	//row ���� NULL���� �ƴ��� �˻�
	if (row != NULL) {
		//���� �´��� �˻�
		if (strcmp(bank_name, row[1]) == 0) {
			
			printf("\n���¹�ȣ�� �Է����ּ���: ");
			scanf("%d", &account1);

			sprintf(faccount, "select * from newclient where bank = '%s' and account = %d", bank_name, account1);

			len2 = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			
			//���°� �ùٸ��� �˻�
			if (row != NULL) {
				
				error = atoi(row[5]);
				acc = atoi(row[0]);
				if (account1 == acc,error <=2) { 
					
					printf("\n��й�ȣ�� �Է����ּ��� : ");
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

							printf("\n��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ��� : ");
							scanf("%d",&password);

						}
						else if (password == pw) {
							break;
						}
					}
					//��й�ȣ�� �ùٸ��� �˻�
					if (password == pw) {
						printf("\n�Ա� �ݾ��� �Է����ּ��� : ");
						scanf("%d", &money1);

						balance = atoi(row[4]);

						money = balance + money1;
						
						printf("\n%s �ŷ���ǥ\n", row[1]);
						printf("[���� �Ա�]");
						printf("\n---------------------------\n");
						printf("��û �ݾ�: %d ��\n", money1);
						printf("ó����� : ����ó��\n");
						printf("�ŷ� �� �ܾ�: %d ��\n", money);						
						printf("\n---------------------------\n");

						char* query_date = "select now()";

						len = mysql_query(conn, query_date);
						res = mysql_store_result(conn);
						while ((row = mysql_fetch_row(res)) != NULL) {
							printf("�ŷ��Ͻ�: %s", row[0]);
							printf("\n���¹�ȣ: %s %d\n\n", bank_name, account1);
						}
						sprintf(update_money, "update newclient set money = %d where account = %d", money, account1);
						len = mysql_query(conn, update_money);
					}
					else {
						
						printf("\n��й�ȣ�� 3ȸ Ʋ�Ƚ��ϴ�. ���� ���� �� �ʱ�ȭ������ ���ư��ϴ�.\n");

						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = %d", bank_name, account1);
						len = mysql_query(conn, update_error);
						
						system("pause");
						system("cls");
					}

				}			
				else if (account1 == acc,error == 3) {
					printf("\n������ �����Դϴ�. ���� ������ ������ �� �̿����ּ���^^\n");
					system("pause");
					system("cls");
				}
				
			}
			else if (row == NULL) {
				
				printf("\n�Է��Ͻ� ���¸� ã�� �� �����ϴ�. �������� �ùٸ� ���¸� �Է����ּ���\n");
				system("pause");
				system("cls");
					
			}
		}		
	}
	else if(row == NULL) {
		printf("\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. �������� �ùٸ� ������� �Է����ּ���\n");
		system("pause");
		system("cls");
	}
	
}

//2�� ���=�Ϸ�
void withdraw() {
	char withdraw[255];
	char fbank[255];
	char update_money[255];
	int faccount = 0;
	int balance = 0;
	int pw = 0;
	int error = 0;
	printf("\n-------------���--------------\n");
	FILE* fp = fopen("������.txt", "r"); //���� ����� �������� ���� �б� �� �߰����
	char buffer[MAX] = { 0, };

	fread(buffer, 1, MAX, fp);// ��ü �о����
	printf("% s", buffer);
	fclose(fp);//���� �ݱ�

	printf("\n\n������ �������ּ���: ");
	scanf("%s", &bank_name);
	
	sprintf(fbank,"select*from newclient where bank = '%s'",bank_name);

	len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	if (row != NULL) {
		//���� �´��� �˻�
		if (strcmp(bank_name, row[1]) == 0) {

			printf("\n���¹�ȣ�� �Է����ּ���: ");
			scanf("%d", &account1);

			sprintf(withdraw, "select * from newclient where bank = '%s' and account = %d", bank_name, account1);

			len = mysql_query(conn, withdraw);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			
			if (row != NULL) {
				error = atoi(row[5]);
				faccount = atoi(row[0]);
				//���� �´��� �˻�
				if (account1 == faccount, error ==0) {
					printf("\n��й�ȣ�� �Է����ּ��� : ");
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

							printf("\n��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ��� : ");
							scanf("%d", &password);

						}
						else if (password == pw) {
							break;
						}
					}
					//��й�ȣ �´��� �˻�
					if (password == pw) {
						printf("\n��� �ݾ��� �Է����ּ��� : ");
						scanf("%d", &money1);

						balance = atoi(row[4]);

						money = balance - money1;
						//��� �������� �˻�
						if (money >= 0) {
							printf("\n%s �ŷ���ǥ\n", row[1]);
							printf("[���� ���]");
							printf("\n---------------------------\n");
							printf("��û �ݾ�: %d ��\n", money1);
							printf("ó����� : ���� ó��\n");
							printf("�ŷ� �� �ܾ�: %d ��\n", money);
							printf("������: 0 ��\n");
							printf("---------------------------\n");

							char* query_date = "select now()";

							len = mysql_query(conn, query_date);
							res = mysql_store_result(conn);
							while ((row = mysql_fetch_row(res)) != NULL) {
								printf("�ŷ��Ͻ�: %s", row[0]);
								printf("\n���¹�ȣ: %d\n\n", account1);
							}
							sprintf(update_money, "update newclient set money = %d where account = %d", money, account1);
							len = mysql_query(conn, update_money);
						}
						else {
							printf("XXXXXXXXXX ���: �ܾ� ���� XXXXXXXXXXXX\n");
							printf("�ʱ�ȭ������ ���ư��ϴ�.\n");
							system("pause");
							system("cls");

						}
					}
					else {
						printf("\n��й�ȣ�� 3ȸ Ʋ�Ƚ��ϴ�. ���� ���� �� �ʱ�ȭ������ ���ư��ϴ�.");
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = %d", bank_name, account1);
						len = mysql_query(conn, update_error);
						system("pause");
						system("cls");
					}
				}
				else if (account1 == faccount, error == 3) {
					printf("\n������ �����Դϴ�. ���� ������ ������ �� �̿����ּ���^^\n");
					system("pause");
					system("cls");
				}
			}
			else if (row == NULL) {
				printf("\n�Է��Ͻ� ���¸� ã�� ���߽��ϴ�. ������ �����ϰ� �Է����ּ���^^\n");
				printf("�ʱ�ȭ������ ���ư��ϴ�.\n");
				system("pause");
				system("cls");
			}
		}
		
	}
	else if (row == NULL) {
		printf("\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. �������� �ùٸ� ������� �Է����ּ���\n");
		system("pause");
		system("cls");
	}
}

//3�� �۱�=�Ϸ�
void sending() {
	char plus[255], fname[255];
	char bank_name2[11];
	char update_money1[255], update_money2[255];
	char fbank[255],faccount[255], faccount2[255];
	int len2 , send;
	int balance_f = 0, balance_l = 0;
	int pw = 0,error = 0,facc = 0, facc2 = 0;

	printf("\n----------------------�۱�------------------------\n");
	printf("������ ������ �Է����ּ��� : ");
	scanf("%s",&bank_name);
	
	sprintf(fbank, "select*from newclient where bank = '%s'", bank_name);

	len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	if (row != NULL) {
		
		if (strcmp(bank_name, row[1]) == 0) {
			printf("\n������ ���� ��ȣ�� �Է����ּ��� : ");
			scanf("%d", &account1);

			sprintf(faccount, "select* from newclient where bank = '%s' and account = %d", bank_name, account1);
			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (row != NULL) {
				error = atoi(row[5]);
				facc = atoi(row[0]);
				if (account1 == facc, error >= 0,error<3) {
					printf("\n��й�ȣ�� �Է����ּ��� : ");
					scanf("%d", &password);

					pw = atoi(row[3]);
					//��й�ȣƲ�� �ݺ�
					for (count = 0; count < 2;count++) {
						if (password != pw) {
							char errorcount[255];
							int uperror;
							uperror = ++error;
							sprintf(errorcount,"update newclient set error = %d where bank ='%s' and account = %d",uperror,bank_name,account1);
							len = mysql_query(conn, errorcount);

							printf("\n��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ��� : ");
							scanf("%d", &password);
							
						}
						else if (password == pw) {
							break;
						}
					}
					if (password == pw) {
						printf("\n�۱��� ������ �Է����ּ��� : ");
						scanf("%s", &bank_name2);
						
						sprintf(fname,"select*from newclient where bank = '%s'",bank_name2);

						len = mysql_query(conn, fname);
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						if (row != NULL) {

							if (strcmp(bank_name2, row[1]) == 0) {
								printf("\n�۱��� ���¸� �Է����ּ��� : ");
								scanf("%d", &account2);

								sprintf(faccount2,"select*from newclient where bank = '%s' and account = %d",bank_name2,account2);

								len = mysql_query(conn, faccount2);
								res = mysql_store_result(conn);
								row = mysql_fetch_row(res);

								if (row != NULL) {
									facc2 = atoi(row[0]);
									printf("\n�۱��� �ݾ��� �Է����ּ��� : ");
									scanf("%d", &money1);

									//������ ���� ������
									len = mysql_query(conn, faccount);
									res = mysql_store_result(conn);
									row = mysql_fetch_row(res);

									balance_f = atoi(row[4]);

									money = balance_f - money1;

									//�ܰ� �˳��� ���
									if (money >= 0) {
										sprintf(update_money1, "update newclient set money = %d where account = %d", money, account1);
										len = mysql_query(conn, update_money1);

										//�۱ݹ��� ���� ������
										sprintf(plus, "select* from newclient where bank = '%s' and account = %d", bank_name2, account2);
										len2 = mysql_query(conn, plus);
										res = mysql_store_result(conn);
										row = mysql_fetch_row(res);

										balance_l = atoi(row[4]);

										send = balance_l + money1;

										sprintf(update_money2, "update newclient set money = %d where account = %d", send, account2);
										len2 = mysql_query(conn, update_money2);

										printf("[���� �۱�]");
										printf("\n---------------------------\n");
										printf("��û �ݾ�: %d ��\n", money1);
										printf("ó����� : ���� ó��\n");
										
										if (strcmp(bank_name,bank_name2) == 0) {

											printf("�ŷ� �� �ܾ�: %d ��\n", money);
											printf("������: 0 ��\n");
										}
										else if (strcmp(bank_name,bank_name2) != 0) {
											fee = money - 500;
											printf("�ŷ� �� �ܾ�: %d ��\n", fee);
											printf("������: 500 ��\n");
											sprintf(fee2, "update newclient set money = %d where account = %d", fee, account1);
											len = mysql_query(conn, fee2);
										}
										printf("---------------------------\n");


										char* query_date = "select now()";
										len = mysql_query(conn, query_date);
										res = mysql_store_result(conn);
										row = mysql_fetch_row(res);
										printf("�ŷ��Ͻ�: %s\n", row[0]);

									}
									else {
										printf("\n������ ������ �ܾ��� �����մϴ�.\n");
										printf("\n�ʱ�ȭ������ ���ư��ϴ�.\n");
										system("pause");
										system("cls");
									}
								}
								else if (row == NULL) {
									printf("\n�Է��Ͻ� ���¸� ã�� ���߽��ϴ�. ������ �����ϰ� �Է����ּ���^^\n");
									printf("�ʱ�ȭ������ ���ư��ϴ�.\n");
									system("pause");
									system("cls");
								}
							}
						}
						else if (row == NULL) {
							printf("\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. �������� �ùٸ� ������� �Է����ּ���\n");
							system("pause");
							system("cls");
						}
					}
					else {
						printf("\n��й�ȣ�� 3ȸ Ʋ�Ƚ��ϴ�. ���� ���� �� �ʱ�ȭ������ ���ư��ϴ�.\n");
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = %d", bank_name, account1);
						len = mysql_query(conn, update_error);
						system("pause");
						system("cls");
					}
				}
				else if (account1 == facc, error == 3) {
					printf("\n������ �����Դϴ�. ���� ������ ������ �� �̿����ּ���^^\n");
					system("pause");
					system("cls");
				}
			}
			else if (row == NULL) {
				printf("\n�Է��Ͻ� ���¸� ã�� ���߽��ϴ�. ������ �����ϰ� �Է����ּ���^^\n");
				printf("�ʱ�ȭ������ ���ư��ϴ�.\n");
				system("pause");
				system("cls");
			}
		}
	}
	else if (row == NULL) {
		printf("\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. �������� �ùٸ� ������� �Է����ּ���\n");
		system("pause");
		system("cls");
	}
}

//4�� �ܾ���ȸ=�Ϸ�
void check_balance() {
	
	char balance[255];
	char fbank[255];
	int faccount = 0;
	int pw = 0, error;

	
	printf("\n--------------�ܾ���ȸ--------------\n");
	printf("\n��ȸ�� ������ �Է����ּ��� : ");
	scanf("%s",&bank_name);
	
	sprintf(fbank,"select*from newclient where bank ='%s'",bank_name);

	len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		if (strcmp(bank_name, row[1]) == 0) {
			printf("\n��ȸ�� ���¹�ȣ�� �Է����ּ��� : ");
			scanf("%d", &account1);

			sprintf(balance, "select* from newclient where account = % d and bank = '%s'", account1, bank_name);

			len = mysql_query(conn, balance);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			
			if (row != NULL) {
				
				faccount = atoi(row[0]);
				
				if (faccount == account1) {
					printf("\n��й�ȣ�� �Է����ּ��� : ");
					scanf("%d", &password);
					getchar();
					
					error = atoi(row[5]);
					pw = atoi(row[3]);
					//��й�ȣƲ�� �ݺ�
					for (count = 0; count < 2;count++) {
						if (password != pw) {
							char errorcount[255];
							int uperror;
							uperror = ++error;
							sprintf(errorcount, "update newclient set error = %d where bank ='%s' and account = %d", uperror, bank_name, account1);
							len = mysql_query(conn, errorcount);

							printf("\n��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ��� : ");
							scanf("%d", &password);

						}
						else if (password == pw) {
							break;
						}
					}
					if (password == pw) {
						printf("\n------------------------------------\n");
						printf("\n���� �ܾ�: %s %s %s ��\n", row[1], row[0], row[4]);
						system("pause");
					}
					else {
						printf("\n��й�ȣ�� 3ȸ Ʋ�Ƚ��ϴ�. ���� ���� �� �ʱ�ȭ������ ���ư��ϴ�.^^\n");
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = %d", bank_name, account1);
						len = mysql_query(conn, update_error);
						system("pause");
						system("cls");
					}
				}
				
			}
			else {
				printf("\n�Է��Ͻ� ���¸� ã�� ���߽��ϴ�. ������ �����ϰ� �Է����ּ���^^\n");
				printf("�ʱ�ȭ������ ���ư��ϴ�.\n");
				system("pause");
				system("cls");
			}
		}
	}
	else if (row == NULL) {
		printf("\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. �������� �ùٸ� ������� �Է����ּ���^^\n");
		system("pause");
		system("cls");
	}
}

//5�� ���� ���� = �Ϸ�
void open_account() {
	char open[255];
	char fbank[255];
	char name[30];
	int newaccount = 0;
	int ps = 0;
	printf("\n--------------���� ����--------------\n");
	printf("\n�̸��� �Է����ּ��� : ");
	scanf("%s", &name);

	FILE* fp;
	fp = fopen("������.txt", "r"); //���� ����� �������� ���� �б� �� �߰����
	char buffer[MAX] = { 0, };

	fread(buffer, 1, MAX, fp);// ��ü �о����
	printf("\n%s", buffer);
	
	fclose(fp);

	printf("\n\n����Ͻ� ������ �Է����ּ��� : ");
	scanf("%s",&bank_name);
	getchar();
	
	char* ptr = strtok(buffer,"\n");
	while (true) {
		ptr = strtok(NULL, "\n");// ���� ���ڿ��� �߶� �����͸� ��ȯ

		if (ptr == NULL) {
			break;
		}
		else if (strcmp(ptr, bank_name) == 0) {
			printf("\n����Ͻ� ��й�ȣ�� �Է����ּ���(4�ڸ�) : ");
			scanf("%d", &password);

			srand((unsigned)time(NULL));// �ð��� ���� �ٸ� ���� ������ ���� ���
			newaccount = rand() % (99999999 - 10000000) + 10000000;
			printf("������ ���� : ����  ���¹�ȣ  �̸�  ��й�ȣ");
			printf("\n������ ���� : %s %d  %s  %d \n", bank_name, newaccount, name, password);



			sprintf(open, "insert into newclient values (%d, '%s', '%s', %d, %d, %d)", newaccount, bank_name, name, password, 0, 0);
			len = mysql_query(conn, open);

			system("pause");
			system("cls");
			return;
		}
	}		 
	printf("\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. ����� �� ����� �ּ���\n");
	system("pause");
	system("cls");
				
	fclose(fp);
	
}

//6�� ��й�ȣ ����
void change_password() {
	char pwc[255],fbank[255],faccount[255];
	char update_pw[255];
	int pw = 0;
	int change = 0;
	int acc, error;

	printf("\n--------------��й�ȣ ����--------------\n");
	printf("\n������ ����ϴ� ������ ������ �Է����ּ��� : ");
	scanf("%s",&bank_name);

	sprintf(fbank, "select*from newclient where bank ='%s'", bank_name);

	len = mysql_query(conn, fbank);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (row != NULL) {
		if (strcmp(bank_name, row[1]) == 0) {
			printf("\n������ ����ϴ� ���¹�ȣ�� �Է����ּ��� : ");
			scanf("%d", &account1);

			sprintf(faccount, "select * from newclient where bank = '%s' and account = %d", bank_name, account1);

			len = mysql_query(conn, faccount);
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);

			if (row != NULL) {
				acc = atoi(row[0]);
				if (account1 == acc) {
					printf("\n������ ���� 4�ڸ� ��й�ȣ�� �Է����ּ��� : ");
					scanf("%d", &password);

					sprintf(pwc, "select*from newclient where account = %d", account1);

					len = mysql_query(conn, pwc);
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					error = atoi(row[5]);
					pw = atoi(row[3]);
					
					//��й�ȣƲ�� �ݺ�
					for (count = 0; count < 2;count++) {
						if (password != pw) {
							char errorcount[255];
							int uperror;
							uperror = ++error;
							sprintf(errorcount, "update newclient set error = %d where bank ='%s' and account = %d", uperror, bank_name, account1);
							len = mysql_query(conn, errorcount);

							printf("\n��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է����ּ��� : ");
							scanf("%d", &password);

						}
						else if (password == pw) {
							break;
						}
					}
					if (password == pw) {
						printf("\n�����Ͻ� 4�ڸ� ��й�ȣ�� �Է����ּ��� : ");
						scanf("%d", &change);
						if(password == change){
							printf("\n���� ��й�ȣ�� ���� ��й�ȣ �Դϴ�. �ʱ�ȭ������ ���ư��ϴ�.\n");

						}
						else if (change>9999 || change<1000) {
							printf("\n4�ڸ� ��й�ȣ�� �ƴմϴ�. �ʱ�ȭ������ ���ư��ϴ�.\n");
						}
						else {
							printf("\n���� ��й�ȣ : %s\n", row[3]);
							printf("\n����� ��й�ȣ : %d\n", change);

							sprintf(update_pw, "update newclient set password = %d where account = %d", change, account1);
							len = mysql_query(conn, update_pw);
						}
					}
					else {
						printf("\n��й�ȣ�� 3ȸ Ʋ�Ƚ��ϴ�. ���� ���� �� �ʱ�ȭ������ ���ư��ϴ�.\n");
						sprintf(update_error, "update newclient set error = 3 where bank = '%s' and account = %d", bank_name, account1);
						len = mysql_query(conn, update_error);
						system("pause");
						system("cls");
					}

				}
			}
			else if (row == NULL) {
				
				printf("\n�Է��Ͻ� ���¸� ã�� �� �����ϴ�. �������� �ùٸ� ���¸� �Է����ּ���\n");
				system("pause");
				system("cls");
				
			}
		}
	}
	else if (row == NULL) {
		printf("\n�Է��Ͻ� ������ �������� �ʽ��ϴ�. �������� �ùٸ� ������� �Է����ּ���\n");
		system("pause");
		system("cls");
	}
}

//7�� ������ �޴� = �Ϸ�
void management() {
	int mnm = 0;
	int pass = 0;
	int man_password = 0;
	char manpass[255];

	printf("\n������ ��й�ȣ�� �����ּ���(4�ڸ�) : ");
	scanf("%d",&pass);
	
	sprintf(manpass,"select*from manpass where management = %d",pass);
	len = mysql_query(conn, manpass);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	if(row != NULL){
		
		man_password = atoi(row[0]);

		if (pass == man_password) {
			printf("\n===================������ ���=====================\n");
			printf("1. ���� �߰�\n");
			printf("2. ���� ���� ����\n");
			printf("3. ������ ��й�ȣ ����\n");
			printf("4. �޴��� ���ư���");
			printf("\n===================================================\n");
			printf("\n>> ");
			scanf("%d", &mnm);
			//1�� �Ϸ�
			if (mnm == 1) {
				
				FILE* fp;
				fp = fopen("������.txt", "r"); //���� ����� �������� ���� �б� ���
				char buffer[MAX] = { 0, };

				fread(buffer, 1, MAX, fp);// ��ü �о����
				printf("% s",buffer);
				
				fclose(fp);

				printf("\n�߰��Ͻ� ������ �Է����ּ��� : ");
				scanf("%s",&bank_name);
				
				FILE* fp2;
				fp2 = fopen("������.txt", "a+"); //���� ��Ͽ� �߰��ϱ� ���� �б� �� �߰����
				
				char* ptr = strtok(buffer, "\n");
				while (true) {
					ptr = strtok(NULL, "\n");// ���� ���ڿ��� �߶� �����͸� ��ȯ

					if (ptr == NULL) {
						break;
					}
					else if (strcmp(ptr, bank_name) == 0) {
						printf("\n�̹� �����ϴ� �����Դϴ�.\n");
						return;
					}
					
				}
				fprintf(fp2, "\n%s", bank_name);

				printf("\n���������� �߰��Ǿ����ϴ�\n");
				system("pause");
				system("cls");

				fclose(fp2);
			}
			//2��
			else if (mnm == 2) {
				char faccount[255];
				int find = 0;
				int pw = 0;
				char man[255];

				printf("\n������ �����Ͻ� ����� ���¸� �Է����ּ��� : ");
				scanf("%s %d",&bank_name,&account1);

				sprintf(faccount,"select*from newclient where bank = '%s' and account = %d and error = 3",bank_name,account1);

				len = mysql_query(conn, faccount);
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);

				if (row != NULL) {
					find = atoi(row[0]);
					if (strcmp(bank_name,row[1]) == 0, find == account1) {
						printf("\n������ ��й�ȣ�� �Է����ּ��� : ");
						scanf("%d",&password);
						
						sprintf(man,"select*from manpass where management = %d",password);

						pw = atoi(row[0]);

						if (password == pw) {
							printf("\n���� ������ �����մϴ�. �������� �����ϰ� �Է����ּ��� ^^\n");
							
							sprintf(update_error,"update newclient set error = 0 where bank = '%s' and account = %d",bank_name,account1);
							len = mysql_query(conn, update_error);
							system("pause");
							system("cls");
						}
						else {
							printf("\n��й�ȣ�� Ʋ�Ƚ��ϴ�. �������� �� �Է����ּ���\n");
							system("pause");
							system("cls");
						}
					}
				
				}
				else {
					printf("\n���� ���°� �ƴ� �����̰ų� ���� �����Դϴ�.\n");
					printf("�ʱ�ȭ������ ���ư��ϴ�.\n");
					system("pause");
					system("cls");
				}
			}
			//3��
			else if (mnm == 3) {
				char newman[255];
				char update_newman[255];
				int mannum = 0;
				int newmannum = 0;
				printf("\n\n���� ������ ��й�ȣ�� �Է����ּ��� : ");
				scanf("%d",&pass);
				
				sprintf(newman,"select*from manpass where management = %d",pass);
				len = mysql_query(conn, newman);
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);

				if (row != NULL) {
					
					mannum = atoi(row[0]);

					if (pass == mannum) {
						printf("\n�����Ͻ� ��й�ȣ�� �Է����ּ��� : ");
						scanf("%d",&newmannum);

						sprintf(update_newman,"update manpass set management = %d",newmannum);
						len = mysql_query(conn, update_newman);

						printf("\n����ó�� �Ǿ����ϴ�.\n");
						system("pause");
						system("cls");
					}
					
				}
				else {
					printf("\n�Է��Ͻ� ������ ��й�ȣ�� �ٸ��ϴ�. ������ �ٽ� �Է����ּ���^^\n");
					system("pause");
					system("cls");
				}
				

			}
			else {
				printf("\n�޴��� ���ư��ϴ�.\n");
				system("pause");
				system("cls");				
			}
		}	
	}
	else {
		printf("\n������ ��й�ȣ�� Ʋ�Ƚ��ϴ�. �ʱ�ȭ������ ���ư��ϴ�.\n");
		system("pause");
		system("cls");

	}
	
}

//���� ��
int main(void)
{
	conn = mysql_init(NULL);//�ʱ�ȭ
	
	//MySQl�� ����
	conn = mysql_real_connect(conn, HOST, USER, PASS, NAME, 3306, (char*)NULL, 0);
	if (!conn) {
		printf("mysql ���� ����");
	}
	for (;;) {
		printf("\n=============== ATM ================\n");
		printf("1.�Ա�\n");
		printf("2.���\n");
		printf("3.�۱�\n");
		printf("4.�ܾ���ȸ\n");
		printf("5.���� ����\n");
		printf("6.��й�ȣ ����\n");
		printf("7.������\n");
		printf("8.����\n");
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
			printf("\n�����մϴ�. ������ �� �̿����ּ���(^^)(__)(^^)\n");
			mysql_free_result(res);//������ ������ ���� ���� �뵵
			mysql_close(conn);//mysql ���� ����

			break;
		}
		else {
			printf("\n�߸��� ������ �Է��Դϴ�. �ٽ� �Է����ּ���\n");
			getchar();


			continue;
		}
	}

	return 0;
}
	
