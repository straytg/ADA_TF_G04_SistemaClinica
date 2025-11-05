#include "implementations/SchedulerOptimizado.h"

bool SchedulerOptimizado::programarCita(const Cita& nuevaCita) {
    // 1. Encontrar el "libro" del médico: O(1)
    auto& horariosOcupados = citasPorMedico[nuevaCita.idMedico];

    // 2. Buscar si la hora ya existe en el árbol (set)
    // Complejidad: O(log k), donde k = citas de ESE médico
    if (horariosOcupados.count(nuevaCita.fechaHora)) {
        return false; // Conflicto
    }

    // 3. Insertar la nueva hora: O(log k)
    horariosOcupados.insert(nuevaCita.fechaHora);
    listaCitas.push_back(nuevaCita); // (Almacenamiento auxiliar)
    return true;
}

std::vector<Cita> SchedulerOptimizado::getCitasDelMedico(int idMedico) {
    // Esta parte sigue siendo O(n) en esta implementación simple
    std::vector<Cita> citasMedico;
    for (const auto& cita : listaCitas) {
        if (cita.idMedico == idMedico) {
            citasMedico.push_back(cita);
        }
    }
    return citasMedico;
}