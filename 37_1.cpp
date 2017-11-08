#include <iostream>
#include <cstdlib>
#include <utility>
#include <time.h>
#include <cstring>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <stdarg.h>



int main()
{
	setlocale(LC_ALL, "Russian");

	FILE* file1 = fopen("file1.txt", "r");
	FILE* file2 = fopen("file2.txt", "r");

	fseek(file1, 0, SEEK_END);
	int size1 = ftell(file1);
	fseek(file1, 0, SEEK_SET);
	char* f1 = (char*)malloc(size1 * 2 * sizeof(char));
	fread(f1, size1, 1, file1);

	f1[size1] = '\0';
	std::cout << f1;
	fseek(file2, 0, SEEK_END);
	int size2 = ftell(file2);
	fseek(file2, 0, SEEK_SET);
	char* f2 = (char*)malloc(size2 * sizeof(char));
	//fread(f1, size2, 1, file2);

	int w_count = 0;
	char w_m[100][1000] = { NULL };



	while (fgets(f2, 100, file2))
	{
		strcpy(w_m[w_count], f2);
		w_count++;
	}

	fclose(file1);
	fclose(file2);

	int i = 0, i2 = 0, ff1 = 0, c1 = 0, ttt = 0;



	for (int q = 0; q < w_count; q++)
	{
		char temp[10000], ch[11] = { "[Censored]" }, find[100];

		for (int g = 0; g < strlen(w_m[q]); g++)
		{
			find[g] = w_m[q][g];
		}
		find[strlen(w_m[q])-1] = '\0';
		while (f1[i] != '\0')
		{
			if (f1[i] == find[ff1])
			{
				ff1++;
			}
			else if (ff1 == strlen(find) && f1[i] == ' ' && f1[i - strlen(find) - 1] == ' ' || ff1 == strlen(find) && f1[i] == ' ' && f1[i - strlen(find) - 1] == '\n' || ff1 == strlen(find) && f1[i] == '\n' && f1[i - strlen(find) - 1] == ' ' || ff1 == strlen(find) && f1[i] == ' ' && i - strlen(find) == 0)
			{
				ff1 = 0;
				i2 -= strlen(find);
				while (ff1 < strlen(ch))
				{
					temp[i2] = ch[ff1];
					ff1++;
					i2++;
				}
			}
			else
			{
				ff1 = 0;
			}

			temp[i2] = f1[i];
			i++;
			i2++;
		}
		temp[i2] = '\0';
		strcpy(f1, temp);
		ttt = i2;
		i = 0;
		i2 = 0;
	}

	FILE* file3 = fopen("file1.txt", "w");
	fwrite(f1, strlen(f1), 1, file3);
	fclose(file3);

	system("pause");
	return 0;
}