# o-ran-e2-kpm

1. [] do the slicing (sst = 1, sd = 1)
	- gnb 
	- ue [slicing] nssai-sst=1, nssai-sd=1
2. [] install open5gs from source to be able to config amf and upf https://open5gs.org/open5gs/docs/guide/02-building-open5gs-from-sources/
without 'ninja install'


**follow this**: https://github.com/s5uishida/open5gs_5gc_srsran_sample_config/tree/main \
**requirement**
1. change open5gs
2. change upf
3. change gnb
4. change ue

#### read more: wiki of this repository

try O-RAN 5G E2 interface to test e2sm kpm <br />

| component  | source code | note | branch |
| ------------- | ------------- | ------------- | ------------- |
| core network  | open5GS | srsRAN_Project in docker | - |
| gNB  | srsRAN_project | in zmq | main | 
| srsue  | srsRAN_4G  | in zmq |  master |
| nearRT-RIC and xApp | xapp_kpm_moni with nearRT-RIC (only this xapp that is work, other not work)| flexRIC | e2ap-v2|
