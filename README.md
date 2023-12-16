# Description Turkish

ASCII karakterler yerine haberleşme binary ile yapılması hedeflenmiştir. Özel olarak belirlenen mesajlama formatı ile haberleşme yapılmıştır. 

Mesaj formatı 2 Byte Başlangıç etiketi 0xFEFD , 2 Byte Veri Paketi Uzunluğu , 1 Byte Mesaj Tipi , N Byte Mesaj Verisi , 1 Byte Reserve ve 2 Byte bitiş etiketi 0xFDFE olacak şekildedir.

LL Low level kütüphane kullanılarak uart ve interrupt çalıştırılmıştır. 

Circular_Buffer ve Circular_Queue içermektedir.
Buffer uzunluğu 512 ve Queue uzunluğu 16 arraydir.

State Machine yapısı ile gelen verilerin kontrolü sağlanmıştır. Gelen bütün veriler 512 byte'lık buffer içerisinde tutulur.(Head) 

Eğer state machine'de son aşamaya kadar veriler başarıyla ulaşırsa yani bitiş etiketi olan 0xFDFE gelince mesaj circular queue'ye aktarılır böylelikle okuma işlemi tamamlanmış olur. (Tail) 

State machine içerisinde aşamalar arası aksıklık olması halinde başa dönmesi için önlemler alınmıştır.

Kurduğum yapıyı daha iyi anlamak için stm32 f401re üzerinde bulunan led'i binary mesaj formatı ile kontrol etmesi hedeflendi.
Bunun için queue içerisindeki mesaj verisini anlamlandıracak fonksiyon oluşturuldu ve mesaj tipi eğer 0x01 ise led durumu flag ini kontrol etmesi, eğer 0x02 gelirse led blink kontrolünü sağlayan flag inin aktifleşmesi ve eğer 0x 03 gelirse'de led pwm ile kontrolünü sağlayan flag aktifleşmesi şeklinde yorumladım. 

Daha sonrasında Mesaj verisi içerisindede parametre verisini alması hedeflendi ancak o kısmı yapmadım.

# Description English 

Communication is intended to be done using binary instead of ASCII characters. Communication has been established with a specifically defined messaging format.

The message format consists of a 2-byte Start tag (0xFEFD), 2-byte Data Packet Length, 1-byte Message Type, N-byte Message Data, 1-byte Reserve, and a 2-byte End tag (0xFDFE).

The Low-Level (LL) library is used to run UART and interrupts.

The project includes Circular_Buffer and Circular_Queue.
The buffer length is 512, and the queue length is an array of 16.

The control of incoming data is ensured with a State Machine structure. All incoming data is kept in a 512-byte buffer (Head).

If the data successfully reaches the final stage in the state machine, i.e., when the end tag 0xFDFE is received, the message is transferred to the circular queue, completing the reading process (Tail).

Precautions have been taken for the state machine to loop back to the beginning in case of a discrepancy between stages.

To better understand the structure I established, the goal was to control the LED on the STM32 F401RE using the binary message format.
For this purpose, a function was created to interpret the message data in the queue. If the message type is 0x01, it checks the LED status flag; if 0x02 is received, it activates the flag for controlling LED blink, and if 0x03 is received, it activates the flag for controlling LED with PWM.

Later on, the goal was to extract parameter data from the message data, but I haven't implemented that part yet.
