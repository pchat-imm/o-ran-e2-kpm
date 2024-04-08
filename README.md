# o-ran-e2-kpm

## Diagram
![overview_hw_sw_ip_port(1)](https://github.com/pchat-imm/o-ran-e2-kpm/assets/40858099/71e6f5ca-ef8f-4fbd-9f8f-828cb9a1a94a)

## Main tutorials: <br />
downloaded document from srsRAN (040324) - follow this one
- /document_srsRAN/zeroMQ_and_multiUE.pdf <br />

from srsRAN
- nearRT-RIC and xApp_kpm: https://docs.srsran.com/projects/project/en/latest/tutorials/source/flexric/source/index.html <br />
- multi UE zmq: https://docs.srsran.com/projects/project/en/latest/tutorials/source/srsUE/source/index.html#over-the-air-setup <br />

## Main component
| component  | source code | note | branch |
| ------------- | ------------- | ------------- | ------------- |
| core network  | open5GS | srsRAN_Project in docker | - |
| gNB  | srsRAN_project | in zmq | main | 
| srsue  | srsRAN_4G  | in zmq |  master |
| nearRT-RIC and xApp | xapp_kpm_moni with nearRT-RIC | flexRIC | br-flexric|

## Installation
- PC with Ubuntu 22.04.1 LTS
- [srsRAN UE](https://github.com/srsran/srsRAN_4G) (srsRAN 4G 23.04 or later)
- [ZeroMQ](https://zeromq.org/)
- [FlexRIC](https://gitlab.eurecom.fr/mosaic5g/flexric)
- [Open5GS 5G Core](https://open5gs.org/)
- Wireshark (Version 4.0.7 or later)

## task 05/04/23
- understand multiUE and gNU Emulator 

