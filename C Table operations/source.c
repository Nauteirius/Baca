#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AddRow(unsigned short* rowCount,int*** array2dPointer,unsigned short w,int pos)
{
	int** array2d = *array2dPointer;

	*rowCount = *rowCount + 1;//inkrementuje sie, to wazne w kontekscie pos

	size_t size = *rowCount * sizeof(int*);
	//printf("Weszlo \n");
	/*int***/ array2d = (int**)realloc(array2d, size); // ustalamy ilosc wierszy //*rowCount * sizeof(int*)

	//printf("Weszlo2 \n");
	*(array2d + *rowCount-1) = (int*)malloc(((w+1) * sizeof(int)));//alokowanie w+1 kolumn w nowym wierszu
	*(*(array2d + *rowCount - 1)+0) = (int)w; // pierwszy element nowego wiersza;
	int i = 1;
	int var;
	while (i<=w)//wypelnianie pozostalych kolumn w wierszu
	{
		scanf("%d", &var);
		//printf("Wczytalo: %d \n",var);
		*(*(array2d + *rowCount - 1) + i) = var;
		i++;
	}

	//nasz wiersz ma byæ na X miejscu
	i = *rowCount-1; // liczba przesuniec w górê
	int* tmp;


	while (i >pos)
	{
		tmp = *(array2d + i);
		*(array2d + i) = *(array2d + i - 1);
		*(array2d + i - 1) = tmp;

		i--;
	}


	*array2dPointer = array2d;


}

void RemoveRow(unsigned short* rowCount, int*** array2dPointer, int pos)
{	
	int** array2d = *(array2dPointer);
	if (*rowCount == 0 || pos>=*rowCount)
	{
		return;
	}
	int i;
	//jesli nie jest z brzegu przesun na koniec i potem usun
	i = pos;
	int* tmp;
	while (i< *rowCount - 1)
	{
		tmp = *(array2d + i);
		*(array2d + i) = *(array2d + i + 1);
		*(array2d + i + 1) = tmp;

		i++;
	}
	free(*(array2d + *rowCount - 1));
	*rowCount= *rowCount -1;

	*(array2dPointer)= array2d;
}
//void RemoveColumn(unsigned short* rowCount, int*** array2dPointer, int pos
void RemoveColumn(unsigned short* rowCount, int*** array2dPointer, int pos)
{
	int** array2d = *(array2dPointer);


	int i = 0;
	int len;//dlugosc wiersza
	int tmp;
	int tmp2;
	int range = pos + 1;//pierwsze miejsce jest ignorowane;
	int var;
	while (i < *rowCount)//bedzie sie zmieniac przy usuwaniu wierszy
	{
		len = *(*(array2d + i));//pierwsza wartosc w wierszu
		range = pos + 1;


		if (pos >= len)//nie wykona sie
		{
			i++;
			continue;
		}
		else if (len == 1)
		{
			RemoveRow(rowCount, &array2d, i);//rowCount zmiejszy siê o 1
			continue;//znowu sprawdzimy wiersz z tym samym indeksem
		}
		else if (pos != -1)
		{
			//usuwamy nieostatni

			while (range < len)//pos=0 range =1 len= 1 
			{
				tmp = *(*(array2d + i) + range);
				*(*(array2d + i) + range) = *(*(array2d + i) + range + 1);
				*(*(array2d + i) + range + 1) = tmp;

				range++;
			}
		}

		*(array2d + i) = (int*)realloc(*(array2d + i), (*(*(array2d + i)) + 1 - 1) * sizeof(int)); //zmiejsz rozmiar o 1
		*(*(array2d + i)) = *(*(array2d + i)) - 1;
		len--; // to sie nie przyda
		
		i++;
	}
	*(array2dPointer) = array2d;

}

