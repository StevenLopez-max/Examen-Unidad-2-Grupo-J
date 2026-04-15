#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Plato {
private:
    int codigo;
    string nombre;
    string categoria;
    float costo;
    float precio;
    int tiempoPreparacion;
    bool disponible;
    int demanda;
public:
    Plato() {
        codigo = 0;
        nombre = "";
        categoria = "";
        costo = 0;
        precio = 0;
        tiempoPreparacion = 0;
        disponible = true;
        demanda = 0;
    }
    void registrar() {
        cout << "Codigo: "; cin >> codigo;
        cout << "Nombre: "; cin >> nombre;
        cout << "Categoria: "; cin >> categoria;
        cout << "Costo: "; cin >> costo;
        cout << "Precio: "; cin >> precio;
        cout << "Tiempo preparacion: "; cin >> tiempoPreparacion;
        disponible = true;
    }

    void mostrar() {
        cout << codigo << " - " << nombre << " $" << precio << endl;
    }

    int getCodigo() { return codigo; }
    float getPrecio() { return precio; }
    int getTiempo() { return tiempoPreparacion; }

    void aumentarDemanda() { demanda++; }
    int getDemanda() { return demanda; }
};

class Pedido {
private:
    string cliente;
    int mesa;
    string hora;
    int prioridad;
    vector<Plato> platos;

public:
    void registrarPedido(vector<Plato>& lista) {
        cout << "Cliente: "; cin >> cliente;
        cout << "Mesa: "; cin >> mesa;

        cin.ignore();
        cout << "Hora (HH:MM): ";
        getline(cin, hora);

        cout << "Prioridad (1-3): "; cin >> prioridad;

        int op;
        do {
            cout << "\nMENU\n";
            for (int i = 0; i < lista.size(); i++) {
                cout << i + 1 << ". ";
                lista[i].mostrar();
            }

            cout << "Seleccione (-1 salir): ";
            cin >> op;

            if (op > 0 && op <= lista.size()) {
                platos.push_back(lista[op - 1]);
                lista[op - 1].aumentarDemanda();
            }

        } while (op != -1);
    }

    float subtotalRecursivo(int i) {
    if (i >= platos.size()) return 0;
    return platos[i].getPrecio() + subtotalRecursivo(i + 1);
}

    float total() {
        float sub = subtotalRecursivo(0);
        float descuento = sub * 0.1;
        float recargo = (prioridad == 3) ? sub * 0.05 : 0;
        float iva = sub * 0.12;

        return sub - descuento + recargo + iva;
    }

    string getCliente() { return cliente; }

    void mostrar() {
        cout << "\nCliente: " << cliente;
        cout << "\nSubtotal: $" << subtotalRecursivo(0) << endl;
        cout << "\nTotal: $" << total() << endl;
    }
};

// -------- FUNCIONES EXTRAS --------

void buscarCliente(vector<Pedido> pedidos) {
    string nombre;
    cout << "Buscar cliente: ";
    cin >> nombre;

    for (auto p : pedidos) {
        if (p.getCliente() == nombre) {
            p.mostrar();
        }
    }
}

void ordenarDemanda(vector<Plato>& lista) {
    sort(lista.begin(), lista.end(), [](Plato a, Plato b) {
        return a.getDemanda() > b.getDemanda();
    });
    cout << "Ordenado por demanda\n";
}

void ordenarTiempo(vector<Plato>& lista) {
    sort(lista.begin(), lista.end(), [](Plato a, Plato b) {
        return a.getTiempo() < b.getTiempo();
    });
    cout << "Ordenado por tiempo\n";
}

// -------- STOCK SIMPLE --------
int stockIngredientes = 10;

void usarStock() {
    stockIngredientes--;
    if (stockIngredientes <= 2) {
        cout << " ALERTA: Poco stock\n";
    }
}
// ---------------- VARIABLES GLOBALES ----------------
int partidasGanadas = 0;
int partidasPerdidas = 0;

