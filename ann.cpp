#include <iostream>
#include <random>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

default_random_engine generator;
normal_distribution<double> distribution(0,1.0);

double sigmoid(const double d)
{
    return 1/(1 + exp(-d));
}

template<int inputSize, int outputSize, int hiddenSize>
struct Ann
{

    template <typename T>
    auto forward(const T& input)
    {
        auto z = input * w1;
        auto z2 = sigmoid(z);
        auto z3 = z2 * w2;
        return sigmoid(z3);
    }

    Matrix<double, hiddenSize, inputSize> x;
    Matrix<double, hiddenSize, outputSize> y;
    Matrix<double, inputSize,  hiddenSize> w1; 
    Matrix<double, hiddenSize, outputSize> w2; 

};
int main()
{
    constexpr int inputSize = 2;
    constexpr int outputSize = 1;
    constexpr int hiddenSize = 3;


    MatrixXd X(hiddenSize, inputSize);
    X << 2, 9,
         1, 5,
         3, 6;
    for (unsigned i = 0; i < inputSize; ++i)
        X.col(i) = X.col(i)/X.col(i).maxCoeff();

    MatrixXd y(outputSize, hiddenSize);
    y << 92, 86, 89;
    y = y/100.; 

    std::cout << X << std::endl;
    std::cout << y << std::endl; 

    Ann<inputSize,outputSize,hiddenSize> ann;

    std::cout << "Predicted : " << ann.forward(X) << std::endl;
    std::cout << "Actual : " << y << std::endl;

    return 0;
}

