// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// Inner.hpp
// This file is part of the Garamon for c2ga.
// Authors: Stephane Breuils and Vincent Nozick
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program

// \file BasisTransformations.hpp
// \author V. Nozick, S. Breuils
// \brief this files generates and load the elements of the transformation matrices into array of Eigen matrices 


#ifndef C2GA_BASISTRANSFORMATIONS_HPP__
#define C2GA_BASISTRANSFORMATIONS_HPP__
#pragma once


#include <Eigen/Sparse>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
#include <sstream>


/*!
 * @namespace c2ga
 */
namespace c2ga{

	/// Decode the string encodedPerGradeMatrixComponents to a vector of T. This vector will contain the components of the transformation matrices
	template<typename T>
	const std::vector<T> decodeStringToVecOfT(std::string encodedPerGradeMatrixComponents) {
	    std::vector<T> resultDecodedGrade;
	    std::istringstream streamStringOverFloat(encodedPerGradeMatrixComponents);
	    std::copy(std::istream_iterator<float>(streamStringOverFloat),
		std::istream_iterator<float>(),
		std::back_inserter(resultDecodedGrade));
	    return resultDecodedGrade;
	}

	/// contains and load the components of the grade 0 direct transformation matrix 
 	template<typename T>
	Eigen::SparseMatrix<T, Eigen::ColMajor>  loadgrade0Matrix() {
		const std::string grade0MatrixComponents = " 0 0 1.000000 ";
		std::vector<T> gradeVectorComponents = decodeStringToVecOfT<T>(grade0MatrixComponents);
		Eigen::SparseMatrix<T, Eigen::ColMajor> perGradeBasisTransformMatrix		 = Eigen::SparseMatrix<T, Eigen::ColMajor>(1,1);
		perGradeBasisTransformMatrix.reserve(1);
		perGradeBasisTransformMatrix.insert((int)gradeVectorComponents[0],(int)gradeVectorComponents[1]) = gradeVectorComponents[2];
		return perGradeBasisTransformMatrix;
	}

	/// contains and load the components of the grade 1 direct transformation matrix 
 	template<typename T>
	Eigen::SparseMatrix<T, Eigen::ColMajor>  loadgrade1Matrix() {
		const std::string grade1MatrixComponents = " 0 0 1.000000 3 0 -1.000000 0 1 1.000000 3 1 1.000000 2 2 1.000000 1 3 1.000000 ";
		std::vector<T> gradeVectorComponents = decodeStringToVecOfT<T>(grade1MatrixComponents);
		Eigen::SparseMatrix<T, Eigen::ColMajor> perGradeBasisTransformMatrix		 = Eigen::SparseMatrix<T, Eigen::ColMajor>(4,4);
		perGradeBasisTransformMatrix.reserve(6);
		for(unsigned int i=0;i<6;++i)
			perGradeBasisTransformMatrix.insert((int)gradeVectorComponents[3*i],(int)gradeVectorComponents[(3*i)+1]) = gradeVectorComponents[(3*i)+2];
		return perGradeBasisTransformMatrix;
	}

	/// contains and load the components of the grade 2 direct transformation matrix 
 	template<typename T>
	Eigen::SparseMatrix<T, Eigen::ColMajor>  loadgrade2Matrix() {
		const std::string grade2MatrixComponents = " 2 0 2.000000 1 1 1.000000 5 1 1.000000 0 2 1.000000 4 2 1.000000 1 3 1.000000 5 3 -1.000000 0 4 1.000000 4 4 -1.000000 3 5 -1.000000 ";
		std::vector<T> gradeVectorComponents = decodeStringToVecOfT<T>(grade2MatrixComponents);
		Eigen::SparseMatrix<T, Eigen::ColMajor> perGradeBasisTransformMatrix		 = Eigen::SparseMatrix<T, Eigen::ColMajor>(6,6);
		perGradeBasisTransformMatrix.reserve(10);
		for(unsigned int i=0;i<10;++i)
			perGradeBasisTransformMatrix.insert((int)gradeVectorComponents[3*i],(int)gradeVectorComponents[(3*i)+1]) = gradeVectorComponents[(3*i)+2];
		return perGradeBasisTransformMatrix;
	}

