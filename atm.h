#pragma once

class Atm {
	char mana[255];
public:
	char fbank[255], faccount[255], update_money[255],error_count[255]; //쿼리용
	char update_error[255];
	char bank_name[15],account[15],password[15];// 계좌 찾기

	int total_money = 0,money = 0,balance =0;
	int error, count, uperror;

	//관리자
	void management();
};

class User :public Atm {
	char fbank2[255], faccount2[255],update_money2[255];
	char bank_name2[15], account2[15];
	int send_money, recieve_money, fee;
public:
	//입금 완료
	void deposit();

	//출금 완료
	void withdraw();

	//송금
	void sending();
};

class Account :public Atm {
	char name[20];
	char open[255];
public:
	char pwc[255];
	//계좌 조회
	void check_balance();

	//계좌 생성
	void open_account();

	//비밀번호 변경

	void change_password();
};
