#include "msp.h"
#include "header.h"
#include <stdio.h>

void beepSound(void){ //Piezo Buzzer Beep Function
    int j = 0;
    TIMER_A1->CCR[0] = 4295;
    for(j = 0; j < 30000; j++){
        if((TIMER_A1->CCTL[0] & TIMER_A_CCTLN_CCIFG) != 0) {
            P3 ->OUT ^=BIT6;
            TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
        }
    }
}

void wallReached(void){
    int j = 0;
    int i = 0;
    stopFunction();
    __delay_cycles(1000000);
    for(j = 0; j < 3; j++){
        beepSound();
        __delay_cycles(500000);
    }

    servoSetup();
    __delay_cycles(500000);

    for(i = 0; i < 3; i++){
        servoClosed();
        __delay_cycles(1000000);
        servoOpen();
        __delay_cycles(1000000);
    }
    rotateFunction();
    __delay_cycles(500000);

    while((adc_raw[0] < 15000) && (adc_raw[2] < 15000) && (adc_raw[2] < 15000)){
        readADC();
    }
    stopFunction();
    ultraSetup();
}

void servoSetup(void){
    TIMER_A2->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;
    TIMER_A2->CCR[0] = 60000;
    TIMER_A2->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A2->CCR[1] = 4500;
}

void servoOpen(void){
    TIMER_A2->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;
    TIMER_A2->CCR[0] = 60000;
    TIMER_A2->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A2->CCR[1] = 3990;
}

void servoClosed(void){
    TIMER_A2->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;
    TIMER_A2->CCR[0] = 60000;
    TIMER_A2->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A2->CCR[1] = 5010;
}

void readADC(void){ //ADC Setup & Reading Function
    ADC14->CTL0 = ADC14_CTL0_SHT0_6 | ADC14_CTL0_SHP | ADC14_CTL0_ON;
    ADC14->CTL1 = ADC14_CTL1_RES_3;
    ADC14->CTL0 |= ADC14_CTL0_MSC | ADC14_CTL0_CONSEQ_1;
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_11;
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_12;
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_13 | ADC14_MCTLN_EOS;
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;
    while((ADC14->CTL0 & ADC14_CTL0_BUSY)!= 0);

    adc_raw[0] = ADC14->MEM[0]; //Should be noted that the global variable adc_raw is only used for this function
    adc_raw[1] = ADC14->MEM[1];
    adc_raw[2] = ADC14->MEM[2];
}

void stopFunction(void){ //DC Motor Stop Function
    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;
    TIMER_A0->CCR[0] = 200;
    TIMER_A0->CCR[1] = 200;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[2] = 200;
    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[3] = 200;
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[4] = 200;
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;
}

void completeShutdown(void){ //DC Motor Stop Function
    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;
    TIMER_A0->CCR[0] = 200;
    TIMER_A0->CCR[1] = 200;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[2] = 200;
    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[3] = 200;
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[4] = 200;
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;
    while(1);
}

void rotateFunction(void){
    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;
    TIMER_A0->CCR[0] = 200;
    TIMER_A0->CCR[1] = 200;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[2] = 100;
    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[3] = 100;
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[4] = 200;
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;
}

void turnLeft(void){
    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;
    TIMER_A0->CCR[0] = 200;
    TIMER_A0->CCR[1] = 150;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[2] = 200;
    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[3] = 50;
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[4] = 200;
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;

}

void turnRight(void){
    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;
    TIMER_A0->CCR[0] = 200;
    TIMER_A0->CCR[1] = 50;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[2] = 200;
    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[3] = 150;
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[4] = 200;
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;

}

void moveForward(void){
    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;
    TIMER_A0->CCR[0] = 200;
    TIMER_A0->CCR[1] = 150;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[2] = 200;
    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[3] = 150;
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[4] = 200;
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;
}
