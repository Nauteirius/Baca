//
#include <iostream>

long long totalGoods = 0;

struct Place
{
	unsigned short amount;
	char etiq[2];
};

struct Shelf
{
	Place slots[128];
	unsigned char amount;
};

struct Rack
{
	Shelf slots[128];
	unsigned char amount;
};

struct Warehouse
{
	Rack slots[128];
	unsigned char amount;
	Shelf handy_shelf;
};

struct Storage
{
	Warehouse slots[128];
	unsigned char amount;
	Rack handy_rack;
	Shelf handy_shelf;
};

Storage storage;

void Fill(unsigned short W, unsigned short R, unsigned short S, unsigned short P, unsigned short A)
{
	totalGoods = 0;
	/*
	storage.amount = W;
	storage.slots->amount = R;
	storage.slots->slots->amount = S;
	storage.slots->slots->slots->amount = P;
	storage.slots->slots->slots->slots->amount = A;
	storage.slots->slots->slots->slots->etiq[0] = 0;
	storage.slots->slots->slots->slots->etiq[1] = 0;
	//storage.slots->slots->slots->slots->etiq = '00';

	storage.slots->handy_shelf.amount = P;
	storage.slots->handy_shelf.slots->amount = A;
	storage.slots->handy_shelf.slots->etiq[0] = 0;
	storage.slots->handy_shelf.slots->etiq[1] = 0;

	storage.handy_shelf.amount = P;
	storage.handy_shelf.slots->amount = A;
	storage.handy_shelf.slots->etiq[0] = 0;
	storage.handy_shelf.slots->etiq[1] = 0;

	storage.handy_rack.amount = S;
	storage.handy_rack.slots->amount = P;
	storage.handy_rack.slots->slots->amount = A;
	storage.handy_rack.slots->slots->etiq[0] = 0;
	storage.handy_rack.slots->slots->etiq[1] = 0;
	*/

	storage.amount = W;
	for (int i = 0; i < storage.amount; i++)
	{
		storage.slots[i].amount = R;
		storage.slots[i].handy_shelf.amount = P;
		for (int l = 0; l < P; l++)
		{
			storage.slots[i].handy_shelf.slots[l].amount = A;
			storage.slots[i].handy_shelf.slots[l].etiq[0] = 0;
			storage.slots[i].handy_shelf.slots[l].etiq[1] = 0;
		}







		for (int j = 0; j < storage.slots[i].amount; j++)
		{
			storage.slots[i].slots[j].amount = S;
			for (int k = 0; k < storage.slots[i].slots[j].amount; k++)
			{
				storage.slots[i].slots[j].slots[k].amount = P;
				for (int l = 0; l < storage.slots[i].slots[j].slots[k].amount; l++)
				{
					storage.slots[i].slots[j].slots[k].slots[l].amount = A;
					storage.slots[i].slots[j].slots[k].slots[l].etiq[0] = 0;
					storage.slots[i].slots[j].slots[k].slots[l].etiq[1] = 0;
				}

			}
		}
	}

	storage.handy_shelf.amount = P;
	for (int l = 0; l < P; l++)
	{
		storage.handy_shelf.slots[l].amount = A;
		storage.handy_shelf.slots[l].etiq[0] = 0;
		storage.handy_shelf.slots[l].etiq[1] = 0;
	}

	storage.handy_rack.amount = S;
	for (int k = 0; k < S; k++)
	{
		storage.handy_rack.slots[k].amount = P;
		for (int l = 0; l < P; l++)
		{
			storage.handy_rack.slots[k].slots[l].amount = A;
			storage.handy_rack.slots[k].slots[l].etiq[0] = 0;
			storage.handy_rack.slots[k].slots[l].etiq[1] = 0;

		}
	}


	totalGoods = (long long)A * P * S * R * W + (long long)A * P * W + (long long)A * P * S + (long long)A * P;


}

void GetE()
{
	std::cout << totalGoods<<std::endl;
}

void GetW(unsigned short w)
{
	long long sum = 0;


	for (int j = 0; j < storage.slots[w].amount; j++) // regal
	{
		for (int k = 0; k < storage.slots[w].slots[j].amount; k++) // polka
		{
			for (int l = 0; l < storage.slots[w].slots[j].slots[k].amount; l++) // miejsce
			{
				sum += storage.slots[w].slots[j].slots[k].slots[l].amount;
			}
		}
	}

	for (int i = 0; i < storage.slots[w].handy_shelf.amount; i++)
	{
		sum += storage.slots[w].handy_shelf.slots[i].amount;
	}


	std::cout << sum << std::endl;
}

void GetRW(unsigned short w, unsigned short r)
{
	long long sum = 0;
	for (int k = 0; k < storage.slots[w].slots[r].amount; k++)
	{
		for (int l = 0; l < storage.slots[w].slots[r].slots[k].amount; l++)
		{
			sum += storage.slots[w].slots[r].slots[k].slots[l].amount;
		}
	}

	std::cout << sum << std::endl;
}

