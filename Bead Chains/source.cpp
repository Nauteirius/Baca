
#include<iostream>
#include "memory_check.h"

struct Koral;
struct Dowiazania
{
	Dowiazania()
	{
		this->next = NULL;
		this->link = NULL;
	}

	~Dowiazania()
	{
		this->link = NULL;
		this->next = NULL;
	}

	Koral* link;
	Dowiazania* next;
	int idk; // id korala do którego idzie polaczenie
	char id1, id2, id3; // id sznura do ktorego idzie polaczenie
};


struct Koral
{
	Koral()
	{
		this->next = NULL;
		this->head = NULL;
	}

	~Koral()
	{
		Dowiazania* dowiazPointer;
		Dowiazania* dowiazPointerNext;
		dowiazPointer = this->head;
		dowiazPointerNext;
		while (dowiazPointer!= NULL)
		{
			dowiazPointerNext = dowiazPointer->next;
			delete dowiazPointer;
			dowiazPointer = dowiazPointerNext;
		}
	
	}
	int idK;
	Koral* next;
	Dowiazania dowiazania;
	Dowiazania* head;
	//lista dowiazan;
};

struct Sznur
{
	Sznur()
	{
		this->head = NULL;
		this->next = NULL;
	}

	~Sznur()
	{
		this->head = NULL;
		this->next = NULL;
	}
	Koral* head;
	Sznur* next;

	char IdS1;
	char IdS2;
	char IdS3;

};


//_MemoryCheck
struct Lista
{
	Lista()
	{
		this->head = NULL;
	}
	Sznur* head;
};




Sznur* ZnajdzSznur(Lista* lista, char id1,char id2, char id3)
{
	Sznur* sznurPointer;
	
	sznurPointer = lista->head;
	//std::cout << "Lista head: " << lista->head << std::endl;

	//std::cout << "Szukane id: " << id1 << id2 << id3 << std::endl;
	while (sznurPointer != NULL)
	{
		//std::cout << "Obecne id: " << sznurPointer->IdS1 << sznurPointer->IdS2 << sznurPointer->IdS3 << std::endl;
		if (sznurPointer->IdS1 == id1 && sznurPointer->IdS2 == id2 && sznurPointer->IdS3 == id3)
		{
			return sznurPointer;
		}

		sznurPointer = sznurPointer->next;
	}
	//std::cout << "Nie znalazlo"<<std::endl;

}

Koral* ZnajdzKoral(Lista* lista, Sznur* sznurPointer, int idk)
{
	Koral* koralPointer;

	koralPointer = sznurPointer->head;
	while (koralPointer != NULL)
	{
		if (koralPointer->idK == idk)
		{
			return koralPointer;
		}
		koralPointer = koralPointer->next;
	}
}

int PorownajId(char id1, char id2, char id3, char idA, char idB, char idC) // lewy do prawego, mniejszy 0 wiekszy 1 remis 2
{
	if (id1 > idA)
	{
		return 1;
	}
	else if (id1 < idA)
	{
		return 0;
	}
	else if (id1 == idA)
	{
		if (id2 > idB)
		{
			return 1;
		}
		else if (id2 < idB)
		{
			return 0;
		}
		else if (id2 == idB)
		{

			if (id3 > idC)
			{
				return 1;
			}
			else if (id3 < idC)
			{
				return 0;
			}
			else if (id3 == idC)
			{
				return 2;
			}

		}
	}


}

void DodajDowiazania(Lista* lista,Koral* koralPointer,char id1,char id2, char id3, int idk, Koral* link = NULL)
{
	Dowiazania* dowiazPointer;
	Dowiazania* dowiazPointerPrev;
	Dowiazania* newDowiazanie;
	int found;
	dowiazPointer = koralPointer->head;
	while (dowiazPointer != NULL)
	{//if id sznura pointera mniejsze LUB id sznura rowne AND id korala <=
		if ((PorownajId(dowiazPointer->id1, dowiazPointer->id2, dowiazPointer->id3, id1, id2, id3) == 0) ||
			(PorownajId(dowiazPointer->id1, dowiazPointer->id2, dowiazPointer->id3, id1, id2, id3) == 2 && dowiazPointer->idk <= idk))
		{
			dowiazPointerPrev = dowiazPointer;
			dowiazPointer = dowiazPointer->next;
		}
		else
		{
			//found == 1;
			break;
		}

	}

	newDowiazanie = new Dowiazania();
	newDowiazanie->id1 = id1;
	newDowiazanie->id2 = id2;
	newDowiazanie->id3 = id3;
	newDowiazanie->idk = idk;
	newDowiazanie->next = dowiazPointer; // next
	newDowiazanie->link = link;
	if (dowiazPointer == koralPointer->head)//prev
	{
		koralPointer->head = newDowiazanie;
	}
	else
	{
		dowiazPointerPrev->next = newDowiazanie;
	}
}

