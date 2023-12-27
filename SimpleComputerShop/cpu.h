#ifndef CPU_H
#define CPU_H

#include "component.h"

#define CPU_FILE "./holders/cpu.txt"

#define CPU_CORES 3
#define CPU_STREAMS 4
#define CPU_SOCKET 5
#define CPU_ARCHITECTURE 6
#define CPU_INTEGRATED_GPU 7
#define CPU_COST 8
#define CPU_AMOUNT 9

namespace CPU
{
    enum IntegratedGpu
    {
        ABSENT = 0,
        PRESENT,
        UNKNOWN
    };
}

namespace Component
{
    class Cpu : public Component
    {
    private:
        int cores;
        int streams;

        CPU::IntegratedGpu integratedGpu;

        QString socket;
        QString architecture;

    public:
        Cpu();
        Cpu(const Cpu&);
        Cpu(int articul, QString name, int cost, Type type, int amount, int cores, int streams, QString socket, QString architecture, CPU::IntegratedGpu integratedGpu);

        ~Cpu() {};

        int GetCores() const;
        int GetStreams() const;
        CPU::IntegratedGpu GetIntegratedGpu() const;
        QString GetSocket() const;
        QString GetArchitecture() const;
    };
}

#endif // CPU_H
