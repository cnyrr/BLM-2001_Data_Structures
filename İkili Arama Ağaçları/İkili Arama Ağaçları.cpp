#include <iostream>

#define SENTINEL -1000000

struct IAA {
	int deger;
	struct IAA* sol_eleman;
	struct IAA* sag_eleman;
};

IAA* IAADugumOlustur(int deger) {
	IAA* yeni_dugum = (IAA*)malloc(sizeof(IAA));

	if (yeni_dugum == NULL)
	{
		printf("Heap'te yer ayrilamadi.");
		exit(1);
	}
	yeni_dugum->deger = deger;
	yeni_dugum->sol_eleman = NULL;
	yeni_dugum->sag_eleman = NULL;
	
	return yeni_dugum;
}

void IAAEkle(IAA** kok, int deger) 
{
	IAA* onceki_dugum = *kok;
	IAA* simdiki_dugum = *kok;
	IAA* yeni_dugum = IAADugumOlustur(deger);
	int sag_tarafa = 0;

	if (simdiki_dugum == NULL)
	{
		*kok = yeni_dugum;
		return;
	}

	while (simdiki_dugum != NULL)
	{
		if (deger < simdiki_dugum->deger)
		{
			sag_tarafa = 0;
			onceki_dugum = simdiki_dugum;
			simdiki_dugum = simdiki_dugum->sol_eleman;
		}
		else if (deger > simdiki_dugum->deger)
		{
			sag_tarafa = 1;
			onceki_dugum = simdiki_dugum;
			simdiki_dugum = simdiki_dugum->sag_eleman;
		}
		else
		{
			break;
		}
	}
	
	if (simdiki_dugum == NULL)
	{
		if (sag_tarafa)
		{
			onceki_dugum->sag_eleman = yeni_dugum;
		}
		else
		{
			onceki_dugum->sol_eleman = yeni_dugum;
		}
	}
	
	return;
}

void IAAInOrderYazdir(IAA* kok) {
	if (kok == NULL)
	{
		return;
	}
	IAAInOrderYazdir(kok->sol_eleman);
	printf("%4d", kok->deger);
	IAAInOrderYazdir(kok->sag_eleman);
	return;
}

void IAAPreOrderYazdir(IAA* kok) {
	if (kok == NULL)
	{
		return;
	}
	printf("%4d", kok->deger);
	IAAPreOrderYazdir(kok->sol_eleman);
	IAAPreOrderYazdir(kok->sag_eleman);
	return;
}

void IAAPostOrderYazdir(IAA* kok) {
	if (kok == NULL)
	{
		return;
	}
	IAAPostOrderYazdir(kok->sol_eleman);
	IAAPostOrderYazdir(kok->sag_eleman);
	printf("%4d", kok->deger);
	return;
}

void IAAElemanSil(IAA** kok, int anahtar)
{
	if (*kok == NULL)
	{
		return;
	}

	IAA* onceki_eleman = NULL;
	IAA* simdiki_eleman = *kok;
	int soldan_mi = 0;

	while (simdiki_eleman != NULL)
	{
		if (simdiki_eleman->deger < anahtar)
		{
			onceki_eleman = simdiki_eleman;
			simdiki_eleman = simdiki_eleman->sag_eleman;
			soldan_mi = 0;
		}
		else if (simdiki_eleman->deger > anahtar)
		{
			onceki_eleman = simdiki_eleman;
			simdiki_eleman = simdiki_eleman->sol_eleman;
			soldan_mi = 1;
		}
		else
		{
			break;
		}
	}

	if (simdiki_eleman == NULL)
	{
		return;
	}

	if (simdiki_eleman->sag_eleman == NULL)
	{
		if (simdiki_eleman == *kok)
		{
			*kok = simdiki_eleman->sol_eleman;
		}
		else if (soldan_mi)
		{
			onceki_eleman->sol_eleman = simdiki_eleman->sol_eleman;
		}
		else
		{
			onceki_eleman->sag_eleman = simdiki_eleman->sol_eleman;
		}
	}
	else if (simdiki_eleman->sol_eleman == NULL)
	{
		if (simdiki_eleman == *kok)
		{
			*kok = simdiki_eleman->sag_eleman;
		}
		else if (soldan_mi)
		{
			onceki_eleman->sol_eleman = simdiki_eleman->sag_eleman;
		}
		else
		{
			onceki_eleman->sag_eleman = simdiki_eleman->sag_eleman;
		}
	}
	else
	{
		IAA* degisenden_onceki_eleman = simdiki_eleman;
		IAA* degisecek_eleman = simdiki_eleman->sag_eleman;

		while (degisecek_eleman->sol_eleman != NULL)
		{
			degisenden_onceki_eleman = degisecek_eleman;
			degisecek_eleman = degisecek_eleman->sol_eleman;
		}

		degisenden_onceki_eleman->sol_eleman = degisecek_eleman->sag_eleman;
		degisecek_eleman->sol_eleman = simdiki_eleman->sol_eleman;
		degisecek_eleman->sag_eleman = simdiki_eleman->sag_eleman;

		if (simdiki_eleman == *kok)
		{
			*kok = degisecek_eleman;
		}
		else if (soldan_mi)
		{
			onceki_eleman->sol_eleman = degisecek_eleman;
		}
		else
		{
			onceki_eleman->sag_eleman = degisecek_eleman;
		}
	}
	free(simdiki_eleman);

	return;
}

