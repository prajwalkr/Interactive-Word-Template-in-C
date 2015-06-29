/***********************************************************************************************************************************************************
*																			   *
*	This is a project simulating Templates in Word. 												   *
*	It is acclaimed by our HOD as the project which has the most "feel-real feeling".                   						   *
*																		           *
************************************************************************************************************************************************************/

#include<stdio.h>
#include<conio.h>   
#include<stdlib.h>   
#include<string.h>  //For strlen()

FILE *ptr;    //For handling files

char file[100][200];    //A 2-d char array to simulate a file

int line=0,linepos=-1,i,j,newline=0,x,y;

char move(char ch) //Function for navigation(Arrows/Enter/Backspace)
{
   do
   {
	 if(newline==13)    //if new line is encountered
	 {
	      printf("\n");
	      file[line][++linepos]='\0';
	      line++;
	      linepos=-1;
	 }
	    else if(ch=='\b')   //if backspace is encountered
	     {
	       x=wherex();
	       y=wherey();
	       if(x!=1)
	       {
		  gotoxy(x-1,y);
		  printf(" ");
		  gotoxy(x-1,y);
		  file[line][linepos]=' ';
		  linepos--;
	       }
	     }
	 else while(kbhit())     //if arrowkey is encountered
	 {
	    x=wherex();
	    y=wherey();
	    ch=getch();
	    if(ch==72)    //if up arrow key is encountered
	    {
	       if(y!=1)
	       {
		  gotoxy(x,y-1);
		  file[line][++linepos]='\0';
		  --linepos;
		  line--;
	       }
	    }
	    else if(ch==75)   //if left arrow key is encountered
	    {
	       if(x!=1)
	       {
		  gotoxy(x-1,y);
		  linepos--;
	       }
	    }
	    else if(ch==77) //if right arrow key is encountered
	    {
	       gotoxy(x+1,y);
	       linepos++;
	    }
	    else if(ch==80)  //if down arrow key is encountered
	    {
	       gotoxy(x,y+1);
	       file[line][++linepos]='\0';
	       --linepos;
	       line++;
	    }
	 }

	 ch=getch();
	 newline=ch;
   }while(ch==0||newline==13);
 return ch;
}
int main()
{
	clrscr();
	char c,filename[100];
	int vari,varj;
	for(vari=0;vari<=99;vari++)
	{
	   for(varj=0;varj<=199;varj++)
	   {
		 file[vari][varj]=' ';
	   }
	}
	if((ptr=fopen("project.dat","w+"))==NULL) //opening file
	{
		printf("error opening file");
		getch();
		return 0;
	}
	clrscr();
	printf("[Orig Address]\n[Line 1]\n[Line 2]\n\n[Date]\n\n[Recipient Add.]\n[Line 1]\n[Line 2]\n\n[Salutation]\n[Subject]\n\n\n\n\n\n\n[Closing phrase]\n[Name of Originator]");
	gotoxy(1,1);
	fseek(ptr,0,SEEK_SET);

       while((c=getch())!=27) //if esc is pressed,we write to file;terminate
	{
	    int d=c;
	    if(c==0)  //if arrowkey is encountered
	    {
		c=move(c);
		printf("%c",c);
		file[line][++linepos]=c;
	    }
	    else if(d==13) //if newline is encountered
	    {
		printf("\n");
		file[line][++linepos]='\0';
		line++;
		linepos=-1;
	    }
	     else if(c=='\b')//if backspace is encountered
	     {
	       x=wherex();
	       y=wherey();
	       if(x!=1)
	       {
		  gotoxy(x-1,y);
		  printf(" ");
		  gotoxy(x-1,y);
		  file[line][linepos]=' ';
		  linepos--;
	       }
	     }
	    else      //if any letter is typed.
	     {
		printf("%c",c);
		file[line][++linepos]=c;
	     }

	}
	for(i=0;i<=line;i++)        //Write to file in the end.
	{
	  for(j=0;j<strlen(file[i]);j++)
	  fprintf(ptr,"%c",file[i][j]);
	  fprintf(ptr,"\n");
	}
	fclose(ptr);   //closing file
	return 0;
}