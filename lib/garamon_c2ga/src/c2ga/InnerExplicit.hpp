// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// InnerExplicit.hpp
// This file is part of the Garamon for c2ga.
// Authors: Stephane Breuils and Vincent Nozick
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program

/// \file InnerExplicit.hpp
/// \author Stephane Breuils, Vincent Nozick
/// \brief Explicit precomputed per grades inner products of c2ga.

#ifndef C2GA_INNER_PRODUCT_EXPLICIT_HPP__
#define C2GA_INNER_PRODUCT_EXPLICIT_HPP__
#pragma once

#include <Eigen/Core>

#include "c2ga/Mvec.hpp"
#include "c2ga/Inner.hpp"
#include "c2ga/Constants.hpp"


/*!
 * @namespace c2ga
 */
namespace c2ga {
    template<typename T> class Mvec;

    /// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 0) and mv2 (grade 0). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 0 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 0 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 0
	template<typename T>
	void inner_0_0(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(0);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 0) and mv2 (grade 1). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 0 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 1 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 1
	template<typename T>
	void inner_0_1(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1.coeff(0)*mv2;
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 0) and mv2 (grade 2). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 0 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 2 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 2
	template<typename T>
	void inner_0_2(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1.coeff(0)*mv2;
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 0) and mv2 (grade 3). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 0 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 3 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 3
	template<typename T>
	void inner_0_3(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1.coeff(0)*mv2;
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 0) and mv2 (grade 4). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 0 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 4 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 4
	template<typename T>
	void inner_0_4(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1.coeff(0)*mv2;
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 1) and mv2 (grade 0). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 1 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 0 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 1
	template<typename T>
	void inner_1_0(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1*mv2.coeff(0);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 1) and mv2 (grade 1). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 1 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 1 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 0
	template<typename T>
	void inner_1_1(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) += -mv1.coeff(0)*mv2.coeff(3) + mv1.coeff(1)*mv2.coeff(1) + mv1.coeff(2)*mv2.coeff(2) - mv1.coeff(3)*mv2.coeff(0);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 1) and mv2 (grade 2). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 1 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 2 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 1
	template<typename T>
	void inner_1_2(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(2) - mv1.coeff(1)*mv2.coeff(0) - mv1.coeff(2)*mv2.coeff(1);
		mv3.coeffRef(1) +=  mv1.coeff(0)*mv2.coeff(4) - mv1.coeff(2)*mv2.coeff(3) - mv1.coeff(3)*mv2.coeff(0);
		mv3.coeffRef(2) +=  mv1.coeff(0)*mv2.coeff(5) + mv1.coeff(1)*mv2.coeff(3) - mv1.coeff(3)*mv2.coeff(1);
		mv3.coeffRef(3) +=  mv1.coeff(1)*mv2.coeff(4) + mv1.coeff(2)*mv2.coeff(5) - mv1.coeff(3)*mv2.coeff(2);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 1) and mv2 (grade 3). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 1 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 3 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 2
	template<typename T>
	void inner_1_3(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) += -mv1.coeff(0)*mv2.coeff(1) + mv1.coeff(2)*mv2.coeff(0);
		mv3.coeffRef(1) += -mv1.coeff(0)*mv2.coeff(2) - mv1.coeff(1)*mv2.coeff(0);
		mv3.coeffRef(2) += -mv1.coeff(1)*mv2.coeff(1) - mv1.coeff(2)*mv2.coeff(2);
		mv3.coeffRef(3) += -mv1.coeff(0)*mv2.coeff(3) - mv1.coeff(3)*mv2.coeff(0);
		mv3.coeffRef(4) += -mv1.coeff(2)*mv2.coeff(3) - mv1.coeff(3)*mv2.coeff(1);
		mv3.coeffRef(5) +=  mv1.coeff(1)*mv2.coeff(3) - mv1.coeff(3)*mv2.coeff(2);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 1) and mv2 (grade 4). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 1 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 4 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 3
	template<typename T>
	void inner_1_4(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(0);
		mv3.coeffRef(1) +=  mv1.coeff(2)*mv2.coeff(0);
		mv3.coeffRef(2) += -mv1.coeff(1)*mv2.coeff(0);
		mv3.coeffRef(3) += -mv1.coeff(3)*mv2.coeff(0);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 2) and mv2 (grade 0). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 2 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 0 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 2
	template<typename T>
	void inner_2_0(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1*mv2.coeff(0);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 2) and mv2 (grade 1). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 2 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 1 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 1
	template<typename T>
	void inner_2_1(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(1) + mv1.coeff(1)*mv2.coeff(2) - mv1.coeff(2)*mv2.coeff(0);
		mv3.coeffRef(1) +=  mv1.coeff(0)*mv2.coeff(3) + mv1.coeff(3)*mv2.coeff(2) - mv1.coeff(4)*mv2.coeff(0);
		mv3.coeffRef(2) +=  mv1.coeff(1)*mv2.coeff(3) - mv1.coeff(3)*mv2.coeff(1) - mv1.coeff(5)*mv2.coeff(0);
		mv3.coeffRef(3) +=  mv1.coeff(2)*mv2.coeff(3) - mv1.coeff(4)*mv2.coeff(1) - mv1.coeff(5)*mv2.coeff(2);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 2) and mv2 (grade 2). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 2 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 2 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 0
	template<typename T>
	void inner_2_2(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) += -mv1.coeff(0)*mv2.coeff(4) - mv1.coeff(1)*mv2.coeff(5) + mv1.coeff(2)*mv2.coeff(2) - mv1.coeff(3)*mv2.coeff(3) - mv1.coeff(4)*mv2.coeff(0) - mv1.coeff(5)*mv2.coeff(1);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 2) and mv2 (grade 3). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 2 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 3 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 1
	template<typename T>
	void inner_2_3(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) += -mv1.coeff(0)*mv2.coeff(1) - mv1.coeff(1)*mv2.coeff(2) - mv1.coeff(3)*mv2.coeff(0);
		mv3.coeffRef(1) += -mv1.coeff(1)*mv2.coeff(3) - mv1.coeff(2)*mv2.coeff(1) + mv1.coeff(5)*mv2.coeff(0);
		mv3.coeffRef(2) +=  mv1.coeff(0)*mv2.coeff(3) - mv1.coeff(2)*mv2.coeff(2) - mv1.coeff(4)*mv2.coeff(0);
		mv3.coeffRef(3) += -mv1.coeff(3)*mv2.coeff(3) - mv1.coeff(4)*mv2.coeff(1) - mv1.coeff(5)*mv2.coeff(2);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 2) and mv2 (grade 4). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 2 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 4 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 2
	template<typename T>
	void inner_2_4(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) += -mv1.coeff(1)*mv2.coeff(0);
		mv3.coeffRef(1) +=  mv1.coeff(0)*mv2.coeff(0);
		mv3.coeffRef(2) += -mv1.coeff(3)*mv2.coeff(0);
		mv3.coeffRef(3) +=  mv1.coeff(2)*mv2.coeff(0);
		mv3.coeffRef(4) +=  mv1.coeff(5)*mv2.coeff(0);
		mv3.coeffRef(5) += -mv1.coeff(4)*mv2.coeff(0);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 3) and mv2 (grade 0). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 3 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 0 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 3
	template<typename T>
	void inner_3_0(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1*mv2.coeff(0);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 3) and mv2 (grade 1). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 3 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 1 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 2
	template<typename T>
	void inner_3_1(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(2) - mv1.coeff(1)*mv2.coeff(0);
		mv3.coeffRef(1) += -mv1.coeff(0)*mv2.coeff(1) - mv1.coeff(2)*mv2.coeff(0);
		mv3.coeffRef(2) += -mv1.coeff(1)*mv2.coeff(1) - mv1.coeff(2)*mv2.coeff(2);
		mv3.coeffRef(3) += -mv1.coeff(0)*mv2.coeff(3) - mv1.coeff(3)*mv2.coeff(0);
		mv3.coeffRef(4) += -mv1.coeff(1)*mv2.coeff(3) - mv1.coeff(3)*mv2.coeff(2);
		mv3.coeffRef(5) += -mv1.coeff(2)*mv2.coeff(3) + mv1.coeff(3)*mv2.coeff(1);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 3) and mv2 (grade 2). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 3 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 2 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 1
	template<typename T>
	void inner_3_2(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) += -mv1.coeff(0)*mv2.coeff(3) - mv1.coeff(1)*mv2.coeff(0) - mv1.coeff(2)*mv2.coeff(1);
		mv3.coeffRef(1) +=  mv1.coeff(0)*mv2.coeff(5) - mv1.coeff(1)*mv2.coeff(2) - mv1.coeff(3)*mv2.coeff(1);
		mv3.coeffRef(2) += -mv1.coeff(0)*mv2.coeff(4) - mv1.coeff(2)*mv2.coeff(2) + mv1.coeff(3)*mv2.coeff(0);
		mv3.coeffRef(3) += -mv1.coeff(1)*mv2.coeff(4) - mv1.coeff(2)*mv2.coeff(5) - mv1.coeff(3)*mv2.coeff(3);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 3) and mv2 (grade 3). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 3 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 3 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 0
	template<typename T>
	void inner_3_3(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(3) + mv1.coeff(1)*mv2.coeff(1) + mv1.coeff(2)*mv2.coeff(2) + mv1.coeff(3)*mv2.coeff(0);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 3) and mv2 (grade 4). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 3 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 4 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 1
	template<typename T>
	void inner_3_4(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) += -mv1.coeff(0)*mv2.coeff(0);
		mv3.coeffRef(1) +=  mv1.coeff(2)*mv2.coeff(0);
		mv3.coeffRef(2) += -mv1.coeff(1)*mv2.coeff(0);
		mv3.coeffRef(3) +=  mv1.coeff(3)*mv2.coeff(0);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 4) and mv2 (grade 0). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 4 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 0 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 4
	template<typename T>
	void inner_4_0(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1*mv2.coeff(0);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 4) and mv2 (grade 1). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 4 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 1 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 3
	template<typename T>
	void inner_4_1(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) += -mv1.coeff(0)*mv2.coeff(0);
		mv3.coeffRef(1) += -mv1.coeff(0)*mv2.coeff(2);
		mv3.coeffRef(2) +=  mv1.coeff(0)*mv2.coeff(1);
		mv3.coeffRef(3) +=  mv1.coeff(0)*mv2.coeff(3);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 4) and mv2 (grade 2). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 4 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 2 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 2
	template<typename T>
	void inner_4_2(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) += -mv1.coeff(0)*mv2.coeff(1);
		mv3.coeffRef(1) +=  mv1.coeff(0)*mv2.coeff(0);
		mv3.coeffRef(2) += -mv1.coeff(0)*mv2.coeff(3);
		mv3.coeffRef(3) +=  mv1.coeff(0)*mv2.coeff(2);
		mv3.coeffRef(4) +=  mv1.coeff(0)*mv2.coeff(5);
		mv3.coeffRef(5) += -mv1.coeff(0)*mv2.coeff(4);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 4) and mv2 (grade 3). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 4 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 3 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 1
	template<typename T>
	void inner_4_3(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(0);
		mv3.coeffRef(1) += -mv1.coeff(0)*mv2.coeff(2);
		mv3.coeffRef(2) +=  mv1.coeff(0)*mv2.coeff(1);
		mv3.coeffRef(3) += -mv1.coeff(0)*mv2.coeff(3);
	}


	/// \brief Compute the inner product between two homogeneous multivectors mv1 (grade 4) and mv2 (grade 4). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 4 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 4 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1.mv2, which is also a homogeneous multivector of grade 0
	template<typename T>
	void inner_4_4(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) += -mv1.coeff(0)*mv2.coeff(0);
	}


	
    template<typename T>
	std::array<std::array<std::function<void(const Eigen::Matrix<T, Eigen::Dynamic, 1> & , const Eigen::Matrix<T, Eigen::Dynamic, 1> & , Eigen::Matrix<T, Eigen::Dynamic, 1>&)>, 5>, 5> innerFunctionsContainer = {{
		{{inner_0_0<T>,inner_0_1<T>,inner_0_2<T>,inner_0_3<T>,inner_0_4<T>}},
		{{inner_1_0<T>,inner_1_1<T>,inner_1_2<T>,inner_1_3<T>,inner_1_4<T>}},
		{{inner_2_0<T>,inner_2_1<T>,inner_2_2<T>,inner_2_3<T>,inner_2_4<T>}},
		{{inner_3_0<T>,inner_3_1<T>,inner_3_2<T>,inner_3_3<T>,inner_3_4<T>}},
		{{inner_4_0<T>,inner_4_1<T>,inner_4_2<T>,inner_4_3<T>,inner_4_4<T>}}
	}};

}/// End of Namespace

#endif // C2GA_INNER_PRODUCT_EXPLICIT_HPP__