#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <random>
#include <iostream>
#include <math.h>


#define BinWidth 1200
#define BinDepth 800
#define BinHeight 2055
int nbInstanceGenerated;

using namespace std;

lognormal_distribution<double> repetition(0.544, 0.658);
//lognormal_distribution<double> volume(9.526, 0.584);
lognormal_distribution<double> hwratio(-0.654, 0.453);
normal_distribution<double> dwratio(0.695, 0.118);

//////////////////////////////////
//Practical constraint generators
//////////////////////////////////

//Density generators
gamma_distribution<double> lowDensity(3.211,1/0.017);
lognormal_distribution<double> highDensity(6.502,0.208);

//Load cap - section 1 (density in 31.76 to 434.64)
double straight3 = 250;
gamma_distribution<double> curve1(5.698,1/0.007);
gamma_distribution<double> curve2(4.589,1/0.007);
gamma_distribution<double> curve3(12.324,1/0.027);

//Load cap - section 2 (density in 434.64 to 617.56)
double straight1_1 = 2000;
//normal_distribution<double> curve4(1278.346,112.354);
lognormal_distribution<double> curve4(7.137,0.112);
lognormal_distribution<double> curve5_1(6.837,0.082);

//Load cap - section 3 (density in 617.56 to 1771.11)
double straight1_2 = 2000;
double straight4 = 2600;
lognormal_distribution<double> curve5_2(7.086,0.059);

//Item shape generators
normal_distribution<double> wd_difference(1.229,3.264);
weibull_distribution<double> widthGen(2.289,22.802);

int round(double input)
{
	int retNb;

	if(input - (int)input < 0.5)
		retNb = (int)input;
	else
		retNb = (int)(input + 1);

	return retNb;
}

double generateVSVolume()
{
	double random = (double)(rand() % 100) / 100.0;

	if(random < 0.02)
		return 3.5;
	else if(random < 0.11)
		return 4.5;
	else if(random < 0.16)
		return 5.5;
	else if (random < 0.22)
		return 6.5;
	else if (random < 0.37)
		return 7.5;
	else if (random < 0.56)
		return 8.5;
	else if (random < 0.67)
		return 9.5;
	else if (random < 0.78)
		return 10.5;
	else if (random < 0.97)
		return 11.5;
	else 
		return 12;
}

double generateSVolume()
{
	double random = (double)(rand() % 100) / 100.0;

	if(random < 0.15)
		return 12.5;
	else if (random < 0.26)
		return 13.5;
	else if(random < 0.38)
		return 14.5;
	else if(random < 0.6)
		return 15.5;
	else if(random < 0.71)
		return 16.5;
	else if(random < 0.79)
		return 17.5;
	else if (random < 0.89)
		return 18.5;
	else if (random < 0.98)
		return 19.5;
	else 
		return 20;
}

double generateMVolume()
{
	double random = (double)(rand() % 100) / 100.0;

	if(random < 0.11)
		return 20.5;
	else if (random < 0.27)
		return 21.5;
	else if(random < 0.37)
		return 22.5;
	else if(random < 0.46)
		return 23.5;
	else if(random < 0.54)
		return 24.5;
	else if(random < 0.61)
		return 25.5;
	else if (random < 0.67)
		return 26.5;
	else if (random < 0.73)
		return 27.5;
	else if (random < 0.78)
		return 28.5;
	else if (random < 0.86)
		return 29.5;
	else if (random < 0.91)
		return 30.5;
	else if (random < 0.96)
		return 31.5;
	else 
		return 32.5;
}

double generateLVolume()
{
	double random = (double)(rand() % 100) / 100.0;

	if(random < 0.19)
		return 33;
	else if (random < 0.42)
		return 35;
	else if(random < 0.53)
		return 37;
	else if(random < 0.6)
		return 39;
	else if(random < 0.67)
		return 41;
	else if(random < 0.72)
		return 43;
	else if (random < 0.79)
		return 45;
	else if (random < 0.86)
		return 47;
	else if (random < 0.89)
		return 49;
	else if (random < 0.97)
		return 51;
	else
		return 53;
}

double generateVLVolume()
{
	double random = (double)(rand() % 100) / 100.0;

	if(random < 0.15)
		return 57.5;
	else if (random < 0.3)
		return 62.5;
	else if(random < 0.6)
		return 67.5;
	else if(random < 0.8)
		return 72.5;
	else if(random < 0.9)
		return 77.5;
	else if(random < 0.925)
		return 82.5;
	else if (random < 0.95)
		return 87.5;
	else
		return 97.5;
}

