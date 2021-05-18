#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>


double angels(double positions[8], double constants[4])
{
	double vinkel;
	if(positions[0]<constants[0])
	{
		if(positions[1]<constants[2])
		{
			vinkel = ((double)((rand()%90)))*(M_PI/180.0);
		}
		else if(positions[1]>constants[3])
		{
			vinkel = ((double)((rand()%90)+270))*(M_PI/180.0);
		}
		else
		{
			vinkel = ((double)((rand()%180)-90))*(M_PI/180.0);
		}
	}
	else if(positions[0]>constants[1])
	{
		if(positions[1]<constants[2])
		{
			vinkel = ((double)((rand()%90)+90))*(M_PI/180.0);
		}
		else if(positions[1]>constants[3])
		{
			vinkel = ((double)((rand()%90)+180))*(M_PI/180.0);
		}
		else
		{
			vinkel = ((double)((rand()%180)+90))*(M_PI/180.0);
		}
	}
	else
	{
		if(positions[1]<constants[2])
		{
			vinkel = ((double)((rand()%180)))*(M_PI/180.0);
		}
		else if(positions[1]>constants[3])
		{
			vinkel = ((double)((rand()%180)+180))*(M_PI/180.0);
		}
		else
		{
			vinkel = ((double)(rand()%360))*(M_PI/180.0); 
		}
	}
	return vinkel;
}

double* container(int N,double boxs[3])
{
	static double constants[4];
	constants[0] = boxs[1]-boxs[0];
	constants[1] = boxs[1]+boxs[0];
	constants[2] = boxs[2]-boxs[0];
	constants[3] = boxs[2]+boxs[0];
	return constants;
}

void spread_virus(int N, int T, int t, double IIR, double PP, double position[8], double positions[N][N][T][8])
{
	for (int i=0; i<N; i++)
	{
		for (int n=0; n<N; n++)
		{
			if(sqrt(pow(position[0]-positions[i][n][t][0],2)+pow(position[1]-positions[i][n][t][1],2))<IIR && position[3]==0.0 && position[7]<PP)
			{
				if (positions[i][n][t][2]==7.0 || positions[i][n][t][2]==22.0)
				{
					position[2] = 7.0;
					position[3] = (double)t;
				}
			}
			if(sqrt(pow(position[0]-positions[i][n][t][0],2)+pow(position[1]-positions[i][n][t][1],2))<IIR && position[3]==0.0 && position[7]>=PP)
			{
				if (positions[i][n][t][2]==7.0 || positions[i][n][t][2]==22.0)
				{
					position[2] = 22.0;
					position[3] = (double)t;
				}
			}
		}
	}
}

