//Federico Pierotti e Matteo Quaranta
#include<iostream>
#include<string>
#include<string.h>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<fstream>
#include<cmath>
using namespace std;
const int DIM=100;
const int DIME=7;

struct elem
{
	string orario;
	int sc;
	elem* succ;
};


struct alunno
{
	string codice;
	string cognome;
	string nome;
	char sesso;
	int classe;
	char sezione;
};


struct esami
{
	int N;
	string descrizione;
};

struct iscritti
{
    char codice[50];
    char cognome[50];
    char nome[20];
    int classe;
    char sezione;
};


//prototipi
void num(int&a);
void ins(string&n, int MIN, int MAX, string s);
void input(alunno al[], int a, int c);
void menu(int&scelta);
void risRand(int mat[DIM][DIME], int a, int c);
void visuaMat(int mat[DIM][DIME], alunno al[DIM], int a, int c);
void insCoda(alunno al[], int mat[DIM][DIME], int &a, int c);
void visuaP(alunno al[], int a, int c, int mat[DIM][DIME], esami d[]);
void elimina(alunno al[], int mat[DIM][DIME], int&a, int c);
void med(alunno al[], int mat[DIM][DIME], int a, int c, float media[]);
void visuaCl(alunno al[], int mat[DIM][DIME], int a, int c, float media[]);
int num_al(alunno al[], int mat[DIM][DIME], int a, int c, int x);
int conta(alunno al[], int a);
int conta2(alunno al[], int a);
int min(alunno al[], int mat[DIM][DIME], int a, int c, int y);
int max(alunno al[], int mat[DIM][DIME], int a, int c, int x);
bool codice(alunno al[], int mat[DIM][DIME], int a, int c, string y);
void attestato(alunno al[], esami d[], int mat[DIM][DIME], int a, int c, string cod);
void vscelta(int sc[]);
void convChar(string s,char v[]); 
void creaFile(alunno al[],int i);
void visua_file();


int main()
{
	fstream f;
	srand(time(NULL));
	int mat[DIM][DIME];
	int scelta;
	int c=7;
	int a;
	float media[DIM];
	int x;
	int n;
	string y;
	string cod;
	elem *p0=new elem;
	int sc[13]={0};

	



	alunno al[DIM]={{"111","Smith","John",'M',4,'C'},
					{"222","Johnson","Emily",'F',2,'D'},
					{"333","Brown","Michael",'M',5,'E'},
					{"444","Davis","Sophia",'F',3,'D'},
					{"555","Miller","James",'M',1,'E'},
					{"666","Wilson","Olivia",'F',4,'C'},
					{"777","Moore","Benjamin",'M',3,'D'},
					{"888","Anderson","Isabella",'F',2,'C'},
					{"999","Taylor","Ethan",'M',5,'E'},
					{"000","Thomas","Ava",'F',1,'E'}};

	esami d[7]={
	{1,"Computer Essentials"},
	{2,"Online Essentials"},
	{3,"Word Processing"},
	{4,"Spreadsheet"},
	{5,"Online Collaboration"},
	{6,"Presentation"},
	{7,"IT Security Specialised Level"},
	};

	if(al[0].codice!="")	//se il vettore v è già stato inizializzato genero la matrice e n acquisisce R
	{
		a=10;
		risRand(mat, a, c); //genero la matrice
		n=a;
	}


	do
	{


		menu(scelta);

		sc[scelta-1]=sc[scelta-1]+1; //per contare il numero di volte che è stata fatta una determinata scelta

		
		switch(scelta)
		{
			case 0: return 0;
				break;

			case 1:num(a);
			cin.ignore();
			input(al, a, c);
			n=a;
					risRand(mat,a,c);
				break;

			case 2: insCoda(al,mat,a,c);
				break;

			case 3: elimina(al, mat, a,c);
				break;

			case 4: visuaP(al,a,c,mat,d);
				break;

			case 5:	med(al,mat,a,c,media);
					if(a>3)
					{
						visuaCl(al,mat,a,c,media);
					}
					else
					{
						cout<<"non ci sono abbastanza alunni "<<endl;
					}
				break;

			case 6: if(a!=0)
					{
						visuaMat(mat,al,a,c);
					}
					else
					{
						cout<<"non sono presenti studenti "<<endl;
					}

				break;

			case 7:
					cout<<"inserire il codice SKILL dello studente "<<endl;
					getline(cin,cod);
					attestato(al,d,mat,a,c,cod);
				break;

			case 8: cout<<"inserisci il codice "<<endl;
					cin>>x;
					cout<<"i partecipanti "<<num_al(al,mat,a,c,x)<<endl;
					cout<<endl;
				break;

			case 9:
					cout<<"il numero dei maschi e:"<<conta(al,a)<<endl;
					cout<<"il numero delle femmine e:"<<conta2(al,a)<<endl;
					cout<<endl;
				break;

			case 10: cout<<"inserire il codice dell'esame (1-7)"<<endl;
					cin>>x;
					cout<<"il risultato minimo e:"<<min(al,mat,a,c,x)<<endl;
					cout<<"il risultato massimo e:"<<max(al,mat,a,c,x)<<endl;
					cout<<endl;
				break;

			case 11: cout<<"inserire il codice (es: 123)"<<endl;
					getline(cin, y);
    		        if(codice(al, mat, a, c, y)==true)
					{
						cout<<"trovato"<<endl;
					}
    		        else
					{
						cout<<"non trovato"<<endl;
					}
				cout<<endl;
				break;

			case 12: vscelta(sc);


				break;
            case 13:
                
                    
                remove("ISCRITTI.dat");
				
				for(int i=0;i<a;i++)
				{
					creaFile(al,i);
				}
				
				visua_file();
                break;

		}
		
		system("pause");
		system("cls");
    }
    while(scelta!=0);

}



