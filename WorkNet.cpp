#include<iostream>
#include<windows.h>
#include<string>
#include<fstream>
#include<vector>
#include <conio.h>

using namespace std;

void SetLang()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); 
}

void ClearFile(string name = "file.txt")
{
	char path[MAX_PATH];
	GetCurrentDirectory(sizeof(path), path);
    string pp = path;
	pp += "\\" + name;
	ofstream outt(pp.c_str());
	outt << "";
	outt.close();
}

int main()
{
	SetLang();
	char path[MAX_PATH];
    GetCurrentDirectory(sizeof(path), path);
    string pp = path;
    ClearFile();
	pp = "netsh wlan show profiles >> " + pp + "\\file.txt";
	system(pp.c_str());
	pp = path;
	ifstream inp(pp + "\\file.txt");
	vector <string> sett;
	while(inp.peek() != EOF)
	{
		string noww;
		getline(inp, noww);
		size_t pos = noww.find(" : ");
    	if (pos != string::npos)
			sett.push_back(noww.substr(pos + 3, noww.size() - 1));
	}
	inp.close();
	int pos = 0;
	char ch;
	do
	{	
		string outstr;
		for(int i = 0; i < sett.size(); i++)
		{
			if(pos == i)
			{
				outstr.append("> ");
			}
			else
			{
				outstr.append("  ");
			}
			outstr.append(sett[i] + '\n');
			cout << outstr;
			outstr = "";
		}
		ch = _getch();
		system("cls");
		if((ch == 80) && (pos < (sett.size() - 1)))
		{
			pos++;
		}
		else if((ch == 80) && (pos == (sett.size() - 1)))
		{
			pos = 0;
		}
		if(ch == 72 && pos > 0)
		{
			pos--;
		}
		else if(ch == 72 && pos == 0)
		{
			pos = sett.size() - 1;
		}
	}
	while(ch != 13);
	ClearFile();
	pp = "netsh wlan show profiles name=\"" + sett[pos] + "\" key=clear >> " + static_cast<string>(path) + "\\file.txt";
	system(pp.c_str());
	pp = path;
	inp.open(pp + "\\file.txt");
	bool WifiIsOpen = true;
	while(inp.peek() != EOF)
	{
		string noww;
		getline(inp, noww);
		size_t po = noww.find("    Содержимое ключа            : ");
    	if (po != string::npos)
    	{
			cout << "Wifi: " << sett[pos] << "\tPassword: "<< noww.substr(34, noww.size() - 1) << "\n\n\n";
			WifiIsOpen = false;
		}
	}
	inp.close();
	if(WifiIsOpen)
	{
		cout << "Сеть открытая\nНу или произошла какая-то ошибка. Бывает...\n\n\n";
	}
	ClearFile();
	pp = "erase " + pp + "\\file.txt";
	system(pp.c_str());
	system("pause");
}