	/// contains and load the components of the grade 3 direct transformation matrix 
 	template<typename T>
	Eigen::SparseMatrix<T, Eigen::ColMajor>  loadgrade3Matrix() {
		const std::string grade3MatrixComponents = " 2 0 -2.000000 1 1 -2.000000 0 2 -1.000000 3 2 1.000000 0 3 -1.000000 3 3 -1.000000 ";
		std::vector<T> gradeVectorComponents = decodeStringToVecOfT<T>(grade3MatrixComponents);
		Eigen::SparseMatrix<T, Eigen::ColMajor> perGradeBasisTransformMatrix		 = Eigen::SparseMatrix<T, Eigen::ColMajor>(4,4);
		perGradeBasisTransformMatrix.reserve(6);
		for(unsigned int i=0;i<6;++i)
			perGradeBasisTransformMatrix.insert((int)gradeVectorComponents[3*i],(int)gradeVectorComponents[(3*i)+1]) = gradeVectorComponents[(3*i)+2];
		return perGradeBasisTransformMatrix;
	}

	/// contains and load the components of the grade 4 direct transformation matrix 
 	template<typename T>
	Eigen::SparseMatrix<T, Eigen::ColMajor>  loadgrade4Matrix() {
		const std::string grade4MatrixComponents = " 0 0 -2.000000 ";
		std::vector<T> gradeVectorComponents = decodeStringToVecOfT<T>(grade4MatrixComponents);
		Eigen::SparseMatrix<T, Eigen::ColMajor> perGradeBasisTransformMatrix		 = Eigen::SparseMatrix<T, Eigen::ColMajor>(1,1);
		perGradeBasisTransformMatrix.reserve(1);
		perGradeBasisTransformMatrix.insert((int)gradeVectorComponents[0],(int)gradeVectorComponents[1]) = gradeVectorComponents[2];
		return perGradeBasisTransformMatrix;
	}




	/// contains and load the components of the grade 0 inverse transformation matrix 
 	template<typename T>
	Eigen::SparseMatrix<T, Eigen::ColMajor>  loadgrade0InverseMatrix() {
		const std::string grade0MatrixComponents = " 0 0 1.000000 ";
		std::vector<T> gradeVectorComponents = decodeStringToVecOfT<T>(grade0MatrixComponents);
		Eigen::SparseMatrix<T, Eigen::ColMajor> perGradeBasisTransformMatrix		 = Eigen::SparseMatrix<T, Eigen::ColMajor>(1,1);
		perGradeBasisTransformMatrix.reserve(1);
		perGradeBasisTransformMatrix.insert((int)gradeVectorComponents[0],(int)gradeVectorComponents[1]) = gradeVectorComponents[2];
		return perGradeBasisTransformMatrix;
	}

	/// contains and load the components of the grade 1 inverse transformation matrix 
 	template<typename T>
	Eigen::SparseMatrix<T, Eigen::ColMajor>  loadgrade1InverseMatrix() {
		const std::string grade1MatrixComponents = " 0 0 0.500000 1 0 0.500000 3 1 1.000000 2 2 1.000000 0 3 -0.500000 1 3 0.500000 ";
		std::vector<T> gradeVectorComponents = decodeStringToVecOfT<T>(grade1MatrixComponents);
		Eigen::SparseMatrix<T, Eigen::ColMajor> perGradeBasisTransformMatrix		 = Eigen::SparseMatrix<T, Eigen::ColMajor>(4,4);
		perGradeBasisTransformMatrix.reserve(6);
		for(unsigned int i=0;i<6;++i)
			perGradeBasisTransformMatrix.insert((int)gradeVectorComponents[3*i],(int)gradeVectorComponents[(3*i)+1]) = gradeVectorComponents[(3*i)+2];
		return perGradeBasisTransformMatrix;
	}

