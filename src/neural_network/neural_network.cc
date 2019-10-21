#include "neural_network.hh"

NeuralNetwork::NeuralNetwork(std::initializer_list<int> sizes)
    : _sizes(sizes)
{}

NeuralNetwork::NeuralNetwork(std::initializer_list<int> sizes,
        std::initializer_list<Matrix> layers)
    : _sizes(sizes), _layers(layers)
{}

bool NeuralNetwork::isIndexValid(const int i) const
{
    return i >= 0 && i < _sizes.size();
}

int NeuralNetwork::getLayerSize(const int layer) const
{
    if (!isIndexValid(layer))
        throw "NN: out of bound";
    return _sizes[layer];
}

Matrix NeuralNetwork::getLayer(const int layer) const
{
    if (!isIndexValid(layer))
        throw "NN: out of bound";
    return _layers[layer];
}

void NeuralNetwork::setLayerSize(const int layer, const int size)
{
    if (!isIndexValid(layer))
        throw "NN: out of bound";
    _sizes[layer] = size;
}

void NeuralNetwork::setLayer(const int layer, const Matrix& m)
{
    if (!isIndexValid(layer))
        throw "NN: out of bound";
    _layers[layer] = m;
}

void NeuralNetwork::initSupervisedTraining(const Matrix& inputs)
{
    _layers.reserve(_sizes.size());
    _layers[0] = inputs;
    for (auto i = 1; i < _sizes.size() - 1; i++)
        _layers[i] = Matrix::random(_sizes[i - 1], _sizes[i], 0, 1);
    _layers[_sizes.size() - 1] = Matrix::random(_sizes.size() - 1, inputs.getHeight(),
            0, 1);
}

std::pair<std::vector<Matrix>> NeuralNetwork::forwardPropagation(void)
{
    std::pair<std::vector<Matrix>> computes;
    computes.first.reserve(_layers.size() - 1);
    computes.second.reserve(_layers.size() - 1);
    computes.first[0] = _layers[0] * layers[1];
    computes.second[0] = Matrix::apply(computes.first[0], sigmoid);
    for (auto i = 1; i < computes.first.capacity(); i++)
    {
        computes.first[i] = computes.second[i - 1] * _layers[i + 1];
        computes.second[i] = Matrix::apply(computes.first[i], sigmoid);
    }
    return computes;
}

void NeuralNetwork::backPropagation(std::pair<std::vector<Matrix>> computes)
{
    std::vector<Matrix> costs;
    costs.reserve(_layers.size() - 2);
    Matrix delta = ((output - computes.second[computes.second.capacity() - 1]) * -1)
        * Matrix::apply(computes.first[computes.first.capacity() - 1], sigmoidPrime); 
    costs[costs.capacity() - 1] = computes.second[_layers.size() - 2].transpose()
        * delta;
    for(auto i = costs.capacity() - 2; i > 0; i--)
    {
        delta = delta * _layers[i + 1].transpose()
            * Matrix::apply(comutes.first[i + 1], sigmoidPrime);
        costs[i] = _layers[i - 1].transpose() * delta;
    }
    for (auto i = 0; i < costs.size(); i++)
        _layers[i + 1] -= costs[i] * SCALAR;
}

void NeuralNetwork::supervisedTraining(const Matrix& inputs, const Matrix& outputs)
{

}
