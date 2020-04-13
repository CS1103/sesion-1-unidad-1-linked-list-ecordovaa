#include "linked_list.h"

utec::first::linked_list_t::linked_list_t(const utec::linked_list_t &other){
    for(size_t i=0;i<size_;++i)
        pop_front(); //Vaciado del contenido de this
    for(size_t i=0;i<other.size_;++i){
        push_back(other.item(i)); //Llenado del contenido de this usando los elementos de other
    }
    size_ = other.size_;
}

utec::linked_list_t &utec::first::linked_list_t::operator=(const utec::linked_list_t &other) {
    for(size_t i=0;i<size_;++i)
        pop_front(); //Vaciado del contenido de this
    for(size_t i=0;i<other.size_;++i)
        push_back(other.item(i));  //Llenado del contenido de this usando los elementos de other
    size_ = other.size_;
    return *this;
}

utec::first::linked_list_t::linked_list_t(utec::linked_list_t &&other) noexcept: size_(std::move(other.size_)), head_(std::move(other.head_)), tail_(std::move(other.tail_))
{   //Move de other a this, se igualan los nodos y se nulifica el tamaño
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

utec::linked_list_t &utec::first::linked_list_t::operator=(utec::linked_list_t &&other) noexcept {
    for(int i=0;i<size_;++i)
        pop_front();   //Vaciado de elementos de this
    //Move de other a this, se igualan los nodos y se nulifica el tamaño
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
    return *this;
}

utec::first::linked_list_t::~linked_list_t() {
    while(head_!=nullptr){
        auto aux = head_;
        head_ = head_->next_;
        delete aux; //Borra el contenido de aux, el cual pasa por todos los nodos
    }
    tail_ = nullptr; //Iguala tail_ a nullptr. Si esta linea no es colocada, this apunta a un contenido borrado con delete, lo que no es recomendable.
    size_ = 0;
}

void utec::first::linked_list_t::push_front(int value) {
    auto node = new node_t(); //Se crea un nuevo nodo y se llena con los datos
    node->value_ = value;
    node->next_ = head_;
    head_ = node; //Head apunta a node
    size_++;
}

void utec::first::linked_list_t::push_back(int value) {
    if(size_==0) push_front(value);
    else{
        auto aux = head_;
        while(aux->next_!= nullptr){
            aux = aux->next_;  //Buscamos al antecesor de tail_
        }
        auto node = new node_t(); //Se crea un nuevo nodo y se llena con los datos
        node->value_ = value;
        node->next_ = nullptr;
        aux->next_ = node;
        tail_ = node; //Tail_ apunta a node
        size_++;
    }
}

void utec::first::linked_list_t::insert(size_t index, int value) {
    if(index==0) push_front(value); //Si es cero, es el equivalente a push front
    if(index==size_-1) push_back(value); //Si el indice es el ultimo elemento posible, es el equivalente a push back
    else {
        index--; //Reducimos index por comodidad
        auto actual = head_;
        while (index--)
            actual = actual->next_; //Buscamos al antecesor de index
        auto node = new node_t();
        node->value_ = value;
        auto aux = actual->next_;
        actual->next_ = node;
        node->next_ = aux; //Hacemos el cambio: antecesor de index -> index -> aux(predecesor del index original)
        size_++;
    }
}

void utec::first::linked_list_t::pop_front() {
    if (head_ == tail_) { //Condicional por si size_ = 1
        delete head_;
        head_ = tail_ = nullptr;
        size_ = 0;
    }
    else {
        auto next = head_->next_; //Borrado del primer elemento
        delete head_;
        head_ = next; //Head apunta a su predecesor
        size_--;
    }
}

void utec::first::linked_list_t::pop_back() {
    if (head_ == tail_) {
        delete head_;
        head_ = tail_ = nullptr; //Se elimina la lista
        size_ = 0;
    }
    else {
        auto actual = head_;
        while (actual->next_->next_!= nullptr) //Buscamos al antecesor de tail_
            actual = actual->next_;
        delete actual->next_; //Eliminamos tail_
        actual->next_ = nullptr;
        tail_ = actual; //Tail_ apunta a actual
    }
    size_--;
}

void utec::first::linked_list_t::erase(size_t index) {
    if (size_== 1) {
        delete head_;
        head_ = tail_ = nullptr; //Se elimina la lista
    }
    else {
        index--;
        auto actual = head_;
        while (index--)
            actual = actual->next_;
        auto aux = actual->next_->next_; //Buscamos al predecesor del index
        delete actual->next_;
        actual->next_ = aux; //Ordenamos las posiciones de actual y aux
    }
    size_--;
}

int &utec::first::linked_list_t::item(size_t index) {
    auto actual = head_;
    while (index--)
        actual = actual->next_;
    return actual->value_; //Retornamos el contenido de actual
}

const int &utec::first::linked_list_t::item(size_t index) const {
    auto actual = head_;
    while (index--)
        actual = actual->next_;
    return actual->value_;  //Retornamos el contenido de actual
}

size_t utec::first::linked_list_t::size() const {
    return size_;  //Retornamos el size
}