void RemoveBlock(unsigned short* rowCount, int*** array2dPointer, int r, int h, int pos, int w)//upgraded removeCol
{ //h=-1 do konca
	//w times
	int** array2d = *(array2dPointer);

	int untilEnd = 0;
	int i = r; // start of removing
	//if (h == -1)//relic of past
	//{
	//	untilEnd = 1;
	//}
	int len;//dlugosc wiersza
	int tmp;
	int tmp2;
	int range = pos + 1;//pierwsze miejsce jest ignorowane;
	int var;
	while (i < *rowCount)//bedzie sie zmieniac przy usuwaniu wierszy
	{
		int coltimes = w; //column removing counter
		h--;
		if (untilEnd==0 && h<0)
		{
			break;
		}
		len = *(*(array2d + i));//pierwsza wartosc w wierszu
		range = pos + 1;


		if (pos >= len)//nie wykona sie
		{
			i++;
			continue;
		}
		else if (len <= coltimes && pos==0)
		{
			RemoveRow(rowCount, &array2d, i);//rowCount zmiejszy siê o 1
			continue;//znowu sprawdzimy wiersz z tym samym indeksem
		}
		else if (pos != -1)
		{
			//update coltimes
			if (len - pos < coltimes)
			{
				coltimes = len - pos;
			}
			int k = 0;
			for (k = 0; k < coltimes; k++)//POWINNO DZIALAC
			{
				range = pos + 1;
				while (range < len)//pos=0 range =1 len= 1 
				{
					tmp = *(*(array2d + i) + range);
					*(*(array2d + i) + range) = *(*(array2d + i) + range + 1);
					*(*(array2d + i) + range + 1) = tmp;

					range++;
				}
				len--;
			}
			//usuwamy nieostatni


		}

		*(array2d + i) = (int*)realloc(*(array2d + i), (*(*(array2d + i)) + 1 - coltimes) * sizeof(int)); //zmiejsz rozmiar o coltimes, NIE ZAWSZE
		*(*(array2d + i)) = *(*(array2d + i)) - coltimes;
		len=len - coltimes; // to sie nie przyda

		i++;
	}
	*(array2dPointer) = array2d;

}

void AddBlock(unsigned short* rowCount, int*** array2dPointer, int r, int h, int pos, int w) //h first rows
{//pos ==-1  dodaj na koniec
	int** array2d = *(array2dPointer);
	if (r > *rowCount)
	{
		r = *rowCount;//dodawanie na koniec
	}
	int extraRows = r+h - *rowCount;
	int stop;
	if (r + h > *rowCount)
	{
		stop = *rowCount;//ile razy
	}
	else
	{
		stop = r+h;
	}
	int i = r;//wiersz od ktorego zaczynamy
	int len;//dlugosc wiersza
	int tmp;
	int tmp2;
	int range = pos + 1;//pierwsze miejsce jest ignorowane;
	int var;
	while (i < stop)
	{
		len = *(*(array2d + i));//pierwsza wartosc w wierszu
		*(array2d + i) = (int*)realloc(*(array2d + i), (*(*(array2d + i)) + 1 + w) * sizeof(int)); //zwieksz kolumne o w;
		*(*(array2d + i)) = *(*(array2d + i)) + w;
		int k = 0;
		for (k = 0; k < w; k++)
		{
			len++;
			scanf("%d", &var);
			range = pos +k +1;//miejsce zerowe to ilosc kolumn, za kazdym razem wstawiamy w kolejne miejsce

			tmp = var;
			if (pos == -1 || pos >= len)//dodaj na koniec
			{
				*(*(array2d + i) + len) = tmp;
			}
			else//dodaj na podana pozycje
			{
				while (range <= len)//pos=0 range =1 len= 1 
				{
					if (range + 1 > len)//to bedzie ostatnia iteracja
					{
						*(*(array2d + i) + range) = tmp;//bo to dodatkowo zrobione miejsce
					}
					else
					{
						tmp2 = *(*(array2d + i) + range);
						*(*(array2d + i) + range) = tmp;
						tmp = tmp2;
					}



					//sprawdzenie ostatniego warunku
					//tmp = *(*(array2d + i) + range);
					//*(*(array2d + i) + range) = var;



					range++;
				}
			}
		}




		i++;
	}
	while (extraRows > 0)
	{
		AddRow(rowCount, &array2d, w, *rowCount);//na koniec
		extraRows--;
	}

	*(array2dPointer) = array2d;

}

