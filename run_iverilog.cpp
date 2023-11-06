#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <chrono>
#include <string>
#include <cstdlib>

using namespace std;
using namespace chrono;

int main(int argc, char* argv[])
{
	string iverilogCmdString = "iverilog -o compvfile ";
	string vvpCmdString = "vvp compvfile";
	string gtkwaveCmdString = "gtkwave out.vcd";

	time_t end_time = system_clock::to_time_t(system_clock::now());

	ofstream fout;

	if (argc > 1)
	{
		fout.open("LOG.txt",ios::app);

		fout << ctime(&end_time) << endl << ">>> " << argc - 1 << " FILES READ:" << endl;

		for (int i = 1; i < argc; i++)
		{
			string s(argv[i]);
			iverilogCmdString.append(s).append(" ");
			fout << argv[i] << endl;
		}

		fout << endl << ">>> COMMANDS GENERATED:" << endl << iverilogCmdString << endl;
	
		fout << vvpCmdString << endl << gtkwaveCmdString << endl << endl;

		fout.close();

		system(iverilogCmdString.c_str());
		system(vvpCmdString.c_str());
		system(gtkwaveCmdString.c_str());
		system("del compvfile");
		system("del out.vcd");
	}

	return 0;
}