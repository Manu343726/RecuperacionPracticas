/* 
 * File:   main.cpp
 * Author: Manu343726
 *
 * Created on 1 de junio de 2013, 12:21
 */

#include <iostream>
using namespace std;

#define DEBUGGING

/************************************************************************************************************************
 * Herramientes para depuración                                                                                         *
 *                                                                                                                      *
 * Las cabeceras utilizadas para depuración se encuentran en el subdirectorio utils/, no incluido en la entrega.        *
 * Me he acostumbrado a utilizar estas macros para depurar: En un primer momento utilizo mi versión de assert,          *
 * el cual escribe los resultados en pantalla, y cuando estoy más o menos seguro, activo el assert de C.                *
 *                                                                                                                      *
 * Mi versión de assert incluye una versión que pinta los errores en rojo. Dicha versión utiliza un sencillo sistema de *
 * cambio de estilo de la consola basado en interfaces fluidas. Solo tengo implementada la versión para windows.        *
 *                                                                                                                      *
 * Cuento todo ésto para pasar por encima todas las "cosas raras" que puedan encontrarse durante la corrección.         *
 *                                                                                                                      *
 * Desactivando el modo de depuración, se deshabilitan todos esos includes (Para seguir a rajatabla las reglas de la    *
 * entrega) y se deshabilita también la macro assert.                                                                   *
 ***********************************************************************************************************************/
#ifdef DEBUGGING

#include "utils/dl32Config.h" //Booleanos, entre otras cosas

#define DEBUGGING_USECASSERT  FALSE
#define DEBUGGING_WAIT_AT_END FALSE
#define DEBUGGING_USE_COLOR   TRUE

#define EXPAND(x) x

#if DEBUGGING_USECASSERT
#ifdef NDEBUG
#undef NDEBUG
#endif /* NDEBUG */

#include <assert.h>
#else

#define assert_data(x) __FILE__ << ", in function " << __FUNCTION__  << " (line " <<  __LINE__ << "):" << " '" << #x << "' --> "

#if DEBUGGING_USE_COLOR

#include "utils/dl32ConsoleColor.h" //NOTA: Implementación basada únicamente en Win32 API. Versión UNIX no disponible todavía.

#ifdef assert
#undef assert
#endif /* ASSERT */

#define assert(x) (x) ? cout << assert_data(x) << "SUCCESS" << endl : cout << push_style << dl32ChangeForegroundColor( RED ) << assert_data(x) << "FAIL (Cascao raro)" << pop_style << endl 
#else

#ifdef assert
#undef assert
#endif /* ASSERT */

#define assert(x) (x) ? cout << assert_data(x) << "SUCCESS" << endl : cout << assert_data(x) << "FAIL (Cascao raro)" << endl
#endif /* TESTING_USE_COLOR */
#endif /* TESTING_USEASSERT */

#else
#define assert(x)
#endif /* DEBUGGING */


/* enable_if necesario para wrapper de iterador (operator-> solo tiene sentido para clases, no para tipos básicos) */
template<bool flag, typename T>
struct enable_if;

template<typename T>
struct enable_if<true, T>
{
    typedef T type;
};

template<typename T>
struct enable_if<false, T>
{
};

/* is_class necesario para wrapper de iterador (operator-> solo tiene sentido para clases, no para tipos básicos) */
template<typename T>
class is_class
{
private:
    typedef char _small;

    typedef class
    {
        char dummy[2];
    } _big;

    static const unsigned int _small_size = sizeof (_small);
    static const unsigned int _big_size = sizeof (_big);

    template<typename U> static _small _checker(void(U::*)());
    template<typename U> static _big _checker(...);
public:
    static const bool value = sizeof ( _checker<T>(NULL)) == _small_size;
};

/******************************************************************************************************************
 *  _                       _                                               _                                   _  *
 * | |    __ _    ___ _ __ | |_ _ __ ___  __ _  __ _    ___ _ __ ___  _ __ (_) ___ ______ _    __ _  __ _ _   _(_) *
 * | |   / _` |  / _ \ '_ \| __| '__/ _ \/ _` |/ _` |  / _ \ '_ ` _ \| '_ \| |/ _ \_  / _` |  / _` |/ _` | | | | | *
 * | |__| (_| | |  __/ | | | |_| | |  __/ (_| | (_| | |  __/ | | | | | |_) | |  __// / (_| | | (_| | (_| | |_| | | *
 * |_____\__,_|  \___|_| |_|\__|_|  \___|\__, |\__,_|  \___|_| |_| |_| .__/|_|\___/___\__,_|  \__,_|\__, |\__,_|_| *
 *                                       |___/                       |_|                               |_|         *
 ******************************************************************************************************************/

