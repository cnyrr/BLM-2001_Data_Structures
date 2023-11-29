#include <iostream>

#define SENTINEL -1000000
// WIP

// Bitmedi
struct IAA {
	int deger;
	struct IAA* sol_eleman;
	struct IAA* sag_eleman;
};

IAA* DugumOlustur(int deger) {
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
	IAA* yeni_dugum = DugumOlustur(deger);
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

void InOrderYazdir(IAA* kok) {
	if (kok == NULL)
	{
		return;
	}
	InOrderYazdir(kok->sol_eleman);
	printf("%4d", kok->deger);
	InOrderYazdir(kok->sag_eleman);
	return;
}

void PreOrderYazdir(IAA* kok) {
	if (kok == NULL)
	{
		return;
	}
	printf("%4d", kok->deger);
	PreOrderYazdir(kok->sol_eleman);
	PreOrderYazdir(kok->sag_eleman);
	return;
}

void PostOrderYazdir(IAA* kok) {
	if (kok == NULL)
	{
		return;
	}
	PostOrderYazdir(kok->sol_eleman);
	PostOrderYazdir(kok->sag_eleman);
	printf("%4d", kok->deger);
	return;
}

void DugumSil(IAA** kok, int deger)
{
	IAA* onceki_dugum = NULL;
	IAA* kontrol_edilen_dugum = *kok;
	int sag_tarafa = 0;

	if (*kok== NULL)
	{
		return;
	}

	while (kontrol_edilen_dugum != NULL)
	{
		if (deger < kontrol_edilen_dugum->deger)
		{
			sag_tarafa = 0;
			onceki_dugum = kontrol_edilen_dugum;
			kontrol_edilen_dugum = kontrol_edilen_dugum->sol_eleman;
		}
		else if (deger > kontrol_edilen_dugum->deger)
		{
			sag_tarafa = 1;
			onceki_dugum = kontrol_edilen_dugum;
			kontrol_edilen_dugum = kontrol_edilen_dugum->sag_eleman;
		}
		else
		{
			break;
		}
	}
	
	if (kontrol_edilen_dugum == NULL)
	{
		return;
	}

	if (kontrol_edilen_dugum->sag_eleman == NULL)
	{
		if (onceki_dugum == NULL)
		{
			if (sag_tarafa)
			{
				*kok = kontrol_edilen_dugum->sol_eleman;
			}
			else
			{
				*kok = kontrol_edilen_dugum->sol_eleman;
			}
		}
		else
		{
			if (sag_tarafa)
			{
				onceki_dugum->sag_eleman = kontrol_edilen_dugum->sol_eleman;
			}
			else
			{
				onceki_dugum->sol_eleman = kontrol_edilen_dugum->sol_eleman;
			}
		}
	}
	else if (kontrol_edilen_dugum->sol_eleman == NULL)
	{
		if (onceki_dugum == NULL)
		{
			if (sag_tarafa)
			{
				*kok = kontrol_edilen_dugum->sag_eleman;
			}
			else
			{
				*kok = kontrol_edilen_dugum->sag_eleman;
			}
		}
		else {
			if (sag_tarafa)
			{
				onceki_dugum->sag_eleman = kontrol_edilen_dugum->sag_eleman;
			}
			else
			{
				onceki_dugum->sol_eleman = kontrol_edilen_dugum->sag_eleman;
			}
		}
	}
	else
	{
		IAA* degisen_onceki_eleman = kontrol_edilen_dugum;
		IAA* degistirilecek_eleman = kontrol_edilen_dugum->sag_eleman;

		while (degistirilecek_eleman->sol_eleman != NULL)
		{
			degisen_onceki_eleman = degistirilecek_eleman;
			degistirilecek_eleman = degistirilecek_eleman->sol_eleman;
		}

		if (onceki_dugum == NULL)
		{
			degisen_onceki_eleman->sol_eleman = degistirilecek_eleman->sag_eleman;
			degistirilecek_eleman->sag_eleman = (*kok)->sag_eleman;
			degistirilecek_eleman->sol_eleman = (*kok)->sol_eleman;
			*kok = degistirilecek_eleman;
		}
		else
		{
			onceki_dugum->sol_eleman = degistirilecek_eleman;
			degisen_onceki_eleman->sol_eleman = degistirilecek_eleman->sag_eleman;
			degistirilecek_eleman->sag_eleman = kontrol_edilen_dugum->sag_eleman;
			degistirilecek_eleman->sol_eleman = kontrol_edilen_dugum->sol_eleman;
		}

	}

	free(kontrol_edilen_dugum);
}

void AgacBuda(IAA** kok, int anahtar)
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
		else
		{
			if (soldan_mi)
			{
				onceki_eleman->sol_eleman = simdiki_eleman->sol_eleman;
			}
			else
			{
				onceki_eleman->sag_eleman = simdiki_eleman->sol_eleman;
			}
		}
	}
	else if (simdiki_eleman->sol_eleman == NULL)
	{
		if (simdiki_eleman == *kok)
		{
			*kok = simdiki_eleman->sag_eleman;
		}
		else
		{
			if (soldan_mi)
			{
				onceki_eleman->sol_eleman = simdiki_eleman->sag_eleman;
			}
			else
			{
				onceki_eleman->sag_eleman = simdiki_eleman->sag_eleman;
			}
		}
	}
	else
	{
		IAA* en_soldan_onceki_eleman = simdiki_eleman;
		IAA* en_soldaki_eleman = simdiki_eleman->sag_eleman;

		while (en_soldaki_eleman->sol_eleman != NULL)
		{
			en_soldan_onceki_eleman = en_soldaki_eleman;
			en_soldaki_eleman = en_soldaki_eleman->sol_eleman;
		}
		if (en_soldan_onceki_eleman != simdiki_eleman)
		{
			en_soldan_onceki_eleman->sol_eleman = en_soldaki_eleman->sag_eleman;
			en_soldaki_eleman->sag_eleman = simdiki_eleman->sag_eleman;
		}
		en_soldaki_eleman->sol_eleman = simdiki_eleman->sol_eleman;

		if (onceki_eleman == NULL)
		{
			*kok = en_soldaki_eleman;
		}
		else { 
			/*if //(soldan_mi == 1)
			{
				onceki_eleman->sol_eleman = en_soldaki_eleman;
			}
			else*/
			{
				onceki_eleman->sag_eleman = en_soldaki_eleman;
			}
			
		}
	}
	free(simdiki_eleman);
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

