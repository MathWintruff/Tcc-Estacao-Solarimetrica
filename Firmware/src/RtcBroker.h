#include <Arduino.h>
#include <time.h>
#include <NTPClient.h>


NTPClient ntp(udp, "a.st1.ntp.br", -3 * 3600, 60000);//Cria um objeto "NTP" com as configurações.utilizada no Brasil
struct tm data;//Cria a estrutura que contem as informacoes da data.
int hora;
char data_formatada[64];
int ATUALIZAR_DH;
String hora_ntp;

void NtpStart(){
    ntp.begin();
    ntp.forceUpdate();  
}

String relogio_ntp(int retorno)
{
  //Esta condição será chamada uma unica fez para atualizar a data e hora com NTP
  if (retorno == 0)
  {
    Serial.print(" Atualizando data e hora...");
    hora = ntp.getEpochTime(); //Atualizar data e hora usando NTP online
    Serial.print(" NTP Unix: ");
    Serial.println(hora);
    timeval tv;//Cria a estrutura temporaria para funcao abaixo.
    tv.tv_sec = hora;//Atribui minha data atual. Voce pode usar o NTP para isso ou o site citado no artigo!
    settimeofday(&tv, NULL);//Configura o RTC para manter a data atribuida atualizada.
    time_t tt = time(NULL);//Obtem o tempo atual em segundos. Utilize isso sempre que precisar obter o tempo atual
    data = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
    strftime(data_formatada, 64, "%d/%m/%Y %H:%M:%S", &data);//Cria uma String formatada da estrutura "data"
    Serial.print(" Data e hora atualizada:");
    Serial.println(data_formatada);
  }

  if (retorno == 1)
  {
    time_t tt = time(NULL);//Obtem o tempo atual em segundos. Utilize isso sempre que precisar obter o tempo atual
    data = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
    strftime(data_formatada, 64, "%d/%m/%Y %H:%M:%S", &data);//Cria uma String formatada da estrutura "data"
    hora_ntp   = data_formatada;
  }
  if (retorno == 2)
  {
    time_t tt = time(NULL);//Obtem o tempo atual em segundos. Utilize isso sempre que precisar obter o tempo atual
    data = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
    strftime(data_formatada, 64, "%d/%m/%Y", &data);//Cria uma String formatada da estrutura "data"
    hora_ntp = data_formatada;
  }
  if (retorno == 3)
  {
    time_t tt = time(NULL);//Obtem o tempo atual em segundos. Utilize isso sempre que precisar obter o tempo atual
    data = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
    strftime(data_formatada, 64, "%H%M", &data);//Cria uma String formatada da estrutura "data"
    hora_ntp = data_formatada;

  }
  return hora_ntp;

}