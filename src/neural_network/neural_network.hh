#pragma once

#include <pair>
#include <vector>

#include "matrix.hh"

class NeuralNetwork
{
    public:
        NeuralNetwork(std::initializer_list<int> sizes);
        NeuralNetwork(std::initializer_list<int> sizes,
                std::initializer_list<Matrix> layers);
        
        int getLayerSize(const int layer) const;
        Matrix getLayer(const int layer) const;

        void setLayerSize(const int layer, const int size);
        void setLayer(const int layer, const Matrix& m);

        void supervisedTraining(const Matrix& inputs, const Matrix& outputs); 

    private:
        bool isIndexValid(const int i) const;
        void initSupervisedTraining(const Matrix& inputs);
        std::pair<std::vector<Matrix>> forwardPropagation(void);
        void backPropagation(std::pair<std::vector<Matrix>> computes);

        std::vector<int> _sizes;
        std::vector<Matrix> _layers;
};