void random_walk(int N,int T,int t,double IR,double P, double positions[N][N][T][8],int SIAD[4][T], double R[3][T],double ds)
{
	double vinkel;
	double afstand;
	int S;
	int I;
	int A;
	int D;
	double BL = 2;
	//box = [størrelse af box, x-position af box, y-position af box]
	double box[3];
	for (int i=0;i<N;i++)
	{
		for (int n=0;n<N;n++)
		{
			//kopierer:
				//længde af infektion:
			positions[i][n][t+1][4] = positions[i][n][t][4];
				//resistance:
			positions[i][n][t+1][6] = positions[i][n][t][6];
				//symptom-status
			positions[i][n][t+1][7] = positions[i][n][t][7];
			
			if(positions[i][n][t][5]>0.0)
			{
				if(t <= (double)(T)/3)
				{
					box[0] = (double)(N/2);
					box[1] = (double)(N/2);
					box[2] = (double)(N/2);
				}
				else if (t > (double)(T)/3 && t <= (double)(T)*2/3)
				{
					if(i%2 == 0 && n%2 == 0)
						{
							box[0] = BL;
							box[1] = (double)(1);
							box[2] = (double)(1);
						}
					if(i%2 == 1 && n%2 == 0)
						{
							box[0] = BL;
							box[1] = (double)(1);
							box[2] = (double)(N);
						}
					if(i%2 == 0 && n%2 == 1)
						{
							box[0] = BL;
							box[1] = (double)(N);
							box[2] = (double)(1);
						}
					if(i%2 == 1 && n%2 == 1)
						{
							box[0] = BL;
							box[1] = (double)(N);
							box[2] = (double)(N);
						}
				}
				else if (t > (double)(T)*2/3)
				{
						box[0] = (double)(N/2);
						box[1] = (double)(N/2);
						box[2] = (double)(N/2);
				}
				/*
				if(positions[i][n][t][2] != 7.0)
				{
					box[0] = (double)((N-2)/2);
					box[1] = (double)((N-2)/2);
					box[2] = (double)((N-2)/2);
				}
				else if (positions[i][n][t][2] == 7.0)
				{
						box[0] = 0.5;
						box[1] = (double)(N);
						box[2] = (double)(N/2);
				}
				*/
				/*
				box[0] = (double)(N/2);
				box[1] = (double)(N/2);
				box[2] = (double)(N/2);
				*/
				//bestemmer den aktuelle skridtlængde:
				afstand = (((double)(rand()%100))/100.0)*ds;
				//bestemmer retningen som partiklen kan gå i:
				vinkel = angels(positions[i][n][t],container(N,box));
				//virussen spredes:
				spread_virus(N,T,t,IR,P,positions[i][n][t],positions);
				
				//ændrer position i retning af vinklen med skridtlængde afstand:
				positions[i][n][t+1][0] = positions[i][n][t][0]+cos(vinkel)*afstand;
				positions[i][n][t+1][1] = positions[i][n][t][1]+sin(vinkel)*afstand;
				
				if (positions[i][n][t][2]==7.0)
				{
					I++;
					if(t<=(positions[i][n][t][4]+positions[i][n][t][3]))
					{
						positions[i][n][t+1][2] = 7.0;
						positions[i][n][t+1][5] = positions[i][n][t][5]-positions[i][n][t][6];
					}
					else
					{
						positions[i][n][t+1][2] = 2.0;
						positions[i][n][t+1][4] = 0.0;
					}	
				}
				else if (positions[i][n][t][2]==22.0)
				{
					A++;
					if(t<=(positions[i][n][t][4]+positions[i][n][t][3]))
					{
						positions[i][n][t+1][2] = 22.0;
						positions[i][n][t+1][5] = positions[i][n][t][5]+(positions[i][n][0][5]-positions[i][n][t][5])*positions[i][n][t][6];
					}
					else
					{
						positions[i][n][t+1][2] = 2.0;
						positions[i][n][t+1][4] = 0.0;
					}
				}
				else if (positions[i][n][t][2]==2.0)
				{
					S++;
					positions[i][n][t+1][5] = positions[i][n][t][5]+(positions[i][n][0][5]-positions[i][n][t][5])*positions[i][n][t][6];
					positions[i][n][t+1][2] = 2.0;
				}
				else
				{
					positions[i][n][t+1][5] = positions[i][n][t][5];
					positions[i][n][t+1][2] = positions[i][n][t][2];
				}
				
			}
			else if(positions[i][n][t][5]<=0.0)
			{
				D++;
				positions[i][n][t+1][0] = positions[i][n][t][0];
				positions[i][n][t+1][1] = positions[i][n][t][1];
				positions[i][n][t+1][2] = 17.0;
			}
		}
	}
	SIAD[0][t] = S;
	SIAD[1][t] = I;
	SIAD[2][t] = A;
	SIAD[3][t] = D;
	
	R[0][0]=0;
	R[1][0]=0;
	R[2][0]=0;

	if (t>0 && SIAD[0][t] != 0)
	{
		R[1][t] = (((double)(SIAD[0][t-1]-SIAD[0][t]))/(double)(SIAD[0][t-1]*SIAD[1][t]));
	}
	else if (t>0 && SIAD[0][t] == 0)
	{
		R[1][t] = 1;
	}

	if (t>0 && SIAD[1][t] != 0)
	{
		R[2][t] = ((double)(SIAD[3][t]-SIAD[3][t-1]))/((double)(SIAD[1][t]));
	}
	else if (t>0 && SIAD[1][t] == 0)
	{
		R[2][t] = 1;
	}
	if (t>0 && R[2][t] != 0)
	{
		R[0][t] = ((double)(SIAD[1][t]+SIAD[2][t]))/((double)(SIAD[1][t-1]+SIAD[2][t-1]));
	}
	if (t>0 && R[2][t] == 0)
	{
		R[0][t] = 1;
	}	
	S = 0;
	I = 0;
	A = 0;
	D = 0;
}

void initial_positions(int N, int T,double IL, int p, double positions[N][N][T][8],int SIAD[4][T],double R[3][T])
{
srand(time(NULL));
	for (int i=0;i<N;i++)
	{
		for (int n=0;n<N;n++)
		{
			positions[i][n][0][0] = (double)i;
			positions[i][n][0][1] = (double)n;
			positions[i][n][0][2] = 2.0;
			positions[i][n][0][4] = IL;
			positions[i][n][0][5] = (double)((rand()%50)+50)/100.0;
			positions[i][n][0][6] = (double)(rand()%100)/1000.0;
			positions[i][n][0][7] = (double)(rand()%100)/100.0;
			//printf("%f\n",positions[i][n][0][7]);
			//printf("x-pos:%f, y-pos:%f, inf. status:%f, time of inf.:%f, duration of inf.:%f, health:%f, resistance:%f\n",positions[i][n][0][0],positions[i][n][0][1],positions[i][n][0][2],positions[i][n][0][3],positions[i][n][0][4],positions[i][n][0][5],positions[i][n][0][6]);
			SIAD[0][0] = (int)pow(N,2);
			SIAD[1][0] = 1;
			SIAD[2][0] = 0;
			SIAD[3][0] = 0;
		}
	}
	positions[0][0][0][2] = 7.0;
	//printf("x-pos:%f, y-pos:%f, inf. status:%f, time of inf.:%f, duration of inf.:%f, health:%f, resistance:%f\n",positions[0][0][0][0],positions[0][0][0][1],positions[0][0][0][2],positions[0][0][0][3],positions[0][0][0][4],positions[0][0][0][5],positions[0][0][0][6]);
}

