#include <iostream>

struct dugum {
    int deger;
};

struct xheap {
    dugum* dizi;
    int kapasite;
    int eleman_sayisi;
};

xheap* xheapOlustur(int kapasite)
{
    xheap* heap = (xheap*)malloc(sizeof(xheap));

    if (heap == NULL || kapasite == 0)
    {
        printf("Malloc basarisiz.");
        exit(EXIT_FAILURE);
    }

    heap->dizi = (dugum*)malloc(kapasite * sizeof(dugum));

    if (heap->dizi == NULL)
    {
        printf("Malloc basarisiz.");
        exit(EXIT_FAILURE);
    }

    heap->kapasite = kapasite;
    heap->eleman_sayisi = 0;

    return heap;
}

void xheapBuyut(xheap* heap, int kapasite_carpani)
{   
    dugum* yeni_dizi = (dugum*)malloc(heap->kapasite * kapasite_carpani * sizeof(dugum));

    if (yeni_dizi == NULL) 
    {
        printf("Malloc basarisiz.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < heap->eleman_sayisi; i++)
    {
        yeni_dizi[i].deger = heap->dizi[i].deger;
    }

    free(heap->dizi);
    heap->dizi = yeni_dizi;
    heap->kapasite = heap->kapasite * kapasite_carpani;

    return;
}

void xheapBubleUp(xheap* heap, int indis)
{
    int gecici = 0;
    int ust_indis = (indis - 1) / 2;
    
    while (heap->dizi[ust_indis].deger < heap->dizi[indis].deger)
    {
        gecici = heap->dizi[ust_indis].deger;
        heap->dizi[ust_indis].deger = heap->dizi[indis].deger;
        heap->dizi[indis].deger = gecici;
        indis = ust_indis;
        ust_indis = (indis - 1) / 2;
    }
    return;
}

void xheapBubleDown(xheap* heap, int indis)
{
    int gecici;
    int sol_indis = 2 * indis + 1;
    int sag_buyuk = 0;

    while (sol_indis < heap->eleman_sayisi)
    {
        sag_buyuk = 0;
        if (sol_indis + 1 < heap->eleman_sayisi && heap->dizi[sol_indis + 1].deger > heap->dizi[sol_indis].deger)
        {
            sag_buyuk = 1;
        }
        
        if (heap->dizi[indis].deger < heap->dizi[sol_indis + sag_buyuk].deger)
        {
            gecici = heap->dizi[indis].deger;
            heap->dizi[indis].deger = heap->dizi[sol_indis + sag_buyuk].deger;
            heap->dizi[sol_indis + sag_buyuk].deger = gecici;
            indis = sol_indis + sag_buyuk;
            sol_indis = 2 * indis + 1;
        }
        else
        {
            break;
        }

    }

    return;
}

void xheapYazdir(xheap* heap)
{
    printf("Kapasite: %d\nEleman sayisi: %d\n", heap->kapasite, heap->eleman_sayisi);
    for (int i = 0; i < heap->eleman_sayisi; i++)
    {
        printf("%4d", heap->dizi[i].deger);
    }
    printf("\n");
    return;
}

void xheapEkle(xheap* heap, int eklenen_deger)
{
    if (heap->kapasite == heap->eleman_sayisi)
    {
        xheapBuyut(heap, 2);
    }

    heap->dizi[heap->eleman_sayisi].deger = eklenen_deger;
    heap->eleman_sayisi++;

    xheapBubleUp(heap, heap->eleman_sayisi - 1);
    return;
}

void xheapMaxSil(xheap* heap)
{
    int gecici;
    if (heap->eleman_sayisi == 0)
    {
        return;
    }
    if (heap->eleman_sayisi == 1)
    {
        heap->eleman_sayisi = 0;
        return;
    }
    gecici = heap->dizi[0].deger;
    heap->dizi[0].deger = heap->dizi[heap->eleman_sayisi - 1].deger;
    heap->dizi[heap->eleman_sayisi - 1].deger = gecici;

    heap->eleman_sayisi--;

    xheapBubleDown(heap, 0);

    return;
}

void xheapDuzelt(xheap* heap)
{
    for (int i = 0; i < ((heap->eleman_sayisi - 2) / 2) + 1; i++)
    {
        xheapBubleDown(heap, ((heap->eleman_sayisi - 1) / 2) - i);
    }

    return;
}

void xheapSort(xheap* heap)
{
    int tekrar = heap->eleman_sayisi - 1;

    for (int sayac = 0; sayac < tekrar; sayac++)
    {
        xheapMaxSil(heap);
    }
    heap->eleman_sayisi = tekrar + 1;

    return;
}

int main()
{
    xheap* heap = xheapOlustur(2);
    xheapEkle(heap, 50);
    xheapEkle(heap, 25);
    xheapEkle(heap, 30);
    xheapEkle(heap, 15);
    xheapEkle(heap, 100);
    xheapEkle(heap, 80);
    xheapEkle(heap, 90);
    xheapEkle(heap, 107);
    xheapYazdir(heap);
    xheapMaxSil(heap);
    xheapYazdir(heap);
    xheapMaxSil(heap);
    xheapYazdir(heap);
    xheapSort(heap);
    xheapYazdir(heap);
    xheapDuzelt(heap);
    xheapYazdir(heap);
}

