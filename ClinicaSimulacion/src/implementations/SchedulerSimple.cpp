#include "implementations/SchedulerSimple.h"
#include <algorithm>

bool SchedulerSimple::programarCita(const Cita& nuevaCita) {
    // Búsqueda lineal de conflictos: O(n)
    // n = número total de citas en la clínica
    for (const auto& citaExistente : todasLasCitas) {
        if (citaExistente.idMedico == nuevaCita.idMedico &&
            citaExistente.fechaHora == nuevaCita.fechaHora) {
            return false; // Conflicto
            }
    }
    todasLasCitas.push_back(nuevaCita);
    return true;
}

std::vector<Cita> SchedulerSimple::getCitasDelMedico(int idMedico) {
    std::vector<Cita> citasMedico;
    // O(n)
    for (const auto& cita : todasLasCitas) {
        if (cita.idMedico == idMedico) {
            citasMedico.push_back(cita);
        }
    }
    return citasMedico;
}