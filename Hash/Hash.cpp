#include <iostream>

#define SENTINEL -1000000000

struct ListeEleman {
    const char* metin;
    ListeEleman* sonraki_eleman;
};

struct HashGozu {
    int sayac;
    ListeEleman* liste_basi;
};

struct HashTablosu {
    HashGozu* tablo_basi;
    int tablo_boyutu;
    int tablo_carpani;
};

ListeEleman* listeElemanOlustur(const char* metin)
{
    ListeEleman* yeni_eleman = (ListeEleman*)malloc(sizeof(ListeEleman));

    if (yeni_eleman == NULL)
    {
        printf("Malloc basarisiz.");
        exit(EXIT_FAILURE);
    }

    yeni_eleman->metin = metin;
    yeni_eleman->sonraki_eleman = NULL;

    return yeni_eleman;
}

HashTablosu* hashTablosuOlustur(int tablo_carpani, int tablo_boyutu)
{
    HashTablosu* yeni_tablo = (HashTablosu*)malloc(sizeof(HashTablosu));

    if (yeni_tablo == NULL)
    {
        printf("Malloc basarisiz.");
        exit(EXIT_FAILURE);
    }

    yeni_tablo->tablo_basi = (HashGozu*)malloc(sizeof(HashGozu) * tablo_boyutu);

    if (yeni_tablo->tablo_basi == NULL)
    {
        printf("Malloc basarisiz.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tablo_boyutu; i++)
    {
        yeni_tablo->tablo_basi[i].sayac = 0;
        yeni_tablo->tablo_basi[i].liste_basi = NULL;
    }

    yeni_tablo->tablo_boyutu = tablo_boyutu;
    yeni_tablo->tablo_carpani = tablo_carpani;

    return yeni_tablo;
}

int hashHesapla(HashTablosu* tablo, const char* girdi)
{
    int sayac = 0;
    int hash = 0;

    if (tablo == NULL || girdi == NULL)
    {
        return SENTINEL;
    }

    while (girdi[sayac] != NULL)
    {
        hash = hash + girdi[sayac] * tablo->tablo_carpani;
        sayac++;
    }
    return hash % tablo->tablo_boyutu;
}

int metinAyniMi(const char* ilk_metin, const char* ikinci_metin)
{
    int sonuc = 1;
    int sayac = 0;

    while (1)
    {   
        if (ilk_metin[sayac] == ikinci_metin[sayac])
        {
            if (ilk_metin[sayac] == NULL)
            {
                break;
            }
            else
            {
                sayac++;
                continue;
            }
        }
        else
        {
            sonuc = 0;
            break;
        }
    }

    return sonuc;
}

int listeElemanSil(ListeEleman** liste_basi, const char* metin)
{
    ListeEleman* onceki_eleman = NULL;
    ListeEleman* simdiki_eleman = *liste_basi;
    int silindi = 0;

    while (simdiki_eleman != NULL && !metinAyniMi(simdiki_eleman->metin, metin))
    {
        onceki_eleman = simdiki_eleman;
        simdiki_eleman = simdiki_eleman->sonraki_eleman;
    }

    if (simdiki_eleman != NULL)
    {
        if (onceki_eleman == NULL)
        {
            *liste_basi = simdiki_eleman->sonraki_eleman;
        }
        else
        {
            onceki_eleman->sonraki_eleman = simdiki_eleman->sonraki_eleman;
        }
        free(simdiki_eleman);
        silindi = 1;
    }

    return silindi;
}

void listeSil(ListeEleman** liste_basi)
{
    ListeEleman* silinen_eleman = *liste_basi;

    while (*liste_basi != NULL)
    {
        silinen_eleman = *liste_basi;
        *liste_basi = (*liste_basi)->sonraki_eleman;
        free(silinen_eleman);
    }

    return;
}

void hashYerlestir(HashTablosu* tablo, const char* yeni_metin)
{
    int hesaplanan_hash = hashHesapla(tablo, yeni_metin);

    if (tablo == NULL || hesaplanan_hash == SENTINEL)
    {
        return;
    }

    ListeEleman* eklenen = listeElemanOlustur(yeni_metin);
    ListeEleman** simdiki = &(tablo->tablo_basi[hesaplanan_hash].liste_basi);

    while (*simdiki != NULL && !metinAyniMi(eklenen->metin, (*simdiki)->metin))
    {
        simdiki = &((*simdiki)->sonraki_eleman);
    }

    if (*simdiki == NULL)
    {
        *simdiki = eklenen;
        tablo->tablo_basi[hesaplanan_hash].sayac++;
    }

    return;
}

void hashDegisimYerlestir(HashTablosu* tablo, ListeEleman* eklenen_eleman)
{
    int hesaplanan_hash = hashHesapla(tablo, eklenen_eleman->metin);
    ListeEleman** simdiki = &(tablo->tablo_basi[hesaplanan_hash].liste_basi);

    while (*simdiki != NULL && !metinAyniMi(eklenen_eleman->metin, (*simdiki)->metin))
    {
        simdiki = &((*simdiki)->sonraki_eleman);
    }

    if (*simdiki == NULL)
    {
        *simdiki = eklenen_eleman;
        tablo->tablo_basi[hesaplanan_hash].sayac++;
    }

    eklenen_eleman->sonraki_eleman = NULL;
    return;
}

void hashSil(HashTablosu* tablo, const char* silinecek_metin)
{
    int hesaplanan_hash = hashHesapla(tablo, silinecek_metin);

    if (tablo == NULL || hesaplanan_hash == SENTINEL)
    {
        return;
    }

    if (tablo->tablo_basi[hesaplanan_hash].sayac != 0)
    {
        if (listeElemanSil(&(tablo->tablo_basi[hesaplanan_hash].liste_basi), silinecek_metin))
        {
            tablo->tablo_basi[hesaplanan_hash].sayac--;
        }
    }
    listeElemanSil(&(tablo->tablo_basi[hesaplanan_hash].liste_basi), silinecek_metin);

    return;
}

void hashYazdir(HashTablosu* tablo)
{
    if (tablo == NULL)
    {
        printf("---- HASH TABLOSU BOS ----\n\n");
        return;
    }

    for (int i = 0; i < tablo->tablo_boyutu; i++)
    {
        ListeEleman* simdiki = tablo->tablo_basi[i].liste_basi;
        printf("%3d : (%3d)", i, tablo->tablo_basi[i].sayac);

        while (simdiki != NULL)
        {
            printf(" %s", simdiki->metin);
            simdiki = simdiki->sonraki_eleman;
        }

        printf("\n");
    }
    printf("\n");

    return;
}

void hashTabloSil(HashTablosu** tablo)
{
    if (*tablo == NULL)
    {
        return;
    }

    for (int i = 0; i < (*tablo)->tablo_boyutu; i++)
    {
        if ((*tablo)->tablo_basi[i].sayac != 0)
        {
            listeSil(&((*tablo)->tablo_basi[i].liste_basi));
        }
    }
    free(*tablo);
    *tablo = NULL;

    return;
}

void hashTabloDegistir(HashTablosu** tablo, int tablo_carpani, int tablo_boyutu)
{
    if (*tablo == NULL)
    {
        return;
    }
    HashTablosu* yeni_tablo = hashTablosuOlustur(tablo_carpani, tablo_boyutu);
    ListeEleman* sonraki_eleman = NULL;

    for (int i = 0; i < (*tablo)->tablo_boyutu; i++)
    {
        while ((*tablo)->tablo_basi[i].liste_basi != NULL)
        {
            sonraki_eleman = (*tablo)->tablo_basi[i].liste_basi->sonraki_eleman;
            hashDegisimYerlestir(yeni_tablo, (*tablo)->tablo_basi[i].liste_basi);
            (*tablo)->tablo_basi[i].liste_basi = sonraki_eleman;
        }
    }

    free(*tablo);
    *tablo = yeni_tablo;

    return;
}

int main()
{
    HashTablosu* Tablo = NULL;
    Tablo = hashTablosuOlustur(5, 13);
    hashYerlestir(Tablo, "erzurum");
    hashYerlestir(Tablo, "istanbul");
    hashYerlestir(Tablo, "sivas");
    hashYerlestir(Tablo, "adana");
    hashYerlestir(Tablo, "erzincan");
    hashYerlestir(Tablo, "canakkale");
    hashYazdir(Tablo);
    hashTabloDegistir(&Tablo, 7, 17);
    hashYazdir(Tablo);
    hashTabloSil(&Tablo);
    hashYazdir(Tablo);
    Tablo = hashTablosuOlustur(7, 17);
    hashYerlestir(Tablo, "erzurum");
    hashYerlestir(Tablo, "istanbul");
    hashYerlestir(Tablo, "sivas");
    hashYerlestir(Tablo, "adana");
    hashYerlestir(Tablo, "erzincan");
    hashYerlestir(Tablo, "canakkale");
    hashYazdir(Tablo);

}
