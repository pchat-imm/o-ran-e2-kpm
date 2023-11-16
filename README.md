# o-ran-e2-kpm

### date 161123
**branch in focus:** 
1. slicing (to have slicing with sst and sd = 1)
2. cfg_gnb (to config gnb to have different mcs)

____
#### read more: wiki of this repository

try O-RAN 5G E2 interface to test e2sm kpm <br />

| component  | source code | note | branch |
| ------------- | ------------- | ------------- | ------------- |
| core network  | open5GS | srsRAN_Project in docker | - |
| gNB  | srsRAN_project | in zmq | main | 
| srsue  | srsRAN_4G  | in zmq |  master |
| nearRT-RIC and xApp | xapp_kpm_moni with nearRT-RIC (only this xapp that is work, other not work)| flexRIC | e2ap-v2|
