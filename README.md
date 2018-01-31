## Program Nasıl Çalıştırılır ##

Arp poisoning saldırısının tespit edilebilmesi için geliştirilen program C programlama dili ile yazılmıştır. Programının çalıştırılabilmesi için şu adımlar izlenmelidir.

    gcc -o APD Arp_Poisoning_Detection.c
    ./APD

## Programda Kullanılan Parametreler ##
Program dışarıdan parametre almamaktadır. Fonksiyonlarda kullanılmış olan parametreler program içerisinde yorum satırları ile açıklanmıştır. Arp tablosunun kullanılabilmesi için arp tablosunun bulunduğu dizin kullanılmıştır. Bu dizin dosya açılması sırasında parametre olarak verilmiştir. 

    Arp tablosunun bulunduğu dizin : /proc/net/arp

## Arp Poisoning Saldırısının Yapılması ##
Arp poisoning saldırısının yapılarak çıktının gözlemlenebilmesi için ettercap programı kullanılmıştır. Program ilk açıldığı zaman "sniff" sekmesi altından "unified sniffing" seçilir. Ağdaki bütün adreslerin gözlemlenebilmesi için "host" sekmesi altında "scan for host'a" tıklanır. "Host list" ile bütün adresler gözlemlenir ve bu adresler içerisinden saldırı yapılacak olan adresler target olarak seçilir. Saldırısının başlatılabilmesi için "mitm" sekmesi altında "arp poisoning" seçilir ve saldırı başlatılır.

## Program Çıktısı ##
Arp poisoning saldırısı tespit edilmesi sonucu kullanıcıyı bilgilendirmek için ekrana

    ********************
    Bulunduğunuz ağda arp saldırısı vardır.
    ********************   
   seklinde bilgi mesajı verilmiştir. 

## Çıktı Nasıl Yorumlanır ##
Arp poisoning saldırısı olduğu bilgisi alındıktan sonra command line açılıp 

    arp
komutu girilerek arp tablosunda bir mac adresinin birden fazla kez tekrar ettiği gözlemlenebilir. Böylelikle arp poisoning saldırısı olduğu arp tablosuna bakılarak da anlaşılabilir.    

 
 
