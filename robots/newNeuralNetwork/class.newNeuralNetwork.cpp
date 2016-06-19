#include <math.h>

class Neural_Network;
class Neuron;
class Genome; 

class Neural_Network {
	
	int numberOfNeurons;
	int inputSize;
	int outputSize;

	double fitness;

	Neuron* Neurons;

	void initNetwork(int numberOfNeurons, int inputSize, int outputSize) {
		this->numberOfNeurons = numberOfNeurons;
		this->inputSize = inputSize;
		this->outputSize = outputSize;

		this->Neurons = new Neuron[numberOfNeurons];
	}



};

class Neuron {


		/**
     * Activation function
     */
    void sigmoid(double &input) {
        input = (1 / (1+exp(-input)));
    }
};

class Genome {

};

int main() {

	const int numberOfNeuralNets = 5;

	Neural_Network* Networks = new Neural_Network[numberOfNeuralNets];

}