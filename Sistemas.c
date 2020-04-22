#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef
    struct No
    {
        void* info;
        struct No* prox;
        double valor;
        double resposta;
    }
    No;

typedef
    struct Lista
    {
        No* inicio;
        int qtdVariaveis;
        int (*compareTo)(void*, void*);
        void (*print)(void*);
    }
    Lista;

typedef
    enum boolean
    {
        false,
        true
    }
    boolean;

boolean pesquisar(Lista* lis, void* info)
{
    if(lis==NULL)
        return false;

    if(lis->inicio==NULL)
        return false;

    No* atual = lis->inicio;

    while(atual!=NULL)
    {
        if(strcmp((char*)atual->info, (char*)info)==0)
            return true;

        atual = atual->prox;
    }

    return false;
}

int posicao(Lista* lis, void* info)
{
    if(lis==NULL)
        return -1;

    if(lis->inicio==NULL)
        return -1;

    No* atual = lis->inicio;

    int pos =0;

    while(atual!=NULL)
    {
        if(strcmp((char*)atual->info, (char*)info)==0)
            return pos;

        atual = atual->prox;

        pos++;
    }

    return -1;
}

void insira(Lista* lis, void* info)
{
    if(lis==NULL)
        return;

    lis->qtdVariaveis++;

    if(lis->inicio==NULL)
    {
        lis->inicio = (No*)malloc(sizeof(No));
        lis->inicio->info = info;
        //lis->inicio->valor = ;
        lis->inicio->prox = NULL;
        return;
    }

    No* atual =  lis->inicio;

    while(atual->prox!=NULL)
    {
        atual = atual->prox;
    }

    atual->prox = (No*)(malloc(sizeof(No)));
    atual->prox->info = info;
  //  atual->prox->valor = NULL;
    atual->prox->prox = NULL;
}

void exclua(Lista* lis, int pos)
{
    if(lis==NULL)
        return;

    if(lis->inicio==NULL)
        return;

    No* atual = lis->inicio;

    int i;

    if(pos==0)
        lis->inicio = lis->inicio->prox;

    for(i=0; i<pos-1; i++)
        if(atual==NULL)
            return;
        else
            atual = atual->prox;

    if(atual == NULL)
        return;

    if(atual->prox != NULL)
    {
        if(atual->prox->prox!= NULL)
        {
            atual->prox->info = atual->prox->prox->info;
            atual->prox->prox = atual->prox->prox->prox;

            return;
        }

        atual->prox->info = NULL;
        atual->prox = NULL;

        return;
    }
    else
    {
        atual->prox->info = NULL;
        atual->prox = NULL;
        return;
    }
}

void insiraValor(Lista* lis, double info, int pos)
{
    int i;

    No* atual = lis->inicio;

    for(i=0; i<pos; i++)
        if(atual->prox==NULL)
            break;
        else
            atual = atual->prox;

    atual->valor = info;
}

void insiraResultado(Lista* lis, double resultado, int pos)
{
    int i;

    No* atual = lis->inicio;

    for(i=0; i<pos; i++)
        if(atual->prox==NULL)
            break;
        else
            atual = atual->prox;

    atual->resposta = resultado;
}

void exibirResultados(Lista lis)
{
    No* atual = lis.inicio;

    printf("(");

    while(atual!=NULL)
    {
        if(atual->prox == NULL)
            printf("%s = %.2f", atual->info, atual->resposta);
        else
            printf("%s = %.2f; ", atual->info, atual->resposta);
        atual = atual->prox;
    }

    printf(")");
}

double pegarValor(Lista lis, int pos)
{
    int i;

    No* atual = lis.inicio;

    for(i=0; i<pos; i++)
        if(atual->prox==NULL)
            break;
        else
            atual = atual->prox;

    return atual->valor;
}

void printeLista(Lista lis)
{
    No* atual;
    atual = lis.inicio;

    while(atual!=NULL)
    {
        printf(atual->info);
        printf("%.2f", atual->valor);
        printf("%.2f", atual->resposta);
        atual = atual->prox;
    }

    printf("\nQtd variaveis: %i", lis.qtdVariaveis);
}

