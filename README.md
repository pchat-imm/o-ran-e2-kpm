## task 05/04/23
- understand multiUE and gNU Emulator \


## task 01/03/2024
- update solution of wrong routing table (cannot ping downlink, cannot iperf)
the `sudo ip ro add 10.45.0.0/16 via 10.53.1.2` return `file exist` and it is
```
>> route -n
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
0.0.0.0         192.168.10.1    0.0.0.0         UG    600    0        0 wlp9s0
10.45.0.0       0.0.0.0         255.255.0.0     U     0      0        0 ogstun
10.53.1.0       0.0.0.0         255.255.255.0   U     0      0        0 br-2d2baf4f3a8c
169.254.0.0     0.0.0.0         255.255.0.0     U     1000   0        0 wlp9s0
172.17.0.0      0.0.0.0         255.255.0.0     U     0      0        0 docker0
172.19.1.0      0.0.0.0         255.255.255.0   U     0      0        0 br-36c6988d1fa9
192.168.10.0    0.0.0.0         255.255.255.0   U     600    0        0 wlp9s0
```
compared to what we want, we lack this line
```
10.45.0.0       10.53.1.2       255.255.0.0     UG    0      0        0 br-dfa5521eb807
```
fix by following the answer on srsRAN_project discussion, stop and restart open5gs service, then 
```
sudo ifconfig ogstun 0.0.0.0 down
```
- update readme case 1:ue1 with 3 ping windows
- update readme case 2:3 ue (ue1, ue2, ue3) - check log/010324_3ue
- merge multiUE to main? - is it possible, which files you need to keep
    - read me of multiUE -> move to new page of wiki
    - wiki (of nearRT-RIC)
    - check config files, is it corrected?
    - document srsRAN
    - task

