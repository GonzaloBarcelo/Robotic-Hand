#include <xc.h>
#include <stdint.h>
#include "Pic32Ini.h"
#include "UART1.h"
#include <math.h>
#define PIN_PULSADOR 5
#define INC_10_GRADOS 4000

int POSICION_1= 2500;
int POSICION_2 = 3750;
int POSICION_3 = 5000;
int POSICION_4 = 6250;
int POSICION_5 = 7500;
int t_alto = 2500;

uint16_t pulgar,indice,corazon,anular,pinky;


// cada 139 cuentas se giran 10Âº

void iniciaAD(void){
// Pines de los LEDs como digitales
	ANSELC &= ~0xFF;
    ANSELB |=0xF;
    ANSELA |= 0x3;
    
	LATA = 0; // En el arranque dejamos todas las salidas a 0
	LATB = 0;
	LATC = 0xF; // Apago los LEDs de la placa

	// Pines como salidas
	TRISA = 1<<1|1;
	TRISB = (1 << PIN_PULSADOR)|(1<<3)|(1<<2)|(1<<1)|1;
	TRISC = 0;



	AD1CON1 = 0; // Apago el ADC por si acaso
	AD1CON2 = 5<<2 | 1<<10; // SMPI = 5, CSCNA = 1
	AD1CON3 = 0x0200; // SAMC = 2 (Tsamp = 2 Tadc)
	// Tadc = 2 * TPBCLK (a tope)
	AD1CHS = 0x00000000; // CH0SA No usado, CH0NA = GND
	AD1CSSL = 0x3F; // Se muestrean AN5 a AN0
	AD1CON1bits.SSRC = 2; // Conv. Disparadas por T3
	AD1CON1bits.ASAM = 1; // Autosampling
	IFS0bits.AD1IF = 0; // Borro el flag de interrupción
	IEC0bits.AD1IE = 1; // Habilito la interrupción
	IPC5bits.AD1IP = 2; // Prioridad 2
	IPC5bits.AD1IS = 0; // Subprioridad 0
	AD1CON1bits.ON = 1; // Arranco el ADC

	T3CON = 0;
	TMR3 = 0;
	PR3 = 5000; // Periodo de 1 ms
	T3CON = 0x8000; // T3 ON, Div = 1
	INTCONbits.MVEC = 1; // Modo multivector
	
}

//int leerServo(int dedo){}

int posicionCOR(uint16_t value){
	//Los valores van a oscilar entre 0 y 1023
	// Por lo tanto, si queremos tener 5 posiciones, cada estará en el rango de 1023/5=205
    asm(" di");
    
    
 int valor_leds = (value>>6);
 LATCCLR = ( valor_leds) & 0x0F;
 LATCSET = (~valor_leds) & 0x0F;
 
    if (value<750){
		return 1;
	}
    else if(750<value && value<830)
	{
		return 3;
	}
    else if (830>value && value<1000)
	{
		return 4;
	}
	else
	{
		return 4;
	}
     
	asm(" ei");


	//Si se detecta otro valor, se devuelve la posicion original
	
}
int posicionIND(uint16_t value){
	//Los valores van a oscilar entre 0 y 1023
	// Por lo tanto, si queremos tener 5 posiciones, cada estará en el rango de 1023/5=205
    asm(" di");
    
    
 int valor_leds = (value>>6);
 LATCCLR = ( valor_leds) & 0x0F;
 LATCSET = (~valor_leds) & 0x0F;
 
    if (value<400){
		return 1;
	}
    else if(400<value && value<440)
	{
		return 2;
	}
    else if (440>value && value<1000)
	{
		return 4;
	}
	else
	{
		return 4;
	}
     
	asm(" ei");


	//Si se detecta otro valor, se devuelve la posicion original
	
}
int posicionMEN(uint16_t value){
	//Los valores van a oscilar entre 0 y 1023
	// Por lo tanto, si queremos tener 5 posiciones, cada estará en el rango de 1023/5=205
    asm(" di");
    
    
 int valor_leds = (value>>6);
 LATCCLR = ( valor_leds) & 0x0F;
 LATCSET = (~valor_leds) & 0x0F;
 
    if (value<350){
		return 1;
	}
    else if(350<value && value<550)
	{
		return 2;
	}
    else if (550>value && value<1000)
	{
		return 4;
	}
	else
	{
		return 4;
	}
     
	asm(" ei");


	//Si se detecta otro valor, se devuelve la posicion original
	
}
int posicionANU(uint16_t value){
	//Los valores van a oscilar entre 0 y 1023
	// Por lo tanto, si queremos tener 5 posiciones, cada estará en el rango de 1023/5=205
    asm(" di");
    
    
 int valor_leds = (value>>6);
 LATCCLR = ( valor_leds) & 0x0F;
 LATCSET = (~valor_leds) & 0x0F;
 
    if (value<380){
		return 1;
	}
    else if(380<value && value<420)
	{
		return 2;
	}
    else if (420>value && value<1000)
	{
		return 4;
	}
	else
	{
		return 4;
	}
     
	asm(" ei");


	//Si se detecta otro valor, se devuelve la posicion original
	
}
int posicionPUL(uint16_t value){
	//Los valores van a oscilar entre 0 y 1023
	// Por lo tanto, si queremos tener 5 posiciones, cada estará en el rango de 1023/5=205
    asm(" di");
    
    
 int valor_leds = (value>>6);
 LATCCLR = ( valor_leds) & 0x0F;
 LATCSET = (~valor_leds) & 0x0F;
 
    if (value<380){
		return 1;
	}
    else if(380<value && value<420)
	{
		return 2;
	}
    else if (420>value && value<1000)
	{
		return 4;
	}
	else
	{
		return 4;
	}
     
	asm(" ei");


	//Si se detecta otro valor, se devuelve la posicion original
	
}
__attribute__((vector(23), interrupt(IPL2SOFT), nomips16))
 void InterrupcionADC(void)
 {
 
 IFS0bits.AD1IF = 0; // Se borra el flag
 asm("di");
 pulgar=ADC1BUF0; //Valor digital del analógico Analogico 0
 indice=ADC1BUF1;
 corazon=ADC1BUF2;
 anular=ADC1BUF3;
 pinky=ADC1BUF4;
 
 asm("ei");

 }