void deleteLista(Lista* lis)
{
    //printf("\n%s\n", lis->inicio->info);
    No* atual = lis->inicio;
    No* prox;

    while(atual!=NULL)
    {
        //printf("\n%s\n", atual->info);
        prox = atual->prox;

        if(atual->info!=NULL)
            free(atual->info);

        free(atual);
        atual = prox;
    }

    free(lis);
}

void printeMatriz(double** mat, int tam)
{
    int i, j;

    for(i=0; i<tam; i++)
    {
        printf("\n");

        for(j=0; j<=tam; j++)
            printf("%.2f  ", *(*(mat + i) + j));
    }
}

void zerarMatriz(double** mat, int tam)
{
    int i, j;

    for(i=0; i<tam; i++)
        for(j=0; j<=tam; j++)
            *(*(mat + i) + j) = 0;
}

void tiraEspacosEmBranco(char* string, int len)
{
    char* i = string;
    char* j = string;

    while(*j != 0)
    {
       *i = *j++;
       if(*i != ' ')
         i++;
    }

    *i = 0;
}

double oMenorComplementar(double** mat, int lin, int col, int total);
double cofator(double** mat, int lin, int col);
double laPlace(double** mat, int colunaDesejada);
double determinanteDosCoeficientes(double** mat, int tam);
double determinanteXn(double** mat, int col, int tam);
double somaDosCoeficientes(double** mat, int tam, int lin);
void terminar(FILE* arq, Lista* lis, double** mat, int tam, char* path, char* eqAtual);

