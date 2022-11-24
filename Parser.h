#ifndef PARSER_H_
#define PARSER_H_
#include "Nodo.h"
class Parser{
private:
	Nodo** sustantivosSingulares;
	Nodo** sustantivosPlurales;
	Nodo** determinantesPlurales;
	Nodo** nombres;
	Nodo** apellidos;
	Nodo** conjunciones;
public:
	Nodo** determinantesSingulares;
	Nodo** verbosSingulares;
	Nodo** verbosPlurales;
	Parser();
	~Parser();
string analizador(string);
string analizadorSujeto(string,Nodo**,Nodo**,int);
};




#endif /* PARSER_H_ */
