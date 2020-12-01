#include <stdio.h>
#include <stdlib.h>

int x,ret;
FILE* account, * pw;
char user[11], passwd[20],cmd[200];
int SNNU_Login();
int SNNU_Logoff();
int SNNU_Status();
int SSL_VPN();


int main() {
	system("color 0B");
	if (fopen("account.ini", "r") == NULL|| fopen("pw.ini", "r") == NULL) {
		printf("初次使用,请输入你的校园卡卡号:");
		ret=scanf("%s", user);
		printf("请输入你的登录密码:");
		ret=scanf("%s", passwd);
		account = fopen("account.ini", "w");
		fprintf(account, "%s", user);
		fclose(account);
		pw = fopen("pw.ini", "w");
		fprintf(pw, "%s", passwd);
		fclose(pw);
	}
	account = fopen("account.ini", "r");
	ret=fscanf(account, "%s", user);
	fclose(account);
	pw = fopen("pw.ini", "r");
	ret=fscanf(pw, "%s", passwd);
	fclose(pw);
	MENU: system("cls");
	printf("----------------------------------------------------------\n");
	printf("-----------------------SNNU登录工具-----------------------\n");
	printf("----------------------------------------------------------\n\n");
	printf("1.登录SNNU有线/无线\n\n2.退出SNNU有线/无线\n\n3.查询SNNU有线/无线登录状态\n\n4.校园网VPN登录(校外/数据流量访问)\n\n5.退出\n\n请输入:");
	ret=scanf("%d", &x);
	if (x == 1)
	{
		SNNU_Login();
	}
	else if (x == 2) {
		SNNU_Logoff();
	}
	else if (x == 3) {
		SNNU_Status();
	}
	else if (x == 4) {
		SSL_VPN();
	}
	else {
		exit(0);
	}
	goto MENU;
}

int SNNU_Login() {
	system("cls");
	printf("正在登录SNNU. . .\n");
	sprintf(cmd, "curl \"http://202.117.144.205:8602/snnuportal/login\" -d \"password=%s&account=%s&\" -v",passwd,user);
	system("cls");
	system(cmd);
	system("cls");
	printf("已登录SNNU!\n");
	system("pause");
	return 0;
}

int SNNU_Logoff() {
	system("cls");
	system("curl http://202.117.144.205:8602/snnuportal/logoff");
	system("cls");
	printf("已退出SNNU!\n");
	system("pause");
	return 0;
}

int SNNU_Status() {
	system("cls");
	system("explorer http://202.117.144.205:8602/snnuportal/userstatus.jsp");
	return 0;
}

int SSL_VPN() {
	system("cls");
	system("explorer http://webvpn.snnu.edu.cn");
	return 0;
}