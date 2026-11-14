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



String nomes[5]={"Tetris","Rei Montanha","Pour Elise","Marcha Turca","Can-can"};

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
  lcd.init();
  lcd.backlight();
  menu();
}

//le os botoes
void loop(){
}