void num(int&a)
{
	cout<<"inserire la numerosita degli alunni:  ";
	cin>>a;
	while(a<1 or a>DIM)
	{
		cout<<"reinserire:  ";
		cin>>a;
	}
}

void ins(string & n, int MIN, int MAX, string s)
{
	cout<<s<<":  ";
	getline(cin,n);
	int num=n.length();
	while(num<MIN or num>MAX)
	{
		cout<<"reinserire:  ";
		cin.ignore();
		getline(cin,n);
		num=n.length();
	}
}



void input(alunno al[], int a, int c)
{
	for(int i=0;i<a;i++)
	{
		ins(al[i].codice,0,3,"inserire il codice");
		ins(al[i].cognome,0,20, "inserire il cognome");
		ins(al[i].nome,0,20,"inserire il nome");
		cout<<"inserire il sesso:  ";
		cin>>al[i].sesso;
		al[i].sesso=toupper(al[i].sesso);
		while(al[i].sesso!='M' and al[i].sesso!='F')
		{
			cout<<"reinserire:  ";
			cin>>al[i].sesso;
		}
		cout<<"inserire la classe:  ";
		cin>>al[i].classe;
		while(al[i].classe<1 or al[i].classe>5)
		{
			cout<<"reinserire:  ";
			cin>>al[i].classe;
		}
		cout<<"inserie la sezione:  ";
		cin>>al[i].sezione;
		while(toupper(al[i].sezione)!='C' and toupper(al[i].sezione)!='D' and toupper(al[i].sezione)!='E')
		{
			cout<<"reinserire:  ";
			cin>>al[i].sezione;
		}
		cin.ignore();
	}
}

