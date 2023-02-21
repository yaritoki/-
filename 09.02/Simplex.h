#pragma once

#include "stdafx.h""
#include "SimplexOps.h"
#include <array>
namespace OptLib  // далее идёт описание "класса Поинт"
{
	template <size_t dim>//dim -параметр
	using Point = std::array <double, dim>;//контейнер верктор знятятся доублы с памятью 8 байт 
	// поинт это псевданим для того чтобы можно было сокращать код применр Point<7> p; - точка в 7-ми мерном пространстве


	template <size_t dim>                                                  // дописать вектор минус цисло, вектор плюс число , поэлементно модуль, поэлементно корень 
	//сложение
	Point<dim> operator + (const Point<dim>& p1, const Point<dim>& p2)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), p2.begin(), result.begin(), std::plus<>{});
		return result;
	}

	//работает
	// вычитание
	template <size_t dim>
	Point<dim> operator - (const Point<dim>& p1, const Point<dim>& p2)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), p2.begin(), result.begin(), std::minus<>{});
		return result;
	}																																//работает

	template <size_t dim>
	Point<dim> operator * (const Point<dim>& p1, const Point<dim> p2)
	{
		Point<dim> result;

		std::transform(p1.begin(), p1.end(), p2.begin(), result.begin(), std::multiplies<>{});

		return result;
	}

	//деление
	template <size_t dim>
	Point<dim> operator / (const Point<dim>& p1, const Point<dim>& p2)
	{
		Point<dim> result;

		std::transform(p1.begin(), p1.end(), p2.begin(), result.begin(), SimplexOps::BinaryOps::del<>{});

		return result;
	}

	//умножение скалярное
	template <size_t dim>
	double sc(const Point<dim>& p1, const Point<dim>& p2)															//переименовать скалярное произведение
	{
		Point<dim> result;
		double res = 0;
		std::transform(p1.begin(), p1.end(), p2.begin(), result.begin(), std::multiplies<>{});
		for (auto& el : result)
			res += el;
		return res;
	}

	/*умножение на число*/
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

	//деление точки на число и на оборот
	template <size_t dim>
	Point<dim> operator / (const Point<dim>& p1, double scalar)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), result.begin(), SimplexOps::UnaryOps::del<double>{scalar});
		return result;
	}
	template <size_t dim>					//пришлось писать отдельный пункт
	Point<dim> operator / (double scalar, const Point<dim>& p1)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), result.begin(), SimplexOps::UnaryOps::del1<double>{scalar});
		return result;
	}


	//сложение числа и точки
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


	//вычитание числа и точки
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

	//модуль
	template <size_t dim>
	Point<dim>  Abs(const Point<dim>& p1)
	{
		Point<dim> result;
		std::transform(p1.begin(), p1.end(), result.begin(), SimplexOps::UnaryOps::abs{});
		return result;
	}

	/*корень*/
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
	//транспонирование
	template<size_t count, typename point>
	SetOfPoints<count, point> Tr(const SetOfPoints<count, point>& rhs)
	{
		SetOfPoints<count, point> Res ;

		for (size_t i = 0; i < count; i++)
		{
			for (size_t j = 0; j < count; j++)//для квадратных
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
			//Матрица без строки и столбца
			SetOfPoints<count - 1, point> newMatrix;
			for (int i = 0; i < size - 1; i++) {
				newMatrix[i] = point[size-1];
			}

			//Раскладываем по 0-ой строке, цикл бежит по столбцам
			for (int j = 0; j < size; j++) {
				//Удалить из матрицы i-ю строку и j-ый столбец
				//Результат в newMatrix
				getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

				//Рекурсивный вызов
				//По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть сумма из формулы)
				//где minor_j - дополнительный минор элемента matrix[0][j]
				// (напомню, что минор это определитель матрицы без 0-ой строки и j-го столбца)
				det = det + (degree * matrix[0][j] * Det(newMatrix);
				//"Накручиваем" степень множителя
				degree = -degree;
			}

			//Чистим память на каждом шаге рекурсии(важно!)
			for (int i = 0; i < size - 1; i++) {
				delete[] newMatrix[i];
			}
			delete[] newMatrix;
		}return det;

	}*/



			
			

			
	
	//нужно дописать через 

	

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

//вывод в поток работает



/*
sqrt		работает
abs			работает
скалярное	работает
p1*p1		работает
p1+p2		работает
p1+bouble	работает
p1-p2		работает
p1/double	работает
p1/p2		
p1*double	 работает





*/	
		






//*-/ умножение на число деление на число






//если бы был класс
/*
class Point
{
Point<dim> operator +(const Point&p1,const Point&p2);
далее идёт алгоритм сложение
}
*/



// всё что шаблонное должно быть в хедере
/*

перегрузка оператора вывода в поток в другом файле нужно
в поинте реализация операторов 
в спп алгоритм 
*/
