#pragma once
#include "models/Medico.h"
#include "models/Paciente.h"
#include <vector>
#include <optional>
#include <string>

// Interfaz para el Objetivo Específico 3
class IAsignadorPersonal {
public:
    // La función ahora es 'const' (no modifica el estado del asignador)
    // y toma la lista de médicos como 'const' (no la modifica).
    // Devuelve el MEJOR médico, pero no altera la lista.
    virtual std::optional<Medico> asignarMedico(
        const std::vector<Medico>& medicosDisponibles,
        const std::string& especialidad) const = 0; // Se añade 'const' y 'especialidad'

    virtual ~IAsignadorPersonal() = default;
};