void menu(int&scelta)
{
	cout<<"|                                                MENU'                                           |"<<endl;
	cout<<"| 0. terminare programma                                                                         |"<<endl;
	cout<<"| 1. Inserimento dati e riempimento randomico della matrice-risultati                            |"<<endl;
	cout<<"| 2. Inserimento in coda di un nuovo                                                             |"<<endl;
	cout<<"| 3. Eliminazione di uno studente                                                                |"<<endl;
	cout<<"| 4. Visualizzazione degli esami e dei relativi punteggi ottenuti da uno studente                |"<<endl;
	cout<<"| 5. Calcolo delle medie dei punteggi di ogni studente                                           |"<<endl;
	cout<<"| 6. Visualizzazione dei risultati in una tabella                                                |"<<endl;
	cout<<"| 7. Stampare l'attestato di partecipazione di uno studente                                      |"<<endl;
	cout<<"| 8. Numero partecipanti ad una esame di cui si indica il codice                                 |"<<endl;
	cout<<"| 9. Numero maschi e numero femmine presenti nell'archivio                                       |"<<endl;
	cout<<"| 10. Risultato Massimo e Minimo di una esame di cui si indica il codice- esame                  |"<<endl;
	cout<<"| 11. Ricerca di uno studente di cui si indica la CODICE SKILL                                   |"<<endl;
	cout<<"| 12. Visualizza in forma tabellare ogni opzione del menu e il numero di volte che e stata scelta|"<<endl;
	cout<<"| 13. creazione e visualizzazione file- iscritti                                                 |"<<endl;
	cout<<"+------------------------------------------------------------------------------------------------+"<<endl;
	cin>>scelta;
	while(scelta<0 or scelta>13)
	{
		cout<<"reinserire:  ";
		cin>>scelta;
	}
	cin.ignore();
	
	system("cls");

}

void risRand(int mat[DIM][DIME], int a, int c)
{

	for(int i=0;i<a;i++)
	{
		for(int j=0;j<c;j++)
		{
			mat[i][j]=-1+rand()%(100+1+1);
		}
	}
}

