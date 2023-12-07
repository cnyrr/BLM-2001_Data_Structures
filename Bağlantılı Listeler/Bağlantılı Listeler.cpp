#include <iostream>

struct BagliListe 
{
    int deger;
    BagliListe* sonraki_eleman;
};

BagliListe* ListeDugumOlustur(int deger)
{
    BagliListe* yeni_dugum = NULL;

    yeni_dugum = (BagliListe*) malloc(sizeof(BagliListe));

    if (yeni_dugum == NULL)
    {
        printf("Malloc basarisiz.");
        exit(EXIT_FAILURE);
    }

    yeni_dugum->deger = deger;
    yeni_dugum->sonraki_eleman = NULL;

    return yeni_dugum;
}

void ListeOlustur(BagliListe** yeni_dugum, int deger)
{
    *yeni_dugum = ListeDugumOlustur(deger);

    return;
}

void ListeDegeriDegistir(BagliListe* degisen_eleman, int yeni_deger) 
{
    if (degisen_eleman != NULL) 
    {
        degisen_eleman->deger = yeni_deger;
    }
    return;
}

void ListeBasaDegerEkle(BagliListe** liste_basi, int deger)
{
    BagliListe* yeni_liste_basi = ListeDugumOlustur(deger);

    yeni_liste_basi->sonraki_eleman = *liste_basi;
    *liste_basi = yeni_liste_basi;

    return;
}

void ListeSonaDegerEkle(BagliListe** liste_basi, int deger)
{
    BagliListe* simdiki_dugum = *liste_basi;

    if (simdiki_dugum == NULL)
    {
        *liste_basi = ListeDugumOlustur(deger);
    }
    else
    {
        while (simdiki_dugum->sonraki_eleman != NULL)
        {
            simdiki_dugum = simdiki_dugum->sonraki_eleman;
        }
        simdiki_dugum->sonraki_eleman = ListeDugumOlustur(deger);
    }

    return;
}

void ListeBasaDugumEkle(BagliListe** liste_basi, BagliListe* yeni_dugum)
{
    yeni_dugum->sonraki_eleman = *liste_basi;
    *liste_basi = yeni_dugum;
    return;
}

void ListeSonaDugumEkle(BagliListe** liste_basi, BagliListe* yeni_dugum)
{
    BagliListe* simdiki_dugum = *liste_basi;

    if (yeni_dugum != NULL)
    {
        yeni_dugum->sonraki_eleman = NULL;
    }
    if (simdiki_dugum == NULL)
    {
        *liste_basi = yeni_dugum;
    }
    else
    {
        while (simdiki_dugum->sonraki_eleman != NULL)
        {
            simdiki_dugum = simdiki_dugum->sonraki_eleman;
        }

        simdiki_dugum->sonraki_eleman = yeni_dugum;
    }
    return;
}

void ListeYazdir(BagliListe* liste_basi)
{
    printf("Liste yaziliyor:\n");
    if (liste_basi == NULL)
    {
        printf("Liste bos.\n");
        return;
    }
    while (liste_basi != NULL)
    {
        printf("Adres:%p ", liste_basi);
        printf("%d\n", liste_basi->deger);
        liste_basi = liste_basi->sonraki_eleman;
    }

    return;
}

void ListeKucukDegerleriSil(BagliListe** liste_basi, int buyuk_deger)
{
    BagliListe* onceki_eleman = NULL;
    BagliListe* kontrol_edilen_eleman = *liste_basi;

    while (kontrol_edilen_eleman != NULL)
    {
        if (kontrol_edilen_eleman->deger < buyuk_deger)
        {
            if (onceki_eleman == NULL)
            {
                (*liste_basi) = (*liste_basi)->sonraki_eleman;
                free(kontrol_edilen_eleman);
                kontrol_edilen_eleman = *liste_basi;
            }
            else
            {
                onceki_eleman->sonraki_eleman = kontrol_edilen_eleman->sonraki_eleman;
                free(kontrol_edilen_eleman);
                kontrol_edilen_eleman = onceki_eleman->sonraki_eleman;
            }
        }
        else
        {
            onceki_eleman = kontrol_edilen_eleman;
            kontrol_edilen_eleman = kontrol_edilen_eleman->sonraki_eleman;
        }
    }
    return;
}

void ListeBuyukDegerleriSil(BagliListe** liste_basi, int kucuk_deger)
{
    BagliListe* onceki_eleman = NULL;
    BagliListe* kontrol_edilen_eleman = *liste_basi;

    while (kontrol_edilen_eleman != NULL)
    {
        if (kontrol_edilen_eleman->deger > kucuk_deger)
        {
            if (onceki_eleman == NULL)
            {
                (*liste_basi) = (*liste_basi)->sonraki_eleman;
                free(kontrol_edilen_eleman);
                kontrol_edilen_eleman = *liste_basi;
            }
            else
            {
                onceki_eleman->sonraki_eleman = kontrol_edilen_eleman->sonraki_eleman;
                free(kontrol_edilen_eleman);
                kontrol_edilen_eleman = onceki_eleman->sonraki_eleman;
            }
        }
        else
        {
            onceki_eleman = kontrol_edilen_eleman;
            kontrol_edilen_eleman = kontrol_edilen_eleman->sonraki_eleman;
        }
    }
    return;
}

