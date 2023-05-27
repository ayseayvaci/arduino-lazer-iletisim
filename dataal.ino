//Lazer alıcısında çalışacak olan kod bloklarıdır.
// Lazer sensörü ile gönderilen binary formatında gönderilen karakterin alıcı sensör ile 
// ışık farkı yönteminden yararlanılarak algılanması. 
// Daha sonra 8 bitlik gönderilen karakterlerin tekrar binary- decimal dönüşümü işlemi uygulanarak
// karakterin algılanması sağlanır.
// 8 bittin ilk biti sinyal bit kullanılmaz diğer 7 bit ascii değere cevrilmiş karakterlerin
// binary karşılığıdır.
#define NUM_SAMPLES 10

int sensorPin = A0;    // lazer alıcı sensörün takıldığın pin tanımlanıyor
int sensorValue = 0;  // sensörden gelen değişkeni saklamak için kullanılan değişken
double average;       // ortalama değişkeni

void setup() { // Arduino ilk çalışmaya başladığında yapılacak olan işlerin ayarlandığı fonk.
 pinMode(sensorPin,INPUT);// lazer alıcı sensörü giriş olarak ayarlıyoruz
 Serial.begin(9600);// serial ekranı başlatıyoruz
 
  sensorValue = analogRead(sensorPin);// alıcı sensörün ortamın ilk ışık değerini okuyoruz
  average = sensorValue;
  Serial.println(average);// ilk değeri ekrana yazdırıyoruz
}

void loop() {
  
  sensorValue = analogRead(sensorPin);// alıcı sensörün değeri okunuyor

  int bits[8]; // değerleri 0-1 olarak alacağı için bir dizi tanımlanıyor 
  if(sensorValue >average+NUM_SAMPLES) // sensörün okuduğu anlık değer ilk okudugu değerden 
  // büyük olup almadığını kontrol ediyor. Böylelikle ortamdaki ışık  değerinden farklı bir
  // ışık algıyayıp algılanmadığı kontrol edilir. 
  {
    for(int i=0;i<8;i++){ // 8 bitlik bir okuma işlemi yapacağımız için döngü kuruyoruz
      if (analogRead(sensorPin)>average+NUM_SAMPLES){// yine eğer gelen ışık ilk ışıktan büyükse
        // lazerden ışık algıladığı anlamına geliyor.
        
        bits[i]=1;// ışık varsa 1 değeri 
      }
      else{
        bits[i]=0;// yoksa 0 değerini dizinin içine atıyor
      }
      delay(100);
    }
    // Burada ufak bir binary - decimal dönüşümü işlemi yapılıyor.
    double dec=0, j=0,r,n,top;
    for(int i=6;i>=0;i--){
      //Serial.print(bits[i]);
      //Serial.print(":");
      n=bits[i];
      //r=n%10;
      //n/=10;
      dec=dec+(n*pow(2,j));
      //Serial.print(pow(2,j));
      //Serial.print("-");
      //Serial.println(dec);
      j++;
     
      
    }
    int b=dec;
    b=b+1;
    char a=b;// decimal deger char'a cevriliyor böylelikle gönderilen karakter ekrana yazılıyor.
    //Serial.println("");
    //Serial.println(b);
    Serial.print(a);
    delay(1000);
    
    
    }
}