void GetRH()
{
	long long sum = 0;
	for (int k = 0; k < storage.handy_rack.amount; k++)
	{
		for (int l = 0; l < storage.handy_rack.slots[k].amount; l++)
		{
			sum += storage.handy_rack.slots[k].slots[l].amount;
		}
	}

	std::cout << sum << std::endl;
}

void GetSW(unsigned short w, unsigned short r, unsigned short s)
{
	long long sum = 0;
	for (int l = 0; l < storage.slots[w].slots[r].slots[s].amount; l++)
	{
		sum += storage.slots[w].slots[r].slots[s].slots[l].amount;
	}

	std::cout << sum << std::endl;
}

void GetSH(unsigned short w)
{
	long long sum = 0;
	for (int l = 0; l < storage.slots[w].handy_shelf.amount; l++)
	{
		sum += storage.slots[w].handy_shelf.slots[l].amount;
	}

	std::cout << sum << std::endl;
}

void GetSR(unsigned short s)
{
	long long sum = 0;

	for (int l = 0; l < storage.handy_rack.slots[s].amount; l++)
	{
		sum += storage.handy_rack.slots[s].slots[l].amount;
	}

	std::cout << sum << std::endl;
}

void GetS()
{
	long long sum = 0;

	for (int l = 0; l < storage.handy_shelf.amount; l++)
	{
		sum += storage.handy_shelf.slots[l].amount;
	}

	std::cout << sum << std::endl;
}

void SetLW(unsigned char w, unsigned char r, unsigned char s, unsigned char p, char dd[3])
{
	storage.slots[w].slots[r].slots[s].slots[p].etiq[0] = dd[0];
	storage.slots[w].slots[r].slots[s].slots[p].etiq[1] = dd[1];
}

void SetLH(unsigned char w, unsigned char p, char dd[3])
{
	storage.slots[w].handy_shelf.slots[p].etiq[0] = dd[0];
	storage.slots[w].handy_shelf.slots[p].etiq[1] = dd[1];
}

void SetLR(unsigned char s, unsigned char p, char dd[3])
{
	storage.handy_rack.slots[s].slots[p].etiq[0] = dd[0];
	storage.handy_rack.slots[s].slots[p].etiq[1] = dd[1];
}

void SetLS(unsigned char p, char dd[3])
{
	storage.handy_shelf.slots[p].etiq[0] = dd[0];
	storage.handy_shelf.slots[p].etiq[1] = dd[1];
}

void GetLW(unsigned short w, unsigned short r, unsigned short s, unsigned short p)
{
	if (storage.slots[w].slots[r].slots[s].slots[p].etiq[0] == 0 && storage.slots[w].slots[r].slots[s].slots[p].etiq[1] == 0)
	{
		std::cout << "--"<<std::endl;
	}
	else
	{
		std::cout << storage.slots[w].slots[r].slots[s].slots[p].etiq[0] << storage.slots[w].slots[r].slots[s].slots[p].etiq[1] << std::endl;
	}

}

void GetLH(unsigned short w, unsigned short p)
{
	if (storage.slots[w].handy_shelf.slots[p].etiq[0] == 0 && storage.slots[w].handy_shelf.slots[p].etiq[1] == 0)
	{
		std::cout << "--"<< std::endl;
	}
	else
	{
		std::cout << storage.slots[w].handy_shelf.slots[p].etiq[0] << storage.slots[w].handy_shelf.slots[p].etiq[1] << std::endl;
	}

}

void GetLR(unsigned short s, unsigned short p)
{

	if (storage.handy_rack.slots[s].slots[p].etiq[0] == 0 && storage.handy_rack.slots[s].slots[p].etiq[1] == 0)
	{
		std::cout << "--"<<std::endl;
	}
	else
	{
		std::cout << storage.handy_rack.slots[s].slots[p].etiq[0] << storage.handy_rack.slots[s].slots[p].etiq[1] << std::endl;
	}

}

void GetLS(unsigned short p)
{
	if (storage.handy_shelf.slots[p].etiq[0] == 0 && storage.handy_shelf.slots[p].etiq[1] == 0)
	{
		std::cout << "--"<<std::endl;
	}
	else
	{
		std::cout << storage.handy_shelf.slots[p].etiq[0] << storage.handy_shelf.slots[p].etiq[1] << std::endl;
	}

}
//void Clear()
//{

