#pragma once

#include "stdafx.h""
#include "SimplexOps.h"
#include <array>
namespace OptLib  // ????? ???? ???????? "?????? ?????"
{
	template <size_t dim>//dim -????????
	using Point = std::array <double, dim>;//????????? ??????? ???????? ?????? ? ??????? 8 ???? 
	// ????? ??? ????????? ??? ???? ????? ????? ???? ????????? ??? ??????? Point<7> p; - ????? ? 7-?? ?????? ????????????


	template <size_t dim>                                                  // ???????? ?????? ????? ?????, ?????? ???? ????? , ??????????? ??????, ??????????? ?????? 
	//????????
	Point<dim> operator + (const Point<dim>& p1, const Point<dim>& p2)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), p2.begin(), result.begin(), std::plus<>{});
		return result;
	}

	//????????
	// ?????????
	template <size_t dim>
	Point<dim> operator - (const Point<dim>& p1, const Point<dim>& p2)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), p2.begin(), result.begin(), std::minus<>{});
		return result;
	}																																//????????

	template <size_t dim>
	Point<dim> operator * (const Point<dim>& p1, const Point<dim> p2)
	{
		Point<dim> result;

		std::transform(p1.begin(), p1.end(), p2.begin(), result.begin(), std::multiplies<>{});

		return result;
	}

	//???????
	template <size_t dim>
	Point<dim> operator / (const Point<dim>& p1, const Point<dim>& p2)
	{
		Point<dim> result;

		std::transform(p1.begin(), p1.end(), p2.begin(), result.begin(), SimplexOps::BinaryOps::del<>{});

		return result;
	}

	//????????? ?????????
	template <size_t dim>
	double sc(const Point<dim>& p1, const Point<dim>& p2)															//????????????? ????????? ????????????
	{
		Point<dim> result;
		double res = 0;
		std::transform(p1.begin(), p1.end(), p2.begin(), result.begin(), std::multiplies<>{});
		for (auto& el : result)
			res += el;
		return res;
	}

	/*????????? ?? ?????*/
	template <size_t dim>
	Point<dim> operator * (const Point<dim>& p1, double scalar)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), result.begin(), SimplexOps::UnaryOps::mult<double>{scalar});
		return result;
	}
	template <size_t dim>
	Point<dim> operator * (double scalar, const Point<dim>& p1)
	{
		return p1 * scalar;
	}

	//??????? ????? ?? ????? ? ?? ??????
	template <size_t dim>
	Point<dim> operator / (const Point<dim>& p1, double scalar)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), result.begin(), SimplexOps::UnaryOps::del<double>{scalar});
		return result;
	}
	template <size_t dim>					//???????? ?????? ????????? ?????
	Point<dim> operator / (double scalar, const Point<dim>& p1)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), result.begin(), SimplexOps::UnaryOps::del1<double>{scalar});
		return result;
	}


	//???????? ????? ? ?????
	template <size_t dim>
	Point<dim> operator + (const Point<dim>& p1, double scalar)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), result.begin(), SimplexOps::UnaryOps::plus<double>{scalar});
		return result;
	}
	template <size_t dim>
	Point<dim> operator + (double scalar, const Point<dim>& p1)
	{
		return p1+ scalar;
	}


	//????????? ????? ? ?????
	template <size_t dim>
	Point<dim> operator - (const Point<dim>& p1, double scalar)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), result.begin(), SimplexOps::UnaryOps::minus<double>{scalar});
		return result;
	}
	template <size_t dim>
	Point<dim> operator - (double scalar, const Point<dim>& p1)
	{
		Point<dim> res =p1* -1;
		return res+ scalar;
	}

	//??????
	template <size_t dim>
	Point<dim>  Abs(const Point<dim>& p1)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), result.begin(), SimplexOps::UnaryOps::abs{});
		return result;
	}

	/*??????*/
	template <size_t dim>
	Point<dim>  Sqrt(const Point<dim>& p1)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), result.begin(), SimplexOps::UnaryOps::sqrt{});
		return result;
	}

	/*


	//16.02
	template <size_t dim>
	struct RawPoint
	{
		RawPoint() = default;
		Point<dim> P;
		RawPoint(const Point<dim>& p) :P{ p } {};
		RawPoint(Point<dim>&& p) :P{ std::move(p) } {};
		double operator [](size_t i)const
		{
			return P[i];
		}
		operator Point<dim>()
		{
			return P;
		};
	};
	template <size_t dim>
	struct PointVal :public RawPoint<dim>
	{
		double val;
		PointVal() = default;
		//PointVal(const PointVal& p) = default;
		PointVal(Point<dim>&& p, double val) :RawPoint<dim>{ std::move(p) }, val{ val }{};
		PointVal(const Point<dim>& p, double val) :RawPoint<dim>{ p }, val{ val }{};

		bool operator<(const Point<dim>& rhs)
		{
			return this->val < rhs.val;
		}
	};*/

	//20.02
	template<size_t count, typename point>
	using SetOfPoints = std::array<point, count>;
	//????????????????
	template<size_t count, typename point>
	SetOfPoints<count, point> Tr(const SetOfPoints<count, point>& rhs)
	{
		SetOfPoints<count, point> Res ;

		for (size_t i = 0; i < count; i++)
		{
			for (size_t j = 0; j < count; j++)//??? ??????????
			{
				Res[i][j] = rhs[j][i];
			}

		}

		return Res;
	}

	/*template<size_t count, typename point>
	double Det(const SetOfPoints<count, point>& rhs,size_t n)
	{
		
		double det = 0;
		SetOfPoints<n, point> matrix, int size;
			int det = 0;
		int degree = 1;
		if (count == 1)
		{
			return rhs[0][0];
		}
		else if (count == 2)
		{
			return rhs[0][0] * rhs[1][1] - rhs[1][0] * rhs[0][1];
		}
		else {
			//??????? ??? ?????? ? ???????
			SetOfPoints<count - 1, point> newMatrix;
			for (int i = 0; i < size - 1; i++) {
				newMatrix[i] = point[size-1];
			}

			//???????????? ?? 0-?? ??????, ???? ????? ?? ????????
			for (int j = 0; j < size; j++) {
				//??????? ?? ??????? i-? ?????? ? j-?? ???????
				//????????? ? newMatrix
				getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

				//??????????? ?????
				//?? ???????: ????? ?? j, (-1)^(1+j) * matrix[0][j] * minor_j (??? ? ???? ????? ?? ???????)
				//??? minor_j - ?????????????? ????? ???????? matrix[0][j]
				// (???????, ??? ????? ??? ???????????? ??????? ??? 0-?? ?????? ? j-?? ???????)
				det = det + (degree * matrix[0][j] * Det(newMatrix);
				//"???????????" ??????? ?????????
				degree = -degree;
			}

			//?????? ?????? ?? ?????? ???? ????????(?????!)
			for (int i = 0; i < size - 1; i++) {
				delete[] newMatrix[i];
			}
			delete[] newMatrix;
		}return det;

	}*/



			
			

			
	
	//????? ???????? ????? 

	

	template<size_t count, typename point>
	point operator*(const SetOfPoints<count, point>& rhs, const point& ihs)
	{
		point res;
		for (size_t i = 0; i < count; i++)
		{
			res[i] = sc(rhs[i], ihs);
		}
		
		return res;
	}
	template<size_t count, typename point>
		SetOfPoints<count,point> operator*(const SetOfPoints<count, point>& rhs, const SetOfPoints<count, point>& ihs)
	{
			SetOfPoints<count, point> Res;
			
		for (size_t i = 0; i < count; i++)
		{
			
				Res[i] = rhs * ihs[i];
		
		}
		Res=Tr(Res);

		return Res;
	}

		
}

//????? ? ????? ????????



/*
sqrt		????????
abs			????????
?????????	????????
p1*p1		????????
p1+p2		????????
p1+bouble	????????
p1-p2		????????
p1/double	????????
p1/p2		
p1*double	 ????????





*/	
		






//*-/ ????????? ?? ????? ??????? ?? ?????






//???? ?? ??? ?????
/*
class Point
{
Point<dim> operator +(const Point&p1,const Point&p2);
????? ???? ???????? ????????
}
*/



// ??? ??? ????????? ?????? ???? ? ??????
/*

?????????? ????????? ?????? ? ????? ? ?????? ????? ?????
? ?????? ?????????? ?????????? 
? ??? ???????? 
*/
