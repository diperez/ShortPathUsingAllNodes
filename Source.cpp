#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

//clase para representar las ciudades
class Ciudad
{
	public:
		string nombre;
		int num;
		vector <int> nodos;
		bool visitado;
};

//clase para almacenar la informacion de los caminos entre las ciudades
class Camino
{
	public:
		string camino;
		int distanciaTotal;
};


int cn = 9; //cantidad de ciudades
int rutaOrigen =-1; // las rutas estan representadas desde el 0 al 8 ya que son 9 rutas.
vector<vector <int>> distancias; // matriz de distancias que se encontraban en excel
vector<Camino> caminos; // vector donde se almacenan todos los caminos posibles para luego elegir el optimo
Ciudad ciudades[9]; // arreglo de las 9 ciudades especificadas


//inicializa la matriz de distancias especificadas en el documento en excel
void inicializarDistancias()
{
	int const vmani[] = {0,88,132,45,29,46,93,29,130};
	vector<int> vman (std::begin (vmani), std::end (vmani));
	
	int const vboai[] = {88,0,220,107,62,127,181,91,149};
	vector<int> vboa (std::begin (vboai), std::end (vboai));	

	int const vchii[] = {132,220,0,177,134,177,37,161,181};
	vector<int> vchi (std::begin (vchii), std::end (vchii));

	int const vgrai[] = {45,107,177,0,44,41,138,16,148};
	vector<int> vgra (std::begin (vgrai), std::end (vgrai));
	
	int const vsbni[] = {29,62,134,44,0,53,121,38,70};
	vector<int> vsbn (std::begin (vsbni), std::end (vsbni));

	int const vjini[] = {46,127,177,41,53,0,122,37,170};
	vector<int> vjin (std::begin (vjini), std::end (vjini));

	int const vleoi[] = {93,181,37,138,121,122,0,122,130};
	vector<int> vleo (std::begin (vleoi), std::end (vleoi));

	int const vmasi[] = {29,91,161,16,165,37,122,0,130};
	vector<int> vmas (std::begin (vmasi), std::end (vmasi));

	int const vmati[] = {130,149,181,148,70,170,130,130,0};
	vector<int> vmat (std::begin (vmati), std::end (vmati));
	
	distancias.push_back(vman);
	distancias.push_back(vboa);
	distancias.push_back(vchi);
	distancias.push_back(vgra);
	distancias.push_back(vsbn);
	distancias.push_back(vjin);
	distancias.push_back(vleo);
	distancias.push_back(vmas);
	distancias.push_back(vmat);
}

//inicializa la informacion de la ciudades y sus interconexiones
void inicializarCiudades()
{
	Ciudad man;
	int const vmani[] = {6,7,5,4};
	vector<int> vman (std::begin (vmani), std::end (vmani));

	man.nombre = "Man";
	man.num = 0;
	man.visitado = 0;
	man.nodos =vman;

	ciudades[0] = man;

	Ciudad boa;
	int const vboai[] = {8,4};
	vector<int> vboa (std::begin (vboai), std::end (vboai));

	boa.nombre = "Boa";
	boa.num = 1;
	boa.visitado = 0;
	boa.nodos = vboa;

	ciudades[1] = boa;

	Ciudad chi;
	int const vchii[] = {6,8};
	vector<int> vchi (std::begin (vchii), std::end (vchii));

	chi.nombre = "Chi";
	chi.num = 2;
	chi.visitado = 0;
	chi.nodos = vchi;


	ciudades[2] = chi;


	Ciudad gra;
	int const vgrai[] = {5,7,4};
	vector<int> vgra (std::begin (vgrai), std::end (vgrai));

	gra.nombre = "Gra";
	gra.num = 3;
	gra.visitado = 0;
	gra.nodos = vgra;

	ciudades[3] = gra;


	Ciudad snb;
	int const vsnbi[] = {8,1,0,3};
	vector<int> vsnb (std::begin (vsnbi), std::end (vsnbi));

	snb.nombre = "Snb";
	snb.num = 4;
	snb.visitado = 0;
	snb.nodos = vsnb;

	ciudades[4] = snb;

	Ciudad jin;
	int const vjini[] = {0,3,7};
	vector<int> vjin (std::begin (vjini), std::end (vjini));

	jin.nombre = "Jin";
	jin.num = 5;
	jin.visitado = 0;
	jin.nodos = vjin;

	ciudades[5] = jin;

	Ciudad leo;
	int const vleoi[] = {0,2,8};
	vector<int> vleo (std::begin (vleoi), std::end (vleoi));

	leo.nombre = "Leo";
	leo.num = 6;
	leo.visitado = 0;
	leo.nodos = vleo;

	ciudades[6] = leo;

	Ciudad mas;
	int const vmasi[] = {3,5,0};
	vector<int> vmas (std::begin (vmasi), std::end (vmasi));

	mas.nombre = "Mas";
	mas.num = 7;
	mas.visitado = 0;
	mas.nodos = vmas;

	ciudades[7] = mas;

	Ciudad mat;
	int const vmati[] = {1,4,2,6};
	vector<int> vmat (std::begin (vmati), std::end (vmati));

	mat.nombre = "Mat";
	mat.num = 8;
	mat.visitado = 0;
	mat.nodos = vmat;

	ciudades[8] = mat;

}

