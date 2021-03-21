//Karla Fernanda Caceres Alvarado A01720082
//Actividad Integradora

#include <iostream>
#include <cstdlib>
using namespace std;

void bienvenida()//sin parametros de entrada/salida void bienvenida. Desplega un letrero de bienvenida.
{
  cout<<" _____  _    _ _____________      ______ \n";
  cout<<"|  __ \\| |  | |___  /___  / |    |  ____|\n";
  cout<<"| |__) | |  | |  / /   / /| |    | |__   \n";
  cout<<"|  ___/| |  | | / /   / / | |    |  __|  \n";
  cout<<"| |    | |__| |/ /__ / /__| |____| |____ \n";
  cout<<"|_|     \\____//_____/_____|______|______|\n"<<endl;

}
void tableroGanar(int mGanar[4][4]) //void tableroGanar, parametros de entrada y salida: mGanar[4][4], matriz ganadora. Asigna valores de la matriz ganadora.
{
  int i=1;
  for(int x=0;x<4;x++)//columnas
  {
    for(int y=0;y<4;y++)//renglones
    {
      mGanar[x][y]=i++;
      if (mGanar[x][y]==16)//asigna valor
        mGanar[x][y]=0;
    }
  }
}

void desplegarTablero(int mTablero[4][4])//void desplegarTablero, parametros de entrada y salida: mTablero[4][4]. Da formato a la matriz para que se vea comoun tablero.
{
  cout<<"━━━━━━━━━━━━━━━━━━━━━"<<endl<<"│ ";
  for(int x=0;x<4;x++)
  {
    for(int y=0;y<4;y++)
    {
      if (mTablero[x][y]==0|| mTablero[x][y]==16)//se el valor de la casilla es 16 o 0, imprime un espacio
      {
        mTablero[x][y]=0;
        cout<<" "<<"  │ ";
      }
      else
      {
        if(mTablero[x][y]<10)//acomoda la matriz para que los numeros esten en el mismo nivel
          cout<<mTablero[x][y]<<"  │ ";
        else
            cout<<mTablero[x][y]<<" │ ";
      }
    }
    cout<<endl<<"━━━━━━━━━━━━━━━━━━━━━"<<endl;
    if  (x<3){
    cout<<"│ ";
    }
  }
}

bool verificar(int mTablero[4][4],int mGanar[4][4])//bool verificar. parametros de entrada: mGanar y mTablero. parametro de salida: un booleano que comprueba si las matrices son iguales.
{
  bool verifGanar=true;
  for(int x=0;x<4;x++)
  {
    for (int y=0;y<4;y++)
    {
      if (mGanar[x][y]!=mTablero[x][y])// si mGanar y mTablero son diferentes, manda un falso
      {
        verifGanar=false;
      }
    }
  }
  return verifGanar;
}

void randomT(int mTablero[4][4])//void randomT, parametros de entrada: mTablero. Genera el tablero, aleatorio o ingresado por el usuario. No regresa valor.
{
  char tablero;
  do{
    cout<<"Tablero aleatorio? (s/n)"<<endl;//decide si el tablero es aleatorio
    cin>>tablero;
    tablero=tolower(tablero);
    if (tablero=='s')
    {
      srand((int)time(0));//para que sea diferente los valores cada vez que se reinicie el programa
      int r, c,temp;
      bool repetir[16];//booleano que contenga los numeros de la matriz
      for(int x=0;x<16;x++)
      {
        repetir[x]=false;//inicia los valores del booleano como falso.
      }
        for(int r=0;r<4;r++)//columnas
        {
          for(int c=0;c<4;c++)//renglones
          {
            do{
              temp=rand()%16+1;//da valor aleatorio
            }while(repetir[temp]==true);//checa si el valor en el arreglo booleano ya fue usado-
            mTablero[r][c]=temp;//cuando compruebe que el valor no fue usado, se lo asigna
            repetir[temp]=true;//marca el valor como usado
          }
        }
    }
    if(tablero=='n'){
      cout<<"Teclee su tablero"<<endl;//permite que se ingrese un tablero.
      for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
          cout<<"Escriba el valor de ("<<x+1<<","<<y+1<<"): ";
          cin>>mTablero[x][y];
        }
      }
    }
  }while(tablero!='s'&&tablero!='n');//evita errores en lo que se ingreso.
}

