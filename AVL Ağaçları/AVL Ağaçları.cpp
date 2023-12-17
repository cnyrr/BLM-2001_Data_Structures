#include <iostream>

struct AVL {
    int deger;
    int yukseklik;
    AVL* sol_eleman;
    AVL* sag_eleman;
};

struct AVL* AVLDugumOlustur(int deger)
{
    AVL* yeni_dugum = (AVL*)malloc(sizeof(struct AVL));

	if (yeni_dugum == NULL)
	{
		printf("Malloc basarisiz oldu.");
		exit(EXIT_FAILURE);
	}

	yeni_dugum->deger = deger;
	yeni_dugum->sol_eleman = NULL;
	yeni_dugum->sag_eleman = NULL;
	yeni_dugum->yukseklik = 1;
	return yeni_dugum;
}

int AVLDengeHesapla(AVL* dugum)
{
	if (dugum == NULL || dugum->sol_eleman == NULL && dugum->sag_eleman == NULL)
	{
		return 0;
	}
	else if (dugum->sag_eleman == NULL)
	{
		return dugum->sol_eleman->yukseklik;
	}
	else if (dugum->sol_eleman == NULL)
	{
		return - dugum->sag_eleman->yukseklik;
	}
	else
	{
		return dugum->sol_eleman->yukseklik - dugum->sag_eleman->yukseklik;
	}
}

void AVLYukseklikGuncelle(AVL* dugum)
{
	if (dugum == NULL)
	{
		return;
	}
	else if (dugum->sol_eleman == NULL && dugum->sag_eleman == NULL)
	{
		dugum->yukseklik = 1;
	}
	else if (dugum->sol_eleman == NULL)
	{
		dugum->yukseklik = dugum->sag_eleman->yukseklik + 1;
	}
	else if (dugum->sag_eleman == NULL)
	{
		dugum->yukseklik = dugum->sol_eleman->yukseklik + 1;
	}
	else
	{
		if (dugum->sol_eleman->yukseklik > dugum->sag_eleman->yukseklik)
		{
			dugum->yukseklik = dugum->sol_eleman->yukseklik + 1;
		}
		else
		{
			dugum->yukseklik = dugum->sag_eleman->yukseklik + 1;
		}
	}

	return;
}

void AVLSagRotasyon(AVL** dugum)
{
	// Sağa gidecek düğümün adresini tut.
	AVL* gecici = *dugum;
	// Sağa gidecek düğüme işaretçiyi, sol düğümü yap.
	*dugum = (*dugum)->sol_eleman;
	// Sağa gidecek düğümün sağı, yerine gelen düğümün sağına işaret etsin.
	(gecici)->sol_eleman = (*dugum)->sag_eleman;
	// Yerine gelen düğümün sağı, sağa giden düğüme işaret etsin.
	(*dugum)->sag_eleman = gecici;
	AVLYukseklikGuncelle(gecici);
	AVLYukseklikGuncelle(*dugum);
	return;
}

void AVLSolRotasyon(AVL** dugum)
{
	// Sola gidecek düğümün adresini tut.
	AVL* gecici = *dugum;
	// Sola gidecek düğüme işaretçiyi, sağ düğümü yap.
	*dugum = (*dugum)->sag_eleman;
	// Sola gidecek düğümün sağı, yerine gelen düğümün soluna işaret etsin.
	(gecici)->sag_eleman = (*dugum)->sol_eleman;
	// Yerine gelen düğümün solu, sola giden düğüme işaret etsin.
	(*dugum)->sol_eleman = gecici;
	AVLYukseklikGuncelle(gecici);
	AVLYukseklikGuncelle(*dugum);
	return;
}