//}
void SetAP(unsigned char w, unsigned char r, unsigned char s, unsigned char P)
{
	int L = storage.slots[w].slots[r].slots[s].amount;
	if (L > P)
	{
		for (int i = P; i < L; i++) // lub musi byc i<128?
		{
			totalGoods -= storage.slots[w].slots[r].slots[s].slots[i].amount;
			storage.slots[w].slots[r].slots[s].slots[i].amount = 0;
			storage.slots[w].slots[r].slots[s].slots[i].etiq[0] = 0;
			storage.slots[w].slots[r].slots[s].slots[i].etiq[1] = 0;
		}
		/*for (int i = L; i < 128; i++) // lub musi byc i<128? // edit ponoæ nie
		{

			storage.slots[w].slots[r].slots[s].slots[i].amount = 0;
			storage.slots[w].slots[r].slots[s].slots[i].etiq[0] = 0;
			storage.slots[w].slots[r].slots[s].slots[i].etiq[1] = 0;
		}*/
	}
	else
	{
		for (int i = L; i < P; i++) // lub musi byc i<128?
		{
			storage.slots[w].slots[r].slots[s].slots[i].amount = 0;
			storage.slots[w].slots[r].slots[s].slots[i].etiq[0] = 0;
			storage.slots[w].slots[r].slots[s].slots[i].etiq[1] = 0;
		}
		/*for (int i = P; i < 128; i++) // lub musi byc i<128?
		{

			storage.slots[w].slots[r].slots[s].slots[i].amount = 0;
			storage.slots[w].slots[r].slots[s].slots[i].etiq[0] = 0;
			storage.slots[w].slots[r].slots[s].slots[i].etiq[1] = 0;
		}*/
	}
	storage.slots[w].slots[r].slots[s].amount = P;

}

void SetAS(unsigned char w, unsigned char r, unsigned char S, unsigned char P)
{
	int L = storage.slots[w].slots[r].amount;
	storage.slots[w].slots[r].amount = S;
	if (L > S) // dla pó³ek które bêd¹ usuniête else dla ca³kiem nowych pó³ek
	{
		for (int i = 0; i < S; i++)
		{
			SetAP(w, r, i, P);
		}
		for (int i = S; i < L; i++) //konwencja niezachowana
		{
			int jr = storage.slots[w].slots[r].slots[i].amount; //czy to konieczne?
			storage.slots[w].slots[r].slots[i].amount = 0; // up
			for (int j = 0; j < jr; j++)
			{
				totalGoods -= storage.slots[w].slots[r].slots[i].slots[j].amount;
				storage.slots[w].slots[r].slots[i].slots[j].amount = 0;
				storage.slots[w].slots[r].slots[i].slots[j].etiq[0] = 0;
				storage.slots[w].slots[r].slots[i].slots[j].etiq[1] = 0;
			}
		}
	}
	else
	{
		for (int i = 0; i < L; i++)
		{
			SetAP(w, r, i, P);
		}
		for (int i = L; i < S; i++)
		{
			int jr = storage.slots[w].slots[r].slots[i].amount; //czy to konieczne? 2. jr istnieje tylko w petli?
			storage.slots[w].slots[r].slots[i].amount = P; // up
			for (int j = 0; j < P; j++)
			{
				storage.slots[w].slots[r].slots[i].slots[j].amount = 0;
				storage.slots[w].slots[r].slots[i].slots[j].etiq[0] = 0;
				storage.slots[w].slots[r].slots[i].slots[j].etiq[1] = 0;
			}
		}
	}/*
	for (int p = 0; p < P; p++) // dla istniej¹cych pó³ek ich miejsc
	{


		int L = storage.slots[w].slots[r].slots[p].amount;
		storage.slots[w].slots[r].slots[p].amount = P;
		if (L > P)
		{
			for (int z = 0; z < P; z++)
			{
				SetAP(w, r, z, P);


			}
			for (int z = P; z < L; z++)
			{
				totalGoods -= storage.slots[w].slots[r].slots[p].slots[z].amount;
				storage.slots[w].slots[r].slots[p].slots[z].amount = 0;
				storage.slots[w].slots[r].slots[p].slots[z].etiq[0] = 0;
				storage.slots[w].slots[r].slots[p].slots[z].etiq[1] = 0;


			}
		}
		else
		{
			for (int z = 0; z <L; z++)
			{
				SetAP(w, r, z, P);


			}
			for (int z = L; z < P; z++)
			{
				totalGoods -= storage.slots[w].slots[r].slots[p].slots[z].amount;
				storage.slots[w].slots[r].slots[p].slots[z].amount = 0;
				storage.slots[w].slots[r].slots[p].slots[z].etiq[0] = 0;
				storage.slots[w].slots[r].slots[p].slots[z].etiq[1] = 0;


			}
		}

	}
	*/


}

