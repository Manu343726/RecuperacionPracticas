/* 
 * File:   main.cpp
 * Author: Manu343726
 *
 * Created on 1 de junio de 2013, 12:21
 */

#include <iostream>
using namespace std;

//NOTA: Antes de nada me gustaría disculparme por si parece que mis anotaciones son algo "bizarras". Las voy escribiendo para aclararme, 
//      y me gusta dejarlas para dejar bien claro por qué hago las cosas de cierta manera.

/***********************************************************************************************************************
* Herramientes para depuración                                                                                         *
*                                                                                                                      *
* Las cabeceras utilizadas para depuración se encuentran en el subdirectorio utils/, no incluido en la entrega.        *
* Los archivos en cuestión son:                                                                                        *
*  - dl32Config.h: Es el archivo de configuración general. Lo necesitan el resto de cabeceras.                         *
*    https://github.com/Manu343726/cpp_lib32/blob/BigRefactoring/code/headers/utils/dl32Config.h                       * 
*  - dl322Exceptions.h: Archivo con las definiciones de excepciones básicas. Lo mismo, necesario para el resto.        *
*    https://github.com/Manu343726/cpp_lib32/blob/BigRefactoring/code/headers/dl32Exceptions.h                         *
*  - dl32ConsoleColor.h: Sistema de cambio de estilo (Color de fuente/fondo) de consola basado en interfaces fluidas.  *  
*    Lo uso en mi assert, y para depurar (Con colorines todo se ve mas claro...).                                      *
*    https://github.com/Manu343726/cpp_lib32/blob/BigRefactoring/code/headers/utils/dl32ConsoleColor.h                 *
*  - dl32ConsoleColor.cpp Implementación del sistema. Solo versión para windows (Por ahora).                           *
*    https://github.com/Manu343726/cpp_lib32/blob/BigRefactoring/code/source/utils/dl32ConsoleColor.cpp                *
*                                                                                                                      *
* NOTA: Estos archivos han sido modificados ligeramente para hacerlos compatibles con C++98/03.                        *
*                                                                                                                      *
* Me he acostumbrado a utilizar estas macros para depurar: En un primer momento utilizo mi versión de assert,          *
* el cual escribe los resultados en pantalla, y cuando estoy más o menos seguro, activo el assert de C.                *
*                                                                                                                      *
* Cuento todo ésto para pasar por encima todas las "cosas raras" que puedan encontrarse durante la corrección.         *
*                                                                                                                      *
* Desactivando el modo de depuración, se deshabilitan todos esos includes (Para seguir a rajatabla las reglas de la    *
* entrega) y se deshabilita también la macro assert.                                                                   *
***********************************************************************************************************************/

//#define DEBUGGING

#ifdef DEBUGGING

#include "utils/dl32Config.h" //Booleanos, entre otras cosas
#include "utils/dl32ConsoleColor.h" //Colorines para depurar

#define DEBUGGING_USECASSERT  FALSE
#define DEBUGGING_WAIT_AT_END FALSE
#define DEBUGGING_USE_COLOR   TRUE
#define DEBUGGING_ASSERT_LONG_FORMAT FALSE


#define EXPAND(x) x

#if DEBUGGING_USECASSERT
#ifdef NDEBUG
#undef NDEBUG
#endif /* NDEBUG */

#include <assert.h>
#else

#if DEBUGGING_ASSERT_LONG_FORMAT
#define assert_data(x) __FILE__ << ", in function '" << __FUNCTION__  << "' (line " <<  __LINE__ << "):" << " '" << #x << "' --> "
#else 
#define assert_data(x) "'" << #x << "' --> "
#endif /* SHORT FORMAT */

#if DEBUGGING_USE_COLOR

//#include "utils/dl32ConsoleColor.h" //NOTA: Implementación basada únicamente en Win32 API. Versión UNIX no disponible todavía.

#ifdef assert
#undef assert
#endif /* ASSERT */