/* "#include TADs EDA" */

/* EXCEPCIONES */

/*
  Definición de algunas excepciones de las distintas
  implementaciones de los TADs.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
 */

#include <string>
#include <iosfwd>

/**
 Clase de la que heredan todas las excepciones, y
 que proporciona el atributo que almacena el
 mensaje de error.
 */
class ExcepcionTAD
{
public:

    ExcepcionTAD()
    {
    }

    ExcepcionTAD(const std::string &msg) : _msg(msg)
    {
    }

    const std::string msg() const
    {
        return _msg;
    }

    friend std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e);

protected:
    std::string _msg;
};

inline std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e)
{
    out << e._msg;
    return out;
}


// Macro para declarar las clases de tipo excepción
// que heredan de ExcepcionConMensaje, para ahorrar
// escribir muchas veces lo mismo...
#define DECLARA_EXCEPCION(Excepcion) \
class Excepcion : public ExcepcionTAD { \
public: \
Excepcion() {}; \
Excepcion(const std::string &msg) : ExcepcionTAD(msg) {} \
};

/**
 Excepción generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(EPilaVacia);

/**
 Excepción generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(EPilaLlena);

/**
 Excepción generada por algunas de las operaciones de las colas.
 */
DECLARA_EXCEPCION(EColaVacia);

/**
 Excepción generada por algunas operaciones de las colas dobles.
 */
DECLARA_EXCEPCION(EDColaVacia);

/**
 Excepción generada por algunas operaciones de las listas.
 */
DECLARA_EXCEPCION(EListaVacia);

/**
 Excepción generada por accesos incorrectos a las listas
 (tanto a un número de elemento incorrecto como por
 mal manejo de los iteradores).
 */
DECLARA_EXCEPCION(EAccesoInvalido);

/* PILA */

/**
  @file Pila.h

  Implementación del TAD Pila utilizando un
  vector dinámico cuyo tamaño va creciendo si
  es necesario.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
 */

/**
 Implementación del TAD Pila utilizando vectores dinámicos.

 Las operaciones son:

 - PilaVacia: -> Pila. Generadora implementada en el
   constructor sin parámetros.
 - apila: Pila, Elem -> Pila. Generadora
 - desapila: Pila - -> Pila. Modificadora parcial.
 - cima: Pila - -> Elem. Observadora parcial.
 - esVacia: Pila -> Bool. Observadora.
 - numElems: Pila -> Entero. Observadora.

 @author Marco Antonio Gómez Martín
 */
template <class T>
class Pila
{
public:

    /** Tamaño inicial del vector dinámico. */
    enum
    {
        TAM_INICIAL = 10
    };

    /** Constructor; operación PilaVacia */
    Pila()
    {
        inicia();
    }

    /** Destructor; elimina el vector. */
    ~Pila()
    {
        libera();
    }

    /**
     Apila un elemento. Operación generadora.

     @param elem Elemento a apilar.
     */
    void apila(const T &elem)
    {
        if (_numElems == _tam)
            amplia();
        _v[_numElems] = elem;
        _numElems++;
    }

    /**
     Desapila un elemento. Operación modificadora parcial,
     que falla si la pila está vacía.

     desapila(Apila(elem, p)) = p
     error: desapila(PilaVacia)
     */
    void desapila()
    {
        if (esVacia())
            throw EPilaVacia();
        --_numElems;
    }

    /**
     Devuelve el elemento en la cima de la pila. Operación
     observadora parcial, que falla si la pila está vacía.

     cima(Apila(elem, p) = elem
     error: cima(PilaVacia)

     @return Elemento en la cima de la pila.
     */
    const T &cima() const
    {
        if (esVacia())
            throw EPilaVacia();
        return _v[_numElems - 1];
    }

