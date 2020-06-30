
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define TONO_ERROR 600

#define TIME_INTERVAL 1000


LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);


int buzzer = 5;            // Pinos buzzer 

int saida = 7;

int vari_horas = 0;            // variavel horas 

int vari_minutos = 0;          // variavel minutos

int vari_segundos = 0;         // variavel segundos

int segundostotal = 0;     // variavel tempo total 

int msg = 0;                // 


int start = A0;            // botao inicio

int vari_inicio = 1024;        // variavel para botao de inicio


int but_horas = A1;             // botao horas

int but_minutos = A2;             // botao minutos

int but_segundos = A3;             // botao segundos


int varbut_horas = 0;           // variavel precionar horas

int varbut_minutos = 0;           // variavel precionar minutos

int varbut_segundos = 0;           // variavel precionar segundos


void setup()

{

   lcd.begin(16, 2);         // Configuração LDC-I2C. 

  

   pinMode(buzzer, OUTPUT);  //Pin de alarme --> Saida

   pinMode(saida, OUTPUT);  //Pin de alarme --> Saida

   pinMode(but_horas, INPUT);     //Pin de botao de horas --> Entrada

   pinMode(but_minutos, INPUT);     //Pin de botao de minutos --> Entrada

   pinMode(but_segundos, INPUT);     //Pin de botao de segundos --> Entrada

   pinMode(start, INPUT);    //Pin de botao de arranque --> Entrada

  

   msg = 0;                  //

   vari_inicio = 1024;           //lim inicio

  

   varbut_horas = 1;              //lim de horas

   varbut_minutos = 1;              //lim de minutos

   varbut_segundos = 1;              //lim de segundos

  

   Serial.begin(9600);

}


void loop()

{

     if(msg==0)             // Mostrar msg de inicio uma única vez

     {

       lcd.setCursor(0,0);

       lcd.print("Temporizador com");

       lcd.setCursor(1,1);

       lcd.print("   Lampada UV   ");

       delay(2500);

       msg = 1;

       lcd.clear();

     }

    

     /*
      * Algoritimo para leitura dos botoes
      */

      do 
      
     {

      

       varbut_horas = analogRead(but_horas);   // leitura botao horas

       varbut_minutos = analogRead(but_minutos);   //leitura botao minutos

       varbut_segundos = analogRead(but_segundos);   //leitura botao segundos

      

       if(varbut_horas > 0)              // Aumentar a variavel horas

       {

        vari_horas = vari_horas + 1 ;

        delay(250);

       } 

      

        if(varbut_minutos > 0)            // Aumentar a variavel minutos

       {

         vari_minutos = vari_minutos + 1;

         if(vari_minutos == 60) vari_minutos = 0;

         delay(250);

       } 

      

        if(varbut_segundos > 0)            // Aumentar a variavel segundos

       {

         vari_segundos = vari_segundos + 1;

         if(vari_segundos == 60) vari_segundos = 0;

         delay(250);

       } 

            

       lcd.setCursor(0,0);

       lcd.print("  Seta o Tempo  ");  //

      

       lcd.setCursor(4,1);    


      if (vari_horas < 10) lcd.print("0");    // Horas menor que 10, seta 0

       lcd.print(vari_horas);                 // Incrementa 1 nas horas

       lcd.print(":");


      if (vari_minutos < 10) lcd.print("0");  // Minutos menor que 10, seta 0

       lcd.print(vari_minutos);               // Incrementa 1 nos minutos


       lcd.print(":");

      if (vari_segundos < 10) lcd.print("0"); // Sergundos menor que 10, seta 0

       lcd.print(vari_segundos);              // Incrementa 1 nos segundos

      

      

     } while(analogRead(start) == 0);  // O menu para escolher a hora é repetido até pressionarmos o botão Iniciar.

    

     segundostotal = vari_segundos + (vari_minutos * 60) + (vari_horas * 60 * 60);  // Converte o tempo escolhido em segundos

      

      /*
       * Quando o botão Iniciar for pressionado e o tempo acumulado, inicia o proximo While
       */

      while (segundostotal > 0)

      {

        delay (1000);          //
        digitalWrite(saida, HIGH);


        segundostotal--;    

  

        vari_horas = ((segundostotal / 60)/ 60);   //Convertemos o total de segundos em horas

        vari_minutos = (segundostotal / 60) % 60;  //Convertemos o total de segundos em minutos

        vari_segundos = segundostotal % 60;        //Convertemos o total de segundos em períodos de 60 segundos


        lcd.setCursor(0,0);

        lcd.print(" Tempo Restante ");        //

 

        lcd.setCursor(4,1);

        if (vari_horas < 10) lcd.print("0");     // Se as horas for inferior a 10, seta um "0" na frente.

        lcd.print(vari_horas);                   // 

        lcd.print(":");


        if (vari_minutos < 10) lcd.print("0");   //Se o minutos for inferior a 10, coloque um "0" na frente.

        lcd.print(vari_minutos);                 // 


        lcd.print(":");

        if (vari_segundos < 10) lcd.print("0");  // Se o segundo valor estiver abaixo de 9, seta 0 antes

        lcd.print(vari_segundos);                // 

       

          if (segundostotal == 0)            // Se o tempo acabar em 0

          { 
                      

             while(1)                        //Loop infinito exibindo mensagem e soando a campainha intermitentemente

             {           

                  lcd.clear();

                  lcd.setCursor(5,0);

                  lcd.print(" Tempo");

                  lcd.setCursor(3,1);

                  lcd.print("Finalizado");

                  digitalWrite(saida, LOW);

                  sonarTono();


                lcd.clear();


                break;               

             }     

          }
         // break;

     }

     

}


    /*
     * Void dos toques do Buzzer 3x
     */

     
void sonarTono()

    {
// Aciona o buzzer na frequencia relativa ao Dó em Hz
    tone(buzzer,261);    
    // Espera um tempo para Desativar
    delay(1000);
    //Desativa o buzzer
    noTone(buzzer); 

    delay(1000);

    tone(buzzer,261);
    delay(1000);
    noTone(buzzer);

    delay(1000);

    
    tone(buzzer,261);
    delay(1000);
    noTone(buzzer);

    }
