#ifndef NODO_H_
#define NODO_H_
#include <string>
#include <locale.h>
using namespace std;
class Nodo{
private:
	Nodo* izquierdo=nullptr;
	Nodo* derecho=nullptr;
	string data="";
public:
	Nodo(string);
	~Nodo();
	Nodo** pasarDatos(string);
	void añadirNodo(string);
	string getData(){return this->data;}
	void setData(string data){this->data=data;}
	bool buscarElemento(string);
	bool buscarDato(string,Nodo**);
};
#endif
