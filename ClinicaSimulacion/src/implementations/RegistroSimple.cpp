#include "implementations/RegistroSimple.h"

void RegistroSimple::agregarPaciente(const Paciente& paciente) {
    // O(1) en promedio
    listaPacientes.push_back(paciente);
}

std::optional<Paciente> RegistroSimple::buscarPaciente(int idPaciente) {
    // Búsqueda Lineal: O(n)
    for (const auto& p : listaPacientes) {
        if (p.idPaciente == idPaciente) {
            return p;
        }
    }
    return std::nullopt; // No se encontró
}