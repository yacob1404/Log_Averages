#include <stdio.h>
#include <stdlib.h>
#include "final.h"

void printStructArr(struct data d, struct averages g){

  printf("dBug:                 %i\n", d.dBug);
  printf("Day:                  %i\n", d.day);
  printf("Month:                %i\n", d.month);
  printf("Year:                 %i\n", d.year);
  printf("Hour:                 %i\n", d.hour);
  printf("Minute:               %i\n", d.minutes);
  printf("Second:               %i\n", d.seconds);
  printf("Percent Power Draw:   %.2f\n", d.power);
  printf("GPU Temperature:      %.2f\n", d.GPUtemp);
  printf("Percent GPU Usage:    %.2f\n", d.GPUusage);
  printf("CPU Temperature:      %.2f\n", d.CPUtemp);
  printf("Percent CPU Usage:    %.2f\n", d.CPUusage);
}

void printStruct(struct averages g, char str[]){
  FILE *ofp;
  ofp = fopen(str, "w");

  fprintf(ofp, "Percent Power Draw: %2.2f%%\n", g.power);
  fprintf(ofp, "GPU Temperature:    %2.2fC\n", g.GPUtemp);
  fprintf(ofp, "GPU Percent Usage:  %2.2f%%\n", g.GPUusage);
  fprintf(ofp, "CPU Temperature:    %2.2fC\n", g.CPUtemp);
  fprintf(ofp, "CPU Percent Usage:  %2.2f%%\n", g.CPUusage);

  fclose(ofp);
}

void fillArr(struct data d[], char str[], int numEntries){
  int i;
  FILE *ifp;
  ifp = fopen(str, "r");

  for(i = 0; i < numEntries; i++){
    fscanf(ifp, "%d, %d-%d-%d %d:%d:%d, %f              ,%f              ,%f          ,%f              ,%f", &d[i].dBug, &d[i].day, &d[i].month, &d[i].year, &d[i].hour, &d[i].minutes, &d[i].seconds, &d[i].power, &d[i].GPUtemp, &d[i].GPUusage, &d[i].CPUtemp, &d[i].CPUusage);
  }
}

float getPowerAvg(struct averages g, struct data d[], int numEntries){
  int i;
  float avg = 0;
  float sum = 0;
//  numEntries = numEntries - 3;
  for(i = 0; i < numEntries; i++){
    avg = avg + d[i].power;
  }
  avg = avg / numEntries;
  return avg;
}

float getGtempAvg(struct averages g, struct data d[], int numEntries){
  int i;
  float avg = 0;
//  numEntries = numEntries - 3;
  for(i = 0; i < numEntries; i++){
    avg = avg + d[i].GPUtemp;
  }
  avg = avg/numEntries;
  return avg;
}

float getGuseageAvg(struct averages g, struct data d[], int numEntries){
  int i;
  float avg = 0;
  for(i = 0; i < numEntries; i++){
    avg = avg + d[i].GPUusage;
  }
  avg = avg/numEntries;
  return avg;
}

float getCtempAvg(struct averages g, struct data d[], int numEntries){
  int i;
  float avg = 0;
  for(i = 0; i < numEntries; i++){
    avg = avg + d[i].CPUtemp;
  }
  avg = avg/numEntries;
  return avg;
}

float getCusageAvg(struct averages g, struct data d[], int numEntries){
  int i;
  float avg = 0;
  for(i = 0; i < numEntries; i++){
    avg = avg + d[i].CPUusage;
  }
  avg = avg/numEntries;
  return avg;
}

void marker(){
  printf("Marked!!!!\n");
}

int main(int argc, char *argv[]) {
  if (argc != 3){
    printf("Syntax Error: ./a.out <infile> <outfile>\n");
    exit(1);
  }

  int i;
  int numEntries = 211;
  data d[213] = {0};
  avg g;

  fillArr(d, argv[1], numEntries);
  g.power = getPowerAvg(g, d, numEntries);
  g.GPUtemp = getGtempAvg(g, d, numEntries);
  g.GPUusage = getGuseageAvg(g, d, numEntries);
  g.CPUtemp = getCtempAvg(g, d, numEntries);
  g.CPUusage = getCusageAvg(g, d, numEntries);
  printStruct(g, argv[2]);
  //for(i = 0; i < numEntries; i++){printStructArr(d[i], g);}

  return 0;
}
