#include<iostream>
#include<math.h>
using namespace std;

#define d 2
#define N 10000
#define G 1000
#define PI 3.14159265

float minf=100000;
float minarea=100000;
int num=0;


class matrix
{	
private:
	float corner[d];
	float width[d];
	
	float area;
	
	float getrho;
public:
	float f;
	float center[d];
	void calculate(float w[d],float cor[d]);
	void update();
	float *getwidth();
	float *getcorner();
	float getgetrho();
	void savefile();
	float function(float w[d], float cor[d]);
};

float matrix::function(float w[d], float cor[d]){
	int i;
	float B;
	float ncenter[d];

	f=20;
	B=4.0;
	for(i=0;i<d;i++)
	{
		ncenter[i]=2*B*center[i]-B-0.1;

		f+= ncenter[i]*ncenter[i]-10*cos(2*PI*ncenter[i]);//func xi^2
	}
	return f;

}

void matrix::calculate(float w[d],float cor[d])
{
	int i;
	float B;
	float GVn;
	float ncenter[d];
	for(i=0;i<d;i++)
	{
		width[i]=w[i];
		corner[i]=cor[i];
		center[i]=cor[i] + w[i]/2;
	}
	area=1;
	for(i=0;i<d;i++)
	{
		area*=width[i];
	}
	f=20;
	B=4.0;
	for(i=0;i<d;i++)
	{
		ncenter[i]=2*B*center[i]-B-0.1;

		f+= ncenter[i]*ncenter[i]-10*cos(2*PI*ncenter[i]);//func xi^2
	}
		f *= 0.001;
	if(num==0)
	{
		minf=f;
		minarea=area;
	}
	if(f<minf) minf=f;
	if(area<minarea) minarea=area;

	GVn = pow((minarea * log(1/minarea)), 2.0/d);
	getrho = pow(area,2.0/d)/(f-minf+d*GVn);
}

void matrix::update()
{
	float GVn;

	GVn = pow((minarea * log(1/minarea)), 2.0/d);
	getrho = pow(area,2.0/d)/(f-minf+d*GVn);
}

float * matrix::getwidth()
{
	float *temp=new float[d];
	int i;
	for(i=0;i<d;i++)
	{
		temp[i]=width[i];
	}
	return temp;
}
float * matrix::getcorner()
{
	float *temp=new float[d];
	int i;
	for(i=0;i<d;i++)
	{
		temp[i]=corner[i];
	}
	return temp;
}

float matrix::getgetrho()
{
	return getrho;
}

void matrix::savefile()
{
	FILE *f;
	int i,j;
	f=fopen("123.txt","a+");
	cout<<"center ";
	for(i=0;i<d;i++)
	{
		cout<<center[i]<<" ";
		fprintf(f,"%f ",center[i]);
	}
	cout<<endl;
	
	fprint()
	fprintf(f,"\n\n");
	fclose(f);
}

class matrix m[N];

int main()
{
	
	float w0[d],cor0[d];
	int i,j,k;
	float maxgetrho;
	int maxtemp=0;
	float *maxwidth,*maxcorner;
	float tempwidth[3][d],tempcorner[3][d];


	//the first retrangle
	for(i=0;i<d;i++)
	{
		w0[i]=1;
		cor0[i]=0;
	}
	m[0].calculate(w0,cor0);
	num++;
	maxgetrho=m[0].getgetrho();
	maxtemp=0;
	m[0].savefile();
	cout<<num<<" max:"<<maxtemp+1<<endl;

	for(i=0;i<G;i++)// iterations 
	{
		cout<<i+1<<endl;
		//1 width,corner
		maxwidth=m[maxtemp].getwidth();
		maxcorner=m[maxtemp].getcorner();

		//2 slipt one retrangle into three retrangles
		float tempmaxwidth=0;
		int tempmax;
		for(j=0;j<d;j++)
		{
			if(maxwidth[j]>tempmaxwidth)//slipt by largest width
			{
				tempmaxwidth=maxwidth[j];
				tempmax=j;
			}
		}

		for(j=0;j<d;j++)
		{
			tempwidth[0][j]=maxwidth[j];
			tempwidth[1][j]=maxwidth[j];
			tempwidth[2][j]=maxwidth[j];
		}
		tempwidth[0][tempmax]=maxwidth[tempmax]/3;
		tempwidth[1][tempmax]=maxwidth[tempmax]/3;
		tempwidth[2][tempmax]=maxwidth[tempmax]/3;

		for(j=0;j<d;j++)
		{
			tempcorner[0][j]=maxcorner[j];
			tempcorner[1][j]=maxcorner[j];
			tempcorner[2][j]=maxcorner[j];
		}


		tempcorner[0][tempmax]=maxcorner[tempmax];
		tempcorner[1][tempmax]=maxcorner[tempmax]+maxwidth[tempmax]/3;
		tempcorner[2][tempmax]=maxcorner[tempmax]+maxwidth[tempmax]/3*2;

		m[num].calculate(tempwidth[0],tempcorner[0]);
		num++;
		m[num].calculate(tempwidth[1],tempcorner[1]);
		num++;
		m[num].calculate(tempwidth[2],tempcorner[2]);
		num++;

		//3 update retrangles
		for(j=maxtemp;j<num;j++)
		{
			m[j]=m[j+1];
		}
		num--;
		for(j=0;j<num;j++)
		{
			m[j].update();
		}
		
		//4 getrho
		maxgetrho=0;
		if(num==1)
		{
			maxgetrho=m[0].getgetrho();
			maxtemp=0;
		}
		else
		{
			for(j=0;j<num;j++)
			{
				cout<<"num: "<<j+1<<" getrho:"<<m[j].getgetrho()<<" getf:"<<m[j].f<<" ";
				for(k=0;k<d;k++)
				{
					cout<<m[j].center[k]<<" ";
				}
				cout<<endl;
				
				if(m[j].getgetrho()>maxgetrho)
				{
					maxgetrho=m[j].getgetrho();
					maxtemp=j;//the one who has the largest rho
				}
			}
		}
		
		m[maxtemp].savefile();
		cout<<num<<" max:"<<maxtemp+1<<endl;
		cout<<endl;
	}

	getchar();

	return 0;
}