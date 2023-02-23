/*Aplicatie pentru gestiunea conturilor bancare pentru persoane fizice de la nivelul unei filiale bancare; 
aplicația permite:
deschidere de cont, 
depuneri si retrageri bani, 
închiderea de cont, 
transfer de bani intre conturi, 
calcul total disponibil la nivel de persoanaă care deține mai multe conturi.*/

/*
 Proiect realizat de Nita Sorin Alexandru
 Profesor coordonator: Barbulescu Alexandru
 Grupa: 1057-D
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h> // am gasit pe net informatii despre aceasta ca sa pot genera data si ora curenta pt fiecare tranzactie.


using namespace std;

class Clienti_Filiala {
private:

    const unsigned int client_id;
	string client_cnp = "0000000000000";
    char* client_nume = nullptr;
    unsigned int client_data_nastere[3] = { 1, 1, 2000 }; // format: { DD, MM, YYYY }
    unsigned int client_nr_conturi_detinute = 0;
    string client_numar_telefon = "Inexistent";

    static int clienti_nr_total;


public:
    
    // 2 constructori

    Clienti_Filiala(string _client_cnp, const char* _client_nume, int zi, int luna, int an, string _client_numar_telefon) :
        client_id(++clienti_nr_total), client_nr_conturi_detinute(0)
    {

        client_nume = new char[strlen(_client_nume) + 1];
        strcpy_s(client_nume, strlen(_client_nume) + 1, _client_nume);

        client_data_nastere[0] = zi;
		client_data_nastere[1] = luna;
		client_data_nastere[2] = an;
		
		client_numar_telefon = _client_numar_telefon;
		client_cnp = _client_cnp;

    }
	
	Clienti_Filiala() : client_id(++clienti_nr_total) {
		client_nume = new char[1];
		string client_cnp = "0000000000000";
		strcpy_s(client_nume, 1, "");
		
		client_data_nastere[0] = 1;
		client_data_nastere[1] = 1;
		client_data_nastere[2] = 2000;

		client_nr_conturi_detinute = 0;
		string client_numar_telefon = "Inexistent";
		
	}

    // constructor de copiere
	Clienti_Filiala(const Clienti_Filiala& client) :
		client_id(client.client_id), client_nr_conturi_detinute(client.client_nr_conturi_detinute)
	{
		if (client_nume != nullptr) {
			delete[] client_nume;
		}

		client_cnp = client.client_cnp;
		
		client_nume = new char[strlen(client.client_nume) + 1];
		strcpy_s(client_nume, strlen(client.client_nume) + 1, client.client_nume);

		client_data_nastere[0] = client.client_data_nastere[0];
		client_data_nastere[1] = client.client_data_nastere[1];
		client_data_nastere[2] = client.client_data_nastere[2];
		
		client_numar_telefon = client.client_numar_telefon;

		clienti_nr_total++;
	}

    // destructor
    ~Clienti_Filiala() {
		if (client_nume != nullptr) {
			delete[] client_nume;
		}

		clienti_nr_total--;
    }
    
    //operator = de copiere
	Clienti_Filiala& operator=(const Clienti_Filiala& client) {
		if (this != &client) {
			if (client_nume != nullptr) {
				delete[] client_nume;
			}

			client_cnp = client.client_cnp;

			client_nume = new char[strlen(client.client_nume) + 1];
			strcpy_s(client_nume, strlen(client.client_nume) + 1, client.client_nume);

			client_data_nastere[0] = client.client_data_nastere[0];
			client_data_nastere[1] = client.client_data_nastere[1];
			client_data_nastere[2] = client.client_data_nastere[2];

			client_nr_conturi_detinute = client.client_nr_conturi_detinute;
		}
		return *this;
	}

	// << si >>
	
	friend ostream& operator<<(ostream& out, const Clienti_Filiala& client) {
		out << "ID client: " << client.client_id << endl;
		out << "Nume client: " << client.client_nume << endl;
		out << "CNP client: " << client.client_cnp << endl;
		out << "Data nasterii: " << client.client_data_nastere[0] << "." << client.client_data_nastere[1] << "." << client.client_data_nastere[2] << endl;
		out << "Numar de telefon: " << client.client_numar_telefon << endl;
		out << "Numar de conturi detinute: " << client.client_nr_conturi_detinute << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Clienti_Filiala& client) {
		cout << "Nume: ";
		char temp[100];
		//in >> temp;
		in.ignore(); //flush pentru a nu se suprapune cu cin.getline
		in.getline(temp, 100); 

		if (client.client_nume != nullptr) {
			delete[] client.client_nume;
		}
		client.client_nume = new char[strlen(temp) + 1];
		strcpy_s(client.client_nume, strlen(temp) + 1, temp);

		cout << "CNP: ";
		in >> client.client_cnp;

		cout << "Data nasterii: ZI LUNA AN: ";
		in >> client.client_data_nastere[0] >> client.client_data_nastere[1] >> client.client_data_nastere[2];

		cout << "Numar de telefon: ";
		in >> client.client_numar_telefon;

		return in;
	}


	// metode generice preluare/afisare a atributelor


	void afisare_date_client() {
		cout << "ID Client: " << client_id << endl;
		cout << "Nume Client: " << client_nume << endl;
		cout << "CNP Client: " << client_cnp << endl;
		cout << "Data nasterii: " << client_data_nastere[0] << "." << client_data_nastere[1] << "." << client_data_nastere[2] << endl;
		cout << "Numar de telefon: " << client_numar_telefon << endl;
		cout << "Numar de conturi detinute: " << client_nr_conturi_detinute << endl;
	}

	static void afisare_nr_clienti() {
		cout << "Contor clienti: " << clienti_nr_total << endl;
	}

	// functii accesor 
	int get_client_id() {
		return client_id;
	}
	
	char* get_client_nume() {
		return client_nume;
	}

	string get_client_cnp() {
		return this->client_cnp;
	}
	
	int get_client_data_nastere() {
		return client_data_nastere[0], client_data_nastere[1], client_data_nastere[2];
	}
	
	int get_client_nr_conturi_detinute() {
		return client_nr_conturi_detinute;
	}
	
	string get_client_numar_telefon() {
		return client_numar_telefon;
	}

	void set_client_nume(char nume[100]) {
		if (client_nume != nullptr) {
			delete[] client_nume;
		}
		client_nume = new char[strlen(nume) + 1];
		strcpy_s(client_nume, strlen(nume) + 1, nume);
	}

	void set_client_cnp(string cnp) {
		if (cnp.length() == 13) {
			client_cnp = cnp;
		}
		else {
			cout << "CNP invalid!" << endl;
		}
	}

	void set_client_data_nastere(int zi, int luna, int an) {
		if ((zi >= 1 && zi <= 31) && (luna >= 1 && luna <= 12) && (an > 1900 && an < 2023)) {
			client_data_nastere[0] = zi;
			client_data_nastere[1] = luna;
			client_data_nastere[2] = an;
		}
	}

	void set_client_nr_conturi_detinute(int nr_conturi) {
		if (nr_conturi >= 0) { //desi e putin ambiguu deoarece am definit variabila ca fiind unsigned de int, am adaptat verificarea conform cerintei.
			client_nr_conturi_detinute = nr_conturi;
		}
	}
	
	void set_client_numar_telefon(string numar_telefon) {
		if (numar_telefon != "") {
			client_numar_telefon = numar_telefon;
		}
	}

	void creare_client_deschidere_cont(string _cnp) {
		cout << "Nume: ";
		char temp[100];
		cin.ignore();
		cin.getline(temp, 100);
		set_client_nume(temp);

		set_client_cnp(_cnp);
		
		cout << "Data nasterii (DD MM YYYY): ";
		int zi, luna, an;
		cin >> zi >> luna >> an;
		set_client_data_nastere(zi, luna, an);
		
		string numar_telefon;
		cout << "Numar de telefon: ";
		cin >> numar_telefon;
		set_client_numar_telefon(numar_telefon);
		
		cout << "Ati fost inregistrat cu succes in baza de date! Trecem mai departe pentru deschiderea contului!" << endl;
		
	}
	
	//**fisiere text**
	//salvare
	static void clienti_salvare_fisier(vector<Clienti_Filiala> clienti) {
		ofstream fisier("clienti.txt");

		fisier << clienti.size() << endl;

		for (int i = 0; i < clienti.size(); i++) {
			fisier << clienti[i].client_id << "\n" << clienti[i].client_cnp << "\n" << clienti[i].client_data_nastere[0] << "\n" << clienti[i].client_data_nastere[1] << "\n" << clienti[i].client_data_nastere[2] << "\n" << clienti[i].client_nr_conturi_detinute << "\n" << clienti[i].client_numar_telefon << "\n" << clienti[i].client_nume << endl;
		}

	}
	
	//incarcare
	static vector<Clienti_Filiala> clienti_incarcare_fisier() {
		vector<Clienti_Filiala> clienti;
		ifstream fisier("clienti.txt");

		int marime;
		fisier >> marime;

		for(int i = 0; i < marime; i++) {
			//while (fisier.good()) {
			unsigned int id;

			string cnp;
			int data_nastere[3];
			int nr_conturi;
			string numar_telefon;
			char nume[100];

			//fisier >> id >> cnp >> data_nastere[0] >> data_nastere[1] >> data_nastere[2] >> nr_conturi >> numar_telefon >> nume;

			fisier >> id;
			fisier >> cnp;
			fisier >> data_nastere[0];
			fisier >> data_nastere[1];
			fisier >> data_nastere[2];
			fisier >> nr_conturi;
			fisier >> numar_telefon;
			fisier.getline(nume, 100);
			fisier.getline(nume, 100);

			clienti.push_back(Clienti_Filiala(cnp, nume, data_nastere[0], data_nastere[1], data_nastere[2], numar_telefon));


		}
		fisier.close();
		return clienti;
	}
	
};
int Clienti_Filiala::clienti_nr_total = 0;



class Conturi_Bancare { //legatura cu clasa Clienti_Filiala, deoarece un client poate avea mai multe conturi bancare
private:
    const unsigned int cont_id;
    char* cont_IBAN = nullptr;
    double cont_sold = 0.0;
	unsigned int cont_data_expirare[3] = { 0,0,0 }; //vector de 3 pentru salvarea datei.
	string cont_pin = "0000"; // 4 caractere format
    unsigned int cont_id_client = 0;
	unsigned int cont_numar_tranzactii = 0;
	bool cont_activ = false;

    static unsigned int cont_nr_total;

public:

	//constructori
	Conturi_Bancare() :cont_id(++cont_nr_total) {
		cont_IBAN = new char[strlen("RO00BANC0000000000000000") + 1];
		strcpy_s(cont_IBAN, strlen("RO00BANC0000000000000000") + 1, "RO00BANC0000000000000000");
		cont_sold = 0.0;
		cont_data_expirare[0] = 0;
		cont_data_expirare[1] = 0;
		cont_data_expirare[2] = 0;
		cont_pin = "0000";
		cont_id_client = 0;
		cont_numar_tranzactii = 0;
		cont_activ = false;

	}

	Conturi_Bancare(const char* _cont_IBAN, double _cont_sold, int zi, int luna, int an, string _cont_pin, unsigned int _cont_id_client, bool _cont_activ) :cont_id(++cont_nr_total) {
		if (_cont_IBAN != nullptr) {
			cont_IBAN = new char[strlen(_cont_IBAN) + 1];
			strcpy_s(cont_IBAN, strlen(_cont_IBAN) + 1, _cont_IBAN);
		}
		if (_cont_sold >= 0) {
			cont_sold = _cont_sold;
		}
		if ((zi >= 1 && zi <= 31) && (luna >= 1 && luna <= 12) && (an > 2020 && an < 2040)) {
			cont_data_expirare[0] = zi;
			cont_data_expirare[1] = luna;
			cont_data_expirare[2] = an;
		}
		if (_cont_pin != "") {
			cont_pin = _cont_pin;
		}
		if (_cont_id_client > 0) {
			cont_id_client = _cont_id_client;
		}
		cont_numar_tranzactii = 0;
		cont_activ = _cont_activ;
	}

	//constructor de copiere
	Conturi_Bancare(const Conturi_Bancare& cont) :cont_id(cont.cont_id) {
		if (cont_IBAN != nullptr) {
			delete[] cont_IBAN;
		}

		if (cont.cont_IBAN != nullptr) {
			cont_IBAN = new char[strlen(cont.cont_IBAN) + 1];
			strcpy_s(cont_IBAN, strlen(cont.cont_IBAN) + 1, cont.cont_IBAN);
		}
		cont_sold = cont.cont_sold;
		cont_data_expirare[0] = cont.cont_data_expirare[0];
		cont_data_expirare[1] = cont.cont_data_expirare[1];
		cont_data_expirare[2] = cont.cont_data_expirare[2];
		cont_pin = cont.cont_pin;
		cont_id_client = cont.cont_id_client;
		cont_numar_tranzactii = cont.cont_numar_tranzactii;
		cont_activ = cont.cont_activ;

		cont_nr_total++;
	}

	//destructor
	~Conturi_Bancare() {
		if (cont_IBAN != nullptr) {
			delete[] cont_IBAN;
		}
		cont_nr_total--;
	}

	//operator =
	Conturi_Bancare& operator=(const Conturi_Bancare& cont) {
		if (this != &cont) {
			if (cont_IBAN != nullptr) {
				delete[] cont_IBAN;
			}
			if (cont.cont_IBAN != nullptr) {
				cont_IBAN = new char[strlen(cont.cont_IBAN) + 1];
				strcpy_s(cont_IBAN, strlen(cont.cont_IBAN) + 1, cont.cont_IBAN);
			}
			cont_sold = cont.cont_sold;
			cont_data_expirare[0] = cont.cont_data_expirare[0];
			cont_data_expirare[1] = cont.cont_data_expirare[1];
			cont_data_expirare[2] = cont.cont_data_expirare[2];
			cont_pin = cont.cont_pin;
			cont_id_client = cont.cont_id_client;
			cont_numar_tranzactii = cont.cont_numar_tranzactii;
			cont_activ = cont.cont_activ;
		}
		return *this;
	}
	
	//operator << si >>
	friend ostream& operator<<(ostream& out, const Conturi_Bancare& cont) {
		out << "ID Cont: " << cont.cont_id << endl;
		out << "IBAN Cont: " << cont.cont_IBAN << endl;
		out << "Sold Cont: " << cont.cont_sold << endl;
		out << "Data expirare: " << cont.cont_data_expirare[0] << "." << cont.cont_data_expirare[1] << "." << cont.cont_data_expirare[2] << endl;
		out << "PIN: " << cont.cont_pin << endl;
		out << "ID client: " << cont.cont_id_client << endl;
		out << "Numar tranzactii: " << cont.cont_numar_tranzactii << endl;
		if (cont.cont_activ == true) {
			out << "Contul este activ" << endl;
		}
		else {
			out << "Contul NU este activ" << endl;
		}
		return out;
	}

	friend istream& operator>>(istream& in, Conturi_Bancare& cont) {
		char temp[50];
		cout << "IBAN Cont: ";
		in >> temp;
		if (cont.cont_IBAN != nullptr) {
			delete[] cont.cont_IBAN;
		}
		cont.cont_IBAN = new char[strlen(temp) + 1];
		strcpy_s(cont.cont_IBAN, strlen(temp) + 1, temp);

		cout << "Sold Cont: ";
		in >> cont.cont_sold;

		cout << "Data expirare: ";
		in >> cont.cont_data_expirare[0];
		in >> cont.cont_data_expirare[1];
		in >> cont.cont_data_expirare[2];

		cout << "PIN: ";
		in >> cont.cont_pin;

		//cout << "ID client: ";
		//in >> cont.cont_id_client;

		cout << "Cont Activ? (1/0): ";
		in >> cont.cont_activ;
		
		return in;
	}

	//metode generice de prelucrare/afisare a atributelor
	void afisare_cont() {
		cout << "ID Cont: " << cont_id << endl;
		cout << "IBAN Cont: " << cont_IBAN << endl;
		cout << "Sold Cont: " << cont_sold << endl;
		cout << "Data expirare: " << cont_data_expirare[0] << "." << cont_data_expirare[1] << "." << cont_data_expirare[2] << endl;
		cout << "PIN: " << cont_pin << endl;
		cout << "ID client: " << cont_id_client << endl;
		cout << "Numar tranzactii: " << cont_numar_tranzactii << endl;
		if (cont_activ == true) {
			cout << "Contul este activ" << endl;
		}
		else {
			cout << "Contul nu este activ" << endl;
		}
	}

	static void afisare_nr_conturi() {
		cout << "Numar total de conturi: " << cont_nr_total << endl;
	}

	//functii accesor
	int get_cont_id() {
		return cont_id;
	}
	
	char* get_cont_IBAN() {
		return cont_IBAN;
	}

	double get_cont_sold() {
		return cont_sold;
	}

	int get_cont_data_expirare() {
		return cont_data_expirare[0], cont_data_expirare[1], cont_data_expirare[2]; //aici mai am de lucrat
	}

	string get_cont_pin() {
		return cont_pin;
	}

	int get_cont_id_client() {
		return cont_id_client;
	}

	int get_cont_numar_tranzactii() {
		return cont_numar_tranzactii;
	}

	int get_cont_nr_total() {
		return cont_nr_total;
	}

	bool get_cont_activ() {
		return cont_activ;
	}
	
	void set_cont_IBAN(char* IBAN) {
		if (cont_IBAN != nullptr) {
			delete[] cont_IBAN;
		}
		cont_IBAN = new char[strlen(IBAN) + 1];
		strcpy_s(cont_IBAN, strlen(IBAN) + 1, IBAN);
	}

	void set_cont_sold(double sold) {
		if (sold != cont_sold)
		cont_sold = sold;
	}

	void set_cont_data_expirare(int zi, int luna, int an) {
		if ((zi >= 1 && zi <= 31) && (luna >= 1 && luna <= 12) && (an > 2020 && an < 2040)) {
			cont_data_expirare[0] = zi;
			cont_data_expirare[1] = luna;
			cont_data_expirare[2] = an;
		}
	}

	void set_cont_pin(string pin) {
		if (pin != cont_pin)
		cont_pin = pin;
	}

	void set_cont_id_client(int id_client) {
		if (id_client != cont_id_client && id_client > 0)
		cont_id_client = id_client;
	}

	void set_cont_numar_tranzactii(int nr_tranzactii) {
		if (nr_tranzactii != cont_numar_tranzactii)
		cont_numar_tranzactii = nr_tranzactii;
	}

	void set_cont_nr_total(int nr_total) {
		if (nr_total != cont_nr_total)
			cont_nr_total = nr_total;
	}

	void set_cont_activ(bool status) {
		if (status != cont_activ)
			cont_activ = status;
	}
	
	//operator []
	unsigned int& operator[](int index) {
		if (index >= 0 && index < 3) {
			return cont_data_expirare[index];
		}
		else {
			cout << "Index invalid!" << endl;
		}
	}

	//operator +
	Conturi_Bancare operator+(Conturi_Bancare& cont) {
		Conturi_Bancare temp;
		temp.cont_sold = cont_sold + cont.cont_sold;
		return temp;
	}

	//operator ++
	Conturi_Bancare& operator++() {
		cont_sold++;
		return *this;
	}

	Conturi_Bancare operator++(int) {
		Conturi_Bancare temp = *this;
		cont_sold++;
		return temp;
	}

	//operator cast
	operator double() {
		return cont_sold;
	}

	//operator !
	bool operator!() {
		if (cont_sold > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	//operator conditional >
	bool operator>(Conturi_Bancare& cont) {
		if (cont_sold > cont.cont_sold) {
			return true;
		}
		else {
			return false;
		}
	}

	//operator egalitate ==
	bool operator==(Conturi_Bancare& cont) {
		if (cont_sold == cont.cont_sold) {
			return true;
		}
		else {
			return false;
		}
	}

	void creare_deschidere_cont() {
		//generare iban random
		time_t dataCurenta = time(NULL);
		struct tm* aTime = localtime(&dataCurenta);
		string IBAN;
		IBAN = "RO00BANC" + to_string(aTime->tm_mday) + to_string(aTime->tm_mon) + to_string(aTime->tm_year) + to_string(aTime->tm_hour) + to_string(aTime->tm_min) + to_string(aTime->tm_sec);
		
		//generare pin random
		string pin = "";
		for (int i = 0; i < 4; i++) {
			srand(time(NULL)); //genereaza o noua secventa unica de numere random, in functie de timpul curent, la fiecare iteratie(sequence random)
			pin += to_string(rand()); //srand(time(0)) este o alternativa la rand() care 
		}
		set_cont_pin(pin);
		//generare data expirare pe baza datei curente(am folosit o librarie externa)
		set_cont_data_expirare(aTime->tm_mday, aTime->tm_mon + 1, aTime->tm_year + 1900 + 5);

		cont_IBAN = new char[strlen(IBAN.c_str()) + 1];
		strcpy_s(cont_IBAN, strlen(IBAN.c_str()) + 1, IBAN.c_str());
		
		set_cont_sold(0);
		cont_activ = true;
		cont_numar_tranzactii = 0;
		
		cout << "Contul a fost creat cu succes!" << endl;
		
	}

	//**fisiere text**
	//salvare
	static void conturi_salvare_fisier(vector<Conturi_Bancare> conturi) {
		ofstream fisier("conturi.txt");

		fisier << conturi.size() << endl;
		
		if (fisier.is_open()) {
			for (int i = 0; i < conturi.size(); i++) {
				fisier << conturi[i].cont_id << " " << conturi[i].cont_IBAN << " " << conturi[i].cont_sold << " " << conturi[i].cont_data_expirare[0] << " " << conturi[i].cont_data_expirare[1] << " " << conturi[i].cont_data_expirare[2] << " " << conturi[i].cont_pin << " " << conturi[i].cont_id_client << " " << conturi[i].cont_activ << endl;
			}
		}
		fisier.close();
		
	}

	//incarcare
	static vector<Conturi_Bancare> conturi_incarcare_fisier() {
		vector<Conturi_Bancare> conturi;
		ifstream fisier("conturi.txt");

		int marime;
		fisier >> marime;

		if (fisier.is_open()) {
			for (int i = 0; i < marime; i++) {
				unsigned int id;
				char* IBAN = new char[30];
				double sold;
				int zi, luna, an;
				string pin;
				unsigned int id_client;
				bool activ;
				fisier >> id >> IBAN >> sold >> zi >> luna >> an >> pin >> id_client >> activ;
				
				conturi.push_back(Conturi_Bancare(IBAN, sold, zi, luna, an, pin, id_client, activ));
				
			}
		}
		fisier.close();
		return conturi;
	}
};
unsigned int Conturi_Bancare::cont_nr_total = 0;



class Tranzactii_Conturi_Bancare {
private:
    const unsigned int tranzactie_id;
	char* tranzactie_tip = nullptr; //nedefinit(initial), depunere, retragere, transfer
	int tranzactie_data[3] = { 0, 0, 0 };
	double tranzactie_suma;
	int tranzactie_id_cont;
	int tranzactie_id_cont_destinatar;
	
	static unsigned int tranzactie_nr_total;
public:
	//constructori
	Tranzactii_Conturi_Bancare() : tranzactie_id(++tranzactie_nr_total) {
		tranzactie_tip = new char[strlen("nedefinit") + 1];
		strcpy_s(tranzactie_tip, strlen("nedefinit") + 1, "nedefinit");
		tranzactie_data[0] = 1;
		tranzactie_data[1] = 1;
		tranzactie_data[2] = 2000;
		tranzactie_suma = 0;
		tranzactie_id_cont = 0;
		tranzactie_id_cont_destinatar = 0;
	}

	Tranzactii_Conturi_Bancare(const char* _tip, int _zi, int _luna, int _an, double _suma, int _id_cont, int _id_cont_destinatar) : tranzactie_id(++tranzactie_nr_total) {
		tranzactie_tip = new char[strlen(_tip) + 1];
		strcpy_s(tranzactie_tip, strlen(_tip) + 1, _tip);
		tranzactie_data[0] = _zi;
		tranzactie_data[1] = _luna;
		tranzactie_data[2] = _an;
		tranzactie_suma = _suma;
		tranzactie_id_cont = _id_cont;
		tranzactie_id_cont_destinatar = _id_cont_destinatar;
	}

	//constructor de copiere
	Tranzactii_Conturi_Bancare(const Tranzactii_Conturi_Bancare& tranzactie) : tranzactie_id(tranzactie.tranzactie_id) {

		if (tranzactie_tip != nullptr) {
			delete[] tranzactie_tip;
		}

		if (tranzactie.tranzactie_tip != nullptr) {
			tranzactie_tip = new char[strlen(tranzactie.tranzactie_tip) + 1];
			strcpy_s(tranzactie_tip, strlen(tranzactie.tranzactie_tip) + 1, tranzactie.tranzactie_tip);
		}
		else {
			tranzactie_tip = nullptr;
		}
		
		tranzactie_data[0] = tranzactie.tranzactie_data[0];
		tranzactie_data[1] = tranzactie.tranzactie_data[1];
		tranzactie_data[2] = tranzactie.tranzactie_data[2];
		tranzactie_suma = tranzactie.tranzactie_suma;
		tranzactie_id_cont = tranzactie.tranzactie_id_cont;
		tranzactie_id_cont_destinatar = tranzactie.tranzactie_id_cont_destinatar;

		tranzactie_nr_total++;
	}

	//operator = de copiere
	Tranzactii_Conturi_Bancare& operator=(const Tranzactii_Conturi_Bancare& tranzactie) {
		if (this != &tranzactie) {
			if (tranzactie_tip != nullptr) {
				delete[] tranzactie_tip;
			}

			if (tranzactie.tranzactie_tip != nullptr) {
				tranzactie_tip = new char[strlen(tranzactie.tranzactie_tip) + 1];
				strcpy_s(tranzactie_tip, strlen(tranzactie.tranzactie_tip) + 1, tranzactie.tranzactie_tip);
			}
			else {
				tranzactie_tip = nullptr;
			}

			tranzactie_data[0] = tranzactie.tranzactie_data[0];
			tranzactie_data[1] = tranzactie.tranzactie_data[1];
			tranzactie_data[2] = tranzactie.tranzactie_data[2];
			tranzactie_suma = tranzactie.tranzactie_suma;
			tranzactie_id_cont = tranzactie.tranzactie_id_cont;
			tranzactie_id_cont_destinatar = tranzactie.tranzactie_id_cont_destinatar;
		}
		return *this;
	}

	//destructor
	~Tranzactii_Conturi_Bancare() {
		if (tranzactie_tip != nullptr) {
			delete[] tranzactie_tip;
		}
		
		tranzactie_nr_total--;
	}

	//operatori << si >>
	friend ostream& operator<<(ostream& out, Tranzactii_Conturi_Bancare& tranzactie) {
		out << "Tranzactie id: " << tranzactie.tranzactie_id << " este de tipul " << tranzactie.tranzactie_tip << ", a avut loc in data de " << tranzactie.tranzactie_data[0] << "." << tranzactie.tranzactie_data[1] << "." << tranzactie.tranzactie_data[2] << ", cu suma " << tranzactie.tranzactie_suma << ", de la contul cu id " << tranzactie.tranzactie_id_cont << ", catre contul cu id " << tranzactie.tranzactie_id_cont_destinatar << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Tranzactii_Conturi_Bancare& tranzactie) {
		cout << "Introdu tipul tranzactiei: ";
		char temp[50];
		in >> temp;
		if (tranzactie.tranzactie_tip != nullptr) {
			delete[] tranzactie.tranzactie_tip;
		}
		tranzactie.tranzactie_tip = new char[strlen(temp) + 1];
		strcpy_s(tranzactie.tranzactie_tip, strlen(temp) + 1, temp);

		cout << "Introdu data tranzactiei: ";
		in >> tranzactie.tranzactie_data[0] >> tranzactie.tranzactie_data[1] >> tranzactie.tranzactie_data[2];

		cout << "Introdu suma tranzactiei: ";
		in >> tranzactie.tranzactie_suma;

		cout << "Introdu id-ul contului curent: ";
		in >> tranzactie.tranzactie_id_cont;

		cout << "Introdu id-ul contului destinatar: ";
		in >> tranzactie.tranzactie_id_cont_destinatar;

		return in;
	}

	//2 metrode generice de prelucrare/afisare a atributelor
	void afisare_tranzactie() {
		cout << "Tranzactie id: " << tranzactie_id << " este de tipul " << tranzactie_tip << ", a avut loc in data de " << tranzactie_data[0] << "." << tranzactie_data[1] << "." << tranzactie_data[2] << ", cu suma " << tranzactie_suma << ", de la contul cu id " << tranzactie_id_cont << ", catre contul cu id " << tranzactie_id_cont_destinatar << endl;
	}

	void afisare_tranzactie_nr_total() {
		cout << "Numarul total de tranzactii este: " << tranzactie_nr_total << endl;
	}

	//functii accessor
	int get_tranzactie_id() {
		return tranzactie_id;
	}
	
	char* get_tranzactie_tip() {
		return tranzactie_tip;
	}
	
	int* get_tranzactie_data() {
		return tranzactie_data;
	}
	
	double get_tranzactie_suma() {
		return tranzactie_suma;
	}

	int get_tranzactie_id_cont() {
		return tranzactie_id_cont;
	}
	
	int get_tranzactie_id_cont_destinatar() {
		return tranzactie_id_cont_destinatar;
	}
	
	void set_tranzactie_tip(const char* _tranzactie_tip) {
		if (tranzactie_tip != nullptr) {
			delete[] tranzactie_tip;
		}
		tranzactie_tip = new char[strlen(_tranzactie_tip) + 1];
		strcpy_s(tranzactie_tip, strlen(_tranzactie_tip) + 1, _tranzactie_tip);
	}

	void set_tranzactie_data(int zi, int luna, int an) {
		if ((zi >= 1 && zi <= 31) && (luna >= 1 && luna <= 12) && (an >= 1900 && an <= 2023)) {
			tranzactie_data[0] = zi;
			tranzactie_data[1] = luna;
			tranzactie_data[2] = an;
		}
		else {
			cout << "data nu este valida!" << endl;
		}
	}

	void set_tranzactie_suma(double tranzactie_suma) {
		if (tranzactie_suma > 0) {
			this->tranzactie_suma = tranzactie_suma;
		}
		else {
			cout << "suma nu este valida!" << endl;
		}
	}

	void set_tranzactie_id_cont(int _tranzactie_id_cont) {
		if (_tranzactie_id_cont > 0) {
			tranzactie_id_cont = _tranzactie_id_cont;
		}
		else {
			cout << "id-ul contului nu este valid!" << endl;
		}
	}

	void set_tranzactie_id_cont_destinatar(int _tranzactie_id_cont_destinatar) {
		if (_tranzactie_id_cont_destinatar > 0) {
			tranzactie_id_cont_destinatar = _tranzactie_id_cont_destinatar;
		}
		else {
			cout << "id-ul contului destinatar nu este valid!" << endl;
		}
	}

	//**fisiere text**
	//salvare
	static void tranzactii_salvare_fisier(vector<Tranzactii_Conturi_Bancare> tranzactii) {
		ofstream fisier("tranzactii.txt");
		
		fisier << tranzactii.size() << endl;
		
		for (int i = 0; i < tranzactii.size(); i++) {
			fisier << tranzactii[i].tranzactie_id << " " << tranzactii[i].tranzactie_tip << " " << tranzactii[i].tranzactie_data[0] << " " << tranzactii[i].tranzactie_data[1] << " " << tranzactii[i].tranzactie_data[2] << " " << tranzactii[i].tranzactie_suma << " " << tranzactii[i].tranzactie_id_cont << " " << tranzactii[i].tranzactie_id_cont_destinatar << endl;
		}
		fisier.close();
		
	}

	//incarcare
	static vector<Tranzactii_Conturi_Bancare> tranzactii_incarcare_fisier() {
		vector<Tranzactii_Conturi_Bancare> tranzactii;
		ifstream fisier("tranzactii.txt");

		int marime;
		fisier >> marime;

		if (fisier.is_open()) {
			for (int i = 0; i < marime; i++) {
				unsigned int id;
				char* tip = new char[30];
				int zi, luna, an;
				double suma;
				int id_cont;
				int id_cont_destinatar;
				
				fisier >> id >> tip >> zi >> luna >> an >> suma >> id_cont >> id_cont_destinatar;

				tranzactii.push_back(Tranzactii_Conturi_Bancare(tip, zi, luna, an, suma, id_cont, id_cont_destinatar));

			}
		}
		fisier.close();
		return tranzactii;
	}
	
};
unsigned int Tranzactii_Conturi_Bancare::tranzactie_nr_total = 0; //folosesc preincrementare, rezerv id-ul 0 pentru eventuale erori


void test()
{
	//********* CLIENTI **********************
	Clienti_Filiala cl1("5010101000001", "Georgescu Adrian", 1, 1, 2001, "070000000"), cl2;
	cl2 = cl1;

	Clienti_Filiala cl3(cl1), cl4(cl2);
	
	cl3.afisare_date_client();
	cl4.afisare_date_client();

	//cout << cl1 << endl;

	Clienti_Filiala::afisare_nr_clienti();

	//cin >> cl2;

	
	//**********CONTURI BANCARE ****************
	Conturi_Bancare cb1("RO00BANC0000000000000000", 950.1, 30, 12, 2030, "5555", 1, 1);
	Conturi_Bancare cb2(cb1), cb3(cb2);
	
	cout << endl << cb1 << endl << cb2 << endl << cb3 << endl;

	//cin >> cb1;
	cout << endl << cb2;
	Conturi_Bancare::afisare_nr_conturi();

	cout << endl << "Operator [] " << cb1[2] << endl;
	
	cout << endl << "Operator + " << endl << cb1 + cb2 << endl;

	cout << endl << "Operator cast " << double(cb2) << endl;

	cout << endl << "Operator ! " << !cb2 << endl;

	cb1 > cb2;
	
	cout << endl << "Operator >" << endl;
	if (cb1 > cb2) {
		cout << "Soldul contului 1 este mai mare decat soldul contului 2" << endl;
	}
	else {
		cout << "Soldul contului 2 este mai mare." << endl;
	}

	cout << endl << "Operator ++" << endl;
	cout << "Sold precedent fara ++: " << cb1.get_cont_sold() << endl;
	cout << "Sold dupa ++ prefixat: " << endl << ++cb1 << endl;
	cout << "sold dupa ++ postfixat: " << endl << cb1++ << endl;
	cout << "Sold final: " << cb1.get_cont_sold() << endl;
	
	
	cout << endl << "Operator ==" << endl;
	if (cb1 == cb2) {
		cout << "Soldurile celor doua conturi sunt egale." << endl;
	}
	else {
		cout << "Soldurile celor doua conturi nu sunt egale." << endl;
	}

	//********** TRANZACTII ***********************
	Tranzactii_Conturi_Bancare tr1;
	Tranzactii_Conturi_Bancare tr2("Retragere", 1, 1, 2020, 100, 1, 0);
	Tranzactii_Conturi_Bancare tr3 = tr2;
	Tranzactii_Conturi_Bancare tr4;
	tr4 = tr3;
	
	cout << endl << tr2 << endl;

	//cin >> tr4;
	cout << endl << tr4 << endl;

	cout << endl << tr1 << endl;

	
}


void main(int argc, char* argv[]) {


	vector <Clienti_Filiala> clienti;
	vector <Conturi_Bancare> conturi;
	vector <Tranzactii_Conturi_Bancare> tranzactii;

	if (argc < 2) {
		cout << "Nu ai introdus argumente, continuam cu date default." << endl;
		clienti.push_back(Clienti_Filiala("5010101000001", "Georgescu Adrian", 1, 1, 2001, "070000000"));
		clienti.push_back(Clienti_Filiala("5020202000002", "Popescu Marcel", 2, 2, 2002, "070000001"));
		clienti.push_back(Clienti_Filiala("5030303000003", "Ionescu Ionel", 3, 3, 2003, "070000002"));
		clienti.push_back(Clienti_Filiala("5030303000004", "Nita Sorin Alexandru", 21, 12, 2001, "070000003"));

		conturi.push_back(Conturi_Bancare("RO00BANC0000000000000000", 950.1, 30, 12, 2030, "1111", 1, 1));
		conturi.push_back(Conturi_Bancare("RO00BANC0000000000000001", 1000, 30, 12, 2030, "2222", 2, 1));
		conturi.push_back(Conturi_Bancare("RO00BANC0000000000000002", 2000, 30, 12, 2030, "3333", 3, 1));
		conturi.push_back(Conturi_Bancare("RO00BANC0000000000000003", 3000, 30, 12, 2030, "4444", 1, 1));
		conturi.push_back(Conturi_Bancare("RO00BANC0000000000000004", 4000, 30, 12, 2030, "5555", 1, 1));
	}
	else {
		for (int i = 0; i < argc; i++) {
			cout << argv[i] << " " << i << endl;
			fopen(argv[i], "r");
			if (strcmp(argv[i], "clienti.txt") == 0) {
				clienti = Clienti_Filiala::clienti_incarcare_fisier();
				cout << "clienti.txt a fost incarcat cu succes" << endl;
			}
			else if (strcmp(argv[i], "conturi.txt") == 0) {
				conturi = Conturi_Bancare::conturi_incarcare_fisier();
				cout << "conturi.txt a fost incarcat cu succes" << endl;
			}
			else if (strcmp(argv[i], "tranzactii.txt") == 0) {
				tranzactii = Tranzactii_Conturi_Bancare::tranzactii_incarcare_fisier();
				cout << "tranzactii.txt a fost incarcat cu succes" << endl;
			}
		}
	}
	
	int optiune;

	do {
		cout << endl << "1. Depunere/Retragere bani" << endl;
		cout << "2. Transfer bani" << endl;
		cout << "3. Inchidere cont" << endl;
		cout << "4. Calcul total disponibil conturi la nivel de persoana" << endl;
		cout << "5. Deschidere cont" << endl;
			cout << "Pentru debugging" << endl;
			cout << "6. Adaugare cont" << endl;
			cout << "7. Afisare clienti" << endl;
			cout << "8. Afisare conturi" << endl;
			cout << "9. Afisare tranzactii" << endl;
			cout << "10. Adaugare client" << endl;
			cout << "0. Iesire si salvare" << endl;
		cin >> optiune;
		switch (optiune) {
			case 1: {
				cout << "Introdu IBAN-ul contului: ";
				string iban;
				int id_cont;
				cin >> iban;
				bool gasit = false;
				for (int i = 0; i < conturi.size(); i++) {
					if (conturi[i].get_cont_IBAN() == iban && conturi[i].get_cont_activ() == 1) {
						id_cont = conturi[i].get_cont_id();
						gasit = true;cout << "Introdu suma: ";
						double suma;
						cin >> suma;
						cout << "Introdu tipul tranzactiei (1 - depunere, 2 - retragere): ";
						int tip;
						cin >> tip;
						Tranzactii_Conturi_Bancare tranzactie;
						if (tip == 1) {
							tranzactie.set_tranzactie_tip("depunere");
							conturi[i].set_cont_sold(conturi[i].get_cont_sold() + suma);
						}
						else if (tip == 2) {
							if (conturi[i].get_cont_sold() - suma >= 0) {
								tranzactie.set_tranzactie_tip("retragere");
								conturi[i].set_cont_sold(conturi[i].get_cont_sold() - suma);
							}
							else {
								cout << "Nu ai destul sold in cont!" << endl;
								break;
							}
						}
						else {
							cout << "Tip invalid!" << endl;
							break;
						}
						tranzactie.set_tranzactie_suma(suma);


						time_t dataCurenta = time(NULL);
						struct tm* aTime = localtime(&dataCurenta);

						tranzactie.set_tranzactie_data(aTime->tm_mday, aTime->tm_mon + 1, aTime->tm_year + 1900);
						tranzactie.set_tranzactie_suma(suma);
						tranzactie.set_tranzactie_id_cont(id_cont);
						tranzactie.set_tranzactie_id_cont_destinatar(id_cont);
						tranzactie.afisare_tranzactie();
						tranzactii.push_back(tranzactie);
						break;
					}
				}
				if (!gasit) {
					cout << "Cont inexistent/inactiv!" << endl;
				}
				break;
			}
			case 2: {
				int id_cont;
				cout << "Introdu id-ul contului sursa: ";
				cin >> id_cont;
				bool gasit = false;
				for (int i = 0; i < conturi.size(); i++) {
					if (conturi[i].get_cont_id() == id_cont && conturi[i].get_cont_activ() == 1) {
						cout << "Introdu pin-ul contului: ";
						string pin;
						cin >> pin;
						if (pin == conturi[i].get_cont_pin()) {
							cout << "Introdu iban-ul contului destinatar: ";
							string iban_cont_destinatar;
							cin >> iban_cont_destinatar;
							bool gasit_destinatar = false;
							for (int j = 0; j < conturi.size(); j++) {
								if (conturi[j].get_cont_IBAN() == iban_cont_destinatar && conturi[j].get_cont_activ() == 1) {
									cout << "Introdu suma: ";
									double suma;
									cin >> suma;
									if (suma <= conturi[i].get_cont_sold()) {
										conturi[i].set_cont_sold(conturi[i].get_cont_sold() - suma);
										conturi[j].set_cont_sold(conturi[j].get_cont_sold() + suma);
										Tranzactii_Conturi_Bancare tranzactie;
										tranzactie.set_tranzactie_tip("transfer");
										tranzactie.set_tranzactie_suma(suma);
										time_t dataCurenta = time(NULL);
										struct tm* aTime = localtime(&dataCurenta);
										tranzactie.set_tranzactie_data(aTime->tm_mday, aTime->tm_mon + 1, aTime->tm_year + 1900);
										tranzactie.set_tranzactie_id_cont(id_cont);
										tranzactie.set_tranzactie_id_cont_destinatar(conturi[j].get_cont_id());
										tranzactie.afisare_tranzactie();
										tranzactii.push_back(tranzactie);
										gasit_destinatar = true;
										break;
									}
									else {
										cout << "Sold insuficient!" << endl;
										break;
									}
								}
							}
							if (!gasit_destinatar) {
								cout << "Cont destinatar inexistent/inactiv!" << endl;
								break;
							}
						}
						else {
							cout << "Pin invalid!" << endl;
							break;
						}
						gasit = true;
						break;
					}
				}
				if (!gasit) {
					cout << "Cont inexistent/inactiv!" << endl;
				}
				break;
			}
			case 3: {
				cout << "Introdu id-ul contului: ";
				int id_cont;
				cin >> id_cont;
				bool gasit = false;
				for (int i = 0; i < conturi.size(); i++) {
					if (conturi[i].get_cont_id() == id_cont && conturi[i].get_cont_activ() == 1 && conturi[i].get_cont_sold() == 0) {
						cout << "Introdu pin-ul contului: ";
						string pin;
						cin >> pin;
						if (pin == conturi[i].get_cont_pin()) {
							cout << "Esti sigur ca doresti sa inchizi contul? (1/0): ";
							int raspuns;
							cin >> raspuns;
							if (raspuns == 1) {
								conturi[i].set_cont_activ(0);
								cout << "Contul tau a fost inchis cu succes!" << endl;
							}
							else {
								cout << "Operatiune anulata!" << endl;
							}
							gasit = true;
							break;
						}
						else {
							cout << "Pin invalid!" << endl;
						}
						gasit = true;
						break;
					}
				}
				if (!gasit) {
					cout << "Cont inexistent/inactiv sau nu are sold-ul pe 0!" << endl;
				}
				break;
			}
			case 4: {
				cout << "Introdu id-ul clientului";
				int id_client;
				cin >> id_client;
				bool gasit = false;
				double suma_totala = 0;
				for (int i = 0; i < conturi.size(); i++) {
					if (conturi[i].get_cont_id_client() == id_client && conturi[i].get_cont_activ() == 1) {
						suma_totala += conturi[i].get_cont_sold();
						gasit = true;
					}
				}
				if (gasit) {
					cout << "Soldul total aferent conturilor detinute de catre client este de " << suma_totala << endl;
				}
				else {
					cout << "Client inexistent/inactiv!" << endl;
				}
				break;
			}
			case 5: {
				cout << "Introduceti CNP-ul dumneavoastra: ";
				string cnp;
				cin >> cnp;
				//bool gasit = false;
				if (cnp.size() == 13) {
					int gasit_cont = 0;
					for (int i = 0; i < clienti.size(); i++) {
						if (clienti[i].get_client_cnp() == cnp) {
							cout << "Sunteti deja client al bancii, trecem mai departe pentru a deschide contul!" << endl;
							gasit_cont = clienti[i].get_client_id();
							cout << clienti[i].get_client_id() << endl;
							break;
						}
					}
					if (gasit_cont == 0) {
						cout << "Nu sunteti client al bancii, va rugam sa va inregistrati!" << endl;
						Clienti_Filiala client;
						client.creare_client_deschidere_cont(cnp);
						gasit_cont = client.get_client_id();
						clienti.push_back(client);
						cout << client.get_client_id() << endl << endl;
					}
					Conturi_Bancare cont;
					cont.creare_deschidere_cont();
					cont.set_cont_id_client(gasit_cont);
					conturi.push_back(cont);
					cont.afisare_cont();
					cout << "Contul a fost deschis cu succes!" << endl << endl;
					//gasit = true;
				}
				else {
					cout << "CNP-ul introdus este invalid (mai putin de 13 cifre)!" << endl;
					break;
				}
				break;
				
			}
			case 6: {
				Conturi_Bancare cont;
				cin >> cont;
				conturi.push_back(cont);
				break;
			}
			case 7: {
				for (int i = 0; i < clienti.size(); i++) {
					cout << clienti[i] << endl;
				}
				break;
			}
			case 8: {
				for (int i = 0; i < conturi.size(); i++) {
					cout << conturi[i] << endl;
				}
				break;
			}
			case 9: {
				for (int i = 0; i < tranzactii.size(); i++) {
					cout << tranzactii[i] << endl;
				}
				break;
			}
			case 10: {
				Clienti_Filiala client;
				cin >> client;
				clienti.push_back(client);
				break;
			}
			case 0: {
				cout << "Aplicatie terminata!" << endl;
				Clienti_Filiala::clienti_salvare_fisier(clienti);
				Conturi_Bancare::conturi_salvare_fisier(conturi);
				Tranzactii_Conturi_Bancare::tranzactii_salvare_fisier(tranzactii);
				break;
			}
		}
	} while (optiune != 0);

}