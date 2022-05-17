#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions
#include <time.h>

#include "ece198.h"

int user_input() {

    while (1)
    {
        if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8))
        {
            HAL_Delay(500);
            return 1; // RED = 1
            break;
        }
        if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))
        {
            HAL_Delay(500);
            return 2; // GREEN = 2
            break;
        }
        if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
        {
            HAL_Delay(500);
            return 3; // YELLOW = 3
            break;
        }
    }

}

bool pattern_checker( int master[5], unsigned int round ) {

    int index = 0;

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, true);

    for( int i = 0; i < round; i++ ) {
        int try = master[index];
        int test = user_input();
        if( try != test ) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false);

            HAL_Delay(100);//change the blinking into loop
            for(int i = 0; i<4; i++){
                HAL_Delay(100);
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
            }
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);//just to make sure the red light is off during the delay
            HAL_Delay(500);
            //Original code here
            /*HAL_Delay(200);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
            HAL_Delay(100);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
            HAL_Delay(100);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
            HAL_Delay(100);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
            HAL_Delay(500);
            */

            return false;
        } 
        index++;
    }

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false);

    HAL_Delay(200);
    for(int i = 0; i<4; i++){//change into blinking loop
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
        HAL_Delay(100);
    }
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
    HAL_Delay(500);//extend the delay time after the light

    //Original code here
    /*
    HAL_Delay(200);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
    HAL_Delay(200);


    */
    return true;
}

int randomNum(){
    int num = 0;
    num = rand()%3+1;
    return num;
}

void patternGenerator(int *num){
    for (int i = 0; i<5; i++){
        num[i] = randomNum();
    }
}

void rMasterUp(){
    uint32_t start = HAL_GetTick();
    while(true){
    uint32_t now = HAL_GetTick(); 
    uint32_t gap = now-start;   
        if(gap<1000){
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true);
        }else{
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);
            break;
        }}
}

void gMasterUp(){
    uint32_t start = HAL_GetTick();
    while(true){
    uint32_t now = HAL_GetTick(); 
    uint32_t gap = now-start;   
        if(gap<1000){
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
        }else{
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
            break;
        }}
}

void yMasterUp(){
    uint32_t start = HAL_GetTick();
    while(true){
    uint32_t now = HAL_GetTick(); 
    uint32_t gap = now-start;   
        if(gap<1000){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, true);
        }else{
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, false);
            break;
        }}
}

void masterLightUp(int i){
    if(i == 1){
        rMasterUp();
        HAL_Delay(100);
    }else if (i == 2)
    {
        gMasterUp();
        HAL_Delay(100);
    }else{
        yMasterUp();
        HAL_Delay(100);
    }  
}

void masterSequence(int *num, int loop){
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false);
    for (int i = 0; i<loop; i++){
        masterLightUp(num[i]);
    }   
}

void active(void){
    
        uint32_t  startedPressed = 0;
        uint32_t  afterPressed = 0;
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)){
    }
        startedPressed = HAL_GetTick();
     while (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)) {
        afterPressed = HAL_GetTick();
        uint32_t time =  afterPressed - startedPressed;
        if (time == 5000){
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true);// turn on LEDs
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, true);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, true);
            HAL_Delay(2000);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);// turn off LEDs
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, false);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false);
            HAL_Delay(200);
            
            break;
        }
        else{
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);// turn off LEDs
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, false);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false);
        }
     }
}

void endOfGame(){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true);// turn on LEDs
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, true);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, true);

    for(int i= 0; i<5; i++){ //loop blinking
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    }
    //original code here
    /*HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);// turn off LEDs
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true);// turn on LEDs
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, true);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, true);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);// turn off LEDs
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true);// turn on LEDs
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, true);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, true);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);// turn off LEDs
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false);
    */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);// make sure turn off LEDs
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, false);
    }

bool startGame() {
    
    int num[5];
    patternGenerator(num);

    for( int round = 1 ; round <= 5; round++ ){
        masterSequence(num, round);
        if( !pattern_checker(num, round) ) {
            return false;
        } 
        if(round > 5) {
            return true;
        }
    }

    return true;
    
    
}

int main(void)
{
    HAL_Init();
    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    //input 
    InitializePin(GPIOB, GPIO_PIN_8, GPIO_MODE_INPUT, GPIO_PULLUP, 10000);//red button
    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_INPUT, GPIO_PULLUP, 10000);//green button
    InitializePin(GPIOA, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP, 10000);//yellow button
    //Master Side LEDs
    InitializePin(GPIOA, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//red
    InitializePin(GPIOB, GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//green
    InitializePin(GPIOC, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//yellow
    //User side LEDs
    InitializePin(GPIOB, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//red
    InitializePin(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//green
    InitializePin(GPIOB, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);//yellow

    
    SerialSetup(9600);

    active();

    bool is_won = false;

    while( !is_won ) {
        is_won = startGame();
    }

    endOfGame();

    return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened

    srand(HAL_GetTick());
    // we can do other things in here too if we need to, but be careful
}
