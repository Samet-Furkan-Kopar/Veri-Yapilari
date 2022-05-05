#include <iostream>
using namespace std;


struct Dugum {
	int Veri;			//Düğümün sayısal değeri
	Dugum* Sonraki;     //Sonraki düğüme işaretçi
};

struct Kuyruk {
	Dugum* bas;         //Kuyruğun başındaki elemanın adresini tutar.
	Dugum* son;         //Kuyruğun sonundaki elemanın adresini tutar.
	void olustur();     //Başlangıç için gereken tanımları içerir.
	void kapat();       //Program bitimindebellek iadesi yapar.
	void ekle(int);     //Kuyruğa yeni veri ekler.
	int cikar();        //Kuyruktan sıradaki elemanı çıkarır.
	bool bosMu();       //Kuyruk boş mu kontrol eder.
};
struct Yigin {
	Kuyruk k1, k2;      //Yığın için kullanılacak kuyruk değişkenleri
	void olustur();     //Başlangıç için gereken tanımları içerir.
	void kapat();       //Program bitimindebellek iadesi yapar.
	void ekle(int);     //Kuyruğa yeni veri ekler.
	int cikar();        //Kuyruktan sıradaki elemanı çıkarır.
	bool bosMu();       //Kuyruk boş mu kontrol eder.
	int tepe();         //Yığının tepesindeki elemanı okur.
	void yazdir();      //Yığın elemanlarını sırayla ekrana yazar.
};


void siraliEkle(Yigin* s, int x);
void yiginCikar(Yigin* s);

int main()
{
	//std::cout << "";
	Yigin s;
	s.olustur();
	s.ekle(3);
	s.ekle(1);
	s.ekle(7);
	s.ekle(4);
	s.ekle(8);
	cout<< "Orijinal Yigin:" <<endl;
	s.yazdir();
	cout << endl;
	cout << endl;
	yiginCikar(&s);
	cout << "--yiginCikar fonksiyon cagrisi" << "\n";
	s.yazdir();
	cout << endl;
	cout << endl;
	siraliEkle(&s, 6);
	cout << "--Sirali Ekle Yigin:" << "\n";
	s.yazdir();
	
}


void Kuyruk::olustur() {
	bas = NULL, son = NULL;
}
void Kuyruk::kapat() {
	Dugum* p;
	while (bas) {
		p = bas;
		bas = bas->Sonraki;
		delete p;
	}
}

void Kuyruk::ekle(int yeni) {
	Dugum* yenidugum = new Dugum();
	yenidugum->Veri = yeni;
	yenidugum->Sonraki = NULL;
	if (bas == NULL) {
		bas = yenidugum;
		son = bas;
	}
	else {
		son->Sonraki = yenidugum;
		son = yenidugum;
	}
}
int Kuyruk::cikar() {
	Dugum* ustdugum;
	int gecici;
	ustdugum = bas;
	bas = bas->Sonraki;
	gecici = ustdugum->Veri;
	delete ustdugum;
	return gecici;
}
bool Kuyruk::bosMu() {
	return bas == NULL;
}


void Yigin::olustur() {
	k1.bas = NULL;
	k2.bas = NULL;
	k1.son = NULL;
	k2.son = NULL;
}
void Yigin::kapat() {
	Dugum* p;
	while (k1.bas) {
		p = k1.bas;
		k1.bas = k1.bas->Sonraki;
		delete p;
	}
}
void Yigin::ekle(int x) {

	k2.ekle(x);
	while (!k1.bosMu())
	{
		k2.ekle(k1.bas->Veri);
		k1.cikar();
	}
	Kuyruk k = k1;
		   k1 = k2;
		   k2 = k;
}
int Yigin::cikar() {

	if (k1.bosMu())
		return 0;	
	  k1.cikar();

}
bool Yigin::bosMu() {
	return k1.bas == NULL;;
}

int Yigin::tepe(){
	if (k1.bosMu())
		return -1;
	return k1.bas->Veri;
}


void Yigin::yazdir()
{
	while (!k1.bosMu())
	{
		cout << k1.bas->Veri<<" ";
		
		k2.ekle(k1.bas->Veri);
		k1.bas = k1.bas->Sonraki;		
	}
	Kuyruk k = k1;
		   k1 = k2;
	       k2 = k;
}


void siraliEkle(Yigin* s, int x) {

	if (s->bosMu() or x > s->tepe()) {
		s->ekle(x);
		return;
	}

	int temp = s->cikar();
	siraliEkle(s, x);
	s->ekle(temp);
}

void yiginCikar(Yigin* s) {
	if (!s->bosMu()) {
		int x=s->cikar();

		yiginCikar(s);
		siraliEkle(s, x);
	}
}

