
class NodoCircular{
    
    private:        
        int dato; //Debe ser generico
        NodoCircular* nodo_sig;

    public:
        NodoCircular(){
            nodo_sig = NULL;
        }
        void setDato(int dato){this->dato = dato;}
        int getDato(){return dato;}
        void setSig(NodoCircular *sig){nodo_sig = sig;}
        NodoCircular* getSig(){return nodo_sig;}
};
