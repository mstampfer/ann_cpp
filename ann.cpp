#include <iostream>
#include <random>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

default_random_engine generator;
normal_distribution<double> distribution(0.0,1.0);


template<int inputSize, int outputSize, int hiddenSize>
struct Ann
{
    template <typename Input, typename Output>
    Ann(Input X, Output y) : X(X), y(y)
    {
        w1 = Matrix<double, inputSize, hiddenSize>::Random();
        w2 = Matrix<double, hiddenSize, outputSize>::Random();
    }

    template <typename T>
    auto sigmoid(const T& z)
    {
        auto a = 1./(1. + (-z).array().exp());
        return a.matrix();
    }

    template <typename T>
    auto dsigmoid_dz(const T& z)
    {   
        auto val = (1-sigmoid(z).array()).matrix();
        return(sigmoid(z).transpose()*val);
    }            


    auto forward()
    {
        auto z = X * w1;
        z2 = sigmoid(z);
        auto z3 = z * w2;
        return sigmoid(z3);
    }

    template <typename Output>
    auto backward(const Output& y_hat)
    {
       auto error = y - y_hat;
       auto delta = error*dsigmoid_dz(y_hat); 

       auto error2 = delta*w2.transpose();
       auto delta2 = error2*dsigmoid_dz(z2);

       w1 += X.transpose()*delta2;
       w2 += z2.transpose()*delta;
    }

    void train()
    {
       y_hat = forward();
       backward(y_hat);
    }

    Matrix<double, hiddenSize, inputSize> X;
    Matrix<double, hiddenSize, outputSize> y;
    Matrix<double, hiddenSize, outputSize> y_hat;
    Matrix<double, hiddenSize, hiddenSize> z2;
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

    MatrixXd y(hiddenSize, outputSize);
    y << 92, 86, 89;
    y = y/100.; 

    std::cout << X << std::endl;
    std::cout << y << std::endl; 

    Ann<inputSize,outputSize,hiddenSize> ann(X, y);

    for (int i=0; i<1000; ++i)
    {
        std::cout << "Predicted : " << ann.forward().transpose() << std::endl;
        std::cout << "Actual : " << y.transpose() << std::endl;
        ann.train();
    }
    return 0;
}

