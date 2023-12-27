#ifndef ALGHORITMS_H
#define ALGHORITMS_H

#include "gpu.h"
#include "cpu.h"
#include "motherboard.h"
#include "ram.h"
#include "rom.h"
#include "case.h"
#include "power_unit.h"
#include "cooler.h"

Component::Type getTypeByFilter(QString selectedFilter);
int getAmountOfEachTypeList(QList<Component::Component*> list);
QString getTextType(Component::Type type);
QList<Component::Component*> sortByTypeComponentList(QList<Component::Component*> listToSort, Component::Type type);
Component::Component* findComponentByIndvNumber(QList<Component::Component*> list, int articul);
Component::Component* getObjectByType(Component::Component* component);
void sortByFunctionComponentList(QList<Component::Component*> &listToSort, bool (*func)(Component::Component* a, Component::Component* b));
void getSortParameters(Component::Type type, QString* parameter1, QString* parameter2, QString* parameter3, QString* parameter4);
int getAmountIndexByType(Component::Type type);
QString getHolderByType(Component::Type type);
void sortByType(QList<Component::Component*>& result, Component::Type type, QRadioButton& sortByAmountLowCheckBox, QRadioButton& sortByAmountHighCheckBox, QRadioButton& sortByPriceMinCheckBox, QRadioButton& sortByPriceMaxCheckBox, QRadioButton& sortByParameter1, QRadioButton& sortByParameter2, QRadioButton& sortByParameter3, QRadioButton& sortByParameter4);
bool compareAmountHigh(Component::Component* a, Component::Component* b);
bool compareAmountLow(Component::Component* a, Component::Component* b);
bool compareCostHigh(Component::Component* a, Component::Component* b);
bool compareCostLow(Component::Component* a, Component::Component* b);
bool compareGpuMemory(Component::Component* a, Component::Component* b);
bool compareGpuMemoryType(Component::Component* a, Component::Component* b);
bool compareGpuFrequency(Component::Component* a, Component::Component* b);
bool compareGpuTireType(Component::Component* a, Component::Component* b);
bool compareCpuCores(Component::Component* a, Component::Component* b);
bool compareCpuStreams(Component::Component* a, Component::Component* b);
bool compareCpuSocket(Component::Component* a, Component::Component* b);
bool compareCpuChipset(Component::Component* a, Component::Component* b);
bool compareMotherboardSocket(Component::Component* a, Component::Component* b);
bool compareMotherboardChipset(Component::Component* a, Component::Component* b);
bool compareMotherboardMemoryType(Component::Component* a, Component::Component* b);
bool compareMotherboardFormfactor(Component::Component* a, Component::Component* b);
bool compareRamAmount(Component::Component* a, Component::Component* b);
bool compareRamFrequency(Component::Component* a, Component::Component* b);
bool compareRamType(Component::Component* a, Component::Component* b);
bool compareRamSlats(Component::Component* a, Component::Component* b);
bool comparePowerunitPower(Component::Component* a, Component::Component* b);
bool comparePowerunitPins(Component::Component* a, Component::Component* b);
bool comparePowerunitFormfactor(Component::Component* a, Component::Component* b);
bool comparePowerunitSertificate(Component::Component* a, Component::Component* b);
bool compareRomType(Component::Component* a, Component::Component* b);
bool compareRomAmount(Component::Component* a, Component::Component* b);
bool compareRomSpeed(Component::Component* a, Component::Component* b);
bool compareRomSlot(Component::Component* a, Component::Component* b);
bool compareCaseColor(Component::Component* a, Component::Component* b);
bool compareCaseMaterial(Component::Component* a, Component::Component* b);
bool compareCaseWindow(Component::Component* a, Component::Component* b);
bool compareCaseFormfactor(Component::Component* a, Component::Component* b);
bool compareCoolerSockets(Component::Component* a, Component::Component* b);
bool compareCoolerType(Component::Component* a, Component::Component* b);
bool compareCoolerFormfactor(Component::Component* a, Component::Component* b);
bool compareCoolerPower(Component::Component* a, Component::Component* b);

#endif // ALGHORITMS_H