void servos(int n_servo, int estado){
    
      switch (estado){
         case 1:
             t_alto = POSICION_1;
             break;
         case 2:
             t_alto = POSICION_2;
             break;
         case 3:
             t_alto = POSICION_3;
             break;
         case 4:
             t_alto = POSICION_4;
             break;
         case 5:
             t_alto = POSICION_5;
             break;
         default:
             t_alto = 2500;  
             break;
         
     }
            switch (n_servo){
         case 1:
             OC1RS = t_alto;
             break;
         case 2:
             OC2RS = t_alto;
             break;
         case 3:
             OC3RS = t_alto;
             break;
         case 4:
             OC4RS = t_alto;
             break;
         case 5:
             OC5RS = t_alto;
             break;
         default:
             OC1RS = t_alto;  
             break;
     }
            
         
     
 }


void main(void)
{
 int t_alto = 2500; // Tiempo en alto de la salida (1 ms)
 iniciaAD();

 SYSKEY=0xAA996655;
 SYSKEY=0x556699AA;
 RPB15R = 5; // OC1 conectado a RB15
 RPB8R=5; //OC2 conectado a RB8
 
 RPB14R=5; //OC3 conectado a RB9
 
 RPB13R = 5;//OC4 conectado al RB13
 
 RPC6R=6; //OC5 conectado al RC6
 
 SYSKEY=0x1CA11CA1;

 OC1CON = 0;
 OC1R = 2500; // Tiempo en alto de 1 ms inicial
 OC1RS = 2500;
 OC1CON = 0x8006; // OC ON, modo PWM sin faltas
 
 OC2CON = 0;
 OC2R = 2500; // Tiempo en alto de 1 ms inicial
 OC2RS = 2500;
 OC2CON = 0x8006; // OC ON, modo PWM sin faltas
 
 OC3CON = 0;
 OC3R = 2500; // Tiempo en alto de 1 ms inicial
 OC3RS = 2500;
 OC3CON = 0x8006; // OC ON, modo PWM sin faltas
 
 OC4CON = 0;
 OC4R = 2500; // Tiempo en alto de 1 ms inicial
 OC4RS = 2500;
 OC4CON = 0x8006; // OC ON, modo PWM sin faltas
 
 OC5CON = 0;
 OC5R = 2500; // Tiempo en alto de 1 ms inicial
 OC5RS = 2500;
 OC5CON = 0x8006; // OC ON, modo PWM sin faltas
 

 T2CON = 0;
 TMR2 = 0;
 PR2 = 49999; // Periodo de 20 ms
 T2CON = 0x8010; // T3 ON, Div = 2
 
   INTCONbits.MVEC=1; 
	asm(" ei");

 while(1){
     
     servos(1,posicionIND(ADC1BUF4)); //RB15 INDICE
     servos(2,posicionCOR(ADC1BUF1)); // RB8 CORAZON
     servos(3,posicionANU(ADC1BUF0)); //RB14 ANULAR
     //servos(4,posicionMEN(ADC1BUF5)); //RB13 MEnIQUE
     //servos(5,posicionPUL(ADC1BUF3)); //RC6 PULGAR
     
/*
      servos(1,1); //RB15 INDICE
     servos(2,1); //RB8 CORAZON
     servos(3,1); //RB14 ANULAR
     servos(4,1); //RB13 MEnIQUE
     servos(5,1); //RC6 PULGAR
 
 */    
     

     

   
     
 }
}