void AVLDugumEkle(AVL** kok, int deger)
{
	int denge;

	if (*kok == NULL)
	{
		*kok = AVLDugumOlustur(deger);
		return;
	}

	if (deger > (*kok)->deger)
	{
		AVLDugumEkle(&((*kok)->sag_eleman), deger);
	}
	else if (deger < (*kok)->deger)
	{
		AVLDugumEkle(&((*kok)->sol_eleman), deger);
	}
	else
	{
		return;
	}

	AVLYukseklikGuncelle(*kok);
	denge = AVLDengeHesapla(*kok);
	
	if (denge < -1 && AVLDengeHesapla((*kok)->sag_eleman) < 0)
	{
		printf("Sol rotasyon yapildi.\n");
		AVLSolRotasyon(kok);
	}
	else if (denge < -1 && AVLDengeHesapla((*kok)->sag_eleman) > 0)
	{
		printf("Sag-sol rotasyon yapildi.\n");
		AVLSagRotasyon(&((*kok)->sag_eleman));
		AVLSolRotasyon(kok);
	}
	else if (denge > 1 && AVLDengeHesapla((*kok)->sol_eleman) < 0)
	{
		printf("Sol-sag rotasyon yapildi.\n");
		AVLSolRotasyon(&((*kok)->sol_eleman));
		AVLSagRotasyon(kok);
	}
	else if (denge > 1 && AVLDengeHesapla((*kok)->sol_eleman) > 0)
	{
		printf("Sag rotasyon yapildi.\n");
		AVLSagRotasyon(kok);
	}

	return;
}

void AVLDugumSil(AVL** kok, int deger)
{
	int denge;

	if (*kok == NULL)
	{
		return;
	}
	else if (deger > (*kok)->deger)
	{
		AVLDugumSil(&((*kok)->sag_eleman), deger);
	}
	else if (deger < (*kok)->deger)
	{
		AVLDugumSil(&((*kok)->sol_eleman), deger);
	}
	else
	{
		AVL* gecici = *kok;

		if ((*kok)->sag_eleman == NULL && (*kok)->sol_eleman == NULL)
		{
			free(*kok);
			*kok = NULL;
			return;
		}
		else if ((*kok)->sag_eleman == NULL)
		{
			*kok = (*kok)->sol_eleman;
			(*kok)->yukseklik++;
			free(gecici);
		}
		else if ((*kok)->sol_eleman == NULL)
		{
			*kok = (*kok)->sag_eleman;
			(*kok)->yukseklik++;
			free(gecici);
		}
		else
		{
			AVL* en_kucuk_dugum = (*kok)->sag_eleman;
			
			// Değişim için geçici değer.
			int deger = (*kok)->deger;

			while (en_kucuk_dugum->sol_eleman != NULL)
			{
				en_kucuk_dugum = en_kucuk_dugum->sol_eleman;
			}

			(*kok)->deger = en_kucuk_dugum->deger;
			en_kucuk_dugum->deger = deger;

			AVLDugumSil(&((*kok)->sag_eleman), deger);
		}
	}

	AVLYukseklikGuncelle(*kok);
	denge = AVLDengeHesapla(*kok);

	if (denge < -1 && AVLDengeHesapla((*kok)->sag_eleman) < 0)
	{
		printf("Sol rotasyon yapildi.\n");
		AVLSolRotasyon(kok);
	}
	else if (denge < -1 && AVLDengeHesapla((*kok)->sag_eleman) > 0)
	{
		printf("Sag-sol rotasyon yapildi.\n");
		AVLSagRotasyon(&((*kok)->sag_eleman));
		AVLSolRotasyon(kok);
	}
	else if (denge > 1 && AVLDengeHesapla((*kok)->sol_eleman) < 0)
	{
		printf("Sol-sag rotasyon yapildi.\n");
		AVLSolRotasyon(&((*kok)->sol_eleman));
		AVLSagRotasyon(kok);
	}
	else if (denge > 1 && AVLDengeHesapla((*kok)->sol_eleman) > 0)
	{
		printf("Sag rotasyon yapildi.\n");
		AVLSagRotasyon(kok);
	}

	return;
}

void AVLPreOrder(AVL* dugum)
{
	if (dugum == NULL)
	{
		return;
	}
	printf("%3d:%1d:%1d ", dugum->deger, dugum->yukseklik, AVLDengeHesapla(dugum));
	AVLPreOrder(dugum->sol_eleman);
	AVLPreOrder(dugum->sag_eleman);
	return;
}

int main()
{
	AVL* kok = AVLDugumOlustur(100);
	AVLDugumEkle(&kok, 200);
	AVLDugumEkle(&kok, 350);
	AVLDugumEkle(&kok, 300);
	AVLPreOrder(kok);
	printf("\n");
	AVLDugumEkle(&kok, 345);
	AVLPreOrder(kok);
	printf("\n");
	AVLDugumEkle(&kok, 330);
	AVLPreOrder(kok);
	printf("\n");
	AVLDugumSil(&kok, 200);
	AVLPreOrder(kok);
	printf("\n");
}