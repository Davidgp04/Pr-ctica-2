#include <iostream>
#include "Nodo.h"
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;
string aMinuscula(string cadena) {
  for (int i = 0; i < cadena.length(); i++) cadena[i] = tolower(cadena[i]);
  return cadena;
}
Nodo::Nodo(string data){
	this->data=data;
}

void Nodo::añadirNodo(string data){
	setlocale(LC_CTYPE,"Spanish");
	Nodo* actual;
	actual=this;
	while(true){
		if (actual->data<data){
			if (actual->derecho==nullptr){
				actual->derecho=new Nodo(data);
				break;
			}else{
				actual=actual->derecho;
			}
		}else if(actual->data>data){
			if (actual->izquierdo==nullptr){
				actual->izquierdo=new Nodo(data);
				break;
			}else{
				actual=actual->izquierdo;
			}
		}else{
			break;
		}
	}
}
Nodo** Nodo::pasarDatos(string nombreArchivo){
	Nodo** lista=new Nodo*[27];
	char letra='a';
	do{
		lista[int(letra)-int('a')]=new Nodo(std::string(1,letra));
		letra++;
	}while(letra<='z');
	ifstream archivo(nombreArchivo.c_str());
	if(archivo.fail()){
		cout<<nombreArchivo<<endl;
		cout<<"El archivo no pudo abrirse\n";
		exit(1);
		}
	string linea;
	while(getline(archivo,linea)){
		try{
		linea=aMinuscula(linea);
		int posicion=int(linea[0])-int('a');
		lista[posicion]->añadirNodo(linea);
		}
		catch(...){
			cout<<linea<<endl;
		}
	}
	cout<<"Cargado "<<nombreArchivo<<endl;
	return lista;
}

bool Nodo::buscarElemento(string elemento){
	Nodo* actual;
	actual=this;
	while(true){
	if (actual==nullptr){
		return false;
	}else if (actual->data==elemento){
		return true;
	}else if (actual->data<elemento){
		actual=actual->derecho;
	}else{
		actual=actual->izquierdo;
	}
	}
}
bool Nodo::buscarDato(string elemento,Nodo** lista){
	elemento=aMinuscula(elemento);
	return lista[int(elemento[0]-int('a'))]->buscarElemento(elemento);
}
