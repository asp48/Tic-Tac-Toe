#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>



//mouse functions
int initmouse();
void showmouseptr();
void hidemouseptr();
void getmousepos(int*,int*,int*);
void restrictmouseptr(int, int, int, int);
union REGS i, o;



//userdefined
void start();
void menu();
void animate();
int newgame();
void drawbase();
void chkquad(int *,int *,int *,int *);
void quadcent(int,int,int*,int *);
void point(int,int,int,int);
int chkwin(int);
void initlz();
void options(int,int);
void save(int,int);
void resume(int);
void load();
void search();
void scoreup(int );
void hs();
void loading();


//global
int record[3][3],left,top,bottom,right;
float sc1=-1.000000,sc2=-1.000000;
char p1[10],p2[10];
typedef struct node
{
    char name[10];
    float score;
    struct node *ptr;
} player;


player *LLI(player *,char [],float);
player *sort(player *,int);
void display(player *);





void main()
{
    int gd=DETECT,gm,ch,win,a;
    char array[10];
    clrscr();
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    left = (getmaxx() / 2 )- 120;
    top = (getmaxy() / 2) - 70;
    right = (getmaxx() / 2) + 100;
    bottom = (getmaxy() / 2) + 100;
    start();
    cleardevice();
    setbkcolor(BLUE);
    printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\tPlayer1 Name: ");
    scanf("%s",p1);
    printf("\n\n\t\t\tPlayer2 Name: ");
    scanf("%s",p2);
    do
    {
        menu();
        ch=getch();
        switch(ch-'0')
        {
        case 1:
            loading();
            search();
            animate();
            setbkcolor(WHITE);
            drawbase();
            win=newgame();
            getch();
            loading();
            scoreup(win);
            cleardevice();
            if(win!=0)
            {
                setcolor(BLUE);
                settextstyle(0,0,4);
                moveto(75,130);
                outtext("NAME");
                moveto(375,130);
                outtext("SCORE");
                setcolor(RED);
                settextstyle(0,0,3);
                moveto(75,200);
                outtext(p1);
                moveto(430,200);
                a=sc1;
                sprintf(array,"%d",a);
                outtext(array);
                setcolor(GREEN);
                moveto(75,350);
                outtext(p2);
                moveto(430,350);
                a=sc2;
                sprintf(array,"%d",a);
                outtext(array);
                getch();
            }
            break;
        case 2:
            loading();
            load();
            getch();
            break;
        case 3:
            cleardevice();
            loading();
            hs();
            break;
        case 4:
            cleardevice();
            exit();
        default:
            cleardevice();
            exit();
        }
    } while(1);
}
void start()
{   int i;
    setbkcolor(WHITE);
    setcolor(GREEN);
    settextstyle(0,0,6);
    moveto(0,220);
    outtext("TICK TACK TOE");
    delay(2000);
}
void menu()
{
    setbkcolor(WHITE);
    fflush(stdin);
    fflush(stdout);
    cleardevice();
    setcolor(BLUE);
    settextstyle(0,0,4);
    moveto((getmaxx()/2)-100,50);
    outtext("Main Menu");
    setcolor(RED);
    settextstyle(0,0,2);
    moveto(100,200);
    outtext("1.New Game");
    moveto(100,250);
    outtext("2.Load Game");
    moveto(100,300);
    outtext("3.High Score");
    moveto(100,350);
    outtext("4.Exit");
    moveto(100,400);
    outtext("Enter Your Choice:");
    return;
}

void animate()
{
    int i;
    setbkcolor(BLUE);
    for(i=0; i<(getmaxx()/2); i+=10)
    {
        cleardevice();
        setcolor(WHITE);
        circle((getmaxx()/2),(getmaxy()/2),(i/4));
        setfillstyle(1,WHITE);
        floodfill((getmaxx()/2),(getmaxy()/2),WHITE);
        circle(i,250,50);
        setfillstyle(1,RED);
        floodfill(i,250,WHITE);
        circle(getmaxx()-i,250,50);
        setfillstyle(1,GREEN);
        floodfill(getmaxx()-i,250,WHITE);
        delay(100);
    }
    setcolor(6);
    settextstyle(0,0,10);
    moveto(130,150);
    outtext("START");
    getch();
    return;
}

