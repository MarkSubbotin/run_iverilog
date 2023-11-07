#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <chrono>
#include <string>
#include <cstdlib>

using namespace std;
using namespace chrono;

int main(int argc, char* argv[])
{
	ofstream fout;

	// Будущие команды для компилятора iverilog
	string iverilogCmdString = "iverilog -o compvfile ";
	string vvpCmdString = "vvp compvfile";
	string gtkwaveCmdString = "gtkwave out.vcd";

	// Получение даты и времени запуска программы от системы
	time_t end_time = system_clock::to_time_t(system_clock::now());


	if (argc > 1)
	{
		// Открытие файла логов
		fout.open("LOG.txt",ios::app);

		// Запись даты и времени
		fout << ctime(&end_time) << endl << ">>> " << argc - 1 << " FILES READ:" << endl;


		for (int i = 1; i < argc; i++)
		{
			// Формирование команды для компиляции всех переданных файлов
			string s(argv[i]);
			iverilogCmdString.append(s).append(" ");
			fout << argv[i] << endl;
		}

		// Отчёт о генерации команд
		fout << endl << ">>> COMMANDS GENERATED:" << endl << iverilogCmdString << endl;
		fout << vvpCmdString << endl << gtkwaveCmdString << endl << endl;

		// Закрытие файла логов
		fout.close();

		// Выполнение команд iverilog
		system(iverilogCmdString.c_str());
		system(vvpCmdString.c_str());
		system(gtkwaveCmdString.c_str());

		// Удаление вспомогаельных файлов
		system("del compvfile");
		system("del out.vcd");
	}

	return 0;
}