#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(){
	int startTime, endTime, precision = 10000;
	double lineChance, minBpm, maxBpm, nextBPM, lineRoll, startVol, endVol, volInc;

	printf("Start Time\n");
	scanf("%d", &startTime);

	printf("End Time\n");
	scanf("%d", &endTime);

	printf("Chance of barline\n");
	scanf("%lf", &lineChance);
	lineChance *= (double)precision;

	printf("Min BPM\n");
	scanf("%lf", &minBpm);

	printf("Max BPM\n");
	scanf("%lf", &maxBpm);

	printf("Start Volume\n");
	scanf("%lf", &startVol);

	printf("End Volume\n");
	scanf("%lf", &endVol);

	//Getting seed for random number generation
	srand((unsigned int)time(NULL));

	//Find out how much to increment the volume by
	volInc = (endVol - startVol) / (endTime - startTime);

	//Print a lot of space
	printf("\n\n\n\n\n\n\n");

	//Print an initial line
	printf("%d,%lf,99999,1,0,%0.lf,1,0\n", startTime, 60000/((maxBpm + minBpm)/2), startVol);

	//Print all the other lines
	for(int i = startTime + 1; i <= endTime; i++){


		//Roll a value to see if the line will be placed
		lineRoll = (double)(rand()%precision);

		//If the lineRoll is <= lineChance place the line
		if(lineRoll <= lineChance){
			//Lower volume
			startVol -= volInc;

			//Find the bpm of the line being placed
			nextBPM = fmod((double)rand(), maxBpm) + minBpm;

			//Convert it to osu readable
			nextBPM = 60000/nextBPM;

			//Print it
			printf("%d,%lf,99999,1,0,%0.lf,1,0\n", i, nextBPM, startVol);
		}
	}

	return 0;
}
