#pragma once

#undef minor

#include <vector>

class Matrix {
    public:
        Matrix(const int height, const int width);
        Matrix(const int height, const int width, std::initializer_list<float> list);

        static Matrix identity(const int size);
        static Matrix random(const int height, const int width, const float min,
               const float max);
        static Matrix apply(const Matrix &m, float (*fun)(const float));

        inline int getHeight(void) const { return _height; }
        inline int getWidth(void)  const { return _width; }
        float getValue(const int y, const int x) const;

        inline void setHeight(const int height) { _height = height; }
        inline void setWidth(const int width) { _width = width; }
        void setValue(const int y, const int x, const float value);

        Matrix transpose(void);
        Matrix submatrix(const int row, const int column);
        float determinant(void);
        float minor(const int row, const int column);
        float cofactor(const int row, const int column);
        Matrix invert(void);
        float flatten(void);

        bool operator==(const Matrix& m) const;
        bool operator!=(const Matrix& m) const;
        Matrix operator+(const Matrix& m);
        Matrix operator-(const Matrix& m);
        Matrix operator*(const Matrix& m);
        Matrix operator*(const float v);

    private:
        bool isCoordValid(const int y, const int x) const;
        int _height;
        int _width;
        std::vector<float> _matrix;
};
