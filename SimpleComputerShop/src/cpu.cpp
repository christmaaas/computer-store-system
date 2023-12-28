#include "cpu.h"

namespace Component
{
    Cpu::Cpu() : Component()
    {
        cores = 0;
        streams = 0;

        integratedGpu = CPU::UNKNOWN;

        socket = nullptr;
        architecture = nullptr;
    }
    Cpu::Cpu(const Cpu& component) : Component(component)
    {
        cores = component.cores;
        streams = component.streams;
        integratedGpu = component.integratedGpu;
        socket = component.socket;
        architecture = component.architecture;
    }
    Cpu::Cpu(int articul, QString name, int cost, Type type, int amount, int cores, int streams, QString socket, QString architecture, CPU::IntegratedGpu integratedGpu) : Component(articul, name, cost, type, amount)
    {
        this->cores = cores;
        this->streams = streams;
        this->integratedGpu = integratedGpu;

        this->socket = socket;
        this->architecture = architecture;
    }
    int Cpu::GetCores() const
    {
        return cores;
    }
    int Cpu::GetStreams() const
    {
        return streams;
    }
    CPU::IntegratedGpu Cpu::GetIntegratedGpu() const
    {
        return integratedGpu;
    }
    QString Cpu::GetSocket() const
    {
        return socket;
    }
    QString Cpu::GetArchitecture() const
    {
        return architecture;
    }
}

