#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_Equipas 4
#define MAX_Jornadas 6

struct equipa {
    char nome[50];
    int pontos;
} e[MAX_Equipas], temp;

struct campeonato {
    int jornada;
    int jogoCasa1;
    int jogoFora1;
    int jogoCasa2;
    int jogoFora2;
    int golosCasa1;
    int golosFora1;
    int golosCasa2;
    int golosFora2;
} c[MAX_Jornadas];


// declarações de funções
void menu_campeonato();
void definirJornadas();
void imprimirResultados(int jornada);
void ordenarPorPontos();
void ordenarAlfabeticamente();
void imprimirMenu1();
void imprimirMenu2();
void Classificacao(int i);

int main() {
    FILE *f;
    int menu=1;
    int equipasIntroduzidas = 0;
    int wordCount = 0, i;
    int edit;
    
    do {
        imprimirMenu1();
        scanf("%d", &menu);
        switch(menu) {
            case 1:
                //ciclo para introduzir as equipas 
                for(i=0; i<4; ++i){                  
                    printf("Introduza a equipa %d\n", i+1);
                    printf("Nome: ");
                    scanf("%s",e[i].nome);
                    //gets(e[i].nome);
                    e[i].pontos = 0;
                }
                // abrir o ficheiro para guardar as equipas introduzidas no ciclo anterior
                f = fopen("equipas.txt","w");
                for(i=0; i<4; i++) {
                    fprintf(f,"%s\n", e[i].nome);
                }
                fclose(f);
                equipasIntroduzidas = 1;
                break;
                
            case 2:
                //caso onde é possivel ao utilizador modificar as equipas
                if (equipasIntroduzidas == 1) {
                    for(i=0; i<4; ++i) {
                        printf("Equipa: %d\n", i+1);
                        printf("Name: ");
                        puts(e[i].nome);
                    }
                    printf("\nEscolha o numero da equipa que pretende editar: ");
                    scanf("%d", &edit);
                    
                    if(edit == 1 || edit == 2 || edit == 3 ||edit == 4)
                    {
                        printf("\nIntroduza o novo nome para a equipa: ");
                        scanf("%s",e[edit-1].nome);
                    }                    
                    else
                    {
                        printf("\nA opcao que introduziu nao e valido!\n\n\n");
                    }
                    
                } else {
                    printf("Ainda nao foram introduzidas equipas!\n");
                }
                break;
                
            case 3:
                //caso onde é possivel iniciar o campeonato
                if (equipasIntroduzidas == 0) {
                    printf("Ainda nao introduziu equipas para comecar o campeonato!\n");
                    break;
                }
                definirJornadas();
                menu_campeonato();
                break;
                
            case 4:
                //caso onde é possivel ir buscar equipas já anteriormente armazenadas
                f=fopen("equipas.txt","r");
                if (f == NULL) {
                    printf("O ficheiro ainda nao esta diponivel!\n");
                    break;
                }  
                while(!feof(f)) {
                    fscanf(f, "%s", e[wordCount].nome);
                    wordCount++;
                }
                equipasIntroduzidas = 1;
                fclose(f);
                break;
                
            case 0:
                break;
                
            default:
                printf("Digite uma opcao valida!\n");
        }
    } while(menu);
}

