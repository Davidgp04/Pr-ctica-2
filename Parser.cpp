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
		return "Expresión no válida\n";
	}else{
		expresion+=' ';
		string palabra;
		int contadorVerbos=0;
		string verbo;
		while(expresion.find(' ',inicio+1)!=string::npos){
			int secundario=expresion.find(' ',inicio);
			palabra=expresion.substr(inicio, secundario-inicio);
			cout<<palabra<<endl;
			if (objeto->buscarDato(palabra,this->verbosSingulares) || objeto->buscarDato(palabra,this->verbosPlurales)){
				contadorVerbos++;
				cout<<palabra<<endl;
				verbo=palabra;
			}
			if (expresion.find(' ', inicio)!=string::npos && contadorVerbos<=1) {
			inicio=secundario+1;
			}else if (contadorVerbos>1){
				return "Frase inválida";
			}else{
				break;
			}
		}
		string sujeto;
		if (contadorVerbos==0){
			return "Frase no válida\n";
		}
		if (objeto->buscarDato(verbo, this->verbosSingulares)){
			cout<<expresion.substr(0,expresion.find(verbo, 0))<<endl;
			sujeto=this->analizadorSujeto(expresion.substr(0,expresion.find(verbo, 0)),this->determinantesSingulares,this->sustantivosSingulares,1);
		}else{
			cout<<expresion.substr(0,expresion.find(verbo, 0))<<endl;
			sujeto=this->analizadorSujeto(expresion.substr(0,expresion.find(verbo, 0)),this->determinantesPlurales,this->sustantivosPlurales,2);
		}
		if (sujeto=="Frase inválida"){
						return sujeto;
			}
		string predicado;
		if (expresion.substr(expresion.find(palabra,0)+palabra.length(), expresion.length()).length()==0){
			predicado="";
		}else{
			predicado=" predicado";
		}
	palabra=" verbo ";
	return (sujeto+palabra+predicado);
	}
}
string Parser::analizadorSujeto(string sujeto,Nodo** determinantes,Nodo** sustantivos,int opcion){
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
		if (palabra=="a"){
		return "Frase inválida";
		}
		if (objeto->buscarDato(palabra,this->nombres)){
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
		if (palabra.find(' ', inicio)!=string::npos) {
					inicio=secundario+1;
					}else{
						break;
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
				return " Sujeto ";
		}
		}else{
			if ((contadorNombres>1 || contadorApellidos>1 || contadorSujetosSingulares>1) && contadorConjunciones<1){
				return "Frase inválida";
			}else if (contadorDeterminantesSingulares>contadorSujetosSingulares || contadorDeterminantesPlurales>contadorSujetosPlurales){
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
