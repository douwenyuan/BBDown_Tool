#include<windows.h>
#include<string.h>
#include<cstring>
#include<cstdio>
#include<unistd.h>
#include<iostream>
#include<algorithm>
using namespace std;
bool check_bv_av(string c)//检查BV号和AV号函数
{
	if(c[1]!='B'||c[1]!='b'||c[2]!='v'||c[1]!='a'||c[1]!='A') return false;
	else return true;
}
int main()
{
	system("chcp 65001");//让窗口支持显示中文
	system("cls");//清除上一条语句执行后所产生的内容
	printf("欢迎使用BBDown终端版！\n");
	if(access("BBDown.exe",F_OK)==1||access("ffmpeg.exe",F_OK)==1)//判定程序安装完整性，bbdown.exe和ffmpeg.exe都是程序必要的文件
	{
		printf("程序不完整，请重新安装。\n");
		system("PAUSE");
		return 0;
	}
	string a="bbdown.exe ",b;
	if(access("BBDown.data",F_OK))//判定"BBDown.data"是否存在，即为判断是否登陆
	{
		printf("请用手机客户端扫描本目录下的qrcode.png登录。\n");
		a+=" login";
		system(a.c_str());
		system("PAUSE");
		return 0;
	}
	printf("请输入您想下载视频的BV/AV号：\n");
	cin>>b;//读入BV/AV号
	while(check_bv_av(b)==1)//BV/AV号不合法时，会重复要求用户输入，直到输入合法
	{
		printf("BV/AV号有误，请重新输入：\n");
		cin>>b;
	}
	a+=b;//把BV/AV号加入要执行的指令中
    /*
		思路：把需要执行的命令汇总到一个总变量，最后一起执行
		用string作为读入的变量，而不用int读入的变量的原因：防止用户输入错误，或利用程序漏洞，可以防止用户输入非法字符，使程序崩溃
	*/
	printf("可选指令（支持指令堆叠，指令序号之间，用半角逗号隔开）：\n");
	printf("0.没有附加参数\n");
	printf("1.使用TV端下载（需要先进行TV版登录，使用后，下载的视频可能没有水印）\n");
	printf("2.仅下载音频\n");
	printf("3.跳过下载字幕\n");
	printf("4.跳过下载封面\n");
	printf("5.分P下载\n");
	printf("6.画质优先\n");
	printf("7.退出登录，使用其他账号进行下载\n");
	//用序号的形式简化复杂指令的输入
	cin>>b;//读入指令
	for(int i=0;i<b.length();i++)
	{
		if(a[i]=='0'&&b.length()==1) break;//判断是否没有附加参数
		else
		{
			if(a[1]!='0'&&b.length()!=1)//没有附加参数时，不能有其他的参数
			{
				printf("指令错误。\n");
				system("PAUSE");
			return 0;
			}
		}
		if(b[i]=='1')
		{
			if(access("BBDownTV.data",F_OK))//判定"BBDownTV.data"是否存在，即为判断是否登陆TV版
			{
				printf("请用手机客户端扫描本目录下的qrcode.png登录TV版。\n");
				a+=" logintv";
				system(a.c_str());
				system("PAUSE");
				return 0;
			}
			else a+=" -tv";//把TV命令加入要执行的指令中
		}
		if(b[i]=='2') a+=" --audio-only";//把仅下载音频命令加入要执行的指令中
		if(b[i]=='3') a+=" --skip-subtitle";//把不下载字幕命令加入要执行的指令中
		if(b[i]=='4') a+=" --skip-cover";//把不下载封面命令加入要执行的指令中
		if(b[i]=='5')
		{
			string c;
			printf("请输入需要下载的集（多个连续的集数用连词符隔开，多个连续的集数或单个集数用半角逗号隔开）\n");
			cin>>c;//读入集数
			a=a+" -p "+c;//把集数和命令加入要执行的指令
		}
		if(b[i]=='6')
		{
			string c;
			printf("请输入优先级，各个项目之间用半角逗号隔开。（目前只支持非中文的画质）\n");//不支持中文是因为string不支持中文
			cin>>c;//读入集数
			a=a+" --dfn-priority "+c;//把集数和命令加入要执行的指令
		}
		if(b[i]=='7')
		{
			system("del BBDown.data");//删除登陆文件（此命令有报毒风险）
			printf("已退出登录。\n");
			system("PAUSE");
		}
	}
	system(a.c_str());//执行总命令
	system("PAUSE");
	return 0;
}