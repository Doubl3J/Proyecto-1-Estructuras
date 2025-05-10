#include <iostream>
using namespace std;
#include <string>
//Para validar que el usuario use inputs correctos (integer o string dependiendo de que se pide)
#include <limits>

//Integrantes del grupo: Jose Mario Castro Cruz y Justin Jamal Morris Bains

//Fecha de incio: 14 de abril 2025
//Última modificación: 8 de mayo 2025

//Lista simple con inserción al inicio, Sublista_Canciones apunta al nodo de la canción que quiere agregar
struct Canciones {
    int ID;
    string Titulo;
    int Duracion;
    int ID_Album;
    int ID_Artista;

    Canciones * sig;

    Canciones(int id,string t,int d){
        ID = id;
        Titulo = t;
        Duracion = d;
        //Estos IDs se actualizan cuando se agreguen a un álbum o artista
        ID_Album = 0; 
        ID_Artista = 0;

        sig = nullptr;
    }

}*primeroC;

//Lista simple con inserción al final, se va a utilizar por las demás estructuras para poder conectarse con Canciones
struct Sublista_Canciones{
    Canciones * cancion;
    Sublista_Canciones * sig;

    Sublista_Canciones(Canciones * c){
        cancion = c;
        sig = nullptr;
    }
};

//Lista simple inserción al final, Sublista_Albumes apunta al nodo del álbum que quiere agregar
struct Albumes {
    int ID;
    string Titulo;
    int Anno;
    int N_canciones;

    Albumes * sig;

    Sublista_Canciones * canciones;

    Albumes(int id, string titulo, int anno) {
        ID = id;
        Titulo = titulo;
        Anno = anno;
        //Se actualiza mientras se agregan canciones
        N_canciones = 0;

        sig = nullptr;
        canciones = nullptr;
    }

}*primeroAlb;

//Lista simple con inserción al final, se va a utilizar por las demás estructuras para poder conectarse con Álbumes
struct Sublista_Albumes{
    Albumes * album;
    Sublista_Albumes * sig;

    Sublista_Albumes(Albumes * a){
        album = a;
        sig = nullptr;
    }
};


//Lista doble ordenada alfabéticamente, Sublista_Artistas apunta al nodo del artista que quiere agregar
struct Artistas {
    int ID;
    string Nombre_Artistico;
    string Nombre_Real;
    string Pais;
    string Sello_Discografico;

    Artistas * sig;
    Artistas * ant;

    Sublista_Albumes * albumes;
    Sublista_Canciones * canciones;

    //Atributos agregador para consultas
    int albumes_publicados;

    Artistas(int id,string nombre_artistico, string nombre_real, string pais){
        ID = id;
        Nombre_Artistico = nombre_artistico;
        Nombre_Real = nombre_real;
        Pais = pais;
        //Se actualiza cuando un sello discográfico lo agregue como artista
        Sello_Discografico = "Independiente";

        sig = nullptr;
        ant = nullptr;

        albumes = nullptr;
        canciones = nullptr;

        albumes_publicados = 0;
    }

}*primeroArt;

//Lista simple con inserción al final, se va a utilizar por las demás estructuras para poder conectarse con Artistas
struct Sublista_Artistas{
    Artistas * artista;
    Sublista_Artistas * sig;

    Sublista_Artistas(Artistas * a){
        artista = a;
        sig = nullptr;
    }
};

//Lista circular con inserción al final
struct Generos_Musicales {
    int ID;
    string Nombre;
    string Descripcion;

    Generos_Musicales * sig;

    Sublista_Canciones * canciones;

    //Atributos agregados para consultas
    int numero_canciones;

    Generos_Musicales(int id, string nombre, string descripcion){
        ID = id;
        Nombre = nombre;
        Descripcion = descripcion;

        sig = nullptr;
        canciones = nullptr;

        numero_canciones = 0;
    }

}*primeroG;

//Lista simple con inserción al inicio
struct Playlist {
    int ID;
    string Nombre;
    string Creador;
    int Fecha;

    Playlist * sig;

    Sublista_Canciones * canciones;

    //Atributos agregados para consultas
    int numero_canciones;

    Playlist(int id, string nombre, string creador,int fecha){
        ID = id;
        Nombre = nombre;
        Creador = creador;
        Fecha = fecha;

        sig = nullptr;
        canciones = nullptr;

        numero_canciones = 0;
    }

}*primeroP;


//Lista doble y circular con inserción al final
struct Sellos_Discograficos {
    int ID;
    string Nombre;
    string Pais;
    int Anno_fundacion;

    Sellos_Discograficos* sig;
    Sellos_Discograficos* ant;

    Sublista_Artistas * artistas;

    //Atributos agregados para consultas
    int numero_artistas;


    Sellos_Discograficos(int _ID, string _Nombre, string _Pais, int _Anno_fundacion) {
        ID = _ID;
        Nombre = _Nombre;
        Pais = _Pais;
        Anno_fundacion = _Anno_fundacion;
        sig = ant = nullptr;
        artistas = nullptr;

        numero_artistas = 0;
    }
} *primeroSD = nullptr;


//Inserción y actualización

//Funciones de Canción

//Inserta una canción al inicio de la lista simple
void insertarCancion(int id,string titulo,int duracion){
    Canciones * nc = new Canciones (id, titulo, duracion);
    nc -> sig = primeroC;
    primeroC = nc;
}

//Busca una canción por su título, si existe se retorna, en el caso contrario se retorna nullptr
Canciones * buscarCancion(string titulo){
    Canciones * temp = primeroC;
    while (temp != nullptr){
        if (temp -> Titulo == titulo){
            return temp;
        }
        temp = temp -> sig;
    }
    return nullptr;
}

//Modificaciones de atributos de Canción

//Usa buscarCancion() para modificar el atributo de una canción si existe  (Esto aplica para todas las de modificarXXXXCancion)
void modificarIDCancion(string titulo, int id){
    Canciones * cancion = buscarCancion(titulo);
    if (cancion == nullptr){
        cout << "Canción no encontrada " << endl;
    }
    else{
        cout << "ID de Canción modificado " << endl;
        cancion -> ID = id;
    }
}

void modificarTituloCancion(string tituloOG, string tituloNV){
    Canciones * cancion = buscarCancion(tituloOG);
    if (cancion == nullptr){
        cout << "Canción no encontrada " << endl;
    }
    else{
        cout << "Título de Canción modificado " << endl;
        cancion -> Titulo = tituloNV;
    }
}

void modificarDuracionCancion(string titulo, int duracion){
    Canciones * cancion = buscarCancion(titulo);
    if (cancion == nullptr){
        cout << "Canción no encontrada " << endl;
    }
    else{
        cout << "Duración de Canción modificada " << endl;
        cancion -> Duracion = duracion;
    }
}

void modificarIDAlbumCancion(string titulo, int ID_Alb){
    Canciones * cancion = buscarCancion(titulo);
    if (cancion == nullptr){
        cout << "Canción no encontrada " << endl;
    }
    else{
        cout << "ID de Álbum de Canción modificado " << endl;
        cancion -> ID_Album = ID_Alb;
    }
}

void modificarIDArtistaCancion(string titulo, int ID_Art){
    Canciones * cancion = buscarCancion(titulo);
    if (cancion == nullptr){
        cout << "Canción no encontrada " << endl;
    }
    else{
        cout << "ID de Artista de Canción modificado " << endl;
        cancion -> ID_Artista = ID_Art;
    }
}

//Elimina la canción de la lista simple
void eliminarCancion(string titulo){
    Canciones * temp = primeroC;
    Canciones * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> Titulo == titulo){
            tempAnt -> sig = temp -> sig;
            cout << "Canción eliminada " << endl;
            delete temp;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Canción no encontrada " << endl;
}


//Funciones de Álbum

//Inserta un álbum al inicio de la lista simple
void insertarAlbum(int id, string titulo, int anno) {
    Albumes* nueva = new Albumes(id, titulo, anno);

    if (primeroAlb == nullptr) {
        primeroAlb = nueva;
    } else {
        Albumes* actual = primeroAlb;
        while (actual->sig) {
            actual = actual->sig;
        }
        actual->sig = nueva;
    }
}

//Busca un álbum por su nombre, si existe se retorna, en el caso contrario se retorna nullptr
Albumes * buscarAlbum (string titulo){
    Albumes * temp = primeroAlb;
    while (temp != nullptr){
        if (temp -> Titulo == titulo){
            return temp;
        }
        temp = temp -> sig;
    }
    return nullptr;
}

//Modificaciones

//Usa buscarAlbum()  para modificar el atributo de un álbum si existe. (Esto aplica para todas las de modificarXXXXAlbum)
void modificarIDAlbum(string titulo, int id){
    Albumes * album = buscarAlbum(titulo);
    if (album == nullptr){
        cout << "Álbum no encontrado " << endl;
    }
    else{
        cout << "ID de Álbum modificado " << endl;
        album -> ID = id;
    }
}

void modificarTituloAlbum(string tituloOG, string tituloNV){
    Albumes * album = buscarAlbum(tituloOG);
    if (album == nullptr){
        cout << "Álbum no encontrado " << endl;
    }
    else{
        cout << "Título de Álbum modificado " << endl;
        album -> Titulo = tituloNV;
    }
}

void modificarAnnoAlbum(string titulo, int anno){
    Albumes * album = buscarAlbum(titulo);
    if (album == nullptr){
        cout << "Álbum no encontrado " << endl;
    }
    else{
        cout << "Año de Álbum modificado " << endl;
        album -> Anno = anno;
    }
}

void modificarNCancionesAlbum(string titulo,int n){
    Albumes * album = buscarAlbum(titulo);
    if (album == nullptr){
        cout << "Álbum no encontrado " << endl;
    }
    else{
        cout << "Número de canciones de Álbum modificado " << endl;
        album -> N_canciones = n;
    }
}

//Elimina un álbum de la lista simple
void eliminarAlbum(string titulo){
    Albumes * temp = primeroAlb;
    Albumes * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> Titulo == titulo){
            tempAnt -> sig = temp -> sig;
            cout << "Álbum eliminado " << endl;
            delete temp;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Álbum no encontrado " << endl;
}

//Modificacion de sublistas

//Inserta una canción a Sublista_Canciones
void insertarCancionAlbum(string tituloAlb, string tituloC){
    Albumes * album = buscarAlbum(tituloAlb);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || album == nullptr){
        cout << "Álbum o canción no encontrada " << endl;
    } 
    else{
        cancion -> ID_Album = album -> ID;
        //Se ordena de mas duracion a menos duracion
        Sublista_Canciones * nSub = new Sublista_Canciones(cancion);
        if (album -> canciones == nullptr){
            album -> canciones = nSub;
        }
        else{
            Sublista_Canciones * temp = album -> canciones;
            //La nueva cancion tiene mas duracion que la primera cancion
            if (temp -> cancion -> Duracion < cancion -> Duracion){
                nSub -> sig = temp;
                album -> canciones = nSub;
            }
            //Si la nueva cancion es mas grande que la siguiente cancion evaluada se pone antes que esta
            while (temp -> sig != nullptr && temp -> sig -> cancion -> Duracion > cancion -> Duracion){
                temp = temp -> sig;
            }
            //Tambien se pone de siguiente si llegamos al final de la lista
            nSub -> sig = temp -> sig;
            temp -> sig = nSub;
            
        }  
    }
}

