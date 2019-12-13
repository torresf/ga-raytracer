// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// Constants.hpp
// This file is part of the Garamon for c2ga.
// Authors: Stephane Breuils and Vincent Nozick
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program

/// \file Constants.hpp
/// \author Stephane Breuils, Vincent Nozick
/// \brief Constant values and data related to the specified geometric algebra (c2ga)


// Doxygen
/// \version 0.1
/// \mainpage
/// \tableofcontents
/// \section instroduction_sec What for?
/// Garamon is a C++ library to represent an manipulate the geometric algebra objects.
/// \section install_bigsec How to install
/// \subsection dependencies_sec Dependecies
/// \li cmake (at least version 3.10)
/// \li Eigen (at least version 3.3.4)
/// \li Doxygen (if you want the documentation)
/// \subsection install_sec Install with cmake (Linux / MacOs)
/// \li go to garamon dir
/// \li mkdir build
/// \li cd build
/// \li cmake ..
/// \li make
/// \li (optional) sudo make install
/// \li (optional for documentation) make html
/// \li The documentation is located in [path to build]/doc/doc-doxygen/html/index.html


#ifndef C2GA_CONSTANTS_HPP__
#define C2GA_CONSTANTS_HPP__
#pragma once


#include <array>
#include <vector>
#include <utility>
#include <string>
#include <Eigen/Sparse>

#include "c2ga/Utility.hpp"
#include "c2ga/BasisTransformations.hpp"
#include "c2ga/DualCoefficients.hpp"


/*!
 * @namespace c2ga
 */
namespace c2ga{

    constexpr unsigned int algebraDimension = 4; /*!< dimension of the algebra (number of  basis vectors of grade 1) */

    constexpr unsigned int perGradeStartingIndex[5] = {0,1,5,11,15};  /*!< array specifying the index of each first element of grade k in the full multivector */

    constexpr unsigned int binomialArray[5] = {1,4,6,4,1};  /*!< array of the (dimension + 1) first binomial coefficients */

    constexpr unsigned int xorIndexToGrade[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4}; /*!< given a Xor index in a multivector, this array indicates the corresponding grade*/ 

    constexpr unsigned int xorIndexToHomogeneousIndex[] = {0,0,1,0,2,1,3,0,3,2,4,1,5,2,3,0}; /*!< given a Xor index in a multivector, this array indicates the corresponding index in the whole homogeneous vector*/

    const std::array<std::vector<unsigned int>, 5> dualPermutations = {{ { 0}, {{ 0,2,1,3}}, {{ 1,0,3,2,5,4}}, {{ 0,2,1,3}}, {0} }}; /*!< array referring to some permutations required to compute the dual. */

    const std::array<Eigen::Matrix<double, Eigen::Dynamic,1>, 5> dualCoefficients = loadFastDualArray<double>(); /*!< array containing some basis change coefficients required to compute the dual */
    
    template<typename T>
    std::array<T, 16> recursiveDualCoefficients = {{ 1.000000,1.000000,1.000000,-1.000000,-1.000000,1.000000,1.000000,-1.000000,-1.000000,-1.000000,1.000000,1.000000,-1.000000,-1.000000,1.000000,1.000000}}; /*!< array containing the coefficients needed to compute the recursive product like (primal^dual) */

    constexpr double pseudoScalarInverse = -1.000000; /*!< compute the inverse of the pseudo scalar */

    const int signReversePerGrade[5] = {1,1,-1,-1,1}; /*!< array of signs to avoid the computation of (-1)^k*(k-1)/2 during the reverse operation */

    const std::vector<std::string> basisVectors = {"0", "1", "2", "i"}; /*!< name of the basis vectors (of grade 1) */

    const std::string metric =
"\
	e0	e1	e2	ei	\n\
e0	0	0	0	-1	\n\
e1	0	1	0	0	\n\
e2	0	0	1	0	\n\
ei	-1	0	0	0	\n\
"; /*!< metric / quadratic form of the algebra (inner product between basis vectors) */


    template<class T>
    const T zero = 0;

    const unsigned int scalar = 0;
    const unsigned int E0 = 1;
    const unsigned int E1 = 2;
    const unsigned int E2 = 4;
    const unsigned int Ei = 8;
    const unsigned int E01 = 3;
    const unsigned int E02 = 5;
    const unsigned int E0i = 9;
    const unsigned int E12 = 6;
    const unsigned int E1i = 10;
    const unsigned int E2i = 12;
    const unsigned int E012 = 7;
    const unsigned int E01i = 11;
    const unsigned int E02i = 13;
    const unsigned int E12i = 14;
    const unsigned int E012i = 15;
    /*!< defines the constants for the cga */

    template<typename T>
    const std::array<Eigen::SparseMatrix<T, Eigen::ColMajor>,5> transformationMatrices = loadMatrices<T>(); /*!< set transformation matrices to transform a k-vector from the orhogonal basis to the original basis */
    template<typename T>
    const std::array<Eigen::SparseMatrix<T, Eigen::ColMajor>,5> transformationMatricesInverse = loadMatricesInverse<T>(); /*!< set transformation matrices to transform a k-vector from the original basis to the orhogonal basis */


    template<typename T>
    Eigen::Matrix<T, Eigen::Dynamic, 1> diagonalMetric = []()->Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>{Eigen::Matrix<T, Eigen::Dynamic, 1> tmp(4);tmp<<2.000000,-2.000000,1.000000,1.000000; return tmp;}();   /*!< defines the diagonal metric (stored as a vector) */


}  // namespace


#endif // C2GA_CONSTANTS_HPP__
