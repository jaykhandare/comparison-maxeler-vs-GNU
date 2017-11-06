#include <time.h>
#include <sys/time.h>   // Lovely: got both time.h and times.h in sys
#include <sys/times.h>  // For both times() and struct tms definitions
#include <unistd.h>     // Defines _SC_CLK_TCK
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*  Maxeler libraries

#include <MaxSLiCInterface.h>
#include "Maxfiles.h"

*/
/*
 * This function is used to get CLOCK_REALTIME to make benchmarks.
 *
*/
double elapsedTime(void){
    struct timespec {
        time_t   tv_sec;        /* seconds */
        long     tv_nsec;       /* nanoseconds */
    }time;
    clockid_t clk_id = CLOCK_REALTIME;

    int flag;
    double timing;

    flag = clock_gettime(clk_id, &time);
    if (flag == 0)
        timing = (double)time.tv_sec + ((double)1.0e-9)*(double)time.tv_nsec;
    else
        timing = -31.0;  // If timer failed, return non-valid time

    return (timing);
}

/*
 *  These functions will perform norm1, norm2 and normInf with basic GNU compilers.
*/
double GNUNorm1(int size, double *x){

    int i;
    double sum = 0.0;

    for(i = 0; i < size; i++) {
        sum = sum + fabs(x[i]);
    }

    return sum;
}

double GNUNorm2(int size, double *x){

    int i;
    double nrm2 = 0.0;

    for(i = 0; i < size; i++) {
        nrm2 = nrm2 + x[i] * x[i];
    }
//    nrm2 = sqrt(nrm2);

    return nrm2;
}

double GNUNormInf(int size, double *x){

    int i;
    double max = 0.0;

    for(i = 0; i < size; i++){
        fabs(x[i])>max?max=fabs(x[i]):max;
    }

    return max;
}

/*
 *  These functions will perform norm1, norm2 and normInf with Maxeler systems.
*/

double MaxelerNorm1(int size, double *x){
//    norm1(size,inArray,outArray);
//    return scalarValue;
    return 1;
}

double MaxelerNorm2(int size, double *x){
//    norm2(size,inArray,outArray);
//    return scalarValue;
    return 1;
}

double MaxelerNormInf(int size, double *x){
//    normInf(size,inArray,outArray);
//    return scalarValue;
    return 1;
}

/*
int main(){
    double timeStart,timeEnd,timeElapsed;
    int i;
    timeStart = elapsedTime();
    for(i = 0; i < 100; i++) {
        printf("");
    }
    timeEnd = elapsedTime();
    timeElapsed = timeEnd - timeStart;
    printf("Time start = %lf\n", timeStart);
    printf("Time end   = %lf\n", timeEnd);
    printf("Time taken for 100 repetitions = %lf\n", timeElapsed);

}
*/


