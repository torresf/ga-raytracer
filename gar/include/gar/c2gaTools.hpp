#pragma once
#ifndef __C2GATOOLS__HPP
#define __C2GATOOLS__HPP

using namespace c2ga;

namespace gar {

template<typename T>
Mvec<T> point(const T &x, const T &y){

	Mvec<T> mv;
	mv[E1] = x;
	mv[E2] = y;
	mv[Ei] = 0.5 * mv.quadraticNorm();
	mv[E0] = 1.0;

	return mv;
}

template<typename T>
Mvec<T> point(const glm::vec2 &vec){
		return point(vec.x, vec.y);
}

template<typename T>
Mvec<T> line(const Mvec<T> &p1, const Mvec<T> &p2) {
	return p1 ^ p2 ^ ei<T>();
}

template<typename T>
Mvec<T> line(const T &a, const T &b, const T &c) {
	return a * e1<T>() + b * e2<T>() + c * ei<T>();
}

template<typename T>
Mvec<T> circle(const T &x, const T &y, const T &r) {
	Mvec<T> dualCircle = point(x, y);
	dualCircle[c2ga::Ei] -= r * r * .5;
	return !dualCircle; // = circle
}

template<typename T>
Mvec<T> normalize(const Mvec<T> &mv) {
	return -mv / (mv | ei<double>());
}

template<typename T>
Mvec<T> getIntersection(const Mvec<T> &mv1, const Mvec<T> &mv2) {
	return !((!mv1) ^ (!mv2)); // Intersection
}

template<typename T>
bool areIntersected(const Mvec<T> &mv1, const Mvec<T> &mv2) {
	return (T)(getIntersection(mv1, mv2) | getIntersection(mv1, mv2)) > 0;
}

template<typename T>
bool isPointInCircle(const Mvec<T> &p, const Mvec<T> &c) {
	return areIntersected(p, c);
}

template<typename T>
Mvec<T> projectPointOnLine(const Mvec<T> &p, const Mvec<T> &l) {
	return -normalize(p < l);
}

template<typename T>
Mvec<T> getCenterOfCircle(const Mvec<T> &circle) {
	return -circle / (ei<T>() < circle);
}

template<typename T>
Mvec<T> getFirstPointFromPointPair(const Mvec<T> &pp) {
	return (pp + sqrt(pp*pp)) / (-ei<T>() | pp);
}

template<typename T>
Mvec<T> projectPointOnCircle(const Mvec<T> &p, const Mvec<T> &c) {
	return getFirstPointFromPointPair(getIntersection(c, line(p, getCenterOfCircle(c))));
}

template<typename T>
float distance(const Mvec<T> &p1, const Mvec<T> &p2) {
	return (p2 - p1).norm();
}



template<typename T>
std::string whoAmI(c2ga::Mvec<T> mv) {

	// zero error checking
	const T epsilon = std::numeric_limits<T>::epsilon();

	// extract grade
	std::vector<unsigned int> grades_ = mv.grades();

	// null vector
	if(grades_.size() == 0)
		return "null vector";

	// non-homogeneous multivector
	if(grades_.size() > 1){
		return "non-homogeous multivector";
		// check if versor ...
	}

		// blade
		if(grades_.size() == 1){

				// numerical stability: scale the multivector so that the average of the coeff is 1
				auto blade = mv.findGrade(grades_[0])->vec;
				mv /= blade.array().abs().sum() / blade.size();
				//return std::to_string((double)blade.array().abs().sum()/ blade.size());

				// extract properties
				T square = (mv | mv);
				c2ga::Mvec<T> ei_outer_mv(c2ga::ei<T>() ^ mv);
				bool squareToZero = (fabs(square) <= 1.0e3*epsilon);
				bool roundObject  = !(fabs(ei_outer_mv.quadraticNorm()) < epsilon);
				//return "squareToZero : " + std::to_string(squareToZero) + " | roundObject : " +  std::to_string(roundObject) + " | ei_outer_mv.norm() : " + std::to_string(ei_outer_mv.quadraticNorm()) + " | square : " + std::to_string(fabs(square));

			switch(grades_[0]){

				////////////////////////////////
				case 0 : // grade 0
					return "scalar";
					break;

				////////////////////////////////
				case 1 : // grade 1
					{
						// euclidean vector
						// if(fabs(mv[c2ga::E0]) < epsilon && fabs(mv[c2ga::Ei]) < epsilon)
						// 	return "Euclidean vector";

						// point (dual tangent trivector)
						if( squareToZero && roundObject )
							return "point (dual tangent trivector)";

						// dual sphere
						if( square > epsilon && roundObject )
							return "dual sphere";

										// imaginary dual sphere (dual sphere with negative radius)
						if( square < -epsilon && roundObject)
							return "imaginary dual sphere";

										// dual plane
										if((!roundObject))
												return "dual plane";

						// unknown
						return "unknown 1-vector";
				break;
					}

				////////////////////////////////
				case 2 : // grade 2
					{
										// tangent vector (put this test first in the grade 2 list)
										bool smallerSquareToZero = (fabs(square) <= 1.0e3*epsilon);
										if(smallerSquareToZero && roundObject)
											return "tangent vector (dual tangent bivector)";

						// pair point
										if(roundObject && (square > epsilon) )
								return "pair point (imaginary dual circle)";

										// imaginary pair point
										if(roundObject && (square < -epsilon))
												return "imaginary pair point (dual circle)";

										// for flat points and dual lines
										bool onlyBivectorInfinity = (fabs( ( (mv ^ c2ga::ei<double>() ) | c2ga::e0<double>() ).quadraticNorm()) < epsilon);

						// flat point
										// no euclidian or eO bivector : only e_ix
#if 1
										if((!roundObject) && onlyBivectorInfinity)
#else
										if(fabs(mv[c2ga::E12]) < epsilon &&
											 fabs(mv[c2ga::E13]) < epsilon &&
											 fabs(mv[c2ga::E23]) < epsilon &&
											 fabs(mv[c2ga::E01]) < epsilon &&
											 fabs(mv[c2ga::E02]) < epsilon &&
											 fabs(mv[c2ga::E03]) < epsilon )
#endif
								return "flat point";

						// dual line
										// no origine bivector
#if 1
										if((!roundObject) && (!onlyBivectorInfinity))
#else
										if(fabs(mv[c2ga::E01]) < epsilon &&
											 fabs(mv[c2ga::E02]) < epsilon &&
											 fabs(mv[c2ga::E03]) < epsilon &&
											 fabs(mv[c2ga::E0i]) < epsilon )
#endif
												return "dual line";

						// unknown
						return "unknown 2-vector";
				break;
					}


				////////////////////////////////
				case 3 : // grade 3
					{

										// tangent bivector (put this test first in the grade 2 list)
										bool smallerSquareToZero = (fabs(square) <= 1.0e3*epsilon);
										if(smallerSquareToZero && roundObject)
											return "tangent bivector (dual tangent vector)";

										// circle
										if(roundObject && (square > epsilon) )
												return "circle (imaginary dual pair point)";

						// imaginary circle
										if(roundObject && (square < -epsilon))
								return "imaginary circle (dual pair point)";


							// for dual flat points and lines
										bool onlyTrivectorInfinity = (fabs( ( (mv ^ c2ga::ei<double>() ) | c2ga::e0<double>() ).quadraticNorm()) < epsilon);

						// dual flat point
										// no e0 trivector
#if 1
										if((!roundObject) && !onlyTrivectorInfinity)
#else
										if(fabs(mv[c2ga::E012]) < epsilon &&
											 fabs(mv[c2ga::E013]) < epsilon &&
											 fabs(mv[c2ga::E023]) < epsilon &&
											 fabs(mv[c2ga::E01i]) < epsilon &&
											 fabs(mv[c2ga::E02i]) < epsilon &&
											 fabs(mv[c2ga::E03i]) < epsilon )
#endif
								return "dual flat point";

						// line
										// only e_ixx trivectors
#if 1
										if((!roundObject) && onlyTrivectorInfinity)
#else
										if(fabs(mv[c2ga::E012]) < epsilon &&
											 fabs(mv[c2ga::E023]) < epsilon &&
											 fabs(mv[c2ga::E013]) < epsilon &&
											 fabs(mv[c2ga::E123]) < epsilon )
#endif
												return "line";


						// unknown
						return "unknown 3-vector";
				break;
					}


				////////////////////////////////
				case 4 : // grade 4
					{
						// dual euclidean vector (removed because a plane can also have this form)
						// if(fabs(mv[c2ga::E0123]) < epsilon && fabs(mv[c2ga::E123i]) < epsilon)
						// 	return "dual Euclidean vector";

						// dual point
						if( squareToZero && roundObject )
							return "tangent trivector (dual point)";

						// sphere and imaginary sphere: compute radius from dual
						c2ga::Mvec<double> dualSphere = mv.dual();
						T dualSquare = dualSphere | dualSphere;

						// sphere
						if( dualSquare > epsilon && roundObject )
							return "sphere";

						// imaginary sphere (sphere with negative radius)
						if( dualSquare < -epsilon && roundObject)
							return "imaginary sphere";

										// plane
										if((!roundObject))
												return "plane";

						// unknown
						return "unknown 4-vector";
				break;
					}


				////////////////////////////////
				case 5 : // grade 5
					{
						// unknown
						return "pseudo-scalar";
				break;
					}

				////////////////////////////////
				default : return "unknown";

			}
		}

		return std::to_string(grades_[0]) + "-vector (homogeneous)";
}

}

#endif
