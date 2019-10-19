#ifdef _TESTS

#include <cmath>

#include "catch.hpp"
#include "constants.hh"
#include "matrix.hh"
#include "op_overloading.hh"

TEST_CASE("MATRIX: construct matrix", "[multi-file:matrix]") {
    Matrix m(4, 4, {   1,    2,    3,    4,
                     5.5,  6.5,  7.5,  8.5,
                       9,   19,   11,   12,
                    13.5, 14.5, 15.5, 16.5});
    Matrix m1(2, 2, {-3,  5,
                      1, -2});
    Matrix m2(3, 3, {-3,  5,  0,
                      1, -2, -7,
                      0,  1,  1});
    REQUIRE((isEqual(m.getValue(0, 0), 1)
            && isEqual(m.getValue(0, 3), 4)
            && isEqual(m.getValue(1, 0), 5.5)
            && isEqual(m.getValue(1, 2), 7.5)
            && isEqual(m.getValue(2, 2), 11)
            && isEqual(m.getValue(3, 0), 13.5)
            && isEqual(m.getValue(3, 2), 15.5)));
    REQUIRE((isEqual(m1.getValue(0, 0), -3)
            && isEqual(m1.getValue(0, 1), 5)
            && isEqual(m1.getValue(1, 0), 1)
            && isEqual(m1.getValue(1, 1), -2)));
    REQUIRE((isEqual(m2.getValue(0, 0), -3)
            && isEqual(m2.getValue(1, 1), -2)
            && isEqual(m2.getValue(2, 2), 1)));
}

TEST_CASE("MATRIX: matrix compare", "[multi-file:matrix]")
{
    Matrix m(4, 4, {1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 8, 7, 6,
                    5, 4, 3, 2});
    Matrix m1(4, 4, {1, 2, 3, 4,
                     5, 6, 7, 8,
                     9, 8, 7, 6,
                     5, 4, 3, 2});
    Matrix m2(4, 4, {2, 3, 4, 5,
                     6, 7, 8, 9,
                     8, 7, 6, 5,
                     4, 3, 2, 1});
    REQUIRE(m == m1);
    REQUIRE(m != m2);
}

TEST_CASE("MATRIX: multiplying two matrix", "[multi-file:matrix]")
{
    Matrix m(4, 4, {1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 8, 7, 6,
                    5, 4, 3, 2});
    Matrix m1(4, 4, {-2, 1, 2,  3,
                      3, 2, 1, -1,
                      4, 3, 6,  5,
                      1, 2, 7,  8});
    Matrix res(4, 4, {20, 22,  50,  48,
                      44, 54, 114, 108,
                      40, 58, 110, 102,
                      16, 26,  46,  42});
    REQUIRE((m * m1) == res);
}

TEST_CASE("MATRIX: multiplying a matrix by the identity matrix", "[multi-file:matrix]")
{
    Matrix m(4, 4, {0, 1,  2,  4,
                    1, 2,  4,  8,
                    2, 4,  8, 16,
                    4, 8, 16, 32});
    REQUIRE((m * Matrix::identity(4)) == m);
}

TEST_CASE("MATRIX: transposing a matrix", "[multi-file:matrix]")
{
    Matrix m(4, 4, {0, 9, 3, 0,
                    9, 8, 0, 8,
                    1, 8, 5, 3,
                    0, 0, 5, 8});
    Matrix res(4, 4, {0, 9, 1, 0,
                      9, 8, 8, 0,
                      3, 0, 5, 5,
                      0, 8, 3, 8});
    REQUIRE(m.transpose() == res);
}

TEST_CASE("MATRIX: transposing the identity matrix", "[multi-file:matrix]")
{
    REQUIRE(Matrix::identity(4).transpose() == Matrix::identity(4));
}

TEST_CASE("MATRIX: Calculating the determinant of a 2x2 matrix", "[multi-file:matrix]")
{
    Matrix m(2, 2, { 1, 5,
                    -3, 2});
    REQUIRE(isEqual(m.determinant(), 17));
}

TEST_CASE("MATRIX: submatrix of a 3x3 matrix", "[multi-file:matrix]")
{
    Matrix m(3, 3, { 1, 5,  0,
                    -3, 2,  7,
                     0, 6, -3});
    Matrix res(2, 2, {-3, 2,
                       0, 6});
    REQUIRE(m.submatrix(0, 2) == res);
}

TEST_CASE("MATRIX: submatrix of a 4x4 matrix", "[multi-file:matrix]")
{
    Matrix m(4, 4, {-6, 1,  1, 6,
                    -8, 5,  8, 6,
                    -1, 0,  8, 2,
                    -7, 1, -1, 1});
    Matrix res(3, 3, {-6,  1, 6,
                      -8,  8, 6,
                      -7, -1, 1});
    REQUIRE(m.submatrix(2, 1) == res);
}

