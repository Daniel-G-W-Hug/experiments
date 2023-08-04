// Lotto-Anwendung.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "stdlib.h"
#include "search.h"
#include "time.h"

using namespace System;

int compare( const void *arg1, const void *arg2 )
{
	// The routine must compare the elements and then return one of the following values:
	// Compare function return value
	// < 0 elem1 less than elem2
	// 0 elem1 equivalent to elem2
	// > 0 elem1 greater than elem2

	if ( (* (int *)arg1) < (* (int *)arg2) ) return -1;
	if ( (* (int *)arg1) > (* (int *)arg2) ) return  1;
	return 0;
}

void RangedRandom_int_unique(int *value, int elm_count, int range_min, int range_max)
{
	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	// rseed must be used prior to calling RangedRandom_int to create varying output
	
	// for creating a unique number, check whether result already occurred and
	// repeat until unique result

	bool *mask;
	int tmp_rand;

	// initialize mask with false
	mask = new bool[range_max-range_min];
	for (int i=0; i<range_max; i++)
		mask[i]=false;

	for (int i = 0; i < elm_count; i++ )
	{
		do
		{
			tmp_rand = (double)rand() / (RAND_MAX + 1) * (range_max - range_min)+ range_min;
		} while (mask[tmp_rand-1]);
		// i.e. continue when entry still unused

		mask[tmp_rand-1] = true; // set used flag to avoid repeated values
		value[i] = tmp_rand;
	}

	//sorting
	qsort(value, (size_t)elm_count, sizeof(int), compare);
}

int main(array<System::String ^> ^args)
{
	// Generate random numbers in the half-closed interval [range_min, range_max)
	const int range_min=1, range_max=91, no_per_drawing=6, no_of_drawings=5;
    int Lottoziehung[no_of_drawings][no_per_drawing];
	float rel_freq[range_max-range_min];

	// Seed the random-number generator with the current time so that
	// the numbers will be different every time we run.
	srand( (unsigned)time( NULL ) );
	// Console::WriteLine("Seed value: {0}", (unsigned)time( NULL ) );

	for (int i=0; i<no_of_drawings; i++)
		RangedRandom_int_unique( &Lottoziehung[i][0], no_per_drawing, range_min, range_max);

	for (int i=0; i<no_of_drawings; i++)
	{
		Console::WriteLine("Ziehung {0,2}: {1,2} {2,2} {3,2} {4,2} {5,2} {6,2}",i+1,
		Lottoziehung[i][0],
		Lottoziehung[i][1],
		Lottoziehung[i][2],
		Lottoziehung[i][3],
		Lottoziehung[i][4],
		Lottoziehung[i][5]);
	}

	// calculate rel_freqency
	/*for (int i=0; i<range_max-range_min; i++)
		rel_freq[i]=0.0;

	for (int i=0; i<no_of_drawings; i++)
		for (int j=0; j<no_per_drawing; j++)
			rel_freq[Lottoziehung[i][j]-1] += 1.0;

	for (int i=0; i<range_max-range_min; i++)
		rel_freq[i]=rel_freq[i]/(no_of_drawings*no_per_drawing);

	for (int i=0; i<range_max-range_min; i++)
		Console::WriteLine("Zahl: {0,2} Häufigkeit: {1,7:F} Abweichung zu Soll: {2,7:F} %",
		i+1, rel_freq[i],(1.0/(range_max-range_min)-rel_freq[i])/(1.0/(range_max-range_min)));*/

	Console::ReadLine();
    return 0;
}