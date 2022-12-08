
#include <iostream>
#include <string>
#include <cstdarg>

struct Liczba
{
	int liczba;
	int znak;
};
std::string Parse(std::string text, int i=0)
{

	if (text[i] >= '1' && text[i] <= '9')//spacje na koncu
	{
		return text.substr(i, text.size()- (i));
	}
	if (text.size() - 1 == i)
	{
		return "0";
	}
	return Parse(text, ++i);
	
}

int Positivity(std::string text, int i=0)
{
	if (text[i] == '-')
	{
		return -1;
	}
	if (text.size() - 1 == i)
	{
		return 1;
	}
	
	return Positivity(text, ++i);
}

std::string Padding(std::string liczba, int i)
{
	if (i == 0)
	{
		return liczba;
	}
	liczba = '0' + liczba;

	return (Padding(liczba, --i));

}

std::string Reverse(std::string liczba, int i = 0)
{
	liczba[liczba.size() - 1 - i] = ('9' - liczba[liczba.size() - 1 - i]) + '0';

	if (i == liczba.size() - 1)
	{
		return liczba;
	}
	return Reverse(liczba, ++i);
	
}
std::string Increase(std::string liczba1, std::string liczba2, int i, int carry = 0, std::string wynik = "")
{

	wynik =  (char)(((((liczba1[i-1] - '0') + (liczba2[i-1] - '0')) + carry) % 10) + '0') + wynik;

	if (((liczba1[i-1] - '0') + (liczba2[i-1] - '0')) + carry >= 10)
	{
		carry = 1;
	}
	else
	{
		carry = 0;
	}


	if (i == 1)
	{
		if (carry != 0)
		{
			wynik = '1' + wynik;
		}

		return wynik;
	}

	return Increase(liczba1, liczba2, --i, carry, wynik);
}
std::string Decrease(std::string liczba1, std::string liczba2, std::string string = "")
{
	int size = liczba1.size();
	liczba2=Reverse(liczba2);
	


	string= Increase(liczba1, liczba2, size);


	//obetnij pierwszy znak, dodaj 1
	string = string.substr(1, size);
	std::string complement = "1";
	complement = Padding(complement, size - 1);
	if (size == 1)
	{
		if ((string[0] - '0') + 1 >= 10)
		{
			string = '0';
		}
		else
		{
			string = ((string[0] - '0') + 1) + '0';
		}

	}
	else
	{
		string = Increase(string, complement, size);
	}


	return string;
}



int Bigger(std::string liczba1, std::string liczba2,int i=0)// 0 to takie same
{

	if (liczba1.size() > liczba2.size())
	{

		return 1;
	}
	else if (liczba1.size() < liczba2.size())
	{
		return 2;
	}
	else if (liczba1.size() == liczba2.size())
	{
		if (liczba1[i] > liczba2[i])
		{
			return 1;
		}
		else if (liczba1[i] < liczba2[i])
		{
			return 2;
		}
		else
		{
			if (i == liczba1.size() - 1)
			{
				return 0;
			}
			else
			{
				return Bigger(liczba1, liczba2, ++i);
			}
		}
	}
}
//std::SumFunc;

void GetStrList(std::string val_str[], int n, va_list argv, int i = 0)
{
	val_str[i] = va_arg(argv, char*);
	if (i > n - 2) 
		return;
	GetStrList(val_str, n, argv, ++i);
	

}

std::string MakeSigned(std::string string, int znak)
{
	if (znak == -1)
	{
		return ('-' + string);
	}
	else
	{
		return string;
	}
}
std:: string SumForCoffe(int args, const std::string* tablica, int i = 0, std::string string = "", int znak = 1)
{

	std::string liczba1;
	int sign1;
	int sign2;
	if (i == 0)
	{
		sign1 = Positivity(tablica[i]);
		liczba1 = Parse(tablica[i]);
	}
	else
	{
		sign1 = znak;
		liczba1 = string;
	}
	std::string liczba2 = Parse(tablica[i + 1]);




	sign2 = Positivity(tablica[i + 1]);
	//Dotad dziala
	/////////////////////////////////////////////////
	if (Bigger(liczba1, liczba2) == 1)
	{
		//dziala
		liczba2 = Padding(liczba2, liczba1.size() - liczba2.size());

	}
	else if (Bigger(liczba1, liczba2) == 2)
	{

		liczba1 = Padding(liczba1, liczba2.size() - liczba1.size());
	}
	////////////////////////////////////////////////////
	int size = liczba1.size();



	if (sign1 * sign2 > 0)
	{

		znak = sign1;
		string = Increase(liczba1, liczba2, size);
	}
	else
	{

		if (Bigger(liczba1, liczba2) == 1)
		{
			znak = sign1;
			string = Decrease(liczba1, liczba2);
		}
		else if (Bigger(liczba1, liczba2)== 2)
		{
			znak = sign2;
			string = Decrease(liczba2, liczba1);
		}
		else if (Bigger(liczba1, liczba2) == 0)
		{
			znak = sign2;
			string = "0";
		}

	}





	if (i == args - 2)
	{
		string = Parse(string);

		string = MakeSigned(string, znak);

		if (string == "-0")
		{
			string = '0';
		}
		return string;
	}

	return SumForCoffe(args, tablica, ++i, string, znak);


}
std::string Sum(int args, const std::string* tablica)
{

	return SumForCoffe(args, tablica);


}