void ListeEsitDegerleriSil(BagliListe** liste_basi, int aranan_deger)
{
    BagliListe* onceki_eleman = NULL;
    BagliListe* kontrol_edilen_eleman = *liste_basi;

    while (kontrol_edilen_eleman != NULL)
    {
        if (kontrol_edilen_eleman->deger == aranan_deger)
        {
            if (onceki_eleman == NULL)
            {
                (*liste_basi) = (*liste_basi)->sonraki_eleman;
                free(kontrol_edilen_eleman);
                kontrol_edilen_eleman = *liste_basi;
            }
            else
            {
                onceki_eleman->sonraki_eleman = kontrol_edilen_eleman->sonraki_eleman;
                free(kontrol_edilen_eleman);
                kontrol_edilen_eleman = onceki_eleman->sonraki_eleman;
            }
        }
        else
        {
            onceki_eleman = kontrol_edilen_eleman;
            kontrol_edilen_eleman = kontrol_edilen_eleman->sonraki_eleman;
        }
    }
    return;
}

void ListeTekCiftOlustur(BagliListe* liste_basi, BagliListe** tekli_liste, BagliListe** ciftli_liste) {
    
    BagliListe* kontrol_edilen_eleman = liste_basi;

    while (kontrol_edilen_eleman != NULL)
    {
        if (kontrol_edilen_eleman->deger % 2 == 1) {
            ListeSonaDegerEkle(tekli_liste, kontrol_edilen_eleman->deger);
        }
        else
        {
            ListeSonaDegerEkle(ciftli_liste, kontrol_edilen_eleman->deger);
        }
        kontrol_edilen_eleman = kontrol_edilen_eleman->sonraki_eleman;
    }
    return;
}

void ListeTekCiftBol(BagliListe** bolunen_liste, BagliListe** tekli_liste)
{
    BagliListe* onceki_eleman = NULL;
    BagliListe* siradaki_eleman = *bolunen_liste;

    while (siradaki_eleman != NULL)
    {
        if (siradaki_eleman->deger % 2 != 0)
        {
            if (onceki_eleman == NULL)
            {
                *bolunen_liste = siradaki_eleman->sonraki_eleman;
                ListeSonaDugumEkle(tekli_liste, siradaki_eleman);
                siradaki_eleman = *bolunen_liste;
            }
            else
            {
                onceki_eleman->sonraki_eleman = siradaki_eleman->sonraki_eleman;
                ListeSonaDugumEkle(tekli_liste, siradaki_eleman);
                siradaki_eleman = onceki_eleman->sonraki_eleman;
            }
        }
        else
        {
            onceki_eleman = siradaki_eleman;
            siradaki_eleman = siradaki_eleman->sonraki_eleman;
        }
    }

    return;
}

void ListeArtanSiraliDegerEkle(BagliListe** liste_basi, int eklenen_deger) {
    BagliListe* onceki_eleman = NULL;
    BagliListe* simdiki_eleman = *liste_basi;
    BagliListe* eklenecek_eleman = ListeDugumOlustur(eklenen_deger);

    while (simdiki_eleman != NULL && simdiki_eleman->deger <= eklenen_deger)
    {
        if (simdiki_eleman->deger == eklenen_deger) return;
        onceki_eleman = simdiki_eleman;
        simdiki_eleman = simdiki_eleman->sonraki_eleman;
    }
    if (simdiki_eleman == *liste_basi)
    {
        eklenecek_eleman->sonraki_eleman = *liste_basi;
        *liste_basi = eklenecek_eleman;
    }
    else
    {
        onceki_eleman->sonraki_eleman = eklenecek_eleman;
        eklenecek_eleman->sonraki_eleman = simdiki_eleman;
    }
    return;
}

void ListeArtanSiraliElemanEkle(BagliListe** liste_basi, BagliListe* eklenen_eleman)
{
    BagliListe* onceki_eleman = NULL;
    BagliListe* simdiki_eleman = *liste_basi;

    while (simdiki_eleman != NULL && simdiki_eleman->deger <= eklenen_eleman->deger)
    {
        if (simdiki_eleman->deger == eklenen_eleman->deger) return;
        onceki_eleman = simdiki_eleman;
        simdiki_eleman = simdiki_eleman->sonraki_eleman;
    }
    if (simdiki_eleman == *liste_basi)
    {
        eklenen_eleman->sonraki_eleman = *liste_basi;
        *liste_basi = eklenen_eleman;
    }
    else
    {
        onceki_eleman->sonraki_eleman = eklenen_eleman;
        eklenen_eleman->sonraki_eleman = simdiki_eleman;
    }
    return;
}

