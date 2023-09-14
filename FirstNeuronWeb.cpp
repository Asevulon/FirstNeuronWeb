#include<iostream>
using namespace std;
#include"Neuron.h"


void main()
{
	srand(time(NULL));
	NeuronWeb nw;
	cout << nw.Train() << endl;
	vector<double>in = { 0,0,0 };
	cout << nw.CalcSmth(in) << endl;
	in = { 0,0,1 };
	cout << nw.CalcSmth(in) << endl;

}