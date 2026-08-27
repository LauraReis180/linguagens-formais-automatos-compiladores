#include "preprocessador.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAM_LINHA 4096

/*
 * Remove comentarios, normaliza espacos e preserva
 * o conteudo das strings.
 */
static void processar_linha(const char *linha, char *resultado)
{
    int i = 0;
    int j = 0;
    int dentro_string = 0;
    int escape = 0;
    int espaco_pendente = 0;

    while (linha[i] != '\0')
    {
        char c = linha[i];

        /*
         * Dentro de uma string:
         * copia tudo exatamente como esta.
         */
        if (dentro_string)
        {
            resultado[j++] = c;

            if (escape)
            {
                escape = 0;
            }
            else if (c == '\\')
            {
                escape = 1;
            }
            else if (c == '"')
            {
                dentro_string = 0;
            }

            i++;
            continue;
        }

        /*
         * Fora de uma string:
         * # inicia comentario.
         */
        if (c == '#')
        {
            break;
        }

        /*
         * Aspas iniciam uma string.
         */
        if (c == '"')
        {
            /*
             * Se havia espacos antes das aspas,
             * coloca apenas um.
             */
            if (espaco_pendente && j > 0)
            {
                resultado[j++] = ' ';
            }

            espaco_pendente = 0;
            dentro_string = 1;
            resultado[j++] = c;

            i++;
            continue;
        }

        /*
         * Tabulacoes, espacos e quebras de linha
         * sao tratados como espacos.
         */
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
        {
            if (j > 0)
            {
                espaco_pendente = 1;
            }

            i++;
            continue;
        }

        /*
         * Se havia varios espacos, coloca somente um.
         */
        if (espaco_pendente)
        {
            resultado[j++] = ' ';
            espaco_pendente = 0;
        }

        resultado[j++] = c;
        i++;
    }

    /*
     * Remove o espaco que eventualmente ficou no final.
     */
    while (j > 0 && resultado[j - 1] == ' ')
    {
        j--;
    }

    resultado[j] = '\0';
}

int preprocessar(FILE *entrada, FILE *saida)
{
    char linha[TAM_LINHA];
    char resultado[TAM_LINHA];

    while (fgets(linha, TAM_LINHA, entrada) != NULL)
    {
        processar_linha(linha, resultado);

        /*
         * Linhas vazias nao sao escritas.
         */
        if (strlen(resultado) == 0)
        {
            continue;
        }

        fprintf(saida, "%s\n", resultado);
    }

    if (ferror(entrada))
    {
        return 0;
    }

    return 1;
}