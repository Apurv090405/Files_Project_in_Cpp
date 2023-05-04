//Main Project File to Sort Number and String in File
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/types.h>
using namespace std;

//Class file is have all properties of files to change in file, print in file etc..
class Files
{
    public :
    char data[100][50];
	int number;
	string name;

    //this data member is delete file from your code folder
	void DeleteFile()
	{
	    string Fn;
        int num;
        cout << "Enter the name of file : ";
        cin >> Fn;
        Fn = Fn + ".txt";
        //to use remove we can delete the file and that function return 1 if file is delete...
	/*The basic_string::c_str() is a built-in function in C++ which returns a pointer to an array that contains a null-terminated sequence of 
        characters representing the current value of the basic_string object.
        This array includes the same sequence of characters that make up the value of the 
        basic_string object plus an additional terminating null-character at the end. */
        if (remove(Fn.c_str()) != 0) {
            perror("Error deleting file");
        }
        else {
            cout << endl <<"File deleted successfully";
        }
	}

	//this member function counts the number,digits and space in file....
	void counts()
	{
	    string Fn;
        int num;
        cout << "Enter the name of file : ";
        cin >> Fn;
        Fn = Fn + ".txt";
        cout << endl;
        ifstream infile;
        infile.open(Fn);
        if(infile.fail())
        {
            cout << "Input file opening failed.\n";
            exit(1);
        }
        int charCount = 0;
        int numCount = 0;
        int spaceCount = 0;
        char ch;
        //using ctype.h libarary we can use the inbuilt function to count the numbers and char...
	/*C++ manipulator noskipws() function is used to clear the skipws format flag for the str stream. 
	When we set noskipws format flag, then it does not skip any number of whitespaces before the next input. 
	Tab spaces, blank spaces and carriage returns are considered whitespaces.*/
        while (infile >> noskipws >> ch) {
            if (isalpha(ch)) {
                charCount++;
            }
            else if (isdigit(ch)) {
                numCount++;
            }
            else if (isspace(ch)) {
                spaceCount++;
            }
        }
        infile.close();
        cout << "Number of characters: " << charCount << endl;
        cout << "Number of numbers: " << numCount << endl;
        cout << "Number of spaces: " << spaceCount << endl;
	}

	//this member function use to print the data of file...
    void PrintFileData()
    {
        string Fn;
        int num;
        cout << "Enter the name of file : ";
        cin >> Fn;
        Fn = Fn + ".txt";
        ifstream infile;
        infile.open(Fn);
        if(infile.fail())
        {
            cout << "Input file opening failed.\n";
            exit(1);
        }
        cout << endl << "Char Data Of File : " << endl;
        int i = 0;
        //to print whole data we can run loop from starting to end of file....
        while(!infile.eof())
        {
            if(data[i]!="\n")
            infile >> data[i];
            // write the data at the screen.
            cout << data[i] << endl;
            i++;
        }
        // close the opened file.
        infile.close();
    }

    //this member function search the word in file...
    void SearchWord()
    {
        string name;
        cout << "Enter the name of file : ";
        cin >> name;
        name = name + ".txt";
        ifstream fin;
        fin.open(name);
        if(fin.fail())
        {
            cout << "Input file opening failed.\n";
            exit(1);
        }
        string search;
        cout << "Enter the word to Search in File : ";
        cin  >> search;
        bool isFound=0;
        while(!fin.eof())
        {
            string temp = "";
            getline(fin,temp);
            for(int i=0;i<search.size();i++)
            {
                if(temp[i]==search[i])
                    isFound = 1;
                else
                {
                    isFound =0;
                    break;
                }
            }
            if(isFound)
            {
                cout << "Word " << search << " is Found : ";
                for(int i = search.size()+1;i<temp.size();i++)
                {
                    cout << temp[i];
                    break;
                }
            }
        }
        if(fin.eof()&&(!isFound))
        {
            cout << "Name not found!\n";
        }
        fin.close();
    }

    //this member function is print the list of names in your folder...
	void ListOffile()
	{
	    //create DIR type pointer to search in directy...
        DIR *dr;
	/*A dirent structure contains the character pointer d_name, 
	which points to a string that gives the name of a file in the directory.*/
        struct dirent *en;
        dr = opendir("."); //open all directory
        cout << "Lists of Files in Your code Folder : " << endl;
        if (dr)
        {
            int i=1;
            //readdir is read the dir
            while ((en = readdir(dr)) != NULL)
            {
                cout << endl << i << ". : "<< en->d_name;
                i++; //print all directory name
            }
            closedir(dr);//close all directory
        }
	}