void SetAR(unsigned char w, unsigned char R, unsigned char S, unsigned char P)
{
	int L = storage.slots[w].amount;
	storage.slots[w].amount = R;
	if (L > R) //utrata regalow
	{
		for (int j = 0; j < R; j++)
		{
			SetAS(w, j, S, P);
		}
		for (int j = R; j < L; j++)
		{
			int kr = storage.slots[w].slots[j].amount;
			storage.slots[w].slots[j].amount = 0; //zerowanie
			for (int k = 0; k < kr; k++)
			{
				int lr = storage.slots[w].slots[j].slots[k].amount;
				storage.slots[w].slots[j].slots[k].amount = 0;
				for (int l = 0; l < lr; l++)
				{
					totalGoods -= storage.slots[w].slots[j].slots[k].slots[l].amount;
					storage.slots[w].slots[j].slots[k].slots[l].amount = 0;
					storage.slots[w].slots[j].slots[k].slots[l].etiq[0] = 0;
					storage.slots[w].slots[j].slots[k].slots[l].etiq[1] = 0;
				}
			}

		}
	}
	else // kreacja regalow
	{
		for (int j = 0; j < L; j++)
		{
			SetAS(w, j, S, P);
		}
		for (int j = L; j < R; j++)
		{
			storage.slots[w].slots[j].amount = S;
			for (int k = 0; k < S; k++)
			{
				storage.slots[w].slots[j].slots[k].amount = P;
				for (int l = 0; l < P; l++)
				{
					storage.slots[w].slots[j].slots[k].slots[l].amount = 0;
					storage.slots[w].slots[j].slots[k].slots[l].etiq[0] = 0;
					storage.slots[w].slots[j].slots[k].slots[l].etiq[1] = 0;
				}
			}
		}
	}
	//for (int j = 0; j < R; j++) // dla istniejacych regalow
	//{
		//int L = storage.slots[w].slots[j].amount;
		//storage.slots[w].slots[j].amount = S; Czy na pewno??

		//a moze ta glebokosc jest poprawna:
		//SetAS(w, j, S, P); // wtedy ten ponizszy i powyzszy kod bedzie niepotrzebny

		/*if (L > S)// polki do usuniecia
		{
			true == true;
		}
		else // nadmiarowe polki
		{
			1 == 1;
		} */
		//}
}

void SetAW(unsigned char W, unsigned char R, unsigned char S, unsigned char P)
{
	int L = storage.amount;
	storage.amount = W;
	if (L > W)
	{
		for (int i = 0; i < W; i++)
		{
			SetAR(i, R, S, P);
		}
		for (int i = W; i < L; i++) //magazine
		{
			int jr = storage.slots[i].amount;
			storage.slots[i].amount = 0;
			for (int j = 0; j < jr; j++) //rack
			{
				int kr = storage.slots[i].slots[j].amount;
				storage.slots[i].slots[j].amount = 0;
				for (int k = 0; k < kr; k++) //shelf
				{
					int lr = storage.slots[i].slots[j].slots[k].amount;
					storage.slots[i].slots[j].slots[k].amount = 0;
					for (int l = 0; l < lr; l++) // place
					{
						totalGoods -= storage.slots[i].slots[j].slots[k].slots[l].amount;
						storage.slots[i].slots[j].slots[k].slots[l].amount = 0;
						storage.slots[i].slots[j].slots[k].slots[l].etiq[0] = 0;
						storage.slots[i].slots[j].slots[k].slots[l].etiq[1] = 0;
					}
				}
			}
			//handy shelf
			int hs = storage.slots[i].handy_shelf.amount;
			storage.slots[i].handy_shelf.amount = 0;
			for (int l = 0; l < hs; l++)
			{
				totalGoods -= storage.slots[i].handy_shelf.slots[l].amount; // do walidacji
				storage.slots[i].handy_shelf.slots[l].amount = 0;
				storage.slots[i].handy_shelf.slots[l].etiq[0] = 0;
				storage.slots[i].handy_shelf.slots[l].etiq[1] = 0;
			}
		}
	}
	else
	{
		for (int i = 0; i > L; i++)
		{
			SetAR(i, R, S, P);
		}
		for (int i = L; i < W; i++) // kreacja magazynow
		{ // co z handyshelf?
			storage.slots[i].amount = R;
			for (int j = 0; j < R; j++)
			{
				storage.slots[i].slots[j].amount = S;
				for (int k = 0; k < S; k++)
				{
					storage.slots[i].slots[j].slots[k].amount = P;
					for (int l = 0; l < P; l++)
					{
						storage.slots[i].slots[j].slots[k].slots[l].amount = 0;
						storage.slots[i].slots[j].slots[k].slots[l].etiq[0] = 0;
						storage.slots[i].slots[j].slots[k].slots[l].etiq[1] = 0;
					}
				}
			}
		}
	}
	//for (int i = 0; i < W; i++)
	//{
		//SetAR(i, R, S, P);// otoz nie do konca, powinno byc w petli powyzej;
	//}
}

void SetHW(unsigned char w, unsigned char P)
{
	int L = storage.slots[w].handy_shelf.amount;
	storage.slots[w].handy_shelf.amount = P;
	if (L > P)
	{
		for (int l = P; l < L; l++)
		{
			totalGoods -= storage.slots[w].handy_shelf.slots[l].amount;
			storage.slots[w].handy_shelf.slots[l].amount = 0;
			storage.slots[w].handy_shelf.slots[l].etiq[0] = 0;
			storage.slots[w].handy_shelf.slots[l].etiq[1] = 0;
		}
	}
	else
	{
		for (int l = L; l < P; l++)
		{
			storage.slots[w].handy_shelf.slots[l].amount = 0;
			storage.slots[w].handy_shelf.slots[l].etiq[0] = 0;
			storage.slots[w].handy_shelf.slots[l].etiq[1] = 0;
		}
	}
}

