#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Boat
{
  private:

        char dir;
        int length;
        vector <int> boatrow;
        vector <int> boatcol;
        int hits;
        string name;

    public:

        //G³ówny konstruktor
        Boat(char d, int lgth, vector<int> r, vector<int> c, int hit, string nme)
        {
            dir=d;
            length=lgth;
            boatrow=r;
            boatcol=c;
            hits=hit;
            name=nme;
        }

        //Uderzenie
        void setHit()
        {
            hits++;
        }

        int checkSunk(int BoatSize)
        {
            if(hits>=BoatSize)
            {
                return 9;
            }
            else
            {
                return 0;
            }
        }

        //Pobranie polozenia statku
        void boatCoordinates()
        {
            cout << "Polozenie statku " << name << endl << endl;
            for(int i=0; i<length; i++)
            {
                cout << "Siatka [" << boatrow[i] << "][" << boatcol[i] << "]" << endl;
            }
        cout << endl;
        }

        //Sprawdzenie czy trafiony zostal statek
        string getBoat(int r, int c)
        {
            for(int i=0; i<length; i++)
            {
                if((boatrow[i]==r) && (boatcol[i]==c))
                {
                    return name;
                }
            }
            return "";
         }
};

enum BoatSize { Submarine = 2, Destroyer = 3, Battleship = 4, Carrier = 5 };
void initGrid(int grid[][10]);
void printBoard(int grid[][10]);
void printGameBoard(int grid[][10]);
int resetColAndRow(int col, int &row, int BoatSize, char d);
char getDirection(int d);
int checkSpaces(int grid[][10], int c, int r, int s, char d);
void editGrid(int grid[][10], int col, int row, int BoatSize, char dir);
bool setBoat(int grid[][10], int BoatSize, int name, vector<Boat> &boatList);
void editBoatInfo(int grid[][10], int c, int r, int BoatSize, char d, vector<Boat> &boatList, int name);
int playGame(int grid[][10], vector<Boat> &boatList);
int getSpace(int grid[][10], int row, int col);

int main()
{
    int grid[10][10];
    vector<Boat> boatList;
    char play;
    initGrid(grid);
    printBoard(grid);  //wyswietla plansze
    setBoat(grid, Carrier, 1, boatList);  //Ustawiam statki na planszy
    setBoat(grid, Battleship, 2, boatList);
    setBoat(grid, Battleship, 3, boatList);
    setBoat(grid, Destroyer, 4, boatList);
    setBoat(grid, Destroyer, 5, boatList);
    setBoat(grid, Destroyer, 6, boatList);
    setBoat(grid, Submarine, 7, boatList);
    setBoat(grid, Submarine, 8, boatList);
    setBoat(grid, Submarine, 9, boatList);
    setBoat(grid, Submarine, 10, boatList);

    cout << "BITWA STATKOW.  Wpisz t aby rozpoczac rozgrywke" << endl << endl;
    cout << "Jeœli na planszy pojawi sie 1, oznacza to trafienie, jesli 9, oznacza to ze nie trafiles." << endl << endl;
    cin >> play;
    if(play=='t')
    {
        playGame(grid, boatList);
    }
    return 0;
}

void initGrid(int grid[][10])
{
    for(int col=0; col<10; col++)
    {
        for(int row=0; row<10; row++)
        {
            grid[col][row]=0;
        }
    }
}

void printBoard(int grid[][10])  //Plansza ze statkami
{
    cout << "   0|1|2|3|4|5|6|7|8|9" << endl << endl;
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(j==0)
            {
                cout << i << "  " ; //wyswietla wiersze
            }
            cout << grid[i][j] ;
            if(j!=9)
            {
                cout << "|";
            }
        }
    cout << endl;
    }
    cout << endl;
}

