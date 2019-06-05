#include "stdafx.h" 
#include <iostream> 
#include <fstream> 
#include <string> 
#include <pthread.h>

using namespace std;
pthread_barrier_t barr;

string alph = "אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ";
string ALPH = "ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞ‗";
int count_alphs_1[33];

std::ifstream in_2;
std::ifstream in_1;
string buffer1_1;
string buffer2_2;
int length_file_1 = 0;
void *file1(void *param)
{

	return 0;
}
void *file2(void *param)
{
	pthread_barrier_wait(&barr);
	string buffer1_1;
	string buffer2_1;
	
	string *sp = static_cast<std::string*>(param);
	string file_name = *sp;

	std::ifstream in_1;
	in_1.open(file_name);

	for (int i = 0; i < 33; i++)
	{
		count_alphs_1[i] = 0;
	}

	int length_file_1 = 0;
	while (!in_1.eof()) // ןמהסקוע ךמכ-גא סכמג ג פאיכו 
	{
		getline(in_1, buffer1_1, ' ');
		length_file_1++;
	}

	auto position_in_file_1 = 0;
	while (length_file_1 > 0)
	{
		in_1.seekg(position_in_file_1, ios::beg);
		getline(in_1, buffer1_1, ' ');
		position_in_file_1 = in_1.tellg();
		// in_1.seekg(0, ios::beg); 
		while (!in_1.eof())
		{
			getline(in_1, buffer2_1, ' ');
			if (buffer1_1[0] == buffer2_1[0])
			{
				for (int i = 0; i < 33; i++)
				{
					if (buffer1_1[0] == alph[i] || buffer1_1[0] == ALPH[i])
					{
						count_alphs_1[i]++;
						break;
					}
				}
			}
		}
		length_file_1--;
	}
	cout << "File name: " << file_name << endl;
	for (int i = 0; i < 33; i++)
	{
		if (count_alphs_1[i] != 0)
		{
			printf("%c = %d\n", alph[i], count_alphs_1[i]);
			count_alphs_1[i] = 0;
		}
	}
	pthread_barrier_wait(&barr);

	return 0;
}
int main(int argc, char* argv[])
{
	pthread_barrier_init(&barr, NULL, 2);
	in_2.open("in_2.txt");
	in_1.open("in_1.txt");


	while (!in_1.eof()) // ןמהסקוע ךמכ-גא סכמג ג פאיכו 
	{
		getline(in_1, buffer1_1, ' ');
		length_file_1++;
	}
	string file_name = "in_2.txt";
	pthread_t mythread;
	pthread_create(&mythread, NULL, file2, (void*)&file_name);
	for (int i = 0; i < 33; i++)
	{
		count_alphs_1[i] = 0;
	}
	string file_name_2 = "in_1.txt";
	file2((void*)&file_name_2);

	system("pause");
	return 1;
}