void SetHS(unsigned char P) // swapped z SETHR
{
	int L = storage.handy_shelf.amount;
	storage.handy_shelf.amount = P;
	if (L > P) //usuwanie miejsc
	{
		for (int l = P; l < L; l++)
		{
			totalGoods -= storage.handy_shelf.slots[l].amount;
			storage.handy_shelf.slots[l].amount = 0;
			storage.handy_shelf.slots[l].etiq[0] = 0;
			storage.handy_shelf.slots[l].etiq[1] = 0;
		}
	}
	else
	{
		for (int l = L; l < P; l++)
		{
			storage.handy_shelf.slots[l].amount = 0;
			storage.handy_shelf.slots[l].etiq[0] = 0;
			storage.handy_shelf.slots[l].etiq[1] = 0;
		}
	}
}

void SetHR(unsigned char S, unsigned char P) //swapped z SetHS
{
	int L = storage.handy_rack.amount;
	storage.handy_rack.amount = S;
	if (L > S)//usuwanie polek
	{


		for (int k = 0; k < S; k++)//SetAP
		{
			int L1 = storage.handy_rack.slots[k].amount;
			storage.handy_rack.slots[k].amount = P;
			if (L1 > P) //nadmiar miejsc
			{
				for (int l = P; l < L1; l++)
				{
					totalGoods -= storage.handy_rack.slots[k].slots[l].amount;
					storage.handy_rack.slots[k].slots[l].amount = 0;
					storage.handy_rack.slots[k].slots[l].etiq[0] = 0;
					storage.handy_rack.slots[k].slots[l].etiq[1] = 0;
				}
			}
			else
			{
				for (int l = L1; l < P; l++)
				{
					storage.handy_rack.slots[k].slots[l].amount = 0;
					storage.handy_rack.slots[k].slots[l].etiq[0] = 0;
					storage.handy_rack.slots[k].slots[l].etiq[1] = 0;
				}
			}
		}
		for (int k = S; k < L; k++)
		{
			int lr = storage.handy_rack.slots[k].amount;
			storage.handy_rack.slots[k].amount = 0;
			for (int l = 0; l < lr; l++)
			{
				totalGoods -= storage.handy_rack.slots[k].slots[l].amount;
				storage.handy_rack.slots[k].slots[l].amount = 0;
				storage.handy_rack.slots[k].slots[l].etiq[0] = 0;
				storage.handy_rack.slots[k].slots[l].etiq[1] = 0;
			}
		}
	}
	else //nowo powstale polki
	{
		for (int k = 0; k < L; k++)//SetAP
		{
			int L1 = storage.handy_rack.slots[k].amount;
			storage.handy_rack.slots[k].amount = P;
			if (L1 > P) //nadmiar miejsc
			{
				for (int l = P; l < L1; l++)
				{
					totalGoods -= storage.handy_rack.slots[k].slots[l].amount;
					storage.handy_rack.slots[k].slots[l].amount = 0;
					storage.handy_rack.slots[k].slots[l].etiq[0] = 0;
					storage.handy_rack.slots[k].slots[l].etiq[1] = 0;
				}
			}
			else
			{
				for (int l = L1; l < P; l++)
				{
					storage.handy_rack.slots[k].slots[l].amount = 0;
					storage.handy_rack.slots[k].slots[l].etiq[0] = 0;
					storage.handy_rack.slots[k].slots[l].etiq[1] = 0;
				}
			}
		}
		for (int k = L; k < S; k++)
		{
			storage.handy_rack.slots[k].amount = P;
			for (int l = 0; l < P; l++)
			{
				storage.handy_rack.slots[k].slots[l].amount = 0;
				storage.handy_rack.slots[k].slots[l].etiq[0] = 0;
				storage.handy_rack.slots[k].slots[l].etiq[1] = 0;
			}
		}
	}
}


void PutW(unsigned char w, unsigned char r, unsigned char s, unsigned char p, unsigned short A)
{
	if (storage.slots[w].slots[r].slots[s].slots[p].amount + A > 65535)
	{
		A = 65535 - storage.slots[w].slots[r].slots[s].slots[p].amount;

	}
	storage.slots[w].slots[r].slots[s].slots[p].amount += A;
	totalGoods += A;
}

void PutH(unsigned char w, unsigned char p, unsigned short A)
{
	if (storage.slots[w].handy_shelf.slots[p].amount + A > 65535)
	{
		A = 65535 - storage.slots[w].handy_shelf.slots[p].amount;

	}
	storage.slots[w].handy_shelf.slots[p].amount += A;
	totalGoods += A;
}

void PutR(unsigned char s, unsigned char p, unsigned short A)
{
	if (storage.handy_rack.slots[s].slots[p].amount + A > 65535)
	{
		A = 65535 - storage.handy_rack.slots[s].slots[p].amount;
	}
	storage.handy_rack.slots[s].slots[p].amount += A;
	totalGoods += A;
}

void PutS(unsigned char p, unsigned short A)
{
	if (storage.handy_shelf.slots[p].amount + A > 65535)
	{
		A = 65535 - storage.handy_shelf.slots[p].amount;
	}
	storage.handy_shelf.slots[p].amount += A;
	totalGoods += A;
}

void PopW(unsigned short w, unsigned short r, unsigned short s, unsigned short p, unsigned short A)//tu juz sa shorty
{
	if (storage.slots[w].slots[r].slots[s].slots[p].amount - A < 0)
	{
		A = storage.slots[w].slots[r].slots[s].slots[p].amount;

	}
	storage.slots[w].slots[r].slots[s].slots[p].amount -= A;
	totalGoods -= A;
}

