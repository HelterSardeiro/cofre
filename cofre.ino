//biblioteca responsável pela comunicação com o display LCD
#include <LiquidCrystal.h>
//biblioteca responsável por capturar a tecla que foi pressionada no teclado
#include <Keypad.h>
#define resetsenha A0
#define solenoide 2
#define camera 3
#include<string.h>
const byte qtdLinhas = 4; //QUANTIDADE DE LINHAS DO TECLADO
const byte qtdColunas = 3; //QUANTIDADE DE COLUNAS DO TECLADO
 
//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
const byte PinosqtdLinhas[qtdLinhas] = {A1, A2, A3, A4}; //PINOS UTILIZADOS PELAS LINHAS
const byte PinosqtdColunas[qtdColunas] = {4, 5, 6}; //PINOS UTILIZADOS PELAS COLUNAS
//INICIALIZAÇÃO DO TECLADO
Keypad customKeypad = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas); 
 
LiquidCrystal lcd(12, 11, 7, 8, 9, 10);
//Senhas
String SENHA_MESTRE = "123456";
String SENHA_ESPERADA = "";
String SENHA_DIGITADA = "";
String CONFIRMA = "";
//int ledverde = 12, ledverm = 11; //portas dos leds


//função responsável por imprimir na tela a mensagem de inicio
void inicio(){
  lcd.print(" APERTE # P/");
  lcd.setCursor(1, 1);
  lcd.print("Cadastrar Senha");
                               
  delay(1900);
}


//Função para cadastro
String senhasimb = "*";


void confirmar(char customKey){
  //Cadastro de senha
  int control = 0,control2 = 0; //variaveis de controle
   do{

        if(customKey == '#'){
                        lcd.clear();
                        lcd.print("CONFIRMAR SENHA:");
                        lcd.setCursor(0,1);
          control = 1;
        } else {
             //Limpa a tela
              lcd.clear();
             lcd.print("Aperte#");
        }
     } while(control == 0);
     int condig = 0; //controle de digitos 
  while(control2 == 0){ //Ler a senha até o usuário clica em *
    lcd.cursor();
    lcd.blink();
     //captura a tecla pressionada do teclado
     customKey = 'O';
              do{
                
                     //captura a tecla pressionada do teclado
                        customKey = customKeypad.getKey();
                        
                   } while(customKey == 'O'); 
      //caso alguma tecla foi pressionada
                        
            if (customKey){
                Serial.println(customKey);
              
                  //caso alguma das teclas imprimíveis foi pressionada
                  //apagar ----------------------------------------------------
                  if(customKey == '*'){
                    CONFIRMA.remove((CONFIRMA.length() - 1), 1);
                    senhasimb.remove((senhasimb.length() - 1), 1);
                    senhasimb.remove((senhasimb.length() - 2), 1);
                    condig --;
                    goto irprint;                    
                  }
                  //apagar ----------------------------------------------------
                  if(customKey == '0' || customKey == '1' || customKey == '2' || customKey == '3' || customKey == '4' || customKey == '5' || customKey == '6' || customKey == '7' || customKey == '8' || customKey == '9'){
                        //concatena o novo símbolo a senha que estamos digitando
                        condig ++;
                        CONFIRMA+=customKey;
                        Serial.println(CONFIRMA);
                        //imprime na tela 
                        
                        lcd.print(customKey);
                        delay(500);
                        irprint:
                        lcd.clear();
                        lcd.print("CONFIRMAR SENHA:");
                        lcd.setCursor(0,1);
                        if(CONFIRMA.length() != 0){
                          lcd.print(senhasimb);
                          senhasimb +="*";
                          }
    
                        if(condig == 6){
                          control2 = 1;
                          lcd.clear(); 
                          condig = 0;  
                        }
                  } 
           } 
  }
 }


