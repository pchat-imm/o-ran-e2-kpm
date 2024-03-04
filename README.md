## task 01/03/2024
- update readme case 1:ue1 with 3 ping windows
- update readme case 2:3 ue (ue1, ue2, ue3) - check log/010324_3ue

## question <br />
- [ ] how to config ue
- [ ] what is gnbradio doing? and what the throttle can be used?

### successful use case
- update readme case 1:ue1 with 3 ping windows
- update readme case 2:3 ue (ue1, ue2, ue3) - check log/010324_3ue

### main tutorial: <br />
- nearRT-RIC and xApp_kpm: https://docs.srsran.com/projects/project/en/latest/tutorials/source/flexric/source/index.html <br />
- multi UE zmq: https://docs.srsran.com/projects/project/en/latest/tutorials/source/srsUE/source/index.html#over-the-air-setup <br />

#### other note before start
- srsRAN_Project is inside czmq/ folder (accidentally install there)
- configs files of gNB, UE, and xApp are in config_files/

#### main component
| component  | source code | note | branch |
| ------------- | ------------- | ------------- | ------------- |
| core network  | open5GS | srsRAN_Project in docker | - |
| gNB  | srsRAN_project | in zmq | main | 
| srsue  | srsRAN_4G  | in zmq |  master |
| nearRT-RIC and xApp | xapp_kpm_moni with nearRT-RIC | flexRIC | br-flexric|

#### different config gNB, UE of nearRT-RIC and multiUE
for multiUE to be able to handle more load, they set symbol rate, channel bandwidth, scs, into two times of original configuration

|component | main | Topic | NearRT-RIC | multiUE |
|----------|------|-------|------------|---------|
|gnb || ru_sdr | srate | 11.52 | 23.04 |
| | cell_cfg | channel_bandwidth_MHz | 10 | 20 |
| |	   | common_scs | 15 | 30 |
| |	   | pdcch: coreset0_index | 6 | 12 |  
| | e2 | enable_du_e2 | true | | 
| |    | e2sm_kpm_enabled | true | |
| |    | addr | 127.0.0.1 | |
| |    | port | 36421 | |
| | metrics | rlc_json_enable | 1 | |
| |	  | rlc_report_period | 1000 | |
|ue| rf | srate | 11.52e6 | 23.04e6 | 
| | rat.nr| max_nof_prb | | 106 |
| |	  | nof_prb | | 106|

the max number of PRB need to be correspond with used bandwidth - BW 20, PRB 106 


### single UE multi-load (1 UE 3 pings windows)

ping command `sudo ip netns exec ue1 ping 10.45.1.1`

log UE
```
~/o-ran-e2-kpm/srsRAN_4G/build/srsue/src$ sudo ./srsue ue_zmq_multiUE.conf 
Active RF plugins: libsrsran_rf_blade.so libsrsran_rf_zmq.so
Inactive RF plugins: 
Reading configuration file ue_zmq_multiUE.conf...

Built in Release mode using commit ec29b0c1f on branch master.

Opening 1 channels in RF device=zmq with args=tx_port=tcp://127.0.0.1:2001,rx_port=tcp://127.0.0.1:2000,base_srate=23.04e6
Supported RF device list: bladeRF zmq file
CHx base_srate=23.04e6
Current sample rate is 1.92 MHz with a base rate of 23.04 MHz (x12 decimation)
CH0 rx_port=tcp://127.0.0.1:2000
CH0 tx_port=tcp://127.0.0.1:2001
Current sample rate is 23.04 MHz with a base rate of 23.04 MHz (x1 decimation)
Current sample rate is 23.04 MHz with a base rate of 23.04 MHz (x1 decimation)
Waiting PHY to initialize ... done!
Attaching UE...
Random Access Transmission: prach_occasion=0, preamble_index=0, ra-rnti=0x39, tti=334
Random Access Complete.     c-rnti=0x4601, ta=0
RRC Connected
PDU Session Establishment successful. IP: 10.45.1.2
RRC NR reconfiguration successful.
```

