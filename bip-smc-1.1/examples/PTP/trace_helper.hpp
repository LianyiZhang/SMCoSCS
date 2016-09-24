#include<iostream>

using namespace std;

void trace_i(string cmp_name, int val)
{
	cout << "var int " << cmp_name << " " << val << endl;
}

void trace_f(string cmp_name, float val)
{
	cout << "var float " << cmp_name << " " << val << endl;
}

void trace_d(string cmp_name, double val) 
{
	cout << "var double " << cmp_name << " " << val << endl;
}

void trace_b(string cmp_name, bool val)
{
	if(val == true)
		cout << "var bool " << cmp_name << " true" << endl;
	else
		cout << "var bool " << cmp_name << " false" << endl;
}