double generateDensity(default_random_engine generator)
{
	double random = (double)(rand() % 10000) / 10000.0;

	if(random < 0.3132)
	{
		return lowDensity(generator);
	}
	else
	{
		return highDensity(generator);
	}
}

double generateLoadCap(default_random_engine generator, double density)
{
	double random = (double)(rand() % 10000) / 10000.0;

	if(density < 434.64)
	{
		if(random < 0.1684)
		{
			return straight3;
		}
		else if(random < 0.4117)
		{
			double random3 = (double)(rand() % 6) / 100.0 + 0.97;
			double nb = curve1(generator)*random3;
			if(nb < 250)
				return 250;
			else
				return nb;
		}
		else if(random < 0.6865)
		{
			double random3 = (double)(rand() % 6) / 100.0 + 0.97;
			double nb = curve2(generator)*random3;
			if(nb < 250)
				return 250;
			else
				return nb;
		}
		else
		{
			double random3 = (double)(rand() % 6) / 100.0 + 0.97;
			double nb = curve3(generator)*random3;
			if(nb < 250)
				return 250;
			else
				return nb;
		}
	}
	else if(density < 617.56)
	{
		double random2 = (double)(rand() % 100) / 100.0;
		if(random2 < 0.04)
			return (int)(rand() % 1200) + 800;
		else if(random2 < 0.06)
			return (int)(rand() % 200) + 300;
		else if(random2 < 0.065)
			return (int)(rand() % 500) + 2000;
		if(random < 0.6513)
		{
			double random3 = (double)(rand() % 6) / 100.0 + 0.97;
			return curve4(generator)*random3;
		}
		else if(random < 0.95)
		{
			double random3 = (double)(rand() % 6) / 100.0 + 0.97;
			return curve5_1(generator)*random3;
		}
		else
		{
			return straight1_1;
		}
	}
	else
	{
		double random2 = (double)(rand() % 100) / 100.0;
		if(random2 < 0.06)
			return (int)(rand() % 1600) + 400;
		if(random2 < 0.08)
			return (int)(rand() % 500) + 2000;
		if(random < 0.8102)
		{
			return straight1_2;
		}
		else if(random < 0.9515)
		{
			double random3 = (double)(rand() % 6) / 100.0 + 0.97;
			return curve5_2(generator)*random3;
		}
		else
		{
			return straight4;
		}
	}
}

string generateItemShape()
{
	double random = (double)(rand() % 10000) / 10000.0;

	if(random < 0.8719)
	{
		return "FULL";
	}
	else if(random < 0.9944)
	{
		return "ALL_EDGES";
	}
	else if(random < 0.9950)
	{
		return "LONG_EDGES";
	}
	else if(random < 0.9955)
	{
		return "SHORT_EDGES";
	}
	else
	{
		return "CORNERS";
	}
}

vector<double> width_depth_reduce(default_random_engine generator)
{
	double random = (double)(rand() % 10000) / 10000.0;
	vector<double> wdreduce;
	if(random < 0.5297)
	{
		wdreduce.push_back(0);
		wdreduce.push_back(0);
	}
	else
	{
		double width = widthGen(generator);
		double difference = wd_difference(generator);

		if(width + difference > 0)
		{
			wdreduce.push_back(width);
			wdreduce.push_back(width + difference);
		}
		else
		{
			wdreduce.push_back(width - difference);
			wdreduce.push_back(width);
		}
	}

	return wdreduce;
}

