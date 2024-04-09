### test uhd
- go to '/usr/local/lib/uhd/example'
```
sudo ./benchmark_rate --rx_rate 10e6 --tx_rate 10e6

[INFO] [UHD] linux; GNU C++ version 10.5.0; Boost_107400; UHD_4.0.0.HEAD-0-g90ce6062
[00:00:00.000118] Creating the usrp device with: ...
[INFO] [B200] Detected Device: B210
[INFO] [B200] Operating over USB 3.
[INFO] [B200] Initialize CODEC control...
[INFO] [B200] Initialize Radio control...
[INFO] [B200] Performing register loopback test... 
[INFO] [B200] Register loopback test passed
[INFO] [B200] Performing register loopback test... 
[INFO] [B200] Register loopback test passed
[INFO] [B200] Setting master clock rate selection to 'automatic'.
[INFO] [B200] Asking for clock rate 16.000000 MHz... 
[INFO] [B200] Actually got clock rate 16.000000 MHz.
Using Device: Single USRP:
  Device: B-Series Device
  Mboard 0: B210
  RX Channel: 0
    RX DSP: 0
    RX Dboard: A
    RX Subdev: FE-RX2
  RX Channel: 1
    RX DSP: 1
    RX Dboard: A
    RX Subdev: FE-RX1
  TX Channel: 0
    TX DSP: 0
    TX Dboard: A
    TX Subdev: FE-TX2
  TX Channel: 1
    TX DSP: 1
    TX Dboard: A
    TX Subdev: FE-TX1

[00:00:02.295728978] Setting device timestamp to 0...
[INFO] [B200] Asking for clock rate 40.000000 MHz... 
[INFO] [B200] Actually got clock rate 40.000000 MHz.
[00:00:02.692968427] Testing receive rate 10.000000 Msps on 1 channels
Setting TX spp to 2040
[00:00:02.715658392] Testing transmit rate 10.000000 Msps on 1 channels
[00:00:12.972366349] Benchmark complete.


Benchmark rate summary:
  Num received samples:     102746818
  Num dropped samples:      0
  Num overruns detected:    0
  Num transmitted samples:  102585480
  Num sequence errors (Tx): 0
  Num sequence errors (Rx): 0
  Num underruns detected:   0
  Num late commands:        0
  Num timeouts (Tx):        0
  Num timeouts (Rx):        0


Done!

```