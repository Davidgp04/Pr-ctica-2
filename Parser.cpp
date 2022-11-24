#include <iostream>
#include <string>
#include "Parser.h"
using namespace std;
Nodo* objeto=new Nodo("temporal");
string aMinuscula2(string cadena) {
  for (int i = 0; i < cadena.length(); i++) cadena[i] = tolower(cadena[i]);
  return cadena;
}
Parser::Parser(){
this->determinantesSingulares=objeto->pasarDatos("determinantesSingulares.txt");
this->determinantesPlurales=objeto->pasarDatos("determinantesPlurales.txt");
this->sustantivosPlurales=objeto->pasarDatos("sustantivosPlurales.txt");
this->sustantivosSingulares=objeto->pasarDatos("sustantivosSingulares.txt");
this->nombres=objeto->pasarDatos("nombresPropios.txt");
this->apellidos=objeto->pasarDatos("apellidos.txt");
this->conjunciones=objeto->pasarDatos("Conjunciones.txt");
this->verbosSingulares=objeto->pasarDatos("verbosSingulares.txt");
this->verbosPlurales=objeto->pasarDatos("verbosPlurales.txt");
}
string Parser::analizador(string expresion){
	int inicio=0;
	expresion=aMinuscula2(expresion);
	if (expresion.find('á',inicio)!=string::npos ||expresion.find('é',inicio)!=string::npos ||expresion.find('í',inicio)!=string::npos || expresion.find('ó',inicio)!=string::npos ||expresion.find('ú',inicio)!=string::npos ){
		return "Nuestro compilador no admite acentos, por favor eliminarlos y volver a intentar\n";
	}
	if (expresion.find(' ',inicio)==string::npos && objeto->buscarDato(expresion, this->verbosSingulares)){
		return "Frase válida compuesta por verbo y sujeto omnisciente\n";
	}else if (expresion.find(' ',inicio)==string::npos && objeto->buscarDato(expresion, this->verbosPlurales)){
	return "Frase válida compuesta por verbo y sujeto omnisciente\n";

	}else if(expresion.find(' ',inicio)==string::npos && not objeto->buscarDato(expresion,this->verbosSingulares) && not objeto->buscarDato(expresion,this->verbosPlurales)){
		return "Expresión no válida por no tener verbos\n";
	}else{
		expresion+=' ';
		string palabra;
		int contadorVerbos=0,contadorVerbosSingulares=0,contadorVerbosPlurales=0;
		string verbo;
		string anterior;
		while(expresion.find(' ',inicio+1)!=string::npos){
			int secundario=expresion.find(' ',inicio);
			palabra=expresion.substr(inicio, secundario-inicio);
			if (objeto->buscarDato(palabra,this->verbosSingulares)){
				if (objeto->buscarDato(anterior,this->determinantesSingulares)){

				}else{
					contadorVerbos++;
					contadorVerbosSingulares+=1;
					verbo=palabra;
					cout<<"verbo-->"<<verbo<<endl;
				}
			}else if (objeto->buscarDato(palabra,this->verbosPlurales)){
				if (objeto->buscarDato(anterior,this->determinantesPlurales)){

				}else{
					contadorVerbos++;
					contadorVerbosPlurales+=1;
					verbo=palabra;
					cout<<"verbo--> "<<verbo<<endl;
				}
			}
			if (expresion.find(' ', inicio)!=string::npos && contadorVerbos<=1) {
			inicio=secundario+1;
			}else if (contadorVerbos>1){
				return "Frase inválida por tener más de un verbo";
			}else{
				break;
			}
			anterior=palabra;
		}
		string sujeto;
		if (contadorVerbos==0){
			return "Frase no válida por no tener verbos\n";
		}
		if (contadorVerbosSingulares>0){
			sujeto=this->analizadorSujeto(expresion.substr(0,expresion.find(verbo, 0)),1);
		}else{
			sujeto=this->analizadorSujeto(expresion.substr(0,expresion.find(verbo, 0)),2);
		}
		if (sujeto=="Frase inválida"){
						return "La frase no tiene una correcta estructura";
			}else{
				cout<<"Sujeto --> "<<expresion.substr(0,expresion.find(verbo, 0))<<endl;
			}
		string predicado;
		if (expresion.substr(expresion.find(verbo,0)+verbo.length(), expresion.length()).length()==0){
			predicado="";
		}else{
			cout<<"Predicado--> "<<expresion.substr(expresion.find(verbo,0)+verbo.length(), expresion.length())<<endl;
			predicado="-predicado";
		}
	palabra="-verbo-";
	return ("Oración válida compuesta por: "+sujeto+palabra+predicado);
	}
}
string Parser::analizadorSujeto(string sujeto,int opcion){
	string informacion="Frase con ";
	if (sujeto.length()==0){
		informacion+="sujeto impersonal ";
		return informacion;
	}else{
		int inicio=0;
		int contadorSujetosSingulares=0,contadorSujetosPlurales=0,contadorDeterminantesSingulares=0,contadorDeterminantesPlurales=0,contadorNombres=0,contadorApellidos=0,contadorConjunciones=0;
		string palabra;
		while(sujeto.find(' ', inicio)!=string::npos){
		int secundario=sujeto.find(' ',inicio);
		palabra=sujeto.substr(inicio, secundario-inicio);
		if (palabra=="a" || palabra=="que"){
		return "Frase inválida";
		}
		if(objeto->buscarDato(palabra,this->conjunciones)){
					contadorConjunciones++;
		}else if (objeto->buscarDato(palabra,this->nombres)){
			contadorNombres++;
		}else if(objeto->buscarDato(palabra,this->apellidos)){
			contadorApellidos++;
		}else if (objeto->buscarDato(palabra,this->sustantivosSingulares)){
			contadorSujetosSingulares++;
		}else if(objeto->buscarDato(palabra,this->sustantivosPlurales)){
			contadorSujetosPlurales++;
		}else if (objeto->buscarDato(palabra,this->determinantesSingulares)){
			contadorDeterminantesSingulares++;
		}else if (objeto->buscarDato(palabra,this->determinantesPlurales)){
			contadorDeterminantesPlurales++;
		}
		if (sujeto.find(' ', inicio)!=string::npos) {
					inicio=secundario+1;
			}
	}
		if (opcion==1){
			if(contadorConjunciones>0){
				return "Frase inválida";
			}else if(contadorSujetosSingulares==0 && contadorSujetosPlurales>0){
				return "Frase inválida";
			}else if(contadorDeterminantesSingulares>contadorSujetosSingulares || contadorDeterminantesPlurales>contadorSujetosPlurales){
				return "Frase inválida";
			}else{
				return " Sujeto-";
		}
		}else{
			if ((contadorNombres>1 || contadorApellidos>1 || contadorSujetosSingulares>1) && contadorConjunciones<1){
				cout<<"No hay suficientes conjunciones";
				return "Frase inválida";
			}else if (contadorDeterminantesSingulares>contadorSujetosSingulares || contadorDeterminantesPlurales>contadorSujetosPlurales){
				cout<<"No hay suficientes sustantivos";
				return "Frase inválida";
			}else{
				return "sujeto ";
			}
			}
		}
}
int main(){
	Parser* objeto1=new Parser();
	while(true){
	cout<<"\nIngrese la expresión deseada"<<endl;
	string expresion;
	getline(cin,expresion);
	cout<<objeto1->analizador(expresion);
	if (expresion=="end"){
		break;
	}
	}
}
