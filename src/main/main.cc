#include "neural_network.hh"

int main(void)
{
    NeuralNetwork nn({2, 4, 1});
    nn.supervisedTraining(
            Matrix(4, 2, {0, 0,
                          0, 1,
                          1, 0,
                          1, 1}),
            Matrix(4, 1, {1,
                          0,
                          0,
                          1}));
    return 0;
}