#define assert(x) (x) ? cout << push_style << dl32ChangeForegroundColor( LIGHTGREEN )  << assert_data(x) << "SUCCESS" << pop_style << endl : cout << push_style << dl32ChangeForegroundColor( LIGHTRED ) << assert_data(x) << "FAIL (Cascao raro)" << pop_style << endl 
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

/********************************
 * WARNING: ENTERING FREAK-ZONE *
 *******************************/

/* enable_if necesario para wrapper de iterador (operator-> solo tiene sentido para clases, no para tipos básicos) */
template<bool flag, typename T>
struct enable_if;

template<typename T>
struct enable_if<true, T>
{
    typedef T type; //Hay, como echo de menos mi using...
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
        char dummy[2];//El tamaño exacto depende de la implementación/SO, pero si sabes que siempre es mas grande que el otro, que es lo que importa.
    } _big;

    static const unsigned int _small_size = sizeof (_small);
    static const unsigned int _big_size   = sizeof (_big);

    template<typename U> static _small _checker(void(U::*)());
    template<typename U> static _big   _checker(...);
public:
    static const bool value = sizeof ( _checker<T>(NULL)) == _small_size;
};

/*********************
 * END OF FREAK-ZONE *
 ********************/

/******************************************************************************************************************
 *  _                       _                                               _                                   _  *
 * | |    __ _    ___ _ __ | |_ _ __ ___  __ _  __ _    ___ _ __ ___  _ __ (_) ___ ______ _    __ _  __ _ _   _(_) *
 * | |   / _` |  / _ \ '_ \| __| '__/ _ \/ _` |/ _` |  / _ \ '_ ` _ \| '_ \| |/ _ \_  / _` |  / _` |/ _` | | | | | *
 * | |__| (_| | |  __/ | | | |_| | |  __/ (_| | (_| | |  __/ | | | | | |_) | |  __// / (_| | | (_| | (_| | |_| | | *
 * |_____\__,_|  \___|_| |_|\__|_|  \___|\__, |\__,_|  \___|_| |_| |_| .__/|_|\___/___\__,_|  \__,_|\__, |\__,_|_| *
 *                                       |___/                       |_|                               |_|         *
 ******************************************************************************************************************/

/* "#include TADs EDA" */

//NOTA: He parloteado tanto que no me cabía el código en la UVA. He borrado la documentación de los TADs.

/* EXCEPCIONES */

#include <string>
#include <iosfwd>

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

DECLARA_EXCEPCION(EPilaVacia);
DECLARA_EXCEPCION(EPilaLlena);
DECLARA_EXCEPCION(EColaVacia);
DECLARA_EXCEPCION(EDColaVacia);
DECLARA_EXCEPCION(EListaVacia);
DECLARA_EXCEPCION(EAccesoInvalido);