TEST_CASE("MATRIX: Calculating a minor of a 3x3 matrix", "[multi-file:matrix]")
{
    Matrix m(3, 3, {3,  5,  0,
                    2, -1, -7,
                    6, -1,  5});
    Matrix subm = m.submatrix(1, 0);
    REQUIRE(isEqual(subm.determinant(), m.minor(1, 0)));
}

TEST_CASE("MATRIX: Calculating a cofactor of a 3x3 matrix", "[multi-file:matrix]")
{
    Matrix m(3, 3, {3,  5,  0,
                    2, -1, -7,
                    6, -1,  5});
    REQUIRE(isEqual(m.cofactor(0, 0), m.minor(0, 0)));
    REQUIRE(isEqual(m.cofactor(1, 0), -m.minor(1,0)));
}

TEST_CASE("MATRIX: Calculating the determinant of a 3x3 matrix", "[multi-file:matrix]")
{
    Matrix m(3, 3, { 1, 2,  6,
                    -5, 8, -4,
                     2, 6,  4});
    REQUIRE(isEqual(m.cofactor(0, 0), 56));
    REQUIRE(isEqual(m.cofactor(0, 1), 12));
    REQUIRE(isEqual(m.cofactor(0, 2), -46));
    REQUIRE(isEqual(m.determinant(), -196));
}

TEST_CASE("MATRIX: Calculating the determinant of a 4x4 matrix", "[multi-file:matrix]")
{
    Matrix m(4, 4, {-2, -8,  3,  5,
                    -3,  1,  7,  3,
                     1,  2, -9,  6,
                     -6, 7,  7, -9});
    REQUIRE(isEqual(m.cofactor(0, 0), 690));
    REQUIRE(isEqual(m.cofactor(0, 1), 447));
    REQUIRE(isEqual(m.cofactor(0, 2), 210));
    REQUIRE(isEqual(m.cofactor(0, 3), 51));
    REQUIRE(isEqual(m.determinant(), -4071));
}

TEST_CASE("MATRIX: Testing invertibility of matrix", "[multi-file:matrix]")
{
    Matrix invertible(4, 4, {6,  4, 4,  4,
                             5,  5, 7,  6,
                             4, -9, 3, -7,
                             9,  1, 7, -6});
    Matrix noninvertible(4, 4, {-4,  2, -2, -3,
                                 9,  6,  2,  6,
                                 0, -5,  1, -5,
                                 0,  0,  0,  0});

    REQUIRE_NOTHROW(invertible.invert());
    REQUIRE_THROWS(noninvertible.invert());
}

TEST_CASE("MATRIX: Inverse of a matrix", "multi-file:matrix]")
{
    Matrix m(4, 4, {-5,  2,  6, -8,
                     1, -5,  1,  8,
                     7,  7, -6, -7,
                     1, -3,  7,  4});
    Matrix res(4, 4, { 0.21800,  0.45110,  0.24060, -0.04510,
                      -0.80820, -1.45670, -0.44360,  0.52060,
                      -0.07890, -0.22360, -0.05260,  0.19730,
                      -0.52250, -0.81390, -0.30070,  0.30630});
    Matrix invm = m.invert();
    
    Matrix m1(4, 4, { 8, -5,  9,  2,
                      7,  5,  6,  1,
                     -6,  0,  9,  6,
                     -3,  0, -9, -4});
    Matrix res1(4, 4, {-0.15380, -0.15380, -0.28200, -0.53840,
                       -0.07690,  0.12300,  0.02560,  0.03070,
                        0.35890,  0.35890,  0.43590,  0.92300,
                       -0.69230, -0.69230, -0.76920, -1.92300});
    Matrix m2(4, 4, { 9,  3,  0,  9,
                     -5, -2, -6, -3,
                     -4,  9,  6,  4,
                     -7,  6,  6,  2});
    Matrix res2(4, 4, {-0.04070, -0.07770,  0.14440, -0.22220,
                       -0.07770,  0.03330,  0.36660, -0.33330,
                       -0.02900, -0.14630, -0.10920,  0.12960,
                        0.17770,  0.06660, -0.26660,  0.33330});
    REQUIRE(isEqual(m.determinant(), 532));
    REQUIRE(isEqual(m.cofactor(2, 3), -160));
    REQUIRE(isEqual(m.cofactor(3, 2), 105));
    REQUIRE(invm == res);
    REQUIRE(m1.invert() == res1);
    REQUIRE(m2.invert() == res2);
}

TEST_CASE("MATRIX: Mutliplying a product by its inverse", "[multi-file:matrix]")
{
    Matrix a(4, 4, { 3, -9,  7,  3,
                     3, -8,  2, -9,
                    -4,  4,  4,  1,
                    -6,  5, -1,  1});
    Matrix b(4, 4, {8,  2, 2, 2,
                    3, -1, 7, 0,
                    7,  0, 5, 4,
                    6, -2, 0, 5});
    Matrix c = a * b;
    REQUIRE(c * b.invert() == a);
}

#endif
