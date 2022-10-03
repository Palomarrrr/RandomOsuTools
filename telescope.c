#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

#define E 2.71828182845

typedef struct curveEnds{
	double *startingPoints, *stoppingPoints;

}curveEnds;

typedef struct time{
	int min;
	int sec;
	int milsec;
}time;

struct curveEnds calcCurveEnds(double iter, double startTop, double stopTop, double stopBottom){

	curveEnds ends;

	ends.startingPoints = malloc(sizeof(double) * 100);
	ends.stoppingPoints = malloc(sizeof(double) * 100);

	double topMultiplier = pow(E, (log(stopTop) - log(startTop)) / iter);
	double bottomMultiplier = pow(E, (log(stopBottom) - log(stopTop)) / iter);

	for(int i = 0; i <= iter; i++){
		ends.stoppingPoints[i] = (stopTop * pow(bottomMultiplier, (double)i));
		ends.startingPoints[i] = (startTop * pow(topMultiplier, (double)i));
	}

	return ends;
}

int timeToTick(time times){
	int tick;

	tick = times.milsec;
	tick += times.sec * 1000;
	tick += times.min * 60000;

	return tick;
}

void makeCurveSV(double start, double end, double startTick, double endTick, double bpm, int snap){
	double tickInc = 60000 / (double)snap / bpm;
	for(double i = startTick; i <= endTick; i += tickInc){
		printf("%0.lf,%lf,4,1,0,100,0\n", floor(i), -100 / (start * pow(pow(E, (log(end) - log(start)) / (endTick - startTick)), i-startTick)));
	}
}

int main(){

	curveEnds ends;
	time startTime;
	time endTime;
	double startTop, startBottom, endBottom, ticksPerWave, startTick, endTick, currentStartTick, bpm;
	int numWaves, snapping;
	char ans;

	printf("Starting Time\n");
	scanf("%d:%d:%d", &startTime.min, &startTime.sec, &startTime.milsec);
	startTick = timeToTick(startTime);

	printf("End Time\n");
	scanf("%d:%d:%d", &endTime.min, &endTime.sec, &endTime.milsec);
	endTick = timeToTick(endTime);

	printf("BPM\n");
	scanf("%lf", &bpm);

	printf("Snapping denominator\n");
	scanf("%d", &snapping);

	printf("Number of waves\n");
	scanf("%d", &numWaves);

	printf("Start and end sv for first curve\nwrite as x,x\n");
	scanf("%lf,%lf", &startTop, &startBottom);

	printf("End sv for the last curve\n");
	scanf("%lf", &endBottom);

	ends = calcCurveEnds(numWaves, startTop, startBottom, endBottom);

	ticksPerWave = floor((endTick-startTick) / (double)numWaves);
	currentStartTick = startTick;

	for(int i = 0; i < numWaves; i++){
		makeCurveSV(ends.startingPoints[i], ends.stoppingPoints[i], currentStartTick, currentStartTick + ticksPerWave, bpm, snapping);
		currentStartTick += ticksPerWave;
	}

	return 0;
}