//funcao onde é iniciado a segunda parte do programa
void menu_campeonato() {
    int menu2 = 1;
    int jornada = 6;
    int creditos = 40;
    int aposta = 0;
    int i;
    char apostaJogo1, apostaJogo2;
    char resultadoJogo1, resultadoJogo2;
    int valorAposta;
    
    do {
        imprimirMenu2(jornada, creditos);
        scanf("%d", &menu2);
        switch(menu2) {
            case 1:
                //ver jornadas
                for (i = 0; i < 6; i++) {
                    printf("\n%d Jornada\n", c[i].jornada);
                    printf("%s x %s\n", e[c[i].jogoCasa1].nome, e[c[i].jogoFora1].nome);
                    printf("%s x %s\n", e[c[i].jogoCasa2].nome, e[c[i].jogoFora2].nome);
                }
                break;
                
            case 2:
                //ver resultados das jornadas anteriores
                printf("\tResultados\n");
                for (i = 0; i < jornada; i++) {
                    printf("%d Jornada\n", c[i].jornada);
                    printf("%s %d - %d %s\n", e[c[i].jogoCasa1].nome, c[i].golosCasa1, c[i].golosFora1, e[c[i].jogoFora1].nome);
                    printf("%s %d - %d %s\n", e[c[i].jogoCasa2].nome, c[i].golosCasa2, c[i].golosFora2, e[c[i].jogoFora2].nome);
                }
                break;
                
            case 3:
                //ver tabela classificativa por pontos
                ordenarPorPontos();
                printf("Classificacao!\n");
                Classificacao(i);
                break;
                
            case 4:
                //ver tabela classificativa por ordem alfabetica
                ordenarAlfabeticamente();
                printf("Classificacao!\n");
                Classificacao(i);
                break;
                
            case 5:
                //ver creditos
                printf("Creditos: %d", creditos);
                break;
                
            case 6:
                //fazer aposta da jornada
                if (jornada > 5){
                    printf("\nO Campeonato chegou ao fim!!!\n");
                    break;
                }
                
                if (aposta == 1) {
                    printf("Já efectuou as apostas para a jornada %d! Avance na jornada!\n", jornada + 1);
                    break;
                }
                
                if (creditos == 0) {
                    printf("\nJá perdeu todos os seus creditos!\n");
                    exit(0);
                    break;
                }
                
                printf("Faca as suas apostas para a jornada %d\n", jornada + 1);
                printf("%s x %s\n", e[c[jornada].jogoCasa1].nome, e[c[jornada].jogoFora1].nome);
                printf("1 x 2?\n");
                scanf("%s", &apostaJogo1);
                printf("%s x %s\n", e[c[jornada].jogoCasa2].nome, e[c[jornada].jogoFora2].nome);
                printf("1 x 2?\n");
                scanf("%s", &apostaJogo2);
                
                do {
                    printf("Introduza o numero de creditos que quer apostar: ");
                    scanf("%d", &valorAposta);
                    if (valorAposta > creditos || valorAposta <= 0) {
                        printf("Introduza um valor dentro do limite dos seus creditos!\n");  
                    }
                } while (valorAposta > creditos || valorAposta <= 0);
                
                creditos -= valorAposta;
                aposta = 1;
                break;
                
            case 7:
                //Caso para avançar a jornada
                if (jornada > 5){
                    printf("\nO Campeonato chegou ao fim!!!\n");
                    break;
                }
                
                if (aposta != 0) {
                    printf("%d jornada\n" , c[jornada].jornada); 
                    // sortear aleatoriamente os resultados
                    c[jornada].golosCasa1 =  rand() % 10;
                    c[jornada].golosFora1 =  rand() % 10;
                    c[jornada].golosCasa2 =  rand() % 10;
                    c[jornada].golosFora2 =  rand() % 10;
                    
                    // verificar a quem atribuir pontos
                    if (c[jornada].golosCasa1 > c[jornada].golosFora1) {
                        e[c[jornada].jogoCasa1].pontos += 3;
                        resultadoJogo1 = '1';
                    } else if (c[jornada].golosCasa1 < c[jornada].golosFora1) {
                        e[c[jornada].jogoFora1].pontos += 3;
                        resultadoJogo1 = '2';
                    } else {
                        e[c[jornada].jogoCasa1].pontos += 1;
                        e[c[jornada].jogoFora1].pontos += 1;
                        resultadoJogo1 = 'x';
                    }
                    
                    if (c[jornada].golosCasa2 > c[jornada].golosFora2) {
                        e[c[jornada].jogoCasa2].pontos += 3;
                        resultadoJogo2 = '1';
                    } else if (c[jornada].golosCasa2 < c[jornada].golosFora2) {
                        e[c[jornada].jogoFora2].pontos += 3;
                        resultadoJogo2 = '2';
                    } else {
                        e[c[jornada].jogoCasa2].pontos += 1;
                        e[c[jornada].jogoFora2].pontos += 1;
                        resultadoJogo2 = 'x';
                    }
                    
                    // verificar se o utilizador acertou as apostas
                    if (apostaJogo1 == resultadoJogo1 && apostaJogo2 == resultadoJogo2) {
                        creditos += valorAposta * 3;
                    } else if (apostaJogo1 != resultadoJogo1 && apostaJogo2 == resultadoJogo2) {
                        creditos += valorAposta * 2;
                    } else if (apostaJogo1 == resultadoJogo1 && apostaJogo2 != resultadoJogo2) {
                        creditos += valorAposta * 2;
                    }
                    
                    // imprimir resultado da jornada
                    printf("\n%s %d-%d %s \n", e[c[jornada].jogoCasa1].nome, c[jornada].golosCasa1, c[jornada].golosFora1, e[c[jornada].jogoFora1].nome);
                    printf("%s %d-%d %s \n", e[c[jornada].jogoCasa2].nome, c[jornada].golosCasa2, c[jornada].golosFora2, e[c[jornada].jogoFora2].nome);
                    
                    // incrementar jornada
                    jornada++;
                    aposta = 0;
                    
                } else {
                    printf("Tem de efetuar a aposta antes de avancar!");
                }
                break;
                
            case 0:
                jornada = 0;
                aposta = 0;
                break;
                
            default:
                printf("Digite uma opcao valida!\n"); 
        }
    } while(menu2 != 0);
}