void main()
{
    FILE * arquivo = (FILE*)malloc(sizeof(FILE));

    Lista lis;
    lis.inicio=NULL;
    lis.qtdVariaveis = 0;

    printf("Digite o nome do arquivo desejado: ");

    char* path = (char*)malloc(sizeof(char)*255);

    scanf("%s", path);

    arquivo = fopen(path, "r");

    if (arquivo!=NULL)
    {
        int qtdequacoes;
        int deu = fscanf(arquivo, "%i", &qtdequacoes);

        printf("Quantidade de equacoes: %i \n", qtdequacoes);
        double** matriz = (double**)(malloc(sizeof(double*)*(qtdequacoes+1)));

        int i;
        for(i=0; i<qtdequacoes; i++)
        {
            matriz[i] = (double*)malloc(sizeof(double)*(qtdequacoes+1));
        }

        zerarMatriz(matriz, qtdequacoes);

        int indAtualLinha =0;
        int indAtualColuna=0;

        boolean eraMaisMenos = false;

        i =0;

        char* eqAtual = (char*)malloc(sizeof(char)*255);
        char* teste;
        int qtdEquacoesLidas=qtdequacoes;
        fgets(eqAtual, 1024, arquivo);

        //LER AS EQUACOES

        while(i<qtdequacoes)
        {
            teste = fgets(eqAtual, 255, arquivo);

            if(teste==NULL)
            {
                printf("\n\n  -> %s esta(o) faltando equacoes!", path);
                exit(0);
            }

            i++;

            tiraEspacosEmBranco(eqAtual, strlen(eqAtual));

            char* igual = strchr(eqAtual, '=');

            int indiceDoIgual = (int)(igual - eqAtual);

            int index;

            for(index=0; index<strlen(eqAtual); index++)
            {
                if(isalpha(*(eqAtual+index))) //eh uma variavel
                {
                    char* aInserir = (char*)malloc(sizeof(char)*255);

                    int len = 0;

                    while(isalpha(*(eqAtual+index)))
                    {
                        *(aInserir + len) = *(eqAtual+index);

                        *(aInserir + len+1) = '\0';

                        len++;
                        index++;
                    }

                    index--;

                    if(pesquisar(&lis, aInserir)==true)
                    {
                        indAtualColuna = (int)pegarValor(lis, posicao(&lis, aInserir));
                    }
                    else
                    {
                        insira(&lis, aInserir);
                        insiraValor(&lis, lis.qtdVariaveis-1, lis.qtdVariaveis-1);
                        indAtualColuna = lis.qtdVariaveis-1;
                    }

                    double coef =1;

                    index-=len-1;

                    while((index-1>=0) && (*(eqAtual+index-1) == '*' || *(eqAtual+index-1) == '/' || isdigit(*(eqAtual+index-1)) || *(eqAtual+index-1) == '-'))
                    {
                        index--;

                        if((*(eqAtual+index) == '-') && (index-1>=0) && (*(eqAtual+index-1) != '*' || *(eqAtual+index-1) != '/'))
                            break;
                    }

                    while((strlen(eqAtual)>index) && (*(eqAtual+index) == '*' || *(eqAtual+index) == '/' || isdigit(*(eqAtual+index)) || isalpha(*(eqAtual+index)) || *(eqAtual+index) == '-'))
                    {
                        if(*(eqAtual+index) == '*')
                        {
                            if(isdigit(*(eqAtual+index+1)))
                                coef = coef * (*(eqAtual+index+1) - '0');

                            index++;
                        }
                        else
                        if(*(eqAtual+index) == '/')
                        {
                            if(isdigit(*(eqAtual+index+1)))
                                coef = coef / (*(eqAtual+index+1) - '0');

                            index++;
                        }
                        else
                        if(isdigit(*(eqAtual+index)))
                        {
                            double valor = *(eqAtual+index) - '0'; //precisa ser assim pra fazer string to int

                            index++;

                            while(isdigit(*(eqAtual+index)))
                            {
                                if(valor<0)
                                    valor = valor*10 - (*(eqAtual+index) - '0');
                                else
                                    valor = valor*10 + (*(eqAtual+index) - '0');
                                index++;
                            }

                            coef = coef*valor;

                            index--;
                        }
                        else
                        if(*(eqAtual+index) == '-')
                        {
                            coef = -coef;
                        }

                        if(isalpha(*(eqAtual+index)))
                        {
                            index++;
                            if(*(eqAtual+index)== '-' || *(eqAtual+index)== '=')
                            {
                                index--;
                                break;
                            }

                            index--;
                        }

                        index++;
                    }
                    *(*(matriz+indAtualLinha)+indAtualColuna) = coef;

                    indAtualColuna++;
                }
                else
                {
                    if(isdigit(*(eqAtual+index)))
                    {
                        int i=0;

                        double valor = *(eqAtual+index) - '0';

                        if(index>0 && (*(eqAtual+index-1)== '-'))
                            valor = -valor;

                        index++;


                        while(strlen(eqAtual)> index && isdigit(*(eqAtual+index)))
                        {
                             if(valor<0)
                                 valor = valor*10 - (*(eqAtual+index)- '0');
                             else
                                 valor = valor*10 + (*(eqAtual+index)- '0');

                             index++;
                        }

                        index--;

                        //ou seja, na verdade, esse continue aí só deve ser chamado se tiver uma variavel, se for coeficiente

                        //percorro pra ver se tera variavel

                        int indexantigo = index;

                        while(strlen(eqAtual)>index+1 && (!isalpha(*(eqAtual+index+1)) && (*(eqAtual+index+1) == '*' || *(eqAtual+index+1) == '/' || isdigit(*(eqAtual+index+1)) || *(eqAtual+index+1) == '-')))
                            index++;

                        if(isalpha(*(eqAtual+index+1)))
                            continue;

                        index=indexantigo;

                        index++;

                        while((strlen(eqAtual)>index) && (*(eqAtual+index) == '*' || *(eqAtual+index) == '/' || isdigit(*(eqAtual+index)) || *(eqAtual+index) == '-'))
                        {
                            if(*(eqAtual+index) == '*')
                            {
                                if(isdigit(*(eqAtual+index+1)))
                                    valor = valor * (*(eqAtual+index+1) - '0');

                                index++;

                            }
                            else
                            if(*(eqAtual+index) == '/')
                            {
                                if(isdigit(*(eqAtual+index+1)))
                                    valor = valor / (*(eqAtual+index+1) - '0');

                                index++;

                            }
                            else
                            if(isdigit(*(eqAtual+index)))
                            {
                                double va = *(eqAtual+index) - '0'; //precisa ser assim pra fazer string to int

                                index++;

                                while(isdigit(*(eqAtual+index)))
                                {
                                    if(va<0)
                                        va = va*10 - (*(eqAtual+index) - '0');
                                    else
                                        va = va*10 + (*(eqAtual+index) - '0');
                                    index++;
                                }

                                valor = va*valor;

                                index--;
                            }
                            else
                            if(*(eqAtual+index) == '-')
                            {
                                if(index>0 && (*(eqAtual+index-1) != '*' || *(eqAtual+index-1) != '/'))
                                    break;

                                valor = -valor;
                            }

                            index++;
                        }
                        index--;

                        if(index < indiceDoIgual) //esta antes do igual, devo trocar o sinal
                            valor = -valor;

                        *(*(matriz + indAtualLinha) + qtdequacoes) += valor;

                        continue;

                    }

                    if(*(eqAtual+index)=='=')
                        indAtualColuna = qtdequacoes;
                }
            }

            indAtualLinha++;
            indAtualColuna=0;
        }

        //FIM LER AS EQUACOES

        printeMatriz(matriz, qtdequacoes);

        if(lis.qtdVariaveis==1)
        {
            insiraResultado(&lis, *(*(matriz)+1), 0);
            exibirResultados(lis);
            exit(1);
        }

        double detCoeficientes = determinanteDosCoeficientes(matriz, qtdequacoes-1);

        //Agora, usando o teorema de Cramer, se D != 0, temos SPD e x1 = Dx1/D, x2 = Dx2/D, ..., xn = Dxn/D
        //Onde Dxi é o determinante da matriz que se obtem substituindo a coluna do xi pelos termos independentes
        //1<=i<=n

        //ja temos D. Vamos calcular Dxn...

        if(detCoeficientes==0) // temos SPI ou SI
        {
            escalonar(matriz, qtdequacoes);

            double somaCoef;

            int linha;
            for(linha=qtdequacoes-1; linha>0; linha--)
            {
                somaCoef = somaDosCoeficientes(matriz, qtdequacoes, linha+1);

                if(somaCoef != *(*(matriz+linha)+qtdequacoes) && somaCoef == 0)
                {
                    printf("\n\n-> Resposta: Sistema Impossivel!");
                    exit(1);
                }
            }

            //é SPI

            printf("\n\n-> Resposta: Sistema Possivel Indeterminado. Infinitos resultados!");
            exit(1);
        }

        double Dxn;

        for(i=0; i<lis.qtdVariaveis; i++)
        {
            Dxn = determinanteXn(matriz, i, lis.qtdVariaveis);

            insiraResultado(&lis, Dxn/detCoeficientes, i);
        }

        printf("\n\n-> Solucao: ");
        exibirResultados(lis);

        fclose(arquivo);

        terminar(&arquivo, &lis, matriz, qtdequacoes, path, eqAtual);
    }
    else
    {
        printf("O arquivo não exite!");
        exit(1);
    }
}

