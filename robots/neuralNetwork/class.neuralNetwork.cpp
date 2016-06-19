#include <iostream>
#include <math.h>
//#include <random>
#include <stdlib.h>
//#include <cstdlib>
#include <vector>
#define ARMA_DONT_USE_WRAPPER
#include <armadillo> // libary for linear algebra


using namespace arma;

/**
 * Class to create and use a single layered neural network
 *
 * @author: Lars Gröber
 */
class Neural_Network {

protected:
    int inputSize;
    int outputSize;
    int numberOfNeurons;

    double fitness;

    double chanceOfMutate = 0.001;
    double maxMutate = 0.01;

    mat outputVec;
    mat inputVec;

   
    /**
     * Activation function
     */
    void sigmoid(double &input) {
        input = 1 / (1+exp(-input));
    }

public:

    mat inputWeights;   // weights on synapses going to neurons
    mat outputWeights;  // weights on synapses going to output


    /**
     * Actually use network to get output from input vector
     *
     * @param: the input matrix - dim (inputRows, inputSize)
     * @returns: outputVec - Matrix of size (inputRows, outputSize)
     */
    mat forward(mat inputVec) {
        inputVec = normalise(inputVec, 2, 1);                   // normalise rows (as they are sets of inputs)
        this->inputVec = inputVec;
        mat nInput;
        nInput = inputVec * this->inputWeights;                 // adding all inputs for every neuron together - nInput has dim(input.rows, numberOfNeurons)

        for (int i = 0; i < this->inputVec.n_rows; ++i) {       // applying sigmoid function to every neuron
            for (int j = 0; j < this->inputSize; ++j) {
                this->sigmoid(nInput(i,j));
            }
        }

        this->outputVec = nInput * this->outputWeights;         // adding all inputs for every output together - outputVec has dim(inputRows, outputSize)

        for (int i = 0; i < this->inputVec.n_rows; ++i) {       // applying sigmoid function to every output
            for (int j = 0; j < this->outputSize; ++j) {
                this->sigmoid(this->outputVec(i,j));
            }
        }

        //outputVec = normalise(outputVec, 2, 1);    
        return outputVec;
    }

    /**
     * Initialize the neural network
     *
     * @param: information needed for the size of the neural network
     */
    void initNetwork(int inputSize, int outputSize, int numberOfNeurons) {
        this->inputSize = inputSize;
        this->outputSize = outputSize;
        this->numberOfNeurons = numberOfNeurons;

        this->inputWeights.set_size(inputSize, numberOfNeurons);
        this->outputWeights.set_size(numberOfNeurons, outputSize);
    }

    /**
     * Initializes Weights-Matrices with random values between -1 and 1
     */
    void initWeightsRandom() {
        std::srand(rand());

        double chanceOfZero = 0.2;

        for (int i = 0; i < this->inputWeights.n_rows; ++i) 
            for (int j = 0; j < this->inputWeights.n_cols; ++j) 
                this->inputWeights(i,j) = ((double)rand() / INT_MAX) < 1 - chanceOfZero ? (double)rand() / (INT_MAX / 2) -1 : 0;    // produce random number between -1 and 1 or effectively not connecting input/neurons

        for (int i = 0; i < this->outputWeights.n_rows; ++i) 
            for (int j = 0; j < this->outputWeights.n_cols; ++j) 
                this->outputWeights(i,j) = ((double)rand() / INT_MAX) < 1 - chanceOfZero ? (double)rand() / (INT_MAX / 2) -1 : 0;
    }

    /**
     * Initialize Weights-Matrices with given values
     */
    void setWeights(mat inputWeights, mat outputWeights) {
        this->inputWeights = inputWeights;
        this->outputWeights = outputWeights;
    }   

};

/**
 * This class contains all custom functions for training the neural network
 * like the custom cost-function.
 *
 * @author: Lars Gröber
 */
class Neural_Custom: public Neural_Network {

protected:
    

public:
    /**
     * Set the fitness for a given problem
     */
    void setFitness(double fitness) {
        this->fitness = fitness;
    }