	/// contains and load the components of the grade 2 inverse transformation matrix 
 	template<typename T>
	Eigen::SparseMatrix<T, Eigen::ColMajor>  loadgrade2InverseMatrix() {
		const std::string grade2MatrixComponents = " 2 0 0.500000 4 0 0.500000 1 1 0.500000 3 1 0.500000 0 2 0.500000 5 3 -1.000000 2 4 0.500000 4 4 -0.500000 1 5 0.500000 3 5 -0.500000 ";
		std::vector<T> gradeVectorComponents = decodeStringToVecOfT<T>(grade2MatrixComponents);
		Eigen::SparseMatrix<T, Eigen::ColMajor> perGradeBasisTransformMatrix		 = Eigen::SparseMatrix<T, Eigen::ColMajor>(6,6);
		perGradeBasisTransformMatrix.reserve(10);
		for(unsigned int i=0;i<10;++i)
			perGradeBasisTransformMatrix.insert((int)gradeVectorComponents[3*i],(int)gradeVectorComponents[(3*i)+1]) = gradeVectorComponents[(3*i)+2];
		return perGradeBasisTransformMatrix;
	}

	/// contains and load the components of the grade 3 inverse transformation matrix 
 	template<typename T>
	Eigen::SparseMatrix<T, Eigen::ColMajor>  loadgrade3InverseMatrix() {
		const std::string grade3MatrixComponents = " 2 0 -0.500000 3 0 -0.500000 1 1 -0.500000 0 2 -0.500000 2 3 0.500000 3 3 -0.500000 ";
		std::vector<T> gradeVectorComponents = decodeStringToVecOfT<T>(grade3MatrixComponents);
		Eigen::SparseMatrix<T, Eigen::ColMajor> perGradeBasisTransformMatrix		 = Eigen::SparseMatrix<T, Eigen::ColMajor>(4,4);
		perGradeBasisTransformMatrix.reserve(6);
		for(unsigned int i=0;i<6;++i)
			perGradeBasisTransformMatrix.insert((int)gradeVectorComponents[3*i],(int)gradeVectorComponents[(3*i)+1]) = gradeVectorComponents[(3*i)+2];
		return perGradeBasisTransformMatrix;
	}

	/// contains and load the components of the grade 4 inverse transformation matrix 
 	template<typename T>
	Eigen::SparseMatrix<T, Eigen::ColMajor>  loadgrade4InverseMatrix() {
		const std::string grade4MatrixComponents = " 0 0 -0.500000 ";
		std::vector<T> gradeVectorComponents = decodeStringToVecOfT<T>(grade4MatrixComponents);
		Eigen::SparseMatrix<T, Eigen::ColMajor> perGradeBasisTransformMatrix		 = Eigen::SparseMatrix<T, Eigen::ColMajor>(1,1);
		perGradeBasisTransformMatrix.reserve(1);
		perGradeBasisTransformMatrix.insert((int)gradeVectorComponents[0],(int)gradeVectorComponents[1]) = gradeVectorComponents[2];
		return perGradeBasisTransformMatrix;
	}




	/// initialize all the direct transformation matrices using array of eigen sparse matrices
	template<typename T>
	const std::array<Eigen::SparseMatrix<T, Eigen::ColMajor>,5> loadMatrices() {
		std::array<Eigen::SparseMatrix<T, Eigen::ColMajor>,5>  transformationMatrices;
		transformationMatrices[0] = loadgrade0Matrix<T>();
		transformationMatrices[1] = loadgrade1Matrix<T>();
		transformationMatrices[2] = loadgrade2Matrix<T>();
		transformationMatrices[3] = loadgrade3Matrix<T>();
		transformationMatrices[4] = loadgrade4Matrix<T>();
		return transformationMatrices;
	}


	/// initialize all the inverse transformation matrices using array of eigen sparse matrices
	template<typename T>
	const std::array<Eigen::SparseMatrix<T, Eigen::ColMajor>,5> loadMatricesInverse() {
		std::array<Eigen::SparseMatrix<T, Eigen::ColMajor>,5>  transformationMatrices;
		transformationMatrices[0] = loadgrade0InverseMatrix<T>();
		transformationMatrices[1] = loadgrade1InverseMatrix<T>();
		transformationMatrices[2] = loadgrade2InverseMatrix<T>();
		transformationMatrices[3] = loadgrade3InverseMatrix<T>();
		transformationMatrices[4] = loadgrade4InverseMatrix<T>();
		return transformationMatrices;
	}


}/// End of Namespace

#endif // C2GA_BASISTRANSFORMATIONS_HPP__
