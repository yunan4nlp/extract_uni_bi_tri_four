#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "Utf.h"

void save(ofstream& os, map<string, long>& state);
static int verboseIter = 1000;

int main(int argc, char* argv[]) {
	string line;
	vector<string> chs;
	map<string, long> uni, bi, tri, four;
	for (int file_num = 1; file_num < argc - 1; file_num++)
	{
		ifstream read(argv[file_num]);
		if (read.is_open())
		{
			cout << "extract " << argv[file_num] << " file.." << endl;
			int line_num = 0;
			while (getline(read, line))
			{
				getCharactersFromUTF8String(line, chs);
				int char_size = chs.size();
				for (int idx = 0; idx < char_size; idx++)
					uni[chs[idx]]++;
				for (int idx = 0; idx < char_size - 1; idx++)
					bi[chs[idx] + "@$" + chs[idx + 1]]++;
				for (int idx = 0; idx < char_size - 2; idx++)
					tri[chs[idx] + "@$" + chs[idx + 1] + "@$" + chs[idx + 2]]++;
				for (int idx = 0; idx < char_size - 3; idx++)
					four[chs[idx] + "@$" + chs[idx + 1] + "@$" + chs[idx + 2] + "@$" + chs[idx + 3]]++;
				line_num++;
				if (line_num % verboseIter == 0)
					cout << line_num << " ";
			}
			cout << endl;
			read.close();
		}
		else {
			cout << argv[file_num] << " file don't exist. " << endl;
			return 0;
		}
	}
	ofstream os(argv[argc - 1]);
	if (os.is_open()) {
		cout << "save state to " << argv[argc - 1] << "..." << endl;
		cout << "save uni..." << endl;
		save(os, uni);
		cout << "save bi..." << endl;
		save(os, bi);
		cout << "save tri..." << endl;
		save(os, tri);
		cout << "save four..." << endl;
		save(os, four);
		os.close();
		cout << "save ok" << endl;
	}
	return 0;
}

void save(ofstream& os, map<string, long>& state) {
	int line_num = 0;
	for (map<string, long>::iterator it = state.begin();
		it != state.end(); it++)
	{
		os << it->first << endl;
		line_num++;
		if (line_num % verboseIter == 0)
			cout << line_num << " ";
	}
	os.flush();
	cout << endl;
}
