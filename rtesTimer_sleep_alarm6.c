//Giorgos Michailidis 7480//
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>


/*Global variables*/
long *timestamp,i;
struct  timeval *tim;
int period_usec,sample_number;
double period;
int n;
pthread_t *tid;

/*Functions*/

//Period Alert//
void period_alert(int rem){
	pthread_create(&tid[i],NULL,get_timestamp,(void*) i);//create pthread//
	i++;
	ualarm(period_usec,0);
}

//Get_timestamp//
void *get_timestamp(void *sample_number){
	n++;
	gettimeofday(&tim[(long)sample_number],NULL);//take value of gettimeofday//
	timestamp[sample]=tim[sample].tv_sec*1000000+tim[sample].tv_usec;//compute timestamp//	
	pthread_exit(NULL);//exit pthread//
}

//

/*Main*/
int main(int argc,char **argv){
	int error;
	FILE *FL;
	if (argc!=3){
		printf("ERROR: Wrong number of inputs. Please enter sampling_range and  period.");
		exit(1);
	}
	int sample_time=atoi(argv[1]);
	period=atof(argv[2]);
	sample_number=(int)(sample_time+period)/period; //calculate sample number//
	n=0;
	//Allocate memory with malloc//
	timestamp=malloc(sizeof(long)*sample_number);
	tim=malloc(sizeof(struct  timeval)*sample_number);
	tid=malloc(sample_number*sizeof(pthread_t));
	//
	period_usec=(int)(1000000*period);
	printf("Starting..period=%d\n",period_usec);
	signal(SIGALRM,period_alert);
	pthread_create(&tid[i],NULL,get_timestamp,(void*) 0);//create pthread//
	ualarm(period_usec,0);
	while(i<sample_number){
		sleep(1);//sleep until all samples taken//
	}
	for (i=i;i<sample_number;i++){
		pthread_join(tid[i],NULL);
	}
	FL=fopen("timestamps.txt","w+");//write results to file//
	fwrite(&timestamp[0],sizeof(long),sample_number,FL);
	fclose(FL);
	printf("Saved to timestamps.txt\n");
	long tot_time=timestamp[sample_number-1]-timestamp[0];//compute total time//
	printf("sample_number :%ld deigmata\n",n);
	printf("Time taken :%ld usec\nError:%ld\n",tot_time,(long)sample_time*1000000-tot_time);//print total time and error//
	return 0;
	//
}

