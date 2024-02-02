## question <br />
- [ ] how to config ue and gnb
- [ ] why it is multi ue? currently only 1 ue with 3 individual ping window


### main tutorial: <br />
- nearRT-RIC and xApp_kpm: https://docs.srsran.com/projects/project/en/latest/tutorials/source/flexric/source/index.html <br />
- multi UE zmq: https://docs.srsran.com/projects/project/en/latest/tutorials/source/srsUE/source/index.html#over-the-air-setup <br />

#### other note before start
- srsRAN_Project is inside czmq/ folder (accidentally install there)
- configs files of gNB, UE, and xApp are in config_files/

#### different config gNB, UE of nearRT-RIC and multiUE
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


### multi_UE

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

log of gNB when have 3 pings windows
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




