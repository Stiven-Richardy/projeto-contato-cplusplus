/*
IFSP - CAMPUS CUBATÃO
TURMA: ADS 371 - ESTRUTURA DE DADOS
NOME: STIVEN RICHARDY SILVA RODRIGUES
*/
#include <iostream>
#include <locale.h>
#include <iomanip>
#include <conio.h>
#include <chrono>
#include <ctime>
#include <regex>

using namespace std;

#define TAM_ARRAY 5

class Data
{
	private:
		int dia;
		int mes;
		int ano;
		
	public:	
		Data(int dia, int mes, int ano)
		{
			this->dia = dia;
			this->mes = mes;
			this->ano = ano;
		}
		Data()
		{
			this->dia = 0;
			this->mes = 0;
			this->ano = 0;
		}

		void setDia(int dia)
		{
			this->dia = dia;
		}
		void setMes(int mes)
		{
			this->mes = mes;
		}
		void setAno(int ano)
		{
			this->ano = ano;
		}
		int getDia()
		{
			return this->dia;
		}
		int getMes()
		{
			return this->mes;
		}
		int getAno()
		{
			return this->ano;
		}

		string getData()
        { 
			string sdia = to_string(this->dia);
			string smes = to_string(this->mes);
			string sano = to_string(this->ano);
			
			return sdia.insert(0, 2-sdia.size(), '0') + "/" + 
		           smes.insert(0, 2-smes.size(), '0') + "/" +
		           sano.insert(0, 4-sano.size(), '0');
        }
        
		Data* dia_seguinte()
		{
			Data *ds = new Data(this->dia, this->mes, this->ano);
			int diasNoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			
			if (ds->ano%4 == 0)
			{
				diasNoMes[1]++;
			}
			
			ds->dia++;
			if(ds->dia > diasNoMes[ds->mes-1])
			{
				ds->dia = 1;
				ds->mes++;
				if (ds->mes > 12)
				{
					ds->mes = 1;
					ds->ano++;
				}
			}
			return ds;
		}
		
		bool valida(tm* dataAtual) {
			int diasNoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		
			if (this->mes < 1 || this->mes > 12 || this->dia < 1 || this->ano < 1) {
				return false;
			}
		
			if ((this->ano % 4 == 0 && this->ano % 100 != 0) || (this->ano % 400 == 0)) {
				diasNoMes[1] = 29;
			}
		
			if (this->dia > diasNoMes[this->mes - 1]) {
				return false;
			}
		
			int anoAtual = dataAtual->tm_year + 1900;
			int mesAtual = dataAtual->tm_mon + 1;
			int diaAtual = dataAtual->tm_mday;
		
			if (this->ano > anoAtual) return false;
			if (this->ano == anoAtual && this->mes > mesAtual) return false;
			if (this->ano == anoAtual && this->mes == mesAtual && this->dia > diaAtual) return false;
		
			return true;
		}
};

class Contato {
	private:
		string email;
		string nome;
		string telefone;
		Data dtnasc;

	public:
		Contato(string email, string nome, string telefone, Data dtnasc) {
			this->email = email;
			this->nome = nome;
			this->telefone = telefone;
			this->dtnasc = dtnasc;
		}
		
		Contato() {
			this->email = "";
			this->nome = "";
			this->telefone = "";
		}
		
		void setEmail(string email) {
			this->email = email;
		}
		
		void setNome(string nome) {
			this->nome = nome;
		}
		
		void setTelefone(string telefone) {
			this->telefone = telefone;
		}
		
		void setDtnasc(Data dtnasc) {
			this->dtnasc = dtnasc;
		}
		
		string getEmail() {
			return this->email;
		}
		
		string getNome() {
			return this->nome;
		}
		
		string getTelefone() {
			return this->telefone;
		}
		
		Data getDtnasc() {
			return this->dtnasc;
		}
		
		int idade(tm* dtatual) {
			int anos = dtatual->tm_year + 1900 - this->dtnasc.getAno();

			if ((dtatual->tm_mon + 1) < this->dtnasc.getMes() || ((dtatual->tm_mon + 1) == this->dtnasc.getMes() && dtatual->tm_mday < this->dtnasc.getDia())) {
				anos--;
			}
			return anos;
		}
};

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");

	string email[TAM_ARRAY];
	string nome[TAM_ARRAY];
	string telefone[TAM_ARRAY];
	Data *dtnasc[TAM_ARRAY];
	Contato contatos[TAM_ARRAY];
	int idade[TAM_ARRAY];
	
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm* local_time = localtime(&now_time);
	
	for (int i = 0; i < TAM_ARRAY; ++i) {
		int dia, mes, ano;
		bool valid;
		
   	    cout << "============================================" << endl
	 	 	 <<	"            CADASTRO DE CONTATOS" << endl
       	 	 << "============================================" << endl;
		
		cout << "Informe o " << (i+1) << "º nome: ";
		cin >> nome[i];
		
		do {
			valid = true;
			cout << "Informe o " << (i+1) << "º e-mail: ";
			cin >> email[i];
			
			if (email[i].find('@') == string::npos & email[i].find('.') == string::npos) {
				cout << "E-mail inválido. Tente novamente." << endl;
				valid = false;
			}
		} while (!valid);
		
		do {
			valid = true;
			cout << "Informe o " << (i+1) << "º Telefone" << endl
			   	 << "(Formato: (XX)XXXXX-XXXX): ";
			cin >> telefone[i];
			regex padrao_tel("^\\(\\d{2}\\)\\d{5}-\\d{4}$");
			
			if (telefone[i].length() < 8 && telefone[i].length() < 8 || !regex_match(telefone[i], padrao_tel)) {
				cout << "Telefone inválido. Tente novamente." << endl;
				valid = false;
			}
		} while (!valid);
		
		do {
			valid = true;
			cout << "Informe a " << (i+1) << "º data de nascimento:" << endl;
			cout << "- Informe o dia: ";
			cin >> dia;
			cout << "- Informe o mês: ";
			cin >> mes;
			cout << "- Informe o ano: ";
			cin >> ano;
		
			dtnasc[i] = new Data(dia, mes, ano);
		
			if (!dtnasc[i]->valida(local_time)) {
				cout << "Data inválida. Tente novamente." << endl;
				valid = false;
				delete dtnasc[i];
			}
		} while (!valid);
		
		cout << (i+1) <<"º Contato cadastrado com sucesso." << endl 
 	 	 	 << "Pressione qualquer tecla para continuar..." << endl 
   	    	 << "--------------------------------------------" << endl;
    	_getch();
		system("cls");
		
		dtnasc[i] = new Data(dia, mes, ano);
		contatos[i] = Contato(email[i], nome[i], telefone[i], *dtnasc[i]);
		idade[i] = contatos[i].idade(local_time);

		delete dtnasc[i];
	}
	
	cout << "============================================" << endl
	 	 <<	"            RELAÇÃO DE CONTATOS" << endl
       	 << "============================================" << endl;
	
	for (int i = 0; i < TAM_ARRAY; ++i) {
		cout << "|" << (i+1) << "º| Nome: " << contatos[i].getNome() << endl
		   	 << "|" << (i+1) << "º| E-mail: " << contatos[i].getEmail() << endl
			 << "|" << (i+1) << "º| Telefone: " << contatos[i].getTelefone() << endl
			 << "|" << (i+1) << "º| Idade: " << idade[i] << " anos" << endl
			 << "--------------------------------------------" << endl;
	}
		
	return 0;
}