void chkquad(int *x,int *y,int *l,int *m)
{
    if((*y>79)&&(*y<180))
    {
        if((*x>109)&&(*x<215))
        {
            *l=0;
            *m=0;
            *x=162;
            *y=130;
        }
        else if((*x>215)&&(*x<400)) {
            *l=0;
            *m=1;
            *x=308;
            *y=130;
        }
        else {
            *l=0;
            *m=2;
            *x=455;
            *y=130;
        }
    }
    else if((*y>180)&&(*y<325))
    {
        if((*x>109)&&(*x<215)) {
            *l=1;
            *m=0;
            *x=162;
            *y=248;
        }
        else if((*x>215)&&(*x<400)) {
            *l=1;
            *m=1;
            *x=308;
            *y=248;
        }
        else {
            *l=1;
            *m=2;
            *x=455;
            *y=248;
        }
    }
    else
    {
        if((*x>109)&&(*x<215)) {
            *l=2;
            *m=0;
            *x=162;
            *y=372;
        }
        else if((*x>215)&&(*x<400)) {
            *l=2;
            *m=1;
            *x=308;
            *y=372;
        }
        else {
            *l=2;
            *m=2;
            *x=455;
            *y=372;
        }
    }
    return;
}


void quadcent(int l,int m,int *x,int *y)
{
    if((l==0)&&(m==0))
    {
        *x=162;
        *y=130;
    }
    else if((l==0)&&(m==1))
    {
        *x=308;
        *y=130;
    }
    else if((l==0)&&(m==2))
    {
        *x=455;
        *y=130;
    }
    else if((l==1)&&(m==0))
    {
        *x=162;
        *y=248;
    }
    else if((l==1)&&(m==1))
    {
        *x=308;
        *y=248;
    }
    else if((l==1)&&(m==2))
    {
        *x=455;
        *y=248;
    }
    else if((l==2)&&(m==0))
    {
        *x=162;
        *y=372;
    }
    else if((l==2)&&(m==1))
    {
        *x=308;
        *y=372;
    }
    else
    {
        *x=455;
        *y=372;
    }
    return;
}


void point(int x,int y,int flag,int p)
{
    if(flag==1)          //turn of player1
    {
        hidemouseptr();
        setcolor(RED);
        circle(x,y,25);
        setfillstyle(1,RED);
        floodfill(x,y,RED);
    }
    else if(flag==2)
    {   //turn of player 2
        hidemouseptr();
        setcolor(GREEN);
        circle(x,y,25);
        setfillstyle(1,GREEN);
        floodfill(x,y,GREEN);
    }
    if(p==1)
    {
        setcolor(15);
        circle(525,30,20);
        setfillstyle(1,BLUE);
        floodfill(525,30,15);
        circle(225,30,20);
        setfillstyle(1,0);
        floodfill(225,30,15);
        setcolor(RED);
    }
    else if(p==2)
    {
        setcolor(15);
        circle(225,30,20);
        setfillstyle(1,BLUE);
        floodfill(225,30,15);
        circle(525,30,20);
        setfillstyle(1,0);
        floodfill(525,30,15);
        setcolor(GREEN);
    }
    showmouseptr();
    return;
}
void drawbase()
{
    cleardevice();
    setbkcolor(0);
    setcolor(5);
    setlinestyle(0,0,6);
    line(215,top-90,215,bottom+90);
    line(400,top-90,400,bottom+90);
    line(left-90,180,right+90,180);
    line(left-90,325,right+90,325);
    restrictmouseptr(left-85,top-85,right+85,bottom+85);
    setcolor(BROWN);
    settextstyle(0,0,2);
    moveto(50,25);
    outtext(p1);
    moveto(350,25);
    outtext(p2);
    return;
}
void initlz()
{   int i,j;
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            record[i][j]=0;
}

