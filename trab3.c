# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <math.h>
# define N 2
# define BILHAO 1000000000

double pi = 0;
double somas[N];

double fator(int t){
  int dividendo;
  if(t%2 == 0)
    dividendo = 1;
  else
    dividendo = -1;

  return ((double)dividendo/(double)(2*t + 1));
}

void* calculo(void* t){
  long j = (long)t;
  int termos = BILHAO/N;
  int parcela = j*termos + termos;
  int i = j*termos;
  for(i; i<parcela; i++){
    somas[j] += fator(i); //threads acessando ao mesmo tempo a variavel pi -> criar vetor[N] e salvar os valores em cada pos.
  }
}

int main(){
  pthread_t threads[N];
  long i;

  for(i=0; i<N; i++)
    somas[i] = 0;

  for(i=0; i<N; i++)
    pthread_create(&threads[i], NULL, calculo,(void*) i);

  for(i=0; i<N; i++){
    pthread_join(threads[i], NULL);
    pi += somas[i];
  }

  printf("pi = %lf\n", pi*4);
}
