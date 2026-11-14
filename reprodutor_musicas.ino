#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
//-----------PINOS-----------
int up=7;
int down=6;
int play=5;
int stop=4;
int ledVerde=9;
int ledVermelho=10;
int buzzer=8;

//-----------Variaveis Globais---------
int musica=0;// Guarda a musica que esta no menu do 0 a 4
int nota;// Guarda a frequencia da nota que esta sendo tocada
int parou=0;//aviso de stop 0 (não para) 1 (pausa)



String nomes[5]={"Tetris","Rei Montanha","Pour Elise","Marcha Turca","Can-can"};

//frequencia das notas (Hz) de cada musica
int notas[5][40]={
{659,494,523,587,523,494,440,440,523,659,587,523,494,523,587,659,523,440,440,440,494,523,587,698,880,784,698,659,523,659,587,523,494,494,523,587,659,523,440,440},
{220,247,262,294,330,262,330,311,247,311,294,233,294,220,247,262,294,330,262,330,440,392,330,262,330,392},
{659,622,659,622,659,494,587,523,440,262,330,440,494,330,415,494,523,330,659,622,659,622,659,494,587,523,440,262,330,440,494,330,523,494,440},
{494,440,415,440,523,587,523,494,523,659,698,659,622,659,988,880,831,880,988,880,831,880,1047},
{523,587,698,659,587,784,784,784,880,659,698,587,587,587,698,659,587,523,1047,988,880,784,698,659,587,523}
};

//duracao de cada nota
int tempos[5][40]={
{400,200,200,400,200,200,400,200,200,400,200,200,600,200,400,400,400,400,200,400,200,200,600,200,400,200,200,600,200,400,200,200,400,200,200,400,400,400,400,400},
{200,200,200,200,200,200,400,200,200,400,200,200,400,200,200,200,200,200,200,200,200,200,200,200,200,800},
{150,150,150,150,150,150,150,150,400,150,150,150,400,150,150,150,400,150,150,150,150,150,150,150,150,150,400,150,150,150,400,150,150,150,600},
{150,150,150,150,300,150,150,150,150,300,150,150,150,150,150,150,150,150,150,150,150,150,600},
{400,200,200,200,200,400,400,200,200,200,200,400,400,200,200,200,200,200,200,200,200,200,200,200,200,400}
};

// menu LCD mostra nome das musicas e a ">" de seleção
void menu(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">");
  lcd.print(nomes[musica]);
  lcd.setCursor(1,1);
  if(musica==4){
    lcd.print(nomes[0]);
  }
  else{
    lcd.print(nomes[musica+1]);
  }
}

// Roda apenas uma vez, configura os leds,botoes,buzzer e liga o display
void setup(){
  pinMode(up,INPUT_PULLUP);
  pinMode(down,INPUT_PULLUP);
  pinMode(play,INPUT_PULLUP);
  pinMode(stop,INPUT_PULLUP);
  pinMode(ledVerde,OUTPUT);
  pinMode(ledVermelho,OUTPUT);
  pinMode(buzzer,OUTPUT);
  lcd.init();
  lcd.backlight();
  menu();
}

// toca a música escolhida
void tocar(){
  parou=0;
  digitalWrite(ledVerde,HIGH);// acende o LED quando toca a musica
  lcd.clear();
  lcd.print("Tocando");
  lcd.setCursor(0,1);
  lcd.print(nomes[musica]);
  
  //O for de fora uma volta para cada nota
  for(int i=0;i<40;i++){
    if(tempos[musica][i]==0) break;
    nota=notas[musica][i];
	
	//toca a nota
    tone(buzzer,nota);

    //vai esperando de 10 em 10 pra dar pra ler os botoes
    for(int t=0;t<tempos[musica][i];t=t+10){

      if(digitalRead(stop)==LOW){
        while(digitalRead(stop)==LOW){}
        delay(50);
        parou=1;
        break;
      }

      if(digitalRead(play)==LOW){
        //pausou
        while(digitalRead(play)==LOW){}
        delay(50);
        noTone(buzzer);
        digitalWrite(ledVerde,LOW);
        digitalWrite(ledVermelho,HIGH);
        lcd.clear();
        lcd.print("Pausado");
        lcd.setCursor(0,1);
        lcd.print(nomes[musica]);
		//mantem parado e esperando
        while(digitalRead(play)==HIGH){
          if(digitalRead(stop)==LOW){
            parou=1;
            break;
          }
        }
        //Se foi o STOP que tirou do pause
        if(parou==1){
          while(digitalRead(stop)==LOW){}
          delay(50);
          break;
        }
        //Play na musica novamente
        while(digitalRead(play)==LOW){}
        delay(50);

        digitalWrite(ledVermelho,LOW);
        digitalWrite(ledVerde,HIGH);
        lcd.clear();
        lcd.print("Tocando...");
        lcd.setCursor(0,1);
        lcd.print(nomes[musica]);
        tone(buzzer,nota);
      }

      delay(10);
    }
	//fim de cada nota
    noTone(buzzer);
    delay(20);
    if(parou==1) break;
  }
  //Desliga os leds
  noTone(buzzer);
  digitalWrite(ledVerde,LOW);
  digitalWrite(ledVermelho,LOW);
  menu();
}

//le os botoes
void loop(){
  if(digitalRead(up)==LOW){
    musica--;
    if(musica<0) musica=4;
    menu();
    while(digitalRead(up)==LOW){}
    delay(50);
  }
  if(digitalRead(down)==LOW){
    musica++;
    if(musica>4) musica=0;
    menu();
    while(digitalRead(down)==LOW){}
    delay(50);
  }
  if(digitalRead(play)==LOW){
    while(digitalRead(play)==LOW){}
    delay(50);
    tocar();
  }
}
