#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/time.h>

using namespace std;

typedef struct {
	int value;
	int frequency;
} line_t;

typedef int* distribution_t; 

/** return value and frequency as 
line_t structure from line line **/
line_t get_values(string line)
{
	istringstream iss(line);
	int tmp[2];
	line_t l;

	for(int i = 0 ; i < 2 ; i++)
	{
		iss >> tmp[i];
		//cout << "value: " << tmp[i] << endl;
	}
	l.value = tmp[0];
	l.frequency = tmp[1]; 
	return l;
}

/** return the frequency sum in file f **/
int get_file_size(string f)
{
	string line;
	int result=0;
	line_t l;

	ifstream file(f.c_str(), ios::in);

	if(file) {
		while((getline(file, line))) {
			l = get_values(line);		
			result += l.frequency;
		}
		file.close();
	} else {
		cerr << "Error opening file : "<< f << endl;
		exit (-1);
	}
	return result;
}

/** return an array that contains f line and  update size **/
distribution_t init_distribution(string f, int& size)
{
	int i = 0;
	int j = 0;
	string line;
	line_t l;

	size = get_file_size(f);
	distribution_t t = new int[size];

	// Open file in read mode
	ifstream file(f.c_str(), ios::in);

	if(file) {
		while((getline(file, line))) {
			l = get_values(line);
			//cout << l.value << "	" << l.frequency << endl;
			for(j = i ; j < l.frequency + i ; j++)			
				t[j] = l.value;
			i += l.frequency;
		}
		file.close();
	} else {
		cerr << "Error opening file : "<< f << endl;
		exit (-1);
	}
	return t;
}

int get_average(distribution_t dist, int size)
{
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += dist[i];
	return sum/size;	
}

/**  select value with respect 
to distribution defined in dist **/
int select(distribution_t dist, int size)
{
	timeval time;
	gettimeofday(&time, NULL);
	srand(time.tv_usec);

	return dist[(random()%size)];
}

/** select value in a uniform
distribution in the inteval [v1, v2] **/
int select(int v1, int v2)
{
	if(v1 >= v2){
		cerr << "Error : the interval lower bound " << v1 << " should be lower than the upper bound " << v2 << endl;
		exit (-1);
	}
	
	int	val = v1;
	distribution_t tmp = new int[v2-v1+1];
	for(int i = 0;  i <= v2-v1 ; i++) {
		tmp[i] = val;
		cout << "tmp[" << i << "] = " << tmp[i] << endl;
		val++;
	}
	return select(tmp, v2-v1+1);
}