bool verifMover(int mTablero[4][4], int coordx, int coordy)// booleano verifMover, parametros de entrada: mTablero, coordx,coordy. Verifica los lados  del  numero que se desea mover para comprobar que sea una casilla permitida. Regresa un booleano.
{
  bool vacio=false;
  if (coordx==0){
    switch(coordy){//checa los  diferentes casos en cada columna del 0 al 3.
      case 0: //checa individualmente en cada renglon.
        if (mTablero[1][0]==0||mTablero[0][1]==0)//caso esquina izq arriba. verificar solo alado y abajo por 0.
          vacio= true;
          break;
      case 1:
      case 2:
        if (mTablero[coordx][coordy-1]==0||mTablero[coordx][coordy+1]==0||mTablero[coordx+1][coordy]==0) //checa primera fila enmedio numeros en ambos lados y abajo por 0.
          vacio=true;
         break;
      case 3:
        if (mTablero[coordx+1][coordy]==0||mTablero[coordx][coordy-1]==0) //checa esquina izq arriba.
          vacio=true;
          break;
    }
  }
  if (coordx==1||coordx==2){ //renglon 2 y 3 (mismas verificaciones)
    switch(coordy){
      case 0:
        if (mTablero[coordx-1][coordy]==0||mTablero[coordx+1][coordy]==0||mTablero[coordx][coordy+1]==0) //verifica casilla 1, superior, inferior y lado derecho. 
          vacio=true;
          break;
      case 1:
      case 2:
        if (mTablero[coordx-1][coordy]==0||mTablero[coordx+1][coordy]==0||mTablero[coordx][coordy+1]==0||mTablero[coordx][coordy-1]==0) //verifica casillas de enmedio, por todos los lados inmediatos
          vacio=true; 
          break;
      case 3:
        if (mTablero[coordx-1][coordy]==0||mTablero[coordx+1][coordy]==0||mTablero[coordx][coordy-1]==0) //verifica esquina derecha.
         vacio=true;
         break;
    }
  }
    if (coordx==3){//renglon 4
    switch(coordy){
      case 0:
        if (mTablero[coordx-1][coordy]==0||mTablero[coordx][coordy+1]==0)//verifica esquina izq inferior.
          vacio= true;
          break;
      case 1:
      case 2:
        if (mTablero[coordx][coordy-1]==0||mTablero[coordx][coordy+1]==0||mTablero[coordx-1][coordy]==0)//verifica centro.
          vacio=true;
         break;
      case 3:
        if (mTablero[coordx][coordy-1]==0||mTablero[coordx-1][coordy]==0)//verifica esq izquierda inferior.
          vacio=true;
          break;
    }
  }
  return vacio; //si se verifico que habia un valor 0, retorna falso, si si existia un valor, retorna verdadero.
}

void pedirNum(int &nMover,int mTablero[4][4],int &coordx,int &coordy) //void pedirNum. parametros de entrada: nMover, mTablero, coordx, coordy. Pide el valor a el usuario, si este es invalido, vuelve a preguntar.
{
  bool vacio=false;
  nMover=-1;
  do
  {
    cout<<"Que numero deseas mover? (1->15)"<<endl;
    cin>>nMover;//recibe el valor del usuario.
    for(int x=0;x<4;x++)
    {
      for (int y=0;y<4;y++)
      {
        if(mTablero[x][y]==nMover) //busca las coordenadas del numero ingresado
        {
          coordx=x;
          coordy=y;
        }
      }
    }
    vacio = verifMover(mTablero, coordx, coordy);
  } while(vacio==false);// si si es un numero valido, continua el programa
}

void mover (int mTablero[4][4], int coordx, int coordy, int nMover,int &mov) //void mover, parametros de entrada: coordenadas, numero, mTablero, contador de movimientos. Salidas: contador, mTablero. Mueve el numero a la casilla vacia.
{
  int coordMx;
  int coordMy;
  for(int x=0;x<4;x++)
  {
    for(int y=0;y<4;y++)
    {
      if (mTablero[x][y]==0)//Busca la casilla vacia
      {
        coordMx= x;
        coordMy= y;//le asigna los valores a una variable temporal
      }
    }
  }
  mTablero[coordMx][coordMy]= nMover;//asigna al espacio el valor
  mTablero[coordx][coordy]=16;//asigna a la casilla del valor el espacio
  mov++;//cuenta el movimiento
}

void ganarTxt(int mov)//void ganarTxt. parametros de entrada: movimientos. desplega el texto cuando se gana eljuego
{
  cout<<endl<<endl<<"***************************************"<<endl<<"***Felicidades! ha terminado la partida***"<<endl;
  cout<<"Movimientos usados: "<<mov;
}

bool jugarSN(int ronda)//bool jugarSN. Pregunta al jugador si quiere continuar la partida despues de cada movimiento. Regresa un booleano.
{
  char jugar=true;
  if (ronda>0){
    do{
      cout<<"Desea seguir jugando? (s/n)"<<endl;
      cin>>jugar;//pregunta si se quiere seguir con la partida
      jugar=tolower(jugar);
    } while(jugar!='s'&&jugar!='n');//confirma que la entrada del usuario sea valida
    if (jugar=='n')
      return false; //si no se desea continuar, regresa falso, de no ser asi, regresa verdadero.
    else
      return true;
  }
  else
    return true;
}

int main() 
{
  int coordy, coordx, mov=0, ronda=0;
  bool jugar;
  bool ganar;
  int mTablero [4][4];
  int mGanar[4][4];
  int nMover;
  bienvenida();
  randomT(mTablero);
  tableroGanar(mGanar);
  desplegarTablero(mTablero);
  do{
  jugar=jugarSN(ronda);
  ronda++;//verifica que en el primer movimiento no pregute si se desea continuar con la partida
  if(jugar==true){
  pedirNum(nMover, mTablero, coordx, coordy);
  mover(mTablero, coordx, coordy, nMover,mov);
  desplegarTablero(mTablero);
  ganar=verificar(mTablero, mGanar);
  }
  } while (ganar==false && jugar==true);
  if(ganar==true)
    ganarTxt(mov);
  if (ganar==false)//texto si se salio de la partida sin ganar.
    cout<<"Fin de la partida. Gracias por jugar."<<endl;
  return 0;
}