//Elimina una canción de Sublista_Canciones
void eliminarCancionAlbumAux(Albumes * album, Canciones * cancion){
    Sublista_Canciones * temp = album -> canciones;
    Sublista_Canciones * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> cancion == cancion){
            tempAnt -> sig = temp -> sig;
            cout << "Canción eliminada de álbum" << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Canción no existe o no esta en el Álbum seleccionado " << endl;
}

//Elimina una canción de Sublista_Canciones si es la primera
void eliminarCancionAlbum(string tituloAlb, string tituloC){
    Albumes * album = buscarAlbum(tituloAlb);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || album == nullptr){
        cout << "Álbum o canción no encontrada " << endl;
    }
    else{
        if (album -> canciones -> cancion -> Titulo == tituloC){
            album -> canciones = album -> canciones -> sig;
            cout << "Canción eliminada de álbum" << endl;
        }
        else{
            eliminarCancionAlbumAux(album,cancion);
        }
    } 
}


//Funciones de Artistas

//Inserta un artista de manera alfabética en una lista doble
void insertarArtistas (int id, string nombre_artistico, string nombre_real, string pais){
    Artistas * nuevoA = new Artistas (id, nombre_artistico, nombre_real, pais);
    if (primeroArt == nullptr){
        primeroArt = nuevoA;
    }
    else{
        Artistas * temp = primeroArt;
        Artistas * tempAnt = nullptr;
        
        //mientras que nuevoA vaya siguiente alfabeticamente que temp
        while (temp != nullptr && nuevoA -> Nombre_Artistico > temp -> Nombre_Artistico ){
            tempAnt = temp;
            temp = temp -> sig;
        }
        //nuevoA va antes alfabéticamente que el primer nodo
        if (temp == primeroArt){
            temp -> ant = nuevoA;
            nuevoA -> sig = temp;
            primeroArt = nuevoA;
        }
        //nuevoA esta en el medio
        else if(tempAnt != nullptr && temp != nullptr){
            tempAnt -> sig = nuevoA;
            nuevoA -> ant = tempAnt;
            nuevoA -> sig = temp;
            temp -> ant = nuevoA;
        }
        //nuevoA esta en el final y por lo tanto temp es nullptr
        else{
            tempAnt -> sig = nuevoA;
            nuevoA -> ant = tempAnt;
        }
    }
}

//Busca un artista por su nombre, si existe se retorna, en el caso contrario se retorna nullptr
Artistas * buscarArtista (string nombre_artistico){
    Artistas * temp = primeroArt;
    while (temp != nullptr){
        if (temp -> Nombre_Artistico == nombre_artistico){
            return temp;
        }
        temp = temp -> sig;
    }
    return nullptr;
}

//Modificaciones

//Usa buscarArtista() para modificar el atributo de un artista si existe. (Esto aplica para todas las de modificarXXXXArtista)
void modificarIDArtista(string nombre_artistico, int id){
    Artistas * artista = buscarArtista(nombre_artistico);
    if (artista == nullptr){
        cout << "Artista no encontrado " << endl;
    }
    else{
        cout << "ID de Artista modificado " << endl;
        artista -> ID = id;
    }
}

void modificarNArtisticoArtista(string nombre_artisticoOG, string nombre_artisticoNV){
    Artistas * artista = buscarArtista(nombre_artisticoOG);
    if (artista == nullptr){
        cout << "Artista no encontrado " << endl;
    }
    else{
        cout << "Nombre Artístico de Artista modificado " << endl;
        artista -> Nombre_Artistico = nombre_artisticoNV;
    }
}

void modificarNRealArtista(string nombre_artistico, string nombre_real){
    Artistas * artista = buscarArtista(nombre_artistico);
    if (artista == nullptr){
        cout << "Artista no encontrado " << endl;
    }
    else{
        cout << "Nombre Real de Artista modificado " << endl;
        artista -> Nombre_Real = nombre_real;
    }
}

void modificarPaisArtista(string nombre_artistico, string pais){
    Artistas * artista = buscarArtista(nombre_artistico);
    if (artista == nullptr){
        cout << "Artista no encontrado " << endl;
    }
    else{
        cout << "País de Artista modificado " << endl;
        artista -> Pais = pais;
    }
}

void modificarSDiscograficoArtista(string nombre_artistico, string sello_discografico){
    Artistas * artista = buscarArtista(nombre_artistico);
    if (artista == nullptr){
        cout << "Artista no encontrado " << endl;
    }
    else{
        cout << "Sello Discográfico de Artista modificado " << endl;
        artista -> Sello_Discografico = sello_discografico;
    }
}

//Elimina un álbum de la lista doble
void eliminarArtista(string tituloAlb){
    Artistas * temp = buscarArtista(tituloAlb);
    if (temp == nullptr){
        cout << "Artista no encontrado " << endl;
        return;
    }
    if (temp == primeroArt){
        primeroArt = temp -> sig;

        if (primeroArt != nullptr){
            primeroArt -> ant = nullptr;
        }

        delete temp;
    }
    else{
        if (temp -> ant != nullptr){
            temp -> ant -> sig = temp -> sig;
        }
        if (temp -> sig != nullptr){
            temp -> sig -> ant = temp -> ant;
        }
        delete temp;
    }
}

//Modificacion de sublistas

//Inserta una canción al final de Sublista_Canciones
void insertarCancionArtista(string nombreArt, string tituloC){
    Artistas * artista = buscarArtista(nombreArt);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || artista == nullptr){
        cout << "Artista o álbum no encontrado " << endl;
    }
    else{
        Sublista_Canciones * nSub = new Sublista_Canciones(cancion);
        if (artista -> canciones == nullptr){
            artista -> canciones = nSub;
        }
        else{
            Sublista_Canciones * temp = artista -> canciones;
            while (temp -> sig != nullptr){
                temp = temp -> sig;
            }
            temp -> sig = nSub;
        }
    }
}


//Elimina una canción de Sublista_Canciones
void eliminarCancionArtistaAux(Artistas * artista, Canciones * cancion){
    Sublista_Canciones * temp = artista -> canciones;
    Sublista_Canciones * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> cancion == cancion){
            tempAnt -> sig = temp -> sig;
            cout << "Canción eliminada de artista " << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Canción no existe o no pertenece al Artista seleccionado " << endl;
}

//Elimina una canción de Sublista_Canciones si es la primera
void eliminarCancionArtista(string nombreArt, string tituloC){
    Artistas * artista = buscarArtista(nombreArt);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || artista == nullptr){
        cout << "Artista o canción no encontrada " << endl;
    }
    else{
        cancion -> ID_Artista = artista -> ID;
        if (artista -> canciones -> cancion -> Titulo == tituloC){
            artista -> canciones = artista -> canciones -> sig;
            cout << "Canción eliminada de artista " << endl;
        }
        else{
            eliminarCancionArtistaAux(artista,cancion);
        }
    }
}

//Inserta un álbum al final de Sublista_Albumes
void insertarAlbumArtista(string nombreArt, string tituloAlb){
    Artistas * artista = buscarArtista(nombreArt);
    Albumes * album = buscarAlbum(tituloAlb);
    if (artista == nullptr || album == nullptr){
        cout << "Artista o álbum no encontrado " << endl;
    }
    else{
        artista ->albumes_publicados++;
        Sublista_Albumes * nSub = new Sublista_Albumes(album);
        if (artista -> albumes == nullptr){
            artista -> albumes = nSub;
        }
        else{
            Sublista_Albumes * temp = artista -> albumes;
            while (temp -> sig != nullptr){
                temp = temp -> sig;
            }
            temp -> sig = nSub;
        }
    }
}

//Elimina un álbum de Sublista_Albumes
void eliminarAlbumArtistaAux(Artistas * artista, Albumes * album){
    Sublista_Albumes * temp = artista -> albumes;
    Sublista_Albumes * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> album == album){
            tempAnt -> sig = temp -> sig;
            cout << "Álbum eliminado de artista " << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Álbum no existe o no pertenece al Artista seleccionado " << endl;
}

//Elimina un álbum de Sublista_Albumes si es la primera
void eliminarAlbumArtista(string tituloArt, string tituloAlb){
    Artistas * artista = buscarArtista(tituloArt);
    Albumes * album = buscarAlbum(tituloAlb);
    if (artista == nullptr || album == nullptr){
        cout << "Artista o álbum no encontrado " << endl;
    }
    else{
        if (artista -> albumes -> album -> Titulo == tituloAlb){
            artista -> albumes = artista -> albumes -> sig;
            cout << "Álbum eliminado de artista " << endl;
        }
        else{
            eliminarAlbumArtistaAux(artista,album);
        }
    }
}


//Funciones de Género Musical

//Inserta un Género Musical al final de una lista circular
void insertarGeneroMusical (int id, string nombre, string descripcion){
    Generos_Musicales * ng = new Generos_Musicales(id,nombre,descripcion);

    if (primeroG == nullptr){
        primeroG = ng;
        ng -> sig = ng;
    }
    else{
        ng -> sig = primeroG;
        Generos_Musicales * temp = primeroG;
        while (temp -> sig != primeroG){
            temp = temp -> sig;
        }
        temp -> sig = ng;
    }
}

//Busca un Género Musical por su nombre, si existe se retorna, en el caso contrario se retorna nullptr
Generos_Musicales * buscarGeneroMusical (string nombre){
    if (primeroG == nullptr){
        return nullptr;
    }
    Generos_Musicales * temp = primeroG;
    do {
        if (temp -> Nombre == nombre){
            return temp;
        }
        temp = temp -> sig;
    }
    while (temp != primeroG);
    return nullptr;
    
}

//Modificaciones

//Usa buscarGeneroMusical para modificar el atributo de un género  musical si existe (Esto aplica para todas las de modificarXXXXGeneroMusical)
void modificarIDGeneroMusical(string nombre, int id){
    Generos_Musicales * genero_musical = buscarGeneroMusical(nombre);
    if (genero_musical == nullptr){
        cout << "Género Musical no encontrado " << endl;
    }
    else{
        cout << "ID de Género Musical modificado " << endl;
        genero_musical -> ID = id;
    }
}

void modificarnombreGeneroMusical(string nombreOG, string nombreNV){
    Generos_Musicales * genero_musical = buscarGeneroMusical(nombreOG);
    if (genero_musical == nullptr){
        cout << "Género Musical no encontrado " << endl;
    }
    else{
        cout << "Nombre de Género Musical modificado " << endl;
        genero_musical -> Nombre = nombreNV;
    }
}

void modificarStringGeneroMusical(string nombre, string descripcion){
    Generos_Musicales * genero_musical = buscarGeneroMusical(nombre);
    if (genero_musical == nullptr){
        cout << "Género Musical no encontrado " << endl;
    }
    else{
        cout << "ID de Género Musical modificado " << endl;
        genero_musical -> Descripcion = descripcion;
    }
}

