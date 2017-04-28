#define BYTE unsigned char
#define WORD unsigned int

#define PA 0X40
#define PB 0X41
#define PC 0X42
#define Rctr 0X43
#define Ptos_all_out 0X80

/*Prototipos de funciones*/
extern void outportB(WORD port, BYTE dato);
extern BYTE inportB(WORD port);
extern void putchar(BYTE dato);
extern void delay(WORD tiempo);
char getch(void);
void printBin(BYTE dato);
void setBitPort(WORD puerto, BYTE num_bit);
void ClrBitPort(WORD puerto, BYTE num_bit);
void NotBitPort(WORD puerto, BYTE num_bit);
void ReverseBitsPort(WORD puerto);
BYTE TstBitPort(WORD puerto, BYTE num_bit);
void puts(char *str);

char dato;
char opcion;
char numeroBit;

void main(void){
  puts("Practica 5b\n\r");            /*Imprime el mensaje*/
  outportB(Rctr, Ptos_all_out);       /*Inicializar 8255*/
  outportB(PA, 0X55);                 /*Presenta 55h en el puerto A*/
  while(1){
    puts("Presiona una tecla:\n\r");
    dato=getch();
    printBin(dato);
    puts("\n\r");
    outportB(PB, dato);
    puts("Selecciona una opcion:\n\r[1]setBitPort\n\r[2]ClrBitPort\n\r[3]NotBitPort\n\r[4]ReverseBitsPort\n\r");
    opcion = getch();                   /*Leer la tecla*/
    switch(opcion){
      case '1':
        puts("Que bit deseas activar?\n\n\n\r");
        numeroBit = getch();
        numeroBit-=48;
        setBitPort(PB,numeroBit);
        break;
      case '2':
        puts("Que bit deseas desactivar?\n\n\n\r");
        numeroBit = getch();
        numeroBit-=48;
        ClrBitPort(PB,numeroBit);
        break;
      case '3':
        puts("Que bit deseas invertir?\n\n\n\r");
        numeroBit = getch();
        numeroBit-=48;
        NotBitPort(PB,numeroBit);
        break;
      /*case '4':
        puts("Esta función intercambia la posición de los MSB a los LSB al presionar enter\n\n\n\r");
        numeroBit=getch();
        numeroBit-=48;
        ReverseBitsPort(PB);
        break;*/
      default:
        puts("Esta funcion invierte la posicion de los bits del LSB al MSB\n\n\n\r");
        ReverseBitsPort(PB);
        break;
    }
  }
}


/*Declaración de funciones*/
/*Función simple para desplegar un byte en formato binario*/
void printBin(BYTE dato){
  BYTE msk = 0x80;
  do{
    putchar( (dato&msk)?'1':'0' );
    msk>>=1;
  }while(msk);
}

/*Funcion para imprimir una cadena de caracteres*/
void puts( char *str){
  while(*str)
    putchar(*str++);
}

char getch(void){
  char dato;
  asm mov ah,8
  asm int 21h
  asm mov dato,al
  return dato;
}

/*Función que manipula la información de un puerto dado para activar un bit*/
void setBitPort(WORD puerto, BYTE num_bit){
  outportB(puerto, inportB(puerto)|(0x01<<num_bit));
}

/*Función que manipula la información de un puerto dado para desactivar un bit*/
void ClrBitPort(WORD puerto, BYTE num_bit){
  outportB(puerto, inportB(puerto)&(~(0x01<<num_bit)));
}

/*Función que manipula la información de un puerto dado para invertir un bit*/
void NotBitPort(WORD puerto, BYTE num_bit){
  outportB(puerto, inportB(puerto)^(0x01<<num_bit));
}

/*Función que invierte la posición de todos los bits que lee del puerto*/
void ReverseBitsPort(WORD puerto){
  unsigned int inicio = 0;
  unsigned int final = 7;
  while(inicio<final){
    if( (TstBitPort(puerto,inicio))^(TstBitPort(puerto,final)) ){
      NotBitPort(puerto,inicio);
      NotBitPort(puerto,final);
    }
    inicio++;
    final--;
  }
}

/*Función verifica el valor de un bit y regresa el estado*/
BYTE TstBitPort(WORD puerto, BYTE num_bit){
  return((inportB(puerto)&(0x01<<num_bit))?1:0);
}