void UsunDowiazanie(Koral* koralPointer, Koral* koralPointer2)
{
	Dowiazania* dowiazPointer;
	Dowiazania* dowiazPointerPrev;

	dowiazPointer = koralPointer->head;
	while (dowiazPointer != NULL)
	{
		if (dowiazPointer->link == koralPointer2) /////////////////////////
		{


			if (dowiazPointer != koralPointer->head)
			{
				dowiazPointerPrev->next = dowiazPointer->next;
			}
			else
			{

				koralPointer->head = dowiazPointer->next;
			}
			
			dowiazPointer->link = NULL;
			delete dowiazPointer;
			break;
		}

		dowiazPointerPrev = dowiazPointer;
		dowiazPointer = dowiazPointer->next;
	}

}

void UsunDowiazania(Lista* lista, Koral* koralUsuwany);
void UsunKoral(Lista* lista, int idk, char id1, char id2, char id3)
{
	Sznur* sznurPointer;
	Koral* koralPointer;
	Koral* koralPointerPrev;
	sznurPointer = ZnajdzSznur(lista, id1, id2, id3);
	koralPointer = sznurPointer->head;
	while (koralPointer != NULL)
	{
		if (koralPointer->idK == idk)
		{
			if (koralPointer != sznurPointer->head)
			{
				koralPointerPrev->next = koralPointer->next;
			}
			else
			{
				sznurPointer->head = koralPointer->next;
			}
			UsunDowiazania(lista, koralPointer);
			delete koralPointer;
			break;
		}



		koralPointerPrev = koralPointer;
		koralPointer = koralPointer->next;
	}

}

void DodajKoral(Lista* lista, int idk, char id1, char id2, char id3)
{
	int found = 0;
	Sznur* sznurPointer;
	Koral* koralPointer;
	Koral* newKoral;
	Koral* koralPointerPrev;
	//std::cout << "flag" << std::endl;
	sznurPointer = ZnajdzSznur(lista, id1, id2, id3);
	//std::cout << sznurPointer<<std::endl;
	koralPointer = sznurPointer->head;

	while (koralPointer != NULL)
	{
		if (koralPointer->idK < idk)
		{
			koralPointerPrev = koralPointer;
			koralPointer = koralPointer->next;
		}
		else
		{
			//found == 1;
			break;
		}

	}
	newKoral = new Koral;
	newKoral->idK = idk;
	newKoral->next = NULL;
	if (koralPointer == sznurPointer->head)//jesli nie ma poprzednika
	{
		sznurPointer->head = newKoral;
	}
	else
	{
		koralPointerPrev->next = newKoral;
	}
	newKoral->next = koralPointer; //koralPointer to pierwszy element wiekszy(lub rowny) ALBO NULL


}

void UsunDowiazania(Lista* lista,Koral* koralUsuwany)
{
	Sznur* sznurPointer;
	Koral* kolarPointer;
	Dowiazania* dowiazPointer;
	Dowiazania* dowiazPointerPrev;
	sznurPointer = lista->head;
	while (sznurPointer != NULL)
	{
		kolarPointer = sznurPointer->head;
		while (kolarPointer != NULL)
		{/////////////////////////////////////////////////////
			dowiazPointer = kolarPointer->head;
			while (dowiazPointer != NULL)
			{
				if (dowiazPointer->link == koralUsuwany)
				{
					if (dowiazPointer != kolarPointer->head)
					{
						dowiazPointerPrev->next = dowiazPointer->next;
					}
					else{
						kolarPointer->head = dowiazPointer->next;
					}

					dowiazPointer->link = NULL;
					delete dowiazPointer;
					break;
				}

				dowiazPointerPrev = dowiazPointer;
				dowiazPointer = dowiazPointer->next;
			}//////////////////////////////////////////////////////////////

			kolarPointer = kolarPointer->next;
		}




		sznurPointer = sznurPointer->next;
	}
}