int DugumSayisi(IAA* kok)
{
	if (kok == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + DugumSayisi(kok->sag_eleman) + DugumSayisi(kok->sol_eleman);
	}
}

int YaprakSayisi(IAA* kok)
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
		return YaprakSayisi(kok->sag_eleman) + YaprakSayisi(kok->sol_eleman);
	}
}

int IcDugumSayisi(IAA* kok)
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
		return 1 + IcDugumSayisi(kok->sag_eleman) + IcDugumSayisi(kok->sol_eleman);
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

int EnKisaYol(IAA* kok)
{
	int sagdan, soldan, kisa_yol, uzun_yol;

	if (kok == NULL)
	{
		return 0;
	}
	sagdan = EnKisaYol(kok->sag_eleman);
	soldan = EnKisaYol(kok->sol_eleman);

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

void IAADengeliMi()
{
	// Agaç dengeli mi ?
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
	IAA* agac_koku = DugumOlustur(70);
	IAAEkle(&agac_koku, 60);
	IAAEkle(&agac_koku, 50);
	IAAEkle(&agac_koku, 32);
	IAAEkle(&agac_koku, 35);
	IAAEkle(&agac_koku, 55);
	IAAEkle(&agac_koku, 80);
	IAAEkle(&agac_koku, 75);
	IAAEkle(&agac_koku, 73);
	IAAEkle(&agac_koku, 78);
	printf("Dede: %4d Torun: %4d\n", IAADugumDedesi(agac_koku, 55), 55);
	printf("Dede: %4d Torun: %4d\n", IAADugumDedesi(agac_koku, 35), 35);
	printf("Dede: %4d Torun: %4d\n", IAADugumDedesi(agac_koku, 70), 70);
	printf("Dede: %4d Torun: %4d\n", IAADugumDedesi(agac_koku, 60), 60);
	printf("Dede: %4d Torun: %4d\n", IAADugumDedesi(agac_koku, 50), 50);
	printf("Dede: %4d Torun: %4d\n", IAADugumDedesi(agac_koku, 90), 90);
	printf("Dede: %4d Torun: %4d\n", IAADugumDedesi(agac_koku, 33), 33);
	

}

