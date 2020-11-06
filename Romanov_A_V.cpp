// Romanov_A_V.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Zapis
{
public:

	Zapis() {};

	Zapis(int den, int chas, int minuta, string predmet, int auditoria)
	{
		this->auditoria = auditoria;
		this->den = den;
		this->chas = chas;
		this->minuta = minuta;
		this->predmet = predmet;
	}

	int get_den()
	{
		return den;
	}

	int get_chas()
	{
		return chas;
	}

	int get_minuta()
	{
		return minuta;
	}

	int get_aud()
	{
		return auditoria;
	}

	string get_predmet()
	{
		return predmet;
	}


private:
	int den;
	int chas;
	int minuta;
	string predmet;
	int auditoria;
};

class Raspisanie
{
public:

	vector <Zapis> print_odin_den(vector <Zapis> spisok, int den)
	{
		for (int i = 0; i < n; i++)
		{
			if (list[i].get_den() == den)
			{
				spisok.push_back(list[i]);
			}
		}
		return spisok;
	}

	vector <Zapis> print_vse(vector <Zapis> spisok)
	{
		for (int i = 0; i < n; i++)
		{
			spisok.push_back(list[i]);
		}
		return spisok;
	}

	void dobavit_zapis(int d, int c, int m, string pr, int aud)
	{
		Zapis a(d, c, m, pr, aud);
		list.push_back(a);
		n++;
	}

	void udalit_zapis(int d, int c, int m, string pr, int aud)
	{
		for (int i = 0; i < n; i++)
		{
			int flag = 0;
			if (list[i].get_den() == d) flag++;
			if (list[i].get_chas() == c) flag++;
			if (list[i].get_minuta() == m) flag++;
            if (list[i].get_predmet() == pr)flag++;
			if (list[i].get_aud() == aud) flag++;
			if (flag == 4) { list.erase(list.begin() + i); n--; }
		}
	}

private:
	vector <Zapis> list;
	int n = 0;
};

Raspisanie rasp;

void iz_consoli()
{
    string sub;
    int h, m, aud, day;
    cout << "Новая запись:" << endl << "Введите день недели: "; cin >> day;
    cout << "Введите час: "; cin >> h;
    cout << "Введите минуты: "; cin >> m;
    cout << "Введите предмет: "; cin >> sub;
    cout << "Введите аудиторию: "; cin >> aud;
    rasp.dobavit_zapis(day, h, m, sub, aud);
    cout << endl;
}

void iz_file()
{
    vector <vector <string>> splitted_line;
    vector <string> buff;
    string line, buf;
    ifstream in("f.txt");
    if (in.is_open())
    {
        getline(in, line);
        int flag = 1;
        for (int i = 0; i < line.size(); i++)
        {
            if (flag % 5 == 0) splitted_line.push_back(buff);

            if (line[i] == ' ')
            {
                buff.push_back(buf);
                flag++;
                continue;
            }

            buf += line[i];
        }
    }
    in.close();
    for (int i = 0; i < splitted_line.size(); i++)
    {
        rasp.dobavit_zapis(stoi(splitted_line[i][0]), stoi(splitted_line[i][1]), stoi(splitted_line[i][2]), splitted_line[i][3], stoi(splitted_line[i][4]));
    }
}

void v_consol(Zapis obj)
{
    cout << "День недели: " << obj.get_den() << endl << "Время: " << obj.get_chas() << ":" << obj.get_minuta() << endl << "Предмет: " << obj.get_predmet()
        << endl << "Аудитория: " << obj.get_aud() << endl << endl;
}

int min(vector <Zapis> list, int flag = 0)
{
    int e = 0;

    if (flag == 1)
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (list[i].get_den() < list[e].get_den()) e = i;
        }
    }

    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].get_chas() < list[e].get_chas() && list[i].get_den() == list[e].get_den()) e = i;
    }

    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].get_minuta() < list[e].get_minuta() && list[i].get_chas() == list[e].get_chas()) e = i;
    }

    return e;
}

void odin_den()
{
    int e, n;
    string a;
    vector <Zapis> roster;
    cout << "Введите день, за который нужно вывести расписание: "; cin >> a;
    roster = rasp.print_vse(roster);
    n = roster.size();
    for (int i = 0; i < n; i++)
    {
        e = min(roster);
        v_consol(roster[e]);
        roster.erase(roster.begin() + e);
    }
    cout << endl << endl;
}

void vse_rasp()
{
    int e, n;
    vector <Zapis> roster;
    roster = rasp.print_vse(roster);
    n = roster.size();
    for (int i = 0; i < n; i++)
    {
        e = min(roster, 1);
        v_consol(roster[e]);
        roster.erase(roster.begin() + e);
    }
    cout << endl << endl;
}

void v_file()
{
    ofstream out;
    out.open("d.txt");
    if (out.is_open())
    {
        int e, n;
        vector <Zapis> roster;
        roster = rasp.print_vse(roster);
        n = roster.size();
        for (int i = 0; i < n; i++)
        {
            e = min(roster);
            out << "День недели: " << roster[i].get_den() << endl << "Время: " << roster[i].get_chas() << ":" << roster[i].get_minuta() << endl << "Предмет: "
                << roster[i].get_predmet() << endl << "Аудитория: " << roster[i].get_aud() << endl << endl;
            roster.erase(roster.begin() + e);
        }
    }
}

void udalit()
{
    string pr;
    int h, m, aud, day;
    cout << "Введите данные для удаления:" << endl << "Введите день недели: "; cin >> day;
    cout << "Введите час: "; cin >> h;
    cout << "Введите минуты: "; cin >> m;
    cout << "Введите предмет: "; cin >> pr;
    cout << "Введите аудиторию: "; cin >> aud;
    rasp.udalit_zapis(day, h, m, pr, aud);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Список команд:" << endl << "1 — добавить запись из консоли" << endl << "2 — добавить запись из файла" << endl << "3 — вывести все расписание"
        << endl << "4 — вывести расписание в файл" << endl << "5 — вывести расписание в файл вывести расписание за один день" << endl << "6 — удалить запись" << endl << "7 — выход" << endl << endl;

    rasp.dobavit_zapis(1, 16, 20, "Математика", 220);
    rasp.dobavit_zapis(1, 16, 20, "Физкультура", 66);

    while (true)
    {
        int c;
        cout << "Введите команду: "; cin >> c;
        cout << endl;
        if (c == 1) iz_consoli();
        if (c == 2) iz_file();
        if (c == 3) vse_rasp();
        if (c == 4) v_file();
        if (c == 5) odin_den();
        if (c == 6) udalit();
        if (c == 7) break;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
