#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <limits>

// Incluimos todos los modelos y las implementaciones CONCRETAS
#include "models/Paciente.h"
#include "models/Medico.h"
#include "models/Cita.h"

// Implementaciones (los algoritmos que usaremos)
#include "implementations/RegistroEficiente.h"
#include "implementations/SchedulerOptimizado.h"
#include "implementations/AsignadorBalanceado.h"
#include "implementations/AsignadorSimple.h" // Incluimos el simple para comparar

// --- Función Auxiliar para limpiar la consola (simulación) ---
void limpiarPantalla() {
    for (int i = 0; i < 50; ++i) {
        std::cout << std::endl;
    }
}

// --- Función Auxiliar para esperar al usuario ---
void esperarUsuario() {
    std::cout << "\nPresiona Enter para continuar...";
    // Limpia el buffer de entrada antes de esperar
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// --- Función Auxiliar para leer un entero de forma segura ---
int leerOpcion() {
    int opcion;
    while (!(std::cin >> opcion)) {
        std::cout << "Error: Debes ingresar un numero. Intenta de nuevo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // Limpia el buffer de entrada (el 'Enter' después del número)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return opcion;
}

// --- Función Auxiliar para leer texto ---
std::string leerTexto() {
    std::string texto;
    std::getline(std::cin, texto);
    return texto;
}


int main() {
    // --- 1. INICIALIZACIÓN DEL SISTEMA ---

    // Elegimos qué algoritmo de asignación usar (¡Aquí puedes cambiar!)
    std::shared_ptr<IAsignadorPersonal> asignador =
        std::make_shared<AsignadorBalanceado>(); // <-- ¡ALGORITMO ÓPTIMO!
    // std::shared_ptr<IAsignadorPersonal> asignador =
    //    std::make_shared<AsignadorSimple>(); // (Prueba con este para ver la diferencia)


    std::shared_ptr<IRegistroPacientes> registro =
        std::make_shared<RegistroEficiente>();
    std::shared_ptr<ISchedulerCitas> scheduler =
        std::make_shared<SchedulerOptimizado>();

    // "Base de datos" de médicos (con especialidades)
    std::vector<Medico> medicosDisponibles = {
        {1, "Dr. House", "Cardiologia", 0},
        {2, "Dra. Grey", "Cirugia", 0},
        {3, "Dr. Shepherd", "Neurocirugia", 0},
        {4, "Dr. Wilson", "Cardiologia", 0} // <-- ¡Hay 2 de Cardiología!
    };

    // "Base de datos" de pacientes (para que no esté vacío)
    registro->agregarPaciente({101, "Paciente A", "Historial A..."});
    registro->agregarPaciente({102, "Paciente B", "Historial B..."});

    // Contador simple para IDs de Citas
    int proximoIdCita = 1;

    // --- 2. BUCLE PRINCIPAL DE LA APLICACIÓN (FRONTEND DE CONSOLA) ---
    bool corriendo = true;
    while (corriendo) {
        limpiarPantalla();
        std::cout << "=========================================" << std::endl;
        std::cout << "  SISTEMA DE GESTION - CLINICA RICARDO PALMA" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << "\n--- Modulo: Registro ---" << std::endl;
        std::cout << "  1. Registrar nuevo paciente" << std::endl;
        std::cout << "  2. Buscar paciente por ID" << std::endl;
        std::cout << "\n--- Modulo: Citas y Asignacion ---" << std::endl;
        std::cout << "  3. Programar Cita (con Asignacion Optima)" << std::endl;
        std::cout << "  4. Ver carga actual de medicos" << std::endl;
        std::cout << "\n  0. Salir" << std::endl;
        std::cout << "\nSelecciona una opcion: ";

        int opcion = leerOpcion();

        switch (opcion) {
            case 1: { // REGISTRAR PACIENTE
                limpiarPantalla();
                std::cout << "--- 1. Registrar Nuevo Paciente ---" << std::endl;
                Paciente nuevoPaciente;
                std::cout << "Ingresa ID (numerico): ";
                nuevoPaciente.idPaciente = leerOpcion();

                std::cout << "Ingresa Nombre: ";
                nuevoPaciente.nombre = leerTexto();

                std::cout << "Ingresa Historial: ";
                nuevoPaciente.historialMedico = leerTexto();

                registro->agregarPaciente(nuevoPaciente);
                std::cout << "\n¡Paciente '" << nuevoPaciente.nombre << "' registrado con exito!" << std::endl;
                esperarUsuario();
                break;
            }
            case 2: { // BUSCAR PACIENTE
                limpiarPantalla();
                std::cout << "--- 2. Buscar Paciente por ID ---" << std::endl;
                std::cout << "Ingresa ID del paciente a buscar: ";
                int idBuscar = leerOpcion();

                auto resultado = registro->buscarPaciente(idBuscar);
                if (resultado) {
                    std::cout << "\nPaciente Encontrado:" << std::endl;
                    std::cout << "  Nombre: " << resultado->nombre << std::endl;
                    std::cout << "  Historial: " << resultado->historialMedico << std::endl;
                } else {
                    std::cout << "\nError: Paciente con ID " << idBuscar << " no encontrado." << std::endl;
                }
                esperarUsuario();
                break;
            }
            case 3: { // PROGRAMAR CITA (FLUJO COMPLETO)
                limpiarPantalla();
                std::cout << "--- 3. Programar Cita (con Asignación Optima) ---" << std::endl;

                // 1. Buscar al paciente
                std::cout << "Ingresa ID del Paciente: ";
                int idPaciente = leerOpcion();
                auto pacienteOpt = registro->buscarPaciente(idPaciente);

                if (!pacienteOpt) {
                    std::cout << "\nError: Paciente con ID " << idPaciente << " no encontrado." << std::endl;
                    esperarUsuario();
                    break;
                }
                auto paciente = *pacienteOpt; // Tenemos el paciente
                std::cout << "  Paciente: " << paciente.nombre << std::endl;

                // 2. Pedir la especialidad
                std::cout << "Ingresa Especialidad (Ej: Cardiologia, Cirugia): ";
                std::string especialidad = leerTexto();

                // 3. Pedir fecha y hora
                std::cout << "Ingresa Fecha y Hora (Ej: 2025-11-05 10:00): ";
                std::string fechaHora = leerTexto();

                // 4. LLAMAR AL ALGORITMO DE ASIGNACIÓN (Backend)
                // El asignador ENCUENTRA al mejor médico (O(m) o O(1))
                auto medicoOpt = asignador->asignarMedico(medicosDisponibles, especialidad);

                if (!medicoOpt) {
                    std::cout << "\nError: No se encontraron médicos para la especialidad '" << especialidad << "'." << std::endl;
                    esperarUsuario();
                    break;
                }
                auto medico = *medicoOpt; // Tenemos al médico óptimo
                std::cout << "  Medico optimo encontrado (por carga): " << medico.nombre << std::endl;

                // 5. LLAMAR AL ALGORITMO DE SCHEDULING (Backend)
                Cita nuevaCita = {proximoIdCita, paciente.idPaciente, medico.idMedico, fechaHora};

                // El scheduler (O(log k)) verifica si hay conflictos
                bool exito = scheduler->programarCita(nuevaCita);

                if (exito) {
                    // 6. ACTUALIZAR EL ESTADO (Confirmar la cita)
                    // Solo si la cita fue exitosa, incrementamos la carga del médico
                    for (auto& med : medicosDisponibles) {
                        if (med.idMedico == medico.idMedico) {
                            med.cargaActual++; // ¡Actualizamos la carga!
                            break;
                        }
                    }
                    proximoIdCita++; // Incrementamos el ID único de cita
                    std::cout << "\n¡Cita programada con exito!" << std::endl;
                    std::cout << "  Paciente: " << paciente.nombre << std::endl;
                    std::cout << "  Medico: " << medico.nombre << std::endl;
                    std::cout << "  Fecha: " << fechaHora << std::endl;
                } else {
                    // El médico estaba ocupado en esa fecha/hora
                    std::cout << "\nError: ¡Conflicto de Horario!" << std::endl;
                    std::cout << "El Dr. " << medico.nombre << " ya tiene una cita a las " << fechaHora << "." << std::endl;
                }
                esperarUsuario();
                break;
            }
            case 4: { // VER CARGA DE MÉDICOS
                limpiarPantalla();
                std::cout << "--- 4. Carga Actual de Medicos ---" << std::endl;
                for (const auto& medico : medicosDisponibles) {
                    std::cout << "  - " << medico.nombre
                              << " (" << medico.especialidad << "): "
                              << medico.cargaActual << " pacientes" << std::endl;
                }
                esperarUsuario();
                break;
            }
            case 0: { // SALIR
                std::cout << "Cerrando el sistema..." << std::endl;
                corriendo = false;
                break;
            }
            default: {
                std::cout << "Opcion no valida. Intentalo de nuevo." << std::endl;
                esperarUsuario();
                break;
            }
        } // fin del switch
    } // fin del while

    return 0;
}