//Elimina un Género Musical de la lista circular
void eliminarGeneroMusical (string nombre){
    if (primeroG == nullptr){
        cout << "No hay géneros musicales" << endl;
        return;
    }

    Generos_Musicales * temp = primeroG;
    Generos_Musicales * tempAnt = nullptr;

    do {
        if (temp -> Nombre == nombre){
            //eliminar cualquier otro nodo
            if (tempAnt != nullptr){

                tempAnt -> sig = temp -> sig;

                if (temp == primeroG){
                    primeroG = temp -> sig;
                }
            }
            else{
                //eliminar primer nodo
                primeroG = temp -> sig;

                if (primeroG == temp){
                    primeroG = nullptr;
                }
                else{
                    Generos_Musicales * ult = primeroG;

                    while (ult -> sig != temp){
                        ult = ult -> sig;
                    }
                    ult -> sig = primeroG;
                }
            }
            delete temp;
            return;
        }
    } while (temp != primeroG);
    cout << "El género musical no se encuentra ingresado " << endl;
}

//Modificacion de sublistas

//Inserta una canción al final de Sublista_Canciones
void insertarCancionGeneroMusical(string nombre, string tituloC){
    Generos_Musicales * gm = buscarGeneroMusical(nombre);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || gm == nullptr){
        cout << "Género musical o canción no encontrada " << endl;
    }
    else{
        gm -> numero_canciones ++;
        Sublista_Canciones * nSub = new Sublista_Canciones(cancion);
        if (gm -> canciones == nullptr){
            gm -> canciones = nSub;
        }
        else{
            Sublista_Canciones * temp = gm -> canciones;
            while (temp -> sig != nullptr){
                temp = temp -> sig;
            }
            temp -> sig = nSub;
        }
    }
}

//Elimina una canción de Sublista_Canciones
void eliminarCancionGeneroMusicalAux(Generos_Musicales * gm, Canciones * cancion){
    Sublista_Canciones * temp = gm -> canciones;
    Sublista_Canciones * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> cancion == cancion){
            tempAnt -> sig = temp -> sig;
            cout << "Canción eliminada de genero musical" << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Canción no existe o no esta en el Género Musical seleccionado " << endl;
}

//Elimina una canción de Sublista_Canciones si es la primera
void eliminarCancionGeneroMusical(string nombre, string tituloC){
    Generos_Musicales * gm = buscarGeneroMusical(nombre);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || gm == nullptr){
        cout << "Género musical o canción no encontrada " << endl;
    }
    else{
        if (gm -> canciones -> cancion -> Titulo == tituloC){
            gm -> canciones = gm -> canciones -> sig;
            cout << "Canción elimnada de género musical " << endl;
        }
        else{
            eliminarCancionGeneroMusicalAux(gm,cancion);
        }
    }
}

//Funciones de Playlists 

//Inserta una playlist al inicio de la lista simple
void insertarPlaylist(int id, string nombre, string creador,int fecha){
    Playlist * np = new Playlist(id,nombre,creador,fecha);
    np -> sig = primeroP;
    primeroP = np;
}

//Busca un Playlist por su nombre, si existe se retorna, en el caso contrario se retorna nullptr
Playlist * buscarPlaylist (string nombre){
    Playlist * temp = primeroP;
    while (temp != nullptr){
        if (temp -> Nombre == nombre){
            return temp;
        }
        temp = temp -> sig;
    }
    return nullptr;
}

//Modificaciones

//Usa buscarPlaylist() para modificar el atributo de un playlist si existe. (Esto aplica para todas las de modificarXXXXPlaylist)
void modificarIDPlaylist(string nombre, int id){
    Playlist * playlist = buscarPlaylist(nombre);
    if (playlist == nullptr){
        cout << "Playlist no encontrado " << endl;
    }
    else{
        cout << "ID de Playlist modificado " << endl;
        playlist -> ID = id;
    }
}

void modificarNombrePlaylist(string nombreOG, string nombreNV){
    Playlist * playlist = buscarPlaylist(nombreOG);
    if (playlist == nullptr){
        cout << "Playlist no encontrado " << endl;
    }
    else{
        cout << "Nombre de Playlist modificado " << endl;
        playlist -> Nombre = nombreNV;
    }
}

void modificarCreadorPlaylist(string nombre, string creador){
    Playlist * playlist = buscarPlaylist(nombre);
    if (playlist == nullptr){
        cout << "Playlist no encontrado " << endl;
    }
    else{
        cout << "Creador de Playlist modificado " << endl;
        playlist -> Creador = creador;
    }
}

void modificarFechaPlaylist(string nombre, int fecha){
    Playlist * playlist = buscarPlaylist(nombre);
    if (playlist == nullptr){
        cout << "Playlist no encontrado " << endl;
    }
    else{
        cout << "Fecha de Playlist modificada " << endl;
        playlist -> Fecha = fecha;
    }
}

//Elimina un Playlist de la lista simple
void eliminarPlaylist(string nombre){
    Playlist * temp = primeroP;
    Playlist * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> Nombre == nombre){
            tempAnt -> sig = temp -> sig;
            cout << "Playlist eliminada " << endl;
            delete temp;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Playlist no encontrada " << endl;
}

//Modificacion de sublistas

//Inserta una canción al final de Sublista_Canciones
void insertarCancionPlaylist(string nombre, string tituloC){
    Playlist * playlist = buscarPlaylist(nombre);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || playlist == nullptr){
        cout << "Playlist o canción no encontrada " << endl;
    }
    else{
        playlist -> numero_canciones ++;
        Sublista_Canciones * nSub = new Sublista_Canciones(cancion);
        if (playlist -> canciones == nullptr){
            playlist -> canciones = nSub;
        }
        else{
            Sublista_Canciones * temp = playlist -> canciones;
            while (temp -> sig != nullptr){
                temp = temp -> sig;
            }
            temp -> sig = nSub;
        }
    }
}

//Elimina una canción de Sublista_Canciones
void eliminarCancionPlaylistAux(Playlist * playlist, Canciones * cancion){
    Sublista_Canciones * temp = playlist -> canciones;
    Sublista_Canciones * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> cancion == cancion){
            tempAnt -> sig = temp -> sig;
            cout << "Canción eliminada de playlist" << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Canción no existe o no esta en el Playlist seleccionado " << endl;
}

//Elimina una canción de Sublista_Canciones si es la primera
void eliminarCancionPlaylist(string nombre, string tituloC){
    Playlist * playlist = buscarPlaylist(nombre);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || playlist == nullptr){
        cout << "Playlist o canción no encontrada " << endl;
    }
    else{
        if (playlist -> canciones -> cancion -> Titulo == tituloC){
            playlist -> canciones = playlist -> canciones -> sig;
            cout << "Canción eliminada de playlist " << endl;
        }
        else{
            eliminarCancionPlaylistAux(playlist,cancion);
        }
    }
}



//Funciones de Sellos Discograficos

//Inserta un sello discográfico al final de la lista doble y circular
void insertarSellosDiscograficos(int id, string nombre, string pais, int anno_de_fundacion) {
    Sellos_Discograficos* NSD = new Sellos_Discograficos(id, nombre, pais, anno_de_fundacion);

    if (primeroSD == nullptr) {
        primeroSD = NSD;
        primeroSD->sig = primeroSD;
        primeroSD->ant = primeroSD;
    } else {
        Sellos_Discograficos* ultimo = primeroSD->ant;
        ultimo->sig = NSD;
        NSD->ant = ultimo;
        NSD->sig = primeroSD;
        primeroSD->ant = NSD;
    }
}

//Busca un sello discográfico por su nombre, si existe se retorna, en el caso contrario se retorna nullptr
Sellos_Discograficos * buscarSellosDiscograficos (string nombre){
    if (primeroSD == nullptr){
        return nullptr;
    }
    Sellos_Discograficos * temp = primeroSD;
    do {
        if (temp -> Nombre == nombre){
            return temp;
        }
        temp = temp -> sig;
    }
    while (temp != primeroSD);
    return nullptr;
}

//Modificaciones

//Usa buscarSellosDiscograficos() para modificar el atributo de un sello discográfico si existe. (Esto aplica para todas las de modificarXXXXSelloDiscografico)
void modificarIDSelloDiscografico (string nombre, int id){
    Sellos_Discograficos * sello_discografico = buscarSellosDiscograficos(nombre);
    if (sello_discografico == nullptr){
        cout << "Sello Discográfico no encontrado " << endl;
    }
    else{
        cout << "ID de Sello Discográfico modificado " << endl;
        sello_discografico -> ID = id;
    }
}

void modificarNombreSelloDiscografico (string nombreOG, string nombreNV){
    Sellos_Discograficos * sello_discografico = buscarSellosDiscograficos(nombreOG);
    if (sello_discografico == nullptr){
        cout << "Sello Discográfico no encontrado " << endl;
    }
    else{
        cout << "Nombre de Sello Discográfico modificado " << endl;
        sello_discografico -> Nombre = nombreNV;
    }
}

void modificarPaisSelloDiscografico (string nombre, string pais){
    Sellos_Discograficos * sello_discografico = buscarSellosDiscograficos(nombre);
    if (sello_discografico == nullptr){
        cout << "Sello Discográfico no encontrado " << endl;
    }
    else{
        cout << "País de Sello Discográfico modificado " << endl;
        sello_discografico -> Pais = pais;
    }
}

void modificarAnnoFundacionSelloDiscografico (string nombre, int anno_fundacion){
    Sellos_Discograficos * sello_discografico = buscarSellosDiscograficos(nombre);
    if (sello_discografico == nullptr){
        cout << "Sello Discográfico no encontrado " << endl;
    }
    else{
        cout << "Año de fundación de Sello Discográfico modificado " << endl;
        sello_discografico -> Anno_fundacion = anno_fundacion;
    }
}

//Elimina un sello discográfico de la lista circular y doble
void eliminarSelloDiscografico(string nombre){
    Sellos_Discograficos * temp = buscarSellosDiscograficos(nombre);
    if (temp == nullptr){
        cout << "Sello Discográfico no encontrado " << endl;
        return;
    }
    if (temp == primeroSD){
        primeroSD = temp -> sig;

        if (primeroSD != nullptr){
            primeroSD -> ant = nullptr;
        }

        delete temp;
    }
    else{
        temp -> ant -> sig = temp -> sig;
        temp -> sig -> ant = temp -> ant;
        delete temp;
    }

}

//Modificacion de sublistas

//Inserta un artista al final de Sublista_Artistas
void insertarArtistaSelloDiscografico(string nombre, string nombreArt){
    Sellos_Discograficos * sd = buscarSellosDiscograficos(nombre);
    Artistas * artista = buscarArtista(nombreArt);
    if (sd == nullptr || artista == nullptr){
        cout << "Sello Discográfico o artista no encontrado " << endl;
    }
    else{
        artista->Sello_Discografico = sd -> Nombre;
        sd -> numero_artistas ++;
        Sublista_Artistas * nSub = new Sublista_Artistas (artista);
        if (sd -> artistas == nullptr){
            sd -> artistas = nSub;
        }
        else{
            Sublista_Artistas * temp = sd -> artistas;
            while (temp -> sig != nullptr){
                temp = temp -> sig;
            }
            temp -> sig = nSub;
        }
    }
}

