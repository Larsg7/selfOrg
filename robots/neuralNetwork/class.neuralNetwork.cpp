#include <iostream>
#include <math.h>
//#include <random>
#include <stdlib.h>
//#include <cstdlib>
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

    double STPTrigger;                                          // value at which STP is applied

    bool STPOn = false;

    mat outputVec;
    mat inputVec;

   
    /**
     * Activation function
     */
    void sigmoid(double &input) {
        input = (1 / (1+exp(-input)));
    }

    /**
     * Derivative of the activation function
     */
    void sigmoidPrime(double &input) {
        input = (exp(-input) / pow((1+exp(-input)),2));
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
        inputVec = normalise(inputVec, 2, 1);                   // normalize rows (as they are sets of inputs)
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
     * Initializes Weights-Matrices with random values between 0 and 1
     */
    void initWeightsRandom() {
        arma_rng::set_seed_random();
        this->inputWeights.randu();
        this->outputWeights.randu();
    }

    /**
     * Initialize Weights-Matrices with given values
     */
    void initWeights(mat inputWeights, mat outputWeights) {
        this->inputWeights = inputWeights;
        this->outputWeights = outputWeights;
    }


    // TODO: Function learn (takes an input matrix, trains network)

};

/**
 * This class contains all custom functions for training the neural network
 * like the custom cost-function.
 *
 * @author: Lars Gröber
 */
class Neural_Custom: public Neural_Network {

protected:
    /**
     * Use STP to update weights
     *
     * @param: the index (0 to numberOfNeurons-1) of the neuron which fired
     */
    void STP(int inputFired) {
        for (int i = 0; i < ; ++i)
        {
            /* code */
        }
    }

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
     * inject winners genes in looser
     */
    void breed(Neural_Custom other_Neural) {
        mat theirInputW = other_Neural.inputWeights;
        mat theirOutputW = other_Neural.outputWeights;
        mat newInputW = theirInputW;
        mat newOutpurW = theirOutputW;

        for (int i = 0; i < this->numberOfNeurons; ++i)
        {
            for (int j = 0; j < this->inputSize; ++j)
            {
                if (rand() % 1 < .5) {
                    newInputW(i,j) = theirInputW(i,j);
                } 
                else {
                    newInputW(i,j) = this->inputWeights(i,j);
                }
            }
        }
        
        for (int i = 0; i < this->numberOfNeurons; ++i)
        {
            for (int j = 0; j < this->outputSize; ++j)
            {
                if (rand() % 1 < .5) {
                    newOutputW(i,j) = theirOutputW(i,j);
                } 
                else {
                    newOutputW(i,j) = this->outputWeights(i,j);
                }
            }
        }
    }

    // TODO: Genetic sorting (fitness etc.), short-term plasticity
    /**
     *  Calculating the fitness of a given network
     */


    /**
     *  Initializes Short-Term plasticity
     */
    /*
    void STP_init(double omega, double gamma, double U) {
        double this->omega = omega;
        double this->gamma = gamma;
        double this->U = U;
        this->STPOn = true;

        mat this->inputSTP = new mat(this->inputSize, 2);         // matrix containing x and u values for each input synapse
        mat this->outputSTP = new mat(this->numberOfNeurons, 2);  // matrix containing x and u values for each output synapse
        this->inputSTP.fill(.5);
        this->outputSTP.fill(.5);
    }
    */
    


};

int main() {
    Neural_Custom neural;
    neural.initNetwork(2, 2, 2);
    neural.initWeightsRandom();

    mat input;
    input.set_size(5,2);
    input.fill(6.);

    mat output;
    output = neural.forward(input);
    output.print();

    output = neural.costFunction(input);
    output.print();
}
