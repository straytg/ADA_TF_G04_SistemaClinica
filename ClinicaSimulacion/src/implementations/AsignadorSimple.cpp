#include "implementations/AsignadorSimple.h"

std::optional<Medico> AsignadorSimple::asignarMedico(
    const std::vector<Medico>& medicosDisponibles,
    const std::string& especialidad) const {

    // Algoritmo "Simple": Devuelve el PRIMER médico que encuentre
    // que coincida con la especialidad.
    // Complejidad: O(m) donde m es el número de médicos.
    for (const auto& medico : medicosDisponibles) {
        if (medico.especialidad == especialidad) {
            return medico; // Devuelve una copia del médico encontrado
        }
    }

    // Si no se encuentra ningún médico para esa especialidad
    return std::nullopt;
}