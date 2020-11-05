//Este programa tiene dos modos de operación:  1.Modo Passthrough el cual muestra en los leds D0, D1, D2 los valores que se seleccionen en S0, S1, S2.
//2.Modo Analog Reference donde se tiene en cuenta el valor leído de un Potenciómetro, y tenemos un valor de referencia que para nosotros es 534 y con S0, S1, S2 seleccionamos una tolerancia, el led D2  se activa cuando el valor del Potenciómetro supere la tolerancia positiva, el D1 se activa cuando el valor del Potenciómetro entre en el rango permitido por la tolerancia y el D0 se activa cuando el valor del Potenciómetro esté por debajo de la tolerancia negativa. 
//S3 permite seleccionar el modo de operación, alto para el Modo Passthrough y se activa  D3. Bajo Modo Analog Reference  y se desactiva D3. 

//Utilizamos el dipswich alrevez para poder tomar el nivel alto arriba para una mayor facilidad de interpretacion 

 //Autores:Leidy Ximena Garzón y Sebastian Babativa Veloza
 //Versión:1.0


class Passthrough{//clase para el primer modo
  
  private:
  int led1,led2,led3,led4; 
  int DIP1,DIP2,DIP3,DIP4;
  int valor,valor1,valor2,valor3;
  //
 
  public:
    void set_led_puertos(int p1, int p2, int p3, int p4,int di1,int di2,int di3,int di4)
    {
      led1=p1;
      led2=p2;
      led3=p3;
      led4=p4;
      DIP1=di1;  
      DIP2=di2;
      DIP3=di3;
      DIP4=di4;
    }

    void configuracion_led()
    {
      pinMode(led1, OUTPUT);//señal de salida primer led
      pinMode(led2, OUTPUT);//señal de salida segundo led
      pinMode(led3, OUTPUT);//señal de salida tercer led
      pinMode(led4, OUTPUT);//señal de salida cuarto led
      pinMode(DIP1, INPUT);//señal de entrada s3 del dipswich
      pinMode(DIP2, INPUT);//señal de entrada s2 del dipswich
      pinMode(DIP3, INPUT);//señal de entrada s1 del dipswich
      pinMode(DIP4, INPUT);//señal de entrada s0  del dipswich
      
    }  
  
    void set_led()
    {
      valor=digitalRead(DIP1);//valor de s3
      valor1=digitalRead(DIP2);//valor de s2
      valor2=digitalRead(DIP3);//valor de s1
      valor3=digitalRead(DIP4);//valor de s0
      
      if(valor==HIGH)
 
      {   
        digitalWrite(led1, HIGH);//si s3 esta en alto prende D3
      
          if(valor1==HIGH)
        
          digitalWrite(led2, HIGH);//si s2 esta en alto prende D2
           else
          {
             digitalWrite(led2, LOW);
          } 
      
            if(valor2==HIGH)
        
              digitalWrite(led3, HIGH);//si s2 esta en alto prende D1
            else
            {
              digitalWrite(led3, LOW);
            } 
      
               if(valor3==HIGH)
        
                digitalWrite(led4, HIGH);
             else
              {
                digitalWrite(led4, LOW);//si s0 esta en alto prende D0
              } 
      
       }
      
     }
     
  
};
class  Analog_Reference{//clase utilizada para el segundo modo
  private:
  
  int led1,led2,led3,led4;
  int DIP1,DIP2,DIP3,DIP4;
  int valor,valor1,valor2,valor3;
  int Pot,val_pot;
  float tolerancia,valor_ref,tol_pos,tol_neg;
 
  public:
    void set_puertos(int p1, int p2, int p3, int p4,int di1,int di2,int di3,int di4,int puert_pot)
    {
      led1=p1;
      led2=p2;
      led3=p3;
      led4=p4;
      DIP1=di1;
      DIP2=di2;
      DIP3=di3;
      DIP4=di4;
      Pot=puert_pot;
      
    }
  
