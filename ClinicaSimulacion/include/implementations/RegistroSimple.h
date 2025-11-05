#pragma once
#include "interfaces/IRegistroPacientes.h"
#include <vector>

class RegistroSimple : public IRegistroPacientes {
private:
    std::vector<Paciente> listaPacientes;
public:
    void agregarPaciente(const Paciente& paciente) override;
    std::optional<Paciente> buscarPaciente(int idPaciente) override;
};