void AddColumn(unsigned short* rowCount, int*** array2dPointer, unsigned short h, int pos) //h first rows
{//pos ==-1  dodaj na koniec
	int** array2d = *(array2dPointer);

	int extraRows = h - *rowCount;
	int stop;
	if (h > *rowCount)
	{
		stop = *rowCount;//ile razy
	}
	else
	{
		stop = h;
	}
	int i = 0;
	int len;//dlugosc wiersza
	int tmp;
	int tmp2;
	int range = pos + 1;//pierwsze miejsce jest ignorowane;
	int var;
	while (i < stop)
	{
		len = *(*(array2d + i));//pierwsza wartosc w wierszu
		*(array2d + i) = (int*)realloc(*(array2d + i), (*(*(array2d + i)) +1+1) * sizeof(int)); //zwieksz kolumne o 1;
		*(*(array2d + i)) = *(*(array2d + i)) + 1;
		len++;
		scanf("%d", &var);
		range = pos + 1;//miejsce zerowe to ilosc kolumn

		tmp = var;
		if (pos == -1 || pos>=len)//dodaj na koniec
		{
			*(*(array2d + i) + len) = tmp;
		}
		else//dodaj na podana pozycje
		{
			while (range <= len)//pos=0 range =1 len= 1
			{
				if (range + 1 > len)//to bedzie ostatnia iteracja
				{
					*(*(array2d + i) + range) = tmp;//bo to dodatkowo zrobione miejsce
				}
				else
				{
					tmp2 = *(*(array2d + i) + range);
					*(*(array2d + i) + range) = tmp;
					tmp = tmp2;
				}



				//sprawdzenie ostatniego warunku
				//tmp = *(*(array2d + i) + range);
				//*(*(array2d + i) + range) = var;



				range++;
			}
		}



		i++;
	}
	while (extraRows > 0)
	{
		AddRow(rowCount, &array2d, 1, *rowCount);//na koniec
		extraRows--;
	}

	*(array2dPointer) = array2d;

}

void Prt(unsigned short* rowCount, int*** array2dPointer)
{
	int** array2d= *(array2dPointer);
	int i = 0;
	int j = 0;
	//printf("W print \n");
	printf("%hu",*rowCount);
	while (i < *rowCount)
	{
		//printf("Dzilawprint");
		printf("\n%hu", **(array2d + i));
		j = 1;
		while (j<= **(array2d + i))
		{ 
			//printf("Dzilawprintwewnetrznapetla");
			printf(" %d",*(*(array2d+i)+j));
			j++;
		}
		i++;
	}
	printf("\n");
	*(array2dPointer) = array2d;
}

void SwitchRow(unsigned short* rowCount, int*** array2dPointer, int a, int b)
{

	int** array2d = *(array2dPointer);
	if (b > *rowCount - 1 || a > *rowCount - 1 || a==b)
	{
		//printf("zly indeks wowcount \n");
		return;

	}
	
	int* tmp;
	int i;
	int j;
	if (a < b)
	{
		i = a;
		j = b;
	}
	else
	{
		i = b;
		j = a;
	}

	//while (i < j)
	//{
		tmp = *(array2d + i);
		*(array2d + i) = *(array2d + j);
		*(array2d + j) = tmp;

		//i++;
	//}

	*(array2dPointer) = array2d;
}

void SwitchCol(unsigned short* rowCount, int*** array2dPointer, int a, int b)
{
	int** array2d = *(array2dPointer);

	int colNum;
	int i = 0;
	int tmp;
	if (b == a)
	{
		return;
	}
	else if (b < a)//a zawsze bedzie mniejsze
	{
		tmp = a;
		a = b;
		b = tmp;
	}

	int range = a + 1;//bo zerowa jest zarezerwowana
	for (i = 0; i < *rowCount; i++)
	{
		colNum = **((array2d + i));
		if (a >= colNum || b >= colNum)
		{
			continue;
		}

		//wymiana

		tmp = *(*(array2d + i) + range);
		*(*(array2d + i) + range) = *(*(array2d + i) + b + 1);
		*(*(array2d + i) + b + 1) = tmp;


	}

	*(array2dPointer) = array2d;
}

unsigned short bigEndiantUs(unsigned short value)
{
	unsigned short result = (value >> 8) | (value << 8);
	return result;
}
int bigEndiantInt(int value)
{
	int result = ((value >> 24) & 0xff) |
		((value << 8) & 0xff0000) |
		((value >> 8) & 0xff00) |
		((value << 24) & 0xff000000);
	return result;
}

