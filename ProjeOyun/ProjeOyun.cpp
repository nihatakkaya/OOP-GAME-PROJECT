#include <iostream>
#include <clocale>
#include <random>
#include <time.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std;

#define RED     "\033[31m"
#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define GREEN "\033[32m"
#define BLUE    "\033[34m"


class Ozellikler
{
protected:
    int can = 100;
    int aclik = 0;
    int susuzluk = 0;
    int konumX = 0;
    int konumZ = 0;
    int konumSag;
    int konumSol;
    int konumIleri;
    int konumGeri;
    int secim;
    int para = 100;


public:
    Ozellikler() = default;

    Ozellikler(int can, int aclik, int susuzluk, int konumX, int konumZ, int konumSag, int konumSol, int konumIleri, int konumGeri, int secim, int para)
        : can(can), aclik(aclik), susuzluk(susuzluk), konumX(konumX), konumZ(konumZ), konumSag(konumSag), konumSol(konumSol), konumIleri(konumIleri), konumGeri(konumGeri), secim(secim), para(para) {
    }
};



class karakter : public Ozellikler
{

public:
    int dongu;

    karakter() : dongu(0) {}

    karakter(int can, int aclik, int susuzluk, int konumX, int konumZ, int konumSag, int konumSol, int konumIleri, int konumGeri, int secim, int para, int dongu)
        : Ozellikler(can, aclik, susuzluk, konumX, konumZ, konumSag, konumSol, konumIleri, konumGeri, secim, para), dongu(dongu) {
    }
    void oyun()
    {

        dongu = 1;
        while (dongu)
        {

            cout << "" << endl;
            cout << "Yapmak istediğiniz işlemi seçiniz" << endl;
            cout << "" << endl;
            cout << YELLOW << "1- Sağa git " << endl << "2- Sola git " << endl << "3- İleri git " << endl << "4- Geri git " << endl << "5- Yemek ye " << endl << "6- Su iç " << endl << "7- Para Gönder " << endl << "8-Karakteri Uyut " << RESET << endl;
            cin >> secim;

            switch (secim)
            {
            case 1:

                hareketSaga();
                susuzlukVeAclikDurumuAzal();
                canAzalma();

                break;

            case 2:

                hareketSola();
                susuzlukVeAclikDurumuAzal();
                canAzalma();

                break;

            case 3:

                hareketIleri();
                susuzlukVeAclikDurumuAzal();
                canAzalma();

                break;

            case 4:

                hareketGeri();
                susuzlukVeAclikDurumuAzal();
                canAzalma();

                break;

            case 5:
                yemekYeme();

                break;

            case 6:
                susuzlukArttir();

                break;

            case 7:
                paraAktarimi();

                break;

            case 8:
                uyut();

                break;
            }

            this_thread::sleep_for(chrono::seconds(2));
            system("cls");

            if (can <= 0)
            {
                cout << RED << "X-X-X-X-X-X-X-X-X-X-X-X-X-X" << endl;
                cout << "!!!    KARAKTER ÖLDÜ    !!!" << endl;
                cout << "X-X-X-X-X-X-X-X-X-X-X-X-X-X" << RESET << endl;
                cout << "" << endl;
                for (int i = 0; i < 3; ++i) { // ölüm ses efekti      
                    Beep(1500, 3000);
                    Sleep(3000);
                }
                break;
            }

        }
    }

    // Sağa hareket etme 
    void hareketSaga()
    {
        this->konumSol = konumSol;
        this->konumSag = konumSag;
        this->konumX = konumX;
        this->konumZ = konumZ;

        cout << "Kaç metre gitmek istediğinizi giriniz: ";
        cin >> konumSag;
        cout << "" << endl;
        cout << "Karakter " << konumSag << " metre sağa gitmiştir" << endl;

        konumX = konumX + konumSag;
        cout << "konumunuz yatay:" << konumX << " dikey:" << konumZ << endl;
        cout << "" << endl;

    }

    // Sola hareket etme 
    void hareketSola()
    {
        this->konumSol = konumSol;
        this->konumSag = konumSag;
        this->konumX = konumX;
        this->konumZ = konumZ;

        cout << "Kaç metre gitmek istediğinizi giriniz: ";
        cin >> konumSol;
        cout << "" << endl;
        cout << "Karakter " << konumSol << " metre sola gitmiştir" << endl;

        konumX = konumX - konumSol;
        cout << "konumunuz yatay:" << konumX << " dikey:" << konumZ << endl;
        cout << "" << endl;

    }

