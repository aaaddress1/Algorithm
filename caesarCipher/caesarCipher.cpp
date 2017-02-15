/**
 * 	@file caesarCipher.cpp
 * 	@author Sheng-Hao Ma (aaaddress1, aka adr)
 * 	@date 02/15/2017
 **/
#include <stdio.h>
#define inRange(x, b, t) ((x >= b) && (x <= t))
int main(void) {
	if (FILE *fp = fopen("data.txt", "r")) {
		/* get text file length */
		fseek(fp, 0, SEEK_END);
		int length = ftell(fp);
		rewind(fp);

		/* copy plantext from static file to memory */
		char *plantext = new char[length + 1];
		fread(plantext, sizeof(char), length, fp);
		printf("data: %s\n", plantext);

		/* Caesar Cipher Loop */
		int offset = 2;
		for(int i = 0; plantext[i]; i++)
			if (inRange(plantext[i], 'A', 'Z') || inRange(plantext[i], 'a', 'z'))
				plantext[i] = ((plantext[i] - (((!!((plantext[i]-0x60)>>31)-1)&0x20)+'A') + offset) % 26) + (((!!((plantext[i]-0x60)>>31)-1)&0x20)+'A');
		printf("data encrypted: %s\n", plantext);

		/* output */
		if (FILE *fo = fopen("output.txt", "w")) {
			fprintf(fo, "%s", plantext);
			puts("sucessful!");
			fclose(fo);
	 	}
	 	delete []plantext;
	 	fclose(fp);
	}
	return 0;
}