    /**
     Devuelve true si la pila no tiene ningún elemento.

     esVacia(PilaVacia) = true
     esVacia(Apila(elem, p)) = false

     @return true si la pila no tiene ningún elemento.
     */
    bool esVacia() const
    {
        return _numElems == 0;
    }

    /**
     Devuelve el número de elementos que hay en la
     pila.
     numElems(PilaVacia) = 0
     numElems(Apila(elem, p)) = 1 + numElems(p)

     @return Número de elementos.
     */
    int numElems() const
    {
        return _numElems;
    }

    // //
    // MÉTODOS DE "FONTANERÍA" DE C++ QUE HACEN VERSÁTIL
    // A LA CLASE
    // //

    /** Constructor copia */
    Pila(const Pila<T> &other)
    {
        copia(other);
    }

    /** Operador de asignación */
    Pila<T> &operator=(const Pila<T> &other)
    {
        if (this != &other)
        {
            libera();
            copia(other);
        }
        return *this;
    }

    /** Operador de comparación. */
    bool operator==(const Pila<T> &rhs) const
    {
        if (_numElems != rhs._numElems)
            return false;
        for (unsigned int i = 0; i < _numElems; ++i)
            if (_v[i] != rhs._v[i])
                return false;
        return true;
    }

    bool operator!=(const Pila<T> &rhs) const
    {
        return !(*this == rhs);
    }

protected:

    void inicia()
    {
        _v = new T[TAM_INICIAL];
        _tam = TAM_INICIAL;
        _numElems = 0;
    }

    void libera()
    {
        delete []_v;
        _v = NULL;
    }

    void copia(const Pila &other)
    {
        _tam = other._numElems + TAM_INICIAL;
        _numElems = other._numElems;
        _v = new T[_tam];
        for (unsigned int i = 0; i < _numElems; ++i)
            _v[i] = other._v[i];
    }

    void amplia()
    {
        T *viejo = _v;
        _tam *= 2;
        _v = new T[_tam];

        for (unsigned int i = 0; i < _numElems; ++i)
            _v[i] = viejo[i];

        delete []viejo;
    }

private:

    /** Puntero al array que contiene los datos. */
    T *_v;

    /** Tamaño del vector _v. */
    unsigned int _tam;

    /** Número de elementos reales guardados. */
    unsigned int _numElems;
};

/* LISTA */

/**
  @file Lista.h

  Implementación del TAD lista, utilizando una 
  lista doblemente enlazada.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
 */

/**
 Implementación del TAD Lista utilizando una lista doblemente enlazada.

 Las operaciones son:

 - ListaVacia: -> Lista. Generadora implementada en el
   constructor sin parámetros.
 - Cons: Lista, Elem -> Lista. Generadora.
 - ponDr: Lista, Elem -> Lista. Modificadora.
 - primero: Lista - -> Elem. Observadora parcial
 - resto: Lista - -> Lista. Modificadora parcial
 - ultimo: Lista - -> Elem. Observadora parcial
 - inicio: Lista - -> Lista. Modificadora parcial
 - esVacia: Lista -> Bool. Observadora
 - numElems: Lista -> Elem. Obervadora.
 - elem: Lista, Entero - -> Elem. Observador parcial.

 @author Marco Antonio Gómez Martín
 */
template <class T>
class Lista
{
private:

    /**
     Clase nodo que almacena internamente el elemento (de tipo T),
     y dos punteros, uno al nodo anterior y otro al nodo siguiente.
     Ambos punteros podrían ser NULL si el nodo es el primero
     y/o último de la lista enlazada.
     */
    class Nodo
    {
    public:

        Nodo() : _sig(NULL), _ant(NULL)
        {
        }

        Nodo(const T &elem) : _elem(elem), _sig(NULL), _ant(NULL)
        {
        }

        Nodo(Nodo *ant, const T &elem, Nodo *sig) :
        _elem(elem), _sig(sig), _ant(ant)
        {
        }

        T _elem;
        Nodo *_sig;
        Nodo *_ant;
    };

public:

    /** Constructor; operación ListaVacia. */
    Lista() : _prim(NULL), _ult(NULL), _numElems(0)
    {
    }

    /** Destructor; elimina la lista doblemente enlazada. */
    ~Lista()
    {
        libera();
    }