void cadastro(){
  char customKey;
  //Cadastro de senha
  int control = 0,control2 = 0; //variaveis de controle
   do{
    
              do{
               
           //captura a tecla pressionada do teclado
              customKey = customKeypad.getKey();
                        
         } while(customKey != '#');

        if(customKey == '#'){
                        lcd.clear();
                        lcd.print("DIGITE A SENHA 6");
                        lcd.setCursor(0,1);
                        lcd.print("DIGITOS:");
                        
          control = 1;
        } else {
             //Limpa a tela
              lcd.clear();
             lcd.print("Aperte#");
        }
     } while(control == 0);
     int condig = 0; //controle de digitos 
  while(control2 == 0){ //Ler a senha até o usuário clica em *
    lcd.cursor();
    lcd.blink();
     //captura a tecla pressionada do teclado
     customKey = 'O';
              do{
                
                     //captura a tecla pressionada do teclado
                    customKey = customKeypad.getKey();
                        
                   } while(customKey == 'O'); 
      //caso alguma tecla foi pressionada
                        
            if (customKey){
                Serial.println(customKey);
              
                  //caso alguma das teclas imprimíveis foi pressionada
                  //apagar ----------------------------------------------------
                  if(customKey == '*'){
                    
                    SENHA_ESPERADA.remove((SENHA_ESPERADA.length() - 1), 1);
                    
                    senhasimb.remove((senhasimb.length() - 1), 1);
                    senhasimb.remove((senhasimb.length() - 2), 1);

                    condig --; 
                
                    goto irprint;  
                    
                  }
                  //apagar ----------------------------------------------------
                  if(customKey == '0' || customKey == '1' || customKey == '2' || customKey == '3' || customKey == '4' || customKey == '5' || customKey == '6' || customKey == '7' || customKey == '8' || customKey == '9'){
                        //concatena o novo símbolo a senha que estamos digitando
                        condig ++;
                        SENHA_ESPERADA+=customKey; 
                        //imprime na tela 
                        
                        lcd.print(customKey);
                        delay(500);
                        irprint:
                        lcd.clear();
                        lcd.print("DIGITE A SENHA 6");
                        lcd.setCursor(0,1);
                        lcd.print("DIGITOS:");
                          if(SENHA_ESPERADA.length() != 0){
                          lcd.print(senhasimb);
                          senhasimb +="*";
                          }
                   
                          
               
                        
                        
                             
                        if(condig == 6){
                          control2 = 1;
                          lcd.clear(); 
                          condig = 0;  
                        }
                  } 
           } 
  }
 } 



int INIT = 0;
void setup(){

  Serial.begin(2400);
 // pinMode(ledverde,OUTPUT);
 // pinMode(ledverm,OUTPUT);
      pinMode(camera,OUTPUT);
      pinMode(solenoide,OUTPUT);
     digitalWrite(solenoide,LOW); //abre a porta
  pinMode(resetsenha, INPUT_PULLUP);
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  do{
    senhafraca:
    reinicia:
    SENHA_ESPERADA = "";
    CONFIRMA = "";
  inicio();

  cadastro();
  if(SENHA_ESPERADA == "123456" || SENHA_ESPERADA == "456789" || SENHA_ESPERADA == "987654" || 
    SENHA_ESPERADA == "654321" || SENHA_ESPERADA == "987654" || SENHA_ESPERADA == "111111"
     || SENHA_ESPERADA == "222222" || SENHA_ESPERADA == "333333" || SENHA_ESPERADA == "444444" || SENHA_ESPERADA == "555555"
      || SENHA_ESPERADA == "666666" || SENHA_ESPERADA == "777777" || SENHA_ESPERADA == "888888" || SENHA_ESPERADA == "999999" || SENHA_ESPERADA == "000000"
      /*ACRESCENTE MAIS SENHA FACEIS FUTURAMENTE AQUI!! SEGUINDO O PADRÃO {-> // CONDIÇÃO // <-} */){
      lcd.print("SENHA FRACA");
      lcd.setCursor(0,1);
      lcd.print("CADASTRE DE NOVO");
      delay(2000);
      lcd.clear();
      senhasimb="*";
      goto senhafraca;
    }
  senhasimb = "*";
  confirmar('#');
  senhasimb = "*";
  if(SENHA_ESPERADA == CONFIRMA){
    
    CONFIRMA = "";
    int j = 0;
    for(j = 0; j < 2; j++){
      lcd.print("ABRA A GAVETA E");
      lcd.setCursor(0,1);
      lcd.print("COLOQUE O SEU");
      delay(1500);
      lcd.clear();
      lcd.print("CELULAR PARA");
      lcd.setCursor(0,1);
      lcd.print("CARREGAR");
      delay(1500);
      lcd.clear();
    }
    lcd.print("FECHE A GAVETA");
    int tempgav = 0;
    while(1){
      if(digitalRead(resetsenha) == 0){ 
        lcd.clear();     
        break;
      }
      delay(50);
      tempgav ++;
      if(tempgav == 600){
        lcd.clear();
        goto reinicia;
      }
    }
    
    break;
  } else{
    lcd.print("SENHAS DIFERENTE");
    lcd.setCursor(0,1);
    lcd.print("DIGITE NOVAMENTE");
    delay(2800);
    lcd.clear();
  }
  }while(SENHA_ESPERADA != CONFIRMA);

}

