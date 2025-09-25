# Wireless Message Dissector

## Overview

### Message Types

This component of the system should be able to decode the following message types, as specified by 3GPP:

- DCI UL
- DCI DL
- PDSCH
- PUSCH
- SIB1
- MIB

### Order of Decoding

These messages are contained in unique areas of the channel, and they are dependent. The following is the order of decoding to get all of them

1. **MIB:** Transmitted in the SSB, this block contains data on the CORESET configuration, which allows us to scan for DCI messages
2. **DL DCI:** These messages contain information on all other channels, as well as uplink scheduling.
3. **UL DCI:** Using the configuration of DL DCI we can find UCI.
4. **SIB1:** This block contains information about the entire channel. It can be found in the PDSCH using information from the DL DCI messages.
5. **All other messages:** Once the SIB1 is decoded, any unencryped messages can be intercepted

## Implementation

### Code References

I found a fascinating implementation of this in the following repository: [https://github.com/asset-group/Sni5Gect-5GNR-sniffing-and-exploitation](https://github.com/asset-group/Sni5Gect-5GNR-sniffing-and-exploitation)

Please do read the srsRAN code as well, since it will form the backbone of this sniffer.

### Project Structure

The project structure will be similar to other projects like pdcch-agent, where srsRAN code is included as a library and compiled as a CMake subproject. For the most part the CMakeLists.txt can be copied from other repositories.

### Configuration

Our configuration will be YAML based, because it is recursive and easy to use. The package is `yaml-cpp`

## Deliverables

### Results

The sniffer should provide detailed logs of intercepted messages and their contents. The same information should be sent to influxdb in an orderly fashion.

### Integration

This project should ideally be containerized in alpine, but ubuntu is fine if necessary. Once containerized it should be integrated into the RAN tester UE.
