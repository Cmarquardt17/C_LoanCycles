#include <stdio.h>
#include <math.h>
#include <stdlib.h>



int monthlyPayment(double principal, double interestRate, int numPayment){

  //Writing out to this file I have chosen
  FILE *out_file = fopen("LoanCycles", "w"); // write only

  //This checks if there is a file found
  if (out_file == NULL)
        {
          printf("Error! Could not open file\n");
          exit(-1); // must include stdlib.h
        }
  //the Variables we will need to calculate
  double interestCost, interestDecimal,calculation, annualPayment, currentPayment;

  //a counter to show what payment we are on
  int payCounter = 0;

  //For calculation the power gets smaller payment after payment
  int powerDecay = numPayment;

  //initializer for the loop
  int i;

  //A for loop to conduct each payment
  for(i=0; i < numPayment; i++){
    //Increment first to show we are on that payment
    payCounter++;

    //convert our percentage into a decimal
    interestDecimal = (interestRate/12)/100;

    //The actual cost of the interest on that payment
    interestCost = (principal * interestDecimal);

    //Calculation to use for dividing whats is owed on the payment
    calculation = (pow(1+interestDecimal, powerDecay)-1)/(interestDecimal*(pow(1+interestDecimal, powerDecay)));

    //Finished conducting the calcualtion so its ready for next payment
    powerDecay--;

    //Our annual payment for each monthly cycle
    annualPayment = principal/calculation;

    //This is the current payment for an exact month
    currentPayment = annualPayment-interestCost; //163.57 good

    //What is owed after paying for that month
    principal = (double) (principal-currentPayment); //836.43

    //Printing the info for each month
    fprintf(out_file,"%d                %.2lf            %.2lf            %.2lf\n", payCounter, interestCost, currentPayment, principal);
  }
  //What our final payment is
  fprintf(out_file, "Final payment     $%.02lf\n", annualPayment);

  printf("Please check LoanCycles.txt for your information!\n");
  return(0);
}

int main(void){
  //variables needed
  int numPayment, numLoans;
  double interestRate, principal;
  char decision;

  printf("Would you like to calculate your loan payments, Y or N? ");
  scanf("%c", & decision);
  if(decision == 'Y'){

        //Enter in the initial price you owe
        printf("principal ");
        scanf("%lf", & principal);

        //Enter in the annual interest rate
        printf("annual interest rate ");
        scanf("%lf", & interestRate);

        //Enter in how many payemtns in time of months
        printf("number of payments (in months) ");
        scanf("%d", & numPayment);

        monthlyPayment(principal, interestRate, numPayment);

      }
  else{
    printf("Have a good day!");
    }
}
