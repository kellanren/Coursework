#include <stdio.h>
#include <math.h>

int main(){
	double SCALE = 1.5;
	double max_y = -100000, min_y = 100000, max_x = 0, min_x = 0;
	
	printf("PLot for y = 10.0 * (1.0 + sin(x)) for x from 0.0 to 10.\n");
	printf("  X      Y       Graph\n");

	for(double i = 0; i <= 21; i += 0.1){
		double y = 10.0 * (1.0 + sin(i));
		
		if(y > max_y){
			max_y = y;
			max_x = i;
		}

		if(y < min_y){
			min_y = y;
			min_x = i;
		}

		int bar_length = (int)(y * SCALE);
		printf("%5.2f%6.2f", i, y);

		for(int num_y = 0; num_y < bar_length; num_y++){
			printf("#");
		}
		printf("\n");
	}
	printf("Maximum Value: Y = %.2f at X = %.2f\n", max_y, max_x);			printf("Minimum Value: Y = %.2f at Y = %.2f\n", min_y, min_x);	
	return 0;
}