//armazena erro de senha
  int conterro = 0;
//armazena erro de senha
int loopcp = 0;
void loop(){
  //init
 init: 
 if(INIT != 0){
  loopcp = 0;
        do{
         senhafraca: 
         reinicia:
         SENHA_ESPERADA = "";
          CONFIRMA = "";
        inicio();
      
        cadastro();
        if(SENHA_ESPERADA == "123456" || SENHA_ESPERADA == "456789" || SENHA_ESPERADA == "987654" || 
    SENHA_ESPERADA == "654321" || SENHA_ESPERADA == "987654" || SENHA_ESPERADA == "111111"
     || SENHA_ESPERADA == "222222" || SENHA_ESPERADA == "333333" || SENHA_ESPERADA == "444444" || SENHA_ESPERADA == "555555"
      || SENHA_ESPERADA == "666666" || SENHA_ESPERADA == "777777" || SENHA_ESPERADA == "888888" || SENHA_ESPERADA == "999999" || SENHA_ESPERADA == "000000"
      /*ACRESCENTE MAIS SENHA FACEIS FUTURAMENTE AQUI!! SEGUINDO O PADRÃO {-> // CONDIÇÃO // <-} */){
      lcd.print("SENHA FRACA");
      lcd.setCursor(0,1);
      lcd.print("CADASTRE DE NOVO");
      delay(2000);
      lcd.clear();
      senhasimb="*";
      goto senhafraca;
    }
        senhasimb = "*";
        confirmar('#');
        senhasimb = "*";
        if(SENHA_ESPERADA == CONFIRMA){
        
          CONFIRMA = "";
          int j = 0;
          for(j = 0; j < 2; j++){
            lcd.print("ABRA A GAVETA E");
            lcd.setCursor(0,1);
            lcd.print("COLOQUE O SEU");
            delay(1500);
            lcd.clear();
            lcd.print("CELULAR PARA");
            lcd.setCursor(0,1);
            lcd.print("CARREGAR");
            delay(1500);
            lcd.clear();
          }
          lcd.print("FECHE A GAVETA");
          int tempgav = 0;
          while(1){
            if(digitalRead(resetsenha) == 0){
              lcd.clear();
              goto irfechar;
              
            }
            delay(50);
            tempgav ++;
            if(tempgav == 600){
              lcd.clear();
              goto reinicia;
            }
          }
          
          break;
        } else{
          lcd.print("SENHAS DIFERENTE");
          lcd.setCursor(0,1);
          lcd.print("DIGITE NOVAMENTE");
         //lcd.print(SENHA_ESPERADA);
       //  lcd.setCursor(0,1);
       //  lcd.print(CONFIRMA);
          delay(2800);
          lcd.clear();
        }
        }while(SENHA_ESPERADA != CONFIRMA);
  }

  //init
        //captura a tecla pressionada do teclado
      irfechar:
      if (loopcp == 0){
          INIT = 0;
          lcd.print("DIGITE P/ FECHAR");
          lcd.setCursor(0,1);
          loopcp ++;
      }
      int tamanho = SENHA_DIGITADA.length(); 
                  int controls = 0;
                  if(tamanho == 6){
                       controls = 1;
                       goto saltaread;
                  } 
                    char customKey = customKeypad.getKey(); 
                  
     
 
      //caso alguma tecla foi pressionada

                          
            if (customKey){
              
                Serial.println(customKey);
                  //caso alguma das teclas imprimíveis foi pressionada
                  saltaread:

                  //apagar ----------------------------------------------------
                  if(customKey == '*'){
                    SENHA_DIGITADA.remove((SENHA_DIGITADA.length() - 1), 1);
                    senhasimb.remove((senhasimb.length() - 1), 1);
                    senhasimb.remove((senhasimb.length() - 2), 1);
                    //contchar --;
                    goto irprint; 
                    
                  }
                  //apagar ----------------------------------------------------
                  
                  if(controls == 0 && (customKey == '0' || customKey == '1' || customKey == '2' || customKey == '3' || customKey == '4' || customKey == '5' || customKey == '6' || customKey == '7' || customKey == '8' || customKey == '9')){
                        //concatena o novo símbolo a senha que estamos digitando
                       
                        SENHA_DIGITADA+=customKey; 
                        
                        Serial.println(SENHA_DIGITADA);
                        //imprime na tela 
                        lcd.print(customKey);
                        delay(500);
                        irprint:
                        lcd.clear();
                        lcd.print("DIGITE P/ FECHAR");

                        lcd.setCursor(0,1);
                        if(SENHA_DIGITADA.length() != 0){
                          lcd.print(senhasimb);
                          senhasimb +="*";
                          }    
                        
                  } else if(controls == 1){ //customKey == '*'
                    if(SENHA_ESPERADA == SENHA_DIGITADA){ //Se senha for correta
                      lcd.clear();
                      lcd.print("Porta Fechada");
                      digitalWrite(solenoide,HIGH); //fecha a porta
                        conterro = 0;
                        delay(900);
                        lcd.clear();
                       
                        SENHA_DIGITADA = "";
                        senhasimb ="*";  
                       voltar:     lcd.print("DIGITE P/ ABRIR");
                        lcd.setCursor(0,1);
                        
                        //---------------------------------------------------------------
                       
                        //caso alguma tecla foi pressionada
                        int printcontrol = 0;
                        int contchar = 0;
                        do{
                          
                           char customKey = customKeypad.getKey(); 

                               //apagar ----------------------------------------------------
                                if(customKey == '*'){
                                  SENHA_DIGITADA.remove((SENHA_DIGITADA.length() - 1), 1);
                                  senhasimb.remove((senhasimb.length() - 1), 1);
                                  senhasimb.remove((senhasimb.length() - 2), 1);
                                  contchar --;
                                  goto irprint2; 
                                  
                                }
                                //apagar ----------------------------------------------------
                              
                              Serial.println(customKey);
                                //caso alguma das teclas imprimíveis foi pressionada
                                 if(printcontrol == 0 && customKey){
                                  lcd.clear();     
                                 }
                                if(customKey == '0' || customKey == '1' || customKey == '2' || customKey == '3' || customKey == '4' || customKey == '5' || customKey == '6' || customKey == '7' || customKey == '8' || customKey == '9'){
                                      printcontrol = 1;
                                      //concatena o novo símbolo a senha que estamos digitando
                                      SENHA_DIGITADA+=customKey; 
                                      contchar ++;
                                      //imprime na tela 
                                      //imprime na tela 
                        
                                      lcd.print(customKey);
                                      delay(500);
                                      irprint2:
                                      lcd.clear();
                                      lcd.print("DIGITE P/ ABRIR");
                                      lcd.setCursor(0,1);
                                    
                                      
                                     if(SENHA_DIGITADA.length() != 0){
                                      lcd.print(senhasimb);
                                      senhasimb +="*";
                                      }   
                                       
                                }
                                 if(contchar == 6){
                                  break;
                                  senhasimb = "*";
                                }
                          
                        } while(1);
                        senhasimb = "*";
                        if(SENHA_ESPERADA == SENHA_DIGITADA){
                          digitalWrite(solenoide,LOW); //abre porta +
                          digitalWrite(camera, HIGH);
                          delay(500);
                          digitalWrite(camera, LOW);
                          lcd.clear();
                          lcd.print("ABRA A GAVETA");
                          lcd.setCursor(0,1);
                          lcd.print("RETIRE O CELULAR");
                          int tempb = 0;
                          do{
                            if(tempb < 5){
                            delay(1000);
                            }
                            tempb++;
                            if(tempb >= 5){
                              lcd.clear();
                              lcd.print("ABRA A GAVETA");
                              lcd.setCursor(0,1);
                              lcd.print("RETIRE O CELULAR");
                              delay(100);
                            }
                          } while(digitalRead(resetsenha) != 0);
                          lcd.clear();
                          lcd.print("OBRIGADO P/ USAR NOVAMENTE, CADASTRE-SE");
                       
                               for(int posi_LCD = 0; posi_LCD < 75; posi_LCD ++){
                               // lcd.setCursor(16,1);
                               delay(50);
                                lcd.scrollDisplayLeft();  //Essa é a função que faz as letras se deslocarem
                             
                                delay(150);         // Quanto menor o tempo, mais rápido será o deslocamento
                              }
                              lcd.clear();
                              lcd.print("OBRIGADO!");

                          delay(3000);
                         
                          SENHA_DIGITADA = "";
                          SENHA_ESPERADA = "";
                          CONFIRMA = "";
                          lcd.clear();
                          INIT = 1;
                          goto init;
                        } else if(SENHA_MESTRE == SENHA_DIGITADA){
                          digitalWrite(solenoide,LOW); //abre porta +
                          digitalWrite(camera, HIGH);
                          delay(500);
                          digitalWrite(camera, LOW);
                          lcd.clear();
                          lcd.print("ABRA A GAVETA");
                          lcd.setCursor(0,1);
                          lcd.print("RETIRE O CELULAR");
                          int tempb = 0;
                          do{
                            if(tempb < 5){
                              delay(1000);
                            }
                            tempb++;
                            if(tempb >= 5){
                              lcd.clear();
                              lcd.print("ABRA A GAVETA");
                              lcd.setCursor(0,1);
                              lcd.print("RETIRE O CELULAR");
                              delay(100);
                            }
                          } while(digitalRead(resetsenha) != 0);
                          lcd.clear();
                          lcd.print("OBRIGADO P/ USAR NOVAMENTE, CADASTRE-SE");                     
                               for(int posi_LCD = 0; posi_LCD < 75; posi_LCD ++)
                              {
                               // lcd.setCursor(16,1);
                               delay(50);
                                lcd.scrollDisplayRight();  //Essa é a função que faz as letras se deslocarem
                             
                                delay(100);         // Quanto menor o tempo, mais rápido será o deslocamento
                              }
                              lcd.clear();
                              lcd.print("OBRIGADO!");
                          delay(3000);
                          SENHA_DIGITADA = "";
                          SENHA_ESPERADA = "";
                          CONFIRMA = "";
                          lcd.clear();
                          INIT = 1;
                          goto init;
                          
                        } else{
                          lcd.clear();
                          SENHA_DIGITADA = "";
                          lcd.print("SENHA ERRADA!");
                          delay(2500);
                          loopcp = 0;
                          lcd.clear();
                          goto voltar;
                        }
                        //---------------------------------------------------------------
                      
                    } else if(SENHA_MESTRE == SENHA_DIGITADA){

                      conterro = 0;
                      lcd.clear();
                      lcd.print("Senha correta!");
                          digitalWrite(camera, HIGH);
                          delay(500);
                          digitalWrite(camera, LOW);
                      delay(900);
                      lcd.clear();
                      digitalWrite(solenoide,HIGH); //abre a porta
                      SENHA_MESTRE = "";
                      SENHA_DIGITADA = "";
                      senhasimb ="*";
                    } else{ // Caso contrario
                        conterro ++;
                       // digitalWrite(solenoide,HIGH); //abre a porta
                        lcd.clear();
                        lcd.print("Senha Errada");
                        lcd.setCursor(1, 1);
                        lcd.print(conterro);
                        loopcp = 0;
                        SENHA_DIGITADA = "";
                        senhasimb ="*";    
                        delay(2500);
                        lcd.clear();
                        if(conterro >= 3){
                          lcd.print("Ops!!!");
                          delay(700);
                          lcd.clear();
                          lcd.print("solicite a");
                          lcd.setCursor(1, 1);
                          lcd.print("senha mestre!");
                          delay(800);
                          lcd.clear();
                        }
                    }
                  } else if(customKey == '#'){
                    senhasimb = "*";
                      lcd.clear();  
          
                      cadastro();

          
                  } 
            }
            

}