void PopH(unsigned char w, unsigned char p, unsigned short A)
{
	if (storage.slots[w].handy_shelf.slots[p].amount - A < 0)
	{
		A = storage.slots[w].handy_shelf.slots[p].amount;

	}
	storage.slots[w].handy_shelf.slots[p].amount -= A;
	totalGoods -= A;
}

void PopR(unsigned char s, unsigned char p, unsigned short A)
{
	if (storage.handy_rack.slots[s].slots[p].amount - A < 0)
	{
		A = storage.handy_rack.slots[s].slots[p].amount;
	}
	storage.handy_rack.slots[s].slots[p].amount -= A;
	totalGoods -= A;
}

void PopS(unsigned char p, unsigned short A)
{
	if (storage.handy_shelf.slots[p].amount - A < 0)
	{
		A = storage.handy_shelf.slots[p].amount;
	}
	storage.handy_shelf.slots[p].amount -= A;
	totalGoods -= A;
}

void MovW(unsigned char wb, unsigned char rb, unsigned char sb, unsigned char we, unsigned char re, unsigned char se, unsigned char p, long long int A)
{
	if (storage.slots[wb].slots[rb].slots[sb].slots[p].amount - A < 0)
	{
		A = storage.slots[wb].slots[rb].slots[sb].slots[p].amount;
	}
	if (storage.slots[we].slots[re].slots[se].slots[p].amount + A > 65535)
	{
		A = 65535 - storage.slots[we].slots[re].slots[se].slots[p].amount;
	}
	//PopW(wb, rb, sb, p, A);
	storage.slots[wb].slots[rb].slots[sb].slots[p].amount -= A;
	//PutW(we, re, se, p, A);
	storage.slots[we].slots[re].slots[se].slots[p].amount += A;
}

void MovH(unsigned char w, unsigned char r, unsigned char s, unsigned char p, unsigned short A)
{
	if (storage.slots[w].slots[r].slots[s].slots[p].amount - A < 0)
	{
		A = storage.slots[w].slots[r].slots[s].slots[p].amount;
	}
	if (storage.slots[w].handy_shelf.slots[p].amount + A > 65535)
	{
		A = 65535 - storage.slots[w].handy_shelf.slots[p].amount;
	}
	PopW(w, r, s, p, A);
	PutH(w, p, A);
}

void MovR(unsigned char w, unsigned char r, unsigned char sb, unsigned char se, unsigned char p, unsigned short A)
{
	if (storage.slots[w].slots[r].slots[sb].slots[p].amount - A < 0)
	{
		A = storage.slots[w].slots[r].slots[sb].slots[p].amount;
	}
	if (storage.handy_rack.slots[se].slots[p].amount + A > 65535)
	{
		A = 65535 - storage.handy_rack.slots[se].slots[p].amount;
	}
	PopW(w, r, sb, p, A);
	PutR(se, p, A);
}

void MovS(unsigned char s, unsigned char p, unsigned short A)
{
	if (storage.handy_rack.slots[s].slots[p].amount - A < 0)
	{
		A = storage.handy_rack.slots[s].slots[p].amount;
	}
	if (storage.handy_shelf.slots[p].amount + A > 65535)
	{
		A = 65535 - storage.handy_shelf.slots[p].amount;
	}
	PopR(s, p, A);
	PutS(p, A);
}

