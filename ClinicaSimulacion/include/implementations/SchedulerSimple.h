#pragma once
#include "interfaces/ISchedulerCitas.h"
#include <vector>

class SchedulerSimple : public ISchedulerCitas {
private:
    std::vector<Cita> todasLasCitas;
public:
    bool programarCita(const Cita& nuevaCita) override;
    std::vector<Cita> getCitasDelMedico(int idMedico) override;
};