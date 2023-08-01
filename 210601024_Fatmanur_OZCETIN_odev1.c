#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int size (FILE *pFile);

int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL, "Turkish");
	printf("CSV2JSON %s", argv[0]);
	
	int totalColumn = 0, newColumn = 0;
	int offset = 1, boolLine = 1;
	int columnCounter = 1, totalLineNumber = 1;
	char squareBrackets = '[', squareBrackets2 = ']';
	char curlyBraces = '{', curlyBraces2= '}';
	char names[255]; 
	char read;
	char comma = ',';
	char quotes = '"';
	char mark = ':';
	char line = '\n';

	FILE *csv ;
	csv = fopen(argv[1], "r");
	if(csv == NULL)
	{
		printf("File not exist !!");
		exit(1);
	}
	else
	{
		if(read = getc(csv) != line)
		{
			newColumn++;			
		}
		
		rewind(csv);
		names[255];
		fread(names, 255, 1, csv);
		
		FILE *json;
		json = fopen(argv[2], "w");
		{
			if(json == NULL)
			{
				printf("File not exist !!");
				exit(1);
			}
			
			fprintf(json, "%c", squareBrackets);
			fprintf(json,"\n");
			fprintf(json, "%c", curlyBraces);
			
			totalColumn = size(csv);
			
			fseek(csv, 255 + totalLineNumber + offset, SEEK_SET);
			
			if(strcmp(argv[3], "HEADER = OFF"))
			{
				fprintf(json, "%c", quotes);
				fprintf(json, "%c%s%d%c%c%c%c", quotes,"COLUMN", columnCounter, quotes, mark, quotes, quotes);
				columnCounter ++;
				int i;
				
				for(i=newColumn; i<sizeof(names); i++)
				{
					if(names[i] != comma)
					{
						fprintf(json, "%c", names[i]);
					}
					else
					{
						fprintf(json, "%c%c%c", quotes, mark, quotes);
						newColumn ++;
					}
				}
				
				if((newColumn + 1) == sizeof(names))
				{
					newColumn = 0;
					fprintf(json, "%c%c%c", quotes, mark, quotes);
					exit(1);
				}
			}
				
			else
			{
				fprintf(json, "%c%s%c%c%c%s%c", quotes, names, quotes, mark, quotes, names, quotes);
				columnCounter++;
				
				fseek(csv, 255 + totalLineNumber + offset, SEEK_SET);
				
				if(columnCounter == (totalColumn))
				{
					columnCounter = 1;
				}
				
				else
				{
					printf("Something wrong");
					exit(1);
				}
			}
			
			if(read = getc(csv) != comma)
			{
				if(read == EOF)
				{
					fprintf(json, "%c\n%c\n%c", quotes, curlyBraces2, squareBrackets2);
					return 0;
				}
				if(read == boolLine)
				{
					totalLineNumber ++;
					exit(1);
				}
				fprintf(json, "%c", read);
				offset;				
			}
			
			if(boolLine == 0)
			{
				fprintf(json, "%c%c", quotes, comma);
			}
			
			if(boolLine == 1)
			{
				fprintf(json, "%c\n%c%c\n%c", quotes, curlyBraces2, comma, curlyBraces);
			}
			offset ++;
		}
	}

}

	int size(FILE *file) 
	{
	rewind(file);
	char word;
	int counter = 1;
		
	while((word = getc(file)) != EOF)
	{
		
		if(word == ',') 
		{
			counter++;
		} else if(word == '\n') 
		{
			break;
		}
	}
	return counter ++;
	}

