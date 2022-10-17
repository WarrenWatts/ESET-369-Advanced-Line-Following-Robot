#include "msp.h"
#include "header.h"
#include <stdio.h>

volatile unsigned int tcap = 0, tcap_flag = 0, tcap_cov = 0;
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	int j = 0;
	int i = 0;

	P3->DIR |= BIT6;

	P3->DIR |= BIT5;
	P5->DIR &= ~BIT7;
	P5->SEL0 |= BIT7;
	P5->SEL1 &= ~BIT7;

	P5->DIR |= BIT6;
	P5->SEL1 &= ~BIT6;
	P5->SEL0 |= BIT6;

	P6->DIR &= ~(BIT0 | BIT1);

	P2->DIR |= 0xF0;
    P2->SEL1 &= ~0xF0;
    P2->SEL0 |= 0xF0;

    P4->SEL1 |= 0x07;
    P4->SEL0 |= 0x07;

    P5->DIR |= BIT0;
    P5->OUT |= BIT0;

	TIMER_A1->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;

	while((P6->IN & BIT0)!=0);

	for(j = 0; j < 3; j++){
	        beepSound();
	        __delay_cycles(500000);
	    }
	for(i = 0; i < 3; i++){
	    servoOpen();
	    __delay_cycles(1000000);
	    servoClosed();
	    __delay_cycles(1000000);
	}


	ultraSetup();

    while(1){
        ultraSensor();
        if((P6->IN & BIT1)==0){
            completeShutdown();
        }
        readADC();
        if(adc_raw[0] <= 12000){ //right sensor
            turnLeft();
        }else if(adc_raw[2] <= 12000){//left sensor
            turnRight();
        }else{
            moveForward();
        }
    }
}


void TA2_N_IRQHandler(void){
    if((TIMER_A2->CTL & TIMER_A_CTL_IFG)!=0){
        tcap_cov=1;
        tcap_flag=1;
        TIMER_A2->CTL &= ~TIMER_A_CTL_IFG;
    }
    if((TIMER_A2->CCTL[2] & TIMER_A_CCTLN_CCIFG)!=0){
        tcap=TIMER_A2->CCR[2];
        tcap_flag=1;
        TIMER_A2->CCTL[2] &= ~TIMER_A_CCTLN_CCIFG;
    }
}

void ultraSetup(void){
    TIMER_A2->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_2 | TIMER_A_CTL_CLR;

    TIMER_A2->CCTL[2] = TIMER_A_CCTLN_CM_2 | TIMER_A_CCTLN_CCIS_0 | TIMER_A_CCTLN_CCIE | TIMER_A_CCTLN_CAP | TIMER_A_CCTLN_SCS;

    TIMER_A2->CTL |= TIMER_A_CTL_IE;

    NVIC->ISER[0] = 1 << ((TA2_N_IRQn) & 31);

    __enable_irq();
}

void ultraSensor(void){
    tcap_flag=0;
    tcap_cov=0;

    TIMER_A2->CTL |= TIMER_A_CTL_CLR;

    P3->OUT |= BIT5;
    //__delay_cycles(30);
    P3->OUT &= ~BIT5;
    //__delay_cycles(100);

    while(tcap_flag==0);

    if((tcap_cov == 0) && (tcap < 2850) && (tcap_flag == 1)){
        wallReached();
    }
}