//função onde são definas as jornadas
void definirJornadas(){
    // 1 jornada
    c[0].jornada = 1;
    c[0].jogoCasa1 = 0;
    c[0].jogoFora1 = 1;
    c[0].jogoCasa2 = 2;
    c[0].jogoFora2 = 3;
    // 2 jornada
    c[1].jornada = 2;
    c[1].jogoCasa1 = 1;
    c[1].jogoFora1 = 2;
    c[1].jogoCasa2 = 3;
    c[1].jogoFora2 = 0;
    // 3 jornada
    c[2].jornada = 3;
    c[2].jogoCasa1 = 3;
    c[2].jogoFora1 = 1;
    c[2].jogoCasa2 = 0;
    c[2].jogoFora2 = 2;
    // 4 jornada
    c[3].jornada = 4;
    c[3].jogoCasa1 = 1;
    c[3].jogoFora1 = 0;
    c[3].jogoCasa2 = 3;
    c[3].jogoFora2 = 2;
    // 5 jornada
    c[4].jornada = 5;
    c[4].jogoCasa1 = 2;
    c[4].jogoFora1 = 1;
    c[4].jogoCasa2 = 0;
    c[4].jogoFora2 = 3;
    // 6 jornada
    c[5].jornada = 6;
    c[5].jogoCasa1 = 1;
    c[5].jogoFora1 = 3;
    c[5].jogoCasa2 = 0;
    c[5].jogoFora2 = 2;
}

//função para ordenar a estrutura por pontos
void ordenarPorPontos() {
    int i, j;
    for (i = 1; i < 4; i++) {
      for (j = 0; j < 4 - i; j++) {
         if (e[j].pontos < e[j + 1].pontos ) {
            temp = e[j];
            e[j] = e[j + 1];
            e[j + 1] = temp;
         }
      }
    }
}

//funcao para ordenar a estrutura por ordem alfabeticamente
void ordenarAlfabeticamente() {
    int j;
    for(int i = 1; i < 4; i++) {
        j = i - 1;
        while( j >= 0 && strcmp( e[j+1].nome, e[j].nome ) < 0 )
        {
            temp =  e[j + 1];
            e[j+1] = e[j];
            e[j] = temp;
            j--;
        }
    }
}

//função para imprimir o 1ºMenu
void imprimirMenu1(){
    printf("\tCampeonato de Futebol\n\n");
    printf("1. Introduza 4 Equipas \n");
    printf("2. Editar Nome das 4 equipas \n");
    printf("3. Comecar Campeonato \n");
    printf("4. Usar Equipas Anteriores \n");
    printf("0. Sair\n");
    printf("Introduza a Opcao Desejada: ");
}

//função para imprimir o 2ºMenu
void imprimirMenu2(int jornada, int creditos){
    printf("\n\tCampeonato de Futebol\n");    
    if (jornada == 6){
        printf("Final do campeonato!!!\n");
        printf("Voce acabou com %d creditos\n\n", creditos);
    }
    else{
        printf("\tJornada %d\n\n", jornada+1);    
    }
    printf("1. Ver Jornadas \n");
    printf("2. Ver Resultados \n");
    printf("3. Ver Classificacao por Pontos \n");
    printf("4. Ver Classificacao por Ordem Alfabetica \n");
    printf("5. Ver Creditos \n");
    printf("6. Fazer Aposta \n");
    printf("7. Avancar Jornada \n");
    printf("0. Sair para o Menu Principal\n");
    printf("Introduza a Opcao Desejada: ");
}

//função onde imprime a classificação
void Classificacao(int i){
    for (i = 0; i < 4; i++)
    {
        printf("%d - %s: %d Pontos\n", i+1, e[i].nome, e[i].pontos);
    }
}
