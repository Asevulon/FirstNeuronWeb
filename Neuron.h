#pragma once
#include<vector>
using namespace std;

struct Neuron
{
	vector<double> w;
	double fi;
	double out = 0;
	Neuron(int size);
};


class NeuronWeb
{
public:
	//слои
	vector<vector<Neuron>>s;
	NeuronWeb();
	void ProcessNeuron(Neuron& n, vector<double>& in);
	double CalcSmth(vector<double>& in);
	int Train();
	int GenerateIn(vector<double>& in);
};