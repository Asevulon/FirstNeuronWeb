#include"Neuron.h"

//диапазон значений
double rand(double left, double right)
{
	return left + (right - left) * double(rand()) / double(RAND_MAX);
}
Neuron::Neuron(int size)
{
	for (int i = 0; i < size; i++)
	{
		w.push_back(rand(0, 1));
	}
	fi = rand(0, 1);
}


NeuronWeb::NeuronWeb()
{
	s = vector < vector<Neuron>>(2, vector<Neuron>());
	s[0] = vector<Neuron>(4, Neuron(3));
	s[1].push_back(Neuron(4));
}


void NeuronWeb::ProcessNeuron(Neuron& n, vector<double>& in)
{
	double res = 0;
	for (int i = 0; i < in.size(); i++)
	{
		res += in[i] * n.w[i];
	}
	res -= n.fi;
	res = tanh(res);
	n.out = res;
}

double NeuronWeb::CalcSmth(vector<double>& in)
{
	vector<double>tin;

	for (int i = 0; i < s[0].size(); i++)
	{
		ProcessNeuron(s[0][i], in);
		tin.push_back(s[0][i].out);
	}
	ProcessNeuron(s[1][0], tin);
	return s[1][0].out;
}


int NeuronWeb::Train()
{
	double e = 0.1;
	int counter = 0;
	double error = 0;
	do
	{
		vector<double>in;
		int d = GenerateIn(in);
		double CurRes = CalcSmth(in);

		double topmist = (1 - s[1][0].out * s[1][0].out) * (d - s[1][0].out);
		double mist[4] = { 0,0,0,0 };

		for (int i = 0; i < 4; i++)
		{
			mist[i] = (1 - s[0][i].out * s[0][i].out) * topmist * s[1][0].w[i];
		}

		s[1][0].fi += e * topmist;
		for (int i = 0; i < 4; i++)
		{
			s[1][0].w[i] += e * topmist * s[0][i].out;
			s[0][i].fi += e * mist[i];
			for (int j = 0; j < 3; j++)
			{
				s[0][i].w[j] += e * mist[i] * in[j];
			}
		}
		error = s[1][0].out - d;
		error *= error;
		counter++;
	} while (error > 1e-6);
	return counter;
}


int NeuronWeb::GenerateIn(vector<double>& in)
{
	vector<double>res;
	int xr = 0;
	for (int i = 0; i < 3; i++)
	{
		int temp = rand(0.5, 1.5);
		res.push_back(temp);
		xr ^= temp;
	}
	in = res;
	return xr;
}