    void configuracion()
    {
      pinMode(led1, OUTPUT);//señal de salida primer led
      pinMode(led2, OUTPUT);//señal de salida segundo led
      pinMode(led3, OUTPUT);//señal de salida tercer led
      pinMode(led4, OUTPUT);//señal de salida cuarto led
      pinMode(DIP1, INPUT);//señal de entrada s3 del dipswich
      pinMode(DIP2, INPUT);//señal de entrada s2 del dipswich
      pinMode(DIP3, INPUT);//señal de entrada s1 del dipswich
      pinMode(DIP4, INPUT);//señal de entrada s0  del dipswich
      pinMode(Pot, INPUT);//señal del potenciomentro(entrada análogica)
      
    }  
    void set_pot()
    { 
      valor=digitalRead(DIP1);//valor de s3
      valor1=digitalRead(DIP2);//valor de s2
      valor2=digitalRead(DIP3);//valor de s1
      valor3=digitalRead(DIP4);//valor de s0
      val_pot=analogRead(Pot);//valor del pontenciometro
      
      if(valor==LOW)
      {
        digitalWrite(led1, LOW);
        
      if(valor1==LOW && valor2==LOW && valor2==LOW )//si los dipswich estan en 000(0% tolerancia)
        tolerancia=0.00;
      else 
      if(valor1==LOW && valor2==LOW && valor2==HIGH )//si los dipswich estan en 001(1% tolerancia)
        tolerancia=0.01;
      else 
      if(valor1==LOW && valor2==HIGH && valor2==LOW )//si los dipswich estan en 010(2% tolerancia)
        tolerancia=0.02;
      else 
      if(valor1==LOW && valor2==HIGH && valor2==HIGH )//si los dipswich estan en 011(3% tolerancia)
        tolerancia=0.03;
      else 
      if(valor1==HIGH && valor2==LOW && valor2==LOW )//si los dipswich estan en 100(4% tolerancia)
        tolerancia=0.04;
      else 
      if(valor1==HIGH && valor2==LOW && valor2==HIGH )//si los dipswich estan en 101(5% tolerancia)
        tolerancia=0.05;
      else 
      if(valor1==HIGH && valor2==HIGH && valor2==LOW )//si los dipswich estan en 110(6% tolerancia)
        tolerancia=0.06;
      else
        tolerancia=0.07;//si los dipswich estan en 110(7% tolerancia)
     
     valor_ref=534;
     tol_pos=valor_ref+(valor_ref*tolerancia);//operación para obtener la tolerancia positiva
     tol_neg= valor_ref-(valor_ref*tolerancia);//operación para obtener la tolerancia negativa
     
        if(  val_pot >tol_pos)//D2 se activa cuando el valor ADC supera la tolerancia positiva
        digitalWrite(led4, HIGH);
        else
         {
           digitalWrite(led4, LOW);
         }
        if(  val_pot>tol_neg && val_pot<tol_pos)
          //D1 se activa cuando el valor ADC esta dentro del rango permitido por la tolerancia y el
          //valor de referencia.

         digitalWrite(led3, HIGH);
        else
        {
          digitalWrite(led3, LOW);
        } 
        if(  val_pot<tol_neg )
          digitalWrite(led2, HIGH);//D0 se activa cuando el valor ADC está por debajo de la tolerancia negativa
        else
        {
          digitalWrite(led2, LOW);
        }
    }
      
    } 
    void serial()
    {  
      Serial.println(val_pot);
    }
    
};  

Passthrough leds_ejemplo;//objeto para el primer modo
Analog_Reference ejemplo_pot;//objeto para el segundo modo


void setup()
{
  leds_ejemplo.set_led_puertos(8,9,10,11,4,5,6,7);
  leds_ejemplo.configuracion_led();
  ejemplo_pot. set_puertos(8,9,10,11,4,5,6,7,A5);
  ejemplo_pot. configuracion();
  Serial.begin(9600);
}

void loop()
{
  leds_ejemplo.set_led();  
  ejemplo_pot.set_pot();
  ejemplo_pot.serial();
  delay(300); 
  
}
