#include<iostream>
using namespace std;
#include"Neuron.h"


void main()
{
	NeuronWeb nw;

	vector<double>in = { 0,0,0 };
	cout << nw.CalcSmth(in) << endl;
}