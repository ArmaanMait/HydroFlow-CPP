# HydroFlow-CPP
Smart Urban Water Distribution &amp; Automated Leakage/Contamination Isolation System in C++ (SDG 6)

## Key Features & OOP Architecture
- **Polymorphic Node Hierarchy:** Abstract base class `WaterNode` with specialized derived classes (`ReservoirNode`, `TreatmentPlantNode`, and `CommunityNode`).
- **Graph-Based Pipeline Mapping:** Uses `std::map` and `std::vector` with smart pointers (`std::unique_ptr`) to manage network nodes and bi-directional pipeline telemetry.
- **Automated Failsafe Isolation:** Continuously monitors node pressure and automatically triggers valve shutdowns when critical pressure collapse (< 20 PSI) is detected.
- **Persistent Audit Logging:** Exports diagnostic and water-saving metrics to `water_network_audit_report.txt` via C++ file streams (`std::ofstream`).

## How to Compile & Run
```bash
g++ -std=c++17 main.cpp -o hydroflow
./hydroflow


================ CURRENT WATER NETWORK NODES ================
[Reservoir] ID: 1 | Lake View Reservoir | Vol: 850000/1000000 L | Pressure: 60 PSI | Status: Optimal
[Treatment] ID: 2 | Apex Filtration Plant | Efficiency: 99.8% | Pressure: 55 PSI | Status: Purifying
[Community] ID: 3 | North Sector Hub | Homes: 150 | Pressure: 40 PSI | Status: Normal

>> [CRITICAL ALERT] Pipe burst detected between Node 2 and Node 3. Pressure collapsed to 12.5 PSI.
>> Initiating Automated Emergency Protocol...
>> [ACTION TAKEN] Valve on pipeline 2 SHUT DOWN automatically. Water wastage arrested.
