#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Header.h"
#include <fstream>
#include<string>
#include <math.h>



using namespace std;

class Words {
public:
	string word;
	int counter;
	friend ostream & operator <<(ostream&out, Words &name)
	{
		out << name.word << endl << name.counter << endl;
		return out;
	}
	friend bool operator==(Words &kelime, Words &kelime1)
	{
		return(kelime.word == kelime1.word);

	}
};

void backwards(node<Words>**n)					//Bu kısım link listte küçükten büyüğe sıralanmış olan sayıların büyükten küçüğe sıralanmasını sağlıyor.
{
	if (n == nullptr || (*n)->link == nullptr)
		return;

	node<Words> * one = *n;
	node<Words> * other = *n = one->link;
	one->link = nullptr;
	backwards(n);
	other->link = one;
}


int main()
{
	node<Words> *a, *b, *c,*e,*f,*Nodelast, *Nodefirst, *Nodecurrent, *testNode,*last, *first, *current, *test;
	bool karar = false;
	char nonAlpha[22] = { ':','"','+','#','^','~',')','(',' ',',','.','!','?','*','/','{','}','=','_','-','[',']' };
	string word, nword;
	Words myobject;
	LinkList<Words> document1, document2;
	ifstream opendocument1("document1.txt"), opendocumentiki("document2.txt"), openstop("StopWord.txt");


	do												//Burada textteki kelimeleri string olarak okuyorum ve noktalama işaretlerini kaldırıyorum.
	{
		opendocument1 >> word;
		for (int i = 0; i < word.length(); i++) {
			for (int j = 0; j < 22; j++) {
				if (nonAlpha[j] == word[i]) {
					word[i] = '\0';
				}
			}
		}
		word[0] = tolower(word[0]);				//Bundaki amaç sizin verdiğiniz yasaklı kelimelerin bazıları büyük harfle başlıyor bazıları küçük harfle başlıyordu onları da çıkartmak için.
		while (!openstop.eof())
		{
			openstop >> nword;
			if (nword == word)
			{
				karar = true;
			}
		}
		word[0] = toupper(word[0]);
		myobject.word = word;
		openstop.close();
		if (karar == true)
		{
			karar = false;
		}
		else
		{
			if (document1.search(myobject) == NULL)    // Eğer benim okuduğum kelime link listte yer alıyorsa onun counterını 1 arttırıyorum.Ancak yok ise yeni oluşturuyrum.
			{
				myobject.counter = 1;
				document1.insertLast(myobject);
			}
			else
			{
				document1.search(myobject)->info.counter++;
			}
		}
		openstop.open("StopWord.txt");

	}while (!opendocument1.eof());
	Nodelast = document1.head;
	if (document1.head == NULL || document1.head->link == NULL)
	{
		cerr << "ERROR!!" << endl;

	}
	else
	{
		do
		{
			Nodefirst = Nodelast->link;
			if (Nodefirst->info.counter < document1.head->info.counter)
			{
				Nodelast->link = Nodefirst->link;
				Nodefirst->link = document1.head;
				document1.head = Nodefirst;
			}
			else
			{
				testNode = document1.head;
				Nodecurrent = document1.head->link;
				while (Nodecurrent->info.counter < Nodefirst->info.counter)
				{
					testNode = Nodecurrent;
					Nodecurrent = Nodecurrent->link;
				}
				if (Nodecurrent != Nodefirst)
				{
					Nodelast->link = Nodefirst->link;
					Nodefirst->link = Nodecurrent;
					testNode->link = Nodefirst;
				}
				else
				{
					Nodelast = Nodelast->link;
				}
			}
		}while (Nodelast->link != NULL);
	}
backwards(&document1.head);   //Bu sıralamayı sağlayan fonksiyonu çağırıyor.
	do
	{
		opendocumentiki >> word;			//Aynı işlemler aşağıda da tekrarlanıyor.

		for (int a = 0; a < word.length(); a++) {
			for (int b = 0; b < 22; b++) {

				if (nonAlpha[b] == word[a]) {
					word[a] = '\0';
				}

			}
		}

		word[0] = tolower(word[0]);
		while (!openstop.eof())
		{

			openstop >> nword;


			if (nword == word)
			{
				karar = true;
			}


		}
		word[0] = toupper(word[0]);
		myobject.word = word;
		openstop.close();
		if (karar == true)
		{
			karar = false;
		}

		else
		{

			if (document2.search(myobject) == NULL)
			{
				myobject.counter = 1;
				document2.insertLast(myobject);
			}
			else
			{
				document2.search(myobject)->info.counter++;
			}

		}
		openstop.open("StopWords.txt");
	} while (!opendocumentiki.eof());
	last = document2.head;
	if (document2.head == NULL || document1.head->link == NULL)
	{
		cerr << "ERROR!!" << endl;
	}
	else
	{
		while (last->link != NULL)
		{
			first = last->link;
			if (first->info.counter < document2.head->info.counter)
			{
				last->link = first->link;
				first->link = document2.head;
				document2.head = first;
			}
			else
			{
				test = document2.head;
				current = document2.head->link;
				while (current->info.counter < first->info.counter)
				{
					test = current;
					current = current->link;
				}
				if (current != first)
				{
					last->link = first->link;
					first->link = current;
					test->link = first;
				}
				else
				{
					last = last->link;
				}
			}
		}
	}
	backwards(&document2.head);
	cout << document1 << endl;
	cout << document2 << endl;
	a = document1.head,b = document2.head,c = document2.head;
	int summ = 0;
	while (a != NULL) {
		b = c;
		while (b != NULL) {

			if (a->info.word == b->info.word)

				summ += a->info.counter*b->info.counter;
			b = b->link;
		}

		a = a->link;
	}



	e = document1.head;
	int linklist1Summ = 0;

   do{
		linklist1Summ += pow(e->info.counter, 2);
		e = e->link;

   } while (e != NULL);


	f = document2.head;
	int linklist2Summ = 0;

	do{
		linklist2Summ += pow(f->info.counter, 2);
		f = f->link;
	} while (f != NULL);

	double Result = 0;
	Result = summ / (sqrt(linklist1Summ)*sqrt(linklist2Summ));
	
	cout <<"Product Sum:" <<summ << endl;
	cout <<"Divider:" << (sqrt(linklist1Summ)*sqrt(linklist2Summ)) << endl;
	cout <<"Cosine similarity between two documents is  " <<Result << endl;

	
	
	
	system("PAUSE");
	return 0;
}