int chkwin(int count)
{   int k,n,a[3],b[3],win;
    char array[10];
    win=0;
    if(count>=5)
    {
        for(k=0; k<3; k++)
        {   //across rows
            if((record[k][0]==1)&&(record[k][1]==1)&&(record[k][2]==1))
            {
                delay(400);
                hidemouseptr();
                cleardevice();
                settextstyle(0,0,3);
                moveto(50,100);
                sprintf(array,"%s is Winner",p1);
                outtext(array);
                win=1;
                return win;
            }
            else if((record[k][0]==2)&&(record[k][1]==2)&&(record[k][2]==2))
            {
                delay(400);
                hidemouseptr();
                cleardevice();
                settextstyle(0,0,3);
                moveto(50,100);
                sprintf(array,"%s is Winner",p2);
                outtext(array);
                win=2;
                return win;
            }                                    //across columns
            else if((record[0][k]==1)&&(record[1][k]==1)&&(record[2][k]==1))
            {
                delay(400);
                hidemouseptr();
                cleardevice();
                settextstyle(0,0,3);
                moveto(50,100);
                sprintf(array,"%s is Winner",p1);
                outtext(array);
                win=1;
                return win;
            }
            else if((record[0][k]==2)&&(record[1][k]==2)&&(record[2][k]==2))
            {
                delay(400);
                hidemouseptr();
                cleardevice();
                settextstyle(0,0,3);
                moveto(50,100);
                sprintf(array,"%s is Winner",p2);
                outtext(array);
                win=2;
                return win;
            }
        }       //across diagonals
        n=0;
        while(n<3)
        {
            a[n]=record[n][n];
            n++;
        }
        n=0;
        k=2;
        while(n<3)
        {
            b[n]=record[n][k];
            n++;
            k--;
        }
        if(((a[0]==1)&&(a[1]==1)&&(a[2]==1))||((b[0]==1)&&(b[1]==1)&&(b[2]==1)))
        {
            delay(400);
            hidemouseptr();
            cleardevice();
            settextstyle(0,0,3);
            moveto(50,100);
            sprintf(array,"%s is Winner",p1);
            outtext(array);
            win=1;
            return win;
        }
        else if(((a[0]==2)&&(a[1]==2)&&(a[2]==2))||((b[0]==2)&&(b[1]==2)&&(b[2]==2)))
        {
            delay(400);
            hidemouseptr();
            cleardevice();
            settextstyle(0,0,3);
            moveto(50,100);
            sprintf(array,"%s is Winner",p2);
            outtext(array);
            win=2;
            return win;
        }
    }
    return win;
}
int newgame()
{
    int count=0,j=1,x,y,g,h,button,l=0,m=0,flag,win;
    initlz();
    showmouseptr();
    while(1)
    {   delay(20);
        getmousepos(&button,&g,&h);
        while((j<3)&&(button==1))
        {
            x=g;
            y=h;
            button=-1;
            fflush(stdin);
            chkquad(&x,&y,&l,&m);     //quadrants
            if(record[l][m]==0)
            {   if(j==1)
                {
                    j=2;
                    flag=1;
                }
                else
                {
                    j=1;
                    flag=2;
                }
                record[l][m]= flag;
                count++;
            }
            else
                break;
            point(x,y,flag,flag);
            win=chkwin(count);
            if((win==1)||(win==2))
                return win;
        }
        if(count==9)
            goto out;
        if(button==2)
        {
            options(count,j);
            return 0;
        }
        fflush(stdin);
        fflush(stdout);
        delay(20);
    }
out:
    hidemouseptr();
    cleardevice();
    settextstyle(0,0,4);
    moveto(250,150);
    outtext("Draw");
    delay(2000);
    fflush(stdin);
    fflush(stdout);
    return 3;
}