int IAAMi(IAA* kok, IAA* aranan_dugum) 
{
	IAA* simdiki_dugum = kok;

	if (aranan_dugum == NULL) 
	{
		return 1;
	}

	while (simdiki_dugum != NULL && simdiki_dugum != aranan_dugum)
	{
		if (simdiki_dugum->deger < aranan_dugum->deger)
		{
			simdiki_dugum = simdiki_dugum->sag_eleman;
		}
		else if (simdiki_dugum->deger > aranan_dugum->deger)
		{
			simdiki_dugum = simdiki_dugum->sol_eleman;
		}
		else
		{
			break;
		}
	}

	if (simdiki_dugum == NULL)
	{
		return 0;
	}
	else if (IAAMi(kok, simdiki_dugum->sol_eleman) && IAAMi(kok, simdiki_dugum->sag_eleman))
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

int IAADugumSayisi(IAA* kok)
{
	if (kok == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + IAADugumSayisi(kok->sag_eleman) + IAADugumSayisi(kok->sol_eleman);
	}
}

int IAAYaprakSayisi(IAA* kok)
{
	if (kok == NULL)
	{
		return 0;
	}
	else if (kok->sag_eleman == NULL && kok->sol_eleman == NULL)
	{
		return 1;
	}
	else
	{
		return IAAYaprakSayisi(kok->sag_eleman) + IAAYaprakSayisi(kok->sol_eleman);
	}
}

int IAAIcDugumSayisi(IAA* kok)
{
	if (kok == NULL)
	{
		return 0;
	}
	else if (kok->sol_eleman == NULL && kok->sag_eleman == NULL)
	{
		return 0;
	}
	{
		return 1 + IAAIcDugumSayisi(kok->sag_eleman) + IAAIcDugumSayisi(kok->sol_eleman);
	}
}

void IAASil(IAA** kok)
{
	if (*kok == NULL)
	{
		return;
	}
	else
	{
		IAASil(&(*kok)->sag_eleman);
		IAASil(&(*kok)->sol_eleman);
		free(*kok);
		*kok = NULL;
	}
}

int IAAEnKisaYol(IAA* kok)
{
	int sagdan, soldan, kisa_yol, uzun_yol;

	if (kok == NULL)
	{
		return 0;
	}
	sagdan = IAAEnKisaYol(kok->sag_eleman);
	soldan = IAAEnKisaYol(kok->sol_eleman);

	if (sagdan > soldan)
	{
		uzun_yol = sagdan;
		kisa_yol = soldan;
	}
	else
	{
		uzun_yol = soldan;
		kisa_yol = sagdan;
	}

	if (kok->sag_eleman != NULL || kok->sol_eleman != NULL)
	{
		return kisa_yol + 1;
	}
	return uzun_yol + 1;
}

int IAADengeliMi(IAA* agac_koku, IAA* kontrol_edilecek_dugum)
{
	if (kontrol_edilecek_dugum == NULL)
	{
		return 1;
	}

	int sol_yol = IAADengeliMi(agac_koku, kontrol_edilecek_dugum->sol_eleman);
	int sag_yol = IAADengeliMi(agac_koku, kontrol_edilecek_dugum->sag_eleman);

	if (sol_yol == 0 || sag_yol == 0)
	{
		return 0;
	}

	if (sol_yol - sag_yol > 1 || sag_yol - sol_yol > 1)
	{
		return 0;
	}

	if (agac_koku == kontrol_edilecek_dugum)
	{
		return 1;
	}

	if (sol_yol > sag_yol)
	{
		return sol_yol + 1;
	}
	else
	{
		return sag_yol + 1;
	}
}

int IAADugumDedesi(IAA* agac_koku, int deger)
{
	IAA* dede = NULL;
	IAA* baba = NULL;
	IAA* simdiki = agac_koku;

	while (simdiki != NULL)
	{
		if (deger < simdiki->deger)
		{
			dede = baba;
			baba = simdiki;
			simdiki = simdiki->sol_eleman;
		}
		else if (deger > simdiki->deger)
		{
			dede = baba;
			baba = simdiki;
			simdiki = simdiki->sag_eleman;
		}
		else
		{
			break;
		}
	}
	
	if (simdiki == NULL || dede == NULL)
	{
		return SENTINEL;
	}

	return dede->deger;

}

int main()
{
	IAA* agac_koku = NULL;
	IAAEkle(&agac_koku, 100);
	IAAEkle(&agac_koku, 50);
	IAAEkle(&agac_koku, 200);
	IAAEkle(&agac_koku, 25);
	IAAEkle(&agac_koku, 75);
	IAAEkle(&agac_koku, 150);
	IAAEkle(&agac_koku, 250);
	printf("Agac dengeli mi?\nDondu: %d\n", IAADengeliMi(agac_koku, agac_koku));
	IAAPreOrderYazdir(agac_koku);
	IAAElemanSil(&agac_koku, 100);
	printf("\n\n \"100\" degeri silindi peki simdi dengeli mi?\nDondu: %d\n", IAADengeliMi(agac_koku, agac_koku));
	IAAPreOrderYazdir(agac_koku);
	IAAElemanSil(&agac_koku, 250);
	printf("\n\n \"250\" degeri silindi peki simdi dengeli mi?\nDondu: %d\n", IAADengeliMi(agac_koku, agac_koku));
	IAAPreOrderYazdir(agac_koku);
	IAAElemanSil(&agac_koku, 200);
	printf("\n\n \"200\" degeri silindi peki simdi dengeli mi?\nDondu: %d\n", IAADengeliMi(agac_koku, agac_koku));
	IAAPreOrderYazdir(agac_koku);
}