int main()
{
	srand(1000);
	default_random_engine generator;
	generator.seed(1000);
	

	nbInstanceGenerated = 5;

	vector<int> nbItems;
	nbItems.push_back(50);
	nbItems.push_back(100);
	nbItems.push_back(150);
	nbItems.push_back(200);
	nbItems.push_back(500);
	nbItems.push_back(1000);
	nbItems.push_back(1500);
	nbItems.push_back(2000);

	for (int Class = 1; Class < 5; Class++)
	{
		for (int size = 0; size < nbItems.size(); size++)
		{
			for (int i = 0; i < nbInstanceGenerated; i++)
			{
				double number;
				double volu;
				double hwnumber;
				double dwnumber;
				int totalNb = 0;
				int width;
				int depth;
				int height;

				string fileName = "Results/Class" + to_string(Class) + "_" + to_string(nbItems[size]) + "Items_Instance" + to_string(i+1) + ".txt";
				ofstream instance;
				instance.open(fileName);

				if(Class == 1)
				{
					int vsCt = 0;
					int sCt = 0;
					int mCt = 0;
					int lCt = 0;
					int vlCt = 0;

					while(totalNb < nbItems[size])
					{
						number = repetition(generator);

						int rep = round(number);

						if(rep == 0)
							rep = 1;

						if(totalNb + rep > nbItems[size])
							rep = nbItems[size] - totalNb;

						if(vsCt < 0.285 * nbItems[size])
						{
							volu = generateVSVolume();
							vsCt += rep;
						}
						else if(sCt < 0.87 * nbItems[size])
						{
							volu = generateSVolume();
							sCt += rep;
						}
						else if(mCt < 0.99 * nbItems[size] && totalNb < nbItems[size])
						{
							volu = generateMVolume();
							mCt += rep;
						}
						else if(totalNb < nbItems[size])
						{
							volu = generateLVolume();
							vlCt += rep;
						}

						double density = generateDensity(generator);
						int weight = (int)density * volu;
						int loadCap = (int)generateLoadCap(generator,density);
						string shape = generateItemShape();
						vector<double> wdReduce = width_depth_reduce(generator);
						int widthReduce = (int)wdReduce[0];
						int depthReduce = (int)wdReduce[1];
						int sequenceNo = (int)(rand() % 1000000);

						hwnumber = hwratio(generator);
						dwnumber = dwratio(generator);

						volu *= 1000000;
						double wdouble = pow(volu / (dwnumber*hwnumber), 1.0/3);
						width = round(wdouble);

						double ddouble = width * dwnumber;
						depth = round(ddouble);

						double hdouble = width * hwnumber;
						height = round(hdouble);

						instance << width << "\t" << depth << "\t" << height << "\t" << weight << "\t" << loadCap << "\t" << widthReduce << "\t" << depthReduce << "\t" << shape << "\t" << rep << "\t" << sequenceNo << endl;

						totalNb += rep;
					}//while(totalNb < nbItems)
				}//if(Class == 1)
				else if(Class == 2)
				{
					int vsCt = 0;
					int sCt = 0;
					int mCt = 0;
					int lCt = 0;
					int vlCt = 0;

					while(totalNb < nbItems[size])
					{
						number = repetition(generator);

						int rep = round(number);

						if(rep == 0)
							rep = 1;

						if(totalNb + rep > nbItems[size])
							rep = nbItems[size] - totalNb;

						if(vsCt < 0.33 * nbItems[size])
						{
							volu = generateVSVolume();
							vsCt += rep;
						}
						else if(sCt < 0.65 * nbItems[size])
						{
							volu = generateSVolume();
							sCt += rep;
						}
						else if(mCt < 0.88 * nbItems[size] && totalNb < nbItems[size])
						{
							volu = generateMVolume();
							mCt += rep;
						}
						else if(lCt < 0.96 * nbItems[size] && totalNb < nbItems[size])
						{
							volu = generateLVolume();
							lCt += rep;
						}
						else if(totalNb < nbItems[size])
						{
							volu = generateVLVolume();
							vlCt += rep;
						}

						double density = generateDensity(generator);
						int weight = (int)density * volu;
						int loadCap = (int)generateLoadCap(generator,density);
						string shape = generateItemShape();
						vector<double> wdReduce = width_depth_reduce(generator);
						int widthReduce = (int)wdReduce[0];
						int depthReduce = (int)wdReduce[1];
						int sequenceNo = (int)(rand() % 1000000);

						volu *= 1000000;


						hwnumber = hwratio(generator);
						dwnumber = dwratio(generator);

						double wdouble = pow(volu / (dwnumber*hwnumber), 1.0/3);
						width = round(wdouble);

						double ddouble = width * dwnumber;
						depth = round(ddouble);

						double hdouble = width * hwnumber;
						height = round(hdouble);

						instance << width << "\t" << depth << "\t" << height << "\t" << weight << "\t" << loadCap << "\t" << widthReduce << "\t" << depthReduce << "\t" << shape << "\t" << rep << "\t" << sequenceNo << endl;

						totalNb += rep;
					}//while(totalNb < nbItems)
				}
				else if(Class == 3)
				{
					int vsCt = 0;
					int sCt = 0;
					int mCt = 0;
					int lCt = 0;
					int vlCt = 0;

					while(totalNb < nbItems[size])
					{
						number = repetition(generator);

						int rep = round(number);

						if(rep == 0)
							rep = 1;

						if(totalNb + rep > nbItems[size])
							rep = nbItems[size] - totalNb;

						if(vsCt < 0.67 * nbItems[size])
						{
							volu = generateVSVolume();
							vsCt += rep;
						}
						else if(sCt < 0.92 * nbItems[size])
						{
							volu = generateSVolume();
							sCt += rep;
						}
						else if(mCt < 0.97 * nbItems[size] && totalNb < nbItems[size])
						{
							volu = generateMVolume();
							mCt += rep;
						}
						else if(lCt < 0.992 * nbItems[size] && totalNb < nbItems[size])
						{
							volu = generateLVolume();
							lCt += rep;
						}
						else if(totalNb < nbItems[size])
						{
							volu = generateVLVolume();
							vlCt += rep;
						}

						double density = generateDensity(generator);
						int weight = (int)density * volu;
						int loadCap = (int)generateLoadCap(generator,density);
						string shape = generateItemShape();
						vector<double> wdReduce = width_depth_reduce(generator);
						int widthReduce = (int)wdReduce[0];
						int depthReduce = (int)wdReduce[1];
						int sequenceNo = (int)(rand() % 1000000);

						volu *= 1000000;


						hwnumber = hwratio(generator);
						dwnumber = dwratio(generator);

						double wdouble = pow(volu / (dwnumber*hwnumber), 1.0/3);
						width = round(wdouble);

						double ddouble = width * dwnumber;
						depth = round(ddouble);

						double hdouble = width * hwnumber;
						height = round(hdouble);

						instance << width << "\t" << depth << "\t" << height << "\t" << weight << "\t" << loadCap << "\t" << widthReduce << "\t" << depthReduce << "\t" << shape << "\t" << rep << "\t" << sequenceNo << endl;

						totalNb += rep;
					}//while(totalNb < nbItems)
				}
				else if(Class == 4)
				{
					int vsCt = 0;
					int sCt = 0;
					int mCt = 0;
					int lCt = 0;
					int vlCt = 0;

					while(totalNb < nbItems[size])
					{
						number = repetition(generator);

						int rep = round(number);

						if(rep == 0)
							rep = 1;

						if(totalNb + rep > nbItems[size])
							rep = nbItems[size] - totalNb;

						if(vsCt < 0.78 * nbItems[size])
						{
							volu = generateVSVolume();
							vsCt += rep;
						}
						else if(sCt < 0.91 * nbItems[size])
						{
							volu = generateSVolume();
							sCt += rep;
						}
						else if(mCt < 0.97 * nbItems[size] && totalNb < nbItems[size])
						{
							volu = generateMVolume();
							mCt += rep;
						}
						else if(lCt < 0.99 * nbItems[size] && totalNb < nbItems[size])
						{
							volu = generateLVolume();
							lCt += rep;
						}
						else if(totalNb < nbItems[size])
						{
							volu = generateVLVolume();
							vlCt += rep;
						}

						double density = generateDensity(generator);
						int weight = (int)density * volu;
						int loadCap = (int)generateLoadCap(generator,density);
						string shape = generateItemShape();
						vector<double> wdReduce = width_depth_reduce(generator);
						int widthReduce = (int)wdReduce[0];
						int depthReduce = (int)wdReduce[1];
						int sequenceNo = (int)(rand() % 1000000);

						volu *= 1000000;


						hwnumber = hwratio(generator);
						dwnumber = dwratio(generator);

						double wdouble = pow(volu / (dwnumber*hwnumber), 1.0/3);
						width = round(wdouble);

						double ddouble = width * dwnumber;
						depth = round(ddouble);

						double hdouble = width * hwnumber;
						height = round(hdouble);

						instance << width << "\t" << depth << "\t" << height << "\t" << weight << "\t" << loadCap << "\t" << widthReduce << "\t" << depthReduce << "\t" << shape << "\t" << rep << "\t" << sequenceNo << endl;

						totalNb += rep;
					}//while(totalNb < nbItems)
				}

				instance.close();
			}//for (int i = 0; i < nbInstanceGenerated; i++)
		}
	}
	return 0;
}