// Lazer sensörde çalışacak olan kod blokları
// Bu kısımda serial ekranına yazılan yazı karakterleri ascii değerine çevrilir
// daha sonra ascii değerleri binary çevrilir.
// Her bir karakter 7 bitliktir.
// Lazer sensörüde binary değerine göre 8 kere yanıp söner.

int ledPin = 13; // lazer sensörünün takıldığı pin      

int c=0;


void setup() {                
  pinMode(ledPin, OUTPUT); // lazeri çıkış olarak ayarlıyoruz
    
  Serial.begin(9600);

}

void loop() {
  int k=0;
  byte n;
  while (Serial.available() > 0) {// Serial ekranından okuma yapmak için ekran da veri olup olamdığı
                                  // kontrol ediliyor.      
    n = Serial.read(); // Serial ekranından byte olarak bir okuma yapılıyor
    Serial.print(char(n));// char karsılığı ekrana yazdırılıyor
    long i;
    char bits[8];
    int x=0;
    
    digitalWrite(ledPin, HIGH);  // Başlama singalı gönderiliyor ilk.
    delay(50);
    digitalWrite(ledPin, LOW);
    
    for (i = 1 << 6; i > 0; i = i / 2)// C programlamada kullanılan decimal sayıyı 
                                      // binary ye cevirmek için kullanılan bit kaydırma işlemi
    {
      if((n & i) != 0){ // Gelen değer 1 ise lazer yanıyor.
        //Serial.print("1");
       digitalWrite(ledPin, HIGH);}
      else{// Gelen değer 0 ise lazer sönüyor
        //Serial.print("0");
        digitalWrite(ledPin, LOW);}
      delay(100);}
    
    digitalWrite(ledPin, LOW);
    delay(1000);
    }
  } 