	//this member function is create new file in your folder...
    void Newfile()
    {
        cout << "Enter the name of file : ";
	    cin >> name;
        cout << "Enter the number of lines you wish to enter in your file : ";
	    cin >> number;
	    name = name + ".txt";
	    cout << endl;
	    //calling openfile function to enter the data in new file....
        openFile(name,number);
    }
    private :
        //this member function is faatch data from user and store it in file...
    void openFile(string fname,int numOfLines)
    {
        // open a file in write mode.
        ofstream outfile;
        outfile.open(fname);
        if(outfile.fail())
        {
            cout << "Input file opening failed.\n";
            exit(1);
        }
        cout << "Writing to the file" << endl;
        fflush(stdin);
        for(int i=0;i<numOfLines;i++)
        {
            cout << "Enter line " << i+1 << " : ";
            fflush(stdin);
            scanf("%[^\n]%*c", data[i]);
            fflush(stdin);
        }
        //calling sorting function to sort the numbers and strings..
        sorting();
        //printing sorted data of file...
        cout << "Shorted Data Of File : " << endl;
        for(int i=0;i<numOfLines;i++)
        {
            cout << data[i] << endl;
            // write inputted data into the file.
            outfile << "\n" << data[i] ;
        }
        cout << endl << "End Of File...";
        outfile.close();
    }

    public :
    //this member function is sorting number and string using bubble short..
    void sorting()
    {
        char temp[50];
        for(int i = 0;i<number;i++)
            {
            for(int j=i+1;j<number;j++)
            {
                if(strcmp(data[i],data[j])>0)
                {
                    strcpy(temp,data[i]);
                    strcpy(data[i],data[j]);
                    strcpy(data[j],temp);
                }
            }
        }
     }
};

//this class is use to access the details of project..
class ProjectDetails
{
    public :
        //this member function print the details of project..
    void details()
    {
        cout << endl << "-----------------------------[Team Members]---------------------------"<<endl;
        cout << "22CS016 : Apurv Chudasama." << endl;
        cout << "22CS048 : Jayraj Parmar." << endl;
        cout << "22CS079 : Raj Shah." << endl;
        cout << endl << "-----------------------------[Team Experience]------------------------"<< endl;
        cout << "Raj and Jayraj are made the logic of shorting string and manage it on" << endl << "Files.Apurv made some console Design by using Windows Library. We can" << endl;
        cout << "deside the logics and all. At last the One Main Project is made and " << endl;
        cout << "after that in main code total 48 error are occur we can solve it in 2" << endl;
        cout << "hours and finally we can give our best..." << endl;
        cout << endl << "------------------------------[Refernces]-----------------------------"<<endl;
        cout << "1. Microsoft Learn : Windows.h file" << endl;
        cout << "2. E. Balaguruswami : file managment" << endl;
        cout << "3. Greeks for greeks : colour code + windows.h examples" << endl;
        cout << "4. Mentors : Doubts and some examples" << endl;
        cout << "5. C++ Primer : references of file manegment";
    }
};

//the layout class is derived class of 2 class just because access the properties...
class Layout : public Files, public ProjectDetails
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

//Create the function to clear console to white color..
void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     //Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     //This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     //A return value... indicating how many chars were written
     //not used but we need to capture this since it will be
     //written anyway (passing NULL causes an access violation).
     DWORD count;
     //This is a structure containing all of the console info
     // it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          //This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

