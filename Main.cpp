//Output window for Project
#include<iostream>
#include<fstream>
#include<windows.h>
#include<string.h>
using namespace std;
class Files
{
    public :
    char data[100][50];
	int number;
	string name;

    void Newfile()
    {
        cout << "Enter the name of file : ";
	    cin >> name;
        cout << "Enter the number of lines" << endl << "you wish to enter in your file : ";
	    cin >> number;
	    name = name + ".txt";
        openFile(name,number);
    }
    private :
    void openFile(string fname,int numOfLines)
    {
        fname = fname + ".txt";
        // open a file in write mode.
        ofstream outfile;
        outfile.open(fname);
        cout << "Writing to the file" << endl;
        fflush(stdin);
        for(int i=0;i<numOfLines;i++)
        {
            cout << "Enter your name " << i+1 << " : "; 
            fflush(stdin);
            cin>>data[i];
            //getline(cin,data[i]); 
            fflush(stdin);
            // write inputted data into the file.
            outfile << data[i] << endl;
        }
        // close the opened file.
        sorting();
         for(int i=0;i<numOfLines;i++)
        {
    
            // write inputted data into the file.
            outfile << data[i] << endl;
        }
        outfile.close();
        
        PrintFileData(fname,numOfLines);
    }

    public :
    void sorting(){
    
        char temp[50];
        for(int i = 0;i<number;i++){
            for(int j=i+1;j<number;j++){
                if(strcmp(data[i],data[j])>0){
                    strcpy(temp,data[i]);
                    strcpy(data[i],data[j]);
                    strcpy(data[j],temp);
                    
                }
            
            }
        }
        for(int i = 0;i<number;i++){
            cout<<data[i];
     }
    }
    void PrintFileData(string fname,int NumOfLines)
    {
        //string data[100];
        fname = fname + ".txt";
        ifstream infile; 
        infile.open(fname); 
        cout << "Data Of File : " << endl;
        for(int i=0;i<NumOfLines;i++)
        { 
            infile >> data[i]; 
            cout << "Line " << i+1 << " ";
            // write the data at the screen.
            cout << data[i] << endl;
        }
        // close the opened file.
        infile.close();
    }

};
class Layout : public Files
{
    public : 
    void SetColor(int ForgC)
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
//Create the function to cleat console
void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     ///Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     ///This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     ///A return value... indicating how many chars were written
     ///   not used but we need to capture this since it will be
     ///   written anyway (passing NULL causes an access violation).
     DWORD count;
     ///This is a structure containing all of the console info
     /// it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     ///Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          ///This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}
//create the function to set background colour
void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0A) << 4) + (ForgC & 0x0A);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
//Create or define the coordinator
COORD coord = {0,0}; ///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; /// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//Main Layout design by rectangle
void drawRectangle(){
    int i, j;
    gotoxy(0,0);
    printf("%c",201);
    //vertical line top
    for(i = 1; i < 75; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    //2nd vertical line 
    for(i = 1; i < 76; i++){
        gotoxy(i,6);
        if(i == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }
    //horizontal line
    for(i = 7; i < 24; i++){
        gotoxy(45,i);
        printf("%c",186);
    }
}
//2nd windwow clear function
void clearWindow(){
    int i,j;
    for(i = 24; i < 78; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);
            cout << " ";
        }
    }
    return;
}
//Fill the details in window
void window(){
    drawRectangle();
    gotoxy(30,2);
    SetColor(35);
    cout << "Project 1" << endl;
    gotoxy(10,3);
    cout << "Chandubhai S Patel institute Of Technology(CSPIT)" << endl;
    gotoxy(13,4);
    gotoxy(13,24);
    cout << "Department of Computer Science & Engg.(CSE)" << endl;
    gotoxy(18,5);
    cout << "Created By 22CS016,22CS048,22CS079";
    SetColor(25);
}

void main_window(Files &f1)
{
    int choice;
    SetColor(28);
    int x = 2;
    while(1){
        gotoxy(47,8);
        cout << "1. Add File" << endl;
        gotoxy(47,10);
        cout << "2. Search File" << endl;
        //gotoxy(x,12);cout << "3. " << endl;
        //gotoxy(x,14);cout << "4. " << endl;
        //gotoxy(x,16);cout << "5. " << endl;
        gotoxy(47,15);
        cout << " "<< "Enter Choice : ";
        scanf("%d",&choice);
        gotoxy(47,17);
        cout << "Console Design by Apurv P Chudasama";
        switch(choice)
        {
            case 1:
                gotoxy(x,9);
                f1.Newfile();
                break;
            /*case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                break;*/
        }
    }
}

};


//Set the whole screen colour


//main function...
int main()
{
    Layout l;
    l.ClearConsoleToColors(17,15);
    //SetConsoleTitle("C++ Project 1 by 22CS016,22CS079,22cs048/");
    l.window();

    Files f;
    l.main_window(f);
    //f.PrintFileData();
    return 0;
}