    /**
     Añade un nuevo elemento en la cabeza de la lista.
     Operación generadora.

     @param elem Elemento que se añade en la cabecera de
     la lista.
     */
    void Cons(const T &elem)
    {
        _numElems++;
        _prim = insertaElem(elem, NULL, _prim);
        if (_ult == NULL)
            _ult = _prim;
    }

    /**
     Añade un nuevo elemento al final de la lista (a la 
     "derecha"). Operación modificadora.

     ponDr(e, ListaVacia) = Cons(e, ListaVacia)
     ponDr(e, Cons(x, xs)) = Cons(x, ponDr(e, xs))
     */
    void ponDr(const T &elem)
    {
        _numElems++;
        _ult = insertaElem(elem, _ult, NULL);
        if (_prim == NULL)
            _prim = _ult;
    }

    /**
     Devuelve el valor almacenado en la cabecera de la
     lista. Es un error preguntar por el primero de
     una lista vacía.

     primero(Cons(x, xs)) = x
     error primero(ListaVacia)

     @return Elemento en la cabecera de la lista.
     */
    const T &primero() const
    {
        if (esVacia())
            throw EListaVacia();
        return _prim->_elem;
    }

    /**
     Devuelve el valor almacenado en la última posición
     de la lista (a la derecha).
     Es un error preguntar por el primero de una lista vacía.

     ultimo(Cons(x, xs)) = x           SI esVacia(xs)
     ultimo(Cons(x, xs)) = ultimo(xs)  SI !esVacia(xs)
     error ultimo(ListaVacia)

     @return Elemento en la cola de la lista.
     */
    const T &ultimo() const
    {
        if (esVacia())
            throw EListaVacia();

        return _ult->_elem;
    }

    /**
     Elimina el primer elemento de la lista.
     Es un error intentar obtener el resto de una lista vacía.

     resto(Cons(x, xs)) = xs
     error resto(ListaVacia)
     */
    void resto()
    {
        if (esVacia())
            throw EListaVacia();

        Nodo *aBorrar = _prim;
        _prim = _prim->_sig;
        borraElem(aBorrar);
        if (_prim == NULL)
            _ult = NULL;
        --_numElems;
    }

    /**
     Elimina el último elemento de la lista.
     Es un error intentar obtener el inicio de una lista vacía.

     inicio(Cons(x, ListaVacia)) = ListaVacia
     inicio(Cons(x, xs)) = Cons(x, inicio(xs)) SI !esVacia(xs)
     error inicio(ListaVacia)
     */
    void inicio()
    {
        if (esVacia())
            throw EListaVacia();

        Nodo *aBorrar = _ult;
        _ult = _ult->_ant;
        borraElem(aBorrar);
        if (_ult == NULL)
            _prim = NULL;
        --_numElems;
    }

    /**
     Operación observadora para saber si una lista
     tiene o no elementos.

     esVacia(ListaVacia) = true
     esVacia(Cons(x, xs)) = false

     @return true si la lista no tiene elementos.
     */
    bool esVacia() const
    {
        return _prim == NULL;
    }

    /**
     Devuelve el número de elementos que hay en la
     lista.
     numElems(ListaVacia) = 0
     numElems(Cons(x, xs)) = 1 + numElems(xs)

     @return Número de elementos.
     */
    unsigned int numElems() const
    {
        return _numElems;
    }

    /**
     Devuelve el elemento i-ésimo de la lista, teniendo
     en cuenta que el primer elemento (primero())
     es el elemento 0 y el último es numElems()-1,
     es decir idx está en [0..numElems()-1].
     Operación observadora parcial que puede fallar
     si se da un índice incorrecto. El índice es
     entero sin signo, para evitar que se puedan
     pedir elementos negativos.

     elem(0, Cons(x, xs)) = x
     elem(n, Cons(x, xs)) = elem(n-1, xs) si n > 0
     error elem(n, xs) si !( 0 <= n < numElems(xs) )
     */
    const T &elem(unsigned int idx) const
    {
        if (idx >= _numElems)
            throw EAccesoInvalido();

        Nodo *aux = _prim;
        for (int i = 0; i < idx; ++i)
            aux = aux->_sig;

        return aux->_elem;
    }

    /**
     Clase interna que implementa un iterador sobre
     la lista que permite recorrer la lista e incluso
     alterar el valor de sus elementos.
     */
    class Iterador
    {
    public:

