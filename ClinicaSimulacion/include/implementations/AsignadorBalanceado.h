#pragma once
#include "interfaces/IAsignadorPersonal.h"

class AsignadorBalanceado : public IAsignadorPersonal {
public:
    // La firma debe coincidir con la de la interfaz
    std::optional<Medico> asignarMedico(
        const std::vector<Medico>& medicosDisponibles,
        const std::string& especialidad) const override;
};