void export_data(int N, int T, double positions[N][N][T][8])
{
	FILE * fpointer = fopen("DATA_PARTIKEL_SIAD.txt","w");
	for (int t=0; t<T;t++)
	{
		for (int i=0;i<N;i++)
		{
			for (int n=0;n<N;n++)
			{
				fprintf(fpointer,"%f	%f	%f	",positions[i][n][t][0],positions[i][n][t][1],positions[i][n][t][2]);
			}
		}
		fprintf(fpointer,"\n");
	}
	fclose(fpointer);
}

void export_picture(int N, int T)
{
	FILE * fpointer1 = fopen("GNU_SIAD_PIC.p","w");
	fprintf(fpointer1,"set terminal png size 1000,1000\n");
	fprintf(fpointer1,"set output 'VISUAL_SIAD_data.png'\n");
	fprintf(fpointer1,"set xrange [-2:%d]\n",N+2);
	fprintf(fpointer1,"set yrange [-2:%d]\n",N+2);
	fprintf(fpointer1,"set grid\n");
	//fprintf(fpointer1,"plot for [i = 1:%f:3] 'SIR_data.txt' using i:i+1 with lines lt i+2 notitle",3*pow(N,2));
	fprintf(fpointer1,"plot for [i=1:%f:3]'DATA_PARTIKEL_SIAD.txt' using i:i+1:i+2 with linespoints lc variable notitle",3*pow(N,2));
	fclose(fpointer1);
}

void export_animation(int N, int T)
{
	FILE * fpointer1 = fopen("GNU_SIAD_ANIM.p","w");
	fprintf(fpointer1,"set terminal gif animate delay 16\n");
	fprintf(fpointer1, "set datafile separator '\t'\n");
	fprintf(fpointer1,"set output 'VISUAL_SIAD_ANIM.gif'\n\n");
	fprintf(fpointer1,"set xrange [-2:%d]\n",N+2);
	fprintf(fpointer1,"set yrange [-2:%d]\n\n",N+2);
	for (int t=0; t<T-5;t++)
		{
			//fprintf(fpointer1,"plot for [i = 1:%f:3] 'SIR_data.txt' every::%d::%d using i:i+1 with lines lt i+2 notitle",3*pow(N,2),t,t+5);
			fprintf(fpointer1,"plot for [i=1:%f:3]'DATA_PARTIKEL_SIAD.txt' using i:i+1:i+2 every 1::%d::%d with linespoints lc variable notitle",3*pow(N,2),t,t+5);
			
			fprintf(fpointer1,"\n");
		}
	fclose(fpointer1);
}

int* export_plot_data(int T,int SIAD[4][T])
{
	FILE * fpointer = fopen("DATA_PLOT_SIAD.txt","w");
	for (int t=0; t<T;t++)
	{
		fprintf(fpointer,"%d	%d	%d	%d	%d\n", t, SIAD[0][t], SIAD[1][t], SIAD[2][t], SIAD[3][t]);
		//printf("%d	%d	%d	%d\n", t, SIAD[0][t], SIAD[1][t], SIAD[3][t]);
	}
	fclose(fpointer);
}

void export_plot(int N, int T)
{
	FILE * fpointer1 = fopen("GNU_SIAD_PLOT.p","w");
	fprintf(fpointer1,"set terminal png size 2000,750\n");
	fprintf(fpointer1,"set output 'VISUAL_SIAD_PLOT.png'\n");
	fprintf(fpointer1,"set xrange [0:%d]\n",T);
	fprintf(fpointer1,"set yrange [-1:%d]\n",(int)pow(N,2)+1);
	//fprintf(fpointer1,"set ytics 0,1,%d\n",(int)pow(N,2));
	//fprintf(fpointer1,"set ytics 0,1,%d\n",T);
	fprintf(fpointer1,"set grid\n");
	fprintf(fpointer1,"plot 'DATA_PLOT_SIAD.txt' using 1:2 with linespoints lt 2 title 'raske','DATA_PLOT_SIAD.txt' using 1:3 with linespoints lt 7 title 'inficerede','DATA_PLOT_SIAD.txt' using 1:4 with linespoints lt 22 title 'Asymptomatiske','DATA_PLOT_SIAD.txt' using 1:5 with linespoints lt 17 title 'døde'");
	fclose(fpointer1);
}