//Elimina un artista de Sublista_Artistas
void eliminarArtistaSelloDiscograficoAux(Sellos_Discograficos * sd, Artistas * artista){
    Sublista_Artistas * temp = sd -> artistas;
    Sublista_Artistas * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> artista == artista){
            tempAnt -> sig = temp -> sig;
            cout << "Artista eliminado de Sello Discográfico " << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Artista no existe o no pertenece al sello discográfico seleccionado " << endl;
}

//Elimina un artista de Sublista_Artistas si es la primera
void eliminarArtistaSelloDiscografico(string nombre, string nombreArt){
    Sellos_Discograficos * sd = buscarSellosDiscograficos(nombre);
    Artistas * artista = buscarArtista(nombreArt);
    if (sd == nullptr || artista == nullptr){
        cout << "Sello Discográfico o artista no encontrado " << endl;
    }
    else{
        if (sd -> artistas -> artista -> Nombre_Artistico == nombreArt){
            sd -> artistas = sd -> artistas -> sig;
            cout << "Artista eliminado de Sello Discográfico " << endl;
        }
        else{
            eliminarArtistaSelloDiscograficoAux(sd,artista);
        }
    }
}

//Reportes

//Imprime un canción individual con todos sus atributos
void imprimirCancion(Canciones * temp){
    cout << "---------------------------------" << endl;
    cout << "ID de Canción: " << temp->ID << endl;
    cout << "Titulo de Canción: " << temp->Titulo << endl;
    cout << "Duración: " << temp->Duracion << endl;
    cout << "ID de Álbum: " << temp->ID_Album << endl;
    cout << "ID de Artista: " << temp->ID_Artista << endl;
}

//Imprime todas las canciones disponibles
void imprimirCanciones(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todas las canciones " << endl; 
    cout << "---------------------------------" << endl;
    Canciones * temp = primeroC;
    while(temp != nullptr){
        imprimirCancion(temp);
        temp = temp -> sig;
    }
}




//Imprime un álbum individual con todos sus atributos
void imprimirAlbum(Albumes * temp, bool printDetails) {
    cout << "---------------------------------" << endl;
    cout << "ID de Album: " << temp->ID << endl;
    cout << "Título: " << temp->Titulo << endl;
    cout << "Año: " << temp->Anno << endl;
    cout << "Número de Canciones: " << temp->N_canciones << endl;
    cout << "---------------------------------" << endl;
    if (printDetails) {
        cout << "Canciones del Álbum: " << endl;
        Sublista_Canciones* canciones = temp->canciones; // Ya están ordenadas al insertar
        while (canciones != nullptr) {
            if (canciones->cancion != nullptr) {
                imprimirCancion(canciones->cancion);
            }
            canciones = canciones->sig;
        }
    }
}


//Imprime todos las álbumes disponibles
void imprimirAlbumes(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todos los álbumes " << endl; 
    cout << "---------------------------------" << endl;
    Albumes * temp = primeroAlb;
    while (temp != nullptr){
        imprimirAlbum(temp,true);
        temp = temp->sig;
    }
}

//Imprime un artista individual con todos sus atributos
void imprimirArtista(Artistas * temp, bool printDetails){
    cout << "---------------------------------" << endl;
    cout << "Nombre Artístico: " << temp -> Nombre_Artistico << endl;
    cout << "Nombre Real: " << temp -> Nombre_Real << endl;
    cout << "País: " << temp -> Pais << endl;
    cout << "Sello Discográfico: " << temp -> Sello_Discografico << endl;
    cout << "---------------------------------" << endl;
    cout << "Canciones del Artista: " << endl;
    if (!printDetails){  //printDetails determina si se quiere imprimir los álbumes y canciones del artista o solo la información del artista
        return;
    }
    Sublista_Canciones * temp2 = temp->canciones;
    while(temp2 != nullptr){
        if(temp2->cancion != nullptr) {
            imprimirCancion(temp2->cancion);
        }
        temp2 = temp2 -> sig;
    }
    cout << "---------------------------------" << endl;
    cout << "Álbumes del Artista: " << endl;
    Sublista_Albumes * temp3 = temp->albumes;
    while(temp3 != nullptr){
        if(temp3->album != nullptr) {
            imprimirAlbum(temp3->album,false);
        }
        temp3 = temp3 -> sig;
    }
}

//Imprime todos los artistas disponibles
void imprimirArtistas(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todos los artistas " << endl; 
    cout << "---------------------------------" << endl;
    Artistas * temp = primeroArt;
    while (temp != nullptr){
        imprimirArtista(temp,true);
        temp = temp -> sig;
    }
}
//Imprime todos los géneros musicales disponibles
void imprimirGenerosMusicales(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todos los géneros musicales" << endl; 
    cout << "---------------------------------" << endl;
    Generos_Musicales * temp = primeroG;
    do {
        cout << "---------------------------------" << endl;
        cout << "ID de Género Musical: " << temp->ID << endl;
        cout << "Nombre de Género Musical: " << temp->Nombre << endl;
        cout << "Descripción de Género Musical: " << temp->Descripcion << endl;
        cout << "---------------------------------" << endl;
        cout << "Canciones del Género Musical: " << endl;
        Sublista_Canciones * temp2 = temp->canciones;
        while (temp2 != nullptr) {
            if (temp2->cancion != nullptr) {
                imprimirCancion(temp2->cancion);
            }
            temp2 = temp2->sig;
        }
        temp = temp->sig;
    } while (temp != primeroG);
}

//Imprime todas las playlist disponibles
void imprimirPlaylists(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todas las playlists " << endl; 
    cout << "---------------------------------" << endl;
    Playlist * temp = primeroP;
    while (temp != nullptr){
        cout << "---------------------------------" << endl;
        cout << "ID de Playlist: " << temp->ID << endl;
        cout << "Nombre de Playlist: " << temp->Nombre << endl;
        cout << "Creador de Playlist: " << temp->Creador << endl;
        cout << "Fecha de Playlist: " << temp->Fecha << endl;
        cout << "---------------------------------" << endl;
        cout << "Canciones de la Playlist: " << endl;
        Sublista_Canciones * temp2 = temp->canciones;
        while (temp2 != nullptr){
            if (temp2->cancion != nullptr){
                imprimirCancion(temp2->cancion);
            }
            temp2 = temp2->sig;
        }
        temp = temp->sig;
    }
}

//Imprime todos los sellos discográficos disponibles
void imprimirSellosDiscograficos(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todos los sellos discográficos " << endl; 
    cout << "---------------------------------" << endl;
    Sellos_Discograficos * temp = primeroSD;
    do {
        cout << "---------------------------------" << endl;
        cout << "ID de Sello Discográfico: " << temp->ID << endl;
        cout << "Nombre de Sello Discográfico: " << temp->Nombre << endl;
        cout << "País de Sello Discográfico: " << temp->Pais << endl;
        cout << "Año de Fundación de Sello Discográfico: " << temp->Anno_fundacion << endl;
        cout << "---------------------------------" << endl;
        Sublista_Artistas * temp2 = temp->artistas;
        while (temp2 != nullptr){
            if (temp2->artista != nullptr){
                imprimirArtista(temp2->artista, false);
            }
            temp2 = temp2->sig;
        }
        temp = temp->sig;
    } while (temp != primeroSD);
}


//Consultas

//Imprime el género musical con más canciones registradas
void generoPopular(){
    Generos_Musicales * temp = primeroG;
    Generos_Musicales * max = temp;
    do{
        if (temp -> numero_canciones > max -> numero_canciones){
            max = temp;
        }
        temp = temp->sig;
    }
    while(temp != primeroG);
    cout << "---------------------------------" << endl;
    cout << "Género Musical con más canciones registradas: " << max ->Nombre << endl;
}
//Imprime el artista con más álbumes publicados
void artistaTrabajador(){
    Artistas * temp = primeroArt;
    Artistas * max = temp;
    while(temp != nullptr){
        if (temp->albumes_publicados > max -> albumes_publicados){
            max = temp;
        }
        temp = temp->sig;
    }
    cout << "---------------------------------" << endl;
    cout << "Artista con más álbumes publicados: " << max -> Nombre_Artistico << endl;

}
//Imprime la canción más larga disponible
void cancionLarga(){
    Canciones * temp = primeroC;
    Canciones * max = temp;
    while (temp != nullptr){
        if (temp -> Duracion > max -> Duracion){
            max = temp;
        }
        temp = temp -> sig;
    }
    cout << "---------------------------------" << endl;
    cout << "Canción más larga: " << max -> Titulo << endl;

}
//Imprime el playlist con más canciones
void playlistLarga(){
    Playlist * temp = primeroP;
    Playlist * max = temp;
    while (temp != nullptr){
        if (temp -> numero_canciones > max -> numero_canciones){
            max = temp;
        }
        temp = temp -> sig;
    }
    cout << "---------------------------------" << endl;
    cout << "Playlist más larga: " << max -> Nombre << endl;
}
//Imprime la cantidad de álbumes que tiene cada artista
void albumesPorArtista(){
    Artistas * temp = primeroArt;
    cout << "---------------------------------" << endl;
    cout << "Álbumes por Artista: " << endl;
    cout << "---------------------------------" << endl;
    while (temp != nullptr){
        cout << "Álbumes publicados por " << temp->Nombre_Artistico << ": " << temp->albumes_publicados << endl;
        temp = temp->sig; 
    }
}
//Imprime el sello discográfico con más artistas
void selloDiscograficoPopular(){
    Sellos_Discograficos * temp = primeroSD;
    Sellos_Discograficos * max = temp;
    do{
        if (temp->numero_artistas > max -> numero_artistas){
            max = temp;
        }
        temp = temp -> sig;
    }
    while(temp != primeroSD);
    cout << "---------------------------------" << endl;
    cout << "Sello Discográfico con más artistas publicados: " << max -> Nombre << endl;
}
//Imprime las canciones publicadas en un año determinado
void cancionesEnAnnoDetermindado (int a){
    Albumes * temp = primeroAlb;
    cout << "Álbumes publicados en  " << a <<": "<< endl;
    while(temp != nullptr){
        if (temp -> Anno = a){
            imprimirAlbum(temp,true);
        }
        temp = temp -> sig;
    }
}
//Imprime los álbumes que superan cierto número de canciones
void albumesSuperiorNumero(int n){
    Albumes * temp = primeroAlb;
    cout << "---------------------------------" << endl;
    cout << "Álbumes que superan " << n << " número de canciones: " << endl;
    while(temp != nullptr){
        if (temp -> N_canciones > n){
            cout << temp->Titulo << "con " << temp->N_canciones << " canciones" << endl;
        }
        temp = temp -> sig;
    }
}

//Validaciones

//Se asegura que el usuario presione un integer y ningún otro tipo de dato
int validInteger(){
    int num;

    // Si se le pone algo que no sea un integer, se quita el error y se elimina el input previo
    while (true){
        cin >> num;
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Input inválido, por favor escribir un número válido" << endl;
        }
        else{return num;}
    }
}