void ListeInsertSort(BagliListe** liste_basi) {
    BagliListe* koparilan_eleman = NULL;
    BagliListe* siradaki_eleman = NULL;

    BagliListe* onceki_eleman = NULL;
    BagliListe* simdiki_eleman = NULL;

    if (*liste_basi == NULL || (*liste_basi)->sonraki_eleman == NULL)
    {
        return;
    }

    siradaki_eleman = (*liste_basi)->sonraki_eleman;
    (*liste_basi)->sonraki_eleman = NULL;

    while (siradaki_eleman != NULL)
    {   
        koparilan_eleman = siradaki_eleman;
        siradaki_eleman = siradaki_eleman->sonraki_eleman;
        simdiki_eleman = (*liste_basi);

        while (simdiki_eleman != NULL && simdiki_eleman->deger < koparilan_eleman->deger)
        {
            onceki_eleman = simdiki_eleman;
            simdiki_eleman = simdiki_eleman->sonraki_eleman;
        }
        if (simdiki_eleman == *liste_basi)
        {
            koparilan_eleman->sonraki_eleman = *liste_basi;
            *liste_basi = koparilan_eleman;
        }
        else
        {
            koparilan_eleman->sonraki_eleman = simdiki_eleman;
            onceki_eleman->sonraki_eleman = koparilan_eleman;
        }
    }

    return;
}

BagliListe* ListeDizidenCevir(int* dizi_adresi, int dizi_uzunlugu)
{
    BagliListe* liste_basi = NULL;

    for (int i = dizi_uzunlugu - 1; i > -1; i--)
    {
        ListeBasaDegerEkle(&liste_basi, dizi_adresi[i]);
    }
    return liste_basi;
}

void ListeRecursiveYaz(BagliListe* liste_basi) {
    if (liste_basi != NULL)
    {
        printf("%3d", liste_basi->deger);
        ListeRecursiveYaz(liste_basi->sonraki_eleman);
    }

    return;
}

void ListeTerstenRecursiveYaz(BagliListe* liste_basi) {
    if (liste_basi != NULL)
    {   
        ListeTerstenRecursiveYaz(liste_basi->sonraki_eleman);
        printf("%3d", liste_basi->deger);
    }

    return;
}

void ListeSil(BagliListe** liste_basi)
{
    BagliListe* silinen_eleman = *liste_basi;

    while (*liste_basi != NULL)
    {
        silinen_eleman = *liste_basi;
        *liste_basi = (*liste_basi)->sonraki_eleman;
        free(silinen_eleman);
    }

    return;
}

void ListeTersCevir(BagliListe** liste_basi)
{
    BagliListe* onceki_eleman = NULL;
    BagliListe* simdiki_eleman = *liste_basi;

    if (*liste_basi == NULL || (*liste_basi)->sonraki_eleman == NULL)
    {
        return;
    }

    while (simdiki_eleman != NULL)
    {   
        simdiki_eleman = simdiki_eleman->sonraki_eleman;
        (*liste_basi)->sonraki_eleman = onceki_eleman;
        onceki_eleman = *liste_basi;
        *liste_basi = simdiki_eleman;
    }
    *liste_basi = onceki_eleman;

    return;
}

int ListeDegerlerArdisikMi(BagliListe* liste_basi, int ilk_deger, int ikinci_deger)
{
    BagliListe* ilk_eleman = liste_basi;

    if (liste_basi == NULL || ilk_deger == ikinci_deger)
    {
        return 0;
    }

    while (liste_basi != NULL && ilk_eleman->deger != ilk_deger && ilk_eleman->deger != ikinci_deger)
    {
        ilk_eleman = liste_basi;
        liste_basi = liste_basi->sonraki_eleman;
    }
    if (liste_basi != NULL && (ilk_eleman->deger + 1 == ikinci_deger || ilk_eleman->deger - 1 == ikinci_deger))
    {
        return 1;
    }

    return 0;
}

void ListeBirlestir(BagliListe** yeni_liste, BagliListe** eklenecek_liste) {
    BagliListe* simdiki_eleman = *yeni_liste;

    if (simdiki_eleman == NULL)
    {
        *yeni_liste = *eklenecek_liste;
        return;
    }
    
    while (simdiki_eleman->sonraki_eleman != NULL)
    {
            simdiki_eleman = simdiki_eleman->sonraki_eleman;
    }
    simdiki_eleman->sonraki_eleman = *eklenecek_liste;
    *eklenecek_liste = NULL;

    return;
}

int main() 
{
    int cevrilecek_dizi[] = {5,1,6,4,25,0,27,90,3};

    BagliListe* liste = ListeDizidenCevir(cevrilecek_dizi, 9);
    BagliListe* liste2 = NULL;
    ListeYazdir(liste);
    ListeTekCiftBol(&liste, &liste2);
    ListeYazdir(liste);
    ListeYazdir(liste2);
}

