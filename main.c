#include <stdio.h>
#include<stdlib.h>

double toplama_cikarma();
double carpma_bolme();
double kontrol();

const char *input;
int pos = 0;

char get_char(){
  return input[pos++];
}
void put_char(){
  pos--;
}

int parantez_kontrolu(){
  int acik_parantez = 0;
  int kapali_parantez = 0;
  char ch;

  while((ch = get_char()) != '\0'){
    if(ch == '('){
      acik_parantez++;
    }
    else if(ch == ')'){
      kapali_parantez++;
    }
  }

  if(acik_parantez == kapali_parantez){
    return 1;
  }
  else{
    return 0;
    
  }
  
}

double parse_number(){
  double result = 0.0;
  char ch = get_char();
  int decimal = 0;
  double decimal_divisor = 1.0;



  while(ch != '\0' && ch<='9' || ch ==','){
    if(ch == ','){
      ch = '.';
      decimal = 1;
    }else {
      if(decimal){
        decimal_divisor *= 10.0;
        result = result + (ch-'0')/decimal_divisor;
      }else{
        result = result * 10.0 + (ch-'0');
      }
    }
    ch = get_char();
  }
  put_char();
  return result;
}

double toplama_cikarma(){
  double result = carpma_bolme();

  while(1){
    char op = getchar();
    if(op == '+'){
      result = result + carpma_bolme();
      
    }else if(op == '-'){
      result = result - carpma_bolme();
      
    }else{
      put_char();
      break;
    }
  }
  return result;
}

double carpma_bolme(){
  double result = kontrol();

  while(1){
    char op = getchar();
    if(op == '*'){
      result = result * kontrol();

    }else if(op == '/'){
      double sonuc = kontrol();
      if(sonuc == 0){
        printf("Hata: Sıfıra bölme hatası!\n");
        exit(1);
      }
      result = result / sonuc;
    }else{
      put_char();
      break;
    }
  }
  return result;
}

double kontrol(){
  char ch = get_char();
  if(ch == '('){
    double result = toplama_cikarma();
    char next_char = get_char();
    if(next_char != ')'){
     put_char();
     printf("Yanlış söz dizimi!\n");
      exit(1);
      
    }
    return result;
  }else if((ch >='0' && ch<='9') || ch == ','){
    put_char();
    return parse_number();
  }else
    put_char();
  printf("Yanlış söz dizimi!\n");
  exit(1);
  }


int main(){
  char islem[100];
  printf("İşlem giriniz: ");
  fgets(islem, sizeof(islem), stdin);
  input=islem;

  if(!parantez_kontrolu()){
    printf("Yanlış söz dizimi");
    return 1;
    
  }
  double result = toplama_cikarma();
  char next_char = get_char();
  if(next_char != '\0' && next_char != '\n' && next_char != ')'){
    printf("Yanlış söz dizimi");
  }else{
    printf("Doğru söz dizimi");
  }
  
  return 0;
}