void terminar(FILE* arq, Lista* lis, double** mat, int tam, char* path, char* eqAtual)
{
    free(arq);

    deleteLista(&lis);

    free(lis);
    free(mat);

    int i;

    for(i =0; i < tam; i++)
        free(mat[i]);

    free(mat);

    free(path);

    free(eqAtual);
}

double somaDosCoeficientes(double** mat, int tam, int lin)
{
    int j;
    double soma=0;

    for(j=0; j<tam; j++)
        soma += *(*(mat+lin-1)+j);

    return soma;
}

void escalonar(double** mat, int tam)
{
    //n eh o numero de incognitas

    int n= tam;
    double mult;
    int k, i, j;

    for (k=0;k<n-1;k++)
        for (i=k+1; i<n;i++)
        {
            if((*(*(mat+k)+k)) == 0)
                continue;

            mult=-1* ((*(*(mat+i)+k))/ (*(*(mat+k)+k))); //NEGATIVAÇÃO (-1 * MAT[2][1]) / MAT[1][1]

            for (j=0;j<n+1;j++)
            {
                *(*(mat+i)+j) = ((*(*(mat+k)+j))*mult)+ (*(*(mat+i)+j));
            }
            /*  MAT[1][1]*NEGATIVAÇÃO + MAT[2][1] TRANSFORMANDO EM GAUSS */
        }
}

