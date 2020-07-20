#include "NeuralNetwork.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Random.h"
#include <cmath>

using namespace std;
const double PI = 3.141592653589793238463;

NeuralNetwork::NeuralNetwork()
{
	//srand(time(NULL));
	srand(static_cast <unsigned> (time(0)));
	
	this->w1 = -2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 -(-2))));
	this->w2 = -2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - (-2))));
	this->b = -2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 -(-2))));
	
	/*this->w1 = Random(-2, 2);
	this->w2 = Random(-2, 2);
	this->b = Random(-2, 2);*/
}

float** NeuralNetwork::inputs()
{
	int rows=10000, columns=3,c=0; 

	float inputss[10000][3];

	float data[24] = { 3,1.5,         1,
		               2, 1,          0,
		               4, 1.5,        1,
		               3, 1,          0,
		               3.5, 0.5,       1,
		               2, 0.5,         0,
		               5.5, 1,        1,
		               1, 1,          0 };




	for (int a = 0; a < rows; a++)
	{
		inputss[a][0] = data[c];     //input1
		inputss[a][1] = data[c+1];   //input2
		inputss[a][2] = data[c+2];   //target
		c += 3;
		//cout << inputss[a][0] << " " << inputss[a][1] << " "<<inputss[a][2] << endl;
		if (c >= 23)
			c = 0;
		
	}
	//inputss[a][0] = a;
	//inputss[a][1] = sin(inputss[a][0] * PI / 180);
		//for (int b = 0; b < columns; b++)
		//{
			//inputss[a][0] = Random(1,8);
			
			//c = inputss[a][0];
			//cout << c << " ";
			//if (c % 2 == 0)
				//inputss[a][1] = 1;
			//else
			//	inputss[a][1] = 0;
			//cout << inputss[a][0] <<" " <<inputss[a][1] << endl;
		//}
			
	float** iarray;
	iarray = new float* [rows];
	for (int i = 0; i < rows; i++)
	{
		iarray[i] = new float[columns];
		for (int j = 0; j < 3; j++)
		{
			iarray[i][j] = inputss[i][j];
			//cout << iarray[i][j] << " ";
		}
		//cout << endl;
		
	}
	
	cout <<"\n\nW1 = " << this->w1 << endl << "b= " << this->b << endl << endl;
	this->m_input_array = iarray;

	return m_input_array;
}

 float NeuralNetwork::sigmoid( float z)
{
	return 1 / (1 + exp(-z));

}

float NeuralNetwork::sigmoid_prime(float z)
{
	return sigmoid(z) * (1 - sigmoid(z));
}


void NeuralNetwork::train()
{
	float learning_rate = 0.1;
	float z,pred,target,loss,dloss_dpred, dpred_dz, dz_dw1, dz_dw2, dz_db, dloss_dz, dloss_dw1, dloss_dw2, dloss_db;

	for (int i = 0; i < 10000; i++)
	{
		z = (this->m_input_array[i][0] * this->w1 + this->m_input_array[i][1]*this->w2) + this->b;
		pred = sigmoid(z); //network prediction	
		target = m_input_array[i][2]; //Target
		loss = abs(pred - target); //loss "cost function"
		if (i >= 9800)
		{
			cout << "Input " << i << endl;
			cout << "Z= " << z << endl;
			
			cout << "Pred= " << pred <<endl;
			
			cout << "Target= " << target<<endl;
			

			cout << "Loss= "<<loss <<endl<<endl;
		}

		dloss_dpred = 2 * (pred - target); //Derivative of loss with respect to pred.

		dpred_dz = sigmoid_prime(z); //Derivative of pred with respect to Z.

			dz_dw1 = m_input_array[i][0]; // Derivative of Z with respect to weight1.
			dz_dw2 = m_input_array[i][1]; // Derivative of Z with respect to weight2.
			dz_db = 1; // Derivative of Z with respect to bias.

		dloss_dz = dloss_dpred * dpred_dz; // Derivative of loss with respect to Z.

		dloss_dw1 = dloss_dz * dz_dw1; // Derivative of loss with respect to weight1.
		dloss_dw2 = dloss_dz * dz_dw2; // Derivative of loss with respect to weight2.
		
		dloss_db = dloss_dz * dz_db; // Derivative of loss with respect to bias.

		this->w1 = this->w1 - learning_rate * dloss_dw1; //update the weight by a small fraction "Alpha" multiply derivative of loss w.r.t w1.
		this->w2 = this->w2 - learning_rate * dloss_dw2; //update the weight by a small fraction "Alpha" multiply derivative of loss w.r.t w2.	
		this->b = this->b - learning_rate * dloss_db;//update the bias by a small fraction "Alpha" multiply derivative of loss w.r.t b.

	}
	cout << "\nWeights and biases after training \n";
	cout << "W1 = " << this->w1 << endl << "b= " << this->b << endl;

	
}

void NeuralNetwork::test()
{
	float prediction,z;

	float x1 = 2;
	float x2 = 0.5;
	z = (this->w1 * x1 + this->w1 * x2) + this->b;

	prediction = sigmoid(z);

	//cout << "Real       = " << m_input_array[90][1]<<endl;
	cout << "Predicted = " << prediction << endl;

}