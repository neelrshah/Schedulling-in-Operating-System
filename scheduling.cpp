

#include<iostream>

#include<stdio.h>
using namespace std;

class cpuschedule
{
    int n,Bu[20];
    float Twt,Awt,A[10],Wt[10],w;
public:
    //Getting the No of processes & burst time
    void Getdata();
    //First come First served Algorithm
    void Fcfs();
    //Shortest job First Algorithm
    void Sjf();
    //Shortest job First Algorithm with Preemption
    void SjfP();
    //Shortest job First Algorithm with NonPreemption
    void SjfNp();
    //Round Robin Algorithm
    void RoundRobin();
    //Priority Algorithm
    void Priority();
};
// Implementation file for Cpu scheduling

//Getting no of processes and Burst time
void cpuschedule::Getdata()
{
    int i;
    cout<<"\nEnter the no of processes:";
    cin>>n;
    for(i=1; i<=n; i++)
    {
        cout<<"\nEnter The BurstTime for Process p"<<i<<"=	";
        cin>>Bu[i];
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//First come First served Algorithm
void cpuschedule::Fcfs()
{
    int i,B[10];
    Twt=0.0;
    for(i=1; i<=n; i++)
    {
        B[i]=Bu[i];
        cout<<"\nBurst time for process p"<<i<<"=	";
        cout<<B[i];
    }
    Wt[1]=0;
    for(i=2; i<=n; i++)
    {
        Wt[i]=B[i-1]+Wt[i-1];
    }

    //Calculating Average Weighting Time
    for(i=1; i<=n; i++)
    {
        Twt=Twt+Wt[i];
    }
    Awt=Twt/n;
    cout<<"\n\nTOTAL WEIGHTING TIME="<<Twt<<endl;
    cout<<"\n\nAVERAGE WEIGHTING TIME="<<Awt<<""<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Shortest job First Algorithm with NonPreemption

void cpuschedule::SjfNp()
{
    int i,B[10],Tt=0,temp,j;
    char S[10];
    float A[10],temp1,t;
    Twt=0.0;
    w=0.0;
    for(i=1; i<=n; i++)
    {
        B[i]=Bu[i];
        cout<<"\nBurst time for process p"<<i<<"=	";
        cout<<B[i];
        S[i]='T';
        Tt=Tt+B[i];
        cout<<"\nEnter the Arrival Time for"<<i<<"th process=	";
        cin>>A[i];
    }

    for(i=n; i>=1; i--)
    {
        for(j=3; j<=n; j++)
        {
            if(B[j-1]>B[j])
            {
                temp=B[j-1];
                temp1=A[j-1];
                B[j-1]=B[j];
                A[j-1]=A[j];
                B[j]=temp;
                A[j]=temp1;
            }
        }
    }


    //For the 1st process
    Wt[1]=0;
    w=w+B[1];
    t=w;
    S[1]='F';

    while(w<Tt)
    {
        i=2;
        while(i<=n)
        {
            if(S[i]=='T'&&A[i]<=t)
            {
                Wt[i]=w;
             
                S[i]='F';
                w=w+B[i];
                t=w;
                i=2;
            }
            else
                i++;
        }
    }


    //calculating average weighting Time
    for(i=1; i<=n; i++)
        Twt=Twt+(Wt[i]-A[i]);
    Awt=Twt/n;
    cout<<"\nTOTAL WEIGHTING TIME="<<Twt<<""<<endl;
    cout<<"\nAVERAGE WEIGHTING TIME="<<Awt<<""<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Priority Algorithm

void cpuschedule::Priority()
{
    int i,B[10],P[10],j;
    w=0.0;
    int max;
    Twt=0.0;
    max=1;
    for(i=1; i<=n; i++)
    {
        B[i]=Bu[i];
        cout<<"\nBurst time for process p"<<i<<"=	";
        cout<<B[i];
        cout<<"\nEnter the priority for process P"<<i<<"=	";
        cin>>P[i];
        if(max<P[i]){
            max=P[i];
        }
    }
    j=1;
    while(j<=max)
    {
        i=1;
        while(i<=n)
        {
            if(P[i]==j)
            {
                Wt[i]=w;
                w=w+B[i];
            }
            i++;
        }
        j++;
    }

    //calculating average weighting Time
    for(i=1; i<=n; i++){
        Twt=Twt+Wt[i];
    }
    Awt=Twt/n;
    cout<<"\nTOTAL WEIGHTING TIME="<<Twt<<""<<endl;
    cout<<"\nAVERAGE WEIGHTING TIME="<<Awt<<""<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Shortest job First Algorithm with Preemption

void cpuschedule::SjfP()
{
    int i,j,m,Wt[10],k,B[10],A[10],Tt=0,Wtm[10],temp;
    char S[20],start[20];
    int max=0,Time=0,min;
    float Twt=0.0,Awt;
    for(i=1; i<=n; i++)
    {
        B[i]=Bu[i]; 
        cout<<"\nBurst time for process P"<<i<<"=	"<<B[i]<<endl; 
        if(B[i]>max){
            max=B[i];
        }
        Wt[i]=0;
        S[i]='T';
        start[i]='F';
        Tt=Tt+B[i];
        cout<<"\nEnter the Arrival Time for"<<i<<"th process=	";
        cin>>A[i];
        if(A[i]>Time){
            Time=A[i];
        }
    }
    //cout<<"Max="<<max;
    int w=0,flag=0,t=0;
    i=1;
    while(t<Time)
    {
        if(A[i]<=t && B[i]!=0)
        {
            if(flag==0)
            {
                Wt[i]=Wt[i]+w;
                cout<<"Wt["<<i<<"]="<<Wt[i];
            }
            B[i]=B[i]-1;
            if(B[i]==0)
                S[i]='F';
            start[i]='T';
            t++;
            w=w+1;
            if(S[i]!='F')
            {
                j=1;
                flag=1;
                while(j<=n && flag!=0)
                {
                    if(S[j]!='F' && B[i]>B[j] && A[j]<=t && i!=j )
                    {
                        flag=0;
                        Wt[i]=Wt[i]-w;
                        i=j;
                    }
                    else
                    {
                        flag=1;
                    }
                    j++;
                }
            }
            else
            {
                i++;
                j=1;
                while(A[j]<=t &&j<=n)
                {
                    if(B[i]>B[j] && S[j]!='F')
                    {
                        flag=0;
                        i=j;
                    }
                    j++;
                }
            }
        }
        else if(flag==0){
            i++;
        }
    }


    cout<<"\nPrinting remaining burst time"<<endl;  
    for(i=1; i<=n; i++){
        cout<<"B["<<i<<"]="<<B[i]<<endl;
    }
    cout<<"";

    while(w<Tt)
    {
        min=max+1;
        i=1;
        while(i<=n)
        {
            if(min>B[i] && S[i]=='T')
            {
                min=B[i];
                j=i;
            }
            i++;
        }
        i=j;
        if(w==Time && start[i]=='T')
        {
            w=w+B[i];
            S[i]='F';
        }
        else
        {
            Wt[i]=Wt[i]+w;
            w=w+B[i];
            S[i]='F';
        }
    }

    cout<<"\nWeight info"<<endl;   

    for(i=1; i<=n; i++) {
        cout<<"WT["<<i<<"]="<<Wt[i]<<endl;  
    }
    cout<<"\nafter subtracting arrival time"<<endl;  
    for(i=1; i<=n; i++)
    {
        Wt[i]=Wt[i]-A[i];
        cout<<"WT["<<i<<"]="<<Wt[i]<<endl;
    }
    //Calculating Average Weighting time
    for(i=1; i<=n; i++)
        Twt=Twt+Wt[i];
    Awt=Twt/n;
    cout<<"\nAVERAGE WEIGHTING TIME="<<Awt<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Round Robin Algorithm

void cpuschedule::RoundRobin()
{

    int i,j,tq,k,B[10],Rrobin[10][10],count[10];
    int max=0;
    int m;
    Twt=0.0;
    for(i=1; i<=n; i++)
    {
        B[i]=Bu[i];
        cout<<"\nBurst time for process p"<<i<<"=	";
        cout<<B[i];
        if(max<B[i])
            max=B[i];
        Wt[i]=0;
    }
    cout<<"\nEnter the Time Quantum=  ";
    cin>>tq;
    //TO find the dimension of the Rrobin array
    m=max/tq+1;

    //initializing Rrobin array
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=m; j++)
        {
            Rrobin[i][j]=0;
        }
    }
    //placing value in the Rrobin array
    i=1;
    while(i<=n)
    {
        j=1;
        while(B[i]>0)
        {
            if(B[i]>=tq)
            {
                B[i]=B[i]-tq;
                Rrobin[i][j]=tq;
                j++;
            }
            else
            {
                Rrobin[i][j]=B[i];
                B[i]=0;
                j++;
            }
        }
        count[i]=j-1;
        i++;
    }

    cout<<"Display"<<endl; 
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=m; j++)
        {
            cout<<"Rr["<<i<<","<<j<<"]="<<Rrobin[i][j]<<endl; 
            //cout<<"	";
        }
        cout<<"\n";
    }
    //calculating weighting time
    int x=1;
    i=1;
    while(x<=n)
    {
        for(int a=1; a<x; a++)
        {
            Wt[x]=Wt[x]+Rrobin[a][i];
        }
        i=1;
        int z=x;
        j=count[z];
        k=1;
        while(k<=j-1)
        {
            if(i==n+1)
            {
                i=1;
                k++;
            }
            else
            {
                if(i!=z)
                {
                    Wt[z]=Wt[z]+Rrobin[i][k];
                }
                i++;
            }
        }
        x++;
    }
    for(i=1; i<=n; i++) {
        cout<<"\nWeighting Time for process P"<<i<<"="<<Wt[i]<<endl; 
    }

    //calculating Average Weighting Time
    for(i=1; i<=n; i++) {
        Twt=Twt+Wt[i];
    }
    Awt=Twt/n;
    cout<<"\nTOTAL WEIGHTING TIME="<<Twt<<endl;
    cout<<"\nAVERAGE WEIGHTING TIME="<<Awt<<""<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Application file for cpu Scheduling

int main()
{
    int ch,cho;
    cpuschedule c;
    do
    {
        cout<<"1.INPUT BURST TIME"<<endl;
        cout<<"2.FIRST COME FIRST SERVE"<<endl;
        cout<<"3.SHORTEST JOB FIRST"<<endl;
        cout<<"4.ROUND ROBIN"<<endl;
        cout<<"5.PRIORITY"<<endl;
        cout<<"6.EXIT"<<endl;
        cout<<"ENTER YOUR CHOICE: "<<endl;
        cin>>ch;
        switch(ch)
        {
        case 1:
            c.Getdata();
            break;
        case 2:
            cout<<"\nFIRST COME FIRST SERVED SCHEDULING"<<endl;
            c.Fcfs();
            break;
        case 3:
            cout<<"\nSHORTEST JOB FIRST SCHEDULING"<<endl;
            do
            {
                
                cout<<"1.SJF-Preemptive"<<endl;
                cout<<"2.SJF-NonPreemptive"<<endl;
                cout<<"3.EXIT"<<endl;
                cout<<"Enter your choice: "<<endl;
                cin>>cho;
                switch(cho)
                {
                case 1:
                    c.SjfP();
                    break;
                case 2:
                    c.SjfNp();
                    break;
                case 3:
                	break;
                }
            }
            while(cho<=2);
            break;
        case 4:
            cout<<"\nROUND ROBIN SCHEDULING"<<endl;
            c.RoundRobin();
            break;
        case 5:
            cout<<"\nPRIORITY SCHEDULING"<<endl;
            c.Priority();
            break;
        case 6:
            break;
        }
    }
    while(ch<=5);
}

/*


1.INPUT BURST TIME
2.FIRST COME FIRST SERVE
3.SHORTEST JOB FIRST
4.ROUND ROBIN
5.PRIORITY
6.EXIT
ENTER YOUR CHOICE: 
1

Enter the no of processes:4

Enter The BurstTime for Process p1=	10

Enter The BurstTime for Process p2=	5

Enter The BurstTime for Process p3=	15

Enter The BurstTime for Process p4=	7
1.INPUT BURST TIME
2.FIRST COME FIRST SERVE
3.SHORTEST JOB FIRST
4.ROUND ROBIN
5.PRIORITY
6.EXIT
ENTER YOUR CHOICE: 
2

FIRST COME FIRST SERVED SCHEDULING

Burst time for process p1=	10
Burst time for process p2=	5
Burst time for process p3=	15
Burst time for process p4=	7

TOTAL WEIGHTING TIME=55

AVERAGE WEIGHTING TIME=13.75

*/