This is 1 UE (rnti = 4601) but with three different ping windows
log of gNB when have 3 pings windowss
- 1 ping: brate ~ 12k+
- 2 ping: brate ~ 24k+
- 3 ping: brate ~ 36k+
```
           -----------------DL-----------------------|------------------UL--------------------
 pci rnti  cqi  ri  mcs  brate   ok  nok  (%)  dl_bs | pusch  mcs  brate   ok  nok  (%)    bsr
   1 4601   15   1   26   1.8k    2    0   0%      0 |  65.5   28    11k    4    0   0%      0
   1 4601   15   1   26   1.8k    2    0   0%      0 |  65.5   28    12k    5    0   0%      0
   1 4601   15   1   26   1.8k    2    0   0%      0 |  65.5   28    12k    5    0   0%      0
   1 4601   15   1   26   3.7k    4    0   0%      0 |  65.5   28    25k   10    0   0%      0
   1 4601   15   1   26   3.7k    4    0   0%      0 |  65.5   28    25k   10    0   0%      0
   1 4601   15   1   26   3.7k    4    0   0%      0 |  65.5   28    23k    9    0   0%      0
   1 4601   15   1   26   5.5k    6    0   0%      0 |  65.5   28    36k   15    0   0%      0
   1 4601   15   1   26   3.7k    4    0   0%      0 |  65.5   28    24k   10    0   0%      0
   1 4601   15   1   26   5.5k    6    0   0%      0 |  65.5   28    37k   15    0   0%      0
   1 4601   15   1   26   6.9k    7    0   0%      0 |  65.5   28    36k   15    0   0%      0
   1 4601   15   1   26   5.5k    6    0   0%      0 |  65.5   28    36k   15    0   0%      0
```


### multi UE (3 UE)
- there are 3 UE as you can see rnti 4601 (ue1), 4602 (ue2), 4603 (ue3)
- they are simulate + ping in order, therefore rsrp are less strong in consequent UE

> gnb
```
The PRACH detector will not meet the performance requirements with the configuration {Format 0, ZCZ 0, SCS 1.25kHz, Rx ports 1}.
Lower PHY in executor blocking mode.

--== srsRAN gNB (commit 0b2702cca) ==--

Connecting to AMF on 10.53.1.2:38412
Available radio types: zmq.
Cell pci=1, bw=10 MHz, dl_arfcn=368500 (n3), dl_freq=1842.5 MHz, dl_ssb_arfcn=368410, ul_freq=1747.5 MHz

==== gNodeB started ===
pci rnti  cqi  ri  mcs  brate   ok  nok  (%)  dl_bs | pusch  mcs  brate   ok  nok  (%)    bsr
   1 4601   15   1   26   7.3k    8    0   0%      0 |  65.5   28    48k   18    0   0%      0
   1 4602   15   1   27   7.6k    8    0   0%      0 |  65.5   28    47k   18    0   0%      0
   1 4603   15   1   27   3.9k    4    0   0%      0 |  65.5   28    23k    9    0   0%      0
   1 4601   15   1   26   7.3k    8    0   0%      0 |  65.5   28    48k   19    0   0%      0
   1 4602   15   1   27   7.7k    8    0   0%      0 |  65.5   28    47k   16    0   0%      0
   1 4603   15   1   27   7.7k    8    0   0%      0 |  65.5   28    46k   17    0   0%      0
   1 4601   15   1   26   7.3k    8    0   0%      0 |  65.5   28    47k   19    0   0%      0
   1 4602   15   1   27   7.6k    8    0   0%      0 |  65.5   28    46k   16    0   0%      0
   1 4603   15   1   27   7.7k    8    0   0%      0 |  65.5   28    47k   18    0   0%      0
   1 4601   15   1   26   7.3k    8    0   0%      0 |  65.5   28    47k   19    0   0%      0
```

#### ue1
- Opening 1 channels in RF device=zmq with args=tx_port=tcp://127.0.0.1:2101,rx_port=tcp://127.0.0.1:2100,base_srate=11.52e6
    - CH0 rx_port=tcp://127.0.0.1:2100
    - CH0 tx_port=tcp://127.0.0.1:2101
