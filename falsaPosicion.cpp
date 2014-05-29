#include <iostream>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include "exprtk.hpp"

using namespace std;

template<typename T>
class Evaluar
{
	string funcion;
	int primer;
	float f;
public:
	void tabFuncion(string ecuacion){

		funcion = ecuacion;

		T r0 = T(-10);
		T r1 = T(10);
		T  x = T(0);

   		exprtk::symbol_table<T> symbol_table;
   		symbol_table.add_variable("x",x);

  		exprtk::expression<T> expression;
   		expression.register_symbol_table(symbol_table);

   		exprtk::parser<T> parser;
   		parser.compile(funcion,expression);

	   	for (x = r0; x <= r1; x= x++)
	   	{
	    	printf("%10.2f\t%10.6f\n",x,expression.value());
	   	}

	}

	float evFuncion( string ecuacion , float num){

		primer = num;
		T  x = T(num);

   		exprtk::symbol_table<T> symbol_table;
   		symbol_table.add_variable("x",x);

  		exprtk::expression<T> expression;
   		expression.register_symbol_table(symbol_table);

   		exprtk::parser<T> parser;
   		parser.compile(ecuacion,expression);

	    f = expression.value();
	    return f;

	}
};

class metodoFalsaPosicion
{
public:
	void falsaPosicion(string ecuacion , float numA, float numB, float numE, int nIt)
	{

		Evaluar <double> evF;
		float a,b,c,e,Fa,Fb, Fm, n;
		int i;

		n = nIt;
		e = numE;
		a = numA;
		b = numB;
		i = 1;

		for (int i = 0; i < n; ++i)
		{
			Fa = evF.evFuncion(ecuacion,a);
			Fb = evF.evFuncion(ecuacion,b);
			c = ( (a*Fb) - (b*Fa) ) / (Fb-Fa); //Formula Metodo Falsa Pocision
			Fm = evF.evFuncion(ecuacion,c);
    		printf("| Iteracion \t|\t      A\t\t\t|\t      B\t\t\t|\t   C      \t|\t    F(C) \t\t|\n");
    		printf("|     %d \t|\t   %5.10f\t\t|\t   %5.10f\t\t|     %5.10f    \t|     %5.10f\t\t|\n",i,a,b,c,Fm);
    		if (Fa*Fm < 0)
    		{
    			b = c;
    		}
    		else
    		{
    			a = c;
    		}
		}

	}

	void falsaPosicionErr(string ecuacion , float numA, float numB, float numE)
	{

		Evaluar <double> evF;
		float a,b,c,e,Fa,Fb, Fm;
		int i;

		e = numE;
		a = numA;
		b = numB;
		i = 1;

		while (abs(b-a) > e)
		{
			Fa = evF.evFuncion(ecuacion,a);
			Fb = evF.evFuncion(ecuacion,b);
			c = ( (a*Fb) - (b*Fa) ) / (Fb-Fa); //Formula Metodo Falsa Pocision
			Fm = evF.evFuncion(ecuacion,c);
    		printf("| Iteracion \t|\t      A\t\t\t|\t      B\t\t\t|\t   C      \t|\t    F(C) \t\t|\n");
    		printf("|     %d \t|\t   %5.10f\t\t|\t   %5.10f\t\t|     %5.10f    \t|     %5.10f\t\t|\n",i,a,b,c,Fm);
    		i++;
    		if (Fa*Fm < 0)
    		{
    			b = c;
    		}
    		else
    		{
    			a = c;
    		}
    	
		}

	}

};

int main()
{
	//variables a utilizar
	float a,b,c,e;
	int op,n;
	char op2='s';
	string expression_string;

	//creacion de los objetos
	Evaluar <double> evF;
	metodoFalsaPosicion Fp;

	while(op2 == 's' || op2 == 'S')
	{
		cout << "Ingrese Su Funcion f(x): (Sin espacios) " << endl;
		cout << "ejemplo: x^3 + cos x - e^2x --> x^3+cos(x)-exp(2*x)" << endl;
		cin >> expression_string;
		cout <<endl<<"Tabulacion:"<<endl;
		evF.tabFuncion(expression_string);
		cout <<endl<<"De acuerdo a la tabla anterior seleccione los valores de cambio de signo"<<endl;
		cout << "Ingrese el punto A: " << endl;
		cin >> a;
		cout << "Ingrese el punto B: " << endl;
		cin >> b;
		evF.evFuncion(expression_string,a);
		evF.evFuncion(expression_string,b);

		cout <<"Como evaluaras la funcion?"<<endl;
		cout <<"1. Por Margen de error"<<endl;
		cout <<"2. Numero de iteracciones"<<endl;
		cout <<"Presione 1/2"<<endl;

		cin >> op;
		if ( op == 1)
		{
			cout << "Ingrese el Margen de Error: " << endl;
			cin >> e;
			system("cls");
			Fp.falsaPosicionErr(expression_string,a,b,e);

		}
		else
		{
			cout << "Cuantas iteraciones quieres hacer?" << endl;
			cin >> n;
			system("cls");
			Fp.falsaPosicion(expression_string,a,b,e,n);

		}
		cout << "Desea evaluar otra ecuacion S/N" << endl;
		cin >> op2;
		system("cls");
	}
	cout << "Hasta luego!" << endl;
	getch();

	return 0;
}

