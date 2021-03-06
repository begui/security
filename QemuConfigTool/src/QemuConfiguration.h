#ifndef QEMUCONFIGURATION_H
#define QEMUCONFIGURATION_H

#include <iostream>
#include <stdint.h>
#include <vector>
#include <set>
#include <map>

/**
 * This class holds configuration values relating to QEMU (can load and save them to file as well),
 * and creates the command line command for each instance of QEMU running.
 */
class QemuConfiguration
{
public:
    QemuConfiguration();

    //@{
    /// Loading and saving configuration from file

    bool saveConfiguration(std::string pathname);
    bool loadConfiguration(std::string pathname);

    //@}

    //@{

    /// Setting and retrieving configuration variables

    void setDriveA(std::string filename, bool qcow2Format);
    std::string getDriveA() const;
    bool getDriveAQCow2() const;

    void setDriveB(std::string filename, bool qcow2Format);
    std::string getDriveB() const;
    bool getDriveBQCow2() const;

    void setOpticalDrive(std::string filename);
    std::string getOpticalDrive() const;

    void setProcessorType(std::string processorName);
    static std::set<std::string> getQemuProcessorTypeList();
    std::string getProcessorType() const;

    void setNetworkAdapterType(std::string networkAdapterName);
    static std::set<std::string> getQemuNetworkAdapterTypeList();
    std::string getNetworkAdapterType() const;

    /**
     * Allows someone to configure the human interface on, the port number will be calculated as
     * +1 of the QMP port number
     */
    void enableHumanInterfaceSocket(bool enable);
    bool getHumanInterfaceSocketEnabled() const;

    void enableVncSocket(bool enable);
    bool getVncSocketEnabled();

    void setOtherOptions(std::string otherOptions);
    std::string getOtherOptions() const;

    void setMemorySize(uint16_t numMegabytes);
    static std::set<std::string> getMemorySizes();
    uint16_t getMemorySize() const;

    void setVgaType(std::string vgaType);
    static std::set<std::string> getVgaTypes();
    std::string getVgaType() const;

    void setNumberUserPorts(uint8_t numPorts);
    int getNumberUserPorts();
    int getNumberOfPortsPerInstance() const;

    void setStartingPortNumber(uint16_t portNumber);
    uint16_t getStartingPortNumber() const;

    void setNumberOfCpus(uint8_t numCpus);
    uint8_t getNumberOfCpus() const;

    bool setPortForwardDestination(uint8_t forwardIndex, uint16_t portDestination);
    uint16_t getPortForwardDestination(uint8_t forwardIndex);

    //@}

    /**
     * Returns the command and arg list to run QEMU with the given configuration
     * @param instance The port numbers get shifted to deconflict from other instances of QEMU
     *                 running this configuration based on this instance number
     * @return True if command line was generated successfully
     */
    bool getCommandLine(std::string & commandName,
                        std::vector<std::string> & args,
                        int instance = 0);

    void clearErrorsAndWarnings();
    std::string getErrorMessage() const { return theErrorMessage; }
    std::vector<std::string> getWarnings() const { return theWarningMessages; }

    std::map<std::string, std::string> getProcessEnvironment(int instance = 0);

protected:

    bool buildCpuArgs(std::string & commandName, std::vector<std::string> & args);

    bool buildDriveArgs(std::vector<std::string> & args);

    bool buildNetworkArgs(std::vector<std::string> & args, int id);

    bool buildQmpArgs(std::vector<std::string> & args, int id);

    bool buildVncArgs(std::vector<std::string> & args, int id);

    bool buildMonitorSocketArgs(std::vector<std::string> & args, int id);

    bool buildOtherArgs(std::vector<std::string> & args);

    bool buildMemoryArgs(std::vector<std::string> & args);

    bool buildVgaArgs(std::vector<std::string> & args);

    void parseSingleConfigLine(std::string singleLine,
                               std::map<std::string, std::string> & termsByRef);

    void logMissingConfig(std::string const & missingKey);

    std::string theDriveA;
    bool    theDriveAQcow2;

    std::string theDriveB;
    bool    theDriveBQcow2;

    std::string theOpticalDrive;

    static const std::set<std::string> theDefaultCpuTypes;
    std::string theCpuType;
    uint8_t theNumberCpus;

    static const std::set<std::string> theDefaultNetworkAdapters;
    std::string theNetworkAdapter;

    bool theHumanInterfaceEnabled;
    bool theVncSocketEnabled;

    std::string theOtherOptions;

    uint16_t theMemoryMb;

    static const std::set<std::string> theDefaultVgaTypes;
    std::string theVideoAdapter;

    std::vector<uint16_t> theDestinationPorts;

    uint16_t theStartingPortNumber;

    std::string theErrorMessage;
    std::vector<std::string> theWarningMessages;
};

#endif // QEMUCONFIGURATION_H
