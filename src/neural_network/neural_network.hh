#pragma once

#include <utility>
#include <vector>

#include "matrix.hh"

class NeuralNetwork
{
    public:
        NeuralNetwork(std::initializer_list<int> sizes);
        NeuralNetwork(std::initializer_list<int> sizes,
                std::initializer_list<Matrix> layers);
        
        int getLayerSize(const size_t layer) const;
        Matrix getLayer(const size_t layer) const;

        void setLayerSize(const size_t layer, const size_t size);
        void setLayer(const size_t layer, const Matrix& m);

        void supervisedTraining(const Matrix& inputs, const Matrix& outputs); 

    private:
        bool isIndexValid(const size_t i) const;
        void initSupervisedTraining(const Matrix& inputs);
        std::pair<std::vector<Matrix>, std::vector<Matrix>> forwardPropagation(void);
        float backPropagation(std::pair<std::vector<Matrix>, std::vector<Matrix>> computes, Matrix outputs);

        std::vector<int> _sizes;
        std::vector<Matrix> _layers;
};