        void avanza()
        {
            if (_act == NULL) throw EAccesoInvalido();
            _act = _act->_sig;
        }

        const T &elem() const
        {
            if (_act == NULL) throw EAccesoInvalido();
            return _act->_elem;
        }

        void pon(const T &elem)
        {
            if (_act == NULL) throw EAccesoInvalido();
            _act->_elem = elem;
        }

        bool operator==(const Iterador &other) const
        {
            return _act == other._act;
        }

        bool operator!=(const Iterador &other) const
        {
            return !(this->operator==(other));
        }
    protected:
        // Para que pueda construir objetos del
        // tipo iterador
        friend class Lista;

        Iterador() : _act(NULL)
        {
        }

        Iterador(Nodo *act) : _act(act)
        {
        }

        // Puntero al nodo actual del recorrido
        Nodo *_act;
    };

    /**
     Devuelve el iterador al principio de la lista.
     @return iterador al principio de la lista;
     coincidirá con final() si la lista está vacía.
     */
    Iterador principio()
    {
        return Iterador(_prim);
    }

    /**
     @return Devuelve un iterador al final del recorrido
     (fuera de éste).
     */
    Iterador final() const
    {
        return Iterador(NULL);
    }

    /**
     Permite eliminar de la lista el elemento
     apuntado por el iterador que se pasa como parámetro.
     El iterador recibido DEJA DE SER VÁLIDO. En su
     lugar, deberá utilizarse el iterador devuelto, que
     apuntará al siguiente elemento al borrado.
     @param it Iterador colocado en el elemento que se
     quiere borrar.
     @return Nuevo iterador colocado en el elemento siguiente
     al borrado (podría coincidir con final() si el
     elemento que se borró era el último de la lista).
     */
    Iterador borra(const Iterador &it)
    {
        if (it._act == NULL)
            throw EAccesoInvalido();

        // Cubrimos los casos especiales donde
        // borramos alguno de los extremos
        if (it._act == _prim)
        {
            resto();
            return Iterador(_prim);
        }
        else if (it._act == _ult)
        {
            inicio();
            return Iterador(NULL);
        }
        else
        {
            // El elemento a borrar es interno a la lista.
            --_numElems;
            Nodo *sig = it._act->_sig;
            borraElem(it._act);
            return Iterador(sig);
        }
    }

    /**
     Método para insertar un elemento en la lista
     en el punto marcado por el iterador. En concreto,
     se añade _justo antes_ que el elemento actual. Es
     decir, si it==l.primero(), el elemento insertado se
     convierte en el primer elemento (y el iterador
     apuntará al segundo). Si it==l.final(), el elemento
     insertado será el último (e it seguirá apuntando
     fuera del recorrido).
     @param elem Valor del elemento a insertar.
     @param it Punto en el que insertar el elemento.
     */
    void insertar(const T &elem, const Iterador &it)
    {

        // Caso especial: ¿añadir al principio?
        if (_prim == it._act)
        {
            Cons(elem);
        }
        else
            // Caso especial: ¿añadir al final?
            if (it._act == NULL)
        {
            ponDr(elem);
        }
            // Caso normal
        else
        {
            insertaElem(elem, it._act->_ant, it._act);
        }
    }

    // //
    // MÉTODOS DE "FONTANERÍA" DE C++ QUE HACEN VERSÁTIL
    // A LA CLASE
    // //

    /** Constructor copia */
    Lista(const Lista<T> &other) : _prim(NULL), _ult(NULL)
    {
        copia(other);
    }

    /** Operador de asignación */
    Lista<T> &operator=(const Lista<T> &other)
    {
        if (this != &other)
        {
            libera();
            copia(other);
        }
        return *this;
    }

    /** Operador de comparación. */
    bool operator==(const Lista<T> &rhs) const
    {
        if (_numElems != rhs._numElems)
            return false;
        Nodo *p1 = _prim;
        Nodo *p2 = rhs._prim;
        while ((p1 != NULL) && (p2 != NULL))
        {
            if (p1->_elem != p2->_elem)
                return false;
            p1 = p1->_sig;
            p2 = p2->_sig;
        }

        return (p1 == NULL) && (p2 == NULL);
    }

    bool operator!=(const Lista<T> &rhs) const
    {
        return !(*this == rhs);
    }


protected:

    void libera()
    {
        libera(_prim);
        _prim = NULL;
        _ult = NULL;
    }

    void copia(const Lista<T> &other)
    {
        // En vez de trabajar con punteros en la inserción,
        // usamos ponDr
        _prim = 0;
        _numElems = 0;

        Nodo *act = other._prim;
        while (act != NULL)
        {
            ponDr(act->_elem);
            act = act->_sig;
        }
    }

private:

    /**
     Inserta un elemento entre el nodo1 y el nodo2.
     Devuelve el puntero al nodo creado.
     Caso general: los dos nodos existen.
        nodo1->_sig == nodo2
        nodo2->_ant == nodo1
     Casos especiales: alguno de los nodos no existe
        nodo1 == NULL y/o nodo2 == NULL
     */
    static Nodo *insertaElem(const T &e, Nodo *nodo1, Nodo *nodo2)
    {
        Nodo *nuevo = new Nodo(nodo1, e, nodo2);
        if (nodo1 != NULL)
            nodo1->_sig = nuevo;
        if (nodo2 != NULL)
            nodo2->_ant = nuevo;
        return nuevo;
    }

    /**
     Elimina el nodo n. Si el nodo tiene nodos antes
     o después, actualiza sus punteros anterior y siguiente.
     Caso general: hay nodos anterior y siguiente.
     Casos especiales: algunos de los nodos (anterior o siguiente
     a n) no existen.
     */
    static void borraElem(Nodo *n)
    {
        assert(n != NULL);
        Nodo *ant = n->_ant;
        Nodo *sig = n->_sig;
        if (ant != NULL)
            ant->_sig = sig;
        if (sig != NULL)
            sig->_ant = ant;
        delete n;
    }

    /**
     Elimina todos los nodos de la lista enlazada cuyo
     primer nodo se pasa como parámetro.
     Se admite que el nodo sea NULL (no habrá nada que
     liberar). En caso de pasarse un nodo válido,
     su puntero al nodo anterior debe ser NULL (si no,
     no sería el primero de la lista!).
     */
    static void libera(Nodo *prim)
    {
        assert(!prim || !prim->_ant);

        while (prim != NULL)
        {
            Nodo *aux = prim;
            prim = prim->_sig;
            delete aux;
        }
    }

    // Puntero al primer y último elemento
    Nodo *_prim, *_ult;

    // Número de elementos (número de nodos entre _prim y _ult)
    unsigned int _numElems;
};

/* FIN "#include TADs EDA" */

#define USE_STL FALSE

#include <vector>
#include <cmath>

template<typename T>
class ListWrapper
{
private:
    Lista<T> _underlying_tad;
public:

    class iterator
    {
        friend class ListWrapper; //Para poder "toquitear"
    private:
        typename Lista<T>::Iterador _underlying_iterator;
    public:
        typedef typename Lista<T>::Iterador UnderLyingIterator;

        iterator(const UnderLyingIterator& it) : _underlying_iterator(it)
        {
        }

        iterator& operator++()
        {
            _underlying_iterator.avanza();
            return *this;
        }

        iterator operator++(int dummy_paramater_to_diff_preincrement)
        {
            iterator temp(*this);
            operator++();
            return temp;
        }

        bool operator==(const iterator& it)
        {
            return _underlying_iterator == it._underlying_iterator;
        }

        bool operator!=(const iterator& it)
        {
            return !(*this == it);
        }

        const T& operator*()
        {
            return _underlying_iterator.elem();
        }

        typename enable_if<is_class<T>::value, const T*>::type
        operator->() //Efectos bastante graciosos de la compleja sintaxis de C++: http://stackoverflow.com/questions/1642028/what-is-the-name-of-this-operator Mientras x vaya hacia a cero, la verdad es que es ingenioso...
        {
            return &_underlying_iterator.elem();
        }
    };

    iterator begin()
    {
        return iterator(_underlying_tad.principio());
        /* RVO? quiero creer que si... */
    }

    iterator end()
    {
        return iterator(_underlying_tad.final());
    }

    unsigned int size()
    {
        return _underlying_tad.numElems();
    }

    bool empty()
    {
        return _underlying_tad.esVacia();
    }

    T& first()
    {
        return static_cast<T&> (_underlying_tad.primero());
    }