//especifica al programa la ruta origin luego de leerla del usuario
void inicializarRutaOrigen(string nombreCiudadOrigen)
{
	for(int i =0; i < cn; i++)
	{
		if(ciudades[i].nombre == nombreCiudadOrigen)
		{
			rutaOrigen = ciudades[i].num;
		}
	}
}

//lee la ruta origen especificada por el usuario
void leerRutaInicio()
{
	string nombreCiudadOrigen;
	cout << "Por favor, introduzca el nombre de la ruta origen: ";
	cin >> nombreCiudadOrigen;

	inicializarRutaOrigen(nombreCiudadOrigen);
}

//retorna verdadero si todas las ciudades fueron visitadas en el camino
bool todasLasCiudadesVisitadas()
{
	for(int i =0; i < cn; i++)
	{
		if(ciudades[i].visitado == false)
		{
			return false;
		}
	}
	return true;
}

//guarda un camino si es candidato a ser el mas corto y paso por todas las rutas
void guardarCamino(string camino, int distanciaTotal)
{
	Camino caminoAGuardar;
	caminoAGuardar.camino = camino;
	caminoAGuardar.distanciaTotal = distanciaTotal;

	caminos.push_back(caminoAGuardar);
}

//funcion recursiva que encuentra el camino mas corto entre todas las ciudades partiendo de la ciudade origen especificada por el usuario.
void buscarCaminoMasCorto(int c, int distanciaTotal, string camino)
{
	Ciudad* actual = &ciudades[c];
	actual->visitado = true;
	camino += actual->nombre + "-> ";
	if(todasLasCiudadesVisitadas())
	{
		//cout << camino << distanciaTotal <<endl;
		camino = camino.substr(0, camino.size() -3);
		guardarCamino(camino, distanciaTotal);
	}

	for(unsigned int i=0; i < actual->nodos.size();i++)
	{
		if(ciudades[actual->nodos[i]].visitado == false)
		{
			//cout << "voy" << actual->num << " voy" << actual->nodos[i] <<endl;
			//system("pause");
			buscarCaminoMasCorto(actual->nodos[i], distanciaTotal + distancias[c][actual->nodos[i]], camino);
			ciudades[actual->nodos[i]].visitado = false;
		}
	}
}

// imprime todos los posibles caminos encontrados en la consola y su distancia total recorrida
void imprimirTodosLosCaminos()
{
	for(int i =0; i< caminos.size(); i++)
	{
		cout << "Camino #"<< i+1 << " "<< caminos[i].camino
			<< " y su distancia total fue " <<caminos[i].distanciaTotal<<endl; 
	}
}

//imprimer el camino mas corto en la consola y su distancia total recorrida
void imprimirElCaminoMasCorto()
{
	int elMasCorto;
	int minimo = INT_MAX;
	for(int i =0; i< caminos.size(); i++)
	{
		if(caminos[i].distanciaTotal < minimo)
		{
			elMasCorto = i;
			minimo = caminos[i].distanciaTotal;
		}
	}
	cout << "Camino mas corto es: "<< caminos[elMasCorto].camino
			<< " y su distancia total fue " <<caminos[elMasCorto].distanciaTotal<<endl; 
}

//funcion principal del programa
int main()
{
	inicializarDistancias();

	inicializarCiudades();

	leerRutaInicio();

	if(rutaOrigen >= 0)
	{
		buscarCaminoMasCorto(rutaOrigen, 0, "");
	
		imprimirTodosLosCaminos(); // comentar esta funcion si no se desean imprimir todos los caminos.

		imprimirElCaminoMasCorto();
	}else
	{
		cout << "La ciudad especificada no concuerda con las ciudades existentes." << endl;
	}

	system("pause");
}
