#pragma once

class Atm {
	char mana[255];
public:
	char fbank[255], faccount[255], update_money[255],error_count[255]; //������
	char update_error[255];
	char bank_name[15],account[15],password[15];// ���� ã��

	int total_money = 0,money = 0,balance =0;
	int error, count, uperror;

	//������
	void management();
};

class User :public Atm {
	char fbank2[255], faccount2[255],update_money2[255];
	char bank_name2[15], account2[15];
	int send_money, recieve_money, fee;
public:
	//�Ա� �Ϸ�
	void deposit();

	//��� �Ϸ�
	void withdraw();

	//�۱�
	void sending();
};

class Account :public Atm {
	char name[20];
	char open[255];
public:
	char pwc[255];
	//���� ��ȸ
	void check_balance();

	//���� ����
	void open_account();

	//��й�ȣ ����

	void change_password();
};