/* LISTA */
template <class T>
class Lista
{
private:
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
    void Cons(const T &elem)
    {
        _numElems++;
        _prim = insertaElem(elem, NULL, _prim);
        if (_ult == NULL)
            _ult = _prim;
    }
    void ponDr(const T &elem)
    {
        _numElems++;
        _ult = insertaElem(elem, _ult, NULL);
        if (_prim == NULL)
            _prim = _ult;
    }
    const T &primero() const
    {
        if (esVacia())
            throw EListaVacia();
        return _prim->_elem;
    }
    const T &ultimo() const
    {
        if (esVacia())
            throw EListaVacia();

        return _ult->_elem;
    }
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
    bool esVacia() const
    {
        return _prim == NULL;
    }
    unsigned int numElems() const
    {
        return _numElems;
    }
    const T &elem(unsigned int idx) const
    {
        if (idx >= _numElems)
            throw EAccesoInvalido();

        Nodo *aux = _prim;
        for (int i = 0; i < idx; ++i)
            aux = aux->_sig;

        return aux->_elem;
    }
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
    static Nodo *insertaElem(const T &e, Nodo *nodo1, Nodo *nodo2)
    {
        Nodo *nuevo = new Nodo(nodo1, e, nodo2);
        if (nodo1 != NULL)
            nodo1->_sig = nuevo;
        if (nodo2 != NULL)
            nodo2->_ant = nuevo;
        return nuevo;
    }
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

#include <cmath>

#define USE_STL

#ifdef USE_STL
#include <vector>
#else
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Un wrapper de la lista enlazada de la asignatura para que tenga la misma interfaz que std::vector.
///
/// @author	Manu343726
///////////////////////////////////////////////////////////////////////////////////////////////////////
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
    };

    iterator begin()
    {
        return iterator(_underlying_tad.principio());
    }

    iterator end()
    {
        return iterator(_underlying_tad.final());
    }

    unsigned int size() const
    {
        return _underlying_tad.numElems();
    }

    bool empty() const
    {
        return _underlying_tad.esVacia();
    }

    T& front()
    {
        return const_cast<T&> (_underlying_tad.primero());
    }
    
    T& back()
    {
        return const_cast<T&> (_underlying_tad.ultimo());
    }

    T& operator[](unsigned int index) 
    {
        return const_cast<T&> (_underlying_tad.elem(index));
    }

    //O(n)... Creo que al final no la uso (De hecho, creo que me la he inventado... que la de std::vector no es así...)
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

    void insert(const iterator& it , const T& value)
    {
        _underlying_tad.insertar(value, it._underlying_iterator);
    }
    
    void erase(const iterator& it)
    {
        _underlying_tad.borra( it._underlying_iterator );
    }

    void push_back(const T& value)
    {
        _underlying_tad.ponDr(value);
    }

    void pop_back()
    {
        _underlying_tad.inicio();//No es por criticar, pero no vendría nada mal una revisión de los nombres de los TADs, porque son de todo menos intuitivos. "inicio", una función que borra el último elemento? El nombre lo entiendo (Te quedas con la parte "inicial" de la lista), pero...
    }

    void pop_front()//Esta también me la he inventado, tampoco está en std::vector<T>
    {
        _underlying_tad.resto(); //No es por criticar, pero no vendría nada mal una revisión de los nombres de los TADs, porque son de todo menos intuitivos. "resto", una función que borra el primer elemento? 
    }
};
#endif

