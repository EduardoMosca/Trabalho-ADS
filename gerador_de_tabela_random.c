#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "xlsxwriter.h"

typedef struct Fila {
  int tempo_ultima_chegada;
  int tempo_chegada_relogio;
  int tempo_servico;
  int tempo_inicio_servico;
  int tempo_cliente_fila;
  int tempo_final_atendimento;
  int tempo_cliente_banco;
  int tempo_livre_caixa;
} Fila;

int tempo_rand_1() {
  int numero = 0;
  int Aleatorio = rand() % 20 + 1;
  if (Aleatorio >= 1 && Aleatorio <= 7) numero = 10;
  if (Aleatorio >= 8 && Aleatorio <= 15) numero = 12;
  if (Aleatorio >= 16 && Aleatorio <= 20) numero = 14;
  return numero;
}

int tempo_rand_2() {
  int numero = 0;
  int Aleatorio = rand() % 10 + 1;
  if (Aleatorio >= 1 && Aleatorio <= 2) numero = 11;
  if (Aleatorio >= 3 && Aleatorio <= 5) numero = 9;
  if (Aleatorio >= 6 && Aleatorio <= 10) numero = 10;
  return numero;
}

Fila *preenche_fila(Fila fila[], int num) {
  int tempo = tempo_rand_1(), x, y;
  for(int i = 0; i < num; i++) {
    fila[i].tempo_ultima_chegada = tempo_rand_1();
    fila[i].tempo_servico = tempo_rand_2();
  }
  for(int i = 0; i < num; i++) {
    if(i==0) {
      x = fila[i].tempo_ultima_chegada;
    }
    else {
      x = x + fila[i].tempo_ultima_chegada;
    }
    fila[i].tempo_chegada_relogio = x;
  }
  for(int i = 0; i < num; i++) {
    if(i == 0) fila[i].tempo_cliente_fila = 0;
    else if(i != 0 && fila[i - 1].tempo_final_atendimento > fila[i].tempo_chegada_relogio) fila[i].tempo_cliente_fila = 1;
    else fila[i].tempo_cliente_fila = 0;
    fila[i].tempo_inicio_servico = fila[i].tempo_chegada_relogio + fila[i].tempo_cliente_fila;
    fila[i].tempo_final_atendimento = fila[i].tempo_inicio_servico + fila[i].tempo_servico;
    fila[i].tempo_cliente_banco = fila[i].tempo_servico + fila[i].tempo_cliente_fila;
    if(i == 0) fila[i].tempo_livre_caixa = fila[i].tempo_inicio_servico;
    else fila[i].tempo_livre_caixa = fila[i].tempo_inicio_servico - fila[i-1].tempo_final_atendimento;
  }
  return fila;
}

int main() { 
  srand(time(NULL));
  Fila *fila = (Fila *)(malloc(sizeof(Fila) * 20));
  fila = preenche_fila(fila, 20);
  lxw_workbook  *workbook  = workbook_new("super_tabela.xlsx");
  lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
  worksheet_write_string(worksheet, 0, 0, "Tempo desde a última chegada", NULL);
  worksheet_write_string(worksheet, 0, 1, "Tempo de chegada no relógio", NULL);
  worksheet_write_string(worksheet, 0, 2, "Tempo de serviço ou atendimento", NULL);
  worksheet_write_string(worksheet, 0, 3, "Tempo de início do serviço", NULL);
  worksheet_write_string(worksheet, 0, 4, "Tempo do cliente na fila do banco", NULL);
  worksheet_write_string(worksheet, 0, 5, "Tempo final do atendimento no relógio", NULL);
  worksheet_write_string(worksheet, 0, 6, "Tempo do cliente no Banco",  NULL);
  worksheet_write_string(worksheet, 0, 7, "Tempo livre ou ocupado do Caixa do banco", NULL);
  for(int i = 1; i < 21; i++) {
    worksheet_write_number(worksheet, i, 0, fila[i - 1].tempo_ultima_chegada, NULL);
  }
  for(int i = 1; i < 21; i++) {
    worksheet_write_number(worksheet, i, 1, fila[i - 1].tempo_chegada_relogio, NULL);
  }
  for(int i = 1; i < 21; i++) {
    worksheet_write_number(worksheet, i, 2, fila[i - 1].tempo_servico, NULL);
  }
  for(int i = 1; i < 21; i++) {
    worksheet_write_number(worksheet, i, 3, fila[i - 1].tempo_inicio_servico, NULL);
  }
  for(int i = 1; i < 21; i++) {
    worksheet_write_number(worksheet, i, 4, fila[i - 1].tempo_cliente_fila, NULL);
  }
  for(int i = 1; i < 21; i++) {
    worksheet_write_number(worksheet, i, 5, fila[i - 1].tempo_final_atendimento, NULL);
  }
  for(int i = 1; i < 21; i++) {
    worksheet_write_number(worksheet, i, 6, fila[i - 1].tempo_cliente_banco, NULL);
  }
  for(int i = 1; i < 21; i++) {
    worksheet_write_number(worksheet, i, 7, fila[i - 1].tempo_livre_caixa, NULL);
  }
  workbook_close(workbook);
  
  return 0;
}