### [ ] have problem with gNB

- gnb Late: 2340; Underflow: 15; Overflow: 1;
Error: exceeded maximum number of timed out transmissions.
- maybe fix with run performance mode (https://github.com/srsran/srsRAN_Project/discussions/316) , underflow once in a while is okay



```
$ sudo ./gnb -c gnb_rf_b210_fdd_srsUE.yml 

The PRACH detector will not meet the performance requirements with the configuration {Format 0, ZCZ 0, SCS 1.25kHz, Rx ports 1}.
Lower PHY in quad executor mode.

--== srsRAN gNB (commit 2f90c8b60) ==--

Connecting to AMF on 10.53.1.2:38412
Available radio types: uhd and zmq.
[INFO] [UHD] linux; GNU C++ version 10.5.0; Boost_107400; UHD_4.0.0.HEAD-0-g90ce6062
[INFO] [LOGGING] Fastpath logging disabled at runtime.
Making USRP object with args 'type=b200'
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
[INFO] [MULTI_USRP] Setting master clock rate selection to 'manual'.
[INFO] [B200] Asking for clock rate 23.040000 MHz... 
[INFO] [B200] Actually got clock rate 23.040000 MHz.
Cell pci=1, bw=20 MHz, dl_arfcn=368500 (n3), dl_freq=1842.5 MHz, dl_ssb_arfcn=368410, ul_freq=1747.5 MHz

==== gNodeB started ===
Type <t> to view trace
Late: 0; Underflow: 5; Overflow: 0;
Late: 4; Underflow: 1; Overflow: 0;
Late: 0; Underflow: 1; Overflow: 0;
Late: 3; Underflow: 5; Overflow: 0;
Late: 0; Underflow: 4; Overflow: 0;
t
t
Late: 0; Underflow: 1; Overflow: 0;
Late: 4; Underflow: 5; Overflow: 0;
Late: 0; Underflow: 4; Overflow: 0;
Late: 19; Underflow: 7; Overflow: 0;
Late: 2340; Underflow: 15; Overflow: 1;
Error: exceeded maximum number of timed out transmissions.
Late: 6000; Underflow: 23; Overflow: 0;
Error: exceeded maximum number of timed out transmissions.
Late: 6000; Underflow: 22; Overflow: 0;
Error: exceeded maximum number of timed out transmissions.
```

- follow this one to config gnb to match with the isim of ue and freq band (https://github.com/srsran/srsRAN_Project/discussions/321)


#### gnu radio w/ USRP B210
- https://wiki.gnuradio.org/index.php/USRP_Source