    // İleri hareket etme 
    void hareketIleri()
    {

        this->konumSol = konumSol;
        this->konumSag = konumSag;
        this->konumX = konumX;
        this->konumZ = konumZ;

        cout << "Kaç metre gitmek istediğinizi giriniz: ";
        cin >> konumIleri;
        cout << "" << endl;
        cout << "Karakter " << konumIleri << " metre ileri gitmiştir" << endl;

        konumZ = konumZ + konumIleri;
        cout << "konumunuz yatay:" << konumX << " dikey:" << konumZ << endl;
        cout << "" << endl;

    }

    // Geri hareket etme 
    void hareketGeri()
    {
        this->konumSol = konumSol;
        this->konumSag = konumSag;
        this->konumX = konumX;
        this->konumZ = konumZ;

        cout << "Kaç metre gitmek istediğinizi giriniz: ";
        cin >> konumGeri;
        cout << "" << endl;
        cout << "Karakter " << konumGeri << " metre geri gitmiştir" << endl;

        konumZ = konumZ - konumGeri;
        cout << "konumunuz yatay:" << konumX << " dikey:" << konumZ << endl;
        cout << "" << endl;

    }


    // Yemek yeme 
    void yemekYeme()
    {
        this->aclik = aclik;
        if (aclik < 15)
        {
            cout << "Karakterin karnı tok" << endl;
        }
        else
        {
            aclik = aclik - 15;
            cout << BLUE << "AFİYET OLSUN" << RESET << endl;
            cout << "Yemek İhtiyacı: %" << aclik << endl;
        }

    }

    // Susuzluk seviyesi arttırma 
    void susuzlukArttir()
    {
        this->susuzluk = susuzluk;
        if (susuzluk < 20)
        {
            cout << "Karakter henüz susamadı" << endl;
        }
        else
        {
            susuzluk = susuzluk - 20;
            cout << BLUE << "AFİYET OLSUN" << RESET << endl;

            cout << "Su İhtiyacı: %" << susuzluk << endl;
        }

    }

    void susuzlukVeAclikDurumuAzal()
    {
        this->aclik = aclik;
        this->susuzluk = susuzluk;

        aclik = aclik + 10;
        susuzluk = susuzluk + 15;
        cout << "Yemek İhtiyacı: %" << aclik << endl << "Su İhtiyacı: %" << susuzluk << endl;

    }

    void canAzalma()
    {
        this->aclik = aclik;
        this->susuzluk = susuzluk;

        if (aclik > 80)
        {
            can = can - 20;
            cout << " " << endl;
            cout << RED << "Karakter çok aç olduğu için canı 20 azaldı.  Yeni can: " << can << RESET << endl;
        }

        if (susuzluk > 65)
        {
            can = can - 20;
            cout << " " << endl;
            cout << RED << "Karakter çok susadığı için canı 20 azaldı. Yeni can: " << can << RESET << endl;
        }

    }

    void paraAktarimi()
    {
        this->para = para;
        int miktar;
        cout << "Mevcut Bakiye : " << para << endl;
        cout << "Kaç para göndermek istiyorsun: ";
        cin >> miktar;
        cout << "" << endl;

        try {
            if (para < miktar) { 
                throw runtime_error(RED "O kadar paran yok :(" RESET); }
            else { 
                cout << miktar << " TL Gönderildi." << endl; 
                cout << "Kalan Para: " << (para = para - miktar) << " TL" << endl; 
            } 
        }
        catch (const runtime_error& e)
        { 
            cout << e.what() << endl; 
        }


    }


    void uyut()
    {
        int saniye = 3;
        clock_t endwait;
        endwait = clock() + saniye * CLOCKS_PER_SEC;
        cout << "Karakter uykuya geçti." << endl;
        while (clock() < endwait) {}


        endwait = clock() + saniye * CLOCKS_PER_SEC;
        cout << "Karakter uyandı." << endl;

    }

};



int main()

{
    string hazir;

    setlocale(LC_ALL, "Turkish");
    cout << GREEN << "*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << "**HOŞGELDİN, HAZIR MISIN**" << endl;
    cout << "*-*-*-*-*-*(E/H)*-*-*-*-*" << RESET << endl;
    cout << "" << endl;


    for (int i = 0; i < 3; ++i) { // kalp atışı efekti
        Beep(900, 300);
        Sleep(400);
        Beep(900, 300);
        Sleep(500);
    }

    cin >> hazir;
    if (hazir == "E" || hazir == "e") {
        karakter Nihat;
        karakter Ece;
        Nihat.oyun();
    }
    else if (hazir == "H" || hazir == "h") {
        cout << " " << endl;
        cout << "Hazır Olduğunda Tekrar Gel :(" << endl;
        cout << " " << endl;
    }
    else {
        cout << "Hatalı Giriş Yaptınız." << endl;
    }


    system("pause");
    return 0;
}