void SaveArray(unsigned short* rowCount, int*** array2dPointer,char* filename)
{
	int** array2d = *(array2dPointer);
	FILE* savefile = fopen(filename, "wb");
	fprintf(savefile, "%hu\n", *rowCount);//zapisanie liczby wierszy
	int i=0;
	int j=1;
	unsigned short colNum;
	int var;
	for (i = 0; i < *rowCount; i++)
	{

		//printf("Dzilawprint");
		colNum = (unsigned short)**((array2d + i));
		colNum = bigEndiantUs(colNum);
		fwrite(&colNum, sizeof(unsigned short), 1, savefile); //2 = sizeof(unsigned short)
		j = 1;
		while (j <= **(array2d + i))
		{
			//printf("Dzilawprintwewnetrznapetla");
			var = (int)*(*(array2d + i) + j);
			var = bigEndiantInt(var);
			fwrite(&var, sizeof(int), 1, savefile);
			j++;
		}
		//i++;


	}

	fclose(savefile);
	*(array2dPointer) = array2d;

}

void Clear(unsigned short* rowCount, int*** array2dPointer)
{
	int** array2d = *(array2dPointer);
	int i = 0;
	int j = 0;
	for (i = 0; i < *rowCount; i++)
	{
		free(* (array2d + i));
	}
	*rowCount = 0;
	*(array2dPointer) = array2d;
}
void LoadArray(unsigned short* rowCount, int*** array2dPointer, char* filename)
{
	int** array2d = *(array2dPointer);
	Clear(rowCount, &array2d);//clearing array

	FILE* loadfile = fopen(filename, "rb");

	unsigned short colNum;
	int var;
	fscanf(loadfile,"%hu", rowCount);
	//fscanf(loadfile, "%c");
	char nothing;
	fread(&nothing,1, 1, loadfile);
	size_t size = *rowCount * sizeof(int*);
	/*int***/ array2d = (int**)realloc(array2d,size); // ustalamy ilosc wierszy //*rowCount * sizeof(int*)

	int i = 0;
	int j = 1;

	for (i = 0; i < *rowCount; i++)
	{
		fread(&colNum, 2, 1, loadfile); //2 = sizeof(unsigned short)
		colNum = bigEndiantUs(colNum);
		*(array2d + i) = (int*)malloc(((colNum + 1) * sizeof(int)));//alokowanie colNum+1 kolumn w nowym wierszu

		**((array2d + i)) = (int)colNum;//pierwszy element nowego wiersza

		j = 1;
		while (j <= **(array2d + i))
		{
			//printf("Dzilawprintwewnetrznapetla");
			fread(&var, 4, 1, loadfile); //2 = sizeof(unsigned short)
			var = bigEndiantInt(var);

			*(*(array2d + i) + j)=var;

			j++;
		}
		//i++;

	}


	fclose(loadfile);
	*(array2dPointer) = array2d;
}

