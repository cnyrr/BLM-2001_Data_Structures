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
	if (dugum == NULL)
	{
		return 0;
	}
	else if (dugum->sol_eleman != NULL && dugum->sag_eleman != NULL)
	{
		return dugum->sol_eleman->yukseklik - dugum->sag_eleman->yukseklik;
	}
	else if (dugum->sol_eleman != NULL)
	{
		return dugum->sol_eleman->yukseklik;
	}
	else if (dugum->sag_eleman != NULL)
	{
		return - dugum->sag_eleman->yukseklik;
	}
	else
	{
		return 0;
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

void AVLSolRotasyon(AVL*** dugum)
{
	// Sola gidecek düğümün adresini tut.
	AVL* gecici = **dugum;
	// Sola gidecek düğüme işaretçiyi, sağ düğümü yap.
	**dugum = (**dugum)->sag_eleman;
	// Sola gidecek düğümün sağı, yerine gelen düğümün soluna işaret etsin.
	(gecici)->sag_eleman = (**dugum)->sol_eleman;
	// Yerine gelen düğümün solu, sola giden düğüme işaret etsin.
	(**dugum)->sol_eleman = gecici;
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

	
	if (denge < -1 && deger > (*kok)->sag_eleman->deger)
	{
		AVLSolRotasyon(&kok);
	}

	AVLYukseklikGuncelle((*kok)->sol_eleman);
	AVLYukseklikGuncelle(*kok);

	return;
}

void AVLPreOrder(AVL* dugum)
{
	if (dugum == NULL)
	{
		return;
	}
	printf("%3d:%2d ", dugum->deger, dugum->yukseklik);
	AVLPreOrder(dugum->sol_eleman);
	AVLPreOrder(dugum->sag_eleman);
	return;
}

int main()
{
	AVL* kok = AVLDugumOlustur(100);
	AVLPreOrder(kok);
	printf("\n");
	AVLDugumEkle(&kok, 200);
	AVLPreOrder(kok);
	printf("\n");
	AVLDugumEkle(&kok, 300);
	AVLPreOrder(kok);
	printf("\n");
}