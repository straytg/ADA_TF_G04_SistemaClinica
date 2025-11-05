#include "implementations/AsignadorBalanceado.h"
#include <limits>

std::optional<Medico> AsignadorBalanceado::asignarMedico(
    const std::vector<Medico>& medicosDisponibles,
    const std::string& especialidad) const {

    // Algoritmo "Menor Carga por Especialidad" (Greedy)
    // Complejidad: O(m) donde m es el número de médicos.

    int minCarga = std::numeric_limits<int>::max();
    std::optional<Medico> medicoSeleccionado = std::nullopt;

    // 1. Iterar sobre TODOS los médicos
    for (const auto& medico : medicosDisponibles) {

        // 2. FILTRAR: Considerar solo a los de la especialidad correcta
        if (medico.especialidad == especialidad) {

            // 3. COMPARAR: Encontrar el que tenga la menor carga
            if (medico.cargaActual < minCarga) {
                minCarga = medico.cargaActual;
                medicoSeleccionado = medico;
            }
        }
    }

    // Devuelve el médico encontrado (o std::nullopt si nadie de esa esp. existe)
    return medicoSeleccionado;
}