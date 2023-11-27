# o-ran-e2-kpm
## branch: slicing

**purpose of this branch**: try to add sst and sd successfully \
**current change 211123**
1. srsue from srsRAN_4G/build/srsue/src
```
Random Access Complete.     c-rnti=0x4601, ta=0
RRC Connected
Failed to setup/configure GW interface
RRC NR reconfiguration successful.
```
- but already try make czmq again and install srsRAN_4G again

2. try run the system again
- [X] open5gs docker of srsRAN_Project
- [X] near-RT RIC
- gNB
- ue

next task: install open5gs from source to be able to config amf and upf https://open5gs.org/open5gs/docs/guide/02-building-open5gs-from-sources/
without 'ninja install'


**follow this**: https://github.com/s5uishida/open5gs_5gc_srsran_sample_config/tree/main \
**requirement**
1. change open5gs
2. change upf
3. change gnb
4. change ue

___
#### read more: wiki of this repository

try O-RAN 5G E2 interface to test e2sm kpm <br />

| component  | source code | note | branch |
| ------------- | ------------- | ------------- | ------------- |
| core network  | open5GS | srsRAN_Project in docker | - |
| gNB  | srsRAN_project | in zmq | main | 
| srsue  | srsRAN_4G  | in zmq |  master |
| nearRT-RIC and xApp | xapp_kpm_moni with nearRT-RIC (only this xapp that is work, other not work)| flexRIC | e2ap-v2|