    T& last()
    {
        return static_cast<T&> (_underlying_tad.ultimo());
    }

    T& operator[](unsigned int index) {
        return static_cast<T&> (_underlying_tad.elem(index));
    }

    //O(n)...

    void insert(const T& value, unsigned int index)
    {
        if (index < 0 || index >= size()) return;
        typename Lista<T>::Iterador it = _underlying_tad.principio();

        for (unsigned int i = 0; i < index; ++i)
        {
            it.avanza();
        }

        _underlying_tad.insertar(value, it);
    }

    void insert(const T& value, iterator it)
    {
        _underlying_tad.insertar(value, it._underlying_iterator);
    }

    void push_back(const T& value)
    {
        _underlying_tad.ponDr(value);
    }

    void push_front(const T& value)
    {
        _underlying_tad.insertar(value, _underlying_tad.principio());
    }

    void pop_back()
    {
        _underlying_tad.borra(_underlying_tad.final());
    }

    void pop_front()
    {
        _underlying_tad.borra(_underlying_tad.principio());
    }
};

/*************************************************************
 * Implementación de cola de prioridad usando un heap máximo *
 ************************************************************/

template<typename T>
class MaxHeap
{
private:
#if USE_STL
    std::vector<T> _heap_array;
#else
    ListWrapper<T> _heap_array; //Uuuh, que elegante, ocupan lo mismo...
#endif /* USE STL */

    unsigned int _less_child(unsigned int parent)
    {
        return 2 * parent + 1;
    }

    unsigned int _bigger_child(unsigned int parent)
    {
        return 2 * parent + 2;
    }

    unsigned int _parent(unsigned int child)
    {
        return (unsigned int) std::floor(child / 2.0f);
    }

    bool _is_root(unsigned int index)
    {
        return index == 0;
    }

public:

    void insert(const T& value)
    {
        _heap_array.push_back(value); //Insertamos el valor al final del arbol
        unsigned int index = _heap_array.size() - 1; //Empieza en el ultimo elemento.

        while (!_is_root(index) && _heap_array[index] > _heap_array[_parent(index)])
        {
            //swap index <--> root_index. C++14 swap operator? ( :=: ) Like python?
            T& tmp = _heap_array[index];
            _heap_array[index] = _heap_array[_parent(index)];
            _heap_array[_parent(index)] = tmp;

            index = _parent(index);
        }
    }

    //Erases the root (The maximum value)

    T erase()
    {
        unsigned int index = _heap_array.size() - 1; //Empieza en el ultimo elemento.

        T ret(_heap_array.first());
        _heap_array.first() = _heap_array.last(); //Ponemos el ultimo elemento en la raiz.
        //Después reordenamos el arbol:

        while (index < _heap_array.size() - 1 && _heap_array[index] < _heap_array[_bigger_child(index)])
        {
            //swap index <--> index_greater_child. C++14 swap operator? ( :=: ) Like python?
            T& tmp = _heap_array[index];
            _heap_array[index] = _heap_array[_bigger_child(index)];
            _heap_array[_bigger_child(index)] = tmp;

            index = _bigger_child(index);
        }

        _heap_array.pop_back(); //Eliminamos el ultimo (Lo pusimos en la raiz al principio).

        return ret; //RVO? Seguramente
    }

    const T& max()
    {
        return static_cast<const T&> (_heap_array.first());
    }
};

template<typename T>
class PriorityQueue : public MaxHeap<T>
{
public:

    void operation1(const T& value)
    {
        this->insert(value);
    }

    T operation2()
    {
        return this->erase();
    }
};

template<typename T>
class Stack
{
private:
#if USE_STL
    std::vector<T> _data;
#else
    ListWrapper<T> _data;
#endif /* STL */
public:

    void operation1(const T& value)
    {
        _data.push_back(value);
    }

    T operation2()
    {
        T tmp(_data.last());
        _data.pop_back();
        return tmp;
    }
};

template<typename T>
class Queue
{
private:
#if USE_STL
    std::vector<T> _data;
#else
    ListWrapper<T> _data;
#endif /* STL */
public:

    void operation1(const T& value)
    {
        _data.push_front(value);
    }

    T operation2()
    {
        T tmp(_data.last());
        _data.pop_back();
        return tmp;
    }
};

int main()
{
    return 0;
}

