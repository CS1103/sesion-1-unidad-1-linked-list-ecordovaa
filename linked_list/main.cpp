#include <iostream>
#include <cassert>
#include <string>
#include "linked_list.h"

using namespace std;

int main() {

    utec::linked_list_t test1;  //Construido por defecto

    //Probando linked_list_t.push_front(...)
    test1.push_front(2);
    test1.push_front(1);
    test1.push_front(0);
    assert(test1.size()==3); //Testeando tamaño
    cout<<"\nFuncion size opera correctamente"<<endl;
    for(size_t i=0; i<3;++i)
        assert(test1.item(i)==i); //Probando elemento por elemento
    cout<<"Funcion item opera correctamente"<<endl;
    cout<<"Funcion push_front opera correctamente"<<endl;

    //Probando linked_list_t.push_back(...)
    test1.push_back(3);
    test1.push_back(4);
    test1.push_back(5);
    assert(test1.size()==6);  //Testeando tamaño
    for(size_t i=3; i<6;++i)
        assert(test1.item(i)==i);  //Probando elemento por elemento
    cout<<"Funcion push_back opera correctamente"<<endl;

    //Probando linked_list_t.insert(... , ...)
    test1.insert(3,100);
    test1.insert(1,200);
    assert(test1.item(1)==200 && test1.item(4)==100 && test1.item(2)==1 && test1.size()==8); //El valor "100" se ha desplazado al indice 4, debido a test1.insert(1,200)
    cout<<"Funcion insert opera correctamente"<<endl;

    //Probando linked_list_t.pop_back()
    for(int i=0; i<3;++i)
        test1.pop_back();
    assert(test1.size()==5 && test1.item(4)==100); //Size_ se ha reducido en 3 unidades, liberando la memoria almacenada para esos valores. tail_ contiene a 100
    cout<<"Funcion pop_back opera correctamente"<<endl;

    //Probando linked_list_t.pop_front()
    for(int i=0; i<3;++i)
        test1.pop_front();
    assert(test1.size()==2 && test1.item(0)==2 && test1.item(1)==100);  //Analogo a pop_back, pero ahora head_ contiene a 2 y los valores anteriores al indice 3 han sido liberados
    cout<<"Funcion pop_front opera correctamente"<<endl;

    //Probando linked_list_t.erase(...)
    test1.erase(1);
    assert(test1.size()==1 && test1.item(0)==2);
    test1.erase(0);
    assert(test1.size()==0);
    cout<<"Funcion erase opera correctamente"<<endl;

    //Asignación, copia. Sobrecarga del operador "="
    for(int i=0;i<6;++i)
        test1.push_back(i);    //Llenado de test1
    assert(test1.size()==6 && test1.item(0)==0);
    utec::linked_list_t test2; //Construido por defecto
    test2 = test1;
    assert(test2.size()==6 && test2.item(0)==0);
    cout<<"Asignacion a traves del operador = opera correctamente"<<endl;

    std::cout << "\nTest realizado exitosamente!" << std::endl;
    return 0;
}