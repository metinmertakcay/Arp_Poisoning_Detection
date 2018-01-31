/**
@author
Name: Metin Mert AKÇAY
E-Mail: metinmertakcayhpalytu@gmail.com
Compiler used: GCC
Operating System Ubuntu(Linux)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 100			//Arp tablosunun bulundugu dosyadan okuma sirasinda okunabilecek maksimum satir boyutu
#define MAC_ADDRESS_SIZE 18		//Mac adresi uzunlugu
#define MAXIMUM_MAC_SIZE 20		//Maksimum sayıda kontrol edilebilecek mac adresi sayisi

/*Bu fonksiyon arp tablosunda bulunan mac adreslerinin bir degiskende saklanmasi islemini gerceklestirir.
@param matrix: Mac adreslerinin yerlestirilecegi degisken
@param line: Arp tablosunun parcalanacak olan satiri
@param row: Mac adresinin yerlestirilecegi matrisin gozu*/
void trimAndSave(char **matrix,char *line,int row)
{
	char delimeter[2] = " ";	//Parcalama aradaki bosluklara gore olacaktir.
	char *token;				//Parcalama islemi sirasinda kullanilacak olan degisken
	int i = 0;					//Sayma amaciyla tutulmus degisken

	//Strtok ile sting parcalama islemine baslaniliyor
	token = strtok(line,delimeter);
	//Parcalanacak eleman kalmayincaya kadar islem devam edecektir.
	while(token != NULL)
	{
		//Arp tablosunda mac adresi 4. sutuna denk gelmektedir.
		if(i % 5 == 3)
		{
			//Mac bilgisi matrise yerlestiriliyor
			strcpy(matrix[row],token);
		}
		token = strtok(NULL,delimeter);
		i++;
	}
}

/*Bu fonksiyon bellekten dinamik olarak yer acilmasi icin olusturulmustur
@return matrix: Dinamik olarak bellekten yer acilmis olan matris geriye dondurulur.*/
char **dinamicMemoryAllocation()
{
	char **matrix;
	int i;

	//Matrisin satiri icin yer acma islemi gerceklestiriliyor
	matrix = (char **)malloc(sizeof(char *)*MAXIMUM_MAC_SIZE);
	//Matris satirlari icin yerin acilip acilmadigi kontrol elediliyor
	if(matrix == NULL)
	{
		printf("\nBellekte yer acilamamistir");
		exit(0);
	}
	for(i=0 ; i<MAXIMUM_MAC_SIZE ;i++)
	{
		//Matrisin sutunlari icin dinamik olarak bellekten yer ayriliyor.
		matrix[i] = (char *)malloc(sizeof(char)*MAC_ADDRESS_SIZE);
		//Matris sutunu icin yer acilip acilmadigi kontrol ediliyor.
		if(matrix[i] == NULL)
		{
			printf("\nBellekte yer acilamamistir");
			exit(0);
		}
	}
	return matrix;
}

/*Bu fonksiyon arp tablosunda ayni mac adresinin tekrar edip etmedigi kontrolu yapilir.
@param matrix: Mac adreslerinin tutuldugu matris
@param size: Toplamda kac tane mac adresi oldugu bilgisi
@return 1: Arp poisoning saldirisi oldugu yani ayni mac adresinden birden fazla oldugu bilgisidir.
@return 0: Herhangi bir sorun yoktur bilgisi dondurulur*/
int searchDuplicate(char **matrix,int size)
{
	int i,j;		//indisleme amaciyla kullanilmistir.

	for(i=0 ; i<size ;i++)
	{
		for(j=i+1 ; j<size ;j++)
		{
			if(!strcmp(matrix[i],matrix[j]))
			{
				return 1;
			}
		}
	}
	return 0;
}

/*Bu fonksiyon aldigi parametreyi kontrol ederek apr poisoning olup olmadigini kontrol eder.
@param result: Arp poisoning olup olmadigini belirleyecek olan degisken*/
void sendMessage(int result)
{
	//Arp saldirisi icin gonderilen mesaj
	if(result == 1)
	{
		printf("\n*************\n");
		printf("Bulundugunuz agda arp saldirisi bulunmaktadir");
		printf("\n*************\n");
		getchar();
	}
}

/*Bu fonksiyon arp tablosunun alinmasi islemini gerceklestirir.*/
void getArpTable()
{
	char filename[] = "/proc/net/arp";			//Arp tablosunun bulundugu dizin
	FILE *file;									//Dosya gostericisi
	char *line;									//Dosyadan okuma islemi icin olusturulmus degisken
	char **mac_addr;							//Mac adreslerinin tutulacagi matris
	int i, j = 0;								//Indis olarak kullanilmistir.
	int result; 								//Birden fazla ayni mac adresinin olup olmadigiyla ilgili mesaji tutacak olan degisken.

	//Dosya read formatinda aciliyor
	file = fopen(filename,"r");
	//Dosyanin acilip acilmadigi kontrol ediliyor
	if(file == NULL)
	{
		printf("\nDosya acilamamistir.");
		exit(0);
	}
	//Arp tablosu bilgileri tutulmasinda kullanilacak olan degisken icin bellekten yer aciliyor.
	line = (char *)malloc(sizeof(char)*LINE_SIZE);
	//Degisken icin yer acilip acilmadigi kontrol ediliyor.
	if(line == NULL)
	{
		printf("\nBellekte yer acilamamistir.");
		exit(0);
	}
	//Dinamik olarak yer acilma islemi gerceklestiriliyor.
	mac_addr = dinamicMemoryAllocation();
	i = 0;
	//Arp tablosunda bulunan ve gereksiz olan seyi(ilk satirdaki bilgiler) almamak icin 1 kere bos okuma yapiliyor
	fgets(line,LINE_SIZE,file);
	//Arp bilgilerinin okunmasina baslaniyor.
	while(fgets(line,LINE_SIZE,file) != NULL)
	{
		trimAndSave(mac_addr,line,i);
		i++;
	}
	result = searchDuplicate(mac_addr,i);
	sendMessage(result);
	//Matris icin acilan yer bellege iade ediliyor.
	for(i=0 ; i< MAXIMUM_MAC_SIZE ;i++)
	{
		free(mac_addr[i]);
	}
	free(mac_addr);
	fclose(file);		//Dosya stream kapaniyor
}

int main()
{
	char **dinamicMemoryAllocation();
	void trimAndSave(char **,char *,int);
	int searchDuplicate(char **,int);
	void sendMessage(int result);
	void getArpTable();

	while(1)
	{
        //Arp bilgilerinin alinmasi icin ilgili fonksiyon cagriliyor.
		getArpTable();
	}
}