// ---------------- FUNCION JUEGO ----------------
void jugar(string palabra) {
    string progreso(palabra.size(), '_');
    vector<char> usadas;
    int intentos = 6;

    while (intentos > 0 && progreso != palabra) {
        cout << "\nPalabra: " << progreso << endl;
        cout << "Intentos restantes: " << intentos << endl;

        cout << "Letras usadas: ";
        for (char c : usadas) cout << c << " ";
        cout << endl;

        char letra;
        cout << "Ingrese una letra: ";
        cin >> letra;

        letra = tolower(letra);

        // Validar letra
        if (!isalpha(letra)) {
            cout << " Solo letras\n";
            continue;
        }

        // Evitar repetidas
        if (find(usadas.begin(), usadas.end(), letra) != usadas.end()) {
            cout << "Letra repetida\n";
            continue;
        }

        usadas.push_back(letra);

        bool acierto = false;
        for (int i = 0; i < palabra.size(); i++) {
            if (tolower(palabra[i]) == letra) {
                progreso[i] = palabra[i];
                acierto = true;
            }
        }

        if (!acierto) intentos--;
    }

    if (progreso == palabra) {
        cout << "\n Ganaste! La palabra era: " << palabra << endl;
        partidasGanadas++;
    } else {
        cout << "\nPerdiste! La palabra era: " << palabra << endl;
        partidasPerdidas++;
    }
}

// ---------------- 1 VS 1 ----------------
void modo1vs1() {
    string palabra;
    cout << "Jugador 1 ingrese la palabra: ";
    cin >> palabra;

    // Limpiar pantalla simple
    for (int i = 0; i < 30; i++) cout << endl;

    jugar(palabra);
}

// ---------------- CPU ----------------
void modoCPU() {
    int opcion;
    cout << "\n--- Seleccione dificultad ---\n";
    cout << "1. Facil\n2. Medio\n3. Dificil\n";
    cin >> opcion;

    string palabra;

    switch (opcion) {
        case 1: palabra = "pizza"; break;
        case 2: palabra = "encebollado"; break;
        case 3: palabra = "yahuarlocro"; break;
        default:
            cout << "Opcion invalida\n";
            return;
    }

    jugar(palabra);
}

// ---------------- INSTRUCCIONES ----------------
void instrucciones() {
    cout << "\n--- INSTRUCCIONES ---\n";
    cout << "- Adivina la palabra letra por letra\n";
    cout << "- Tienes 6 intentos\n";
    cout << "- Solo puedes ingresar letras\n";
    cout << "- No repetir letras\n";
}

// ---------------- RESULTADOS ----------------
void resultados() {
    cout << "\n--- RESULTADOS ---\n";
    cout << "Ganadas: " << partidasGanadas << endl;
    cout << "Perdidas: " << partidasPerdidas << endl;
}

// ---------------- MENU AHORCADO ----------------
void menuAhorcado() {
    int opcion;

    do {
        cout << "\n===== AHORCADO =====\n";
        cout << "1. Jugar 1 vs 1\n";
        cout << "2. Jugar contra CPU\n";
        cout << "3. Ver resultados\n";
        cout << "4. Instrucciones\n";
        cout << "5. Volver al menu principal\n";
        cout << "Seleccione: ";
        cin >> opcion;

        switch (opcion) {
            case 1: modo1vs1(); break;
            case 2: modoCPU(); break;
            case 3: resultados(); break;
            case 4: instrucciones(); break;
            case 5: cout << "Volviendo...\n"; break;
            default: cout << "Opcion invalida\n";
        }

    } while (opcion != 5);
}

// -------- MAIN --------
int main() {
    vector<Plato> platos;
    vector<Pedido> pedidos;

    int op;

    do {
        cout << "\n1. Registrar Plato";
        cout << "\n2. Crear Pedido";
        cout << "\n3. Buscar Cliente";
        cout << "\n4. Ordenar por Demanda";
        cout << "\n5. Ordenar por Tiempo";
        cout << "\n6. Jugar Ahorcado";
        cout << "\n0. Salir\nOpcion: ";
        cin >> op;

        switch (op) {
            case 1: {
                Plato p;
                p.registrar();
                platos.push_back(p);
                break;
            }

            case 2: {
                Pedido ped;
                ped.registrarPedido(platos);
                ped.mostrar();
                pedidos.push_back(ped);
                usarStock();
                break;
            }

            case 3:
                buscarCliente(pedidos);
                break;

            case 4:
                ordenarDemanda(platos);
                break;

            case 5:
                ordenarTiempo(platos);
                break;
            case 6:
            menuAhorcado();
        }
            

    } while (op != 0);

    return 0;
}