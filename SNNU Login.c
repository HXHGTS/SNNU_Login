#include <stdio.h>
#include <stdlib.h>

int x,ret;

int main() {
	system("color 0B");
	MENU: system("cls");
	printf("----------------------------------------------------------\n");
	printf("-----------------------SNNU登录工具-----------------------\n");
	printf("----------------------------------------------------------\n\n");
	printf("1.登录SNNU有线/无线\n\n2.退出SNNU有线/无线\n\n3.查询SNNU有线/无线登录状态\n\n4.校园网VPN登录(校外/数据流量访问)\n\n请输入:");
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
	else {
		SSL_VPN();
	}
	goto MENU;
}

int SNNU_Login() {
	system("explorer http://202.117.144.205:8602/snnuportal/");
	return 0;
}

int SNNU_Logoff() {
	system("explorer http://202.117.144.205:8602/snnuportal/logoff");
	return 0;
}

int SNNU_Status() {
	system("explorer http://202.117.144.205:8602/snnuportal/userstatus.jsp");
	return 0;
}

int SSL_VPN() {
	system("explorer http://webvpn.snnu.edu.cn");
	return 0;
}