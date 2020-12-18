#include <stdio.h>
#include <stdlib.h>

int RunMode,ret,i;
FILE* account, * pw, * source;
char user[25], passwd[20],cmd[200],ip[26],url[125],phpsessid[30],blackhole[50],credit[10];
int SNNU_Login();
int CMCC_Login();
int CUNI_Login();
int SNNU_Logoff();
int SNNU_Status();
int SSL_VPN();
int SaveUserInfo();


int main() {
	system("color 0B");
	if (fopen("account.ini", "r") == NULL|| fopen("pw.ini", "r") == NULL) {
		SaveUserInfo();
	}
	account = fopen("account.ini", "r");
	ret=fscanf(account, "%s", user);
	fclose(account);
	pw = fopen("pw.ini", "r");
	ret=fscanf(pw, "%s", passwd);
	fclose(pw);
	MENU: system("cls");
	printf("----------------------------------------------------------\n");
	printf("------------SNNU登录工具（支持有线/无线接入）-------------\n");
	printf("----------------------------------------------------------\n\n");
	printf("1.登录校园网\n\n2.登录移动校园宽带\n\n3.登录联通校园宽带\n\n4.一键退出校园网、校园宽带\n\n5.查询账号认证状态\n\n6.VPN登录(校外/数据流量访问)\n\n7.更新校园网账号密码\n\n0.退出\n\n请输入:");
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
		SNNU_Logoff();
	}
	else if (RunMode == 5) {
		SNNU_Status();
	}
	else if (RunMode == 6) {
		SSL_VPN();
	}
	else if (RunMode == 7) {
		SaveUserInfo();
	}
	else {
		exit(0);
	}
	goto MENU;
}

int SNNU_Login() {
	printf("正在登录SNNU. . .\n");
	sprintf(cmd, "curl \"http://202.117.144.205:8602/snnuportal/login\" -d \"password=%s&account=%s\"",passwd,user);
	system("cls");
	system(cmd);
	system("cls");
	printf("已登录SNNU!\n");
	system("pause");
	return 0;
}

int CMCC_Login() {
	printf("正在登录移动宽带. . .\n");
	sprintf(cmd, "curl \"http://202.117.144.205:8602/snnuportal/login\" -d \"password=%s&account=%s&yys=%s\"", passwd, user,"mobile");
	system("cls");
	system(cmd);
	system("cls");
	printf("已登录移动宽带!\n");
	system("pause");
	return 0;
}

int CUNI_Login() {
	printf("正在登录联通宽带. . .\n");
	sprintf(cmd, "curl \"http://202.117.144.205:8602/snnuportal/login\" -d \"password=%s&account=%s&yys=%s\"", passwd, user,"unicom");
	system("cls");
	system(cmd);
	system("cls");
	printf("已登录联通宽带!\n");
	system("pause");
	return 0;
}

int SNNU_Logoff() {
	system("curl http://202.117.144.205:8602/snnuportal/logoff");
	system("cls");
	printf("已退出SNNU!\n");
	system("pause");
	return 0;
}

int SNNU_Status() {
	system("curl http://202.117.144.205:8602/snnuportal/userstatus.jsp > userstatus.source");
	system("type userstatus.source | findstr \"account\" > account.source");
	system("type userstatus.source | findstr \"ipaddr\" > login_ip.source");
	system("curl http://202.117.144.205:8602/snnuportal/userstatus.jsp | findstr \"http://202.117.144.205:80/zili/auth_login.php?\" > login_status.source");
	source = fopen("account.source", "r");
	ret=fscanf(source, "%s %s %s value=%s/>", blackhole,blackhole,blackhole,user);
	fclose(source);
	source = NULL;
	source = fopen("login_ip.source", "r");
	ret = fscanf(source, "%s %s %s value=%s/>", blackhole, blackhole, blackhole, ip);
	fclose(source);
	source = NULL;
	source = fopen("login_status.source", "r");
	ret = fscanf(source, "      <td><div class=\"zhengwen\" align=\"center\"><span class=\"zhengwen2\">Copyright （C）2012 陕西师范大学</span> &nbsp;<span class=\"zhengwen2\">服务电话：<span class=\"dianhua\">029-85310558</span></span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class=\"zhengwen2\"><a href=\"%s\">自助服务主页</a>&nbsp;&nbsp;&nbsp; | &nbsp;&nbsp;<a href=\"http://www.snnu.edu.cn/\">学校主页</a>&nbsp;&nbsp;&nbsp; | &nbsp;&nbsp;<a href=\"http://202.117.144.205/zili_pre/\">临时账号注册</a></span><br>", url);
	fclose(source);
	for (i = 0; i <= 125; i++) {
		if (url[i]=='\"') {
			url[i] = '\0';
			break;
		}
	}
	sprintf(cmd,"curl \"%s\" -c login.source",url);
	system(cmd);
	system("curl -b login.source \"http://202.117.144.205/zili/myinfo.php\" > info.txt");
	system("chcp 65001");
	system("type info.txt | find \"元\" > credit.source");
	source = fopen("credit.source", "r");
	ret = fscanf(source, "                                        %s", credit);
	fclose(source);
	for (i = 0; i <= 10; i++) {
		if (credit[i] != '.' && credit[i] < '0'|| credit[i] > '9') {
			credit[i] = '\0';
			break;
		}
	}
	system("chcp 936");
	system("del /F /S /Q *.source");
	system("del info.txt");
	system("cls");
	printf("登录账号:%s\n", user);
	printf("登录ip:%s\n", ip);
	printf("余额:");
	printf("%s元\n", credit);
	system("pause");
	return 0;
}

int SSL_VPN() {
	system("explorer http://webvpn.snnu.edu.cn");
	return 0;
}

int SaveUserInfo() {
	printf("初次使用,请输入你的校园卡卡号:");
	ret = scanf("%s", user);
	printf("请输入你的登录密码:");
	ret = scanf("%s", passwd);
	account = fopen("account.ini", "w");
	fprintf(account, "%s", user);
	fclose(account);
	pw = fopen("pw.ini", "w");
	fprintf(pw, "%s", passwd);
	fclose(pw);
	return 0;
}