- Random Access Complete.     c-rnti=0x4601, ta=0
- PDU Session Establishment successful. IP: 10.45.1.2
```
>> sudo ./srsue ./ue1_zmq.conf 
Active RF plugins: libsrsran_rf_blade.so libsrsran_rf_zmq.so
Inactive RF plugins: 
Reading configuration file ./ue1_zmq.conf...

Built in Release mode using commit ec29b0c1f on branch master.

Opening 1 channels in RF device=zmq with args=tx_port=tcp://127.0.0.1:2101,rx_port=tcp://127.0.0.1:2100,base_srate=11.52e6
Supported RF device list: bladeRF zmq file
CHx base_srate=11.52e6
Current sample rate is 1.92 MHz with a base rate of 11.52 MHz (x6 decimation)
CH0 rx_port=tcp://127.0.0.1:2100
CH0 tx_port=tcp://127.0.0.1:2101
Current sample rate is 11.52 MHz with a base rate of 11.52 MHz (x1 decimation)
Current sample rate is 11.52 MHz with a base rate of 11.52 MHz (x1 decimation)
Waiting PHY to initialize ... done!
Attaching UE...
Random Access Transmission: prach_occasion=0, preamble_index=7, ra-rnti=0x39, tti=174
Random Access Complete.     c-rnti=0x4601, ta=0
RRC Connected
PDU Session Establishment successful. IP: 10.45.1.2
RRC NR reconfiguration successful.
---------Signal-----------|-----------------DL-----------------|-----------UL-----------
rat  pci  rsrp   pl   cfo | mcs  snr  iter  brate  bler  ta_us | mcs   buff  brate  bler
 nr    1    41    0  -11u |  26   66   1.0   7.3k    0%    0.0 |  28    0.0    47k    0%
 nr    1    41    0  -16u |  26   66   1.0   7.3k    0%    0.0 |  28    0.0    47k    0%
 nr    1    41    0  -14u |  26   66   1.0   7.3k    0%    0.0 |  28    0.0    49k    0%
 nr    1    41    0  -18u |  26   66   1.0   7.4k    0%    0.0 |  28    0.0    47k    0%
 nr    1    41    0 -7.1u |  26   66   1.0   7.3k    0%    0.0 |  28    0.0    50k    0%
 nr    1    41    0  -16u |  26   66   1.0   7.3k    0%    0.0 |  28    0.0    50k    0%
 nr    1    41    0  -20u |  26   65   1.0   7.3k    0%    0.0 |  28    0.0    44k    0%
 nr    1    41    0 -7.1u |  26   66   1.0   7.3k    0%    0.0 |  28    0.0    47k    0%
 nr    1    41    0  -13u |  26   66   1.0   7.3k    0%    0.0 |  28    0.0    44k    0%
 nr    1    41    0  -15u |  26   66   1.0   7.3k    0%    0.0 |  28    0.0    50k    0%
 nr    1    41    0  -18u |  26   66   1.0   7.3k    0%    0.0 |  28    0.0    50k    0%
```

#### ue2
- Opening 1 channels in RF device=zmq with args=tx_port=tcp://127.0.0.1:2201,rx_port=tcp://127.0.0.1:2200,base_srate=11.52e6
    - CH0 rx_port=tcp://127.0.0.1:2200
    - CH0 tx_port=tcp://127.0.0.1:2201
- Random Access Complete.     c-rnti=0x4602, ta=0
- PDU Session Establishment successful. IP: 10.45.1.4
```
---------Signal-----------|-----------------DL-----------------|-----------UL-----------
rat  pci  rsrp   pl   cfo | mcs  snr  iter  brate  bler  ta_us | mcs   buff  brate  bler
 nr    1    31    0  -12u |  26   64   1.0   7.6k    0%    0.0 |  28    0.0    47k    0%
 nr    1    32    0  -12u |  26  n/a   1.0   7.6k    0%    0.0 |  28    0.0    47k    0%
 nr    1    31    0  -14u |  27   65   1.0   7.7k    0%    0.0 |  28    0.0    46k    0%
 nr    1    32    0  -14u |  26  n/a   1.0   7.7k    0%    0.0 |  28    0.0    47k    0%
 ```

 #### ue3
 - Opening 1 channels in RF device=zmq with args=tx_port=tcp://127.0.0.1:2301,rx_port=tcp://127.0.0.1:2300,base_srate=11.52e6
    - CH0 rx_port=tcp://127.0.0.1:2300
    - CH0 tx_port=tcp://127.0.0.1:2301
- Random Access Complete.     c-rnti=0x4603, ta=0
- PDU Session Establishment successful. IP: 10.45.1.5
```
---------Signal-----------|-----------------DL-----------------|-----------UL-----------
rat  pci  rsrp   pl   cfo | mcs  snr  iter  brate  bler  ta_us | mcs   buff  brate  bler
 nr    1    22    0 -5.3u |  27   80   1.0   7.7k    0%    0.0 |  28    0.0    47k    0%
 nr    1    22    0   22n |  26   81   1.0   7.6k    0%    0.0 |  28    0.0    32k    0%
 nr    1    22    0  7.4u |  26   80   1.0   7.5k    0%    0.0 |  28    0.0    35k    0%
 nr    1    22    0  5.5u |  27   81   1.0   7.9k    0%    0.0 |  28    0.0    51k    0%
 ```s