void printGameBoard(int grid[][10]) //Plansza do gry bez widocznych statkow
{
    cout << "   0|1|2|3|4|5|6|7|8|9" << endl << endl;
    for(int i=0; i<10; i++)  //petla kolumn
    {
        for(int j=0; j<10; j++)  //petle wierszy
        {
            if(j==0)
            {
                cout << i << "  " ; //wyœwietla liczbe kolumn
            }
            if(grid[i][j]==1)  //jesli trafi, wyswietli 1
            {
                cout << 1;
            } else if(grid[i][j]==9)  //jesli spudluje, wyswietli 9
            {
                cout << 9;
            } else
            {
                cout << 0;  //wypelniacz
            }

            if(j!=9)
            {
                cout << "|";
            }
        }
    cout << endl;
    }
    cout << endl;
}

bool setBoat(int grid[][10], int BoatSize, int name, vector<Boat> &boatList)
//Funkcja rozmieszczajaca statki na planszy
{
    srand(time(0));
    int col=0;
    int row=0;
    char d='v';
    bool placementFailure=true;
    char check='v';
    int cS=0;

    d=getDirection(rand()%10);  //wybiera dowolna pozycje na planszy
    col=resetColAndRow(col, row, BoatSize, d);  //Ta funkcja zwraca wybrana kolumne oraz wiersz gdzie rozmiescic statek

    while(placementFailure)
    {
        if(d=='h')
        {
            cS=checkSpaces(grid, col, row, BoatSize, d);//Sprawdza miejsce czy jest wolne
            if(cS==1)//Jesli miejsce na planszy jest zajete wybierze inna pozycje
            {
                d=getDirection(rand()%10);
                col=resetColAndRow(col, row, BoatSize, d);
                cS==0;
                continue;
            }
            editGrid(grid, col, row, BoatSize, d);//umieszcza statek na planszy
            editBoatInfo(grid, col, row, BoatSize, d, boatList, name);//tworzy statek
            return 0;
        }
        else if(d=='v')
        {
            cS=checkSpaces(grid, col, row, BoatSize, d);
            if(cS==1)
            {
                d=getDirection(rand()%10);
                col=resetColAndRow(col, row, BoatSize, d);
                cS==0;
                continue;
            }
            editGrid(grid, col, row, BoatSize, d);
            editBoatInfo(grid, col, row, BoatSize, d, boatList, name);
            return 0;
        }
     }
}

char getDirection(int d)
{
    if(d>4)
        {
            return 'h';  //wybiera jak ustawic statek
        }
        else
        {
            return 'v';
        }
}

void editGrid(int grid[][10], int col, int row, int BoatSize, char dir)
//Ta funkcja przyporzadkowuje odpowiednia liczbe do wielkosci statku
{
    if(dir=='h')
    {
        for(int i=0; i<BoatSize; i++)
        {
            grid[row][col]=BoatSize;
            col++;
            cout << endl;
        }
    }
    else if(dir=='v')
    {
        for(int i=0; i<BoatSize; i++)
        {
            grid[row][col]=BoatSize;
            row++;
            cout << endl;
        }
    }
    else
    {
        cout << "Error!  No direction passed" << endl;
    }
    //printBoard(grid);  //skonczone rozmieszczanie
}

int checkSpaces(int grid[][10], int c, int r, int s, char d)
//Sprawdzenie zeby statki sie na siebie nie nachodzily
{
    int check=0;
    if(d=='h')
    {
        for(int i=c; i<c+s; i++)
        {
        check=grid[r][i];
                if(check!=0)
                {
                    return 1;
                }
        }

        return 0;
    }
    else
    {
        for(int i=r; i<r+s; i++)
        {
        check=grid[i][c];
                if(check!=0)
                {
                    return 1;

                }
        }

        return 0;
    }
}

