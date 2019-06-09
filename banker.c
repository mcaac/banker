#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> // biblioteca pra usar o sleep()
#define DORME 5



int verificarArquivo(FILE *fp, char *str);
void *initCliente(cliente c, int rec);
int gerarRandom(int max);
int *gerarRecursos(int max);
int verificarRecursos(int solicitados, int disponivel);
void *pegarRecurso(int solicitados, int recursos);
void *liberarRecurso(int solicitados, int recursos);

int Available[]; // Quantidade de recursos disponíveis de cada tipo
int Max[][]; // Quantidade máxima de recursos que um cliente pode pedir
int need[][]; // Quantidade de recursos que um cliente vai pedir em sua próxima requisição
int assigned[][]; // Recursos que estão alocados no momento e para quem
int work[]; // Para ser usado no algoritmo de safe
int finish[]; // Para ser usado no algoritmo de safe
int Aux[][];


pthread_mutex_t lock;
//falta a Matriz global de onde os ira ser retirado os recursos

int main(int argc, const char * argv[]) {
    FILE *fp;
    char *str = "teste \n";
    srand(time(NULL));
    int Max[num][3]; // tem q ler o arquivo e passar para a matriz o valores dentro dele 
    //num seria o numero de linha= numero de threads
    // 3 pois tres colunas de tipos de recursos e uma de tempo total
    
    int num = verificarArquivo(fp, str); // verificando se o arquivo tem o formato correto
    if (num <= 0) {
        printf("Arquivo de entrada inválido");
        return 0;
    }
    pthread_t threads[num]; // cria o vetor de threads de acordo com o número de linhas
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    cliente clientes[5];
 
    for (int i = 0; i < num; i++) {
        pthread_create(&threads[i], &attr, initCliente(num), argv[1]);
    }
                       sleep(50);
    return 0;
}


// colocar todas as funções completas

int gerarRandom(int max){
    int r = rand()%max;
    return r;
}


void *initCliente (int idCliente){
        int s = gerarRandom(DORME); // função pra gerar num aleatorio pra dormir

        gerarRecursos(idCliente); // função prar gerar num aleatorio de recursos solicitados
        int v = verificarRecursos(idCliente);

        if (v == 1) {
            pegarRecurso(sol,indice cliente)
            sleep(s);
        }
        else if(v==0){
            sleep(s);
            gerarRecursos(idCliente);
            verificarRecursos(idCliente);
        }
        
    
    pthread_exit(0);
}



void  *gerarRecursos(int id){
    
    for (int i = 0; i<=2; i++) {
        Aux[id][i] = gerarRandom(Max[id][i]);
    }
}



void *pegarRecurso(int id){
    // bloquear a área crítica de alguma forma MUTEX
    
    pthread_mutex_lock(&lock);
    for (int i = 0; i <= 2; i++) {
        Available[id][i] = Available[id][i] - assigned[id][i];
        need[id][i]=Max[id][i]-assigned[c][i];
        // a subtração deve ser feita na função que acessa os 
    }

    int d = gerarRandom(DORME);
    sleep(d);
    liberarRecurso(id);

    pthread_mutex_unlock(&lock);
    // LIBERA O MUTEX GALERAAA

}
//nao pode ser um funcao pra pegar e liberar recurso
// pois recurso so pode ser pego quando solicitado e liberado pelo mutex
// ja liberar recurso pode ser a qualquer momento

void *liberarRecurso(int id){
    

    for (int i = 0; i <=2; i++) {
        Available[c][i] = Available[c][i] + assigned[c][i];
    }

    pthread_exit(0);
}


int verificarRecursos(int id){
    int flag = 1;

    for (int i = 0; i <=2; i++) {
        if (Aux[id][i]>=Available[c][i]) {
            flag = 0;
            //gerarRecurso novamente
            return flag;
        }
        Aux[id][i]=assigned[id][i];
    }
    return flag; // retorna 1 se disponível e 0 se indisponível
}


