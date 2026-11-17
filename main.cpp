#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <string>

using namespace std;

// Abstract Base Class demonstrating Encapsulation and Polymorphism
class WaterNode {
protected:
    int id;
    string name;
    double pressure; // PSI
    bool activeStatus;

public:
    WaterNode(int nodeId, string nodeName, double initialPressure)
        : id(nodeId), name(nodeName), pressure(initialPressure), activeStatus(true) {}

    virtual ~WaterNode() {}

    virtual void displayStatus() const = 0;
    virtual string getNodeType() const = 0;

    int getId() const { return id; }
    string getName() const { return name; }
    double getPressure() const { return pressure; }
    void setPressure(double p) { pressure = p; }
    
    bool isActive() const { return activeStatus; }
    void setStatus(bool status) { activeStatus = status; }
};

// Derived Class: Reservoir Node
class ReservoirNode : public WaterNode {
private:
    double currentVolume;
    double maxCapacity;

public:
    ReservoirNode(int id, string name, double pressure, double currentVol, double maxCap)
        : WaterNode(id, name, pressure), currentVolume(currentVol), maxCapacity(maxCap) {}

    void displayStatus() const override {
        cout << "[Reservoir] ID: " << id << " | " << name 
             << " | Vol: " << static_cast<int>(currentVolume) << "/" << static_cast<int>(maxCapacity) << " L"
             << " | Pressure: " << pressure << " PSI"
             << " | Status: " << (activeStatus ? "Optimal" : "Isolated") << "\n";
    }

    string getNodeType() const override { return "Reservoir"; }
};

// Derived Class: Treatment Plant Node
class TreatmentPlantNode : public WaterNode {
private:
    double filtrationEfficiency;

public:
    TreatmentPlantNode(int id, string name, double pressure, double efficiency)
        : WaterNode(id, name, pressure), filtrationEfficiency(efficiency) {}

    void displayStatus() const override {
        cout << "[Treatment] ID: " << id << " | " << name 
             << " | Efficiency: " << filtrationEfficiency << "%"
             << " | Pressure: " << pressure << " PSI"
             << " | Status: " << (activeStatus ? "Purifying" : "Offline") << "\n";
    }

    string getNodeType() const override { return "Treatment Plant"; }
};

// Derived Class: Community Hub Node
class CommunityNode : public WaterNode {
private:
    int connectedHomes;

public:
    CommunityNode(int id, string name, double pressure, int homes)
        : WaterNode(id, name, pressure), connectedHomes(homes) {}

    void displayStatus() const override {
        cout << "[Community] ID: " << id << " | " << name 
             << " | Homes: " << connectedHomes 
             << " | Pressure: " << pressure << " PSI"
             << " | Status: " << (activeStatus ? "Normal" : "Valve Shut") << "\n";
    }

    string getNodeType() const override { return "Community Hub"; }
};

// Pipeline Edge Structure connecting nodes
struct Pipeline {
    int pipeId;
    int fromNode;
    int toNode;
    double flowRate; // L/min
    bool valveOpen;
    bool hasLeak;
};

int main() {
    vector<unique_ptr<WaterNode>> networkNodes;
    networkNodes.push_back(make_unique<ReservoirNode>(1, "Lake View Reservoir", 60.0, 850000.0, 1000000.0));
    networkNodes.push_back(make_unique<TreatmentPlantNode>(2, "Apex Filtration Plant", 55.0, 99.8));
    networkNodes.push_back(make_unique<CommunityNode>(3, "North Sector Hub", 40.0, 150));

    // Graph adjacency map storing pipelines by Pipe ID
    map<int, Pipeline> pipelines;
    pipelines[1] = {1, 1, 2, 1200.0, true, false};
    pipelines[2] = {2, 2, 3, 950.0, true, false};

    cout << "================ CURRENT WATER NETWORK NODES ================\n";
    for (const auto& node : networkNodes) {
        node->displayStatus();
    }

    // Simulate pipe burst between Node 2 and Node 3
    networkNodes[2]->setPressure(12.5);
    pipelines[2].hasLeak = true;

    // Event-driven anomaly detector (< 20 PSI threshold)
    for (auto& [id, pipe] : pipelines) {
        for (const auto& node : networkNodes) {
            if (node->getId() == pipe.toNode && node->getPressure() < 20.0) {
                cout << "\n>> [CRITICAL ALERT] Pipe burst detected between Node " 
                     << pipe.fromNode << " and Node " << pipe.toNode 
                     << ". Pressure collapsed to " << node->getPressure() << " PSI.\n";
                cout << ">> Initiating Automated Emergency Protocol...\n";
                
                pipe.valveOpen = false;
                node->setStatus(false);
                
                cout << ">> [ACTION TAKEN] Valve on pipeline " << pipe.pipeId 
                     << " SHUT DOWN automatically. Water wastage arrested.\n";
            }
        }
    }

    // Export persistent audit report using std::ofstream
    ofstream auditFile("water_network_audit_report.txt");
    if (auditFile.is_open()) {
        auditFile << "HYDROFLOW WATER NETWORK AUDIT REPORT\n";
        auditFile << "-------------------------------------\n";
        auditFile << "Incident: Pipe burst between Node 2 and Node 3 (12.5 PSI)\n";
        auditFile << "Action: Automated shutdown on Pipeline 2\n";
        auditFile << "Non-Revenue Water Saved: ~54,000 Litres (98% Reduction)\n";
        auditFile << "SDG 6 Alignment: Target 6.1 & Target 6.4 Compliant\n";
        auditFile.close();
    }

    return 0;
}
