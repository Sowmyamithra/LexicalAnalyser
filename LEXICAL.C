//Lexical Analyser
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<conio.h>
int I=1;
struct SymbolTable
{
	char id[20];
	int Index;
}T[100];
int isoperator(char s)
{
	FILE *fp;
	char c;
	int flag=-1;
	int index=0;
	fp=fopen("Op.txt","r");
	while(!feof(fp))
	{
		c=fgetc(fp);
		if(c=='\n')
			index++;
		if(c==s)
		{
			flag=1;
			break;
		}
	}
	fclose(fp);
	if(flag==1)
		return((index+1));
	else
		return(-1);
}
int ispunctuation(char s)
{
	FILE *fp;
	char c;
	int index=0;
	int flag=-1;
	fp=fopen("Punct.txt","r");
	while(!feof(fp))
	{
		c=fgetc(fp);
		if(c=='\n')
			index++;
		if(c==s)
		{
			flag=1;
			break;
		}
	}
	fclose(fp);
	if(flag==1)
		return((index+1));
	else
		return(-1);
}
int iskeyword(char *s)
{
	FILE *fp=fopen("Keywords.txt","r");
	int index=0;
	int l=0,flag=-1;
	char c,temp[20];
	while(!feof(fp))
	{
		index++;
		c=fgetc(fp);
		l=0;
		strcpy(temp,"");
		while(isalpha(c) && !feof(fp))
		{
			temp[l]=c;
			l++;
			c=fgetc(fp);
		}
		temp[l]='\0';
		//printf("\n");
		//puts(temp);
		if(strcmp(temp,s)==0)
		{
			flag=1;
			break;
		}
	}
	fclose(fp);
	if(flag==1)
		return(index);
	else
		return(flag);
}
int isidentifier(char *s)
{
	int flag=-1;
	int l=0;
	if(!isdigit(s[0]))
	{
		while(l<strlen(s))
		{
			if(isalpha(s[l]) || isdigit(s[l]) || s[l]=='_')
			{
				flag=1;
			}
			else
			{
				flag=-1;
				break;
			}
			l++;
		}
		if(flag==1)
			return(1);
		else
			return(-1);
	}
	else
	{
		return(-1);
	}
}
void check(char c)
{
	printf("\n%c",c);
	if(isoperator(c)!=-1)
	{
		printf("\n<op,");
		printf("%d>",isoperator(c));
	}
	else if(ispunctuation(c)!=-1)
	{
		printf("\n<punct,");
		printf("%d>",ispunctuation(c));
	}
	else if(isdigit(c))
	{
		printf("\n<const,");
		printf("%c>",c);
	}
}
int isthere(char *s)
{
	int i=0;
	int flag=-1;
	for(i=0;i<I;i++)
	{
		if(strcmp(s,T[i].id)==0)
		{
			flag=i;
			break;
		}
	}
	if(flag==-1)
		return(-1);
	else
		return(flag);
}
void main()
{
	FILE *fp;
	int j=0,l=0;
	char c,temp[20];
	clrscr();
	printf("\n\n");
	fp=fopen("Lexical.txt","w");
	while((c=getchar())!=EOF)
		fputc(c,fp);
	fclose(fp);
	fp=fopen("Lexical.txt","r");
	while(!feof(fp))
	{
		c=fgetc(fp);
		printf("\n%c",c);
		if(isoperator(c)!=-1)
		{
			printf("\n<op,");
			printf("%d>",isoperator(c));
		}
		else if(ispunctuation(c)!=-1)
		{
			printf("\n<punct,");
			printf("%d>",ispunctuation(c));
		}
		else if(isdigit(c))
		{
			printf("\n<const,");
			printf("%c>",c);
		}
		else
		{
			l=0;
			strcpy(temp,"");
			while(isalpha(c) && !feof(fp))
			{
				temp[l]=c;
				l++;
				c=fgetc(fp);
			}
			temp[l]='\0';
			//i=ftell(fp)-1;
			//fseek(fp,i,SEEK_SET);
			if(iskeyword(temp)!=-1)
			{

				printf("\n<keyword,");
				printf("%d>",iskeyword(temp));
			}
			else if(isidentifier(temp)!=-1)
			{
				if(isthere(temp)==-1)
				{
					strcpy(T[j].id,temp);
					T[j].Index=I;
					I++;
					j++;
				}
				printf("\n<id,%d>",isthere(temp));
			}
			check(c);
		}
	}
	fclose(fp);
}