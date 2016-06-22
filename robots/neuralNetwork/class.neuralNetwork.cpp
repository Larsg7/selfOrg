#include <iostream>
#include <math.h>
//#include <random>
#include <stdlib.h>
//#include <cstdlib>
#include <iostream>
#include <fstream>
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

    double randomWeightsRange = 2;
    double chanceOfZero = 0.2;

    double fitness;

    double chanceOfMutate = 0.01;
    double maxMutate = 2;

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
        //inputVec = normalise(inputVec, 2, 1);                     
        this->inputVec = inputVec;
        mat nInput;
        nInput = inputVec * this->inputWeights;                     // adding all inputs for every neuron together - nInput has dim(input.rows, numberOfNeurons)

        for (int i = 0; i < this->inputVec.n_rows; ++i) {           // applying sigmoid function to every neuron
            for (int j = 0; j < this->inputSize; ++j) {
                this->sigmoid(nInput(i,j));
            }
        }

        this->outputVec = nInput * this->outputWeights;             // adding all inputs for every output together - outputVec has dim(inputRows, outputSize)

        for (int i = 0; i < this->inputVec.n_rows; ++i) {           // applying sigmoid function to every output
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
     * Initialize Weights-Matrices with random values between -randomWeightsRange and randomWeightsRange
     * or with 0 (chanceOfZero) and effectively not connecting neurons
     */
    void initWeightsRandom() {
        std::srand(rand());        

        for (int i = 0; i < this->inputWeights.n_rows; ++i) 
            for (int j = 0; j < this->inputWeights.n_cols; ++j) 
                this->inputWeights(i,j) = ((double)rand() / INT_MAX) < 1 - this->chanceOfZero ? (double)rand() / (INT_MAX / 2*this->randomWeightsRange) -this->randomWeightsRange : 0;    

        for (int i = 0; i < this->outputWeights.n_rows; ++i) 
            for (int j = 0; j < this->outputWeights.n_cols; ++j) 
                this->outputWeights(i,j) = ((double)rand() / INT_MAX) < 1 - this->chanceOfZero ? (double)rand() / (INT_MAX / 2*this->randomWeightsRange) -this->randomWeightsRange : 0;
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
 * This class contains all custom functions for training and breeding the neural network
 *
 * @author: Lars Gröber
 */
class Neural_Custom: public Neural_Network {

protected:
    

public:
    /**
     * Set and retrive the fitness-value 
     */
    void setFitness(double fitness) {
        this->fitness = fitness;
    }

    double getFitness() {
        return this->fitness;
    }

    /**
     * Breed a new network with another network and initialize it (has the same topology)
     *
     * @param: the other network to breed with
     * @return: the newly created network
     */
    Neural_Custom* breed(Neural_Custom* other_Neural) {

        mat theirInputW = other_Neural->inputWeights;
        mat theirOutputW = other_Neural->outputWeights;
        
        mat newInputW = theirInputW;
        mat newOutputW = theirOutputW;

        for (int i = 0; i < this->inputWeights.n_rows; ++i) 
            for (int j = 0; j < this->inputWeights.n_cols; ++j) 
                newInputW(i,j) = rand() < INT_MAX / 2 ? theirInputW(i,j) : this->inputWeights(i,j);     // with a chance of 1/2 use the own weight for the new network 
        

        for (int i = 0; i < this->outputWeights.n_rows; ++i) 
            for (int j = 0; j < this->outputWeights.n_cols; ++j)
                newOutputW(i,j) = rand() < INT_MAX / 2 ? theirOutputW(i,j) : this->outputWeights(i,j);

        Neural_Custom* newNetwork = new Neural_Custom;
        newNetwork->initNetwork(this->inputSize, this->outputSize, this->numberOfNeurons);  
        newNetwork->setWeights(newInputW, newOutputW);
        newNetwork->mutate();   // important part: mutate the weights

        return newNetwork;
    }

    /**
     * Function to mutate the weights randomly
     */
    void mutate() {

        // with a chance of chanceOfMutate change one weight by something between 1-maxMutate and 1+maxMutate
        for (int i = 0; i < this->inputWeights.n_rows; ++i) 
            for (int j = 0; j < this->inputWeights.n_cols; ++j)
                this->inputWeights(i,j) *= (double)rand()/INT_MAX < this->chanceOfMutate ? 1+fmod((double)rand()/(INT_MAX/2)-1, this->maxMutate) : 1;   
                
        for (int i = 0; i < this->outputWeights.n_rows; ++i) 
            for (int j = 0; j < this->outputWeights.n_cols; ++j)
                this->outputWeights(i,j) *= (double)rand()/INT_MAX < this->chanceOfMutate ? 1+fmod((double)rand()/(INT_MAX/2)-1, this->maxMutate) : 1;
    }

};

///// end of class /////




// fitness function for the given problem
double fitness(double a, double b, double output) {
    double c = abs((a + b) - output);
    return exp(-c);
}

// determine largest Value and corresponding index
void largestValue(double v[], double &max, int &maxIndex, int size) {
    for (int i = 0; i < size; ++i)
    {
        if (max < v[i])
        {
            max = v[i];
            maxIndex = i;
        }
    }
}


int main() {
    // writing data in file "data"
    std::ofstream ofFile;
    ofFile.open("data");

    int inputSize = 2;
    int outputSize = 1;
    int numberOfNeurons = 5;

    int numberOfNetworks = 50;
    int numberOfGenerations = 500; 

    //test();

    std::srand(time(NULL));

    std::vector<Neural_Custom*> listNetworks;
    std::vector<Neural_Custom*> listNextNetworks;

    // Initialize random population
    for (int i = 0; i < numberOfNetworks; ++i)
    {
        listNetworks.push_back(new Neural_Custom);
        listNetworks[i]->initNetwork(inputSize, outputSize, numberOfNeurons);
        listNetworks[i]->initWeightsRandom();
    }

    
    // run genetic algorithm

    int generation = 1;

    while (generation <= numberOfGenerations) {

        double fitnessArr[listNetworks.size()];
        double totalFitness = 0.;

        // set nextNetworks back to zero
        listNextNetworks.erase(listNextNetworks.begin(), listNextNetworks.end());

        // for testing purpose input is set to a constant value
        mat input = mat(1,2);
            

        double inputArr[] =  {0.1, 0.1, 0.3, 0.5, 0.37, 0.2, 0.09};
        double inputArr2[] = {0.5, 0.8, 0.0, 0.1, 0.41, 0.3, 0.9};

        // Determine fitness of population
        for (int i = 0; i < listNetworks.size(); ++i) {
            fitnessArr[i] = 0;
            for (int j = 0; j < 7; ++j)
            {
                input(0,0) = inputArr[j];
                input(0,1) = inputArr2[j];

                mat output = listNetworks[i]->forward(input);
                //output.print();
                
                fitnessArr[i] += (fitness((double)input(0,0), (double)input(0,1), (double)output(0,0)));
                //output.print();
                
            }         

            //std::cout << "Fitness of Network " << i << " in generation " << generation << ": " << fitnessArr[i] << std::endl;

        }    


        std::cout << "Generation " << generation << " complete!" << std::endl;

        
        for (int j = 0; j < listNetworks.size(); ++j) {
            totalFitness += fitnessArr[j];
        }

        double highestFitness = 0;
        int highestFitnessIndex = 0;
        largestValue(fitnessArr, highestFitness, highestFitnessIndex, listNetworks.size());

        // print out some information
        std::cout << "highest Fitness: " << highestFitness << std::endl;
        std::cout << "best output: " << listNetworks[highestFitnessIndex]->forward(input) << std::endl;
        listNetworks[highestFitnessIndex]->inputWeights.print();   
        listNetworks[highestFitnessIndex]->outputWeights.print();     

        std::cout << "totalFitness: " << totalFitness << std::endl << std::endl;

        ofFile << generation << "   " << highestFitness << "   " << totalFitness << std::endl;
        
        // Breed two networks to new one using fitness as probability
        for (int i = 0; i < numberOfNetworks; ++i) {

            double randn1 = (double)rand() / INT_MAX;
            double randn2 = (double)rand() / INT_MAX;

            double a = 0;
            double b = 0;
            int first = 0;      // first network to breed with
            int second = 0;     // second network to breed with

            for (int j = 0; j < numberOfNetworks; j++)
            {
                a += fitnessArr[j] / totalFitness;

                //std::cout << a << std::endl;

                first = (a > randn1 && first == 0) ? j : first;
                second = (a > randn2 && second == 0) ? j : second;

                if (first == second && first != 0 && second != 0)
                    continue;
            }
            
            //std::cout << first << ", " << second << std::endl;

            listNextNetworks.push_back(listNetworks[first]->breed(listNetworks[second]));
        }

        listNetworks = listNextNetworks;

        generation++;
        // end of generation
    }

    ofFile.close();

    return 1;
}









/*

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

*/