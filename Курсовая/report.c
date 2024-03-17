#include "temp_function.h"

#define LINES 520000

int main(int argc, char * argv[])
{
    FILE* myfile;
    double Avr_Month_T = 0;
    int Min_Month_T = 0;
    int Max_Month_T = 0;
    int month = 0;
    int r = 0;
    int i = 0;
    int k = 1;
    struct sensor* info = malloc(LINES*sizeof(struct sensor));
    if(!info)
    {
        printf("Memory is not allocated");
        return -1;
    }
    Information();
    int rez=0;
    while ((rez = getopt(argc,argv,"hf:m:tde")) != -1)
    {
        switch (rez)
        {
            case 'h':
                printf("-h                -> Information;\n");
                printf("-f                -> CSV input file for processing;\n");
                printf("-m <number month> -> Statistics for the specified month;\n");
            break;
            case 'f':
                myfile = fopen(optarg, "r");
                if(myfile == NULL)
                {
                    printf("\nERROR");
                    return 1;
                }
                while((r = fscanf(myfile,"%d;%d;%d;%d;%d;%d",
                                    &info[i].year, 
                                    &info[i].month, 
                                    &info[i].day, 
                                    &info[i].hours, 
                                    &info[i].minutes, 
                                    &info[i].t 
                                    )) > 0)
                {
                    if(r<6)
                    {
                        char s[100];
                        r = fscanf(myfile, "%[^\n]", s);
                        i--;
                    }
                    i++;
                    k++;
                }
                Avr_Month_T = Avr_Month_Temp(info, i, month);
                Min_Month_T = Min_Month_Temp(info, i, month);
                Max_Month_T = Max_Month_Temp(info, i, month);

                if(!argv[3])
                {
                    printf("\n****************************************************************************\n");
                    printf("\n%5s%10s%15s%20s%25s\n", "Year", "Month", "Avr_Month_T", "Min_Month_T", "Max_Month_T");
                    printf("\n****************************************************************************\n");
                    for(month = 1; month <= 12; month++)
                        print_month_statistic(info,i, month, Avr_Month_T, Min_Month_T, Max_Month_T);
                    Avr_Yearh_Temp(info, i);
                    Min_Yearh_Temp(info, i);
                    Max_Yearh_Temp(info, i);
                }
                fclose(myfile);
            break;
            case 'm':
                printf("\nNumber month: %d\n",atoi(optarg));
                month = atoi(optarg);
                Avr_Month_T = Avr_Month_Temp(info, i, month);
                Min_Month_T = Min_Month_Temp(info, i, month);
                Max_Month_T = Max_Month_Temp(info, i, month);
                printf("\n****************************************************************************\n");
                printf("\n%5s%10s%15s%20s%25s\n", "Year", "Month", "Avr_Month_T", "Min_Month_T", "Max_Month_T");
                printf("\n****************************************************************************\n");                
                print_month_statistic(info, i, month, Avr_Month_T, Min_Month_T, Max_Month_T);
                break;
        }
    }
    free(info);
    return 0;
}