/*
 *Tampoco estaría mal, como comentaste el otro día en clase, incluir un vector. Mas que nada, porque en contra de lo que piensa la mayoría de 
 *la gente, hoy en día las listas enlazadas son bastante más lentas que los vectores (La caché manda). 
 * 
 *He encontrado una entrada en stackoverflow (http://stackoverflow.com/questions/9764452/comprehensive-vector-vs-linked-list-benchmark-for-randomized-insertions-deletion) 
 *donde mencionan el tema, precisamente hablando de la conferencia que te comenté en clase donde Stroupstrup hacía comparativas de rendimiento entre ambas cosas.
 * 
 *Precisamente una de las cosas en las que más insiste en las transparencias es en mantener los datos de manera lineal, cohesivos. No hacer las cosas al estilo
 *"cada cosa en una punta" como hacen los lenguajes de alto nivel (C#/Java, punterolandia).
 *Es cierto que los accesos son aleatorios, lo que implica O(n) en la lista enlazada. Pero, realmente ganas algo con la lista enlazada? Veamos:
 * 
 *        OPERACION                    |                              VECTOR                                                                                  |                 LISTA
 * ------------------------------------+----------------------------------------------------------------------------------------------------------------------+-----------------------------------------------------
 * push_back                           |  O(1) en la mayoría de los casos (Promedio).                                                                         |  O(1) (Lista doblemente enlazada). (Siempre alloc).
 * push_front                          |  O(n) vale, aquí gana la lista por goleada. Por algo std::vector no lo implementa.                                   |  O(1) (Siempre alloc)
 * pop_back                            |  O(1) (Promedio)                                                                                                     |  O(1) (Siempre alloc)
 * pop_front                           |  O(n) Igual que su hermana, push_front. (VER NOTA INFERIOR).                                                         |  O(1) (siempre dealloc)
 * erase (Random access)               |  O(n) NOTA: No recuerdo (No debería, mantiene el orden) si std::vector implementa swap-end, en ese caso sería O(1).  |  O(1) (Siempre dealloc)
 * at (Aka operator[], random access)  |  O(1) más barato imposible.                                                                                          |  O(n) (+ penalización de caché)
 * 
 * La lista enlazada tiene dos problemas muy grandes: Caché (Puntero detrás de puntero...) y allocations (Para todas las operaciones hace alloc/dealloc, y las peticiones de memoria son muuuuuuy caras).
 * Para acceso secuencial, es cierto que se pueden usar iteradores. Pero aún así el redimiento de vector sigue siendo superior (La lista es un tren de punteros, la caché se vuelve loca...).
 * Y por supuesto, el uso de memoria: La lista utiliza 2* tamaño puntero por cada nodo, lo que se traduce en que suele ocupar mas del doble que vector.
 * 
 * Al final la conclusión a la que llegas, es que salvo para ciertas cosas (Implementación de colas y poco más) vector siempre gana por goleada (Al final lo que cuenta es el promedio, me da igual
 * el caso peor, si en el 95% de los casos es bastante más rápido), para el tipo de accessos/operaciones que se suelen hacer.
 * 
 *Aunque no está muy claro, el timing que se ha hecho ésta gente sale acorde con ésto. Personalmente no me he puesto a hacer timmings por mi cuenta.
 *
 *PD: Me he fijado que el enlace que está en el post está roto (Es el enlace del MSDN es raro...La presentación está en Channel 9): http://www.ii.uni.wroc.pl/~nivelle/C++11_style_Wroclaw.pdf
*/
/*************************************************************
 * Implementación de cola de prioridad usando un heap máximo *
 ************************************************************/

template<typename T>
class MaxHeap
{
private:
#ifdef USE_STL
    std::vector<T> _heap_array;
#else
    ListWrapper<T> _heap_array; //Uuuh, que elegante, ocupan lo mismo...
#endif /* USE STL */

    static unsigned int _less_child(unsigned int parent)
    {
        return 2 * parent + 1;
    }

    static unsigned int _bigger_child(unsigned int parent)
    {
        return 2 * parent + 2;
    }

    static unsigned int _parent(unsigned int child)
    {
        return (unsigned int) std::floor(child / 2.0f);
    }

    static bool _is_root(unsigned int index)
    {
        return index == 0;
    }
 
#ifdef DEBUGGING
    dl32ConsoleColor _get_color(unsigned int i)
    {
        static const dl32ConsoleColor COLOR_TABLE[] = { LIGHTBLUE , LIGHTGREEN , LIGHTAQUA , LIGHTRED , LIGHTPURPLE , LIGHTYELLOW , BRIGHTWHITE };
        
        return COLOR_TABLE[i % 7];
    }
    
    void _print()
    {
        cout << push_style << FOREGROUND << BLACK;
        
        for(unsigned int i = 0; i < _heap_array.size() ; ++i)
            cout << BACKGROUND << _get_color(_heap_array[i]) /* cada nodo tiene un color, así es mas facil ver como cambia el heap */ << _heap_array[i] << BACKGROUND << BLACK << " ";
        
        cout << pop_style << endl;
    }
#endif
public:
    bool empty() const {return _heap_array.empty(); }

    //Las trazas de las funciones quedan de la siguiente manera: https://twitter.com/Manu343726/status/341236064263995392/photo/1
    //Me era mas facil de ver con colores.
    
