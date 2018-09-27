
#include<bits/stdc++.h>
using namespace std;

#define mx 10001

int allocation[mx][mx];
int need[mx][mx];
int process[mx];


// CHECKING IF FINISH ARRAY IS COMPLETELY TRUE OR NOT
bool check(int arr[], int n)
{
    for(int i=0;i<n;i++)
    {
        if(!arr[i])
        {
            return false;
        }
    }
    return true;
}

// SAFETY ALGORITHM
bool isSafe(int available[], int n, int m)
{
    int work[m];
    int finish[n];

    // INITIALISE
    for(int i=0;i<m;i++)
    {
        work[i]=available[i];
    }

    for(int i=0;i<n;i++)
    {
        finish[i]=0;
    }
    int k=0;
    while(1)
    {
    int cntr=0;
    for(int i=0;i<n;i++)
    {
        if(!finish[i])
        {
            int j=0;
            for(j=0;j<m;j++)
            {
                if(need[i][j]>work[j])
                {
                    break;
                }
            }
            if(j==m)
            {
                for(j=0;j<m;j++)
                {
                    work[j]+=allocation[i][j];
                }
                finish[i]=true;
                process[k]=i+1;
                cntr=1;
                k++;
            }
        }
    }
    if(check(finish,n))
    {
        return true;
    }
    if(!cntr)
    {
        return false;
    }
    }
}

// RESOURCE REQUEST ALGORITHM
int resource_request_algo(int p, int request[], int available[], int n, int m)
{
    int flag=0;
    for(int i=0;i<m;i++)
    {
        if(request[i]>need[p][i])
        {
            flag=1;
            break;
        }
    }
    if(flag)
    {
        return 0;
    }
    flag=0;
    for(int i=0;i<m;i++)
    {
        if(request[i]>available[i])
        {
            flag=1;
            break;
        }
    }
    if(flag)
    {
        return 0;
    }

    for(int i=0;i<m;i++)
    {
        available[i]-=request[i];
        allocation[p][i]+=request[i];
        need[p][i]-=request[i];
    }

    if(isSafe(available,n,m))
    {
		for(int i=0;i<n;i++)
        {
            cout<<process[i]<<" ";
        }
        cout<<endl;
        return 1;
    }
    else
    {
        for(int i=0;i<m;i++)
        {
            available[i]+=request[i];
            allocation[p][i]-=request[i];
            need[p][i]+=request[i];
        }
        return 0;
    }
}

// DRIVER CODE
int main()
{

    int n,m;
    cout<<"Enter no of process: ";
    cin>>n;
    cout<<"Enter no of resource: ";
    cin>>m;

    cout<<"Enter allocation:\n";

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>allocation[i][j];
        }
    }

    cout<<"Enter max:\n";
    int max[n][m];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>max[i][j];
        }
    }

    // NEED MATRIX
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }

    cout<<"Enter available: ";
    int available[m];
    for(int i=0;i<m;i++)
    {
        cin>>available[i];
    }

    int p;
    cout<<"Enter process no which want request:";
    cin>>p;
    cout<<"Enter request for process "<<p<<" : ";
    int request[m];
    for(int i=0;i<m;i++)
    {
        cin>>request[i];
    }

    if(resource_request_algo(p-1, request, available, n, m))
    {
        cout<<"The new system is in safe state..."<<endl;
    }
    else
    {
        cout<<"The new system is not in safe state..."<<endl;
    }

    return 0;
}