void options(int count,int p)
{   int mid,g,h,button,x,y;
    hidemouseptr();
    setcolor(BLUE);
    rectangle(left-10,top+10,right+10,bottom-12);
    setfillstyle(1,WHITE);
    floodfill(left+150,top+150,BLUE);
    mid=(bottom-top)/2;
    setcolor(0);
    line(left-10,mid+top,right+10,mid+top);
    settextstyle(0,0,3);
    moveto(left+60,200);
    outtext("SAVE");
    moveto(left+60,295);
    outtext("QUIT");
    showmouseptr();
    while(1)
    {
        getmousepos(&button,&g,&h);
        delay(100);
        if(button==1)
        {
            hidemouseptr();
            x=g;
            y=h;
            if((x>190)&&(x<430))
            {
                if((y>180)&&(y<(mid+180)))
                {
                    save(count,p);
                    return;
                }
                else if((y>(mid+180))&&(y<(bottom-12)))
                {
                    cleardevice();
                    exit();
                }
                else
                {
                    resume(p);
                    return;
                }
            }
            else
            {
                resume(p);
                return;
            }
        }
    }
}
void save(int count,int p)
{
    int i,j;
    FILE *fp;
    fp=fopen("SAVE.TXT","w");
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            fprintf(fp,"%d ",record[i][j]);
    fprintf(fp,"%d ",count);
    fprintf(fp,"%d ",p);
    fclose(fp);
    cleardevice();
    settextstyle(0,0,2);
    setcolor(WHITE);
    moveto(175,225);
    outtext("Saved Successfully");
    delay(1000);
    return;
}
void load()
{
    int i,j,x=0,y=0,g,h,button,p,count,l=0,m=0,flag,win,q,ch;
    FILE *fp;
    fp=fopen("SAVE.TXT","r");
    if((ch=getc(fp))==EOF)
    {
        cleardevice();
        setcolor(BLUE);
        settextstyle(0,0,3);
        moveto(150,250);
        outtext("NO SAVED GAMES");
        return;
    }
    rewind(fp);
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            fscanf(fp,"%d",&record[i][j]);
    fscanf(fp,"%d",&count);
    fscanf(fp,"%d",&p);
    fclose(fp);
    drawbase();
    q=(p+1)%2;
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
        {
            quadcent(i,j,&x,&y);
            point(x,y,record[i][j],q);
        }
    showmouseptr();
    while(1)
    {
        delay(20);
        fflush(stdin);
        fflush(stdout);
        getmousepos(&button,&g,&h);
        while((p<3)&&(button==1))
        {
            x=g;
            y=h;
            button=-1;
            fflush(stdin);
            chkquad(&x,&y,&l,&m);     //quadrants
            if(record[l][m]==0)
            {   if(p==1)
                {
                    p=2;
                    flag=1;
                    q=1;
                }
                else
                {
                    p=1;
                    flag=2;
                    q=2;
                }
                record[l][m]= flag;
                count++;
            }
            else
                break;
            point(x,y,flag,q);
            win=chkwin(count);
            if((win==1)||(win==2))
            {
                fp=fopen("SAVE.TXT","w");
                fclose(fp);
                return;
            }
        }
        if(count==9)
            goto out;
        if(button==2)
        {
            options(count,p);
            return;
        }
        fflush(stdin);
        fflush(stdout);
        delay(20);
    }
out:
    hidemouseptr();
    cleardevice();
    settextstyle(0,0,4);
    moveto(250,150);
    outtext("Draw");
    delay(2000);
    fflush(stdin);
    fflush(stdout);
    fp=fopen("SAVE.TXT","w");
    fclose(fp);
}