int* export_constants_plot_data(int N, int T,double R[3][T])
{
	FILE * fpointer = fopen("DATA_CONSTANTS_PLOT_SIAD.txt","w");
	for (int t=0; t<T;t++)
	{
		fprintf(fpointer,"%d	%f	%f	%f\n", t,R[0][t],R[1][t],R[2][t]);
		//printf("%d	%d	%d	%d\n", t, SIAD[0][t], SIAD[1][t], SIAD[3][t]);
	}
	fclose(fpointer);
}

void export_constants_plot(int N, int T)
{
	FILE * fpointer1 = fopen("GNU_SIAD_CONSTANTS_PLOT.p","w");
	fprintf(fpointer1,"set terminal png size 2000,750\n");
	fprintf(fpointer1,"set output 'VISUAL_SIAD_CONSTANTS_PLOT.png'\n");
	fprintf(fpointer1,"set xrange [0:%d]\n",T);
	//fprintf(fpointer1,"set ytics 0,1,%d\n",(int)pow(N,2));
	//fprintf(fpointer1,"set ytics 0,1,%d\n",T);
	fprintf(fpointer1,"set grid\n");
	fprintf(fpointer1,"plot 'DATA_CONSTANTS_PLOT_SIAD.txt' using 1:2 with linespoints lt 2 title 'R_0','DATA_CONSTANTS_PLOT_SIAD.txt' using 1:3 with linespoints lt 7 title 'beta','DATA_CONSTANTS_PLOT_SIAD.txt' using 1:4 with linespoints lt 22 title 'gamma'");
	fclose(fpointer1);
}

int main()
{
	//kvadrat-rod af mængden af punkter:
	int N = 10;
	//tid af simulation:
	int T = 100;
	//maksimal skridtlængde:
	double ds = 0.6;
	//infektions-radius:
	double ir = 0.8;
	//længde af infektion:
	double il = 6;
	//procentdelen af symptomatiske tilfælde
	double p = 1;
	//vektoren med mængden af Susceptible, Inficerede, Asymptomatiske og døde til hvert tidsskridt
	int SIAD[4][T];
	double R[3][T];
	double R0;
	double beta;
	double gamma;
	double counter[] = {0,0,0};
	//monsteret
	double position[N+1][N+1][T][8];
	initial_positions(N, T, il, p, position, SIAD,R);
	printf("	startbetingelser er:\n");
	printf("	- mængden af partikler: %d\n",(int)(pow(N,2)));
	printf("	- Tidslængden: %d\n", T);
	printf("	- Maksimal skridlængde: %f\n", ds);
	printf("	- Infektions-radius: %f\n", ir);
	printf("	- Infektions-længde: %d\n", (int)il);
	printf("	- Procentdelen af symptomatiske: %d%%\n",(int)(p*100));
	printf("	- Procentdelen af asymptomatiske: %d%%\n\n",(int)((1-p)*100));
	
	for (int t=0;t<T;t++)
	{
		random_walk(N,T,t,ir,p, position,SIAD,R, ds);
		R0 = R0+R[0][t];
		beta = beta+R[1][t];
		gamma = gamma+R[2][t];
	}
	R0 = R0/T;
	beta = beta/T;
	gamma = gamma/T;
	printf("	Random walk has been walked\n");
	export_data(N, T, position);
	
	printf("	R0 er: %f\n",R0);
	printf("	beta er: %f\n",beta);
	printf("	gamma er: %f\n",gamma);
	printf("	- susceptible er: %d\n",SIAD[0][T-1]);
	printf("	- Inficerede er: %d\n",SIAD[1][T-1]);
	printf("	- Asymptomatiske er: %d\n",SIAD[2][T-1]);
	printf("	- Døde er: %d\n\n",SIAD[3][T-1]);	
	printf("	Finished exporting particle data\n");
	
	export_plot_data(T, SIAD);
	printf("	Finished exporting plotting data\n");
	export_plot(N,T);
	printf("	Finished writing GNU_SIR_PLOT.p\n");
	export_constants_plot_data(N, T,R);
	printf("	Finished exporting constants\n");
	export_constants_plot(N, T);
	printf("	Finished writing GNU_SIR_CONSTANTS_PLOT.p\n");
	export_picture(N,T);
	printf("	Finished writing GNU_SIR_PIC.p\n");
	export_animation(N, T);
	printf("	Finished writing GNU_SIR_ANIM.p\n");
	return 0;
}