    double getFitness() {
        return this->fitness;
    }

    /**
     * Breed a new network with another network and initialise it (has the same topology)
     *
     * @param: the other network to breed with
     * @return: the newly created network
     */
    Neural_Custom breed(Neural_Custom other_Neural) {

        mat theirInputW = other_Neural.inputWeights;
        mat theirOutputW = other_Neural.outputWeights;
        
        mat newInputW = theirInputW;
        mat newOutputW = theirOutputW;

        for (int i = 0; i < this->inputWeights.n_rows; ++i) 
            for (int j = 0; j < this->inputWeights.n_cols; ++j) 
                newInputW(i,j) = rand() < INT_MAX / 2 ? theirInputW(i,j) : this->inputWeights(i,j);     // with a chance of 1/2 use the own weight for the new network 
                
        for (int i = 0; i < this->outputWeights.n_rows; ++i) 
            for (int j = 0; j < this->outputWeights.n_cols; ++j)
                newOutputW(i,j) = rand() < INT_MAX / 2 ? theirOutputW(i,j) : this->outputWeights(i,j);

        Neural_Custom newNetwork;
        newNetwork.initNetwork(this->inputSize, this->outputSize, this->numberOfNeurons);           
        newNetwork.setWeights(newInputW, newOutputW);
        newNetwork.mutate();
        return newNetwork;
    }

    void mutate() {

        // with a chance of chanceOfMutate change one weight by something between 1-maxMutate and 1+maxMutate
        for (int i = 0; i < this->inputWeights.n_rows; ++i) 
            for (int j = 0; j < this->inputWeights.n_cols; ++j)
                this->inputWeights(i,j) *= (double)rand()/INT_MAX < this->chanceOfMutate ? 1+fmod((double)rand()/(INT_MAX/2)-1, this->maxMutate) : 1;   
                
        for (int i = 0; i < this->outputWeights.n_rows; ++i) 
            for (int j = 0; j < this->outputWeights.n_cols; ++j)
                this->outputWeights(i,j) *= (double)rand()/INT_MAX < this->chanceOfMutate ? 1+fmod((double)rand()/(INT_MAX/2)-1, this->maxMutate) : 1;
    }

    // TODO: Genetic sorting (fitness etc.), short-term plasticity

};

double fitness(double a, double b, double output) {
    double c = ((a + b) - output);
    return 1/exp(c*c*c);
}

void test();


int main() {
    int numberOfNetworks = 25;
    int inputSize = 2;
    int outputSize = 1;
    int numberOfNeurons = 2;

    test();

    std::srand(time(NULL));

    std::vector<Neural_Custom*> listNetworks;

    for (int i = 0; i < numberOfNetworks; ++i)
    {
        listNetworks.push_back(new Neural_Custom);
        listNetworks[i]->initNetwork(inputSize, outputSize, numberOfNeurons);
        listNetworks[i]->initWeightsRandom();
    }

    for (int i = 0; i < listNetworks.size(); ++i)
        {
            mat input = mat(1,2);
            input(0,0) = 2;
            input(0,1) = 4;
            input.print();
            mat output = listNetworks[i]->forward(input);
            output.print();
            std::cout << fitness((double)input(0,0), (double)input(0,1), (double)output(0,0)) << std::endl;
        }    







}















void test() {
    Neural_Custom neural;
    neural.initNetwork(2, 1, 2);
    neural.initWeightsRandom();

    Neural_Custom neural2;
    neural2.initNetwork(2, 1, 2);
    neural2.initWeightsRandom();

    Neural_Custom neural3 = neural.breed(neural2);

    mat input;
    input.set_size(1,2);
    input.fill(6.);

    std:cout << input(0,0) << std::endl;

    mat output;
    output = neural.forward(input);
    output.print();

    std::cout << "Neural2:" << std::endl;

    output = neural2.forward(input);
    output.print();

    std::cout << "Neural3:" << std::endl;

    output = neural3.forward(input);
    output.print();
}

