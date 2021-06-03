#include <stdio.h>
#include <stdlib.h>

int RunMode,ret;
FILE* account;
char portal[23] = "http://202.117.144.205";
char port8601[17] = ":8601/snnuportal";
char port8602[17] = ":8602/snnuportal";
char port8603[17] = ":8603/snnuportal";
char user[12], passwd[20],cmd[200];
int SNNU_Login();
int CMCC_Login();
int CUNI_Login();
int CTEL_Login();
int SNNU_Logoff();
int SNNU_Status();
int Network_Repair();
int SaveUserInfo();


int main() {
	system("color 0B");
	if (fopen("account.ini", "r") == NULL) {
		SaveUserInfo();
	}
	account = fopen("account.ini", "r");
	ret=fscanf(account, "%s %s", user,passwd);
	fclose(account);
	MENU: system("cls");
	printf("----------------------------------------------------------\n");
	printf("------------SNNU登录工具（支持有线/无线接入）-------------\n");
	printf("----------------------------------------------------------\n\n");
	printf("1.登录校园网\n\n2.登录移动宽带\n\n3.登录联通宽带\n\n4.登录电信宽带\n\n5.一键退出登录状态\n\n6.网络状态测试\n\n7.网络异常修复(请先关闭笔记本热点功能)\n\n8.更新校园网账号密码\n\n0.退出\n\n请输入:");
	ret=scanf("%d", &RunMode);
	system("cls");
	if (RunMode == 1)
	{
		SNNU_Login();
	}
	else if (RunMode == 2) {
		CMCC_Login();
	}
	else if (RunMode == 3) {
		CUNI_Login();
	}
	else if (RunMode == 4) {
		CTEL_Login();
	}
	else if (RunMode == 5) {
		SNNU_Logoff();
	}
	else if (RunMode == 6) {
		SNNU_Status();
	}
	else if (RunMode == 7) {
		Network_Repair();
	}
	else if (RunMode == 8) {
		SaveUserInfo();
	}
	else {
		exit(0);
	}
	goto MENU;
}

int SNNU_Login() {
	printf("正在登录SNNU. . .\n");
	sprintf(cmd, "curl \"%s%s/login\" -d \"password=%s&account=%s\"",portal,port8602,passwd,user);
	if (system(cmd) == 0) {
		system("cls");
		printf("已登录SNNU!\n");
	}
	else {
		system("cls");
		printf("无法登录SNNU,请确认网线/WLAN已连接!\n");
	}
	system("pause");
	return 0;
}

int CMCC_Login() {
	printf("正在登录移动宽带. . .\n");
	sprintf(cmd, "curl \"%s%s/login\" -d \"password=%s&account=%s&yys=%s\"",portal,port8602, passwd, user,"mobile");
	if (system(cmd) == 0) {
		system("cls");
		printf("已登录移动宽带!\n");
	}
	else {
		system("cls");
		printf("无法登录移动宽带,请确认网线/WLAN已连接!\n");
	}
	system("pause");
	return 0;
}

int CUNI_Login() {
	printf("正在登录联通宽带. . .\n");
	sprintf(cmd, "curl \"%s%s/login\" -d \"password=%s&account=%s&yys=%s\"", portal, port8602, passwd, user, "unicom");
	if (system(cmd) == 0) {
		system("cls");
		printf("已登录联通宽带!\n");
	}
	else {
		system("cls");
		printf("无法登录联通宽带,请确认网线/WLAN已连接!\n");
	}
	system("pause");
	return 0;
}

int CTEL_Login()
{
	printf("正在登录电信宽带. . .\n");
	sprintf(cmd, "curl \"%s%s/login\" -d \"password=%s&account=%s&yys=%s\"", portal, port8602, passwd, user, "telecom");
	if (system(cmd) == 0) {
		system("cls");
		printf("已登录电信宽带!\n");
	}
	else {
		system("cls");
		printf("无法登录电信宽带,请确认网线/WLAN已连接!\n");
	}
	system("pause");
	return 0;
}

int SNNU_Logoff() {
	sprintf(cmd, "curl %s%s/logoff", portal, port8602);
	if (system(cmd) == 0) {
		system("cls");
		printf("已退出校园网登录!\n");
	}
	else {
		system("cls");
		printf("无法退出校园网登录,请确认网线/WLAN已连接!\n");
	}
	system("pause");
	return 0;
}

int SNNU_Status() {
	printf("-------------------------\n");
	printf("正在检测校园网连通性. . .\n");
	printf("-------------------------\n\n");
	if (system("ping net.snnu.edu.cn") == 0) {
		printf("-------------------\n");
		printf("校园网内网访问正常!\n");
		printf("-------------------\n");
	}
	else {
		printf("------------------------------------------\n");
		printf("校园网内网访问出错，请确认网线/WLAN已连接!\n");
		printf("------------------------------------------\n\n\n");
	}
	printf("---------------------------\n");
	printf("正在检测外部网络连通性. . .\n");
	printf("---------------------------\n\n");
	if (system("ping tdns.x2v6.sched.dcloudstc.com") == 0) {
		printf("-----------------\n");
		printf("外部网络访问正常!\n");
		printf("-----------------\n");
	}
	else {
		printf("------------------------------------------------\n");
		printf("外部网络访问出错，请确认校园网余额/宽带是否到期!\n");
		printf("------------------------------------------------\n\n");
	}
	system("pause");
	return 0;
}

int Network_Repair() {
	printf("正在重置dns. . .\n");
	system("netsh interface ip set dns \"以太网\" dhcp");
	system("netsh interface ipv6 set dns \"以太网\" dhcp");
	system("netsh interface ip set dns \"WLAN\" dhcp");
	system("netsh interface ipv6 set dns \"WLAN\" dhcp");
	system("ipconfig /flushdns");
	printf("正在重新获取ip地址. . .\n");
	system("ipconfig /release");
	system("ipconfig /renew");
	printf("修复完成,请尝试重新登录!\n");
	system("pause > nul");
	return 0;
}

int SaveUserInfo() {
	printf("初次使用,请输入你的校园卡卡号:");
	ret = scanf("%s", user);
	printf("请输入你的登录密码:");
	ret = scanf("%s", passwd);
	account = fopen("account.ini", "w");
	fprintf(account, "%s %s", user,passwd);
	fclose(account);
	return 0;
}