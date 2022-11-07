
#include "DLists.h"

int main()
{
	DList lLista = DList();

	lLista.read("C:/temp/PyED/heroes.csv");
	
	lLista.push_back("Clark", "Kent", "ClarkKent", "asd123", 1234567890123456, 3400);


	cout << "Datos organizados por nombre: " << endl;
	lLista.repr(ECampos::nombre);

	/*
	cout << endl << "Datos organizados por fecha: " << endl;
	PDATA lItem = NULL;
	while (lItem = lLista.get(ECampos::fnac)) {
		cout << "(" << lItem->sID << ") " << lItem->sNombre << " " << lItem->sApellido << " " 
			<< lItem->sFNac << " " << lItem->sSalario << endl;
	}

	cout << endl << "Datos organizados por salario (desc): " << endl;
	while (lItem = lLista.get(ECampos::salario, true)) {
		cout << "(" << lItem->sID << ") " << lItem->sNombre << " " << lItem->sApellido << " " 
			<< lItem->sFNac << " " << lItem->sSalario << endl;
	}

	cout << endl << "Datos organizados por id (desc): " << endl;
	while (lItem = lLista.get(ECampos::index, true)) {
		cout << "(" << lItem->sID << ") " << lItem->sNombre << " " << lItem->sApellido << " "
			<< lItem->sFNac << " " << lItem->sSalario << endl;
	}
	
	cout << endl << "Datos sin un Clack: " << endl;
	lLista.del("Clark", "Kent", "1938-04-18", 100);
	lLista.repr(ECampos::nombre);

	cout << endl << "Datos sin un Bruno: " << endl;
	lLista.del("Bruno", "Diaz", "1939-03-30", 5500);
	lLista.repr(ECampos::nombre);

	cout << endl << "Datos sin Diana: " << endl;
	lLista.del("Diana", "Prince", "1941-01-01", 500);
	lLista.repr(ECampos::nombre);

	cout << endl << "Datos sin el id 2: " << endl;
	lLista.del(2);
	lLista.repr(ECampos::nombre);
	*/
	//lLista.write("C:/temp/PyED/heroes.csv");
}