    void insert(const T& value)
    {
        unsigned int index;
#ifdef DEBUGGING
        cout << push_style << FOREGROUND << YELLOW << "Starting insert... (Pushing " << value << ")" << pop_style << endl;
        cout << "BEGINING HEAP: "; _print();
#endif     
        _heap_array.push_back( value );
        index = _heap_array.size() - 1;
 
#ifdef DEBUGGING
        cout << "(pushback)"; _print();
#endif     
        while( !_is_root( index ) && _heap_array[index] > _heap_array[_parent( index )] )
        {
#ifdef DEBUGGING
            cout << push_style << FOREGROUND << YELLOW << "swapping node " << _heap_array[index] << " (index " << index << ") with its parent (node " << _heap_array[_parent(index)] << ", index " << _parent( index ) << ")" << pop_style << endl;
#endif
            
            T tmp( _heap_array[index] );
            _heap_array[index] = _heap_array[_parent( index )];
            _heap_array[_parent( index )] = tmp;
            
            index = _parent( index );
        }
        
#ifdef DEBUGGING
        cout << "END HEAP: "; _print();
        cout << push_style << FOREGROUND << YELLOW << "Insert finished" << pop_style << endl;
#endif
    }

    //Erases the root (The maximum value)
    T erase()
    {
        if( _heap_array.empty() ) return T();
   
#ifdef DEBUGGING
        cout << push_style << FOREGROUND << YELLOW << "Starting erase..." << pop_style << endl;
        cout << "BEGINING HEAP: "; _print();
#endif       
        unsigned int index = 0; //Empieza en la raiz.
        
        T ret( _heap_array.front() );
        
        _heap_array.front() = _heap_array.back();
        _heap_array.pop_back();
#ifdef DEBUGGING
        cout << "(lesser swapped to front)"; _print();
#endif      
        _re_heap_tree(0);
  
#ifdef DEBUGGING 
        cout << "END HEAP: "; _print();
        cout << push_style << FOREGROUND << YELLOW << "erase finished (value " << ret << " popped)" << pop_style << endl;      
#endif
        return ret; //NRVO si no recuerdo mal. Hay que confiar en el optimizador...
    }
    
    //Si, lo he copiado del pseudocódigo de la wikipedia. Me estaba haciendo un lío con la versión iterativa.
    void _re_heap_tree(unsigned int node)
    {
        unsigned int largest = node;
        unsigned int less    = _less_child( largest );
        unsigned int bigger  = _bigger_child( largest );
        
        if( less < _heap_array.size() && _heap_array[less] > _heap_array[largest] )
            largest = less;
        
        if( bigger < _heap_array.size() && _heap_array[bigger] > _heap_array[largest] )
            largest = bigger;
        
        if( node != largest)
        {
            T tmp = _heap_array[node];
            _heap_array[node] = _heap_array[largest];
            _heap_array[largest] = tmp;
            
#ifdef DEBUGGING
            cout << push_style << FOREGROUND << YELLOW << "re_heapping... Actual: " << pop_style; _print();
#endif
            _re_heap_tree(largest);
        }
    }

    const T& top()
    {
        return static_cast<const T&> (_heap_array.front());
    }
};

#if !defined( USE_STL )

template<typename T>
class PriorityQueue : public MaxHeap<T>
{
public:

    void operation1(const T& value)
    {
        this->insert(value); //this necesario por ambiguedad al heredar de plantillas (Por qué nunca me acuerdo, siempre tengo que volver a buscarlo?) 
                             //http://stackoverflow.com/questions/4643074/why-do-i-have-to-access-template-base-class-members-through-the-this-pointer  
                             //También conocido como: "Hola, me llamo C++, y tardo veinte años en compilar"
                             //La verdad es que es mejor eso que cuando tienes que usar this->template function<template_parameter>() porque no tiene ni ida de lo que le estás diciendo...
    }

    T operation2()
    {
        return this->erase();
    }
};
#else
#include <queue>

template<typename T>
class PriorityQueue
{
private: 
    std::priority_queue<int,std::vector<int>,std::less<int> > _queue;
public:

    void operation1(const T& value)
    {
        _queue.push(value); 
    }

    T operation2()
    {
        T tmp( _queue.top() );
        _queue.pop();
        return tmp; //Esto si que si, NRVO.
    }
    