void resume(int p)
{
    int i,j,x,y,h,g,button,l=0,m=0,flag,count,win,q;
    cleardevice();
    drawbase();
    q=(p+1)%2;
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
        {
            quadcent(i,j,&x,&y);
            point(x,y,record[i][j],q);
        }
    showmouseptr();
    while(1)
    {
        delay(20);
        fflush(stdin);
        fflush(stdout);
        getmousepos(&button,&g,&h);
        while((p<3)&&(button==1))
        {
            x=g;
            y=h;
            button=-1;
            fflush(stdin);
            chkquad(&x,&y,&l,&m);     //quadrants
            if(record[l][m]==0)
            {   if(p==1)
                {
                    p=2;
                    flag=1;
                    q=1;
                }
                else
                {
                    p=1;
                    flag=2;
                    q=2;
                }
                record[l][m]= flag;
                count++;
            }
            else
                break;
            point(x,y,flag,q);
            win=chkwin(count);
            if((win==1)||(win==2))
                return;
        }
        if(count==9)
            goto out;
        if(button==2)
        {
            options(count,p);
            return;
        }
        fflush(stdin);
        fflush(stdout);
        delay(20);

    }
out:
    hidemouseptr();
    cleardevice();
    settextstyle(0,0,4);
    moveto(250,150);
    outtext("Draw");
    delay(2000);
    fflush(stdin);
    fflush(stdout);
}
//mouse programs
int initmouse()
{
    i.x.ax = 0;
    int86(0X33,&i,&o);
    return ( o.x.ax );
}

void showmouseptr()
{
    i.x.ax = 1;
    int86(0X33,&i,&o);
}

void getmousepos(int *button, int *g, int *h)
{
    i.x.ax = 3;
    int86(0X33,&i,&o);

    *button = o.x.bx;
    *g = o.x.cx;
    *h = o.x.dx;
}
void restrictmouseptr(int x1, int y1, int x2, int y2)
{
    i.x.ax = 7;
    i.x.cx = x1;
    i.x.dx = x2;
    int86(0X33,&i,&o);

    i.x.ax = 8;
    i.x.cx = y1;
    i.x.dx = y2;
    int86(0X33,&i,&o);
}
void hidemouseptr()
{
    i.x.ax = 2;             // to hide mouse
    int86(0X33,&i,&o);
}


void search()
{
    int dummy;
    char str[10],msg[10];
    FILE *fp;
    long int fp1;
    fp=fopen("SCORE.TXT","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s",str);
        if(strcmp(p1,str)==0)
        {
            fgets(msg,strlen(p1)+1,fp);
            fscanf(fp,"%f",&sc1);
        }
        else if(strcmp(p2,str)==0)
        {
            fgets(msg,strlen(p2)+1,fp);
            fscanf(fp,"%f",&sc2);
        }
        else
            fscanf(fp,"%d",&dummy);
    }
    fclose(fp);
    fp=fopen("SCORE.TXT","a+");
    if(sc1==-1.000000)
    {   fprintf(fp,"\n%s\n%f",p1,0.000000);
        sc1=0.000000;
    }
    if(sc2==-1.000000)
    {   fprintf(fp,"\n%s\n%f",p2,0.000000);
        sc2=0.000000;
    }
    fclose(fp);
}
void scoreup(int win)
{
    int dummy=0;
    char str[10],msg[10];
    FILE *fp;
    long int fp1,fp2;
    if(win==1)
    {
        sc1+=10.000000;
        sc2-=5.000000;
    }
    else if(win==2)
    {
        sc2+=10.000000;
        sc1-=5.000000;
    }
    else if(win==3)
    {
        sc1+=5.000000;
        sc2+=5.000000;
    }
    fp=fopen("SCORE.TXT","r+");
    rewind(fp);
    while(!feof(fp))
    {
        fscanf(fp,"%s",str);
        if(strcmp(p1,str)==0)
        {
            fgets(msg,strlen(p1)+1,fp);
            fp1=ftell(fp);
        }
        else if(strcmp(p2,str)==0)
        {
            fgets(msg,strlen(p2)+1,fp);
            fp2=ftell(fp);
        }
        else
            fscanf(fp,"%d",&dummy);
    }
    fclose(fp);
    fp=fopen("SCORE.TXT","r+");
    fseek(fp,fp1,0);
    fprintf(fp,"%f",sc1);
    fseek(fp,fp2,0);
    fprintf(fp,"%f",sc2);
    fclose(fp);
}
void hs()
{
    FILE *fp;
    char str[10],msg[10];
    player *q,*first=NULL;
    int dummy,count=0;
    float sc;
    fp=fopen("HS.TXT","r");
    while(!feof(fp))
    {
        if(fscanf(fp,"%s",str)>0)
        {   fgets(msg,strlen(p1)+1,fp);
            fscanf(fp,"%f",&sc);
            if((strcmp(str,p1)!=0)&&(strcmp(str,p2)!=0))
            {
                first=LLI(first,str,sc);
                count++;
            }
        }
    }
    fclose(fp);
    if(sc1!=-1&&sc2!=-1)
    {
        first=LLI(first,p1,sc1);
        first=LLI(first,p2,sc2);
        count+=2;
        first=sort(first,count);
    }
    display(first);
}

