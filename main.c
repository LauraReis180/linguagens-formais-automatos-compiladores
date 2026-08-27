#include <stdio.h>
#include "preprocessador.h"

int main(int argc, char *argv[])
{
    FILE *entrada;
    FILE *saida;

    /*
     * O programa precisa receber:
     * 1 - arquivo de entrada
     * 2 - arquivo de saida
     */
    if (argc != 3)
    {
        printf("Uso: %s <arquivo_entrada.asm> <arquivo_saida.pre>\n", argv[0]);
        return 1;
    }

    /*
     * Abre o arquivo Assembly para leitura.
     */
    entrada = fopen(argv[1], "r");

    if (entrada == NULL)
    {
        printf("Erro: nao foi possivel abrir o arquivo de entrada '%s'.\n", argv[1]);
        return 1;
    }

    /*
     * Cria/abre o arquivo de saida.
     */
    saida = fopen(argv[2], "w");

    if (saida == NULL)
    {
        printf("Erro: nao foi possivel criar o arquivo de saida '%s'.\n", argv[2]);
        fclose(entrada);
        return 1;
    }

    /*
     * Executa o pre-processador.
     */
    if (!preprocessar(entrada, saida))
    {
        printf("Erro durante o pre-processamento.\n");

        fclose(entrada);
        fclose(saida);

        return 1;
    }

    fclose(entrada);
    fclose(saida);

    printf("Pre-processamento concluido com sucesso.\n");

    return 0;
}