    bool empty() const {return _queue.empty(); }
    unsigned int size() const {return _queue.size(); }
    const T& top() const { return _queue.top(); }
};
#endif

template<typename T>
class Stack
{
private:
#ifdef USE_STL
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
        T tmp(_data.back());
        _data.pop_back();
        return tmp;
    }
    
    bool empty() const {return _data.empty(); }
};

template<typename T>
class Queue
{
private:
#ifdef USE_STL
    std::vector<T> _data;
#else
    ListWrapper<T> _data;
#endif /* STL */
public:

    void operation1(const T& value)
    {
        _data.insert( _data.begin() , value );
    }

    T operation2()
    {
        T tmp(_data.back());
        _data.pop_back();
        return tmp;
    }
    
    bool empty() const {return _data.empty(); }
};

enum TADOperation
{
    OP1 = 1, OP2 = 2
};

struct TADType
{
    bool couldBeStack;
    bool couldBeQueue;
    bool couldBePriorityQueue;

    //Deprecated in modern C++, use static const string instead. In modern C++, raw strings are std::string, not const char*.
    //Lo pongo porque GCC no hace más que refunfuñar. Estoy con GCC8.0, en modo C++98, pero aún así refunfuña.
    static const char* IS_STACK;
    static const char* IS_QUEUE;
    static const char* IS_PRIORITY_QUEUE;
    static const char* COULD_BE_MORE_THAN_ONE_TAD;
    static const char* IS_NOT_ANY_OF_OUR_TADS;

    TADType() : couldBeStack(true), couldBeQueue(true), couldBePriorityQueue(true)
    {
    }

    const char* result()
    {
        //A que habría molado hacerlo con un bitset y una lookup table?

        if (couldBeStack && !couldBeQueue && !couldBePriorityQueue) return IS_STACK;
        if (!couldBeStack && couldBeQueue && !couldBePriorityQueue) return IS_QUEUE;
        if (!couldBeStack && !couldBeQueue && couldBePriorityQueue) return IS_PRIORITY_QUEUE;

        if (!couldBeStack && !couldBeQueue && !couldBePriorityQueue) return IS_NOT_ANY_OF_OUR_TADS;

        return COULD_BE_MORE_THAN_ONE_TAD;
    }
};

const char* TADType::IS_STACK = "stack";
const char* TADType::IS_QUEUE = "queue";
const char* TADType::IS_PRIORITY_QUEUE          = "priority queue";
const char* TADType::COULD_BE_MORE_THAN_ONE_TAD = "not sure";
const char* TADType::IS_NOT_ANY_OF_OUR_TADS     = "impossible";

inline bool is_valid(TADOperation op)//Creo que al final no la he usado
{
    return op == OP1 || op == OP2;
}

istream& operator>>(istream& is , TADOperation& op)
{
    int integer;
    is >> integer;
    op = (TADOperation)integer;
    return is;
}

void UVA11995(istream& is)
{
    while (is.good()) // is good, muy apropiado...
    {
        unsigned int set_operations_count;
        TADType results;
        Stack<int> stack;
        Queue<int> queue;
        PriorityQueue<int> priority_queue;

        is >> set_operations_count;

        for (unsigned int i = 0; i < set_operations_count; ++i)
        {
            TADOperation operation;
            int aux_value;

            is >> operation;
            is >> aux_value;

            switch (operation)
            {
                case OP1:
                    stack.operation1(aux_value);
                    queue.operation1(aux_value);
                    priority_queue.operation1(aux_value);
                    break;
                case OP2:
                    //NOTA: Es cierto, son operadores de bits, no lógicos, C++ no provee &&= o ||=. Pero funciona como se espera (true es 0x00000001 y false es 0x00000000)
                    results.couldBeStack &= !stack.empty() && stack.operation2() == aux_value; //Lo malo de que no sean operadores lógicos, es que no tienen lazy-evaluation. Si fuera así, en el momento en el que could fuera false, no volvería a ejecutar nada de ésto (Lo que estaría muy bien).
                    results.couldBeQueue &= !queue.empty() && queue.operation2() == aux_value;
                    results.couldBePriorityQueue &= !priority_queue.empty() && priority_queue.operation2() == aux_value;
                    break;
                default:
                    throw "ERROR AL LEER LA ENTRADA (CABUUUUUUM!)";//Espero no ver ningún cabuum...
            }
        }

        cout << results.result() << endl;
    }
}