player *LLI(player *x,char s[10],float scr)
{
    player *p,*temp;
    p=(player*)malloc(sizeof(player));
    p->ptr=NULL;
    strcpy(p->name,s);
    p->score=scr;
    if(x==NULL)
    {
        x=p;
    }
    else
    {
        temp=x;
        while(temp->ptr!=NULL)
            temp=temp->ptr;
        temp->ptr=p;
    }
    return x;
}




void display(player *x)
{
    char n,array[10];
    int i=0,scr;
    FILE *fp;
    player *temp;
    cleardevice();
    if(x==NULL)
    {
        setcolor(BLUE);
        settextstyle(0,0,3);
        moveto(150,250);
        outtext("NO HIGH SCORES");
        getch();
        return;
    }
    temp=x;
    setcolor(BLUE);
    rectangle(0,0,getmaxx(),getmaxy());
    setfillstyle(1,WHITE);
    floodfill(250,250,BLUE);
    settextstyle(0,0,4);
    moveto(75,75);
    outtext("NAME");
    moveto(375,75);
    outtext("SCORE");
    setcolor(GREEN);
    settextstyle(0,0,3);
    fp=fopen("HS.TXT","w");
    while((i<3)&&(temp!=NULL))
    {
        moveto(75,150+(i*75));
        outtext(temp->name);
        moveto(430,150+(i*75));
        scr=temp->score;
        sprintf(array,"%d",scr);
        outtext(array);
        fprintf(fp,"%s\n%f\n",temp->name,temp->score);
        temp=temp->ptr;
        i++;

    }
    fclose(fp);
    getch();
    return;
}

player *sort(player *x,int n)
{
    int i=0,j=0,loop,numofnodes;
    player *next,*prev,*behindprev;
    numofnodes=n;
    j=0;
    while(j<numofnodes)
    {
        prev=x;
        next=x->ptr;
        behindprev=x;
        loop=0;
        i=0;
        while(i<(n-1-j))
        {

            if(prev->score<next->score)
            {
                if(loop==0)
                {
                    prev->ptr = next->ptr;
                    next->ptr = prev;
                    x = next;
                }
                else
                {
                    prev->ptr = next->ptr;
                    next->ptr = prev;
                    behindprev->ptr=next;
                }
                behindprev=next;
                next=prev->ptr;
            }
            else
            {
                if(loop==0)
                    x=prev;
                else
                    behindprev=behindprev->ptr;
                next=next->ptr;
                prev=prev->ptr;
            }
            loop++;
            i++;
        }
        j++;

    }
    return x;
}
void loading()
{
    setbkcolor(WHITE);
    setcolor(RED);
    settextstyle(0,0,3);
    moveto(230,250);
    outtext("Loading..........");
}