int resetColAndRow(int col, int &row, int BoatSize, char d)
{
    switch(BoatSize) //Tworzy kolumny i wiersze sprawdzajace czy ³ódka nie wysz³a poza plansze
    {
        case Submarine:
            if(d=='h')
            {
                col=rand()%8;
                row=rand()%10;
            }
            else
            {
                col=rand()%10;
                row=rand()%8;
            }
            break;
        case Destroyer:
            if(d=='h')
            {
                col=rand()%7;
                row=rand()%10;
            }
            else
            {
                col=rand()%10;
                row=rand()%7;
            }
            break;
        case Battleship:
            if(d=='h')
            {
                col=rand()%6;
                row=rand()%10;
            }
            else
            {
                col=rand()%10;
                row=rand()%6;
            }
            break;
        case Carrier:
            if(d=='h')
            {
                col=rand()%5;
                row=rand()%10;
            }
            else
            {
                col=rand()%10;
                row=rand()%5;
            }
    }
    return col;
}

void editBoatInfo(int grid[][10], int c, int r, int BoatSize, char d, vector<Boat> &boatList, int name)
//Funkcja tworzaca statki
{
    switch(name)
    {
        case 1:
            if(d=='h')
            {
                vector<int> r1 (5);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (5);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            //Aircraft Carrier
            Boat carrierBoat('h', 5, r1, c1, 0, "Aircraft Carrier");
            boatList.push_back(carrierBoat);
            }
            else if(d=='v')
            {
                vector<int> r1 (5);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (5);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            //Aircraft Carrier
            Boat carrierBoat('v', 5, r1, c1, 0, "Aircraft Carrier");
            boatList.push_back(carrierBoat);
            }
            break;
        case 2:
            if(d=='h')
            {
                vector<int> r1 (4);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (4);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            //Battleship 1
            Boat battleship1Boat('h', 4, r1, c1, 0, "Battleship 1");
            boatList.push_back(battleship1Boat);
            }
            else if(d=='v')
            {
                vector<int> r1 (4);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (4);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            //Battleship 1
            Boat battleship1Boat('v', 4, r1, c1, 0, "Battleship 1");
            boatList.push_back(battleship1Boat);
        }
        break;
        case 3:
            if(d=='h')
            {
                vector<int> r1 (4);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (4);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            //Battleship 2
            Boat battleship2Boat('h', 4, r1, c1, 0, "Battleship 2");
            boatList.push_back(battleship2Boat);
            }
            else if(d=='v')
            {
                vector<int> r1 (4);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (4);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            //Battleship 2
            Boat battleship2Boat('v', 4, r1, c1, 0, "Battleship 2");
            boatList.push_back(battleship2Boat);
            }
            break;
        case 4:
            if(d=='h')
            {
                vector<int> r1 (3);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (3);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
             //Destroyer 1
             Boat destroyer1Boat('h', 3, r1, c1, 0, "Destroyer 1");
             boatList.push_back(destroyer1Boat);
             }
             else if(d=='v')
             {
                vector<int> r1 (3);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (3);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
             //Destroyer 1
             Boat destroyer1Boat('v', 3, r1, c1, 0, "Destroyer 1");
             boatList.push_back(destroyer1Boat);
             }
             break;
        case 5:
        if(d=='h')
        {
            vector<int> r1 (3);
            for (int i=0; i<(int)r1.size(); ++i)
            {
                r1.at(i)=r;
            }
            vector<int> c1 (3);
            for (int i=0; i<(int)c1.size(); ++i)
            {
                c1.at(i)=c;
                c++;
            }
        //Destroyer 2
        Boat destroyer2Boat('h', 3, r1, c1, 0, "Destroyer 2");
        boatList.push_back(destroyer2Boat);
        }
        else if(d=='v')
        {
            vector<int> r1 (3);
            for (int i=0; i<(int)r1.size(); ++i)
            {
                r1.at(i)=r;
                r++;
            }
            vector<int> c1 (3);
            for (int i=0; i<(int)c1.size(); ++i)
            {
                c1.at(i)=c;
            }
            //Destroyer 2
            Boat destroyer2Boat('v', 3, r1, c1, 0, "Destroyer 2");
            boatList.push_back(destroyer2Boat);
        }
            break;
        case 6:
            if(d=='h')
            {
                vector<int> r1 (3);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (3);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            //Destroyer 3
            Boat destroyer3Boat('h', 3, r1, c1, 0, "Destroyer 3");
            boatList.push_back(destroyer3Boat);
            }
            else if(d=='v')
            {
                vector<int> r1 (3);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (3);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            //Destroyer 3
            Boat destroyer3Boat('v', 3, r1, c1, 0, "Destroyer 3");
            boatList.push_back(destroyer3Boat);
            }
            break;
        case 7:
            if(d=='h')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            //Submarine1
            Boat submarine1Boat('h', 2, r1, c1, 0, "Submarine 1");
            boatList.push_back(submarine1Boat);
            }
            else if(d=='v')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            //Submarine 1
            Boat submarine1Boat('v', 2, r1, c1, 0, "Submarine 1");
            boatList.push_back(submarine1Boat);
            }
            break;
        case 8:
            if(d=='h')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            //Submarine 2
            Boat submarine2Boat('h', 2, r1, c1, 0, "Submarine 2");
            boatList.push_back(submarine2Boat);
            }
            else if(d=='v')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            //Submarine 2
            Boat submarine2Boat('v', 2, r1, c1, 0, "Submarine 2");
            boatList.push_back(submarine2Boat);
            }
            break;
        case 9:
            if(d=='h')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                    c++;
                }
            //Submarine 3
            Boat submarine3Boat('h', 2, r1, c1, 0, "Submarine 3");
            boatList.push_back(submarine3Boat);
            }
            else if(d=='v')
            {
                vector<int> r1 (2);
                for (int i=0; i<(int)r1.size(); ++i)
                {
                    r1.at(i)=r;
                    r++;
                }
                vector<int> c1 (2);
                for (int i=0; i<(int)c1.size(); ++i)
                {
                    c1.at(i)=c;
                }
            //Submarine 3
            Boat submarine3Boat('v', 2, r1, c1, 0, "Submarine 3");
            boatList.push_back(submarine3Boat);
            }
            break;
        case 10:
        if(d=='h')
        {
            vector<int> r1 (2);
            for (int i=0; i<(int)r1.size(); ++i)
            {
                r1.at(i)=r;
            }
            vector<int> c1 (2);
            for (int i=0; i<(int)c1.size(); ++i)
            {
                c1.at(i)=c;
                c++;
            }
        //Submarine 4
        Boat submarine4Boat('h', 2, r1, c1, 0, "Submarine 4");
        boatList.push_back(submarine4Boat);
        }
        else if(d=='v')
        {
            vector<int> r1 (2);
            for (int i=0; i<(int)r1.size(); ++i)
            {
                r1.at(i)=r;
                r++;
            }
            vector<int> c1 (2);
            for (int i=0; i<(int)c1.size(); ++i)
            {
                c1.at(i)=c;
            }
        //Submarine 4
        Boat submarine4Boat('v', 2, r1, c1, 0, "Submarine 4");
        boatList.push_back(submarine4Boat);
        }
        break;
    }
}

