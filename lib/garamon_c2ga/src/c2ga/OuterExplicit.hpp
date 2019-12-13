// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// OuterExplicit.hpp
// This file is part of the Garamon for c2ga.
// Authors: Stephane Breuils and Vincent Nozick
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program

/// \file OuterExplicit.hpp
/// \author Stephane Breuils, Vincent Nozick
/// \brief Explicit precomputed per grades outer product.


#ifndef C2GA_OUTER_PRODUCT_EXPLICIT_HPP__
#define C2GA_OUTER_PRODUCT_EXPLICIT_HPP__
#pragma once

#include <Eigen/Core>

#include "c2ga/Mvec.hpp"
#include "c2ga/Outer.hpp"


/*!
 * @namespace c2ga
 */
namespace c2ga {
    template<typename T> class Mvec;

    /// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 0) and mv2 (grade 0). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 0 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 0 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 0
	template<typename T>
	void outer_0_0(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(0);
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 0) and mv2 (grade 1). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 0 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 1 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 1
	template<typename T>
	void outer_0_1(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1.coeff(0)*mv2;
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 0) and mv2 (grade 2). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 0 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 2 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 2
	template<typename T>
	void outer_0_2(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1.coeff(0)*mv2;
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 0) and mv2 (grade 3). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 0 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 3 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 3
	template<typename T>
	void outer_0_3(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1.coeff(0)*mv2;
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 0) and mv2 (grade 4). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 0 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 4 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 4
	template<typename T>
	void outer_0_4(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1.coeff(0)*mv2;
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 1) and mv2 (grade 0). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 1 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 0 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 1
	template<typename T>
	void outer_1_0(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1*mv2.coeff(0);
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 1) and mv2 (grade 1). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 1 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 1 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 2
	template<typename T>
	void outer_1_1(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(1) - mv1.coeff(1)*mv2.coeff(0);
		mv3.coeffRef(1) +=  mv1.coeff(0)*mv2.coeff(2) - mv1.coeff(2)*mv2.coeff(0);
		mv3.coeffRef(2) +=  mv1.coeff(0)*mv2.coeff(3) - mv1.coeff(3)*mv2.coeff(0);
		mv3.coeffRef(3) +=  mv1.coeff(1)*mv2.coeff(2) - mv1.coeff(2)*mv2.coeff(1);
		mv3.coeffRef(4) +=  mv1.coeff(1)*mv2.coeff(3) - mv1.coeff(3)*mv2.coeff(1);
		mv3.coeffRef(5) +=  mv1.coeff(2)*mv2.coeff(3) - mv1.coeff(3)*mv2.coeff(2);
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 1) and mv2 (grade 2). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 1 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 2 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 3
	template<typename T>
	void outer_1_2(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(3) - mv1.coeff(1)*mv2.coeff(1) + mv1.coeff(2)*mv2.coeff(0);
		mv3.coeffRef(1) +=  mv1.coeff(0)*mv2.coeff(4) - mv1.coeff(1)*mv2.coeff(2) + mv1.coeff(3)*mv2.coeff(0);
		mv3.coeffRef(2) +=  mv1.coeff(0)*mv2.coeff(5) - mv1.coeff(2)*mv2.coeff(2) + mv1.coeff(3)*mv2.coeff(1);
		mv3.coeffRef(3) +=  mv1.coeff(1)*mv2.coeff(5) - mv1.coeff(2)*mv2.coeff(4) + mv1.coeff(3)*mv2.coeff(3);
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 1) and mv2 (grade 3). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 1 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 3 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 4
	template<typename T>
	void outer_1_3(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(3) - mv1.coeff(1)*mv2.coeff(2) + mv1.coeff(2)*mv2.coeff(1) - mv1.coeff(3)*mv2.coeff(0);
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 2) and mv2 (grade 0). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 2 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 0 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 2
	template<typename T>
	void outer_2_0(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1*mv2.coeff(0);
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 2) and mv2 (grade 1). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 2 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 1 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 3
	template<typename T>
	void outer_2_1(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(2) - mv1.coeff(1)*mv2.coeff(1) + mv1.coeff(3)*mv2.coeff(0);
		mv3.coeffRef(1) +=  mv1.coeff(0)*mv2.coeff(3) - mv1.coeff(2)*mv2.coeff(1) + mv1.coeff(4)*mv2.coeff(0);
		mv3.coeffRef(2) +=  mv1.coeff(1)*mv2.coeff(3) - mv1.coeff(2)*mv2.coeff(2) + mv1.coeff(5)*mv2.coeff(0);
		mv3.coeffRef(3) +=  mv1.coeff(3)*mv2.coeff(3) - mv1.coeff(4)*mv2.coeff(2) + mv1.coeff(5)*mv2.coeff(1);
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 2) and mv2 (grade 2). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 2 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 2 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 4
	template<typename T>
	void outer_2_2(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(5) - mv1.coeff(1)*mv2.coeff(4) + mv1.coeff(2)*mv2.coeff(3) + mv1.coeff(3)*mv2.coeff(2) - mv1.coeff(4)*mv2.coeff(1) + mv1.coeff(5)*mv2.coeff(0);
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 3) and mv2 (grade 0). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 3 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 0 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 3
	template<typename T>
	void outer_3_0(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1*mv2.coeff(0);
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 3) and mv2 (grade 1). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 3 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 1 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 4
	template<typename T>
	void outer_3_1(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3.coeffRef(0) +=  mv1.coeff(0)*mv2.coeff(3) - mv1.coeff(1)*mv2.coeff(2) + mv1.coeff(2)*mv2.coeff(1) - mv1.coeff(3)*mv2.coeff(0);
	}


	/// \brief Compute the outer product between two homogeneous multivectors mv1 (grade 4) and mv2 (grade 0). 
	/// \tparam the type of value that we manipulate, either float or double or something.
	/// \param mv1 - the first homogeneous multivector of grade 4 represented as an Eigen::VectorXd
	/// \param mv2 - the second homogeneous multivector of grade 0 represented as a Eigen::VectorXd
	/// \param mv3 - the result of mv1^mv2, which is also a homogeneous multivector of grade 4
	template<typename T>
	void outer_4_0(const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv1, const Eigen::Matrix<T, Eigen::Dynamic, 1>& mv2, Eigen::Matrix<T, Eigen::Dynamic, 1>& mv3){
		mv3 += mv1*mv2.coeff(0);
	}


	

    template<typename T>
	std::array<std::array<std::function<void(const Eigen::Matrix<T, Eigen::Dynamic, 1> & , const Eigen::Matrix<T, Eigen::Dynamic, 1> & , Eigen::Matrix<T, Eigen::Dynamic, 1>&)>, 5>, 5> outerFunctionsContainer = {{
		{{outer_0_0<T>,outer_0_1<T>,outer_0_2<T>,outer_0_3<T>,outer_0_4<T>}},
		{{outer_1_0<T>,outer_1_1<T>,outer_1_2<T>,outer_1_3<T>,{}}},
		{{outer_2_0<T>,outer_2_1<T>,outer_2_2<T>,{},{}}},
		{{outer_3_0<T>,outer_3_1<T>,{},{},{}}},
		{{outer_4_0<T>,{},{},{},{}}}
	}};

}/// End of Namespace

#endif // C2GA_OUTER_PRODUCT_EXPLICIT_HPP__