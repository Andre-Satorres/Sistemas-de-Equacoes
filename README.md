# Sistemas de Equacoes
## Trabalho de Tópicos em Orientação a Objetos em Linguagem C (4o Período / Informática Matutino)

O propósito deste trabalho é escrever um programa em C para resolver sistemas de equações lineares com qualquer quantidade de equações pelo método de Gauss-Seidel. Para atingir este objetivo, explico abaixo como funciona o Método de Gaus Seidel Para resolver Sistemas de Equações Lineares:

#### 1.	Considere o seguinte sistema de equações:
```bash
3y + 2z = 28
4x + 2z = 24
2x + 3y = 16
```

#### 2.	Extraia do sistema os coeficientes e, com eles, monte uma matriz (cuide também de guardar numa lista lidada os nomes das variáveis para, ao final do processo, dar o valor obtido para cada uma):
```bash
0	3	2	28
4	0	2	24
2	3	0	16
```

#### 3.	Podemos considerar que a parte da matriz que é formada pelos coeficientes multiplicadores das variáveis é quadrada. Troque a ordem das linhas e/ou dessas colunas (não mexer na última) de forma que não existam zeros na diagonal principal (dar o sistema de equações como sem solução, caso não consiga eliminar os zeros da diagonal principal):

```bash
4	0	2	24
2	3	0	16
0	3	2	28
```

#### 4.	Torne 1 o 1º elemento da diagonal principal, dividindo toda a 1ª linha (4 0 2 24) pelo elemento a ser tornado 1 (4), passando a ter (1 0 1/2 6) na 1ª linha:

```bash
1	0	1/2	6
2	3	0	16
0	3	2	28
```

#### 5.	AGORA O OBJETIVO É TORNAR 0, TODOS OS DEMAIS ELEMENTOS DA COLUNA 1;

Como na posição 3,1 já temos 0, não faremos nada com a linha 3 (nela, nada muda);

Na posição 2,1 temos 2; para torna-lo 0, tomamos a linha onde acabamos de implantar 1 (1 0 1/2 6), multiplicamos todos os seus elementos por -2 (que é o número que desejamos “zerar” com o sinal trocado) e obtemos ( 2 0 -1 -12); somamos então estes valores aos valores da linha onde desejamos implantar 0 (2 3 0 16), passamos a ter (0 3 -1 4) na 2ª linha:

```bash
1	0	1/2	6
0	3	-1	4
0	3	2	28
```

#### 6.	Tornando 1 o 2º elemento da diagonal principal, dividindo toda a 2ª linha (0 3 -1 4) pelo elemento a ser tornado 1 (3), passando a ter (0 1 -1/3 4/3) na 2ª linha:

```bash
1	0	1/2	6
0	1	-1/3	4/3
0	3	2	28
```

#### 7.	AGORA O OBJETIVO É TORNAR 0, TODOS OS DEMAIS ELEMENTOS DA COLUNA 2;

Como na posição 1,2 já temos 0, não faremos nada com a linha 1 (nela, nada muda);

Na posição 3,2 temos 3; para torna-lo 0, tomamos a linha onde acabamos de implantar 1 (0 1 -1/3 4/3), multiplicamos todos os seus elementos por -3 (que é o número que desejamos “zerar” com o sinal trocado) e obtemos (0 -3 1 -4); somamos então estes valores aos valores da linha onde desejamos implantar 0 (0 3 2 28), passamos a ter (0 0 3 24) na 3ª linha:

```bash
1	0	1/2	6
0	1	-1/3	4/3
0	0	3	24
```

#### 8.	Tornando 1 o 3º elemento da diagonal principal, dividindo toda a 3ª linha (0 0 3 24) pelo elemento a ser tornado 1 (3) , passando a ter (0 0 1 8) na 3ª linha:

```bash
1	0	1/2	6
0	1	-1/3	4/3
0	0	1	8
```

#### 9.	AGORA O OBJETIVO É TORNAR 0, TODOS OS DEMAIS ELEMENTOS DA COLUNA 2;

Na posição 1,3 temos 1/2; para torna-lo 0, tomamos a linha onde acabamos de implantar 1 (0 0 1 8), multiplicamos todos os seus elementos por -1/2 (que é o número que desejamos “zerar” com o sinal trocado) e obtemos (0 0 -1/2 -4); somamos então estes valores aos valores da linha onde desejamos implantar 0 (1 0 1/2 6), passamos a ter (1 0 0 2) na 1ª linha:

```bash
1	0	0	2
0	1	-1/3	4/3
0	0	1	8
```

#### 10.	Na posição 2,3 temos -1/3; para torna-lo 0, tomamos a linha onde acabamos de implantar 1 (0 0 1 8), multiplicamos todos os seus elementos por 1/3 (que é o número que desejamos “zerar” com o sinal trocado) e obtemos (0 0 1/3 8/3); somamos então estes valores aos valores da linha onde desejamos implantar 0 (1 0 -1/3 4/3), passamos a ter (1 0 0 4) na 2ª linha:

```bash
1	0	0	2
0	1	0	4
0	0	1	8
```

#### 11.	Os valores presentes na coluna 4, ou seja (2 4 8) são a solução do sistema de equações linear; assim sendo, x=2, y=4 e z=8.




### Observações Finais:

#### 1.	Sugere-se que, para ser mais fácil de testar, seu trabalho leia os dados de um arquivo texto.

Assim, se você pretendesse testar seu programa com o exemplo apresentado acima voce poderia usar o Bloco de Notas para criar um arquivo com o seguinte formato:
```bash
3
3y + 2z = 28
4x + 2z = 24
2x + 3y = 16
```

O número 3 que inicia o arquivo indicaria que o arquivo contem os coeficientes de um sistema de equações lineares com 3 equações.

Ao executar seu programa ele poderia ler os coeficientes do arquivo e com eles formar a matriz inicial para a plicação do Método de Gauss-Seidel que seria a matriz indicada abaixo:

```bash
0	3	2	28
4	0	2	24
2	3	0	16
```

Cabe-me lembrar que o trabalho não deve se limitar a resolver sistemas de equações lineares com 3 equações, sendo exigido que seja capaz de resolver sistemas com qualquer quantidade de equações.
Naturalmente os valores dos coeficientes deve ser armazenado numa matriz, mas cuide para que a mesma seja alocada dinamicamente e de jamais acessar suas posições via indexação (usando colchetes).
Cuide ainda para usar listas ligadas para realizar operações intermediárias sobre linhas e colunas da matriz.