//Se asegura que el usuario presione un string y ningún otro tipo de dato
string validString() {
    string input;

    while (true) {
         getline(cin, input);  // Leer solo la siguiente palabra o conjunto de caracteres sin espacios

        bool isValid = true;

        // Verificar si todos los caracteres son letras
        for (char c : input) {
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                isValid = false;
                break;
            }
        }

        if (isValid) {
            return input;
        } else {
            cout << "use un nombre válido" << endl;
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el búfer de entrada
        }
    }
}

//Busca si existe un álbum con el título buscado
bool albumYaExiste(int id, string titulo) {
    Albumes* temp = primeroAlb;
    while (temp != nullptr) {
        if ((id != 0 && temp->ID == id) || (!titulo.empty() && temp->Titulo == titulo)) {
            if (id != 0 && temp->ID == id) {
                cout << "Error: El ID " << id << " ya está en uso por el álbum '" << temp->Titulo << "'\n";
            }
            if (!titulo.empty() && temp->Titulo == titulo) {
                cout << "Error: El título '" << titulo << "' ya está en uso por el álbum con ID " << temp->ID << "\n";
            }
            return true;
        }
        temp = temp->sig;
    }
    return false;
}
//Busca si existe un artista con el nombre buscado
bool artistaYaExiste(int id, string nombre_artistico) {
    Artistas* temp = primeroArt;
    while (temp != nullptr) {
        if ((id != 0 && temp->ID == id) || (!nombre_artistico.empty() && temp->Nombre_Artistico == nombre_artistico)) {
            if (id != 0 && temp->ID == id) {
                cout << "Error: El ID " << id << " ya está en uso por el artista '" << temp->Nombre_Artistico << "'\n";
            }
            if (!nombre_artistico.empty() && temp->Nombre_Artistico == nombre_artistico) {
                cout << "Error: El nombre artístico '" << nombre_artistico << "' ya está en uso\n";
            }
            return true;
        }
        temp = temp->sig;
    }
    return false;
}
//Busca si existe un sello discográfico con el nombre buscado
bool selloYaExiste(int id, string nombre) {
    if (primeroSD == nullptr) return false;
    
    Sellos_Discograficos* temp = primeroSD;
    do {
        if ((id != 0 && temp->ID == id) || (!nombre.empty() && temp->Nombre == nombre)) {
            if (id != 0 && temp->ID == id) {
                cout << "Error: El ID " << id << " ya está en uso por el sello '" << temp->Nombre << "'\n";
            }
            if (!nombre.empty() && temp->Nombre == nombre) {
                cout << "Error: El nombre '" << nombre << "' ya está en uso por el sello con ID " << temp->ID << "\n";
            }
            return true;
        }
        temp = temp->sig;
    } while (temp != primeroSD);
    
    return false;
}
//Busca si existe una canción con el título buscado
bool cancionYaExiste(int id, string titulo) {
    Canciones* temp = primeroC;
    while (temp != nullptr) {
        if (temp->ID == id || temp->Titulo == titulo) {
            return true;  // Si encuentra una canción con el mismo ID o título, retorna true
        }
        temp = temp->sig;
    }
    return false;  // Si no encuentra ninguna coincidencia, retorna false
}
//Busca si existe un género musical con el nombre buscado
bool generoYaExiste(int id, std::string nombre) {
    if (primeroG == nullptr) return false;
    
    Generos_Musicales* temp = primeroG;
    do {
        if ((id != 0 && temp->ID == id) || (!nombre.empty() && temp->Nombre == nombre)) {
            std::cout << "\n¡Ya existe un género ";
            if (id != 0 && temp->ID == id) {
                cout << "con el ID " << id;
            }
            if (!nombre.empty() && temp->Nombre == nombre) {
                if (id != 0) std::cout << " y ";
                std::cout << "con el nombre '" << nombre << "'";
            }
            std::cout << "! Por favor, usa otro.\n";
            return true;
        }
        temp = temp->sig;
    } while (temp != primeroG);
    
    return false;
}

//Busca si existe una playlist con el nombre buscado
bool playlistYaExiste(int id, string nombre) {
    Playlist* temp = primeroP;
    while (temp != nullptr) {
        if ((id != 0 && temp->ID == id) || (!nombre.empty() && temp->Nombre == nombre)) {
            if (id != 0 && temp->ID == id) {
                cout << "Error: El ID " << id << " ya está en uso por la playlist '" << temp->Nombre << "'\n";
            }
            if (!nombre.empty() && temp->Nombre == nombre) {
                cout << "Error: El nombre '" << nombre << "' ya está en uso por la playlist con ID " << temp->ID << "\n";
            }
            return true;
        }
        temp = temp->sig;
    }
    return false;
}

//Menú con las opciones para modificar la lista de canciones
void subMenuCancion() {
    int opcion;
    do {
        cout << "\n--- SUBMENÚ CANCIONES ---\n";
        cout << "1. Insertar canción\n";
        cout << "2. Modificar ID de canción\n";
        cout << "3. Modificar título de canción\n";
        cout << "4. Modificar duración de canción\n";
        cout << "5. Modificar ID de álbum de canción\n";
        cout << "6. Modificar ID de artista de canción\n";
        cout << "7. Eliminar canción\n";
        cout << "8. Volver al menú anterior\n";
        cout << "Seleccione una opción: ";
        opcion = validInteger();

        switch (opcion) {
            case 1:{
                // Insertar canción (validación de duplicados)
                int id;
                string titulo;
                int duracion;
                cout << "Ingrese ID: ";
                id = validInteger();

                // Validar si el ID ya existe
                if (cancionYaExiste(id, "")) {
                    cout << "Canción no insertada, ID ya existe.\n";
                    break;
                }

                cout << "Ingrese título: ";
                cin >> titulo;

                // Validar si el título ya existe
                if (cancionYaExiste(0, titulo)) {
                    cout << "Canción no insertada, título ya existe.\n";
                    break;
                }

                cout << "Ingrese duración: ";
                duracion = validInteger();
                insertarCancion(id, titulo, duracion);
                break;
            }
            case 2:{
                // Modificar ID de canción (validación de duplicados)
                string tituloModID;
                int idNuevo;
                cout << "Ingrese título de la canción a modificar: ";
                cin >> tituloModID;

                cout << "Ingrese el nuevo ID: ";
                idNuevo = validInteger();

                // Validar si el nuevo ID ya está en uso
                if (cancionYaExiste(idNuevo, "")) {
                    cout << "ID ya está siendo usado por otra canción.\n";
                    break;
                }

                modificarIDCancion(tituloModID, idNuevo);
                break;
            }
            case 3:{
                // Modificar título de canción (validación de duplicados)
                string tituloModOriginal, tituloModNuevo;
                cout << "Ingrese título original de la canción: ";
                cin >> tituloModOriginal;

                cout << "Ingrese el nuevo título: ";
                cin >> tituloModNuevo;

                // Validar si el nuevo título ya está en uso
                if (cancionYaExiste(0, tituloModNuevo)) {
                    cout << "Título ya está siendo usado por otra canción.\n";
                    break;
                }

                modificarTituloCancion(tituloModOriginal, tituloModNuevo);
                break;
            }
            case 4:{
                // Modificar duración de canción (sin validación de existencia)
                string tituloModDuracion;
                int duracionNueva;
                cout << "Ingrese título de la canción a modificar: ";
                cin >> tituloModDuracion;
                cout << "Ingrese la nueva duración: ";
                duracionNueva = validInteger();
                modificarDuracionCancion(tituloModDuracion, duracionNueva);
                break;
            }
            case 5:{
                // Modificar ID de álbum de canción (sin validación de existencia)
                string tituloModIDAlbum;
                int idAlbumNuevo;
                cout << "Ingrese título de la canción a modificar: ";
                cin >> tituloModIDAlbum;
                cout << "Ingrese el nuevo ID de álbum: ";
                idAlbumNuevo = validInteger();
                modificarIDAlbumCancion(tituloModIDAlbum, idAlbumNuevo);
                break;
            }
            case 6:{
                // Modificar ID de artista de canción (sin validación de existencia)
                string tituloModIDArtista;
                int idArtistaNuevo;
                cout << "Ingrese título de la canción a modificar: ";
                cin >> tituloModIDArtista;
                cout << "Ingrese el nuevo ID de artista: ";
                idArtistaNuevo = validInteger();
                modificarIDArtistaCancion(tituloModIDArtista, idArtistaNuevo);
                break;
            }
            case 7:{
                // Eliminar canción (sin validación de existencia)
                string tituloEliminar;
                cout << "Ingrese título de la canción a eliminar: ";
                cin >> tituloEliminar;
                eliminarCancion(tituloEliminar);
                break;
            }
            case 8:
                cout << "Volviendo...\n";
                break;

            default:
                cout << "Opción inválida.\n";
                break;
        }
    } while (opcion != 8);
}