double determinanteXn(double** mat, int col, int tam)
{
    double** nova = (double**)(malloc(sizeof(double*)* tam));

    int i,j;

    for(i=0; i<tam; i++)
        *(nova+i) = (double*)malloc(sizeof(double)*(tam));

    for(i =0; i<tam; i++)
        for(j =0; j<tam; j++)
            *(*(nova+i)+j) = *(*(mat+i)+j);


    //agr, na coluna col, colocar os termos independentes e formar a matriz

    for(i=0; i<tam; i++) //percorrerlinha a linha
        *(*(nova+i)+col) = *(*(mat+i)+tam);

    return laPlace(nova, tam-1);

}

double determinanteDosCoeficientes(double** mat, int tam)
{
    return laPlace(mat, tam);
}

double laPlace(double** mat, int colunaDesejada)
{
    //soma dos produtos dos elementos de uma fila por seus respectivos cofatores

    if(colunaDesejada ==1) //se a ultima coluna for a seguda, entao eh facil calcular o dterminante
        return ((*(*(mat)) * (*(*(mat+1)+1))) - (*(*(mat)+1) * (*(*(mat+1)))));


    Lista nova;
    nova.inicio=NULL;
    nova.qtdVariaveis = 0;

    int linAtual;

    char* soPraInserir = "teste";

    for(linAtual=0; linAtual<=colunaDesejada; linAtual++)
    {
        insira(&nova, soPraInserir);
        insiraValor(&nova, *(*(mat+linAtual)+colunaDesejada), linAtual);
    }

    //tenho uma lista pronta com os elementos da coluna
    int i;
    double determinante=0;

    for(i=0; i<nova.qtdVariaveis; i++)
        determinante += pegarValor(nova, i) * cofator(mat, i, colunaDesejada);

    return determinante;
}

double cofator(double** mat, int lin, int col)
{
    return pow(-1, lin+col) * oMenorComplementar(mat, lin, col, col);
}

void printeMat(double** mat, int tam)
{
    int i, j;

    for(i=0; i<tam; i++)
    {
        for(j=0; j<tam; j++)
            printf("%.2f  ", *(*(mat + i) + j));

        printf("\n");
    }
}

double oMenorComplementar(double** mat, int lin, int col, int total)
{
    //eh o determinante da matriz que se obtem eliminando a linha i e a coluna j de uma matriz dada

    //vou dar um return laPlace(de uma nova matriz sem a ultima linha e ultima coluna)

    double** nova = (double**)(malloc(sizeof(double*)* total));
    int i;
    int qtdLinOutra=0;

    for(i=0; i<total; i++)
        *(nova+i) = (double*)malloc(sizeof(double)*(total));

    int j;
    int qtdColOutra;

    for(i =0; i<total; i++)
    {
        qtdColOutra=0;
        if(i==lin)
            qtdLinOutra++;

        if(qtdLinOutra>total)
            break;

        for(j =0; j<total; j++)
        {
            if(j==col)
                qtdColOutra++;

            if(qtdColOutra>total)
                break;

            *(*(nova+i)+j) = *(*(mat+qtdLinOutra)+qtdColOutra);

            qtdColOutra++;
        }
        qtdLinOutra++;
    }

    //matriz montada

    if(total == 2)
        return ((*(*(nova)) * (*(*(nova+1)+1))) - (*(*(nova)+1) * (*(*(nova+1)))));

    return laPlace(nova, total-1);
}