int main()
{
	 int w;
	 int r;
	 int s;
	 int p;
	 long long int a;
	 int w2;
	 int r2;
	 int s2;
	char dd[3];


	char command[7];

	while (true)
	{
		//czyszczenie tablicy znaków. 

		command[0] = 0;
		command[1] = 0;
		command[2] = 0;
		command[3] = 0;
		command[4] = 0;
		command[5] = 0;
		command[6] = 0;



		std::cin >> command;
		if (command[0] == 'E' && command[1] == 'N' && command[2] == 'D')
		{
			break;
		}

		if (command[0] == 'F' && command[1] == 'I' && command[2] == 'L' && command[3] == 'L')
		{
			std::cin >> w >> r >> s >> p >> a;

			if (w >= 0 && w <= 128 && r >= 0 && r <= 128 && s >= 0 && s <= 128 && p >= 0 && p <= 128 && a >= 0 && a <= 65535)
			{
				Fill(w, r, s, p, a);
			}
			else
			{
				std::cout << "error" << std::endl;
			}

		}
		//GET
		if (command[0] == 'G' && command[1] == 'E' && command[2] == 'T')
		{
			if (command[3 + 0] == '-' && command[3 + 1] == 'E' && command[3 + 2] == 0)
			{
				GetE();
			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'W' && command[3 + 2] == 0)
			{
				std::cin >> w;
				if (w >= 0 && w < storage.amount)
				{
					GetW(w);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'R' && command[3 + 2] == 'W')
			{
				std::cin >> w >> r;
				if (w >= 0 && w < storage.amount && r >= 0 && r < storage.slots[w].amount)
				{
					GetRW(w, r);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'R' && command[3 + 2] == 'H')
			{
				GetRH();
			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'S' && command[3 + 2] == 'W')
			{
				std::cin >> w >> r >> s;
				if (w >= 0 && w < storage.amount && r >= 0 && r < storage.slots[w].amount && s >= 0 && s < storage.slots[w].slots[r].amount)
				{
					GetSW(w, r, s);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'S' && command[3 + 2] == 'H')
			{
				std::cin >> w;
				if (w >= 0 && w < storage.amount)
				{
					GetSH(w);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'S' && command[3 + 2] == 'R')
			{
				std::cin >> s;
				if (s >= 0 && s < storage.handy_rack.amount)
				{
					GetSR(s);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'S' && command[3 + 2] == 0)
			{
				GetS();

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'L' && command[3 + 2] == 'W')
			{
				std::cin >> w >> r >> s >> p;
				if (w >= 0 && w < storage.amount && r >= 0 && r < storage.slots[w].amount && s >= 0 && s < storage.slots[w].slots[r].amount && p >= 0 && p < storage.slots[w].slots[r].slots[s].amount)
				{
					GetLW(w, r, s, p);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'L' && command[3 + 2] == 'H')
			{
				std::cin >> w >> p;
				if (w >= 0 && w < storage.amount && p >= 0 && p < storage.slots[w].handy_shelf.amount)
				{
					GetLH(w, p);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'L' && command[3 + 2] == 'R')
			{
				std::cin >> s >> p;
				if (s >= 0 && s < storage.handy_rack.amount && p >= 0 && p < storage.handy_rack.slots[s].amount)
				{
					GetLR(s, p);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'L' && command[3 + 2] == 'S')
			{
				std::cin >> p;
				if (p >= 0 && p < storage.handy_shelf.amount)
				{
					GetLS(p);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


		}//gety skonczone


		if (command[0] == 'S' && command[1] == 'E' && command[2] == 'T')
		{

			if (command[3 + 0] == '-' && command[3 + 1] == 'A' && command[3 + 2] == 'P')
			{
				std::cin >> w >> r >> s >> p;
				if (w >= 0 && w < storage.amount && r >= 0 && r < storage.slots[w].amount && s >= 0 && s < storage.slots[w].slots[r].amount && p >= 0 && p <= 128)
				{
					SetAP(w, r, s, p);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'A' && command[3 + 2] == 'S')
			{
				std::cin >> w >> r >> s >> p;
				if (w >= 0 && w < storage.amount && r >= 0 && r < storage.slots[w].amount && s >= 0 && s <= 128 && p >= 0 && p <= 128)
				{
					SetAS(w, r, s, p);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'A' && command[3 + 2] == 'R')
			{
				std::cin >> w >> r >> s >> p;
				if (w >= 0 && w < storage.amount && r >= 0 && r <= 128 && s >= 0 && s <= 128 && p >= 0 && p <= 128)
				{
					SetAR(w, r, s, p);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'A' && command[3 + 2] == 'W')
			{
				std::cin >> w >> r >> s >> p;
				if (w >= 0 && w <= 128 && r >= 0 && r <= 128 && s >= 0 && s <= 128 && p >= 0 && p <= 128)
				{
					SetAW(w, r, s, p);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}



			if (command[3 + 0] == '-' && command[3 + 1] == 'H' && command[3 + 2] == 'W')
			{
				std::cin >> w >> p;
				if (w >= 0 && w < storage.amount && p >= 0 && p <= 128)
				{
					SetHW(w, p);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'H' && command[3 + 2] == 'R')
			{
				std::cin >> s >> p;
				if (s >= 0 && s <= 128 && p >= 0 && p <= 128)
				{
					SetHR(s, p);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'H' && command[3 + 2] == 'S')
			{
				std::cin >> p;
				if (p >= 0 && p <= 128)
				{
					SetHS(p);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'L' && command[3 + 2] == 'W')
			{
				std::cin >> w >> r >> s >> p >> dd;
				if (w >= 0 && w < storage.amount && r >= 0 && r < storage.slots[w].amount && s >= 0 && s < storage.slots[w].slots[r].amount && p >= 0 && p < storage.slots[w].slots[r].slots[s].amount)//dd nie jest sprawdzane
				{
					SetLW(w, r, s, p, dd);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'L' && command[3 + 2] == 'H')
			{
				std::cin >> w >> p >> dd;
				if (w >= 0 && w < storage.amount && p >= 0 && p < storage.slots[w].handy_shelf.amount)//dd nie jest sprawdzane
				{
					SetLH(w, p, dd);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'L' && command[3 + 2] == 'R')
			{
				std::cin >> s >> p >> dd;
				if (s >= 0 && s < storage.handy_rack.amount && p >= 0 && p < storage.handy_rack.slots[s].amount)//dd nie jest sprawdzane
				{
					SetLR(s, p, dd);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'L' && command[3 + 2] == 'S')
			{
				std::cin >> p >> dd;
				if (p >= 0 && p < storage.handy_shelf.amount)//dd nie jest sprawdzane
				{
					SetLS(p, dd);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}



		}//koniec setow


		if (command[0] == 'P' && command[1] == 'U' && command[2] == 'T')
		{

			if (command[3 + 0] == '-' && command[3 + 1] == 'W' && command[3 + 2] == 0)
			{
				std::cin >> w >> r >> s >> p >> a;
				if (w >= 0 && w < storage.amount && r >= 0 && r < storage.slots[w].amount && s >= 0 && s < storage.slots[w].slots[r].amount && p >= 0 && p < storage.slots[w].slots[r].slots[s].amount && a >= 0)
				{
					PutW(w, r, s, p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'H' && command[3 + 2] == 0)
			{
				std::cin >> w >> p >> a;
				if (w >= 0 && w < storage.amount && p >= 0 && p < storage.slots[w].handy_shelf.amount && a >= 0)
				{
					PutH(w, p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'R' && command[3 + 2] == 0)
			{
				std::cin >> s >> p >> a;
				if (s >= 0 && s < storage.handy_rack.amount && p >= 0 && p < storage.handy_rack.slots[s].amount && a >= 0)
				{
					PutR(s, p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}



			if (command[3 + 0] == '-' && command[3 + 1] == 'S' && command[3 + 2] == 0)
			{
				std::cin >> p >> a;
				if (p >= 0 && p < storage.handy_shelf.amount && a >= 0)
				{
					PutS(p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


		}//koniec PUT

		if (command[0] == 'P' && command[1] == 'O' && command[2] == 'P')
		{

			if (command[3 + 0] == '-' && command[3 + 1] == 'W' && command[3 + 2] == 0)
			{
				std::cin >> w >> r >> s >> p >> a;
				if (w >= 0 && w < storage.amount && r >= 0 && r < storage.slots[w].amount && s >= 0 && s < storage.slots[w].slots[r].amount && p >= 0 && p < storage.slots[w].slots[r].slots[s].amount && a >= 0)
				{
					PopW(w, r, s, p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}


			if (command[3 + 0] == '-' && command[3 + 1] == 'H' && command[3 + 2] == 0)
			{
				std::cin >> w >> p >> a;
				if (w >= 0 && w < storage.amount && p >= 0 && p < storage.slots[w].handy_shelf.amount && a >= 0)
				{
					PopH(w, p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'R' && command[3 + 2] == 0)
			{
				std::cin >> s >> p >> a;
				if (s >= 0 && s < storage.handy_rack.amount && p >= 0 && p < storage.handy_rack.slots[s].amount && a >= 0)
				{
					PopR(s, p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'S' && command[3 + 2] == 0)
			{
				std::cin >> p >> a;
				if (p >= 0 && p < storage.handy_shelf.amount && a >= 0)
				{
					PopS(p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}
		}// koniec pop

		if (command[0] == 'M' && command[1] == 'O' && command[2] == 'V')
		{

			if (command[3 + 0] == '-' && command[3 + 1] == 'W' && command[3 + 2] == 0)
			{
				std::cin >> w >> r >> s >> w2 >> r2 >> s2 >> p >> a;
				if (w >= 0 && w < storage.amount && r >= 0 && r < storage.slots[w].amount && s >= 0 && s < storage.slots[w].slots[r].amount && w2 >= 0 && w2 < storage.amount && r2 >= 0 && r2 < storage.slots[w2].amount && s2 >= 0 && s2 < storage.slots[w2].slots[r2].amount && p >= 0 && p < storage.slots[w2].slots[r2].slots[s2].amount && p < storage.slots[w].slots[r].slots[s].amount && a >= 0)
				{
					MovW(w, r, s, w2, r2, s2, p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'H' && command[3 + 2] == 0)
			{
				std::cin >> w >> r >> s >> p >> a;
				if (w >= 0 && w < storage.amount && r >= 0 && r < storage.slots[w].amount && s >= 0 && s < storage.slots[w].slots[r].amount && p >= 0 && p < storage.slots[w].slots[r].slots[s].amount && a >= 0 && a <= 65535)
				{
					MovH(w, r, s, p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'R' && command[3 + 2] == 0)
			{
				std::cin >> w >> r >> s >> s2 >> p >> a;
				if (w >= 0 && w < storage.amount && r >= 0 && r < storage.slots[w].amount && s >= 0 && s < storage.slots[w].slots[r].amount && s2 >= 0 && s2 < storage.slots[w].slots[r].amount && p >= 0 && p < storage.slots[w].slots[r].slots[s].amount && p < storage.slots[w].slots[r].slots[s2].amount && a >= 0 && a <= 65535)
				{
					MovR(w, r, s, s2, p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

			if (command[3 + 0] == '-' && command[3 + 1] == 'S' && command[3 + 2] == 0)
			{
				std::cin >> s >> p >> a;
				if (s >= 0 && s < storage.handy_rack.amount && p >= 0 && p < storage.handy_rack.slots[s].amount && a >= 0 && a <= 65535)
				{
					MovS(s, p, a);
				}
				else
				{
					std::cout << "error" << std::endl;
				}

			}

		}//koniec mov


	}

	return 0;

}