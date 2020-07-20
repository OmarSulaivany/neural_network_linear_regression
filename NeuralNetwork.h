#ifndef NN_H
#define NN_H
class NeuralNetwork
{
public:
	NeuralNetwork();
	float** inputs();
    float sigmoid(float z);
	float sigmoid_prime(float z);
	void train();
	void test();
private:
	float w1,w2, b;
	float** m_input_array = nullptr;
};
#endif // !NN_H

