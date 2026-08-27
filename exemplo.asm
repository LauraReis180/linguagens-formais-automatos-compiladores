# Programa de teste do pre-processador

.data

msg:    .asciiz "Resultado # obtido"     # mensagem
valor:      .word 10

.text

main:

    li      $t0, 5       # primeiro valor

    li   $t1, 10         # segundo valor

    add     $t2,   $t0,   $t1