int main()
{
	unsigned short w;
	int r;
	int h;
	int c;
	unsigned short rowCount = 0;
	int looper = 0;
	char* name = malloc(20 * sizeof(char));
	int** array2d = (int**)malloc((0 * sizeof(int*)));//inicjalizacja pustej tablicy
	//*(array2d) = (int*)malloc((0 * sizeof(int))); 
	char* operation = (char*)malloc(4 * sizeof(char));//tablica znaków
	*(operation+0) = 'a'; // jakas wartosc na poczatek, jest potrzebna?
	*(operation+1) = 'a';
	*(operation+2) = 'a';
	while (*(operation) != 'E' || *(operation+1) != 'N' || *(operation + 2) != 'D')
	{
		scanf(" %c", (operation));
		scanf(" %c", (operation + 1));
		scanf(" %c", (operation + 2));

		if (*(operation) == 'A' && *(operation+1) == 'F' && *(operation + 2) == 'R')
		{
			scanf("%hu", &w);
			AddRow(&rowCount, &array2d, w, 0);
		}

		if (*(operation) == 'A' && *(operation+1) == 'L' && *(operation + 2) == 'R')
		{
			scanf("%hu", &w);
			AddRow(&rowCount, &array2d, w, rowCount);//rowCount - 1, ROW COUNT sie inkrementuje
		}

		if (*(operation) == 'A' && *(operation+1) == 'F' && *(operation + 2) == 'C')
		{
			scanf("%hu", &w);
			AddColumn(&rowCount, &array2d, w, 0);//na poczatek
		}

		if (*(operation) == 'A' && *(operation + 1) == 'L' && *(operation + 2) == 'C')
		{
			scanf("%hu", &w);
			AddColumn(&rowCount, &array2d, w, -1);//na koniec
		}

		if (*(operation) == 'I' && *(operation + 1) == 'B' && *(operation + 2) == 'R')
		{
			scanf("%i", &r);
			scanf("%hu", &w);

			if (r + 1 <= rowCount)
			{
				AddRow(&rowCount, &array2d, w, r);
			}
			looper = 0;
			while (looper < w)
			{
				scanf("%i", &r);
				looper++;
			}

		}

		if (*(operation) == 'I' && *(operation + 1) == 'A' && *(operation + 2) == 'R')
		{
		
			scanf("%i", &r);
			scanf("%hu", &w);
			if (r + 1 <= rowCount)
			{
				AddRow(&rowCount, &array2d, w, r+1);
			}
			looper = 0;
			while (looper < w)
			{
				scanf("%i", &r);
				looper++;
			}
		}

		if (*(operation) == 'I' && *(operation + 1) == 'B' && *(operation + 2) == 'C')
		{
		
			
			scanf("%i", &r);
			scanf("%hu", &w);
			AddColumn(&rowCount, &array2d, w, r);//na koniec
		}

		if (*(operation) == 'I' && *(operation + 1) == 'A' && *(operation + 2) == 'C')
		{
			
			scanf("%i", &r);
			scanf("%hu", &w);
			AddColumn(&rowCount, &array2d, w, r+1);//na koniec
		}

		if (*(operation) == 'S' && *(operation + 1) == 'W' && *(operation + 2) == 'R')
		{
			scanf("%hu", &w);
			scanf("%i", &r);
			SwitchRow(&rowCount, &array2d, w, r);//jest tam sprawdzanie
		}

		if (*(operation) == 'S' && *(operation + 1) == 'W' && *(operation + 2) == 'C')
		{
			scanf("%hu", &w);
			scanf("%i", &r);
			SwitchCol(&rowCount, &array2d, w, r);
		}

		if (*(operation) == 'D' && *(operation + 1) == 'F' && *(operation + 2) == 'R')
		{

			RemoveRow(&rowCount, &array2d, 0);//jest tam sprawdzanie
		}

		if (*(operation) == 'D' && *(operation + 1) == 'L' && *(operation + 2) == 'R')
		{

			RemoveRow(&rowCount, &array2d, rowCount-1);//jest tam sprawdzanie
		}

		if (*(operation) == 'D' && *(operation + 1) == 'F' && *(operation + 2) == 'C')
		{

			RemoveColumn(&rowCount, &array2d, 0);//jest tam sprawdzanie
		}
		if (*(operation) == 'D' && *(operation + 1) == 'L' && *(operation + 2) == 'C')
		{

			RemoveColumn(&rowCount, &array2d, -1);//jest tam sprawdzanie
		}

		if (*(operation) == 'R' && *(operation + 1) == 'M' && *(operation + 2) == 'R')
		{
			scanf("%hu", &w);
			RemoveRow(&rowCount, &array2d, w);//jest tam sprawdzanie
		}

		if (*(operation) == 'R' && *(operation + 1) == 'M' && *(operation + 2) == 'C')
		{
			scanf("%hu", &w);
			RemoveColumn(&rowCount, &array2d, w);//jest tam sprawdzanie
		}
		if (*(operation) == 'R' && *(operation + 1) == 'M' && *(operation + 2) == 'B')
		{
			scanf("%i", &r);
			scanf("%i", &h);
			scanf("%i", &c);
			scanf("%hu", &w);


			RemoveBlock(&rowCount, &array2d, r, h, c, w);
		}

		if (*(operation) == 'I' && *(operation + 1) == 'S' && *(operation + 2) == 'B')
		{
			scanf("%i", &r);
			scanf("%i", &c);
			scanf("%i", &h);
			scanf("%hu", &w);


			AddBlock(&rowCount, &array2d, r, h, c, w);
		}
		if (*(operation) == 'W' && *(operation + 1) == 'R' && *(operation + 2) == 'F')
		{
			scanf("%s", name);


			SaveArray(&rowCount, &array2d, name);
		}

		if (*(operation) == 'R' && *(operation + 1) == 'D' && *(operation + 2) == 'F')
		{
			scanf("%s", name);


			LoadArray(&rowCount, &array2d, name);
		}


		if (*(operation) == 'P' && *(operation + 1) == 'R' && *(operation + 2) == 'T')
		{
			Prt(&rowCount, &array2d);
		}


	}
	free(name);
	Clear(&rowCount, &array2d);
	free(array2d);
	return 0;
}
