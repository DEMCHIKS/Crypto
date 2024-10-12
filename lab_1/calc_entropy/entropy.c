#include <stdio.h>
#include <math.h>
#include <wchar.h>
#include <stdbool.h>

// COUNT_LETTER = 32 
// 0 <= H <= log2(COUNT_LETTER) 
// 0 <= H <= log2(32) <= 5


#define COUNT_LETTER 32

float H1_monogram_with_SPACE(int num_of_occur[COUNT_LETTER]) {
    float accum = 0;
    int total = 0; // використовується для підрахунку загальної кількості всіх біграм

    // Calculate total occurrences
    for (int i = 0; i < COUNT_LETTER; i++) {
        total += num_of_occur[i];
    }

    // Calculate entropy
    for (int i = 0; i < COUNT_LETTER; i++) {
        if (num_of_occur[i] > 0) {
            float P = (float)num_of_occur[i] / total;
            accum += (-1/1) * (P * log2f(P));
        }
    }

    return accum;
}

// float H1_monogram_without_SPACE(){

// 	return result;
// }

float H2_bigram_with_SPACE_1(int num_of_occur[COUNT_LETTER][COUNT_LETTER]) {
    float accum = 0;
    int total = 0; // використовується для підрахунку загальної кількості всіх біграм

    for (int i = 0; i < COUNT_LETTER; i++) {
        for (int j = 0; j < COUNT_LETTER; j++) {
            total += num_of_occur[i][j];
        }
    }

    for (int i = 0; i < COUNT_LETTER; i++) {
        for (int j = 0; j < COUNT_LETTER; j++) {
            if (num_of_occur[i][j] > 0) {
                float P = (float)num_of_occur[i][j] / total;
                accum += (-1/2) * (P * log2f(P));
            }
        }
    }
    return accum;
}


// float H2_bigram_without_SPACE_1(){

// 	return result;
// }


// float H2_bigram_with_SPACE_2(){

// 	return result;
// }


// float H2_bigram_without_SPACE_2(){

// 	return result;
// }


int main() {

	int occurrences[COUNT_LETTER] = {0}; 
    float entropy = H1_monogram_with_SPACE(occurrences);
    printf("H1 monogram with SPACE: %f\n", entropy);
    return 0;
}