//Menú con las opciones para modificar la lista de artistas
void subMenuArtista() {
    int opcion;
    do {
        cout << "\n--- SUBMENÚ ARTISTAS ---\n";
        cout << "1. Insertar artista\n";
        cout << "2. Modificar ID de artista\n";
        cout << "3. Modificar nombre artístico\n";
        cout << "4. Modificar nombre real\n";
        cout << "5. Modificar país\n";
        cout << "6. Modificar sello discográfico\n";
        cout << "7. Eliminar artista\n";
        cout << "8. Añadir canción a artista\n";
        cout << "9. Eliminar canción de artista\n";
        cout << "10. Añadir álbum a artista\n";
        cout << "11. Eliminar álbum de artista\n";
        cout << "12. Volver al menú anterior\n";
        cout << "Seleccione una opción: ";
        opcion = validInteger();

        switch (opcion) {
            case 1: {
                int id;
                string nombre_artistico, nombre_real, pais;
                cout << "Ingrese ID del artista: ";
                id = validInteger();
                cout << "Ingrese nombre artístico: ";
                cin.ignore();
                getline(cin, nombre_artistico);
                if (artistaYaExiste(id, nombre_artistico)) break;
                cout << "Ingrese nombre real: ";
                getline(cin, nombre_real);
                cout << "Ingrese país de origen: ";
                pais =validInteger();
                getline(cin, pais);
                insertarArtistas(id, nombre_artistico, nombre_real, pais);
                cout << "Artista creado exitosamente!\n";
                break;
            }
            case 2: {
                string nombre;
                int nuevoID;
                cout << "Ingrese nombre artístico del artista a modificar: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese nuevo ID: ";
                nuevoID = validInteger();
                if (artistaYaExiste(nuevoID, "")) break;
                modificarIDArtista(nombre, nuevoID);
                break;
            }
            case 3: {
                string nombreActual, nuevoNombre;
                cout << "Ingrese nombre artístico actual: ";
                cin.ignore();
                getline(cin, nombreActual);
                cout << "Ingrese nuevo nombre artístico: ";
                getline(cin, nuevoNombre);
                if (artistaYaExiste(0, nuevoNombre)) break;
                modificarNArtisticoArtista(nombreActual, nuevoNombre);
                break;
            }
            case 4: {
                string nombre, nuevoNombreReal;
                cout << "Ingrese nombre artístico: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese nuevo nombre real: ";
                getline(cin, nuevoNombreReal);
                modificarNRealArtista(nombre, nuevoNombreReal);
                break;
            }
            case 5: {
                string nombre, nuevoPais;
                cout << "Ingrese nombre artístico: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese nuevo país: ";
                getline(cin, nuevoPais);
                modificarPaisArtista(nombre, nuevoPais);
                break;
            }
            case 6: {
                string nombre, nuevoSello;
                cout << "Ingrese nombre artístico: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese nuevo sello discográfico: ";
                getline(cin, nuevoSello);
                modificarSDiscograficoArtista(nombre, nuevoSello);
                break;
            }
            case 7: {
                string nombre;
                cout << "Ingrese nombre artístico del artista a eliminar: ";
                cin.ignore();
                getline(cin, nombre);
                eliminarArtista(nombre);
                break;
            }
            case 8: {
                string nombreArtista, tituloCancion;
                cout << "Ingrese nombre artístico: ";
                cin.ignore();
                getline(cin, nombreArtista);
                cout << "Ingrese título de la canción: ";
                getline(cin, tituloCancion);
                insertarCancionArtista(nombreArtista, tituloCancion);
                break;
            }
            case 9: {
                string nombreArtista, tituloCancion;
                cout << "Ingrese nombre artístico: ";
                cin.ignore();
                getline(cin, nombreArtista);
                cout << "Ingrese título de la canción a eliminar: ";
                getline(cin, tituloCancion);
                eliminarCancionArtista(nombreArtista, tituloCancion);
                break;
            }
            case 10: {
                string nombreArtista, tituloAlbum;
                cout << "Ingrese nombre artístico: ";
                cin.ignore();
                getline(cin, nombreArtista);
                cout << "Ingrese título del álbum: ";
                getline(cin, tituloAlbum);
                insertarAlbumArtista(nombreArtista, tituloAlbum);
                break;
            }
            case 11: {
                string nombreArtista, tituloAlbum;
                cout << "Ingrese nombre artístico: ";
                cin.ignore();
                getline(cin, nombreArtista);
                cout << "Ingrese título del álbum a eliminar: ";
                getline(cin, tituloAlbum);
                eliminarAlbumArtista(nombreArtista, tituloAlbum);
                break;
            }
            case 12:
                cout << "Volviendo al menú principal...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 12);
}

//Menú con las opciones para modificar la lista de álbumes
void subMenuAlbum() {
    int opcion;
    do {
        cout << "\n--- SUBMENÚ ÁLBUMES ---\n";
        cout << "1. Insertar álbum\n";
        cout << "2. Modificar ID de álbum\n";
        cout << "3. Modificar título de álbum\n";
        cout << "4. Modificar año de álbum\n";
        cout << "5. Modificar número de canciones\n";
        cout << "6. Eliminar álbum\n";
        cout << "7. Añadir canción a álbum\n";
        cout << "8. Eliminar canción de álbum\n";
        cout << "9. Volver al menú anterior\n";
        cout << "Seleccione una opción: ";
        opcion = validInteger();

        switch (opcion) {
            case 1: {
                // Insertar álbum con validación
                int id, anno;
                string titulo;
                
                cout << "Ingrese ID del álbum: ";
                id = validInteger();
                
                cout << "Ingrese título del álbum: ";
                cin.ignore();
                getline(cin, titulo);
                
                if (albumYaExiste(id, titulo)) {
                    break;
                }
                
                cout << "Ingrese año del álbum (1951-2024): ";
                anno = validInteger();
                while (anno < 1951 || anno > 2024) {
                    cout << "Año inválido. Ingrese entre 1951-2024: ";
                    anno = validInteger();
                }
                
                insertarAlbum(id, titulo, anno);
                cout << "Álbum creado exitosamente!\n";
                break;
            }

            case 2: {
                // Modificar ID con validación
                string titulo;
                int nuevoID;
                
                cout << "Ingrese título del álbum a modificar: ";
                cin.ignore();
                getline(cin, titulo);
                
                cout << "Ingrese nuevo ID: ";
                nuevoID = validInteger();
                
                if (albumYaExiste(nuevoID, "")) {
                    break;
                }
                
                modificarIDAlbum(titulo, nuevoID);
                break;
            }

            case 3: {
                // Modificar título con validación
                string tituloActual, nuevoTitulo;
                
                cout << "Ingrese título actual del álbum: ";
                cin.ignore();
                getline(cin, tituloActual);
                
                cout << "Ingrese nuevo título: ";
                getline(cin, nuevoTitulo);
                
                if (albumYaExiste(0, nuevoTitulo)) {
                    break;
                }
                
                modificarTituloAlbum(tituloActual, nuevoTitulo);
                break;
            }

            case 4: {
                // Modificar año
                string titulo;
                int nuevoAnno;
                
                cout << "Ingrese título del álbum: ";
                cin.ignore();
                getline(cin, titulo);
                
                cout << "Ingrese nuevo año (1951-2024): ";
                nuevoAnno = validInteger();
                while (nuevoAnno < 1951 || nuevoAnno > 2024) {
                    cout << "Año inválido. Ingrese entre 1951-2024: ";
                    nuevoAnno = validInteger();
                }
                
                modificarAnnoAlbum(titulo, nuevoAnno);
                break;
            }

            case 5: {
                // Modificar número de canciones
                string titulo;
                int nuevoNumero;
                
                cout << "Ingrese título del álbum: ";
                cin.ignore();
                getline(cin, titulo);
                
                cout << "Ingrese nuevo número de canciones: ";
                nuevoNumero = validInteger();
                
                modificarNCancionesAlbum(titulo, nuevoNumero);
                break;
            }

            case 6: {
                // Eliminar álbum
                string titulo;
                
                cout << "Ingrese título del álbum a eliminar: ";
                cin.ignore();
                getline(cin, titulo);
                
                eliminarAlbum(titulo);
                break;
            }

            case 7: {
                // Añadir canción a álbum
                string tituloAlbum, tituloCancion;
                
                cout << "Ingrese título del álbum: ";
                cin.ignore();
                getline(cin, tituloAlbum);
                
                cout << "Ingrese título de la canción: ";
                getline(cin, tituloCancion);
                
                insertarCancionAlbum(tituloAlbum, tituloCancion);
                break;
            }

            case 8: {
                // Eliminar canción de álbum
                string tituloAlbum, tituloCancion;
                
                cout << "Ingrese título del álbum: ";
                cin.ignore();
                getline(cin, tituloAlbum);
                
                cout << "Ingrese título de la canción a eliminar: ";
                getline(cin, tituloCancion);
                
                eliminarCancionAlbum(tituloAlbum, tituloCancion);
                break;
            }

            case 9:
                cout << "Volviendo al menú principal...\n";
                break;

            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 9);
}

//Menú con las opciones para modificar la lista de géneros musicales
void subMenuGenero() {
    int opcion;
    do {
        cout << "\n--- SUBMENÚ GÉNEROS ---\n";
        cout << "1. Insertar género\n";
        cout << "2. Modificar ID de género\n";
        cout << "3. Modificar nombre de género\n";
        cout << "4. Modificar descripción de género\n";  
        cout << "5. Eliminar género\n";
        cout << "6. Añadir canción a género\n";          
        cout << "7. Eliminar canción de género\n";       
        cout << "8. Volver al menú anterior\n";
        cout << "Seleccione una opción: ";
        opcion = validInteger();

        switch (opcion) {
            case 1: {
                int idGenero;
                string nombreGenero, descripcion;
                cout << "Ingrese ID del género: ";
                idGenero = validInteger();

                if (generoYaExiste(idGenero, "")) {
                    cout << "Error: ID ya existe.\n";
                    break;
                }

                cout << "Ingrese nombre del género: ";
                cin >> nombreGenero;

                if (generoYaExiste(0, nombreGenero)) {
                    cout << "Error: Nombre ya existe.\n";
                    break;
                }

                cout << "Ingrese descripción: ";
                cin.ignore();
                getline(cin, descripcion);

                insertarGeneroMusical(idGenero, nombreGenero, descripcion);
                break;
            }

            case 2: {
                string nombre;
                int nuevoID;
                cout << "Ingrese nombre del género a modificar: ";
                cin >> nombre;
                cout << "Ingrese nuevo ID: ";
                nuevoID = validInteger();

                if (generoYaExiste(nuevoID, "")) {
                    cout << "Error: Nuevo ID ya está en uso.\n";
                    break;
                }

                modificarIDGeneroMusical(nombre, nuevoID);
                break;
            }

            case 3: {
                string nombreActual, nuevoNombre;
                cout << "Ingrese nombre actual del género: ";
                cin >> nombreActual;
                cout << "Ingrese nuevo nombre: ";
                cin >> nuevoNombre;

                if (generoYaExiste(0, nuevoNombre)) {
                    cout << "Error: Nombre ya está en uso.\n";
                    break;
                }

                modificarnombreGeneroMusical(nombreActual, nuevoNombre);
                break;
            }

            case 4: {
                string nombre, nuevaDescripcion;
                cout << "Ingrese nombre del género: ";
                cin >> nombre;
                cout << "Ingrese nueva descripción: ";
                cin.ignore();
                getline(cin, nuevaDescripcion);

                modificarStringGeneroMusical(nombre, nuevaDescripcion);
                break;
            }

            case 5: {
                string nombre;
                cout << "Ingrese nombre del género a eliminar: ";
                cin >> nombre;
                eliminarGeneroMusical(nombre);
                break;
            }

            case 6: {
                string nombreGenero, tituloCancion;
                cout << "Ingrese nombre del género: ";
                cin >> nombreGenero;
                cout << "Ingrese título de la canción: ";
                cin.ignore();
                getline(cin, tituloCancion);

                insertarCancionGeneroMusical(nombreGenero, tituloCancion);
                break;
            }

            case 7: {
                string nombreGenero, tituloCancion;
                cout << "Ingrese nombre del género: ";
                cin >> nombreGenero;
                cout << "Ingrese título de la canción: ";
                cin.ignore();
                getline(cin, tituloCancion);

                eliminarCancionGeneroMusical(nombreGenero, tituloCancion);
                break;
            }

            case 8:
                cout << "Volviendo al menú principal...\n";
                break;

            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 8);
}
//Menú con las opciones para modificar la lista de playlists
void subMenuPlaylist() {
    int opcion;
    do {
        cout << "\n--- SUBMENÚ PLAYLISTS ---\n";
        cout << "1. Insertar playlist\n";
        cout << "2. Modificar ID de playlist\n";
        cout << "3. Modificar nombre de playlist\n";
        cout << "4. Modificar creador de playlist\n";
        cout << "5. Modificar fecha de playlist\n";
        cout << "6. Eliminar playlist\n";
        cout << "7. Añadir canción a playlist\n";
        cout << "8. Eliminar canción de playlist\n";
        cout << "9. Volver al menú anterior\n";
        cout << "Seleccione una opción: ";
        opcion = validInteger();

        switch (opcion) {
            case 1: {
                int id, fecha;
                string nombre, creador;

                cout << "Ingrese ID de la playlist: ";
                id = validInteger();

                cout << "Ingrese nombre de la playlist: ";
                cin.ignore();
                getline(cin, nombre);

                if (playlistYaExiste(id, nombre)) {
                    break;
                }

                cout << "Ingrese nombre del creador: ";
                getline(cin, creador);

                cout << "Ingrese fecha (formato YYYYMMDD): ";
                fecha = validInteger();

                insertarPlaylist(id, nombre, creador, fecha);
                cout << "Playlist creada exitosamente!\n";
                break;
            }

            case 2: {
                string nombre;
                int nuevoID;

                cout << "Ingrese nombre de la playlist a modificar: ";
                cin.ignore();
                getline(cin, nombre);

                cout << "Ingrese nuevo ID: ";
                nuevoID = validInteger();

                if (playlistYaExiste(nuevoID, "")) {
                    cout << "Error: El nuevo ID ya está en uso por otra playlist.\n";
                    break;
                }

                modificarIDPlaylist(nombre, nuevoID);
                break;
            }

            case 3: {
                string nombreActual, nuevoNombre;

                cout << "Ingrese nombre actual de la playlist: ";
                cin.ignore();
                getline(cin, nombreActual);

                cout << "Ingrese nuevo nombre: ";
                getline(cin, nuevoNombre);

                if (playlistYaExiste(0, nuevoNombre)) {
                    cout << "Error: El nuevo nombre ya está en uso por otra playlist.\n";
                    break;
                }

                modificarNombrePlaylist(nombreActual, nuevoNombre);
                break;
            }

            case 4: {
                string nombre, nuevoCreador;

                cout << "Ingrese nombre de la playlist: ";
                cin.ignore();
                getline(cin, nombre);

                cout << "Ingrese nuevo creador: ";
                getline(cin, nuevoCreador);

                modificarCreadorPlaylist(nombre, nuevoCreador);
                break;
            }

            case 5: {
                string nombre;
                int nuevaFecha;

                cout << "Ingrese nombre de la playlist: ";
                cin.ignore();
                getline(cin, nombre);

                cout << "Ingrese nueva fecha (formato YYYYMMDD): ";
                nuevaFecha = validInteger();

                modificarFechaPlaylist(nombre, nuevaFecha);
                break;
            }

            case 6: {
                string nombre;

                cout << "Ingrese nombre de la playlist a eliminar: ";
                cin.ignore();
                getline(cin, nombre);

                eliminarPlaylist(nombre);
                break;
            }

            case 7: {
                string nombrePlaylist, tituloCancion;

                cout << "Ingrese nombre de la playlist: ";
                cin.ignore();
                getline(cin, nombrePlaylist);

                cout << "Ingrese título de la canción: ";
                getline(cin, tituloCancion);

                insertarCancionPlaylist(nombrePlaylist, tituloCancion);
                break;
            }

            case 8: {
                string nombrePlaylist, tituloCancion;

                cout << "Ingrese nombre de la playlist: ";
                cin.ignore();
                getline(cin, nombrePlaylist);

                cout << "Ingrese título de la canción a eliminar: ";
                getline(cin, tituloCancion);

                eliminarCancionPlaylist(nombrePlaylist, tituloCancion);
                break;
            }

            case 9:
                cout << "Volviendo al menú principal...\n";
                break;

            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 9);
}



//Menú con las opciones para modificar la lista de sellos discográficos
void subMenuSello() {
    int opcion;
    do {
        cout << "\n--- SUBMENÚ SELLOS DISCOGRÁFICOS ---\n";
        cout << "1. Insertar sello\n";
        cout << "2. Modificar ID de sello\n";
        cout << "3. Modificar nombre de sello\n";
        cout << "4. Modificar país de sello\n";
        cout << "5. Modificar año de fundación\n";
        cout << "6. Eliminar sello\n";
        cout << "7. Añadir artista a sello\n";
        cout << "8. Eliminar artista de sello\n";
        cout << "9. Volver al menú anterior\n";
        cout << "Seleccione una opción: ";
        opcion = validInteger();

        switch (opcion) {
            case 1: {
                int id, anno;
                string nombre, pais;
                
                cout << "Ingrese ID del sello: ";
                id = validInteger();
                
                cout << "Ingrese nombre del sello: ";
                cin.ignore();
                getline(cin, nombre);
                
                if (selloYaExiste(id, nombre)) {
                    break;
                }
                
                cout << "Ingrese país de origen: ";
                nombre = validString();
                getline(cin, pais);
                
                cout << "Ingrese año de fundación: ";
                anno = validInteger();
                
                insertarSellosDiscograficos(id, nombre, pais, anno);
                cout << "Sello creado exitosamente!\n";
                break;
            }

            case 2: {
                string nombre;
                int nuevoID;
                
                cout << "Ingrese nombre del sello a modificar: ";
                cin.ignore();
                getline(cin, nombre);
                
                cout << "Ingrese nuevo ID: ";
                nuevoID = validInteger();
                
                if (selloYaExiste(nuevoID, "")) {
                    break;
                }
                
                modificarIDSelloDiscografico(nombre, nuevoID);
                break;
            }

            case 3: {
                string nombreActual, nuevoNombre;
                
                cout << "Ingrese nombre actual del sello: ";
                cin.ignore();
                getline(cin, nombreActual);
                
                cout << "Ingrese nuevo nombre: ";
                getline(cin, nuevoNombre);
                
                if (selloYaExiste(0, nuevoNombre)) {
                    break;
                }
                
                modificarNombreSelloDiscografico(nombreActual, nuevoNombre);
                break;
            }

            case 4: {
                string nombre, nuevoPais;
                
                cout << "Ingrese nombre del sello: ";
                cin.ignore();
                getline(cin, nombre);
                
                cout << "Ingrese nuevo país: ";
                getline(cin, nuevoPais);
                
                modificarPaisSelloDiscografico(nombre, nuevoPais);
                break;
            }

            case 5: {
                string nombre;
                int nuevoAnno;
                
                cout << "Ingrese nombre del sello: ";
                cin.ignore();
                getline(cin, nombre);
                
                cout << "Ingrese nuevo año de fundación: ";
                nuevoAnno = validInteger();
                
                modificarAnnoFundacionSelloDiscografico(nombre, nuevoAnno);
                break;
            }

            case 6: {
                string nombre;
                
                cout << "Ingrese nombre del sello a eliminar: ";
                cin.ignore();
                getline(cin, nombre);
                
                eliminarSelloDiscografico(nombre);
                break;
            }

            case 7: {
                string nombreSello, nombreArtista;
                
                cout << "Ingrese nombre del sello: ";
                cin.ignore();
                getline(cin, nombreSello);
                
                cout << "Ingrese nombre del artista: ";
                getline(cin, nombreArtista);
                
                insertarArtistaSelloDiscografico(nombreSello, nombreArtista);
                break;
            }

            case 8: {
                string nombreSello, nombreArtista;
                
                cout << "Ingrese nombre del sello: ";
                cin.ignore();
                getline(cin, nombreSello);
                
                cout << "Ingrese nombre del artista a eliminar: ";
                getline(cin, nombreArtista);
                
                eliminarArtistaSelloDiscografico(nombreSello, nombreArtista);
                break;
            }

            case 9:
                cout << "Volviendo al menú principal...\n";
                break;

            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 9);
}

//Menú de mantenimiento para interactuar con las listas 
void Mantenimiento() {
    int opcion;
    do {
        cout << "\n----- Submenú Mantenimiento -----" << endl;
        cout << "1. Artistas" << endl;
        cout << "2. Álbums" << endl;
        cout << "3. Canciones" << endl;
        cout << "4. Géneros Musicales" << endl;
        cout << "5. Playlists" << endl;
        cout << "6. Sellos Discográficos" << endl;
        cout << "7. Volver al Menú Principal" << endl;
        cout << "Seleccione una opción: ";
        opcion = validInteger();

        switch(opcion) {
            case 1: subMenuArtista(); break;
            case 2: subMenuAlbum(); break;
            case 3: subMenuCancion(); break;
            case 4: subMenuGenero(); break;
            case 5: subMenuPlaylist(); break;
            case 6: subMenuSello(); break;
            case 7: cout << "Volviendo al menú principal..." << endl; break;
            default: cout << "Opción no válida. Intente de nuevo." << endl; break;
        }
    } while (opcion != 7); 
}

//Interfaz de menú de consultas
void consultasAux(){
    cout << "\n" << "-------------------------------------------------" << endl;
    cout << "Menu de consultas" << endl;
    cout << "1 = Género con más canciones registradas" << endl;
    cout << "2 = Artista con más ablumes publicados " << endl;
    cout << "3 = Canción más larga de la base de datos" << endl;
    cout << "4 = Playlist con más canciones" << endl;
    cout << "5 = Cantidad de álbumes por artista" << endl;
    cout << "6 = Sello Discográfico con más artistas firmados" << endl;
    cout << "7 = Canciones publicadas en un año determinado" << endl;
    cout << "8 = Álbumes que superan un número determinado de canciones" << endl;
    cout << "9 = Volver al menu principal" << endl;
    cout << "Presione un número para seleccionar que hacer " << endl;
    
}
//Menú de reportes para imprimir las listas que desee el usuario
void reportes() {
    int opcion;
    std::cout << "=== MENÚ DE REPORTES ===\n";
    std::cout << "1. Imprimir todo\n";
    std::cout << "2. Imprimir canciones\n";
    std::cout << "3. Imprimir álbumes\n";
    std::cout << "4. Imprimir artistas\n";
    std::cout << "5. Imprimir géneros musicales\n";
    std::cout << "6. Imprimir playlists\n";
    std::cout << "7. Imprimir sellos discográficos\n";
    std::cout << "Seleccione una opción: ";
    std::cin >> opcion;

    switch(opcion) {
        case 1:
            imprimirCanciones();
            imprimirAlbumes();
            imprimirArtistas();
            imprimirGenerosMusicales();
            imprimirPlaylists();
            imprimirSellosDiscograficos();
            break;
        case 2:
            imprimirCanciones();
            break;
        case 3:
            imprimirAlbumes();
            break;
        case 4:
            imprimirArtistas();
            break;
        case 5:
            imprimirGenerosMusicales();
            break;
        case 6:
            imprimirPlaylists();
            break;
        case 7:
            imprimirSellosDiscograficos();
            break;
        default:
            std::cout << "Opción inválida.\n";
            break;
    }
}

//Interfaz de menú principal
void interfazAux(){
    cout << "\n" << "-------------------------------------------------" << endl;
    cout << "Bienvenido a Musigest" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Menu de interacción" << endl;
    cout << "1 = Mantenimiento" << endl;
    cout << "2 = Consultas " << endl;
    cout << "3 = Reportes" << endl;
    cout << "4 = Salida" << endl;
    cout << "Presione un número para seleccionar que hacer " << endl;
}
//Menú de consultas para responder las curiosidades del usuario
void consultas() {
    int opcion;
    do {
        consultasAux();
        opcion = validInteger();
        
        switch(opcion) {
            case 1:
                generoPopular();
                break;
            case 2:
                artistaTrabajador();
                break;
            case 3:
                cancionLarga();
                break;
            case 4:
                playlistLarga();
                break;
            case 5:
                albumesPorArtista();
                break;
            case 6:
                selloDiscograficoPopular();
                break;
            case 7: {
                cout << "Ingrese el año a consultar: ";
                int x = validInteger();
                cancionesEnAnnoDetermindado(x);
                break;
            }
            case 8: {
                cout << "Ingrese el número mínimo de canciones: ";
                int x = validInteger();
                albumesSuperiorNumero(x);
                break;
            }
            case 9:
                cout << "Volviendo al menú anterior..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
        
        // Pausa para ver resultados antes de volver al menú
        if(opcion != 9) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while(opcion != 9);  // Sale del bucle cuando elige 9 (Volver)
}

//Menú principal
void interfaz(){
    int n;
    while (true){
        interfazAux();
        n = validInteger();
        switch (n){
            case 1:
                Mantenimiento();
                break;
            case 2:
                consultas();
                break;
            case 3:
                reportes();
                break;
            case 4:
                return;
        }
    }
}







int main (){


    //Test cases (10 por función)

    insertarCancion(111,"Show me how",5); //Men I Trust
    insertarCancion(213, "Halcyon", 4); // Men I Trust
    insertarCancion(789, "Forever", 3); // Clairo
    insertarCancion(345, "Glue Song", 3); // Beabadoobee
    insertarCancion(567, "The London", 4); // J. Cole, Future
    insertarCancion(910, "Yoru ni Kakeru", 4); // Yoasobi
    insertarCancion(678, "Pushin P", 2); // Gunna
    insertarCancion(432, "Numb", 3); // Men I Trust
    insertarCancion(156, "Sofia", 3); // Clairo
    insertarCancion(299, "See You Soon", 3); // Beabadoobee
    insertarCancion(701, "Wet Dreamz", 4); // J. Cole


    insertarAlbum(243,"Charm",2024);
    insertarAlbum(382, "THE BOOK 2", 2023); // Yoasobi
    insertarAlbum(715, "Immunity", 2019); // Clairo
    insertarAlbum(926, "DS4EVER", 2022); // Gunna
    insertarAlbum(564, "Forever Live Sessions", 2021); // Men I Trust
    insertarAlbum(837, "Beatopia", 2022); // Beabadoobee
    insertarAlbum(490, "2014 Forest Hills Drive", 2014); // J. Cole
    insertarAlbum(311, "High Off Life", 2020); // Future
    insertarAlbum(112, "The Book", 2021); // Yoasobi
    insertarAlbum(456, "Sling", 2021); // Clairo
    insertarAlbum(789, "Wunna", 2020); // Gunna
    insertarAlbum(234, "Oncle Jazz", 2019); // Men I Trust
    insertarAlbum(678, "Fake It Flowers", 2020); // Beabadoobee
    insertarAlbum(901, "KOD", 2018); // J. Cole
    insertarAlbum(345, "I Never Liked You", 2022); // Future

    insertarArtistas(456,"Yoasobi","Lilas","Japan");
    insertarArtistas(123,"Clairo","Claire","USA");
    insertarArtistas(789,"Gunna","Sergio","USA");
    insertarArtistas(303,"Men I Trust","Men I Trust","Canada");
    insertarArtistas(101,"Beabadoobee","Beatrice Kristi Laus","Philippines");
    insertarArtistas(505,"J. Cole","Jermaine Cole","USA");
    insertarArtistas(808,"Future","Nayvadius DeMun Wilburn","USA");
    insertarArtistas(202, "Taylor Swift", "Taylor Alison Swift", "USA");
    insertarArtistas(707, "Bad Bunny", "Benito Antonio Martínez Ocasio", "Puerto Rico");
    insertarArtistas(404, "BTS", "Bangtan Sonyeondan", "South Korea");


    insertarGeneroMusical(111,"Rap","You know what rap is");
    insertarGeneroMusical(222,"Indie","Idk if this is a real genre");
    insertarGeneroMusical(333,"Pop","Like taylor swift or something");
    insertarGeneroMusical(444,"Country","The one nobody likes");
    insertarGeneroMusical(555, "Rock", "Guitar-driven music genre");
    insertarGeneroMusical(666, "Electronic", "Music created using electronic instruments");
    insertarGeneroMusical(777, "R&B", "Rhythm and Blues");
    insertarGeneroMusical(888, "Jazz", "Improvisational music with swing and blue notes");
    insertarGeneroMusical(999, "Classical", "Traditional Western art music");
    insertarGeneroMusical(101, "Hip Hop", "Urban music genre originating in the Bronx");

    insertarPlaylist(231,"Best hits","Random Dude",2025);
    insertarPlaylist(324,"Running or idk","Runner",2077);
    insertarPlaylist(431,"Sleeping","Lazy guy",2024);
    insertarPlaylist(567, "Workout Mix", "Fitness Guru", 2023);
    insertarPlaylist(890, "Chill Vibes", "Relaxation Expert", 2022);
    insertarPlaylist(123, "Study Focus", "Student", 2024);
    insertarPlaylist(456, "Party Hits", "DJ", 2023);
    insertarPlaylist(789, "Road Trip", "Traveler", 2021);
    insertarPlaylist(234, "Rainy Day", "Weather Fan", 2020);
    insertarPlaylist(901, "Morning Coffee", "Barista", 2023);

    insertarSellosDiscograficos(789, "Sony Music Japan", "Japan", 1968); // Yoasobi
    insertarSellosDiscograficos(456, "FADER Label", "USA", 2002); // Clairo
    insertarSellosDiscograficos(234, "YSL Records", "USA", 2016); // Gunna
    insertarSellosDiscograficos(567, "Independent", "Canada", 2015); // Men I Trust
    insertarSellosDiscograficos(901, "Dirty Hit", "UK", 2010); // Beabadoobee
    insertarSellosDiscograficos(678, "Dreamville Records", "USA", 2007); // J. Cole
    insertarSellosDiscograficos(345, "Epic Records", "USA", 1953); // Future
    insertarSellosDiscograficos(111, "Republic Records", "USA", 1995);
    insertarSellosDiscograficos(222, "Interscope Records", "USA", 1990);
    insertarSellosDiscograficos(333, "Atlantic Records", "USA", 1947);


    insertarCancionAlbum("Charm", "Show me how");
    insertarCancionAlbum("Charm", "Numb");
    insertarCancionAlbum("THE BOOK 2", "Yoru ni Kakeru");
    insertarCancionAlbum("Immunity", "Sofia");
    insertarCancionAlbum("DS4EVER", "Pushin P");
    insertarCancionAlbum("Forever Live Sessions", "Forever");
    insertarCancionAlbum("Beatopia", "Glue Song");
    insertarCancionAlbum("2014 Forest Hills Drive", "Wet Dreamz");
    insertarCancionAlbum("High Off Life", "The London");
    insertarCancionAlbum("The Book", "Yoru ni Kakeru");

    insertarCancionArtista("Men I Trust", "Show me how");
    insertarCancionArtista("Men I Trust", "Halcyon");
    insertarCancionArtista("Clairo", "Forever");
    insertarCancionArtista("Beabadoobee", "Glue Song");
    insertarCancionArtista("J. Cole", "The London");
    insertarCancionArtista("Yoasobi", "Yoru ni Kakeru");
    insertarCancionArtista("Gunna", "Pushin P");
    insertarCancionArtista("Men I Trust", "Numb");
    insertarCancionArtista("Clairo", "Sofia");
    insertarCancionArtista("Beabadoobee", "See You Soon");

    insertarAlbumArtista("Men I Trust", "Charm");
    insertarAlbumArtista("Yoasobi", "THE BOOK 2");
    insertarAlbumArtista("Clairo", "Immunity");
    insertarAlbumArtista("Gunna", "DS4EVER");
    insertarAlbumArtista("Men I Trust", "Forever Live Sessions");
    insertarAlbumArtista("Beabadoobee", "Beatopia");
    insertarAlbumArtista("J. Cole", "2014 Forest Hills Drive");
    insertarAlbumArtista("Future", "High Off Life");
    insertarAlbumArtista("Yoasobi", "The Book");
    insertarAlbumArtista("Clairo", "Sling");

    insertarCancionGeneroMusical("Indie", "Show me how");
    insertarCancionGeneroMusical("Indie", "Halcyon");
    insertarCancionGeneroMusical("Pop", "Forever");
    insertarCancionGeneroMusical("Indie", "Glue Song");
    insertarCancionGeneroMusical("Rap", "The London");
    insertarCancionGeneroMusical("Pop", "Yoru ni Kakeru");
    insertarCancionGeneroMusical("Rap", "Pushin P");
    insertarCancionGeneroMusical("Indie", "Numb");
    insertarCancionGeneroMusical("Indie", "Sofia");
    insertarCancionGeneroMusical("Indie", "See You Soon");

    insertarCancionPlaylist("Best hits", "Show me how");
    insertarCancionPlaylist("Best hits", "Yoru ni Kakeru");
    insertarCancionPlaylist("Running or idk", "Pushin P");
    insertarCancionPlaylist("Running or idk", "The London");
    insertarCancionPlaylist("Sleeping", "Glue Song");
    insertarCancionPlaylist("Sleeping", "Numb");
    insertarCancionPlaylist("Workout Mix", "Pushin P");
    insertarCancionPlaylist("Chill Vibes", "Show me how");
    insertarCancionPlaylist("Study Focus", "Numb");
    insertarCancionPlaylist("Party Hits", "The London");

    insertarArtistaSelloDiscografico("Sony Music Japan", "Yoasobi");
    insertarArtistaSelloDiscografico("FADER Label", "Clairo");
    insertarArtistaSelloDiscografico("YSL Records", "Gunna");
    insertarArtistaSelloDiscografico("Dirty Hit", "Beabadoobee");
    insertarArtistaSelloDiscografico("Dreamville Records", "J. Cole");
    insertarArtistaSelloDiscografico("Epic Records", "Future");
    insertarArtistaSelloDiscografico("Republic Records", "Taylor Swift");
    insertarArtistaSelloDiscografico("Interscope Records", "Bad Bunny");
    insertarArtistaSelloDiscografico("Atlantic Records", "BTS");
    insertarArtistaSelloDiscografico("Independent", "Men I Trust");

    
    eliminarCancionAlbum("Charm", "Numb");
    eliminarCancionArtista("Men I Trust", "Halcyon");
    eliminarCancionGeneroMusical("Indie", "Show me how");
    eliminarCancionPlaylist("Best hits", "Show me how");
    eliminarAlbumArtista("Men I Trust", "Forever Live Sessions");
    eliminarArtistaSelloDiscografico("Independent", "Men I Trust");

 
    eliminarCancion("See You Soon");
    eliminarAlbum("Sling");
    eliminarArtista("Future");
    eliminarGeneroMusical("Country");
    eliminarPlaylist("Sleeping");
    eliminarSelloDiscografico("Epic Records");

    imprimirCanciones();
    imprimirAlbumes();
    imprimirArtistas();
    imprimirPlaylists();
    imprimirGenerosMusicales();
    imprimirSellosDiscograficos();
    interfaz();

    return 0;
}