## diagram
![overview_hw_sw_ip_port(1)](https://github.com/pchat-imm/o-ran-e2-kpm/assets/40858099/71e6f5ca-ef8f-4fbd-9f8f-828cb9a1a94a)

## question <br />
- [ ] how to config ue
- [ ] what is gnbradio doing? and what the throttle can be used?

### successful use case
- update readme case 1:ue1 with 3 ping windows
- update readme case 2:3 ue (ue1, ue2, ue3) - check log/010324_3ue

### main tutorial: <br />
downloaded document from srsRAN (040324) - follow this one
- /document_srsRAN/zeroMQ_and_multiUE.pdf 

from srsRAN
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

## To run the system
## 1. single UE muli load
### 1.1 configuration
#### gnb
gnb config files \
- made the symbol rate higher (from 11.52e6 to 23.04e6) \
```
ru_sdr:
  device_driver: zmq
  device_args: tx_port=tcp://127.0.0.1:2000,rx_port=tcp://127.0.0.1:2001,base_srate=23.04e6
  srate: 23.04
  tx_gain: 75
  rx_gain: 75
```

#### srsUE
netns (network namespace), exec (executive)
```
# add UE
>> sudo ip netns add ue1

# verify namespace
>> sudo ip netns list
```
srsUE config files \
- increase symbol rate (from 11.52e6 to 23.04e6) \
- match tx port (127.0.0.1:2000) and rx_port (127.0.0.1:2001) with gNB
- set device_name to tun_srsue (Tunneling device - for network simulation, only software, not physical hardware) - read more of TUN device on **/common_knowledge/TUN_device.md**
```
[rf]
freq_offset = 0
tx_gain = 50
rx_gain = 40
srate = 23.04e6
nof_antennas = 1

device_name = zmq
device_args = tx_port=tcp://127.0.0.1:2001,rx_port=tcp://127.0.0.1:2000,base_srate=23.04e6

[gw]
netns = ue1
ip_devname = tun_srsue
ip_netmask = 255.255.255.0
```

### 1.2 Testing the network
#### Routing configuraiton
- before being able to ping UE, you need to add a route to the UE on the host machine (open5GS docker container)
  - The ip address group 10.45.0.0/16 is from 10.45.0.1 to 10.45.255.254 (10.45.255.255 is for broadcast)
  - 10.53.1.2 is to AMF (open5GS)
  - ro = route
```
# add a route to the UE on the open5GS docker
>> sudo ip ro add 10.45.0.0/16 via 10.53.1.2

# check the host routing table
>> route -n

Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
0.0.0.0         192.168.0.1     0.0.0.0         UG    100    0        0 eno1
10.45.0.0       10.53.1.2       255.255.0.0     UG    0      0        0 br-dfa5521eb807
10.53.1.0       0.0.0.0         255.255.255.0   U     0      0        0 br-dfa5521eb807
```
Then add a default route for the UE (this can be done when you run the whole system first open5GS docker -> gNB -> srsUE)
```
# add a default route for the UE
>> sudo ip netns exec ue1 ip route add default via 10.45.1.1 dev tun_srsue

# check routing table of ue1
>> sudo ip netns exec ue1 route -n

Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
0.0.0.0         10.45.1.1       0.0.0.0         UG    0      0        0 tun_srsue
10.45.1.0       0.0.0.0         255.255.255.0   U     0      0        0 tun_srsue
```
```
chatchamon@worker01:~/o-ran-e2-kpm/srsRAN_4G/build/srsue/src$ route -n
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
0.0.0.0         172.20.10.1     0.0.0.0         UG    600    0        0 wlp9s0
10.45.0.0       10.53.1.2       255.255.0.0     UG    0      0        0 br-2d2baf4f3a8c
10.53.1.0       0.0.0.0         255.255.255.0   U     0      0        0 br-2d2baf4f3a8c
169.254.0.0     0.0.0.0         255.255.0.0     U     1000   0        0 wlp9s0
172.17.0.0      0.0.0.0         255.255.0.0     U     0      0        0 docker0
172.19.1.0      0.0.0.0         255.255.255.0   U     0      0        0 br-36c6988d1fa9
172.20.10.0     0.0.0.0         255.255.255.240 U     600    0        0 wlp9s0
chatchamon@worker01:~/o-ran-e2-kpm/srsRAN_4G/build/srsue/src$ sudo ip netns exec ue1 ip route add default via 10.45.1.1 dev tun_srsue
[sudo] password for chatchamon: 
chatchamon@worker01:~/o-ran-e2-kpm/srsRAN_4G/build/srsue/src$ sudo ip netns exec ue1 route -n
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
0.0.0.0         10.45.1.1       0.0.0.0         UG    0      0        0 tun_srsue
10.45.1.0       0.0.0.0         255.255.255.0   U     0      0        0 tun_srsue
```
#### 1.3 Ping
- **Uplink**
```
# test connection in uplink
>> sudo ip netns exec ue1 ping 10.45.1.1

>> sudo ip netns exec ue1 ping 10.45.1.1 -c 4
PING 10.45.1.1 (10.45.1.1) 56(84) bytes of data.
64 bytes from 10.45.1.1: icmp_seq=1 ttl=64 time=40.1 ms
64 bytes from 10.45.1.1: icmp_seq=2 ttl=64 time=37.1 ms
64 bytes from 10.45.1.1: icmp_seq=3 ttl=64 time=36.0 ms
64 bytes from 10.45.1.1: icmp_seq=4 ttl=64 time=36.9 ms

--- 10.45.1.1 ping statistics ---
4 packets transmitted, 4 received, 0% packet loss, time 3001ms
rtt min/avg/max/mdev = 36.001/37.526/40.096/1.539 ms

```
- **Downlink**
The assigned IP address can be change everytime UE reconnects to the network. It is best practive to always double-check the latest IP address
```
# run ping in downlink
>> ping <assigned IP address>
>> ping 10.45.1.2
$ ping 10.45.1.2 -c 4
PING 10.45.1.2 (10.45.1.2) 56(84) bytes of data.
64 bytes from 10.45.1.2: icmp_seq=1 ttl=63 time=33.3 ms
64 bytes from 10.45.1.2: icmp_seq=2 ttl=63 time=30.8 ms
64 bytes from 10.45.1.2: icmp_seq=3 ttl=63 time=24.7 ms
64 bytes from 10.45.1.2: icmp_seq=4 ttl=63 time=55.0 ms

--- 10.45.1.2 ping statistics ---
4 packets transmitted, 4 received, 0% packet loss, time 3004ms
rtt min/avg/max/mdev = 24.747/35.979/55.032/11.432 ms
```

#### 1.4 iPerf3
run iPerf client on the UE and iPerf server on the open5GS docker container
```
# open5GS docker
>> iperf3 -s -i 1

# UE TCP
>> sudo ip netns exec ue1 iperf3 -c 10.53.1.1 -i 1 -t 10

# UE UDP
>> sudo ip netns exec ue1 iperf3 -c 10.53.1.1 -i 1 -t 10 -u -b 1M
```

<details close>
  <summary>Log iPerf TCP</summary>

```
# open5GS docker
>> iperf3 -s -i 1
-----------------------------------------------------------
Server listening on 5201
-----------------------------------------------------------
Accepted connection from 10.45.1.2, port 56090
[  5] local 10.53.1.1 port 5201 connected to 10.45.1.2 port 56102
[ ID] Interval           Transfer     Bitrate
[  5]   0.00-1.00   sec   988 KBytes  8.10 Mbits/sec                  
[  5]   1.00-2.00   sec  1.35 MBytes  11.3 Mbits/sec                  
[  5]   2.00-3.00   sec  1.32 MBytes  11.1 Mbits/sec                  
[  5]   3.00-4.00   sec  1.41 MBytes  11.8 Mbits/sec                  
[  5]   4.00-5.00   sec  1.32 MBytes  11.0 Mbits/sec                  
[  5]   5.00-6.00   sec  1.43 MBytes  12.0 Mbits/sec                  
[  5]   6.00-7.00   sec  1.11 MBytes  9.28 Mbits/sec                  
[  5]   7.00-8.00   sec  1.74 MBytes  14.6 Mbits/sec                  
[  5]   8.00-9.00   sec  1.57 MBytes  13.1 Mbits/sec                  
[  5]   9.00-10.00  sec  1.48 MBytes  12.5 Mbits/sec                  
[  5]  10.00-10.19  sec   272 KBytes  11.9 Mbits/sec                  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bitrate
[  5]   0.00-10.19  sec  14.0 MBytes  11.5 Mbits/sec                  receiver

# UE TCP
>> sudo ip netns exec ue1 iperf3 -c 10.53.1.1 -i 1 -t 10
Connecting to host 10.53.1.1, port 5201
[  5] local 10.45.1.2 port 56102 connected to 10.53.1.1 port 5201
[ ID] Interval           Transfer     Bitrate         Retr  Cwnd
[  5]   0.00-1.00   sec  1.38 MBytes  11.5 Mbits/sec    0   82.0 KBytes       
[  5]   1.00-2.00   sec  1.49 MBytes  12.5 Mbits/sec    0    150 KBytes       
[  5]   2.00-3.00   sec  1.93 MBytes  16.2 Mbits/sec    0    218 KBytes       
[  5]   3.00-4.00   sec  1.55 MBytes  13.0 Mbits/sec    0    290 KBytes       
[  5]   4.00-5.00   sec  1.30 MBytes  10.9 Mbits/sec    0    358 KBytes       
[  5]   5.00-6.00   sec  2.42 MBytes  20.3 Mbits/sec    0    431 KBytes       
[  5]   6.00-7.00   sec   954 KBytes  7.82 Mbits/sec   17    327 KBytes       
[  5]   7.00-8.00   sec  1.86 MBytes  15.6 Mbits/sec    0    246 KBytes       
[  5]   8.00-9.00   sec  1.86 MBytes  15.6 Mbits/sec    0    264 KBytes       
[  5]   9.00-10.00  sec   954 KBytes  7.82 Mbits/sec    0    274 KBytes       
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bitrate         Retr
[  5]   0.00-10.00  sec  15.7 MBytes  13.1 Mbits/sec   17             sender
[  5]   0.00-10.19  sec  14.0 MBytes  11.5 Mbits/sec                  receiver
iperf Done.

# gNB tracer
           -----------------DL-----------------------|------------------UL--------------------
 pci rnti  cqi  ri  mcs  brate   ok  nok  (%)  dl_bs | pusch  mcs  brate   ok  nok  (%)    bsr
   1 4601   15   1   27   797k  471    0   0%    359 |  65.5   28    28M  443    0   0%   108k
   1 4601   15   1   28   2.2M 1000    0   0%    185 |  65.5   28    74M 1000    0   0%   300k
   1 4601   15   1   28   706k  350    0   0%      0 |  65.5   28    25M  348    0   0%      0

# UE tracer
---------Signal-----------|-----------------DL-----------------|-----------UL-----------
rat  pci  rsrp   pl   cfo | mcs  snr  iter  brate  bler  ta_us | mcs   buff  brate  bler
 nr    1    40    0   23u |  26   90   1.0    13k    0%    0.0 |  28    0.0   229k    0%
 nr    1    14    0   16u |  27   76   1.5   671k    0%    0.0 |  27    12k    24M    0%
 nr    1    10    0   13u |  27   73   1.8   1.4M    0%    0.0 |  28    65k    51M    0%
 nr    1     8    0  7.8u |  27   73   1.9   2.0M    0%    0.0 |  28   139k    74M    0%
 nr    1     8    0   17u |  27   72   1.8   2.1M    0%    0.0 |  28   215k    74M    0%
 nr    1     7    0   14u |  27   72   1.8   2.0M    0%    0.0 |  28   287k    74M    0%
---------Signal-----------|-----------------DL-----------------|-----------UL-----------
rat  pci  rsrp   pl   cfo | mcs  snr  iter  brate  bler  ta_us | mcs   buff  brate  bler
 nr    1     8    0   14u |  27   72   1.8   2.1M    0%    0.0 |  28   363k    74M    0%
 nr    1     8    0  6.1u |  27   73   1.8   1.8M    0%    0.0 |  28   245k    74M    0%
 nr    1     7    0   13u |  27   73   1.8   2.9M    0%    0.0 |  28   164k    74M    0%
 nr    1     7    0   19u |  27   72   1.8   2.0M    0%    0.0 |  28   186k    74M    0%
 nr    1     7    0   11u |  27   73   1.8   2.0M    0%    0.0 |  28   198k    74M    0%
 nr    1    29    0   21u |  27   84   1.7   229k    0%    0.0 |  27    0.0   6.3M    0%

```
</details>

<details close>
  <summary>Log iPerf UDP</summary>

```
# server
-----------------------------------------------------------
Server listening on 5201
-----------------------------------------------------------
Accepted connection from 10.45.1.2, port 39180
[  5] local 10.53.1.1 port 5201 connected to 10.45.1.2 port 34266
[ ID] Interval           Transfer     Bitrate         Jitter    Lost/Total Datagrams
[  5]   0.00-1.00   sec   113 KBytes   927 Kbits/sec  8.886 ms  0/80 (0%)  
[  5]   1.00-2.00   sec   119 KBytes   973 Kbits/sec  9.109 ms  0/84 (0%)  
[  5]   2.00-3.00   sec   124 KBytes  1.02 Mbits/sec  7.034 ms  0/88 (0%)  
[  5]   3.00-4.00   sec   123 KBytes  1.01 Mbits/sec  8.370 ms  0/87 (0%)  
[  5]   4.00-5.00   sec   122 KBytes   996 Kbits/sec  6.809 ms  0/86 (0%)  
[  5]   5.00-6.00   sec   122 KBytes   996 Kbits/sec  7.167 ms  0/86 (0%)  
[  5]   6.00-7.00   sec   122 KBytes   996 Kbits/sec  7.593 ms  0/86 (0%)  
[  5]   7.00-8.00   sec   122 KBytes   996 Kbits/sec  8.278 ms  0/86 (0%)  
[  5]   8.00-9.00   sec   120 KBytes   985 Kbits/sec  6.509 ms  0/85 (0%)  
[  5]   9.00-10.00  sec   126 KBytes  1.03 Mbits/sec  11.210 ms  0/89 (0%)  
[  5]  10.00-10.08  sec  9.90 KBytes   955 Kbits/sec  9.501 ms  0/7 (0%)  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bitrate         Jitter    Lost/Total Datagrams
[  5]   0.00-10.08  sec  1.19 MBytes   992 Kbits/sec  9.501 ms  0/864 (0%)  receiver
-----------------------------------------------------------

# UE UDP
>> sudo ip netns exec ue1 iperf3 -c 10.53.1.1 -i 1 -t 10 -u -b 1M
Connecting to host 10.53.1.1, port 5201
[  5] local 10.45.1.2 port 34266 connected to 10.53.1.1 port 5201
[ ID] Interval           Transfer     Bitrate         Total Datagrams
[  5]   0.00-1.00   sec   123 KBytes  1.01 Mbits/sec  87  
[  5]   1.00-2.00   sec   122 KBytes   996 Kbits/sec  86  
[  5]   2.00-3.00   sec   122 KBytes   996 Kbits/sec  86  
[  5]   3.00-4.00   sec   123 KBytes  1.01 Mbits/sec  87  
[  5]   4.00-5.00   sec   122 KBytes   996 Kbits/sec  86  
[  5]   5.00-6.00   sec   122 KBytes   996 Kbits/sec  86  
[  5]   6.00-7.00   sec   123 KBytes  1.01 Mbits/sec  87  
[  5]   7.00-8.00   sec   122 KBytes   996 Kbits/sec  86  
[  5]   8.00-9.00   sec   122 KBytes   996 Kbits/sec  86  
[  5]   9.00-10.00  sec   123 KBytes  1.01 Mbits/sec  87  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bitrate         Jitter    Lost/Total Datagrams
[  5]   0.00-10.00  sec  1.19 MBytes  1.00 Mbits/sec  0.000 ms  0/864 (0%)  sender
[  5]   0.00-10.08  sec  1.19 MBytes   992 Kbits/sec  9.501 ms  0/864 (0%)  receiver

# gNB tracer
           -----------------DL-----------------------|------------------UL--------------------
 pci rnti  cqi  ri  mcs  brate   ok  nok  (%)  dl_bs | pusch  mcs  brate   ok  nok  (%)    bsr
   1 4601   15   1   27    37k   56    0   0%      0 |  65.5   28   1.4M  108    0   0%  2.01k
   1 4601   15   1   27    36k   57    0   0%      0 |  65.5   28   2.3M  125    0   0%      0
   1 4601   15   1   27    41k   64    0   0%      0 |  65.5   28   2.0M  141    0   0%  5.45k
   1 4601   15   1   27    45k   70    0   0%      0 |  65.5   28   2.2M  153    0   0%  2.01k
   1 4601   15   1   27    44k   70    0   0%      0 |  65.5   28   2.1M  136    0   0%  2.01k
   1 4601   15   1   27    44k   70    0   0%      0 |  65.5   28   2.1M  131    0   0%  2.01k
   1 4601   15   1   27    39k   61    0   0%      0 |  65.5   28   2.1M  132    0   0%  2.01k
   1 4601   15   1   27    39k   61    0   0%      0 |  65.5   28   2.3M  122    0   0%      0
   1 4601   15   1   27    41k   64    0   0%      0 |  65.5   28   2.1M  146    0   0%  2.01k
   1 4601   15   1   27    41k   60    0   0%      0 |  65.5   28   1.9M  131    0   0%      0
   1 4601   15   1   26   1.8k    3    0   0%      0 |  65.5   28    13k    6    0   0%      0

# UE tracer
 ---------Signal-----------|-----------------DL-----------------|-----------UL-----------
rat  pci  rsrp   pl   cfo | mcs  snr  iter  brate  bler  ta_us | mcs   buff  brate  bler
 nr    1    34    0   23u |  26   87   1.0    37k    0%    0.0 |  27    0.0   1.4M    0%
 nr    1    34    0   23u |  26   86   1.0    37k    0%    0.0 |  27    0.0   2.3M    0%
 nr    1    33    0   20u |  26   86   1.0    41k    0%    0.0 |  27    0.0   2.1M    0%
 nr    1    33    0   20u |  26   86   1.0    44k    0%    0.0 |  27   2.4k   2.0M    0%
 nr    1    33    0   23u |  26   86   1.0    42k    0%    0.0 |  27   1.5k   2.2M    0%
 nr    1    33    0   21u |  26   85   1.0    46k    0%    0.0 |  27   3.0k   2.1M    0%
 nr    1    33    0   23u |  26   86   1.0    40k    0%    0.0 |  27    0.0   2.2M    0%
 nr    1    34    0   18u |  26   86   1.0    37k    0%    0.0 |  27   1.5k   2.2M    0%
 nr    1    33    0   23u |  26   86   1.0    43k    0%    0.0 |  27    863   2.1M    0%
 nr    1    34    0   22u |  26   86   1.0    39k    0%    0.0 |  27   2.4k   2.1M    0%
 nr    1    38    0   24u |  26   88   1.0    23k    0%    0.0 |  27    0.0   913k    0%
```
</details>


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
```