void cadastromestre(){
  char customKey;
  //Cadastro de senha
  int control = 0,control2 = 0; //variaveis de controle
   do{
    
              do{
                
           //captura a tecla pressionada do teclado
              customKey = customKeypad.getKey();
         } while(customKey != '#');

        if(customKey == '#'){
          voltarm:       lcd.clear();
                        lcd.print("DIGITE A SENHA 6");
                        lcd.setCursor(0,1);
                        lcd.print("DIGITOS:");
          control = 1;
        } else {
             //Limpa a tela
              lcd.clear();
             lcd.print("Aperte#");
        }
     } while(control == 0); 
     int condig = 0; //controle de digitos 
  while(control2 == 0){ //Ler a senha até o usuário clica em *
     //captura a tecla pressionada do teclado
     customKey = '0';
              do{
                
                     //captura a tecla pressionada do teclado
                     
                        customKey = customKeypad.getKey();
                        
                   } while(customKey == '0'); 
      //caso alguma tecla foi pressionada
            if (customKey){
                Serial.println(customKey);
                  //caso alguma das teclas imprimíveis foi pressionada
                  if(customKey == '1' || customKey == '2' || customKey == '3' || customKey == '4' || customKey == '5' || customKey == '6' || customKey == '7' || customKey == '8' || customKey == '9'){
                        //concatena o novo símbolo a senha que estamos digitando
                       condig ++; 
                        SENHA_MESTRE+=customKey; 
                        Serial.println(SENHA_MESTRE);
                        //imprime na tela 
                        
                        lcd.print(customKey);
                        delay(500);
                        lcd.clear();
                        lcd.print("DIGITE A SENHA 6");
                        lcd.setCursor(0,1);
                        lcd.print("DIGITOS:");
                        
                        lcd.print(senhasimb);   // ---> x 
                        senhasimb +="*";       
                  } else if (customKey == '*'){
                    if(condig > 6){
                      lcd.clear();
                      lcd.print("OPS!!!");
                      lcd.setCursor(0,1);
                      lcd.print("SENHA GRANDE!");
                      delay(1200);
                      lcd.clear();
                      lcd.print("LIMITE MAX DE");
                      lcd.setCursor(0,1);
                      lcd.print("6 CARACTERES!");
                      delay(1200);
                      goto voltarm;
                    }
                    control2 = 1;
                    lcd.clear();
                    lcd.print("Senha Cadastrada!");
                    delay(1000);
                    lcd.clear();
                   
                  }
           } 
 } 
 
//Cadastro de senha
}

 /*
 *
 * fim cadastro de senha mestre
 *
 */