//create the function to set background color
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
    for(i = 0; i < 120; i++){
        gotoxy(i,0);
        printf("%c",205);
    }
    //2nd vertical line
    for(i = 0; i < 120; i++){
        gotoxy(i,7);
        if(i == 70){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    //horizontal line
    for(i = 8; i < 30; i++){
        gotoxy(70,i);
        printf("%c",186);
    }

    //last vertical line...
    for(i = 0; i < 120; i++){
        gotoxy(i,29);
        if(i == 70){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
}

//2nd windwow clear function
void clearWindow(){
    int i,j;
    for(i = 0; i < 69; i++)
        {
        for(j = 8; j < 50; j++){
            gotoxy(i,j);
            cout << " ";
        }
    }
}

//Fill the details in window 1
void window()
{
    drawRectangle();
    gotoxy(45,1);
    SetColor(0);
    cout << "Chember Of Coders";
    gotoxy(27,2);
    SetColor(9);
    cout << "CE145 : Project 1 : Numbers and String Shorting In Files" << endl;
    gotoxy(30,3);
    SetColor(500);
    cout << "Chandubhai S Patel institute Of Technology(CSPIT)" << endl;
    gotoxy(33,4);
    //gotoxy(13,24);
    cout << "Department of Computer Science & Engg.(CSE)" << endl;
    gotoxy(37,5);
    SetColor(9);
    cout << "Created By 22CS016,22CS048,22CS079";
    SetColor(2);
    gotoxy(28,6);
    cout << "Mentors : Abhishek Patel, Srushti Gajjar, Vaibhavi patel";
}

//fill details in window 2
void main_window(Files &f1)
{
    int choice;
    SetColor(20);
    int x = 0;
    gotoxy(71,8);
    cout << "------------------[Choices]----------------------";
    gotoxy(72,10);
    SetColor(16);
    cout << "1. Adding and Shorting data in file" << endl;
    gotoxy(72,12);
    cout << "2. Lists Of Files" << endl;
    gotoxy(72,14);
    cout << "3. Print Data Of file" << endl;
    gotoxy(72,16);
    cout << "4. Search Word in File" << endl;
    gotoxy(72,18);
    cout << "5. Count total Char & Digits in file" << endl;
    gotoxy(72,20);
    cout << "6. Delete exciting file" << endl;
    gotoxy(72,22);
    cout << "7. Project Details" << endl;
    gotoxy(71,27);
    SetColor(2);
    cout << "-------------------------------------------------";
    gotoxy(71,25);
    cout << "-------------------------------------------------";
    SetColor(2);
    gotoxy(72,28);
    cout << "Console Design by Apurv P Chudasama";

    //using infinity while loop the user can enter multiple choice...
    while(1)
    {
        gotoxy(72,26);
        cout << "Enter Choice : ";
        gotoxy(86,26);
        cin >> choice;
        gotoxy(x,8);
        clearWindow();
        //using switchcase statment we can provide the choice as user input...
        switch(choice)
        {
            case 1:
                SetColor(2);
                gotoxy(15,9);
                cout << "1. Adding and Shorting data in file" << endl;
                SetColor(500);
                gotoxy(x,11);
                f1.Newfile();
                break;
            case 2:
                SetColor(2);
                gotoxy(25,9);
                cout << "2. Lists Of Files" << endl;
                SetColor(500);
                gotoxy(x,11);
                ListOffile();
                break;
            case 3:
                SetColor(2);
                gotoxy(22,9);
                cout << "3. Print Data Of file" << endl;
                SetColor(500);
                gotoxy(x,11);
                f1.PrintFileData();
                break;
            case 4:
                SetColor(2);
                gotoxy(22,9);
                cout << "4. Search Word in File" << endl;
                SetColor(500);
                gotoxy(x,11);
                f1.SearchWord();
                break;
            case 5:
                SetColor(2);
                gotoxy(15,9);
                cout << "5. Count total Char & Digits in file" << endl;
                SetColor(500);
                gotoxy(x,11);
                counts();
                break;
            case 6:
                SetColor(2);
                gotoxy(20,9);
                cout << "6. Delete exciting file" << endl;
                SetColor(500);
                gotoxy(x,11);
                DeleteFile();
                break;
            case 7:
                SetColor(2);
                gotoxy(20,9);
                cout << "    -:Chember Of Coders :-   ";
                SetColor(500);
                gotoxy(x,10);
                details();
                break;
            default:
                SetColor(2);
                gotoxy(x,30);
                cout << "404! Error!" << endl << endl;
                cout << "you Enter Wrong Choice so i can stop Program execution..." << endl;
                int rating;
                cout << "Enter your rating out of 5 : ";
                cin >> rating;
                cout << "Thank you for use the Program";
                exit(1);
        }
    }
}
};

//Set the whole screen colour
//main function...
int main()
{
    Layout l;
    l.ClearConsoleToColors(17,15); // set the color...
    SetConsoleTitle("C++ Project 1 by 22CS016,22CS079,22cs048"); //set title of console
    l.window();
    Files f;
    l.main_window(f);
    return 0;
}