void visuaMat(int mat[DIM][DIME], alunno al[DIM], int a, int c)
{
	cout<<"            ";
	for(int g=0;g<c;g++)
	{
		cout<<setw(12)<<"corso "<<g+1;
	}
	cout<<endl;
	for(int i=0;i<a;i++)
	{
		cout<<setw(12)<<al[i].cognome;
		for(int j=0;j<c;j++)
		{
			cout<<setw(12)<<mat[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}

void insCoda(alunno al[], int mat[DIM][DIME], int &a, int c)
{
		ins(al[a].codice,0,3,"inserire il codice");
		ins(al[a].cognome,0,20, "inserire il cognome");
		ins(al[a].nome,0,20,"inserire il nome");
		cout<<"inserire il sesso:  ";
		cin>>al[a].sesso;
		al[a].sesso=toupper(al[a].sesso);
		while(toupper(al[a].sesso)!='M' and toupper(al[a].sesso)!='F')
		{
			cout<<"reinserire:  ";
			cin>>al[a].sesso;
		}
		cout<<"inserire la classe:  ";
		cin>>al[a].classe;
		while(al[a].classe<1 or al[a].classe>5)
		{
			cout<<"reinserire:  ";
			cin>>al[a].classe;
		}
		cout<<"inserie la sezione:  ";
		cin>>al[a].sezione;
		while(toupper(al[a].sezione)!='C' and toupper(al[a].sezione)!='D' and toupper(al[a].sezione)!='E')
		{
			cout<<"reinserire:  ";
			cin>>al[a].sezione;
		}
		for(int j=0;j<c;j++)
		{
			mat[a][j]=-1+rand()%(100+1+1);
		}
		cin.ignore();
		a++;
		cout<<endl;
}

void visuaP(alunno al[], int a, int c, int mat[DIM][DIME], esami d[])
{
	int i=0;
	int k=0;
	string cogn;
	cout<<"inserire il cognome dello studente:  ";
	getline(cin,cogn);
	cout<<endl;

	while(i<a and k==0)
	{
		if(al[i].cognome==cogn)
		{
			k=1;
			for(int h=0;h<c;h++)
			{
				cout<<setw(12.5)<<"corso "<<h+1;
			}
			cout<<endl;
			cout<<al[i].cognome;
			for(int j=0;j<c;j++)
			{
				cout<<setw(12)<<mat[i][j];
			}
			cout<<endl;
		}
		cout<<endl;
		i++;
	}

	if(k==0)
	{
		cout<<"non esiste lo studente "<<endl;
	}
}

void elimina(alunno al[], int mat[DIM][DIME], int&a, int c)
{
	int i=0;
	int h=a;
	string x;
	cout<<" inserire il cognome dello studente da eliminare:  ";
	getline(cin,x);
	cout<<endl;
	while(i<a and h==a)
	{
		if(al[i].cognome==x)
		{
			for(int j=i;j<a;j++)
			{
				al[j].cognome=al[j+1].cognome;
				al[j].nome=al[j+1].nome;
				for(int k=0;k<c;k++)
				{
					mat[j][k]=mat[j+1][k];
				}
			}
			a--;
		}
		i++;
	}
	if(h==a)
	{
		cout<<"lo studente non è presente "<<endl;
	}
}

void med(alunno al[], int mat[DIM][DIME], int a, int c, float media[])
{
	for(int i=0;i<a;i++)
	{
		float somma=0;
		for(int j=0;j<c;j++)
		{
			somma=somma+mat[i][j];
		}
		media[i]=somma/7;
	}
}

void visuaCl(alunno al[], int mat[DIM][DIME], int a, int c, float media[])
{
	float max1=media[0];
	float max2=0;
	float max3=0;
	int p=0;
	int s;
	int t;
	for(int i=1;i<a;i++)
	{
		if(media[i]>max1)
		{
			max1=media[i];
			p=i;
		}
	}
	for(int i=0;i<a;i++)
	{
		if(media[i]>max2 and media[i]!=max1)
		{
			max2=media[i];
			s=i;
		}
	}
	for(int i=0;i<a;i++)
	{
		if(media[i]>max3 and media[i]!=max2 and media[i]!=max1)
		{
			max3=media[i];
			t=i;
		}
	}

	cout<<endl;
	cout<<endl;
	cout<<"1^ classificato "<<al[p].nome<<" "<<al[p].cognome<<" con la media di "<<max1<<endl;
	cout<<"2^ classificato "<<al[s].nome<<" "<<al[s].cognome<<" con la media di "<<max2<<endl;
	cout<<"3^ classificato "<<al[t].nome<<" "<<al[t].cognome<<" con la media di "<<max3<<endl;
	cout<<endl;
	cout<<endl;
}

	int num_al(alunno al[], int mat[DIM][DIME], int a, int c, int x)
	{
		int n;
		if(a==0)
		{
			n=0;
		}
		else
		{
			if(mat[a-1][c-1]!=-1)
			{
				n=1+num_al(al, mat, a-1, c, x);
			}
			else
			{
				n=num_al(al, mat, a-1, c, x);
			}
		}
		return n;
	}

	int conta(alunno al[], int a)
	{
		int c;
		if(a==0)
		{
			c=0;
		}
		else
		{
			if(al[a-1].sesso ==toupper('m'))
			{
				c=1+conta(al,a-1);
			}
			else
			{
				c=conta(al,a-1);
			}
		}
		return c;
	}

	int conta2(alunno al[], int a)
	{
		int c;
		if(a==0)
		{
			c=0;
		}
		else
		{
			if(al[a-1].sesso ==toupper('f'))
			{
				c=1+conta2(al,a-1);
			}
			else
			{
				c=conta2(al,a-1);
			}
		}
		return c;
	}

	int min(alunno al[], int mat[DIM][DIME], int a, int c, int x)
	{	int m;

		if(a==1)
		{
			m=mat[0][x-1];
		}
		else
		{
			m=min(al,mat,a-1,c,x);
			if(mat[a-1][x-1]<m)
			{
				m=mat[a-1][x-1];
			}
		}
		return m;
	}

	int max(alunno al[], int mat[DIM][DIME], int a, int c, int x)
	{	int m;

		if(a==1)
		{
			m=mat[0][x-1];
		}
		else
		{
			m=max(al,mat,a-1,c,x);
			if(mat[a-1][x-1]>m)
			{
				m=mat[a-1][x-1];
			}
	}
	return m;
}

bool codice(alunno al[], int mat[DIM][DIME], int a, int c, string y)
{
	bool flag;
    if(a==0)
	{
		flag=false;
	}
    else
	{
    if(y==al[a-1].codice)
    {
    	flag=true;
	}
	else
	{
		flag=codice(al, mat, a-1, c, y);
	}
	}

    return flag;
}






string mese(int m) //restituisce il nome del mese in base al numero
{
	string s;
	
	switch(m)
	{
		case 1:
			s="gennaio";
		break;
		
		case 2:
			s="febbraio";
		break;
		
		case 3:
			s="marzo";
		break;
		
		case 4:
			s="aprile";
		break;
		
		case 5:
			s="maggio";
		break;
		
		case 6:
			s="giugno";
		break;
		
		case 7:
			s="luglio";
		break;
		
		case 8:
			s="agosto";
		break;
		
		case 9:
			s="settembre";
		break;
		
		case 10:
			s="ottobre";
		break;
		
		case 11:
			s="novembre";
		break;
		
		case 12:
			s="dicembre";
		break;
		
		
		
	}
	return s;
}



    void attestato(alunno al[], esami d[], int mat[DIM][DIME], int a, int c, string cod)
    {
    	int g, an;
		string m;
	
    	time_t ttime = time(0);
    	tm *local_time = localtime(&ttime);
    	an = 1900 + local_time->tm_year;
    	m = mese(1 + local_time->tm_mon);
    	g = local_time->tm_mday;
    
		for(int i=0;i<a;i++)
    	{
    		for(int j=0;j<c;j++)
    		{

    		if(al[i].codice==cod and mat[i][j]!=-1)
    		{
   
    
    
    cout << "****************************************************************************************" << endl;
    cout << "*                                                              IIS Blaise Pascal       *" << endl;
    cout << "*"<<setw(14)<<" "<<left<<setw(15)<<al[i].cognome<<left<<setw(25)<<al[i].nome<<right<<setw(4)<<al[i].classe<<al[i].sezione<<right<<setw(28)<<"*"<<endl;
    cout << "*                                                                                      *" << endl;
    cout << "*      Esame: " <<left<<setw(30)<<d[j].descrizione<<right<<setw(44)<< "*" << endl;
    cout << "*      Punteggio ottenuto:"<<setw(3)<<mat[i][j]<<setw(59)<<   "*" << endl;
    cout << "*                                                                                      *" << endl;
    cout << "*"<<setw(65)<<" "<<"("<<g<<"/"<<m<<"/"<<an<<")"<<setw(6)<< "*" << endl;
    cout << "*                                                                                      *" << endl;
    cout << "****************************************************************************************" << endl;
			}
		}

	}
	cout<<endl;
}

void ins(elem*&p0, int scelta)
{
	time_t t = time(NULL);
	struct tm *ltm = localtime(&t);
	elem* p;
	p=new elem;
	(*p).sc=scelta;
	char buffer[10];
	strftime(buffer, 10, "%H:%M:%S", ltm);
	(*p).orario = string(buffer);
	cout<<(*p).orario<<endl;
	p=(*p).succ;
}

void vscelta(int sc[])
{

	cout<<setw(9)<<"Scelte "<<setw(9)<<"Volte";
	
	cout<<endl;

	for(int i=0; i<13; i++)
	{
		cout<<setw(6)<<i+1<<setw(11)<<sc[i]<<endl;
	}
	
}


void convChar(string s,char v[]) 
{
	for(int i=0;i<20;i++)
	{
		v[i]=s[i];
	}
} 

void creaFile(alunno al[],int i)	
{
	iscritti buff;
	fstream f;
	
	f.open("ISCRITTI.dat",ios::app|ios::binary);
	
	convChar(al[i].cognome,buff.cognome);
	convChar(al[i].nome,buff.nome);
	convChar(al[i].codice,buff.codice);
	
	buff.classe=al[i].classe;
	buff.sezione=al[i].sezione;
	
	f.write((char*)& buff,sizeof(buff));
	f.close();
}

void visua_file()
{
	iscritti buff;
	fstream f;
	
	f.open("ISCRITTI.dat",ios::in|ios::binary);
	
	cout<<left<<setw(15)<<"Cognome"<<left<<setw(15)<<"Nome"<<left<<setw(8)<<"Codice"<<left<<setw(8)<<"Classe"<<left<<setw(8)<<"Sezione"<<endl;
	
	f.read((char*)& buff,sizeof(buff));
	
	while(!f.eof())
	{
		cout<<left<<setw(15)<<buff.cognome<<left<<setw(15)<<buff.nome<<left<<setw(8)<<buff.codice<<left<<setw(8)<<buff.classe<<left<<setw(8)<<buff.sezione<<endl;
		f.read((char*)& buff,sizeof(buff));
	}
	f.close();
}