std::string Sum(int n, ...)
{
	va_list args;
	va_start(args, n);
	std::string val_str[n];
	GetStrList(val_str, n, args);
	va_end(args);

	return Sum(n, val_str);

}
void Sum(std::string* string, int args, const std::string* tablica)
{
	*string = Sum(args, tablica);

}
void Sum(std::string* string, int n, ...)
{
	va_list args;
	va_start(args, n);
	std::string val_str[n];
	GetStrList(val_str, n, args);
	va_end(args);

	*string = Sum(n, val_str);
}

void Sum(std::string& string, int args, const std::string* tablica)
{
	string = Sum(args, tablica);
}
void Sum(std::string& string, int n, ...)
{
	va_list args;
	va_start(args, n);
	std::string val_str[n];
	GetStrList(val_str, n, args);
	va_end(args);

	string = Sum(n, val_str);
}
std::string AddZero(std::string liczba, int n)
{
	if (n == 0)
	{
		return liczba;
	}
	liczba = liczba + '0';
	return AddZero(liczba, --n);
}
void Multiply(std::string liczba1, std::string liczba2, std::string* tablica,int size, std::string wynik="", int i = 0, int j = 0, int carry = 0)
{
	
	wynik = (char)((((liczba1[size - 1 - j] - '0') * (liczba2[size - 1 - i] - '0') + carry) % 10) + '0') + wynik;
	carry = ((liczba1[size - 1 - j] - '0') * (liczba2[size - 1 - i] - '0') + carry) / 10;

	if (i == size - 1)
	{
		if (carry != 0)
		{
			wynik = char(carry + '0') + wynik;

		}

		wynik = AddZero(wynik, j);

		*(tablica+j) = wynik;
		//reset
		carry = 0;
		wynik = "";
		j++;
		i = -1;
		if (j == size)
		{
			return;
		}
	}

	Multiply(liczba1, liczba2,tablica,size, wynik, ++i,j, carry);



}
std::string MultForCoffe(int args, const std::string* tablica, int i = 0, std::string string = "", int znak = 1)
{


	std::string liczba1;
	int sign1;
	int sign2;
	if (i == 0)
	{
		sign1 = Positivity(tablica[i]);
		liczba1 = Parse(tablica[i]);
	}
	else
	{
		sign1 = znak;
		liczba1 = string;
	}
	std::string liczba2 = Parse(tablica[i + 1]);




	sign2 = Positivity(tablica[i + 1]);

	/////////////////////////////////////////////////
	if (Bigger(liczba1, liczba2) == 1)
	{

		liczba2 = Padding(liczba2, liczba1.size() - liczba2.size());

	}
	else if (Bigger(liczba1, liczba2) == 2)
	{

		liczba1 = Padding(liczba1, liczba2.size() - liczba1.size());
	}
	////////////////////////////////////////////////////
	int size = liczba1.size();



	znak = sign1 * sign2;
	std::string tab[size];


	
	Multiply(liczba1, liczba2, tab, size);


	if (size > 1)
	{
		string = Sum(size, tab);
	}
	else
	{
		string = tab[0];
	}
	



	if (i == args - 2)
	{
	
		string = Parse(string);
		string = MakeSigned(string, znak);
		if (string == "-0")
		{
			string = '0';
		}
		return string;
	}

	return MultForCoffe(args, tablica, ++i, string, znak);


}
std::string Mult(int args, const std::string* tablica)
{
	return MultForCoffe(args, tablica);


}

std::string Mult(int n, ...)
{
	va_list args;
	va_start(args, n);
	std::string val_str[n];
	GetStrList(val_str, n, args);
	va_end(args);

	return Mult(n, val_str);
}
//std::string Mult(int args, const std::string* tablica, int i = 0, std::string string = "", int znak = 1)
void Mult(std::string* string, int args, const std::string* tablica)
{
	*string = Mult(args, tablica);
}
void Mult(std::string* string, int n, ...)
{
	va_list args;
	va_start(args, n);
	std::string val_str[n];
	GetStrList(val_str, n, args);
	va_end(args);

	*string = Mult(n, val_str);
}
void Mult(std::string& string, int args, const std::string* tablica)
{
	string = Mult(args, tablica);
}
void Mult(std::string& string, int n, ...)
{
	va_list args;
	va_start(args, n);
	std::string val_str[n];
	GetStrList(val_str, n, args);
	va_end(args);

	string = Mult(n, val_str);
}

std::string Operation(std::string(*fun)(int, const std::string*), int args, const std::string* tablica)
{
	return fun(args, tablica);
}
std::string Operation(std::string(*fun)(int, const std::string*), int n, ...)
{
	va_list args;
	va_start(args, n);
	std::string val_str[n];
	GetStrList(val_str, n, args);
	va_end(args);
	return fun(n, val_str);
}
void Operation(std::string* string, std::string(*fun)(int, const std::string*), int n, ...)
{
	va_list args;
	va_start(args, n);
	std::string val_str[n];
	GetStrList(val_str, n, args);
	va_end(args);
	*string = fun(n, val_str);
}
void Operation(std::string* string, std::string(*fun)(int, const std::string*), int args, const std::string* tablica)
{
	*string = fun(args, tablica);
}
void Operation(std::string& string, void (*fun)(std::string*, int, const std::string*), int args, const std::string* tablica)
{
	fun(&string, args, tablica);
}
void Operation(std::string& string, void (*fun)(std::string*, int, const std::string*), int n, ...)
{
	va_list args;
	va_start(args, n);
	std::string val_str[n];
	GetStrList(val_str, n, args);
	va_end(args);
	fun(&string,n, val_str);
}