#define PRIORITY_QUEUE_TEST

#if defined(PRIORITY_QUEUE_TEST) && defined(DEBUGGING)

#if !defined(USE_STL) //Si estoy usando la stl, queue ya se incluyó en MaxHeap.
#include <queue>
#endif

#include <stdlib.h> //La STL actualmente provee ua biblioteca entera con tropecientos generadores de numeros pseudoaleatorios: http://en.cppreference.com/w/cpp/numeric/random
#include <time.h>
#include <mmsystem.h>

const unsigned int TESTS_COUNT = 1000;

void test()
{
    PriorityQueue<int> my_queue;
    std::priority_queue<int,std::vector<int>,std::less<int> > stl_queue;
    
    srand( time(NULL) );
    
    unsigned int pass_count  = 0;
    unsigned int fail_count  = 0;
    unsigned int total_tests = 0;
    
    unsigned int push_fails = 0;
    unsigned int push_pass  = 0;
    unsigned int pop_fails = 0;
    unsigned int pop_pass  = 0;
    
    bool passed;
    
#define internal_assert(x) assert( passed = (x) ); total_tests++; if( passed ) { pass_count++; } else { fail_count++; }
#define assert_push(x) internal_assert(x); if( passed ) { push_pass++; } else { push_fails++; }
#define assert_pop(x)  internal_assert(x); if( passed ) { pop_pass++;  } else { pop_fails++; }
    
    for(unsigned int i = 0 ; i < TESTS_COUNT ; ++i)
    {
        cout << push_style << FOREGROUND << GRAY << "starting test " << i+1 << "..." << pop_style << endl;
        
        TADOperation operation = (rand() % 2 == 0) ? OP1 : OP2;
        int number_for_push    = rand();
        unsigned int actual_passed = pass_count;
        
        if( operation == OP1 )
        {
            cout << push_style << FOREGROUND << GRAY << "PUSH TEST" << pop_style << endl;
            
            my_queue.operation1( number_for_push );
            stl_queue.push( number_for_push );
            
            assert_push( my_queue.top() == stl_queue.top() );
            
            cout << push_style << FOREGROUND << GRAY << "END OF PUSH TEST" << pop_style << endl;
        }
        else
        {
            cout << push_style << FOREGROUND << GRAY << "POP TEST" << pop_style << endl;
            
            assert_pop( my_queue.empty() == stl_queue.empty() );
                    
            if( !my_queue.empty() && !stl_queue.empty() )
            {
                assert_pop( my_queue.operation2() == stl_queue.top() );
                cout << "STLQUEUE TOP: " << stl_queue.top() << endl;
                stl_queue.pop();
            }
            
            cout << push_style << FOREGROUND << GRAY << "END OF POP TEST" << pop_style << endl;
        }
    }
    
    cout << endl << "total tests executed: " << total_tests << endl;
    cout << " - Tests passed: " << pass_count << " (" << push_pass << " push tests passed. " << pop_pass << " pop tests passed)" << endl;
    cout << " - Tests failed: " << fail_count << " (" << push_fails << " push tests failed. " << pop_fails << " pop tests failed)" << endl << endl;
}

#endif /* PRIORITY_QUEUE_TEST */

int main()
{
#if defined( PRIORITY_QUEUE_TEST ) && defined( DEBUGGING )
    test();
#else
    UVA11995(cin);
#endif /* PRIORITY_QUEUE_TEST */
    return 0;
}

