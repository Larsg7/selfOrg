#include <iostream>

using namespace std;

class player {
    private:
        double fitness;
        int strategy;
        double payoff[4] = {2,-1,0,-0.5};

    public:
    int revealStrat() {
        return strategy;
    }

    void setVariables (double fit, int str) {
        fitness = fit;
        strategy = str;
    }

    double revealFit() {
        return fitness;
    }

    void doPayoff(int number) {
        fitness += payoff[number];
    }

    void playgame ( player& opponent) {
        int myresult;
        int oppresult;
        if (strategy == 1 && opponent.revealStrat() == 1) {
            myresult, oppresult = 2;
        }
        else if (strategy == 2 && opponent.revealStrat() == 2) {
            myresult, oppresult = 3;
        }
        else if (strategy == 1 && opponent.revealStrat() == 2) {
            myresult = 1;
            oppresult = 0;
        }
        else if (strategy == 2 && opponent.revealStrat() == 1) {
            myresult = 0;
            oppresult = 1;
        }
        doPayoff(myresult);
        opponent.doPayoff(oppresult);
    }
};

int main() {

    player A;
    player B;

    A.setVariables(10,1);
    B.setVariables(10,2);

    A.playgame(B);

    cout << "A: " << A.revealFit() << endl;
    cout << "B: " << B.revealFit() << endl;

    return 0;
}