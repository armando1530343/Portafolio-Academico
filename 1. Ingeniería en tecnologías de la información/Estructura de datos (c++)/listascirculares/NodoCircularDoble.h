
class NodoCircularDoble{
    
    private:        
        int dato; //Debe ser generico
        NodoCircularDoble* nodo_sig;
        NodoCircularDoble* nodo_ant;

    public:
        NodoCircularDoble(){
            nodo_sig = NULL;
            nodo_ant = NULL;
        }
        void setDato(int dato){this->dato = dato;}
        int getDato(){return dato;}

        void setSig(NodoCircularDoble *sig){nodo_sig = sig;}
        NodoCircularDoble* getSig(){return nodo_sig;}
 
        void setAnt(NodoCircularDoble *ant){nodo_ant = ant;}
        NodoCircularDoble* getAnt(){return nodo_ant;}
};