void PrzeniesKoral(Lista* lista, int idk, char id1, char id2, char id3, char idA, char idB, char idC)//Na koniec drugiego korala
{
	Sznur* sznurPointer;
	Koral* koralPointer;
	Koral* koralPointerUltimate;
	Koral* koralPointerPrev;
	sznurPointer = ZnajdzSznur(lista, id1, id2, id3);
	koralPointer = sznurPointer->head;
	while(koralPointer != NULL)
	{
		if (koralPointer->idK == idk)
		{
			if (koralPointer != sznurPointer->head)
			{
				koralPointerPrev->next = koralPointer->next;
			}
			else
			{
				sznurPointer->head = koralPointer->next;
			}

			koralPointerUltimate = koralPointer;//czy tak mozna
			break;
		}



		koralPointerPrev = koralPointer;
		koralPointer = koralPointer->next;

	}
	////////////////////////////// "usunieto///

	sznurPointer = ZnajdzSznur(lista, idA, idB, idC);
	koralPointer = sznurPointer->head;
	while (koralPointer != NULL)
	{/////////////////////////////////////////////////////////////// Updated:
		if (koralPointer->idK < koralPointerUltimate->idK)
		{
			koralPointerPrev = koralPointer;
			koralPointer = koralPointer->next;
		}
		else
		{
			//found =1
			break;
		}
	}
	// czy na pewno?
	if (koralPointer == sznurPointer->head)
	{
		sznurPointer->head = koralPointerUltimate;
	}
	else
	{
		koralPointerPrev->next = koralPointerUltimate;
	}
	koralPointerUltimate->next = koralPointer;
	

}

void UsunSznur(Lista* lista, char id1, char id2, char id3)
{
	Sznur* sznurPointer;
	Sznur* sznurPointerPrev;
	Koral* kolarPointer;
	Koral* kolarPointerPrev;
	sznurPointer = ZnajdzSznur(lista, id1, id2, id3);





	sznurPointer = lista->head;
	while (sznurPointer != NULL)
	{

		if (sznurPointer->IdS1 == id1 && sznurPointer->IdS2 == id2 && sznurPointer->IdS3 == id3)
		{
			if (sznurPointer == lista->head)
			{
				lista->head = sznurPointer->next;
			}
			else
			{
				sznurPointerPrev->next = sznurPointer->next;
			}

			kolarPointer = sznurPointer->head;
			while (kolarPointer != NULL)
			{

				kolarPointerPrev = kolarPointer;

				kolarPointer = kolarPointer->next;
				//std::cout << "flag 1"<<std::endl;
				UsunDowiazania(lista, kolarPointerPrev);
				//std::cout << "flag 2";
				delete kolarPointerPrev;

			}

			delete sznurPointer;
			break;
		}
		sznurPointerPrev = sznurPointer;
		sznurPointer = sznurPointer->next;
	}

}


void Wyswietl(Lista* lista)
{
	Sznur* sznurPointer;
	Koral* koralPointer;
	Dowiazania* dowiazPointer;

	sznurPointer = lista->head;
	while (sznurPointer != NULL)
	{
		std::cout << sznurPointer->IdS1 << sznurPointer->IdS2 << sznurPointer->IdS3 << " ";

		koralPointer = sznurPointer->head;
		while (koralPointer != NULL)
		{
			std::cout << std::endl << koralPointer->idK << " ";

			dowiazPointer = koralPointer->head;
			while (dowiazPointer != NULL)
			{
				std::cout << dowiazPointer->id1 << dowiazPointer->id2 << dowiazPointer->id3 << " " << dowiazPointer->idk << " ";//Uwaga!/////// <<

				dowiazPointer = dowiazPointer->next;
			}



			koralPointer = koralPointer->next;
		}




		std::cout << std::endl;
		sznurPointer = sznurPointer->next;
	}
}

