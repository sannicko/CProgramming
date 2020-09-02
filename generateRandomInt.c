#include <stdio.h>

int main(void) {
   const double PI_VAL = 3.14159265;

   double circleRadius;
   double circleCircumference;
   double circleArea;
   
   printf("Enter circumference: ");
   scanf("%lf", &circleCircumference);
   
circleCircumference = PI_VAL;          // FIXME delete
   circleRadius = circleCircumference / 2 * PI_VAL;
printf("Radius: %lf\n", circleRadius); // FIXME delete
   
   /*
    circleArea = PI_VAL * circleRadius * circleRadius;
    
    printf("Circle area is: %lf\n", circleArea);
    */
   
   return 0;
}