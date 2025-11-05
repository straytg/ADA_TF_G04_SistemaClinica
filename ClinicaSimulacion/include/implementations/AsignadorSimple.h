#pragma once
#include "interfaces/IAsignadorPersonal.h"

class AsignadorSimple : public IAsignadorPersonal {
public:
    // La firma debe coincidir con la de la interfaz (incluyendo los 'const')
    std::optional<Medico> asignarMedico(
        const std::vector<Medico>& medicosDisponibles,
        const std::string& especialidad) const override;
};