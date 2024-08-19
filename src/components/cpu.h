#ifndef CPU_H
#define CPU_H

#include "component.h"

namespace Component
{
    class Cpu final : public Component
    {
    public:
        enum IntegratedGpu : uint8_t
        {
            Unknown = 0,
            Absent,
            Present,
        };

        enum CpuSettings : uint8_t
        {
            Cores = 3,
            Steams,
            Socket,
            Architecture,
            IntegrategGpu,
            Cost,
            Amount,
        };

        Cpu() noexcept = default;
        Cpu(const Cpu&) noexcept = default;
        Cpu(const int article, const QString& name, const int cost, const ComponentType type,
            const int amount, const int cores, const int streams, const QString& socket,
            const QString& architecture, const IntegratedGpu integratedGpu) noexcept :
            Component(article, name, cost, type, amount)
        {
            this->cores = cores;
            this->streams = streams;
            this->integratedGpu = integratedGpu;

            this->socket = socket;
            this->architecture = architecture;
        }

        ~Cpu() override = default;

        [[nodiscard]] inline int GetCores() const noexcept { return cores; }
        [[nodiscard]] inline int GetStreams() const noexcept { return streams; }
        [[nodiscard]] inline IntegratedGpu GetIntegratedGpu() const noexcept { return integratedGpu; }
        [[nodiscard]] inline const QString& GetSocket() const noexcept { return socket; }
        [[nodiscard]] inline const QString& GetArchitecture() const noexcept { return architecture; }

    private:
        int cores = 0;
        int streams = 0;
        IntegratedGpu integratedGpu;
        QString socket;
        QString architecture;
    };
}

#endif // CPU_H