int main()
{

	Lista lista;
	Sznur* sznurPointer;
	Sznur* sznurPointerPrev;
	Sznur* sznurPointerTemp;
	Sznur* newSznur;
	Sznur* sznurPointer2;
	Lista* listaPointer = &lista;
	Koral* koralPointer;
	Koral* koralPointer2;

	char command;
	// char* command; Jak ustalic wielkosc
	char id1;
	char id2;
	char id3;
	char idA;
	char idB;
	char idC;
	int idk;
	int idk2;
	while (true)
	{
		//czyszczenie tablicy znaków. 



		// *(command + 4) == 0;




		std::cin >> command;
		if (command == 'S')
		{
			std::cin >> id1>> id2>> id3;


			//NowySznurNaKoniec()

			sznurPointer = lista.head;
			while (sznurPointer != NULL)
			{

				if (PorownajId(sznurPointer->IdS1, sznurPointer->IdS2, sznurPointer->IdS3, id1, id2, id3)==0)
				{
					sznurPointerPrev = sznurPointer;
					sznurPointer = sznurPointer->next;
				}
				else
				{
					break;
				}
			}


			newSznur = new Sznur;
			newSznur->IdS1 = id1;
			newSznur->IdS2 = id2;
			newSznur->IdS3 = id3;
			newSznur->head = NULL;
			newSznur->next = sznurPointer;
			if (lista.head == sznurPointer)
			{
				lista.head = newSznur;
			}
			else
			{
				sznurPointerPrev->next = newSznur;
			}




		}


		if (command == 'B')
		{
			std::cin >> idk >> id1>>id2>>id3;
			//idk = int(command1 - '0') + int(command2 - '0') * 10 + int(command3 - '0') * 100;

			DodajKoral(listaPointer, idk, id1, id2, id3);

		}


		if (command == 'L')
		{
			std::cin >> idk >> id1 >> id2 >> id3 >> idk2 >> idA >> idB >> idC;

			sznurPointer = ZnajdzSznur(listaPointer, id1, id2, id3);

			koralPointer = ZnajdzKoral(listaPointer, sznurPointer, idk);

			sznurPointer2 = ZnajdzSznur(listaPointer, idA, idB, idC);
			koralPointer2 = ZnajdzKoral(listaPointer, sznurPointer2, idk2);
			DodajDowiazania(listaPointer, koralPointer, idA, idB, idC, idk2, koralPointer2);


		}

		if (command == 'U')
		{
			std::cin >> idk >> id1 >> id2 >> id3 >> idk2 >> idA >> idB >> idC;
			sznurPointer = ZnajdzSznur(listaPointer, id1, id2, id3);
			koralPointer = ZnajdzKoral(listaPointer, sznurPointer, idk);

			sznurPointer2 = ZnajdzSznur(listaPointer, idA, idB, idC);
			koralPointer2 = ZnajdzKoral(listaPointer, sznurPointer2, idk2);
			UsunDowiazanie(koralPointer, koralPointer2);

		}

		if (command == 'D')
		{
			std::cin >> idk >> id1 >> id2 >> id3;
			UsunKoral(listaPointer, idk, id1, id2, id3);
		}

		if (command == 'M')
		{
			std::cin >> idk >> id1 >> id2 >> id3 >> idA >> idB >> idC;


			PrzeniesKoral(listaPointer, idk, id1, id2, id3, idA, idB, idC);



		}

		if (command == 'R')
		{
			std::cin >> id1 >> id2 >> id3;

			UsunSznur(listaPointer, id1, id2, id3);
		}

		if (command == 'P')
		{
			Wyswietl(listaPointer);
		}

		if (command == 'F')
		{
			sznurPointer = lista.head;
			while (sznurPointer != NULL)
			{
				sznurPointerTemp = sznurPointer->next;
				UsunSznur(listaPointer, sznurPointer->IdS1, sznurPointer->IdS2, sznurPointer->IdS3);

				sznurPointer = sznurPointerTemp;
			}


			break;
		}
	}
	_MemoryCheck();
}