int playGame(int grid[][10], vector<Boat> &boatList)
{
    bool gameInProgress=true;
    int row=0;
    int col=0;
    int guess=0;
    int hit=0;
    int miss=0;
    int space=0;
    char d='g';
    string btname="";
    int sunk=0;

    while(gameInProgress)
    {
        printGameBoard(grid);
        //printBoard(grid);			//odkomentowac zeby wyswietlic plansze komputera
        cout << "Podaj wiersz: ";
        cin >> row;
        cout << "Podaj kolumne: ";
        cin >> col;
        cout << endl;
        guess++;
        space=getSpace(grid, row, col);

        switch(space)
        {
            case 0:
                cout << "Pudlo!" << endl;
                grid[row][col]=9;
                miss++;
                break;
            case 1:
                cout << "To miejsce zostalo juz zbombardowane, tracisz ruch." << endl;
                break;
            case 2:
                grid[row][col]=1;
                hit++;

                btname=boatList[6].getBoat(row, col);
                if(btname=="Submarine 1")
                {
                    cout << "Trafiles " << btname << "!" << endl;
                    boatList[6].setHit();
                    sunk=boatList[6].checkSunk(Submarine);
                    if(sunk==9)
                    {
                        cout << "Zatopiles Submarine 1." << endl;
                    }
                } else if(btname.empty())
                {
                    btname=boatList[7].getBoat(row, col);
                    if(btname=="Submarine 2")
                    {
                        cout << "Trafiles " << btname << "!" << endl;
                        boatList[7].setHit();
                        sunk=boatList[7].checkSunk(Submarine);
                        if(sunk==9)
                        {
                            cout << "Zatopiles Submarine 2." << endl;
                        }
                    } else if(btname.empty())
                    {
                        btname=boatList[8].getBoat(row, col);
                        cout << "Trafiles " << btname << "!" << endl;
                        boatList[8].setHit();
                        sunk=boatList[8].checkSunk(Submarine);
                        if(sunk==9)
                        {
                            cout << "Zatopiles Submarine 3." << endl;
                        }
                    } else if(btname.empty())
                    {
                        btname=boatList[9].getBoat(row, col);
                        cout << "Trafiles " << btname << "!" << endl;
                        boatList[9].setHit();
                        sunk=boatList[9].checkSunk(Submarine);
                        if(sunk==9)
                        {
                            cout << "Zatopiles Submarine 4." << endl;
                        }
                    }
                }
                btname.clear();
                break;
            case 3:
                grid[row][col]=1;
                hit++;

                btname=boatList[3].getBoat(row, col);
                if(btname=="Destroyer 1")
                {
                    cout << "Trafiles " << btname << "!" << endl;
                    boatList[3].setHit();
                    sunk=boatList[3].checkSunk(Destroyer);
                    if(sunk==9)
                    {
                        cout << "Zatopiles Destroyer 1." << endl;
                    }
                } else if(btname.empty())
                {
                    btname=boatList[4].getBoat(row, col);
                    if(btname=="Destroyer 2")
                    {
                        cout << "Trafiles " << btname << "!" << endl;
                        boatList[4].setHit();
                        sunk=boatList[4].checkSunk(Destroyer);
                        if(sunk==9)
                        {
                            cout << "Zatopiles Destroyer 2." << endl;
                        }
                    } else if(btname.empty())
                    {
                        btname=boatList[5].getBoat(row, col);
                        cout << "Trafiles " << btname << "!" << endl;
                        boatList[5].setHit();
                        sunk=boatList[5].checkSunk(Destroyer);
                        cout << "zatopiony " << sunk << endl;
                        if(sunk==9)
                        {
                            cout << "Zatopiles Destroyer 3." << endl;
                        }
                    }
                }
                btname.clear();
                break;
            case 4:
                grid[row][col]=1;
                hit++;

                btname=boatList[1].getBoat(row, col);
                if(btname=="Battleship 1")
                {
                    cout << "Trafiles " << btname << "!" << endl;
                    boatList[1].setHit();
                    sunk=boatList[1].checkSunk(Battleship);
                    if(sunk==9)
                    {
                        cout << "Zatopiles Battleship 1." << endl;
                    }
                }
                if(btname.empty())
                {
                    btname=boatList[2].getBoat(row, col);
                    cout << "Trafiles " << btname << "!" << endl;
                    boatList[2].setHit();
                    sunk=boatList[2].checkSunk(Battleship);
                    if(sunk==9)
                    {
                        cout << "Zatopiles Battleship 2." << endl;
                    }
                }
                btname.clear();
                break;
            case 5:
                cout << "Trafiles aircraft carrier! " << endl;
                grid[row][col]=1;
                hit++;
                boatList[0].setHit();
                sunk=boatList[0].checkSunk(Carrier);
                if(sunk==9)
                {
                    cout << "Zatopiles aircraft carrier." << endl;
                }
                break;
        }
        if(hit==30)
        {
            gameInProgress=false;
        }
    }

    cout << "Dziekuje za zagranie w moja gre!  Zatopiles wszystkie statki w " << guess << " ruchow!" << endl;

}

int getSpace(int grid[][10], int row, int col)
{
    int space=0;
    space=grid[row][col];
    return space;
}