int main() {

    printf("GNU vs Maxeler\n");
    double timeStart,timeEnd,timeElapsed;
    FILE *results;

    int i,j;
    int GNUFlag1 = 1,GNUFlag2 = 2,GNUFlagInf = 3,MaxFlag1 = 4,MaxFlag2 = 5,MaxFlagInf = 6;

//  vector
    double *x;
//  results
    double GNUNorm1Results,GNUNorm2Results,GNUNormInfResults;
    double MaxelerNorm1Results,MaxelerNorm2Results,MaxelerNormInfResults;

    int initialSizeofVector = 100000;
    int stride = 50000;
    int finalSizeofVector = 1000000;

    results = fopen("../results","w");

    for(int sizeofVector = initialSizeofVector;sizeofVector <= finalSizeofVector;sizeofVector += stride) {
//          allocating memory to vector x
        x = calloc(sizeofVector, sizeof(double));
        if (x == NULL) {
            printf("Memory allocation failed for array size = %d\n", i);
            printf("*******\nExiting...\n*******");
            exit(13);
        }
//          populating the vector
        for(j = 0; j < sizeofVector; j++) {
            x[j] = (double)rand();
        }


        timeStart = elapsedTime();
        for(i = 0; i < 100; i++) {
            GNUNorm1Results = GNUNorm1(sizeofVector, x);
        }
        timeEnd = elapsedTime();
        timeElapsed = timeEnd - timeStart;
//        printf("Time start = %lf\n", timeStart);
//        printf("Time end   = %lf\n", timeEnd);
        printf("GNU Norm1: Time taken for 100 repetitions = %lf\n", timeElapsed);
        printf("#flops = %d\n",sizeofVector);
        fprintf(results,"%d %.17e %d %d \n",sizeofVector,timeElapsed,100,GNUFlag1);


        timeStart = elapsedTime();
        for(i = 0; i < 100; i++) {
            GNUNorm2Results = GNUNorm2(sizeofVector, x);
        }
        timeEnd = elapsedTime();
        timeElapsed = timeEnd - timeStart;
//        printf("Time start = %lf\n", timeStart);
//        printf("Time end   = %lf\n", timeEnd);
        printf("GNU Norm2: Time taken for 100 repetitions  = %lf\n", timeElapsed);
        printf("#flops = %d\n",2*sizeofVector);
        fprintf(results,"%d %.17e %d %d \n",sizeofVector,timeElapsed,100,GNUFlag2);


        timeStart = elapsedTime();
        for(i = 0; i < 100; i++) {
            GNUNormInfResults = GNUNormInf(sizeofVector,x);
        }
        timeEnd = elapsedTime();
        timeElapsed = timeEnd - timeStart;
//        printf("Time start = %lf\n", timeStart);
//        printf("Time end   = %lf\n", timeEnd);
        printf("GNU NormInf: Time taken for 100 repetitions  = %lf\n", timeElapsed);
        printf("#flops = %d\n",sizeofVector);
        fprintf(results,"%d %.17e %d %d \n",sizeofVector,timeElapsed,100,GNUFlagInf);

/*
        timeStart = elapsedTime();
        MaxelerNorm1Results = MaxelerNorm1(sizeofVector,x);
        timeEnd = elapsedTime();
        timeElapsed = timeEnd - timeStart;
//        printf("Time start = %lf\n", timeStart);
//        printf("Time end   = %lf\n", timeEnd);
        printf("Maxeler Norm1: Time taken for 100 repetitions  = %lf\n", timeElapsed);
        fprintf(results,"%d %.17e %d %d \n",sizeofVector,timeElapsed,100,MaxFlag1);


        timeStart = elapsedTime();
        MaxelerNorm2Results = MaxelerNorm2(sizeofVector,x);
        timeEnd = elapsedTime();
        timeElapsed = timeEnd - timeStart;
//        printf("Time start = %lf\n", timeStart);
//        printf("Time end   = %lf\n", timeEnd);
        printf("Maxeler Norm2: Time taken for 100 repetitions  = %lf\n", timeElapsed);
        fprintf(results,"%d %.17e %d %d \n",sizeofVector,timeElapsed,100,MaxFlag2);


        timeStart = elapsedTime();
        MaxelerNormInfResults = MaxelerNormInf(sizeofVector,x);
        timeEnd = elapsedTime();
        timeElapsed = timeEnd - timeStart;
//        printf("Time start = %lf\n", timeStart);
//        printf("Time end   = %lf\n", timeEnd);
        printf("Maxeler NormInf: Time taken for 100 repetitions  = %lf\n", timeElapsed);
        fprintf(results,"%d %.17e %d %d \n",sizeofVector,timeElapsed,100,MaxFlagInf);



        if(GNUNorm1Results == MaxelerNorm1Results){
            printf("Results for norm1 match for vector size = %d.\n",sizeofVector);
        }
        else{
            printf("Results for norm1 match for vector size = %d.\n",sizeofVector);
        }

        if(GNUNorm2Results == MaxelerNorm2Results){
            printf("Results for norm2 match for vector size = %d.\n",sizeofVector);
        }
        else{
            printf("Results for norm2 match for vector size = %d.\n",sizeofVector);
        }

        if(GNUNormInfResults == MaxelerNormInfResults){
            printf("Results for normInf match for vector size = %d.\n",sizeofVector);
        }
        else{
            printf("Results for normInf match for vector size = %d.\n",sizeofVector);
        }

*/
        free(x);
    }
    printf("Results stored in \"results\"\n");
    fclose(results);

    return 0;
}